#ifndef HITMOLE_USERDEFINED_H
#define HITMOLE_USERDEFINED_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct USER_DEFINE
{
 DF_Windows windows;//��Ϸ�������洰��
 DF_PictureLibrary * picLib;//��Ϸ�����õ�ͼƬ��	
 gm_s16 imgIcon;
 gm_s8 selectnum;
 gm_s16 border;
}UserDefine;

extern void initUserDefine(UserDefine * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void HitMole_UserDefine_Windows_Render(void * param);//���������������
 void HitMole_UserDefine_windows_Update(void * param);//�������水������
#endif