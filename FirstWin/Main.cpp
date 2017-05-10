#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwind, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

	// register the window class
	const wchar_t CLASS_NAME[] = L"My First Window Class";
	WNDCLASS wc = {};

	// window class members
	wc.lpfnWndProc = WindowProc;		// pointer to window process
	wc.hInstance = hInstance;			// handle for hInstance from wWinMain
	wc.lpszClassName = CLASS_NAME;		// String for CLASS_NAME (see 6 lines above)

	RegisterClass(&wc);					// register address @system

										// create the window
	HWND hwnd = CreateWindowEx(			// returns handle for new window (or NULL if failure)
		0,								// optional window styles
		CLASS_NAME,						// window class
		L"Learn to program Windows",	// window text
		WS_OVERLAPPEDWINDOW,			// window style (overlapped is commonly used)

										// pos x,y & size x,y
		100, 50, 500, 800,

		NULL,							// parent window (NULL == highest stage, no parent)
		NULL,							// menu (NULL == no menu)
		hInstance,						// instance handle
		NULL							// additional application data (NULL == random void ptr)
	);

	if (hwnd == NULL)
		return 0;

	ShowWindow(hwnd, nCmdShow);			// makes the new window (hwnd handle) visible
										// nCmdShow -> minimize/maximize

										// run message loop
	MSG msg = {};
	// get message from queue and store it in &msg
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);			// call this BEFORE DispatchMessage
		DispatchMessage(&msg);			// tell system to call target windows' windows-procedure
	}

	return 0;

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {

	case WM_CLOSE:						// OPTIONAL
		if (MessageBox(hwnd, L"Echt jetzt?", L"My First Window Class", MB_OKCANCEL) == IDOK)
			DestroyWindow(hwnd);

		//else user canceled, do not close
		return 0;						// important, to indicate we processed WM_CLOSE

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}