/*******************************************************************
* 
* 
* �ļ����ƣ�MemoryBox_Title.h

�˹�������ʾ��Ϸ��Logo����
*******************************************************************/

#ifndef MEMORYBOX_TITLE_H
#define MEMORYBOX_TITLE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct MEMORYBOX_TITLE
{
	gm_u16 timer;
	gm_s32 imgTitle;//LogoͼƬ��
	DF_Windows windows;//Logo���ڽ���
	DF_PictureLibrary * picLib;//LogoͼƬ��
}MemoryBoxTitle;


extern void initMemoryBoxTitle(MemoryBoxTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void MemoryBox_Title_Windows_Render(void * param);//Logo�������

void MemoryBox_Title_Windows_Update(void * param);//Logo����ˢ��
#endif
