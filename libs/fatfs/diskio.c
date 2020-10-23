/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Low level disk I/O module for Petit FatFs
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include "diskio.h"

/*
 * Initialize Disk Drive
 */
DSTATUS disk_initialize(void)
{
	return STA_NOINIT;
}

/*
 * Read Partial Sector
 *
 * buff:   pointer to the destination object
 * sector: sector number (LBA)
 * offset: offset in the sector
 * count:  byte count (bit15:destination)
 */
DRESULT disk_readp(BYTE* buff, DWORD sector, UINT offset, UINT count)
{
	return RES_ERROR;
}

