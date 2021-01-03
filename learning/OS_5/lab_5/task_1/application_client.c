#include <stdio.h>
#include <string.h>
#include <windows.h>

int main()
{
    HWND hWnd;
    COPYDATASTRUCT data;
    char str[80];
    hWnd = FindWindow("CTemplate1", "CTemplate1");
    do {
        gets(str);
        data.cbData = strlen(str);
        data.lpData = str;
        SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetFocus(), (LPARAM)&data);
    } while (strcmp(str, "quit"));
    return 0;
}
