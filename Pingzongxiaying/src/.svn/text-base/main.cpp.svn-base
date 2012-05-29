/************************************************************************/
/*  main.cpp : 定义应用程序的入口点。                                                                    */
/************************************************************************/


#include "stdafx.h"



#define MAX_LOADSTRING 100
// 设置屏幕尺寸
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

//#define FULL_SCREEN

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

LPDIRECT3D9			 g_pD3d		  = NULL;    // Direct3D接口指针
LPDIRECT3DDEVICE9	 g_pD3ddev	  = NULL;    //D3d设备指针
LPDIRECTINPUT8 g_lpdi       = NULL;	//D3d 输入接口指针
LPDIRECTINPUTDEVICE8 g_pKeyboard  = NULL;	//D3d键盘 输入设备
LPDIRECTINPUTDEVICE8 g_pMouse  = NULL;	//D3d鼠标 输入设备
DWORD MouseX, MouseY;					//鼠标坐标
DWORD MouseButton[4];					//按钮状态
ID3DXSprite* g_pSprite=NULL;

CTitle g_Title;//封面类

CRole g_MainRole("img\\guwen.png");//主角类

int	   g_WindowMode=1;		//0=全屏 other=窗口
BOOL   g_bActive = FALSE;	//是否窗口激活
RECT   g_rcWindow;

double g_dElpasedTime;//逝去时间
double g_dCurTime;//当前时刻
double g_dLastTime;//上次时刻
double g_dAnimationTimer  = 0.0;
double g_dControllerTimer = 0.0;
GAMESTATE g_gamestate=K_TITLE;//全局状态机

using namespace std;

//创建精灵列表
typedef list<CSprite> SPRITELIST;

SPRITELIST g_SpriteList;
SPRITELIST::iterator g_sprite_i;
SPRITELIST::iterator g_sprite_j;
SPRITELIST::iterator g_sprite_k;

//全局精灵和纹理
LPDIRECT3DTEXTURE9 g_pTextureMap,g_pTextTitle,g_pTextButton;
LPD3DXSPRITE       g_pD3DXSprite;


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PINGZONGXIAYING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	//读入游戏启动配置文件-(读取窗口模式)
	Wxm_IniFile Ini("ini\\setup.ini");
	g_WindowMode=Ini.ReadValueInt("Setup", "WindowMode");

	//获取系统当前分辨率
	int nowWidth=GetSystemMetrics(SM_CXSCREEN); 
	int nowHeight=GetSystemMetrics(SM_CYSCREEN);

	if( g_WindowMode != 0 && g_WindowMode != 1 )
	{
		if( IDYES==MessageBox(NULL, "使用窗口显示模式吗？\n[Alt+Enter] 切换全屏或窗口显示."
			, "注意", MB_YESNO))
			g_WindowMode=1;
		else
			g_WindowMode=0;
	}

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	//初始化DX
	if( FAILED( GameStart() ) )
	{
		return FALSE;
	}
	

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PINGZONGXIAYING));

	//static float lastTime = (float)timeGetTime(); 
	// 主消息循环:
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
				Render_frame();//渲染帧
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
	//// 清除DirectX 和 COM
	//CleanD3D();
	//CleanDirectInput();
	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
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
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

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
   
   GetWindowRect(hWnd,&g_rcWindow);//为分辨率改变存原分辨率

   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
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
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case WM_SIZE:
			// 检查是否窗口最小化
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
		// TODO: 在此添加任意绘图代码...
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









// “关于”框的消息处理程序。
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
	刷新屏幕的函数
	@param timeDelta 逝去的时间
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
// Desc: 初始化D3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	g_pD3d = Direct3DCreate9(D3D_SDK_VERSION);    // 创建Direct3接口

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
	d3dpp.EnableAutoDepthStencil = TRUE;//启用深度缓存
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE; // Do NOT sync to vertical retrace
	//d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_DEFAULT; // Sync to vertical retrace
	d3dpp.Flags                  = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// 创建3D设备
	g_pD3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,	hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,
		&g_pD3ddev);

	//3D到2D变换
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
// Desc: 用DirectInput创建一个键盘设备
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
	//加载纹理
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
	
	//地图纹理
	D3DXCreateTextureFromFileEx(g_pD3ddev,"img\\map.png",
		512,384,
		1,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_DEFAULT,D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f),
		&d3dxImageInfo,
		NULL,
		&g_pTextureMap);


}
