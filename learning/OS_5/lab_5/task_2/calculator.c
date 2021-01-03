#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ERROR_READ_IN_BUFFER_FROM_WINDOW 0b00000001
#define ERROR_ALLOCATION_MEMORY 0b00000010
#define INCORRECT_EXIT_PROGRAMM 0b00000011

#define MAX_SIZE_BUFFER_READ 10

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HWND text_field, button;

TCHAR szClassName[] = "WindowsAppCalculator";

int WINAPI
WinMain(HINSTANCE hThisInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpszArgument,
        int nCmdShow)
{ // create window based on template
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    wincl.lpszClassName = szClassName;
    wincl.hInstance = hThisInstance;
    wincl.lpfnWndProc = WindowProcedure; // call window procedure
    wincl.style = CS_HREDRAW | CS_VREDRAW;
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.hIcon = 0;
    wincl.lpszMenuName = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    if (!RegisterClassEx(&wincl)) {
        return 0;
    }
    hwnd = CreateWindowEx(
            0,
            szClassName,
            "Calculator",
            WS_MINIMIZEBOX | WS_SYSMENU,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            500,
            500,
            HWND_DESKTOP,
            NULL,
            hThisInstance,
            NULL);
    ShowWindow(hwnd, nCmdShow);
    while (GetMessage(&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}

int Convert_Char_To_Int(char* data_char)
{
    int data_int = 0;
    int sign = 0;            // start sign equally one(plus)
    if (data_char[0] == '-') // if first symbol int strig it is minus
    {
        sign = -1;        // sign equally minus one (minus)
        data_char[0] = 0; // first data char equally zero (because first zero
        				  // dont change result)
        data_int = data_int * sign; // convert numeric less zero by numeric large zero
    }
    for (short int i = (0 - sign);
         ((data_char[i] >= 0x30) && (data_char[i] <= 0x39)
          && (i < MAX_SIZE_BUFFER_READ) && (data_char[i] != '\0'));
         i++) {
        data_int = data_int + (data_char[i] & 0x0F); // convert digit to char
        data_int = data_int
                * 10; // digit shift in right for next category of number
    }
    data_int = data_int / 10;   // delete last zero (one zero in cycle excess)
	if(sign == -1) // consider the sign
	{
		data_int = data_int * sign;
	}
    return data_int;
}

char* Convert_Int_To_Char(int data_int)
{
    char* data_char = NULL;
    char* buffer = NULL;
    short int sign = 0;
    data_char = (char*)calloc(MAX_SIZE_BUFFER_READ, sizeof(char));
    buffer = (char*)calloc(MAX_SIZE_BUFFER_READ, sizeof(char));
    if (data_char == NULL) {
        return NULL;
    }
    if (data_int < 0) {
        data_char[0] = '-';
        sign = -1;
        data_int = data_int * sign;
    }
    for (short int i = 0; (i < MAX_SIZE_BUFFER_READ); i++) {
        buffer[i]
                = ((data_int % 10)
                   | 0x30);       // convert last category of number to char
        data_int = data_int / 10; // delete last category of number from numeric
        if (0 >= data_int)        // if numeric end
        {
            data_char[i] = '\0'; // last symbol equally end of string
            for (short int j = (0 - sign), k = i; k >= 0; j++, k--) {
                data_char[j] = buffer[k]; // fill result string inverse buffer
                                          // string (because first convert last
                                          // category of number)
            }
            break;
        }
    }
    return data_char;
}

LRESULT CALLBACK
WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInst;
    static PAINTSTRUCT ps;
    static HWND hBtnAdditional, hBtnDifference, hBtnMultiple, hBtnDivision;
    static HWND hEdt1, hEdt2;
    static HWND hAnswer;
    switch (message) {
    case (WM_CREATE): {
        text_field = CreateWindow(
                "static",
                "Write Need Numeric:",
                WS_VISIBLE | WS_CHILD,
                20,
                20,
                210,
                20,
                hwnd,
                NULL,
                NULL,
                NULL);
        hEdt1 = CreateWindow(
                "edit",
                "0",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                20,
                50,
                100,
                20,
                hwnd,
                0,
                hInst,
                NULL);
        hEdt2 = CreateWindow(
                "edit",
                "0",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                130,
                50,
                100,
                20,
                hwnd,
                0,
                hInst,
                NULL);
        hBtnAdditional = CreateWindow(
                "button",
                "+",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                20,
                80,
                40,
                40,
                hwnd,
                0,
                hInst,
                NULL);
        hBtnDifference = CreateWindow(
                "button",
                "-",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                60,
                80,
                40,
                40,
                hwnd,
                0,
                hInst,
                NULL);
        hBtnMultiple = CreateWindow(
                "button",
                "*",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                100,
                80,
                40,
                40,
                hwnd,
                0,
                hInst,
                NULL);
        hBtnDivision = CreateWindow(
                "button",
                "/",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                140,
                80,
                40,
                40,
                hwnd,
                0,
                hInst,
                NULL);
        hAnswer = CreateWindow(
                "static",
                "0",
                WS_CHILD | WS_VISIBLE,
                250,
                50,
                120,
                20,
                hwnd,
                0,
                hInst,
                NULL);
        break;
    }
    case (WM_COMMAND): {
        char* input_data = NULL;
        int first_argument = 0;
        int second_argument = 0;
        int result = 0;
        input_data = (char*)calloc(MAX_SIZE_BUFFER_READ, sizeof(char));
        if (input_data == NULL) {
            return ERROR_ALLOCATION_MEMORY;
        }
        if (!(GetWindowText(
                    hEdt1,
                    input_data,
                    MAX_SIZE_BUFFER_READ))) // get string from window and write
                                            // in char array
        {
            return ERROR_READ_IN_BUFFER_FROM_WINDOW;
        }
        first_argument = Convert_Char_To_Int(
                input_data); // call convert string to integer
        if (!(GetWindowText(
                    hEdt2,
                    input_data,
                    MAX_SIZE_BUFFER_READ))) // get string from window and write
                                            // in char array
        {
            return ERROR_READ_IN_BUFFER_FROM_WINDOW;
        }
        second_argument = Convert_Char_To_Int(
                input_data); // call convert string to integer
        if (lParam == (LPARAM)hBtnAdditional) {
            result = first_argument + second_argument;
            SetWindowText(
                    hAnswer,
                    Convert_Int_To_Char(result)); // write in window result for
                                                  // convert integer to string
        }
        if (lParam == (LPARAM)hBtnDifference) {
            result = first_argument - second_argument;
            SetWindowText(
                    hAnswer,
                    Convert_Int_To_Char(result)); // write in window result for
                                                  // convert integer to string
        }
        if (lParam == (LPARAM)hBtnMultiple) {
            result = first_argument * second_argument;
            SetWindowText(
                    hAnswer,
                    Convert_Int_To_Char(result)); // write in window result for
                                                  // convert integer to string
        }
        if (lParam == (LPARAM)hBtnDivision) {
            if (second_argument == 0) // if division on zero
            {
                result = 0; // result equally zero
            } else {
                result = first_argument
                        / second_argument; // standart procedure division
            }
            SetWindowText(
                    hAnswer,
                    Convert_Int_To_Char(result)); // write in window result for
                                                  // convert integer to string
        }
        break;
    }
    case (WM_DESTROY): {
        PostQuitMessage(0);
        break;
    }
    default: {
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    }
    return 0;
}
