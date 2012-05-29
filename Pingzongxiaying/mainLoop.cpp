//-----------------------------------------------------------------------------
// Name: GameStart()
// Desc: Initialize all DirectX objects to be used
//-----------------------------------------------------------------------------
HRESULT GameStart( )
{
	g_bActive=TRUE;

	HRESULT hr;

	HWND hWnd = FindWindow(szWindowClass,szTitle);

	if( FAILED( hr = InitD3D( hWnd ) ) )
		return hr;//����3D�豸

	if( FAILED( hr = InitDirectInput( hWnd ) ) )//��ʼ������ӿ�
		return hr;

	InitializeSprites();
	//InitializeStars();
	//InitializeExhaust();

	//g_dwLastFireTick = timeGetTime();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: GameOver()
// Desc: Release all the objects
//-----------------------------------------------------------------------------
void GameOver()
{
	CleanD3D();
	CleanDirectInput();

	_RELEASE(g_pTextTitle);
	_RELEASE(g_pTextButton);

	//for( g_sprite_i = g_SpriteList.begin(); g_sprite_i != g_SpriteList.end(); ++g_sprite_i )
	//	g_sprite_i->releaseMemory();

	//// Cleanup the STL generated linked list
	//g_SpriteList.erase( g_SpriteList.begin(), g_SpriteList.end() );
}


//void MoveMainRole()
//{
//
//}

/** 
	��Ⱦ��֡
*/
void Render_frame()
{
	g_dAnimationTimer  += g_dElpasedTime;
	g_dControllerTimer += g_dElpasedTime;

	if( g_dElpasedTime >= 0.016 )
		g_dElpasedTime = 0.0; // ��֤60 FPS
	else
		return;//̫���ˣ�����һ�ΰ�

	g_pD3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

	g_pD3ddev->BeginScene();    // begins the 3D scene

	char buffer[256];
	g_pKeyboard->GetDeviceState(sizeof(buffer),(LPVOID)&buffer); //��ȡ����

	if (g_gamestate==K_TITLE)//����������˵�����
	{
		////

		////��Ⱦ����
		//LPDIRECT3DTEXTURE9 pTextSprite;
		//D3DXIMAGE_INFO d3dxImageInfo;
		//D3DXCreateTextureFromFileEx(g_pD3ddev,"main.jpg",
		//							800,600,
		//							1,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		//							D3DX_DEFAULT,D3DX_DEFAULT,
		//							D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f),
		//							&d3dxImageInfo,
		//							NULL,
		//							&pTextSprite);
		//D3DXCreateSprite( g_pD3ddev, &g_pSprite );
		//g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		//g_pSprite->Draw(pTextSprite,NULL, 0, 0, 0x99ffffff);
		//g_pSprite->End();

		//ID3DXSprite* pSprite2=NULL;
		////����Ⱦһ����Ⱦ����
		//LPDIRECT3DTEXTURE9 pTextSprite2;
		//D3DXIMAGE_INFO d3dxImageInfo2;
		//D3DXCreateTextureFromFileEx(g_pD3ddev,"img\\startbutton.png",
		//	300,100,
		//	1,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		//	D3DX_DEFAULT,D3DX_DEFAULT,
		//	D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f),
		//	&d3dxImageInfo2,
		//	NULL,
		//	&pTextSprite2);
		//D3DXCreateSprite( g_pD3ddev, &pSprite2 );
		//g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		//D3DXVECTOR3 vPosition( 500.0f, 200.0f, 0.0f );
		//g_pSprite->Draw(pTextSprite2,NULL, 0, &vPosition, 0x99ffffff);
		//g_pSprite->End();

		g_Title.LoadTitleIni("ini\\TITLE.INI","Title");
		g_Title.ShowTitle(g_pD3ddev);
		//g_Title.LoadTitleIni("ini\\TITLE.INI","Title");
		//g_Title.ShowTitle(g_pD3ddev);

		D3DXVECTOR3 vPosition( 600.0f, 400.0f, 0.0f );
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		g_pSprite->Draw(g_pTextTitle,NULL, 0, 0, 0x99ffffff);//���Ʊ���
		g_pSprite->Draw(g_pTextButton,NULL, 0, &vPosition, 0x99ffffff);//���ư�ť1
		g_pSprite->End();

		if( KEYDOWN(buffer, DIK_SPACE) )
			g_gamestate=K_GAMING;//������Ϸ
		
	}
	else if (g_gamestate==K_GAMING)//������Ϸ״̬
	{
		//��Ⱦ����
		D3DXIMAGE_INFO d3dxImageInfo;
		
		RECT  rcGrass;//�ݵ�λ��
		rcGrass.top=320;
		rcGrass.bottom=384;
		rcGrass.left=192;
		rcGrass.right=256;
		D3DXVECTOR3 vPosition( 0.0f, 0.0f, 0.0f );
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		for (int x=0;x<864;x+=64)//����ͼ
		{
			for (int y=0;y<664;y+=64)
			{
				vPosition.x=x;
				vPosition.y=y;
				g_pSprite->Draw(g_pTextureMap,&rcGrass, 0, &vPosition, 0x99ffffff);
			}
		}
		RECT rcMounting;
		rcMounting.top=128;
		rcMounting.bottom=192;
		rcMounting.left=128;
		rcMounting.right=192;
		vPosition.x=128;
		vPosition.y=192;
		for (int y=64;y<664;y+=64)
		{
			vPosition.y=y;
			g_pSprite->Draw(g_pTextureMap,&rcMounting, 0, &vPosition, 0x99ffffff);
		}		
		g_pSprite->End();

		if (g_dAnimationTimer>10000)//��ɫ�ƶ�
		{
					
			g_MainRole.NextFrame();
			g_dAnimationTimer=0.0;
		}
		if (g_dControllerTimer>1000)//���ư������
		{
			if( KEYDOWN(buffer, DIK_UP) )
				g_MainRole.MoveRole(K_UP);//����
			if( KEYDOWN(buffer, DIK_DOWN) )
				g_MainRole.MoveRole(K_DOWN);//����
			if( KEYDOWN(buffer, DIK_LEFT) )
				g_MainRole.MoveRole(K_LEFT);//����
			if( KEYDOWN(buffer, DIK_RIGHT) )
				g_MainRole.MoveRole(K_RIGHT);//����
			g_dControllerTimer=0;
		}
		
		g_MainRole.DrawRole(g_pD3ddev);

	}
	
	//g_pD3ddev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );//���ò���ƽ��
	//g_pD3ddev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	//for( g_sprite_i = g_SpriteList.begin(); g_sprite_i != g_SpriteList.end(); ++g_sprite_i )
		//g_sprite_i->drawSprite( g_pD3ddev );



	g_pD3ddev->EndScene();    // ends the 3D scene

	g_pD3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}