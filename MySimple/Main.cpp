#include "Game.h"
//#include "Dx.h"

ComPtr<ID3D11Device>			device = nullptr;
ComPtr<ID3D11DeviceContext>		context = nullptr;
ComPtr<ID3D11DeviceContext>		dContext = nullptr;
ComPtr<ID3D11Buffer>			cbPerMesh = nullptr;
Timer timer;
Controller input;
Data* dat ;
Camera* camera;


HWND hWnd = nullptr;
HINSTANCE hInst = nullptr;




LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	static TCHAR szWindowClass[] = _T("MKii");

	int screenW = 1600;
	int screenH = 900;

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;//(HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	RegisterClassEx(&wcex);


	hInst = hInstance;
	hWnd = CreateWindow(szWindowClass, szWindowClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, screenW, screenH, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



	Game game;
	//Dx dx(hWnd);
	//dx.Initialize();


	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			game.Update();
			game.Draw();
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

	case WM_MOUSEMOVE: {



		long mx = LOWORD(lParam);
		long my = HIWORD(lParam);


		RECT re;
		GetWindowRect(hWnd, &re);

		input.m_md.m_screenX = (mx / ((re.right - re.left)*0.5f) - 1.0f) / ((re.right - re.left) / (re.bottom - re.top));
		input.m_md.m_screenY = 1.0f - my / ((re.bottom - re.top) * 0.5f);


	}


		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	
	return 0;
}