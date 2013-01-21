/* arch/arm/mach-msm/memory.c
 *
 * Copyright (C) 2007 Google, Inc.
 * Copyright (c) 2009-2010, Code Aurora Forum. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/bootmem.h>
#include <linux/memory_alloc.h>
#include <linux/module.h>
#include <linux/memory_alloc.h>
#include <linux/memblock.h>
#include <asm/pgtable.h>
#include <asm/io.h>
#include <asm/mach/map.h>
#include <asm/cacheflush.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <mach/msm_memtypes.h>
#include <mach/msm_memtypes.h>
#include <linux/hardirq.h>
#include <linux/android_pmem.h>
#if defined(CONFIG_MSM_NPA_REMOTE)
#include "npa_remote.h"
#include <linux/completion.h>
#include <linux/err.h>
#endif

int arch_io_remap_pfn_range(struct vm_area_struct *vma, unsigned long addr,
			    unsigned long pfn, unsigned long size, pgprot_t prot)
{
	unsigned long pfn_addr = pfn << PAGE_SHIFT;
	if ((pfn_addr >= 0x88000000) && (pfn_addr < 0xD0000000)) {
		prot = pgprot_device(prot);
		printk("remapping device %lx\n", prot);
	}
	return remap_pfn_range(vma, addr, pfn, size, prot);
}

void *strongly_ordered_page;

/*
 * The trick of making the zero page strongly ordered no longer
 * works. We no longer want to make a second alias to the zero
 * page that is strongly ordered. Manually changing the bits
 * in the page table for the zero page would have side effects
 * elsewhere that aren't necessary. The result is that we need
 * to get a page from else where. Given when the first call
 * to write_to_strongly_ordered_memory occurs, using bootmem
 * to get a page makes the most sense.
 */
void map_page_strongly_ordered(void)
{
#if defined(CONFIG_ARCH_MSM7X27)
	long unsigned int phys;

	if (strongly_ordered_page)
		return;

	strongly_ordered_page = alloc_bootmem(PAGE_SIZE);
	phys = __pa(strongly_ordered_page);
	ioremap_page((long unsigned int) strongly_ordered_page,
		phys,
		get_mem_type(MT_DEVICE_STRONGLY_ORDERED));
	printk(KERN_ALERT "Initialized strongly ordered page successfully\n");
#endif
}
EXPORT_SYMBOL(map_page_strongly_ordered);

void write_to_strongly_ordered_memory(void)
{
#if defined(CONFIG_ARCH_MSM7X27)
	if (!strongly_ordered_page) {
		if (!in_interrupt())
			map_page_strongly_ordered();
		else {
			printk(KERN_ALERT "Cannot map strongly ordered page in "
				"Interrupt Context\n");
			/* capture it here before the allocation fails later */
			BUG();
		}
	}
	*(int *)strongly_ordered_page = 0;
#endif
}
EXPORT_SYMBOL(write_to_strongly_ordered_memory);

void flush_axi_bus_buffer(void)
{
#if defined(CONFIG_ARCH_MSM7X27)
	__asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 5" \
				    : : "r" (0) : "memory");
	write_to_strongly_ordered_memory();
#endif
}

#define CACHE_LINE_SIZE 32

/* These cache related routines make the assumption that the associated
 * physical memory is contiguous. They will operate on all (L1
 * and L2 if present) caches.
 */
void clean_and_invalidate_caches(unsigned long vstart,
	unsigned long length, unsigned long pstart)
{
	unsigned long vaddr;

	for (vaddr = vstart; vaddr < vstart + length; vaddr += CACHE_LINE_SIZE)
		asm ("mcr p15, 0, %0, c7, c14, 1" : : "r" (vaddr));
#ifdef CONFIG_OUTER_CACHE
	outer_flush_range(pstart, pstart + length);
#endif
	asm ("mcr p15, 0, %0, c7, c10, 4" : : "r" (0));
	asm ("mcr p15, 0, %0, c7, c5, 0" : : "r" (0));

	flush_axi_bus_buffer();
}

