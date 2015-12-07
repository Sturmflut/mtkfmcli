#ifndef _MTKFM_LIB_H_
#define _MTKFM_LIB_H_

#include <stdint.h>

int mtkfm_lib_opendevice();
void mtkfm_lib_closedevice(int fd);

int mtkfm_lib_printhwinfo(int fd);

int mtkfm_lib_powerup(int fd, uint32_t freq);
int mtkfm_lib_poweruptx(int fd, uint32_t freq);

int mtkfm_lib_tune(int fd, uint32_t freq);

int mtkfm_lib_getrssi(int fd, uint32_t* rssi);

int mtkfm_lib_seek(int fd);

int mtkfm_lib_setvolume(int fd, uint32_t volume);
uint32_t mtkfm_lib_getvolume(int fd);

int mtkfm_lib_setvolume(int fd, uint32_t mute);

const char* mtkfm_lib_errstring(int errcode);

#endif
