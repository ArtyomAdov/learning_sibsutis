#include "resource.h"

LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI
WinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow)
{
    MSG msg;
    DialogBox(hInstance, (LPCTSTR)IDD_DLGTEST, NULL, (DLGPROC)DlgProc);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) { // simulary first programm
    case (WM_INITDIALOG): {
        return TRUE;
    }
    case (WM_COMMAND): {
        switch (LOWORD(wParam)) {
        case (IDOK):
            PostQuitMessage(0);
            return TRUE;
        case (IDC_BTNSEND): {
            char class_name[100];
            HWND hAnotherDlg;
            GetClassName(hDlg, class_name, 100);
            hAnotherDlg = FindWindow(class_name, "WindowOne");
            GetDlgItemText(hDlg, IDC_EDIT2, class_name, 100);
            COPYDATASTRUCT data;
            data.cbData = strlen(class_name);
            data.lpData = class_name;
            SendMessage(
                    hAnotherDlg,
                    WM_COPYDATA,
                    (WPARAM)GetFocus(),
                    (LPARAM)&data);
            return TRUE;
        }
        default: {
            return FALSE;
        }
        }
        break;
    }
    case (WM_COPYDATA): {
        SetDlgItemText(hDlg, IDC_EDIT1, ((COPYDATASTRUCT*)lParam)->lpData);
        return TRUE;
    }
    default: {
        return FALSE;
    }
    }
}