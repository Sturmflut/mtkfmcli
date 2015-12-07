#include <stdio.h>
#include <stdlib.h>

#include "mtkfm_cli.h"


void print_usage()
{
	printf("Usage: mtkfmcli <command> <argument1> <argument2>\n");
	printf("\n");
	printf("Status commands:\n");
	printf("  hwinfo               Show hardware info\n");
	printf("\n");
	printf("Control commands\n");
	printf("  powerup <freq>       Power the FM radio on and tune it to <freq> kHz\n");
	printf("  powertx <freq>       Power the FM transmitter on and tune it to <freq> kHz\n");
	printf("  scan                 Scan the whole frequency range for stations\n");
	printf("  poweroff             Power the FM radio off\n");
}


int main(int argc, char** argv)
{
	if(argc < 2)
	{
		print_usage();
		return 1;
	}

	if(strncmp("hwinfo", argv[1], 6) == 0)
		return mtkfm_command_hwinfo(argc, argv);

	if(strncmp("powerup", argv[1], 7) == 0)
		return mtkfm_command_powerup(argc, argv);

	if(strncmp("powertx", argv[1], 7) == 0)
		return mtkfm_command_poweruptx(argc, argv);

	if(strncmp("scan", argv[1], 4) == 0)
		return mtkfm_command_scan(argc, argv);

	print_usage();

	return EXIT_FAILURE;
}

