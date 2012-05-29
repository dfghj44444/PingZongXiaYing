//********************************************
//	封面类
//  @Create：2010.11.29.
//  @Author:OneDouble
//********************************************
#include "stdafx.h"
using namespace std;

CTitle::CTitle()
{
	m_Select=0;
	m_pButton = NULL;
	m_pBackGroundFile = NULL;
}

CTitle::~CTitle()
{
	_DELETE_ARRAY(m_pButton);
	_FREE( m_pBackGroundFile );
}

/** 读取
	@param filename:文件名
*/
void CTitle::LoadTitleIni(char *filename, char *index)
{
	Wxm_IniFile Ini(filename);

	m_pBackGroundFile=Ini.ReadValue(index, "BackGroundFile");

	m_ButtonNum=Ini.ReadValueInt(index, "ButtonCount");
	m_pButton=new CButton[m_ButtonNum];

	//初始化按钮
	char* strFile;
	char* strIndex;
	for(int i=0; i<m_ButtonNum; i++)
	{
		strFile = Ini.ReadValue(index, i);
		strIndex = Ini.ReadKey(index,i);
		m_pButton[i].LoadIni(strFile, strIndex);
		//_FREE(strFile);
		//_FREE(strIndex);
	}

	//初始化字体
	//char *strTemp = GameIni.ReadValue("配置文件","字体");
	//ShowVersionFont.LoadFont(strTemp, "版本字体");
	//_FREE(strTemp);
	
	//strTemp = GameIni.ReadValue("Start","version");
	//strcpy(m_szVersion,strTemp);
	//_FREE(strTemp);
}

//------------------------------------

//显示
void CTitle::ShowTitle(LPDIRECT3DDEVICE9 pD3ddev )
{
	//渲染背景
	LPDIRECT3DTEXTURE9 pTextSprite;
	D3DXIMAGE_INFO d3dxImageInfo;
	ID3DXSprite* pSprite;
	D3DXCreateTextureFromFileEx(pD3ddev,m_pBackGroundFile,
								800,600,
								1,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
								D3DX_DEFAULT,D3DX_DEFAULT,
								D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f),
								&d3dxImageInfo,
								NULL,
								&pTextSprite);
	D3DXCreateSprite( pD3ddev, &pSprite );
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pSprite->Draw(pTextSprite,NULL, 0, 0, 0x99ffffff);
	pSprite->End();
	for(int i=0; i<m_ButtonNum; i++)
	{
		m_pButton[i].drawSprite(pD3ddev);
	}
}

