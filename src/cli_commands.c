#include <stdio.h>
#include <stdlib.h>

#include "mtkfm_cli.h"
#include "mtkfm_lib.h"

int mtkfm_command_hwinfo(int argc, char** argv)
{
	int fd;
	int ret;

	// Open the device
	fd = mtkfm_lib_opendevice();

	if(fd == -1)
	{
		printf("Can't open device\n");
		return EXIT_FAILURE;
	}

	// Power on and tune
	printf("Powering up...\n");

	ret = mtkfm_lib_powerup(fd, 100000);

	if(!ret)
	{
		printf("Power on error: %s\n", mtkfm_lib_errstring(ret));
		return EXIT_FAILURE;
	}

	// Print HW info
	if(!mtkfm_lib_printhwinfo(fd))
	{
		printf("Could not get hardware info\n");
		return EXIT_FAILURE;
	}

	// Close device
	mtkfm_lib_closedevice(fd);

	return EXIT_SUCCESS;
}


int mtkfm_command_powerup(int argc, char** argv)
{
	int fd;
	long int freq;
	int ret;
	uint32_t rssi;
	
	if(argc != 3)
	{
		printf("Usage: mtkfmcli powerup <freq>\n");
		return EXIT_FAILURE;
	}

	// Convert frequency
	freq = strtol(argv[2], NULL, 10);

	if(freq < 76000)
	{
		printf("Minimum freqency is 76000 kHz\n");
		return EXIT_FAILURE;
	}

	// Open the device
	fd = mtkfm_lib_opendevice();

	if(fd == -1)
	{
		printf("Can't open device\n");
		return EXIT_FAILURE;
	}

	// Power on and tune
	printf("Powering up and tuning to %li kHz...\n", freq);

	ret = mtkfm_lib_powerup(fd, freq);

	if(!ret)
	{
		printf("Power up error: %s\n", mtkfm_lib_errstring(ret));
		return EXIT_FAILURE;
	}

	printf("FM volume is %i, setting to 15\n", mtkfm_lib_getvolume(fd));
	mtkfm_lib_setvolume(fd, 15);
	printf("FM volume is now %i\n", mtkfm_lib_getvolume(fd));

	// unmute
	printf("Unmuting...\n");
	ret = mtkfm_lib_setmute(fd, 0);

	// Power on and tune
	printf("Tuning...\n");

	ret = mtkfm_lib_tune(fd, freq);

	if(!ret)
	{
		printf("Failure while tuning: %s\n", mtkfm_lib_errstring(ret));
		return EXIT_FAILURE;
	}

	printf("Tuned to %i\n", ret);

	while(1)
	{
		sleep(1);

		ret = mtkfm_lib_getrssi(fd, &rssi);
		
		if(!ret)
		{
			printf("Failed to get RSSI!\n");
			return EXIT_FAILURE;
		}

		printf("RSSI: %i\n", rssi);
	}

	// Close device
	mtkfm_lib_closedevice(fd);

	return EXIT_SUCCESS;
}


int mtkfm_command_poweruptx(int argc, char** argv)
{
	int fd;
	long int freq;
	int ret;
	
	if(argc != 3)
	{
		printf("Usage: mtkfmcli poweruptx <freq>\n");
		return EXIT_FAILURE;
	}

	// Convert frequency
	freq = strtol(argv[2], NULL, 10);

	if(freq < 76000)
	{
		printf("Minimum freqency is 76000 kHz\n");
		return EXIT_FAILURE;
	}

	// Open the device
	fd = mtkfm_lib_opendevice();

	if(fd == -1)
	{
		printf("Can't open device\n");
		return EXIT_FAILURE;
	}

	// Power on and tune
	printf("Powering up TX and tuning to %li kHz...\n", freq);

	ret = mtkfm_lib_poweruptx(fd, freq);

	if(!ret)
	{
		printf("Power up error: %s\n", mtkfm_lib_errstring(ret));
		return EXIT_FAILURE;
	}

	//printf("FM volume is %i, setting to 15\n", mtkfm_lib_getvolume(fd));
	//mtkfm_lib_setvolume(fd, 15);
	//printf("FM volume is now %i\n", mtkfm_lib_getvolume(fd));

	// unmute
	//printf("Unmuting...\n");
	//ret = mtkfm_lib_setmute(fd, 0);

	// Power on and tune
	//printf("Tuning...\n");

	//ret = mtkfm_lib_tune(fd, freq);

	//if(!ret)
	//{
	//	printf("Failure while tuning: %s\n", mtkfm_lib_errstring(ret));
	//	return EXIT_FAILURE;
	//}

	//printf("Tuned to %i\n", ret);

	//sleep(4);

	sleep(500);

	// Close device
	mtkfm_lib_closedevice(fd);

	return EXIT_SUCCESS;
}


int mtkfm_command_scan(int argc, char** argv)
{
	return EXIT_FAILURE;
}

