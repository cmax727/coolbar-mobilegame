#ifndef MEMORYBOX_ABOUT_H
#define MEMORYBOX_ABOUT_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct MEMORYBOX_ABOUT
{
	DF_Windows windows;//��Ϸ�������洰��
	DF_PictureLibrary * picLib;//��Ϸ�����õ�ͼƬ��
	TextBox textBox;   //�ı��༭��
	gm_s16 imgback;
}MemoryBox_About;

extern void initMemoryBoxAbout(MemoryBox_About * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void MemoryBox_About_Windows_Render(void * param);//���������������
 void MemoryBox_About_windows_Update(void * param);//�������水������
#endif

