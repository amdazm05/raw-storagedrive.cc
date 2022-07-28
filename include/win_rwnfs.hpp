#ifndef     ___WIN_RWNFS
#define     ___WIN_RWNFS

#include <fileapi.h>
#include <Windows.h>


class WinRWNFS
{
    private:
        static HANDLE file;
        static LPCWSTR filename;
    public:
        static void setPath         (LPCWSTR path);
        static void createFile      (LPCSTR path);
        static void writeByteToDrive(char data);
        static void writePageToDrive(char * data);
        static void readDatafromFile(void);
};

#endif     //___WIN_RWNFSs