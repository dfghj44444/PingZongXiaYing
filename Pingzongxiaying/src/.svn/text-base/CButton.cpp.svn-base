#include "stdafx.h"


CButton::CButton() 
{

}

CButton::~CButton()
{

}
void CButton::LoadIni(char* strFile,char* strIndex)
{
	Wxm_IniFile IniFile(strFile);
	strcpy(m_chSpriteTextureName,IniFile.ReadValue(strIndex,"PicFileName"));
	strcpy(m_chType,"button");
	m_nWidth  = IniFile.ReadValueInt(strIndex,"Width");
	m_nHeight = IniFile.ReadValueInt(strIndex,"Height");
	m_bSingleFrame = IniFile.ReadValueInt(strIndex,"SingleFrame");
	m_bActive      = true;
	m_nFrameOffset_x     = IniFile.ReadValueInt(strIndex,"X");
	m_nFrameOffset_y     = IniFile.ReadValueInt(strIndex,"Y");
	m_nFrameWidth        = IniFile.ReadValueInt(strIndex,"dX");
	m_nFrameHeight       = IniFile.ReadValueInt(strIndex,"dY");
	m_fPosition_x		 = IniFile.ReadValueInt(strIndex,"PosX");
	m_fPosition_x		 = IniFile.ReadValueInt(strIndex,"PosY");
}
