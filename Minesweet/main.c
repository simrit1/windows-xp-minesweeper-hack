#pragma warning(disable: 4996)
#include <windows.h>
#include <stdio.h>

#define MINE_TIMER_ADDRESS (0x0100579C)

int MineReadTimer(HANDLE hProcess);
int MineWriteTimer(HANDLE hProcess, DWORD time);

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

	CloseHandle(hProcess);
}

int MineReadTimer(HANDLE hProcess)
{
	DWORD time;
	ReadProcessMemory(
		hProcess,
		(LPCVOID)MINE_TIMER_ADDRESS,
		&time,
		sizeof(DWORD),
		NULL);
	return time;
}

int MineWriteTimer(HANDLE hProcess, DWORD time)
{
	WriteProcessMemory(
		hProcess,
		(LPCVOID)MINE_TIMER_ADDRESS,
		&time,
		sizeof(DWORD),
		NULL);
}
