#ifdef INIFILE_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#ifndef _WXM_INI_H
#define _WXM_INI_H

class  DLL_EXPORT  Wxm_IniFile{
private:
	char m_FileName[MAX_PATH];	//�ļ���
	int m_DataLen;			//�ļ�����
	char *m_pData;				//�ļ�����

	int m_IndexNum;			//������Ŀ��[]����Ŀ��
	int *m_pIndexList;			//������λ���б�

	int m_Point;				//��ǰָ��
	int m_Line, m_Word;			//��ǰ�У���ǰ��

public:
	Wxm_IniFile();
/**
	�вι���
	@param filename ���򿪵��ļ���
*/
	Wxm_IniFile(char *);		
	~Wxm_IniFile();				

	char *GetData();		//�����ļ�����
	int GetLines(int);			//�����ļ�������
/**
	�����ļ�
	@param filename ��������ļ���
*/
	bool Open(char *);		
/** 
	�����ļ�
	@param filename:�ļ���
*/
	bool Save(char *filename=NULL);		

private:
	
/** 
	��������е�����λ�ò�������m_pIndexList
*/
	void InitIndex();			
/**
	����ָ������λ��
	@param string ֵ
	@return �������ڵ�λ��
*/
	int FindIndex(char *);		
/** 
	����ָ�����ݵ����ݵ�λ��
	@param index ������
	@param string ����ֵ
	@return Ŀ��λ��
*/
	int FindKey(int, char *);	
/** 
	�ߵ���һ��
	@param p λ��
	@return ��һ������
*/
	int GotoNextLine(int); 	

/**
	��ָ��λ�ö�һ���ݼ���ֵ
	@param p λ������
	@return ָ��λ����������
*/
	char *ReadKey(int &);	
/** 
	��ָ��λ�ö�һ���ַ���
	@param p  ��������
*/
	char *ReadData(int);

/** 
	���һ������
*/
	bool AddIndex(char *);		
/** 
	�ڵ�ǰλ�ü���һ������
	@param p λ��
	@param name ���ݼ�
	@param string ����ֵ
*/
	bool AddData(int, char *, char *);	
/** 
	�ڵ�ǰλ���޸�һ�����ݵ�ֵ
	@param p λ��
	@param name ���ݼ�
	@param string ����ֵ

*/
	bool ModityData(int, char *, char *); 

public:


/** 
	����ͨ��ʽ��һ�ַ�������
	@param ������
	@param ������
	@return Ŀ���ַ���
*/
	char *ReadValue(char *, char *);	
/** 
	��ָ�����ж�һ������ͬ����Ϊ�˳����Ķ�ȡ�����ҿ��Բ����ľ��������
	@param index:������
	@param lines:�к�
*/
	int ReadValueInt(char *, int );	
/**
	����ͨ��ʽ��һint����
	@param index ������
	@param name ���ݼ�
*/
	int ReadValueInt(char *, char *);	

/** 
	��ָ�����ж�һ�ַ��������������������ڶ���һ�����ݣ�
	���ҿ��Բ����ľ�������֣�������ѭ���ķ�ʽ��
	@param ������
	@param �к�
	@return ����ֵ
*/
	char *ReadValue(char *, int);	
	/** 
	��ָ�����ж�һ���ݼ���Ŀ�Ļ���Ϊ��������ȡ��
	@param index ������
	@param lines �к�
	@return ���ݼ�
*/
	char *ReadKey(char *, int);	
/** 
	����ͨ��ʽдһ����
	@param index ������
	@param name ���ݼ�
	@param string ����ֵ��int��
*/
	bool WriteValueInt(char *, char *, int);	
	/** 
	����ͨ��ʽдһ�ַ������ݡ����������֣�����
	@param index ������
	@param name ���ݼ�
	@param string ����ֵ
*/
	bool WriteValue(char *, char *, char *);	

	/** 
	�������������������Ǳ���(����)����ι��ж����У�һ��������ѭ��������
	@param index ������
*/
	int GetContinueDataNum(char *);			//������������������INDEX����һ�����У�
};

#endif