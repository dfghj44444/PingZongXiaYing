#pragma once

#include "../resource.h"

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void Render_frame();    // ��Ⱦ��֡/��ѭ��

enum GAMESTATE
{
	K_EMPTY,
	K_TITLE,//���˵�
	K_GAMING,//��Ϸ��
	K_FINISH,//��Ϸʧ��
	K_COUNT
};

/**
	ˢ����Ļ�ĺ���
	@param timeDelta ��ȥ��ʱ��
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
// Desc: ��DirectInput����һ�������豸
//-----------------------------------------------------------------------------
HRESULT InitDirectInput( HWND hWnd );
//-----------------------------------------------------------------------------
// Name: FreeDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
void CleanDirectInput( void );

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: ��ʼ��D3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd);
void CleanD3D(void);    // �ر�Direct3D�ͷ��ڴ�

//Ԥ������Դ
void InitializeSprites(void);