/************************************************************************/
/* ½ÇÉ«Àà
/* @Author:OneDouble													*/
/************************************************************************/
#include "stdafx.h"


CRole::CRole():
m_hp(100),m_mp(100),m_bAlive(true),
m_nFrameHeight(60),m_nFrameWidth(40),
m_fPosition_x(0),m_fPosition_y(0),
m_eDirection(K_DOWN),m_eStep(K_STEP_FIRST),
m_sRoleName("guwen")
{

}

CRole::~CRole()
{
	_RELEASE(m_pSpriteTexture);
	_RELEASE(m_pD3DXSprite);
}

CRole::CRole(char* filename):m_hp(100),m_mp(100),m_bAlive(true),
m_nFrameHeight(60),m_nFrameWidth(40),
m_fPosition_x(0),m_fPosition_y(0),
m_eDirection(K_DOWN),m_eStep(K_STEP_FIRST),
m_sRoleName("guwen")
{
	m_sFileName=filename;
}
bool CRole::DrawRole( LPDIRECT3DDEVICE9 pDevice )
{
	if( m_pD3DXSprite == NULL )
	{
		D3DXIMAGE_INFO d3dxImageInfo;

		D3DXCreateTextureFromFileEx( pDevice,
			LPCTSTR(m_sFileName.c_str()),
			160, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
			240, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
			1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
			0, //D3DPOOL_DEFAULT,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED, //D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f),
			&d3dxImageInfo,
			NULL,
			&m_pSpriteTexture );

		D3DXCreateSprite( pDevice, &m_pD3DXSprite );
	}

		RECT  rcSource;

		rcSource.top    = m_eDirection  * m_nFrameHeight;
		rcSource.left   = m_eStep		* m_nFrameWidth ;
		rcSource.bottom = rcSource.top  + m_nFrameHeight;
		rcSource.right  = rcSource.left + m_nFrameWidth;

		D3DXVECTOR3 vCenter( 0.0f, 0.0f, 0.0f );
		D3DXVECTOR3 vPosition( m_fPosition_x, m_fPosition_y, 0.0f );

		m_pD3DXSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_pD3DXSprite->Draw( m_pSpriteTexture,
				&rcSource,
				&vCenter,
				&vPosition,
				D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,1.0f) );
		}
		m_pD3DXSprite->End();

	return true;

}

bool CRole::MoveRole(DIRECTION dir)
{
	m_eDirection=dir;
	if(dir==K_DOWN)
		m_fPosition_y += m_nFrameHeight/10;
	if(dir==K_UP)
		m_fPosition_y -= m_nFrameHeight/10;
	if(dir==K_LEFT)
		m_fPosition_x -= m_nFrameWidth/10;
	if(dir==K_RIGHT)
		m_fPosition_x += m_nFrameWidth/10;
	return true;
}
bool CRole::NextFrame()
{
	switch (m_eStep)
	{
		case(K_STEP_FIRST):
			m_eStep=K_STEP_SECOND;
			break;
		case(K_STEP_SECOND):
			m_eStep=K_STEP_THIRD;
			break;
		case(K_STEP_THIRD):
			m_eStep=K_STEP_FOUTH;
			break;
		case(K_STEP_FOUTH):
			m_eStep=K_STEP_FIRST;
			break;
	}

	return true;
}