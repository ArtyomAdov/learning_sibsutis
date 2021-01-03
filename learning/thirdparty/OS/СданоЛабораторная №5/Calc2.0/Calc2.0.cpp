#include <windows.h>
#include <stdlib.h>
#include <string>
#include <math.h>

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND hEdit1, hEdit2, HEdit, hPlus, hMinus, hMult, hDiv, hStep, hLog, hSQRT1, hSQR1, hSQRT2, hSQR2, hsin1, hsin2, hcos1, hcos2;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;

	LPCSTR lpszAppName = "Win1";
	wc.lpszClassName = lpszAppName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = MyWndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);      
	wc.lpszMenuName = 0;  
	wc.hbrBackground = /*(HBRUSH)(COLOR_WINDOW + 1);*/CreateSolidBrush(RGB(20, 30, 40)); 
	wc.style = CS_HREDRAW | CS_VREDRAW;   
	
	if (!RegisterClass(&wc)) 
		return 0;
		
	hWnd = CreateWindow(lpszAppName, "Генератор цепочек", WS_OVERLAPPEDWINDOW | WS_BORDER, 0, 0, 480, 400, NULL, NULL, hInstance, NULL);
	
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);      
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	long double c, a, b;	
	char string[32], str1[13], str2[13];
	
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			HEdit = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_READONLY | ES_RIGHT, 5, 5, 100, 40, hWnd, (HMENU)1, NULL, NULL);
			HEdit1 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_READONLY | ES_RIGHT, 5, 75, 100, 40, hWnd, (HMENU)1, NULL, NULL);
			/*hEdit1 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 5, 70, 200, 40, hWnd, (HMENU)2, NULL, NULL);
			hEdit2 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 255, 70, 205, 40, hWnd, (HMENU)3, NULL, NULL);			
			
			hPlus = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 250, 100, 40, hWnd, (HMENU)4, NULL, NULL);
			hMinus = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | WS_BORDER, 185, 250, 100, 40, hWnd, (HMENU)5, NULL, NULL);
			hMult = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 300, 100, 40, hWnd, (HMENU)6, NULL, NULL);
			hDiv = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | WS_BORDER, 185, 300, 100, 40, hWnd, (HMENU)7, NULL, NULL);
			hStep = CreateWindow("BUTTON", "X^Y", WS_VISIBLE | WS_CHILD | WS_BORDER, 290, 250, 100, 40, hWnd, (HMENU)12, NULL, NULL);
			hLog = CreateWindow("BUTTON", "LogX(Y)", WS_VISIBLE | WS_CHILD | WS_BORDER, 290, 300, 100, 40, hWnd, (HMENU)17, NULL, NULL);
			
			hSQRT1 = CreateWindow("BUTTON", "SQRT", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 120, 100, 40, hWnd, (HMENU)8, NULL, NULL);
			hSQR1 = CreateWindow("BUTTON", "X^2", WS_VISIBLE | WS_CHILD | WS_BORDER, 105, 120, 100, 40, hWnd, (HMENU)9, NULL, NULL);
			hSQRT2 = CreateWindow("BUTTON", "SQRT", WS_VISIBLE | WS_CHILD | WS_BORDER, 255, 120, 100, 40, hWnd, (HMENU)10, NULL, NULL);
			hSQR2 = CreateWindow("BUTTON", "Y^2", WS_VISIBLE | WS_CHILD | WS_BORDER, 355, 120, 105, 40, hWnd, (HMENU)11, NULL, NULL);
			hsin1 = CreateWindow("BUTTON", "SIN(X)", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 165, 100, 40, hWnd, (HMENU)13, NULL, NULL);
			hcos1 = CreateWindow("BUTTON", "COS(X)", WS_VISIBLE | WS_CHILD | WS_BORDER, 105, 165, 100, 40, hWnd, (HMENU)14, NULL, NULL);
			hsin2 = CreateWindow("BUTTON", "SIN(Y)", WS_VISIBLE | WS_CHILD | WS_BORDER, 255, 165, 100, 40, hWnd, (HMENU)15, NULL, NULL);
			hcos2 = CreateWindow("BUTTON", "COS(Y)", WS_VISIBLE | WS_CHILD | WS_BORDER, 355, 165, 105, 40, hWnd, (HMENU)16, NULL, NULL);
			MessageBox(hWnd, "Добро пожаловать в Calc2.0!!!", "Приложение Calc2.0", MB_OK | MB_ICONEXCLAMATION);
*/
			break;	
		case WM_COMMAND:
			if (LOWORD(wParam) == 4)
			{	
				GetWindowText(hEdit1, str1, 13);
				GetWindowText(hEdit2, str2, 13);
	
				a = atof(str1);
				b = atof(str2);
	
				c = a + b;
				sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);				
			}
			else if (LOWORD(wParam) == 5)
			{
				GetWindowText(hEdit1, str1, 13);
				GetWindowText(hEdit2, str2, 13);
	
				a = atof(str1);
				b = atof(str2);
	
				c = a - b;
				sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 6)
			{
				GetWindowText(hEdit1, str1, 13);
				GetWindowText(hEdit2, str2, 13);
	
				a = atof(str1);
				b = atof(str2);
	
				c = a * b;
				sprintf(string, "%f", c);
			
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 7)
			{
				GetWindowText(hEdit1, str1, 13);
				GetWindowText(hEdit2, str2, 13);
	
				a = atof(str1);
				b = atof(str2);
	
				c = a / b;
				sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 12)
			{
				GetWindowText(hEdit1, str1, 13);
				GetWindowText(hEdit2, str2, 13);
	
				a = atof(str1);
				b = atof(str2);
	
				c = pow(a, b);
				sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 17)
			{
				GetWindowText(hEdit1, str1, 13);
				GetWindowText(hEdit2, str2, 13);
	
				a = atof(str1);
				b = atof(str2);
	
				c = log(b) / log(a);
				sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 8)
			{
				GetWindowText(hEdit1, str1, 13);
	
				a = atof(str1);

			    c = sqrt(a);
			    sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 9)
			{
				GetWindowText(hEdit1, str1, 13);
	
				b = atof(str1);
	
				c = b * b;
				sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 10)
			{
				GetWindowText(hEdit2, str2, 13);
	
				a = atof(str2);

			    c = sqrt(a);
			    sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 11)
			{
				GetWindowText(hEdit2, str2, 13);
	
				b = atof(str2);
	
				c = b * b;
				sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 13)
			{
				GetWindowText(hEdit1, str1, 13);
	
				a = atof(str1);

			    c = sin(a * 3.14159265 / 180);
			    sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 14)
			{
				GetWindowText(hEdit1, str1, 13);
	
				b = atof(str1);
	
				c = cos(b * 3.14159265 / 180);
				sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 15)
			{
				GetWindowText(hEdit2, str2, 13);
	
				a = atof(str2);

			    c = sin(a * 3.14159265 / 180);
			    sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			else if (LOWORD(wParam) == 16)
			{
				GetWindowText(hEdit2, str2, 13);
	
				b = atof(str2);
	
				c = (b * 3.14159265 / 180);
				sprintf(string, "%f", c);
				
				SetWindowText(HEdit, 0);
				SendMessage(HEdit, EM_REPLACESEL, TRUE, (LPARAM)string);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
