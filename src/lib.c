#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include "mtkfm_lib.h"

#include "mtk_ioctl.h"


static const char* errstrings[] = {
	"None",
	"Failed",
	"Invalid parameter",
	"Bad status",
	"Tuning failed",
	"Seek failed",
	"Busy",
	"Scan failed"
};


int mtkfm_lib_opendevice()
{
	return open("/dev/fm", O_RDONLY);	
}


void mtkfm_lib_closedevice(int fd)
{
	close(fd);
}


int mtkfm_lib_printhwinfo(int fd)
{
	struct fm_hw_info hwinfo;

	if(ioctl(fd, FM_IOCTL_GET_HW_INFO, &hwinfo) != 0)
	{
		printf("FM_IOCTL_GET_HW_INFO ioctl failed\n");
		return 0;
	}

	printf("Chip ID: %x\n", hwinfo.chip_id);	
	printf("ECO version: %x\n", hwinfo.eco_ver);	
	printf("ROM Version: %x\n", hwinfo.rom_ver);	
	printf("DSP patch version: %x\n", hwinfo.patch_ver);	

	return 1;
}


int mtkfm_lib_powerup(int fd, uint32_t freq)
{
	struct fm_tune_parm tuneparm;

	memset(&tuneparm, 0, sizeof(struct fm_tune_parm));

	// Set "safe" defaults for powerup
	tuneparm.band = 1;
	tuneparm.space = 1;
	tuneparm.hilo = 0;
	tuneparm.freq = (fm_u16) (freq / 100);
	printf("tuneparm.freq = %i\n", tuneparm.freq);

	if(ioctl(fd, FM_IOCTL_POWERUP, &tuneparm) != 0)
	{
		printf("FM_IOCTL_POWERUP ioctl failed\n");
		return tuneparm.err;
	}
		
	return 1;
}


int mtkfm_lib_poweruptx(int fd, uint32_t freq)
{
	struct fm_tune_parm tuneparm;

	memset(&tuneparm, 0, sizeof(struct fm_tune_parm));

	// Set "safe" defaults for powerup
	tuneparm.band = 1;
	tuneparm.space = 1;
	tuneparm.hilo = 0;
	tuneparm.freq = (fm_u16) (freq / 100);
	printf("TX tuneparm.freq = %i\n", tuneparm.freq);

	if(ioctl(fd, FM_IOCTL_POWERUP_TX, &tuneparm) != 0)
	{
		printf("FM_IOCTL_POWERUP_TX ioctl failed\n");
		return tuneparm.err;
	}
		
	return 1;
}


int mtkfm_lib_tune(int fd, uint32_t freq)
{
	struct fm_tune_parm tuneparm;

	memset(&tuneparm, 0, sizeof(struct fm_tune_parm));

	// Set "safe" defaults for powerup
	tuneparm.band = 1;
	tuneparm.space = 1;
	tuneparm.hilo = 0;
	tuneparm.freq = (fm_u16) (freq / 100);
	printf("tuneparm.freq = %i\n", tuneparm.freq);

	if(ioctl(fd, FM_IOCTL_TUNE, &tuneparm) != 0)
	{
		printf("FM_IOCTL_TUNE ioctl failed\n");
		return tuneparm.err;
	}
		
	return tuneparm.freq;
}


int mtkfm_lib_seek(int fd)
{
	struct fm_seek_parm seekparm;

	seekparm.band = 1;
	seekparm.space = 1;
	seekparm.hilo = 0;
	seekparm.seekdir = 1;
	seekparm.seekth = 4;

	if(ioctl(fd, FM_IOCTL_SEEK, &seekparm) != 0)
	{
		printf("FM_IOCTL_SEEK ioctl failed\n");
		return seekparm.err;
	}
		
	return seekparm.freq;
}


int mtkfm_lib_setvolume(int fd, uint32_t volume)

{
	if(ioctl(fd, FM_IOCTL_SETVOL, &volume) != 0)
	{
		printf("FM_IOCTL_SETVOL, ioctl failed\n");
		return 0;
	}
		
	return 1;
}


uint32_t mtkfm_lib_getvolume(int fd)
{
	uint32_t volume;

	if(ioctl(fd, FM_IOCTL_GETVOL, &volume) != 0)
	{
		printf("FM_IOCTL_GETVOL, ioctl failed\n");
		return -1;
	}
		
	return volume;
}


int mtkfm_lib_setmute(int fd, uint32_t mute)

{
	if(ioctl(fd, FM_IOCTL_MUTE, &mute) != 0)
	{
		printf("FM_IOCTL_MUTE, ioctl failed\n");
		return 0;
	}
		
	return 1;
}


int mtkfm_lib_getrssi(int fd, uint32_t* rssi)
{
	if(ioctl(fd, FM_IOCTL_GETRSSI, rssi) != 0)
	{
		printf("FM_IOCTL_GET_RSSI ioctl failed\n");
		return 0;
	}

	return 1;
}


const char* mtkfm_lib_errstring(int errcode)
{
	if(errcode >= 0 &&
	   errcode <= 7)
		return errstrings[errcode];

	return "";
}
