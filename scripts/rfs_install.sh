#!/bin/sh

KERNEL=kernel_current
RFS=build_current

function modify_config_fs () {
	local config=$KERNEL/fs/Kconfig

	# modify configuration
	grep -q "source \"fs\/rfs\/Kconfig\"" $config
	if [ $? -eq 1 ]; then
		sed -i.bak -e '
/config CRAMFS$/ i\
source \"fs/rfs/Kconfig\"\
' $config
	fi

	# from linux-2.6.29, fs/Kconfig is changed
	grep -q "source \"fs\/rfs\/Kconfig\"" $config
	if [ $? -eq 1 ]; then
		sed -i.bak -e '
/if MISC_FILESYSTEMS/ a\
\
source \"fs/rfs/Kconfig\"
' $config
	fi

}

function modify_makefile_fs () {
	local make=$KERNEL/fs/Makefile

	# modify makefile
	grep -q "CONFIG_RFS_FS" $make
	if [ $? -eq 1 ]; then
		sed -i.bak -e '
/CONFIG_CRAMFS/ a\
obj-$(CONFIG_RFS_FS)		+= rfs/
' $make
	fi
}

function do_link () {
	local NESTLE_BASE=../../../$RFS

	ln -sf $NESTLE_BASE/fs/rfs $KERNEL/fs/
}

#Setup
modify_config_fs
modify_makefile_fs
echo "..complete to modify config, makefile"

do_link
echo "..complete to make link"

echo "Setup complete"

