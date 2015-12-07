#ifndef _MTK_IOCTL_H_
#define _MTK_IOCTL_H_

typedef signed int fm_s32;
typedef unsigned char fm_u8;
typedef unsigned short fm_u16;

struct fm_tune_parm {
    fm_u8 err;
    fm_u8 band;
    fm_u8 space;
    fm_u8 hilo;
    fm_u16 freq; // IN/OUT parameter
};


struct fm_hw_info {
    fm_s32 chip_id; //chip ID, eg. 6620
    fm_s32 eco_ver; //chip ECO version, eg. E3
    fm_s32 rom_ver; //FM DSP rom code version, eg. V2
    fm_s32 patch_ver; //FM DSP patch version, eg. 1.11
    fm_s32 reserve;
};



struct fm_seek_parm {
    fm_u8 err;
    fm_u8 band;
    fm_u8 space;
    fm_u8 hilo;
    fm_u8 seekdir;
    fm_u8 seekth;
    fm_u16 freq; // IN/OUT parameter
};

struct fm_scan_parm {
    fm_u8  err;
    fm_u8  band;
    fm_u8  space;
    fm_u8  hilo;
    fm_u16 freq; // OUT parameter
    fm_u16 ScanTBL[16]; //need no less than the chip
    fm_u16 ScanTBLSize; //IN/OUT parameter
};


#define FM_IOC_MAGIC        0xf5

#define FM_IOCTL_POWERUP	_IOWR(FM_IOC_MAGIC, 0, struct fm_tune_parm*)
#define FM_IOCTL_POWERDOWN	_IOWR(FM_IOC_MAGIC, 1, int32_t*)

#define FM_IOCTL_TUNE          _IOWR(FM_IOC_MAGIC, 2, struct fm_tune_parm*)

#define FM_IOCTL_SEEK          _IOWR(FM_IOC_MAGIC, 3, struct fm_seek_parm*)

#define FM_IOCTL_SETVOL        _IOWR(FM_IOC_MAGIC, 4, uint32_t*)
#define FM_IOCTL_GETVOL        _IOWR(FM_IOC_MAGIC, 5, uint32_t*)

#define FM_IOCTL_MUTE          _IOWR(FM_IOC_MAGIC, 6, uint32_t*)

#define FM_IOCTL_GETRSSI       _IOWR(FM_IOC_MAGIC, 7, int32_t*)

#define FM_IOCTL_SCAN          _IOWR(FM_IOC_MAGIC, 8, struct fm_scan_parm*)

#define FM_IOCTL_POWERUP_TX    _IOWR(FM_IOC_MAGIC, 20, struct fm_tune_parm*)

#define	FM_IOCTL_GET_HW_INFO	_IOWR(FM_IOC_MAGIC, 40, struct fm_hw_info*)

#define FM_SUCCESS      0
#define FM_FAILED       1
#define FM_EPARM        2
#define FM_BADSTATUS    3
#define FM_TUNE_FAILED  4
#define FM_SEEK_FAILED  5
#define FM_BUSY         6
#define FM_SCAN_FAILED  7

#endif
