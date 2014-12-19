/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* �ļ����ƣ�RussBlock_Help.h

�˹�������ʾ��Ϸ�а����������,����Ҫ���õײ��װTextBox����
ע:TextBox����������ʾ���������С��TextBox.curPage����ǰ��ʾҳ
*******************************************************************/

#ifndef RUSSBLOCK_HELP_H
#define RUSSBLOCK_HELP_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct RUSSBLOCK_HELP
{
	DF_Windows windows;//��Ϸ�������洰��
	DF_PictureLibrary * picLib;//��Ϸ�����õ�ͼƬ��
	TextBox textBox;   //�ı��༭��
//	gm_s16 imgHelp[4]; //��Ϸ�����м���ͼƬ��
//	gm_s16	imgMenuBar; //��Ϸ�����м���ͼƬ��
}RussBlock_Help;

extern void initRussBlockHelp(RussBlock_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void RussBlock_Help_Windows_Render(void * param);//���������������
 void RussBlock_Help_windows_Update(void * param);//�������水������
 void initHelp(RussBlock_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void Help_Windows_Render(void * param);
#endif