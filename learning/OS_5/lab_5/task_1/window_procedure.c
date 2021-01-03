#include <windows.h>

LRESULT CALLBACK
MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;
    switch (message) {
    case (WM_DESTROY): { //сообщение генерируется при уничтожении окна
        PostQuitMessage(0); //указывает системе штатно выполнить
        //выход из программы
        break;
    }
    case WM_HOTKEY: {
        ShowWindow(hWnd, SW_SHOWNORMAL);
        break;
    } // Процедура окна.
    case WM_PAINT: {
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rt);
        DrawText(hdc, "From Paint", strlen("From Paint"), &rt, DT_CENTER);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_COPYDATA: {
        GetClientRect(hWnd, &rt);
        hdc = GetDC(hWnd);
        DrawText(
                hdc,
                (char*)(((COPYDATASTRUCT*)lParam)->lpData),
                ((COPYDATASTRUCT*)lParam)->cbData,
                &rt,
                DT_LEFT);
        ReleaseDC(hWnd, hdc);
        break;
    }
    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);
        //Обеспечивается обработка сообщений по умолчанию
    }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
