#ifndef _MTKFM_CLI_H_
#define _MTKFM_CLI_H_

// Hardware commands
int mtkfm_command_hwinfo(int argc, char** argv);

// Control commands
int mtkfm_command_poweron(int argc, char** argv);
int mtkfm_command_powerontx(int argc, char** argv);
int mtkfm_command_scan(int argc, char** argv);

#endif
