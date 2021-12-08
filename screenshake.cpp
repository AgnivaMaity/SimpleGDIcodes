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

DWORD WINAPI screenshaker(LPVOID)
{
	HDC desk = GetDC(0);
    int sh = GetSystemMetrics(0), sw = GetSystemMetrics(1);
    while (1)
    {
        SeedXorshift32(__rdtsc());
        int y = xorshift32() & sh;
        int number = xorshift32() % 9;
        SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
        switch (number)
        {
        case 1:
            BitBlt(desk, xorshift32() % 21 - 11, xorshift32() % 21 - 11, sh, sw, desk, 0, 0, SRCCOPY);
            break;
        case 2:
            RedrawWindow(0, 0, 0, 155);
            break;
        case 3:
            BitBlt(desk, 0, 0, sh, sw, desk, xorshift32() % 21 - 11, xorshift32() % 21 - 11, SRCCOPY);
            break;
        case 4:
            RedrawWindow(0, 0, 0, 155);
            break;
        case 5:
            BitBlt(desk, 10, y, sw, 96, desk, 0, y, SRCCOPY);
            break;
        case 6:
            RedrawWindow(0, 0, 0, 155);
            break;
        case 7:
            BitBlt(desk, -10, y, sw, -96, desk, 0, y, SRCCOPY);
            break;
        case 8:
            RedrawWindow(0, 0, 0, 155);
            break;
        }
    }
}

int main()
{
	HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)screenshaker, 0, 0, 0);
	Sleep(INFINITE);
}