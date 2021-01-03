#include <windows.h>
#include <stdlib.h>
#include <string>
#include <math.h>

#define IDD_DLGTEST 101
#define IDC_EDIT1 1000
#define IDC_EDIT2 1001
#define IDC_EDIT3 1003
#define Plus 1002
#define Minus 1004
#define Umn 1005
#define Del 1006
#define Exit 1007

long double c, a, b;	
char string[32], str1[13], str2[13];
LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    DialogBox(hInstance,(LPCTSTR)IDD_DLGTEST, NULL, (DLGPROC)DlgProc);
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    char strText[100];
    switch (message)
    {
        case WM_INITDIALOG:
	    	return TRUE;
		case WM_COMMAND:
	    	switch (LOWORD(wParam))
	    	{
	    		case 1007:
					PostQuitMessage(0);
		    		return TRUE;
		    		
				case 1002:
					GetDlgItemText(hDlg, IDC_EDIT1, str1, 100);
					GetDlgItemText(hDlg, IDC_EDIT2, str2, 100);
					a = atof(str1);
					b = atof(str2);
					c = a + b;
					sprintf(string, "%f", c);
					SetDlgItemText(hDlg, IDC_EDIT3, string);
		    		return TRUE;
		    	
				case 1004:
					GetDlgItemText(hDlg, IDC_EDIT1, str1, 100);
					GetDlgItemText(hDlg, IDC_EDIT2, str2, 100);
					a = atof(str1);
					b = atof(str2);
					c = a - b;
					sprintf(string, "%f", c);
					SetDlgItemText(hDlg, IDC_EDIT3, string);
					return TRUE;
				
				case 1005:
					GetDlgItemText(hDlg, IDC_EDIT1, str1, 100);
					GetDlgItemText(hDlg, IDC_EDIT2, str2, 100);
					a = atof(str1);
					b = atof(str2);
					c = a * b;
					sprintf(string, "%f", c);
					SetDlgItemText(hDlg, IDC_EDIT3, string);
					return TRUE;
				
				case 1006:
					GetDlgItemText(hDlg, IDC_EDIT1, str1, 100);
					GetDlgItemText(hDlg, IDC_EDIT2, str2, 100);
					a = atof(str1);
					b = atof(str2);
					c = a / b;
					sprintf(string, "%f", c);
					SetDlgItemText(hDlg, IDC_EDIT3, string);
					return TRUE;
		    	break;
	        }
        	break;
	    default:
	    	return FALSE;
	}
}
