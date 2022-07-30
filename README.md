# nfs-drive-handler
No file system drive handler based on Windows API - Used for reading and writing to raw drives/USBs/SD cards
Must have MinGW or POSIX based compiler for windows:
https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download
 ``` 
     mkdir build
     cd build 
     cmake -G "MinGW Makefiles" .. OR cmake -G -DEXAMPLE=ON -G "MinGW Makefiles" ..
```
