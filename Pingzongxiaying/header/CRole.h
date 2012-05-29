
#ifndef _CROLE_H
#define _CROLE_H

#include "../../PublicLib/PublicLib.h"
//角色类
class CRole
{
public:


	CRole();
	~CRole();
	CRole(char* filename);
	bool DrawRole( LPDIRECT3DDEVICE9 pDevice );
	bool MoveRole(DIRECTION dir);
	bool NextFrame();


	int m_hp;//血量
	int m_mp;//魔法
	
	int m_nFrameHeight;//帧高
	int m_nFrameWidth;//帧宽
	FLOAT m_fPosition_x;
	FLOAT m_fPosition_y;

	DIRECTION m_eDirection;//朝向
	STEP m_eStep;//第几步
	bool m_bAlive;//是否活着
	std::string m_sRoleName;//角色名
	std::string m_sFileName;//文件名
	LPDIRECT3DTEXTURE9 m_pSpriteTexture;
	LPD3DXSPRITE       m_pD3DXSprite;

};
#endif