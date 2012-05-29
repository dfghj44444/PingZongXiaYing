/************************************************************************/
/*  main.cpp : ����Ӧ�ó������ڵ㡣                                                                    */
/************************************************************************/


#include "stdafx.h"



#define MAX_LOADSTRING 100
// ������Ļ�ߴ�
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

//#define FULL_SCREEN

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

LPDIRECT3D9			 g_pD3d		  = NULL;    // Direct3D�ӿ�ָ��
LPDIRECT3DDEVICE9	 g_pD3ddev	  = NULL;    //D3d�豸ָ��
LPDIRECTINPUT8 g_lpdi       = NULL;	//D3d ����ӿ�ָ��
LPDIRECTINPUTDEVICE8 g_pKeyboard  = NULL;	//D3d���� �����豸
LPDIRECTINPUTDEVICE8 g_pMouse  = NULL;	//D3d��� �����豸
DWORD MouseX, MouseY;					//�������
DWORD MouseButton[4];					//��ť״̬
ID3DXSprite* g_pSprite=NULL;

CTitle g_Title;//������

CRole g_MainRole("img\\guwen.png");//������

int	   g_WindowMode=1;		//0=ȫ�� other=����
BOOL   g_bActive = FALSE;	//�Ƿ񴰿ڼ���
RECT   g_rcWindow;

double g_dElpasedTime;//��ȥʱ��
double g_dCurTime;//��ǰʱ��
double g_dLastTime;//�ϴ�ʱ��
double g_dAnimationTimer  = 0.0;
double g_dControllerTimer = 0.0;
GAMESTATE g_gamestate=K_TITLE;//ȫ��״̬��

using namespace std;

//���������б�
typedef list<CSprite> SPRITELIST;

SPRITELIST g_SpriteList;
SPRITELIST::iterator g_sprite_i;
SPRITELIST::iterator g_sprite_j;
SPRITELIST::iterator g_sprite_k;

//ȫ�־��������
LPDIRECT3DTEXTURE9 g_pTextureMap,g_pTextTitle,g_pTextButton;
LPD3DXSPRITE       g_pD3DXSprite;


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PINGZONGXIAYING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	//������Ϸ���������ļ�-(��ȡ����ģʽ)
	Wxm_IniFile Ini("ini\\setup.ini");
	g_WindowMode=Ini.ReadValueInt("Setup", "WindowMode");

	//��ȡϵͳ��ǰ�ֱ���
	int nowWidth=GetSystemMetrics(SM_CXSCREEN); 
	int nowHeight=GetSystemMetrics(SM_CYSCREEN);

	if( g_WindowMode != 0 && g_WindowMode != 1 )
	{
		if( IDYES==MessageBox(NULL, "ʹ�ô�����ʾģʽ��\n[Alt+Enter] �л�ȫ���򴰿���ʾ."
			, "ע��", MB_YESNO))
			g_WindowMode=1;
		else
			g_WindowMode=0;
	}

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	//��ʼ��DX
	if( FAILED( GameStart() ) )
	{
		return FALSE;
	}
	

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PINGZONGXIAYING));

	//static float lastTime = (float)timeGetTime(); 
	// ����Ϣѭ��:
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
		//else
		//{	

		//	float currTime  = (float)timeGetTime();
		//	float timeDelta = (currTime - lastTime)*0.001f;

		//	Display(timeDelta);

		//	lastTime = currTime;
		//	}
		//}
	while( TRUE )
	{
		// Look for messages, if none are found then 
		// update the state and display it
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if( 0 == GetMessage(&msg, NULL, 0, 0 ) )
			{
				// WM_QUIT was posted, so exit
				return (int)msg.wParam;
			}

			// Translate and dispatch the message
			if( 0 == TranslateAccelerator( msg.hwnd, hAccelTable, &msg ) )
			{
				TranslateMessage( &msg ); 
				DispatchMessage( &msg );
			}
		}
		else
		{
			if( g_bActive )
			{
				g_dCurTime     = timeGetTime();
				g_dElpasedTime += ((g_dCurTime - g_dLastTime) * 0.001);
				g_dLastTime    = g_dCurTime;
				Render_frame();//��Ⱦ֡
			}
			else
			{
				// Go to sleep if we have nothing else to do
				WaitMessage();

				// Ignore time spent inactive 
				//g_dwLastTick = timeGetTime();
			}
		}

		//CDx
	}
	GameOver();
	//// ���DirectX �� COM
	//CleanD3D();
	//CleanDirectInput();
	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PINGZONGXIAYING));
	wcex.hCursor		= LoadCursor(hInstance, LPCTSTR(IDC_CURSOR1));
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   if(g_WindowMode)
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 300, 300, 800, 600, NULL, NULL, hInstance, NULL);
   else
	hWnd = CreateWindow(szWindowClass,szTitle, WS_EX_TOPMOST | WS_POPUP,
	   0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL,  hInstance,  NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);

   //GameStart(hWnd);
   
   GetWindowRect(hWnd,&g_rcWindow);//Ϊ�ֱ��ʸı��ԭ�ֱ���

   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case WM_SIZE:
			// ����Ƿ񴰿���С��
			if (SIZE_MAXHIDE==wParam || SIZE_MINIMIZED==wParam)
				g_bActive = FALSE;
			else   g_bActive = TRUE;
			break;
		case WM_CHAR:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			break;
		case WM_KEYDOWN:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}









// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

/**
	ˢ����Ļ�ĺ���
	@param timeDelta ��ȥ��ʱ��
*/
bool Display(float timeDelta)
{
	if( g_pD3ddev ) // Only use Device methods if we have a valid device.
	{
		// Instruct the device to set each pixel on the back buffer black -
		// D3DCLEAR_TARGET: 0x00000000 (black) - and to set each pixel on
		// the depth buffer to a value of 1.0 - D3DCLEAR_ZBUFFER: 1.0f.
		g_pD3ddev->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

		// Swap the back and front buffers.
		g_pD3ddev->Present(0, 0, 0, 0);
	}
	return true;
}
//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: ��ʼ��D3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	g_pD3d = Direct3DCreate9(D3D_SDK_VERSION);    // ����Direct3�ӿ�

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information
	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use	

	D3DDISPLAYMODE d3ddm;
	g_pD3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
	if(g_WindowMode)
	{
		d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
		d3dpp.BackBufferFormat = d3ddm.Format;
	}
	else
	{
		d3dpp.Windowed = FALSE;    // program windowed, not fullscreen	
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
		d3dpp.BackBufferWidth = SCREEN_WIDTH;    // set the width of the buffer
		d3dpp.BackBufferHeight = SCREEN_HEIGHT;    // set the height of the buffer
	}
	d3dpp.EnableAutoDepthStencil = TRUE;//������Ȼ���
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE; // Do NOT sync to vertical retrace
	//d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_DEFAULT; // Sync to vertical retrace
	d3dpp.Flags                  = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// ����3D�豸
	g_pD3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,	hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,
		&g_pD3ddev);

	//3D��2D�任
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ), 
		SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f );
	g_pD3ddev->SetTransform( D3DTS_PROJECTION, &matProj );

	g_pD3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pD3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: FreeDirect3D()
// Desc: Free all DirectDraw objects
//-----------------------------------------------------------------------------
void CleanD3D(void)
{
	_RELEASE(g_pD3ddev);    // close and release the 3D device
	_RELEASE(g_pD3d);    // close and release Direct3D
}

//-----------------------------------------------------------------------------
// Name: InitDirectInput()
// Desc: ��DirectInput����һ�������豸
//-----------------------------------------------------------------------------
HRESULT InitDirectInput( HWND hWnd )
{
	HRESULT hr;

	CleanDirectInput();

	// Create a DInput object
	if( FAILED( hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (VOID**)&g_lpdi, NULL ) ) )
		return hr;

	// Obtain an interface to the system keyboard device.
	if( FAILED( hr = g_lpdi->CreateDevice( GUID_SysKeyboard, &g_pKeyboard, NULL ) ) )
		return hr;

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.
	if( FAILED( hr = g_pKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
		return hr;

	// Set the cooperative level to let DirectInput know how
	// this device should interact with the system and with other
	// DirectInput applications.
	hr = g_pKeyboard->SetCooperativeLevel( hWnd, DISCL_NOWINKEY | 
		DISCL_NONEXCLUSIVE | 
		DISCL_FOREGROUND );

	if( hr == DIERR_UNSUPPORTED )
	{
		CleanDirectInput();
		MessageBox( hWnd, TEXT("SetCooperativeLevel() returned DIERR_UNSUPPORTED.\n")
			TEXT("For security reasons, background exclusive keyboard\n")
			TEXT("access is not allowed."), TEXT("PrototypeX"), MB_OK );
		return S_OK;
	}

	if( FAILED(hr) )
		return hr;

	// Acquire the newly created device
	g_pKeyboard->Acquire();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: FreeDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
void CleanDirectInput( void )
{	
	// Unacquire the device one last time just in case 
	// the app tried to exit while the device is still acquired.
	if( g_pKeyboard ) 
		g_pKeyboard->Unacquire();

	// Release any DirectInput objects.
	_RELEASE( g_pKeyboard );
	_RELEASE( g_lpdi );
}





void InitializeSprites(void)
{
	D3DXCreateSprite( g_pD3ddev, &g_pSprite );
	//��������
	D3DXIMAGE_INFO d3dxImageInfo;
	D3DXCreateTextureFromFileEx(g_pD3ddev,"main.jpg",
								800,600,
								1,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
								D3DX_DEFAULT,D3DX_DEFAULT,
								D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f),
								&d3dxImageInfo,
								NULL,
								&g_pTextTitle);

	//startButton
	D3DXCreateTextureFromFileEx(g_pD3ddev,"img\\startbutton.png",
		150,60,
		1,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_DEFAULT,D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f),
		&d3dxImageInfo,
		NULL,
		&g_pTextButton);
	
	//��ͼ����
	D3DXCreateTextureFromFileEx(g_pD3ddev,"img\\map.png",
		512,384,
		1,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_DEFAULT,D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f),
		&d3dxImageInfo,
		NULL,
		&g_pTextureMap);


}
