#pragma warning(disable: 4996)
#include <windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include "main.h"

int main()
{
	DWORD pid = NULL, time = NULL;
	PROCESSENTRY32 pe32 = { NULL };

	printf("Search the minesweeper processs...");
	pe32 = fnSearchMinesweeperProcess();
	if (pe32.th32ProcessID == NULL) {
		puts("FAILED");
		exit(-1);
	}
	puts("SUCCESS");

	printf("PID: %d\n", pe32.th32ProcessID);

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 1, pe32.th32ProcessID);

	printf(": %d\n", MineReadTimer(hProcess));
	puts("Enter the desired timer value");
	scanf("%d", &time);

	while (1) {
		Sleep(1000);
		system("cls");
		MineLocation(hProcess);
		
	MineWriteTimer(hProcess, time);
	}

	CloseHandle(hProcess);
}

int MineReadTimer(HANDLE hProcess)
{
	DWORD time;
	ReadProcessMemory(
		hProcess,
		(LPCVOID)TIMER_ADDRESS,
		&time,
		sizeof(DWORD),
		NULL);
	return time;
}

int MineWriteTimer(HANDLE hProcess, DWORD time)
{
	WriteProcessMemory(
		hProcess,
		(LPCVOID)TIMER_ADDRESS,
		&time,
		sizeof(DWORD),
		NULL);
}

PROCESSENTRY32 fnSearchMinesweeperProcess() {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS,
		NULL);
	PROCESSENTRY32 pe32 = { NULL };
	pe32.dwSize = sizeof(PROCESSENTRY32);
	char szExeFileCompare[MAX_PATH] = { NULL };

	for (UINT nProcessRow = 0; nProcessRow < 200; nProcessRow++) {
		Process32Next(hProcessSnap, &pe32);
		for (UINT nProcessColumn = 0; *(pe32.szExeFile + nProcessColumn) != NULL; nProcessColumn++) {
			*(szExeFileCompare + nProcessColumn) = *(pe32.szExeFile + nProcessColumn);
		}
	if (!strcmp(szExeFileCompare, "Winmine__XP.exe")) {
		CloseHandle(hProcessSnap);
		return pe32;
	}
		memset(&szExeFileCompare, NULL, strlen(szExeFileCompare));
	}

	CloseHandle(hProcessSnap);
	memset(&pe32, NULL, sizeof(PROCESSENTRY32));
	return pe32;
}

int MineLocation(HANDLE hProcess)
{
	unsigned char mapTemp[286] = { NULL };
	unsigned char map[MAP_HEIGHT][MAP_WIDTH] = { NULL };

	ReadProcessMemory(
		hProcess,
		(LPCVOID)MAP_START_ADDRESS,
		&mapTemp,
		286,
		NULL);

	UINT z = 0;
	for (UINT y = 0; y < MAP_HEIGHT; y++) {
		for (UINT x = 0; x < MAP_WIDTH; x++) {
			if (*(mapTemp + z) == ID_NEWLINE) {
				z += 1;
				while ((*(mapTemp + z) != ID_NEWLINE) && (z < MAP)) {
					z += 1;
				}
				z += 1;
				break;
			}
			*(*(map + y) + x) = *(mapTemp + z);
			z += 1;
		}
	}
	for (UINT y = 0; y < MAP_HEIGHT; y++) {
		for (UINT x = 0; *(*(map + y) + x) != NULL; x++) {
			switch (*(*(map + y) + x)) {
			case ID_MINE:
				printf("* ");
				break;
			case ID_MINE_FLAG:
				printf("v ");
				break;
			case ID_UNKNOWN:
				printf("? ");
				break;
			case ID_UNKNOWN_FLAG:
				printf("v ");
				break;
			case ID_BACKGROUND:
				printf("0 ");
				break;
			case (ID_BACKGROUND + 1):
				printf("1 ");
				break;
			case (ID_BACKGROUND + 2):
				printf("2 ");
				break;
			case (ID_BACKGROUND + 3):
				printf("3 ");
				break;
			case (ID_BACKGROUND + 4):
				printf("4 ");
				break;
			case (ID_BACKGROUND + 5):
				printf("5 ");
				break;
			case (ID_BACKGROUND + 6):
				printf("6 ");
				break;
			case (ID_BACKGROUND + 7):
				printf("7 ");
				break;
			case (ID_BACKGROUND + 8):
				printf("8 ");
				break;
			}
		}
		puts("");
	}
}