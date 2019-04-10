#pragma warning(disable: 4996)
#include <windows.h>
#include <stdio.h>
#include "main.h"

int main()
{
	DWORD pid = NULL, time = 0;

	puts("enter the minesweeper PID");
	scanf("%d", &pid);

	HANDLE hProcess = OpenProcess(
		PROCESS_ALL_ACCESS,
		1,
		pid);

	if (hProcess == NULL) {
		puts("not valid PID");
		exit(-1);
	}

	printf("Total Time: %d\n", MineReadTimer(hProcess));
	scanf("%d", &time);
	MineWriteTimer(hProcess, time);

	while (1) {
		Sleep(1000);
		system("cls");
		MineLocation(hProcess);
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