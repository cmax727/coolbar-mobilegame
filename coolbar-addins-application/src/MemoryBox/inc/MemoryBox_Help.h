#ifndef MEMORYBOX_HELP_H
#define MEMORYBOX_HELP_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct MEMORYBOX_HELP
{
	DF_Windows windows;//��Ϸ�������洰��
	DF_PictureLibrary * picLib;//��Ϸ�����õ�ͼƬ��
	TextBox textBox;   //�ı��༭��
	gm_s16 imgback;
}MemoryBox_Help;

extern void initMemoryBoxHelp(MemoryBox_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void MemoryBox_Help_Windows_Render(void * param);//���������������
 void MemoryBox_Help_windows_Update(void * param);//�������水������
#endif