void clean_caches(unsigned long vstart,
	unsigned long length, unsigned long pstart)
{
	unsigned long vaddr;

	for (vaddr = vstart; vaddr < vstart + length; vaddr += CACHE_LINE_SIZE)
		asm ("mcr p15, 0, %0, c7, c10, 1" : : "r" (vaddr));
#ifdef CONFIG_OUTER_CACHE
	outer_clean_range(pstart, pstart + length);
#endif
	asm ("mcr p15, 0, %0, c7, c10, 4" : : "r" (0));
	asm ("mcr p15, 0, %0, c7, c5, 0" : : "r" (0));

	flush_axi_bus_buffer();
}

void invalidate_caches(unsigned long vstart,
	unsigned long length, unsigned long pstart)
{
	unsigned long vaddr;

	for (vaddr = vstart; vaddr < vstart + length; vaddr += CACHE_LINE_SIZE)
		asm ("mcr p15, 0, %0, c7, c6, 1" : : "r" (vaddr));
#ifdef CONFIG_OUTER_CACHE
	outer_inv_range(pstart, pstart + length);
#endif
	asm ("mcr p15, 0, %0, c7, c10, 4" : : "r" (0));
	asm ("mcr p15, 0, %0, c7, c5, 0" : : "r" (0));

	flush_axi_bus_buffer();
}

void *alloc_bootmem_aligned(unsigned long size, unsigned long alignment)
{
	void *unused_addr = NULL;
	unsigned long addr, tmp_size, unused_size;

	/* Allocate maximum size needed, see where it ends up.
	 * Then free it -- in this path there are no other allocators
	 * so we can depend on getting the same address back
	 * when we allocate a smaller piece that is aligned
	 * at the end (if necessary) and the piece we really want,
	 * then free the unused first piece.
	 */

	tmp_size = size + alignment - PAGE_SIZE;
	addr = (unsigned long)alloc_bootmem(tmp_size);
	free_bootmem(__pa(addr), tmp_size);

	unused_size = alignment - (addr % alignment);
	if (unused_size)
		unused_addr = alloc_bootmem(unused_size);

	addr = (unsigned long)alloc_bootmem(size);
	if (unused_size)
		free_bootmem(__pa(unused_addr), unused_size);

	return (void *)addr;
}

int platform_physical_remove_pages(unsigned long start_pfn,
	unsigned long nr_pages)
{
	return 1;
}

int platform_physical_active_pages(unsigned long start_pfn,
	unsigned long nr_pages)
{
	return 1;
}

int platform_physical_low_power_pages(unsigned long start_pfn,
	unsigned long nr_pages)
{
	return 1;
}

unsigned long allocate_contiguous_ebi_nomap(unsigned long size,
	unsigned long align)
{
  return _allocate_contiguous_memory_nomap(size, MEMTYPE_EBI0,
	align, __builtin_return_address(0));
}
EXPORT_SYMBOL(allocate_contiguous_ebi_nomap);

char *memtype_name[] = {
       "SMI_KERNEL",
       "SMI",
       "EBI0",
       "EBI1"
};

struct reserve_info *reserve_info;

static void __init calculate_reserve_limits(void)
{
       int i;
       struct membank *mb;
       int memtype;
       struct memtype_reserve *mt;

       for (i = 0, mb = &meminfo.bank[0]; i < meminfo.nr_banks; i++, mb++)  {
               memtype = reserve_info->paddr_to_memtype(mb->start);
               if (memtype == MEMTYPE_NONE) {
                       pr_warning("unknown memory type for bank at %lx\n",
                               mb->start);
                       continue;
               }
               mt = &reserve_info->memtype_reserve_table[memtype];
               mt->limit = max(mt->limit, mb->size);
       }
}

static void __init adjust_reserve_sizes(void)
{
       int i;
       struct memtype_reserve *mt;

       mt = &reserve_info->memtype_reserve_table[0];
       for (i = 0; i < MEMTYPE_MAX; i++, mt++) {
               if (mt->flags & MEMTYPE_FLAGS_1M_ALIGN)
                       mt->size = (mt->size + SECTION_SIZE - 1) & SECTION_MASK;
               if (mt->size > mt->limit) {
                       pr_warning("%lx size for %s too large, setting to %lx\n",
                               mt->size, memtype_name[i], mt->limit);
                       mt->size = mt->limit;
               }
       }
}

