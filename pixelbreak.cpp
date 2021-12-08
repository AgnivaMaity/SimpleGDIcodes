#include <Windows.h>

DWORD xs;
VOID SeedXorshift32(DWORD dwSeed)
{
    xs = dwSeed;
}
DWORD xorshift32()
{
    xs ^= xs << 13;
    xs ^= xs << 17;
    xs ^= xs << 5;
    return xs;
}

DWORD WINAPI breakpixels(LPVOID)
{
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		SeedXorshift32(__rdtsc());
		int y = xorshift32() % sh;
		int number = xorshift32() % 5;
		switch (number)
		{
		case 1:
			RedrawWindow(0, 0, 0, 133);
			break;
		case 2:
			BitBlt(desk, 20, y, sw, 192, desk, 0, y, SRCCOPY);
			break;
		case 3:
			RedrawWindow(0, 0, 0, 133);
			break;
		case 4:
			BitBlt(desk, 20, y, sw, 192, desk, 0, y, SRCCOPY);
			break;
		}
	}
}

int main()
{
    HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)breakpixels, 0, 0, 0);
    Sleep(INFINITE);
}