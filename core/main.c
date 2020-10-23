/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <libs/fatfs/pff.h>
#include <mcu/common.h>

void main(void)
{
	FATFS fatfs;
	FRESULT ret;

	ret = pf_mount(&fatfs);
	if (ret != FR_OK) {
		uart_printf("unable to mount filesystem");
	}

	while (1) {
		;;
	}
}

