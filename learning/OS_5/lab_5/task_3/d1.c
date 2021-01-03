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
    switch (message) {
    case (WM_INITDIALOG): {
        return TRUE;
    }
    case (WM_COMMAND): {
        switch (LOWORD(wParam)) {
        case (IDOK):
            PostQuitMessage(0); // quit
            return TRUE;
        case (IDC_BTNSEND): {                    // Click button "Send"
            char class_name[100];                // buffer for save class name
            HWND hAnotherDlg;                    // pointer for comrad window
            GetClassName(hDlg, class_name, 100); // fill buffer
            hAnotherDlg
                    = FindWindow(class_name, "WindowTwo"); // find comrad window
            GetDlgItemText(
                    hDlg,
                    IDC_EDIT2,
                    class_name,
                    100);        // write text from buffer for  comrad
            COPYDATASTRUCT data; // create copydata
            data.cbData = strlen(class_name); // fill size for copydata
            data.lpData = class_name;         // fill text for copy data
            SendMessage(
                    hAnotherDlg,
                    WM_COPYDATA,
                    (WPARAM)GetFocus(),
                    (LPARAM)&data); // send messege for comrad
            return TRUE;
        }
        default: {
            return FALSE;
        }
        }
        break;
    }
    case (WM_COPYDATA): {
        SetDlgItemText(
                hDlg,
                IDC_EDIT1,
                ((COPYDATASTRUCT*)lParam)->lpData); // get messege from comrad
        return TRUE;
    }
    default: {
        return FALSE;
    }
    }
}