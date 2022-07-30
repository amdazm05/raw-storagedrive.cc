#ifndef     ___WIN_RWNFS
#define     ___WIN_RWNFS

#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <string>
#include <winioctl.h>
#include <Shlobj.h>
class WinRWNFS
{
    private:
        static HANDLE hDevice;
        static LARGE_INTEGER pos;
        static DWORD cnt, wcnt;
        static BOOL bResult;
        static char   dev_name[64];
        static DWORD  BytesReturned;
        static VOLUME_DISK_EXTENTS vde;
    public:
        static int drive_open(char *drive_name);    
        static int drive_write(unsigned int sec, unsigned int num_secs, char *buf);
        static int drive_read(unsigned int sec, unsigned int num_secs, char *buf);
};

#endif     //___WIN_RWNFSs