#pragma once

#include "../resource.h"

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void Render_frame();    // 渲染单帧/主循环

enum GAMESTATE
{
	K_EMPTY,
	K_TITLE,//主菜单
	K_GAMING,//游戏中
	K_FINISH,//游戏失败
	K_COUNT
};

/**
	刷新屏幕的函数
	@param timeDelta 逝去的时间
*/
bool Display(float timeDelta);

//-----------------------------------------------------------------------------
// Name: GameStart()
// Desc: Initialize all DirectX objects to be used
//-----------------------------------------------------------------------------
HRESULT GameStart( );

//-----------------------------------------------------------------------------
// Name: GameOver()
// Desc: Release all the DirectDraw objects
//-----------------------------------------------------------------------------
void GameOver();

//-----------------------------------------------------------------------------
// Name: InitDirectInput()
// Desc: 用DirectInput创建一个键盘设备
//-----------------------------------------------------------------------------
HRESULT InitDirectInput( HWND hWnd );
//-----------------------------------------------------------------------------
// Name: FreeDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
void CleanDirectInput( void );

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: 初始化D3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd);
void CleanD3D(void);    // 关闭Direct3D释放内存

//预加载资源
void InitializeSprites(void);