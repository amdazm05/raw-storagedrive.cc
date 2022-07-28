#include <win_rwnfs.hpp>
#include <iostream>

HANDLE WinRWNFS::file;
LPCWSTR WinRWNFS::filename=NULL;

void WinRWNFS::setPath(LPCWSTR path)
{   
    WinRWNFS::filename = path; 
    return;
}

void WinRWNFS::createFile(LPCSTR path)
{
    file=CreateFile(
        "\\\\.\\D:",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, 
        NULL, 
        OPEN_EXISTING, 
        FILE_FLAG_NO_BUFFERING | FILE_FLAG_RANDOM_ACCESS, 
        NULL);

    if(file == INVALID_HANDLE_VALUE)
    {
        std::cout<<"error";
    }
    char buffer[512] = { 0 };
    DWORD bytesWritten;
    int cond= WriteFile(file, buffer, 512, &bytesWritten, NULL); 
    std::cout<<cond<<"ending this"<<std::endl;
    if(cond!= TRUE)
    {
        DWORD lastError = GetLastError();
        std::cout<<"Error"<<lastError<<std::endl;
        CloseHandle(file);
        return;
    }
} 


void WinRWNFS::writeByteToDrive(char data)
{   
    DWORD bytesWritten;
    std::cout<<"Write"<<WriteFile(WinRWNFS::file, (LPCVOID)data, sizeof(char), &bytesWritten, NULL);
    return;
}
void WinRWNFS::writePageToDrive(char * data)
{
    DWORD bytesWritten;
    std::cout<<"Write"<<WriteFile(WinRWNFS::file, (LPCVOID)data, sizeof(char), &bytesWritten, NULL);
    return;
}

void  WinRWNFS::readDatafromFile(void)
{
    if (file != INVALID_HANDLE_VALUE)
    {
        char buffer[512];
        DWORD readBytes = 0;
        bool errro=ReadFile(file, buffer, sizeof(buffer), &readBytes, NULL);
        /* .. */
        CloseHandle(file);
        std::cout<<"buffer empty"<<errro<<buffer<<std::endl;
    }

    return;
}