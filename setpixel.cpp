#include <Windows.h>

DWORD WINAPI SetPixelEffect(LPVOID lpParam)
{
    HDC desk = GetDC(0);
    int x = GetSystemMetrics(0), y = GetSystemMetrics(1);
    while (1)
    {
        SetPixel(desk, rand() % x, rand() % y, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % x, rand() % y, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetPixel(desk, rand() % x, rand() % y, RGB(rand() % 255, rand() % 255, rand() % 255));
        ReleaseDC(GetDesktopWindow(), desk); // fkush the DC.
        DeleteObject(&x); DeleteObject(&y); // prevent memory leaks.
    }
    DeleteDC(desk); //bruh
}

int main()
{
  HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetPixelEffect, 0, 0, 0);
  Sleep(INFINITE);
}
