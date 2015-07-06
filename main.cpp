#pragma once
#include "arkanoid_includes.h"

extern WNDCLASS wc;
extern HWND hWnd;
extern MSG msg;
extern Platform CurrentPlatform;
extern HDC hdc;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
TCHAR WinName[] = _T("MainFrame") ;
int APIENTRY _tWinMain(HINSTANCE This, // ���������� �������� ����������
	HINSTANCE Prev,                   // � ����������� �������� ������ 0
	LPTSTR cmd,                       // ��������� ������
	int mode)                         // ����� ����������� ����
{
	Level lnew;
	lnew.setNullLevel();
	CurrentGame.Levels.push_back(lnew);
		
	// ����������� ������ ����
	wc.hInstance = This;
	wc.lpszClassName = WinName;                // ��� ������ ����
	wc.lpfnWndProc = WndProc;                  // ������� ����
	wc.style = CS_HREDRAW | CS_VREDRAW;       // ����� ����
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);    // ����������� ������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ����������� ������
	wc.lpszMenuName = NULL;       // ��� ����
	wc.cbClsExtra = 0;            // ��� �������������� ������ ������
	wc.cbWndExtra = 0;            // ��� �������������� ������ ����
	// ���������� ���� ����� ������
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	if (!RegisterClass(&wc)) return 0;   // ����������� ������ ����
// �������� ����
	hWnd = CreateWindow(WinName, // ��� ������ ����
    _T("������ Windows-����������"),  // ��������� ����
	WS_OVERLAPPEDWINDOW,         // ����� ����
	CW_USEDEFAULT, // x
	CW_USEDEFAULT, // y   ������� ����
	CW_USEDEFAULT, // width
	CW_USEDEFAULT, // Height
	HWND_DESKTOP, // ���������� ������������� ����
	NULL,         // ��� ����
	This,         // ���������� ����������
	NULL);        // �������������� ���������� ���
	ShowWindow(hWnd, mode); // �������� ����
// ���� ��������� ���������
	while(GetMessage(&msg, NULL, 0, 0))
	{
	TranslateMessage(&msg); // ������� ���������� ����� ������� �������
	DispatchMessage(&msg);  // �������� ��������� ������� WndProc()
	}
	return 0;
}
// ������� ������� ���������� ������������ ��������
// � �������� ��������� �� ������� ��� ������� ����������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	          WPARAM wParam, LPARAM lParam)
{       // ���������� ���������
	PAINTSTRUCT ps;
	static int sx, sy;
	switch(message)
	{
		case WM_CREATE:
			SetTimer(hWnd, 1, CurrentGame.FPS, NULL);
		break;
		case WM_SIZE:
			sx = LOWORD(lParam);
			sy = HIWORD(lParam);
		break;
		case WM_TIMER:
			CurrentGame.Play();
		break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			CurrentGame.render(sx, sy);
			EndPaint(hWnd, &ps);
		break;
		case WM_KEYDOWN:
			if(VK_UP & wParam){
				if(CurrentPlatform.moveControl(1))
				{
					CurrentPlatform.step(1);
				}
			}
			if(VK_RIGHT & wParam){
				if(CurrentPlatform.moveControl(2))
				{
					CurrentPlatform.step(2);
				}
			}
			if(VK_DOWN & wParam){
				if(CurrentPlatform.moveControl(3))
				{
					CurrentPlatform.step(3);
				}
			}
			if(VK_LEFT & wParam){
				if(CurrentPlatform.moveControl(4))
				{
					CurrentPlatform.step(4);
				}
			}
			if(VK_SPACE & wParam){
				CurrentGame.End();
			}
		break;
		case WM_DESTROY : PostQuitMessage(0);
			          break; // ���������� ���������
		// ��������� ��������� �� ���������
		default : return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
