#define _CRT_SECURE_NO_WARNINGS

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' "\
"version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <wingdi.h>
#include <stdio.h>
#include <objidl.h>
#include <io.h>
#include <shlobj.h>
#include <Winuser.h>
#include <Winreg.h>
#include <math.h>
#include <time.h> 
#include <string>
#include <string.h>
#include <wchar.h>
#include <iostream>
#include <shlwapi.h>
#include "resource.h"

enum Orientation { Portrait, Landscape };

enum PageSize { A4, B5, Letter, Legal, Executive,
                    A0, A1, A2, A3, A5, A6, A7, A8, A9, B0, B1,
                    B10, B2, B3, B4, B6, B7, B8, B9, C5E, Comm10E,
                    DLE, Folio, Ledger, Tabloid, Custom, NPageSize = Custom, NPaperSize = Custom };
typedef PageSize PaperSize;

typedef HDC		(_cdecl	*GetPdfDC)		();
typedef void	(_cdecl	*ReleasePdfDC)	(HDC hdc);
typedef void	(_cdecl *InitiateQtApp)	();
typedef void	(_cdecl	*SetPaperSizeAndOrientation) (PaperSize ps, Orientation or);
typedef bool	(_cdecl *InitiatePdf)	(wchar_t* path);
typedef int		(_cdecl *CreatePdf)		();
typedef	void	(_cdecl	*PrintPagePdf)	();
typedef bool	(_cdecl	*NewPdfPage)	();

BOOL APIENTRY DialogSetSN( HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);

HANDLE hFile;
DWORD max;

TCHAR szAppName[]	= TEXT("Анализ двигательной активности пациента");
TCHAR szAppTitle[]	= TEXT("Анализ ДАП");
TCHAR szClass[]		= TEXT("WindowAppClass");
LRESULT CALLBACK WndProc( HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain( HINSTANCE	hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WndProc(0, WM_INITDIALOG, 0, 0);

	MSG msg;
	HWND hWnd;

	hWnd = FindWindow( szAppName, NULL);
	if (hWnd)
	{
		if (IsIconic( hWnd))
			ShowWindow(hWnd, SW_RESTORE);
		SetForegroundWindow( hWnd);
		return FALSE;
	}
		
	hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)WndProc);
	
	if (hWnd == NULL)
	{
		MessageBox(NULL, TEXT("Сбой инициализации окна"), TEXT("статус"), NULL);
		return FALSE;
	}
	ShowWindow(hWnd, SW_SHOW);
	
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		SendMessage(GetDlgItem( hWnd, IDC_PROGRESS1), PBM_STEPIT, 0, 0);
	}

	return msg.wParam;  
}

const wchar_t pdfName[] = TEXT("x.pdf");

LRESULT CALLBACK WndProc( HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			HMODULE			hPdfDLL				= LoadLibrary(TEXT("saveAsPdf.dll"));
					
			InitiatePdf		InitiatePdfFunc		= (InitiatePdf)::GetProcAddress(hPdfDLL,	"InitiatePdf");
			CreatePdf		CreatePdfFunc		= (CreatePdf)::GetProcAddress(hPdfDLL,		"CreatePdf");
			GetPdfDC		GetPdfDCFunc		= (GetPdfDC)::GetProcAddress(hPdfDLL,		"GetPdfDC");
			ReleasePdfDC	ReleasePdfDCFunc	= (ReleasePdfDC)::GetProcAddress(hPdfDLL,	"ReleasePdfDC");
			SetPaperSizeAndOrientation	SetPaperSizeAndOrientationFunc = (SetPaperSizeAndOrientation)::GetProcAddress(hPdfDLL, "SetPaperSizeAndOrientation");//(QPrinter::PaperSize ps, QPrinter::Orientation or);
			InitiateQtApp	InitiateQtAppFunc	= (InitiateQtApp)::GetProcAddress(hPdfDLL,	"InitiateQtApp");
			PrintPagePdf	PrintPagePdfFunc	= (PrintPagePdf)::GetProcAddress(hPdfDLL,	"PrintPagePdf");
			NewPdfPage		NewPdfPageFunc		= (NewPdfPage)::GetProcAddress(hPdfDLL,		"NewPdfPage");
			
			InitiateQtAppFunc();
						

			if (InitiatePdfFunc((wchar_t*)pdfName))
			{
				SetPaperSizeAndOrientationFunc(Legal, Landscape);
				HDC hdc = GetPdfDCFunc();

				int Font1 = 400;
				RECT diRECT = {0, 0, 2000, Font1};
				SetBkColor(hdc, RGB(255, 255, 255));
				SetTextColor(hdc, RGB(0, 0, 0));

				HFONT hFont = CreateFont(Font1, 0, 0, 0, FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
				SelectObject(hdc, hFont);
				DrawText(hdc, TEXT("Page 1"), -1, &diRECT, DT_LEFT | DT_TOP);


				RECT diRECT2 = {0, 1000, 400, 2400};
				SetBkColor(hdc, RGB(0, 0, 255));
				SetTextColor(hdc, RGB(255, 255, 0));
				HFONT hFont2 = CreateFont(40, 0, 0, 0, FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
				SelectObject(hdc, hFont2);				
				DrawText(hdc, TEXT("Hier ist er"), -1, &diRECT2, DT_RIGHT | DT_BOTTOM);

				PrintPagePdfFunc();
				NewPdfPageFunc();

				//SetBkMode(hdc, TRANSPARENT);
				DrawText(hdc, TEXT("Page 2"), -1, &diRECT, DT_LEFT | DT_TOP);

				RECT diRECT3 = {0, 1200, 2000, 2400};
				HBRUSH br = CreateSolidBrush(RGB(255, 0, 0 ));
				FillRect(hdc, &diRECT3, br);

				PrintPagePdfFunc();

				CreatePdfFunc();
			}
			else
			{
				MessageBox(0, TEXT("Access denied"), pdfName, 0);
			}

			ExitProcess(0);

			SendMessage(GetDlgItem(hdlg,IDC_PROGRESS1), PBM_SETRANGE, 0, MAKELPARAM(0, 1000));
			SendMessage(GetDlgItem(hdlg,IDC_PROGRESS1), PBM_SETSTEP, 50, 0);
			return TRUE;
		}
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDCANCEL:
				{					
				}
			}
			break;
		}
	}
	return FALSE;
}