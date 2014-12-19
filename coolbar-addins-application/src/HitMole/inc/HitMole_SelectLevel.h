#ifndef HITMOLE_SELECTLEVEL_H
#define HITMOLE_SELECTLEVEL_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct SELECTLEVEL
{
 DF_Windows windows;//��Ϸ�������洰��
 DF_PictureLibrary * picLib;//��Ϸ�����õ�ͼƬ��	
 gm_s16 imgIcon;
 gm_s8 selectnum;
 gm_s16 border;
}SelectLevel;

extern void initSelectLevel(SelectLevel * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void HitMole_SelectLevel_Windows_Render(void * param);//���������������
 void HitMole_SelectLevel_windows_Update(void * param);//�������水������
#endif

