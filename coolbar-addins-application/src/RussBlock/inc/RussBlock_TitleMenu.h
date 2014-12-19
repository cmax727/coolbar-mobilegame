/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* �ļ����ƣ�RussBlock_TitleMenu.h

�˹�������ʾ��Ϸ�����˵�����
*******************************************************************/

#ifndef RUSSBLOCK_TITLEMENU_H
#define RUSSBLOCK_TITLEMENU_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct RUSSBLOCK_TITLE_MENU
{
	gm_s32 selectMenu;
	gm_s16 imgTitleMenu[6];//���˵�ͼƬ��
	gm_s16 imgMenuBar;
	gm_s16 imgCmd;
	DF_PictureLibrary * picLib;
	DF_Windows windows;
}RussBlockTitleMenu;
//��ʹ�����˵�����
extern void initRussBlockTitleMenu(RussBlockTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void RussBlock_TitleMenu_Render(void * param);//���˵��л���

void RussBlock_TitleMenu_Update(void * param);//���˵���ˢ��
/*���˵��󱳾� ���� width��height��Ϊ MENUBARWIDTH,MENUBARHEIGHT �������� ,y Ϊy����*/
void RussBlock_MenuBar_Paint(DF_PictureLibrary * param,gm_s16 id,gm_s16 width,gm_s16 height,gm_s16 y);	





#endif
