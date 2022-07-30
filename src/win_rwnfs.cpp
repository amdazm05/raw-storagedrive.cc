#include <win_rwnfs.hpp>
#include <iostream>

HANDLE WinRWNFS::hDevice;
LARGE_INTEGER WinRWNFS::pos;
DWORD WinRWNFS::cnt, WinRWNFS::wcnt;
BOOL WinRWNFS::bResult;
char   WinRWNFS::dev_name[64];
DWORD  WinRWNFS::BytesReturned;
VOLUME_DISK_EXTENTS WinRWNFS::vde;

 int WinRWNFS::drive_open(char *drive_name) 
 {
     sprintf(dev_name, "\\\\.\\%s", drive_name);
     hDevice = CreateFileA(dev_name,                              // Drive to open
                          GENERIC_READ | GENERIC_WRITE,          // Access to the drive
                          FILE_SHARE_READ | FILE_SHARE_WRITE,    // Share mode
                          NULL,                                  // Security
                          OPEN_EXISTING,                         // Disposition
                          0,                                     // no file attributes
                          NULL);
    
     if (hDevice == INVALID_HANDLE_VALUE) {
         printf("Can't open the drive %s (err = %d).\n", drive_name, GetLastError());
         return(-1);
     }
    
     bResult = DeviceIoControl(hDevice, IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, 
                               NULL, 0, &vde, sizeof(vde), &BytesReturned, NULL);
     if (!bResult) {
         printf("Failed to get physical disk name (err = %d).\n", GetLastError());
         return(-1);
     }
        
     CloseHandle(hDevice);
     sprintf(dev_name, "\\\\.\\PhysicalDrive%d", vde.Extents[0].DiskNumber);
        
     hDevice = CreateFileA(dev_name,                              // Drive to open
                          GENERIC_READ | GENERIC_WRITE,          // Access to the drive
                          FILE_SHARE_READ | FILE_SHARE_WRITE,    // Share mode
                          NULL,                                  // Security
                          OPEN_EXISTING,                         // Disposition
                          0,                                     // no file attributes
                          NULL);
    
     if (hDevice == INVALID_HANDLE_VALUE) {
         printf("Can't open the disk %s (err = %d).\n", dev_name, GetLastError());
         return(-1);
     }
    
     bResult = DeviceIoControl(hDevice, FSCTL_LOCK_VOLUME, 
                               NULL, 0, NULL, 0, &BytesReturned, NULL);
     if (!bResult) {
         printf("Failed to lock volume (err = %d).\n", GetLastError());
         return(-1);
     }
    
     bResult = DeviceIoControl(hDevice, FSCTL_DISMOUNT_VOLUME, 
                               NULL, 0, NULL, 0, &BytesReturned, NULL);
     if (!bResult) {
         printf("Failed to dismount volume (err = %d).\n", GetLastError());
         return(-1);
     }
        
     return(0);
 }

int WinRWNFS::drive_write(unsigned int sec, unsigned int num_secs, char *buf)
{
  pos={};
  cnt=0, wcnt=0;
  bResult=false;

  pos.QuadPart = ((LONGLONG)sec) << 9; // assume 512-byte sector
  cnt = ((DWORD)num_secs) << 9;

  bResult = SetFilePointerEx(hDevice, pos, NULL, FILE_BEGIN);
  if (!bResult)
  {
    printf("SetFilePointerEx() failed (err = %d).\n", GetLastError());
    return (-1);
  }

  bResult = WriteFile(hDevice, buf, cnt, &wcnt, NULL);
  if (!bResult || cnt != wcnt)
  {
    printf("WriteFile() failed (err = %d).\n", GetLastError());
    return (-1);
  }

  return (0);
}

int WinRWNFS::drive_read(unsigned int sec, unsigned int num_secs, char *buf)
{
  pos={};
  cnt=0, wcnt=0;
  bResult=false;
  pos.QuadPart = ((LONGLONG)sec) << 9; // assume 512-byte sector
  cnt = ((DWORD)num_secs) << 9;

  bResult = SetFilePointerEx(hDevice, pos, NULL, FILE_BEGIN);
  if (!bResult)
  {
    printf("SetFilePointerEx() failed (err = %d).\n", GetLastError());
    return (-1);
  }

  bResult = ReadFile(hDevice, buf, cnt, &wcnt, NULL);
  if (!bResult || cnt != wcnt)
  {
    printf("ReadFile() failed (err = %d).\n", GetLastError());
    return (-1);
  }

  return (0);
}