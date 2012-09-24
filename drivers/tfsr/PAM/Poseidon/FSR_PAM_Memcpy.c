/**
 *   @mainpage   Flex Sector Remapper : LinuStoreIII_1.2.0_b036-FSR_1.2.1p1_b139_RTM
 *
 *   @section Intro
 *       Flash Translation Layer for Flex-OneNAND and OneNAND
 *    
 *    @section  Copyright
 *---------------------------------------------------------------------------*
 *                                                                           *
 * Copyright (C) 2003-2010 Samsung Electronics                               *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License version 2 as         *
 * published by the Free Software Foundation.                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 *
 *     @section Description
 *
 */

/**
 * @file      FSR_PAM_Memcpy.c
 * @brief     memcpy32
 * @author    SongHo Yoon
 * @date      21-NOV-2007
 * @remark
 * REVISION HISTORY
 * @n  21-NOV-2007 [SongHo Yoon] : first writing
 *
 */

#include "FSR.h"

/*****************************************************************************/
/* Function Implementation                                                   */
/*****************************************************************************/

/**
 * @brief           memcpy
 *
 * @return          none
 *
 * @author          SongHo Yoon
 * @version         1.0.0
 *
 */
PUBLIC VOID
memcpy32 (VOID       *pDst,
          VOID       *pSrc,
          UINT32     nSize)
{
    UINT32   nIdx;
    UINT32  *pSrc32;
    UINT32  *pDst32;
    UINT32   nSize32;


    pSrc32  = (UINT32 *)(pSrc);
    pDst32  = (UINT32 *)(pDst);
    nSize32 = nSize / sizeof (UINT32);

    for(nIdx = 0; nIdx < nSize32; nIdx++)
    {
        pDst32[nIdx] = pSrc32[nIdx];
    }
}
