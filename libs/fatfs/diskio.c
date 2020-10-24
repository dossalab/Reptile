/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Low level disk I/O module for Petit FatFs
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <drivers/sdcard.h>
#include <board/common.h>
#include "diskio.h"

static struct sdcard card;

/*
 * Initialize Disk Drive
 */
DSTATUS disk_initialize(void)
{
	DSTATUS ret = 0;

	sdcard_init(&card, BOARD_SDCARD_CS_PORT, BOARD_SDCARD_CS_PIN);
	if (!sdcard_probe(&card)) {
		ret |= STA_NOINIT;
	}

	return ret;
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
	if (sdcard_read(&card, buff, sector, offset, count) < 0) {
		return RES_ERROR;
	}

	return RES_OK;
}

