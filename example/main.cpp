#include <win_rwnfs.hpp>
#include <iostream>

int main(void)
{  
  char buff[512]="Hello Sector This Ahmed Azeem";
  char readbuf[512];
  WinRWNFS::drive_open("D:");
  WinRWNFS::drive_write(1,1,buff);
  WinRWNFS::drive_read(1,1,readbuf);
  std::cout<<"Got read data:" <<readbuf<<std::endl;
  system("pause");
  return 0;
}
