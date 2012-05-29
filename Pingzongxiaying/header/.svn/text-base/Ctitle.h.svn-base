#ifndef _CTITLE_H
#define _CTITLE_H

//********封面类*********
class CTitle{
public:
	int m_ButtonNum;			//按钮数量
	CButton *m_pButton;		//按钮

	int m_Select;				//当前选择
	char *m_pBackGroundFile;	//背景图片文件

public:
	//CFont ShowVersionFont;
	CTitle();
	~CTitle();

	void LoadTitleIni(char *, char *);					//读入配置
	void ShowTitle(LPDIRECT3DDEVICE9 pD3ddev );		//显示
	void DoMenu();		//封面循环
private:
	char m_szVersion[10];
};

#endif