//封面循环
void CTitle::DoMenu()
{
	int bHigh=-1, Contral=1;
	int oldx, oldy;

	//g_ePlayState = PS_Null;
	bool b[3]={0,0,0};

	/*Music.Stop();
	WCHAR* str = WChar("music\\title.mid");
	Music.LoadMusic(str);
	_DELETE(str);
	Music.Play();*/

	////读入背景页面
	//DDReLoadBitmap(lpDDSBackGround, BackGroundFile);
	//for(int i=0; i<ButtonNum; i++)
	//{
	//	Button[i].CheckLoop(lpDDSBackGround, -1);
	//}

	//ColorOut(lpDDSBackGround, 100);
	//
	//CCursor::GetCursor(CCursor::CS_CHANGEMAP).pPic.SetShowCount(0);

	////显示版本号
	//int showversion_x,showversion_y;
	//TEXTMETRIC tm;
	//ShowVersionFont.GetFontInfo(lpDDSBack,&tm);
	//showversion_x = MainWidth-tm.tmAveCharWidth*strlen(m_szVersion)-4;
	//showversion_y = MainHeight-tm.tmHeight-tm.tmExternalLeading-4;
	//ShowVersionFont.PrintText( lpDDSBackGround,showversion_x,showversion_y,m_szVersion);
	//菜单循环
	MSG msg;
	if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
            if (!GetMessage(&msg, NULL, 0, 0)) return;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
		}
	else
		{
			////获取输入信息
			//GetInputData();
			//
			////背景
			//Blt(lpDDSBack, 0, 0, lpDDSBackGround, RectScreen, false);
			//
			//if( Contral == 0 && oldx!=point.x || oldy!=point.y )
			//{
			//	Contral=1;
			//	oldx=point.x;
			//	oldy=point.y;
			//}
			//else if( Contral == 1 && ( UP_DOWN || DOWN_DOWN ) )
			//{
			//	Contral=0;
			//	Select=0;
			//	key=0;
			//}

			//if( Contral==0 )	//键盘
			//{
				//选择
				//if( UP_DOWN )
				//{
				//	Select--;
				//	if( Select<0 ) Select=ButtonNum-1;
				//	CMenu::Sound_HighLight.Play();
				//}
				//if( DOWN_DOWN )
				//{
				//	Select++;
				//	if( Select>ButtonNum-1 ) Select=0;
				//	CMenu::Sound_HighLight.Play();
				//}
				//
				////显示
				//for(int i=0; i<ButtonNum; i++)
				//{
				//	if( i==Select ) bHigh=1;
				//	else bHigh=-1;

				//	int ret=Button[i].CheckLoop(lpDDSBack, bHigh);
				//	if( ret==2 )	Select=i;
				//}

				//if( A_UP )
				//	Button[Select].CheckLoop(lpDDSBack, 2);

				//if( A_UP )
				//{
				//	switch( Select )
				//	{
				//	case 0:		//new game
				//		{
				//			CMenu::Sound_TileClick.Play();
				//			Music.Stop();
				//			NewGame();
				//			char *str=GameIni.ReadValue("Start", "起始脚本");
				//			Script.Run( str );
				//			_FREE(str);
				//			return;
				//		}
				//	case 1:		//load game
				//		CMenu::Sound_TileClick.Play();
				//		if( CMenu::LoadSave.DoMenu(lpDDSBack, true, 168, 48 ) )
				//		{
				//			g_ePlayState=PS_MAIN;
				//			FadeIn(2);
				//			map.ShowMap();
				//			if( CMusic::bPlay )	//背景音乐
				//			{
				//				Music.Resume();
				//			}
				//			return;
				//		}
				//		DDReLoadBitmap(lpDDSBackGround, BackGroundFile);
				//		ShowVersionFont.PrintText( lpDDSBackGround,showversion_x,showversion_y,m_szVersion);
				//		break;
				//	case 2:		//exit game
				//		CMenu::Sound_TileClick.Play();
				//		Music.Stop();
				//		RunGame=false;
				//		return;
				//	}
				//}
			//}
			//else if( Contral==1 )	//鼠标
			//{
			//	int ret[3], ret2[3];
			//	for(int i=0; i<ButtonNum; i++)
			//	{
			//		ret[i]=Button[i].CheckLoop(lpDDSBack, -1);
			//		if( ret[i]==2 && ret2[i] != 2 )
			//		{
			//			Select=i;
			//			CMenu::Sound_HighLight.Play();
			//		}
			//		ret2[i] = ret[i];
			//	}

			//	for(int i=0; i<ButtonNum; i++)
			//	{
			//		if( ret[i]==1 )
			//		{
			//			switch( Select )
			//			{
			//			case 0:		//new game
			//				{
			//					CMenu::Sound_TileClick.Play();
			//					Music.Stop();
			//					NewGame();
			//					char *str=GameIni.ReadValue("Start", "起始脚本");
			//					Script.Run( str );
			//					_FREE(str);
			//					return;
			//				}
			//			case 1:		//load game
			//				CMenu::Sound_TileClick.Play();
			//				if( CMenu::LoadSave.DoMenu(lpDDSBack, true, 168, 48 ) )
			//				{
			//					g_ePlayState=PS_MAIN;
			//					FadeIn(2);
			//					map.ShowMap();
			//					if( CMusic::bPlay )	//背景音乐
			//					{
			//						Music.Resume();
			//					}
			//					return;
			//				}
			//				DDReLoadBitmap(lpDDSBackGround, BackGroundFile);
			//				ShowVersionFont.PrintText( lpDDSBackGround,showversion_x,showversion_y,m_szVersion);
			//				break;

			//			case 2:		//exit game
			//				CMenu::Sound_TileClick.Play();
			//				Music.Stop();
			//				RunGame=false;
			//				return;
			//			}
			//		}
			//	}
			//}
			//ShowMouseCursor(lpDDSBack, false);
			//_UpdateScreen();

			////直接进入地图编辑模式
			//if( key==DIK_F5 && Key.GetState(DIK_LALT) )
			//{
			//	NewGame();
			//	Music.Stop();
			//	//初始化Undomap
			//	UndoMap=new Cell_Struct[map.Width*map.Height];
			//	memcpy(UndoMap, map.Cell, sizeof(Cell_Struct)*map.Width*map.Height);
			//	g_ePlayState=PS_EDIT;
			//	bShowHardCursor=true;
			//	ShowCursor(true);
			//	return;
			//}
		}
		//else WaitMessage();	//等待消息
}
