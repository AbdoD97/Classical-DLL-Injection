#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>


using namespace std;

int main()
{
    HANDLE hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    PROCESSENTRY32 pe32 ;
    DWORD PID;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hProcess;


    do
    {
        string process_name = pe32.szExeFile;
      //
         if ( process_name.compare("Notepad.exe") == 0)
         {
            PID = pe32.th32ProcessID;
            break;
            }

    }
    while(Process32Next( hProcessSnap, &pe32 ) );
    HANDLE inject_me = OpenProcess(PROCESS_ALL_ACCESS , TRUE , PID);
    const char * dll_Path = "C:\\me.dll";
    LPVOID  memoryaddy = VirtualAllocEx(inject_me,NULL ,sizeof(dll_Path),MEM_COMMIT | MEM_RESERVE ,PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(inject_me,memoryaddy,dll_Path,strlen(dll_Path),NULL);

            HMODULE hModule = GetModuleHandle("kernel32");
        //cout << hModule << endl;
    FARPROC lpStartAddress = GetProcAddress(hModule, ("LoadLibraryA"));
cout << lpStartAddress << endl;


    HANDLE hThread = CreateRemoteThread(inject_me, NULL, 0,(LPTHREAD_START_ROUTINE)lpStartAddress, memoryaddy, 0, NULL);
    //cout << hThread << endl;

    return 0;
}
