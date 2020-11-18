#include <windows.h>
#include <stdio.h>
#include <VersionHelpers.h>

int main(
	int argc,
	char * argv[]
)
{
	OSVERSIONINFOEX info;
	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	GetVersionEx((LPOSVERSIONINFO)&info);

	printf("Windows version: %u.%u\n", info.dwMajorVersion, info.dwMinorVersion);
}