static void __init reserve_memory_for_mempools(void)
{
       int i, memtype, membank_type;
       struct memtype_reserve *mt;
       struct membank *mb;
       int ret;

       mt = &reserve_info->memtype_reserve_table[0];
       for (memtype = 0; memtype < MEMTYPE_MAX; memtype++, mt++) {
               if (mt->flags & MEMTYPE_FLAGS_FIXED || !mt->size)
                       continue;

               /* We know we will find a memory bank of the proper size
                * as we have limited the size of the memory pool for
                * each memory type to the size of the largest memory
                * bank. Choose the memory bank with the highest physical
                * address which is large enough, so that we will not
                * take memory from the lowest memory bank which the kernel
                * is in (and cause boot problems) and so that we might
                * be able to steal memory that would otherwise become
                * highmem.
                */
               for (i = meminfo.nr_banks - 1; i >= 0; i--) {
                       mb = &meminfo.bank[i];
                       membank_type =
                               reserve_info->paddr_to_memtype(mb->start);
                       if (memtype != membank_type)
                               continue;
                       if (mb->size >= mt->size) {
                               mt->start = mb->start + mb->size - mt->size;
                               ret = memblock_remove(mt->start, mt->size);
                               BUG_ON(ret);
                               break;
                       }
               }
       }
}

static void __init initialize_mempools(void)
{
       struct mem_pool *mpool;
       int memtype;
       struct memtype_reserve *mt;

       mt = &reserve_info->memtype_reserve_table[0];
       for (memtype = 0; memtype < MEMTYPE_MAX; memtype++, mt++) {
               if (!mt->size)
                       continue;
               mpool = initialize_memory_pool(mt->start, mt->size, memtype);
               if (!mpool)
                       pr_warning("failed to create %s mempool\n",
                               memtype_name[memtype]);
       }
}

void __init msm_reserve(void)
{
       memory_pool_init();
       reserve_info->calculate_reserve_sizes();
       calculate_reserve_limits();
       adjust_reserve_sizes();
       reserve_memory_for_mempools();
       initialize_mempools();
}

/* emulation of the deprecated pmem_kalloc and pmem_kfree */
int32_t pmem_kalloc(const size_t size, const uint32_t flags)
{
       int pmem_memtype;
       int memtype = MEMTYPE_NONE;
       int ebi1_memtype = MEMTYPE_EBI1;
       unsigned int align;
       int32_t paddr;

       switch (flags & PMEM_ALIGNMENT_MASK) {
       case PMEM_ALIGNMENT_4K:
               align = SZ_4K;
               break;
       case PMEM_ALIGNMENT_1M:
               align = SZ_1M;
               break;
       default:
               pr_alert("Invalid alignment %x\n",
                       (flags & PMEM_ALIGNMENT_MASK));
               return -EINVAL;
       }

       /* on 7x30 and 8x55 "EBI1 kernel PMEM" is really on EBI0 */
       if (machine_is_msm7x30_surf() || machine_is_msm7x30_fluid() ||
               machine_is_msm8x55_svlte_surf() ||
               machine_is_msm8x55_svlte_ffa())
                       ebi1_memtype = MEMTYPE_EBI0;

       pmem_memtype = flags & PMEM_MEMTYPE_MASK;
       if (pmem_memtype == PMEM_MEMTYPE_EBI1)
               memtype = ebi1_memtype;
       else if (pmem_memtype == PMEM_MEMTYPE_SMI)
               memtype = MEMTYPE_SMI_KERNEL;
       else {
               pr_alert("Invalid memory type %x\n",
                       flags & PMEM_MEMTYPE_MASK);
               return -EINVAL;
       }

       paddr = allocate_contiguous_memory_nomap(size, memtype, align);
       if (!paddr && pmem_memtype == PMEM_MEMTYPE_SMI)
               paddr = allocate_contiguous_memory_nomap(size,
                       ebi1_memtype, align);

       if (!paddr)
               return -ENOMEM;
       return paddr;
}
EXPORT_SYMBOL(pmem_kalloc);

int pmem_kfree(const int32_t physaddr)
{
       free_contiguous_memory_by_paddr(physaddr);

       return 0;
}
EXPORT_SYMBOL(pmem_kfree);
