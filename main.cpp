#include <iostream>
#include <win_rwnfs.hpp>

#include <tchar.h>

#define BUFSIZE MAX_PATH 

void something(void)
 {
  BOOL bFlag;
  TCHAR Buf[BUFSIZE];           // temporary buffer for volume name
  TCHAR Drive[] = TEXT("c:\\"); // template drive specifier
  TCHAR I;                      // generic loop counter

  // Walk through legal drive letters, skipping floppies.
  for (I = TEXT('A'); I < TEXT('Z');  I++ ) 
   {
    // Stamp the drive for the appropriate letter.
    Drive[0] = I;

    bFlag = GetVolumeNameForVolumeMountPoint(
                Drive,     // input volume mount point or directory
                Buf,       // output volume name buffer
                BUFSIZE ); // size of volume name buffer

    if (bFlag) 
     {
      _tprintf (TEXT("The ID of drive \"%s\" is \"%s\"\n"), Drive, Buf);
     }
   }
 }


int main()
{
    something();
    LPCSTR path="\\\\.\\D:";

    char a[512]="hello there diskuyuuu";
    WinRWNFS::createFile(path);
    // WinRWNFS::writePageToDrive(a);
    // printf("error 2 %",strerror(errno));
    // WinRWNFS::readDatafromFile();
    // printf("error 3 %",strerror(errno));
    system("pause");
    return 0;
}
