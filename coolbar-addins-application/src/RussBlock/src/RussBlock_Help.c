#include "RussBlock_Help.h"
#include "RussBlock_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
//��ʹ��������������Ϣ������ͼƬ������
void initRussBlockHelp(RussBlock_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=RussBlock_Help_Windows_Render;//��������
	myself->windows.UpdateCallBack=RussBlock_Help_windows_Update;//��������
	myself->picLib=picLib;
//	myself->imgHelp[0]=myself->picLib->GetImage(myself->picLib,"help.gif");
//	myself->imgHelp[1]=myself->picLib->GetImage(myself->picLib,"cmd.gif");
//	RussBlock_Loading_UpdateStep();
//	myself->imgHelp[2]=myself->picLib->GetImage(myself->picLib,"bottom.gif");
//	myself->imgMenuBar=russBlockPicLib.GetImage(&russBlockPicLib,"menubar.gif");
	RussBlock_Loading_UpdateStep();

	//ʹ���ı��༭����������
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,200);
	myself->textBox.SetDistance(&myself->textBox,20);
	myself->textBox.SetText(&myself->textBox,RussBlock_TextResource_Help);
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,30,40,SCREEN_WIDTH-TEXT_SIZE*4,135);
	myself->textBox.SetText(&myself->textBox,RussBlock_TextResource_Help);
#endif 
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
}
//���ư����н���
void RussBlock_Help_Windows_Render(void * param)
{
	RussBlock_Help * myself=(RussBlock_Help *)param;
	
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
#ifdef GAME_240_320
//	RussBlock_MenuBar_Paint(myself->picLib,myself->imgMenuBar,MENUBARWIDTH*6,MENUBARHEIGHT*7,9+5);//�����������
	myself->textBox.Render(&myself->textBox,0xffffff);//���ư�������
//	myself->picLib->DrawRegionEx(myself->picLib,myself->imgHelp[0],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgHelp[0]))>>1,9+7+5,0,40,92,20,true,0);
//	myself->picLib->DrawImage(myself->picLib,myself->imgHelp[2],0,SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgHelp[2]));
//	myself->picLib->DrawRegionEx(myself->picLib,myself->imgHelp[1],206,301,0,39,25,13,TRUE,0);
	getManagerPtr()->DrawString("�����¼���ҳ",25,64,298,0xffffff);
#endif 
#ifdef GAME_176_220 
//	RussBlock_MenuBar_Paint(myself->picLib,myself->imgMenuBar,MENUBARWIDTH*4,MENUBARHEIGHT*5,5);
	myself->textBox.Render(&myself->textBox,0xffffff);//���ư�������
//	myself->picLib->DrawRegionEx(myself->picLib,myself->imgHelp[0],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgHelp[0]))>>1,13,0,36,83,18,true,0);
//	myself->picLib->DrawImage(myself->picLib,myself->imgHelp[2],0,SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgHelp[2]));
//	myself->picLib->DrawRegionEx(myself->picLib,myself->imgHelp[1],148,203,0,39,25,13,TRUE,0);

	getManagerPtr()->DrawString("�����¼���ҳ",12,45 ,202,0xffffff);
#endif 
}
//�������������н���
void RussBlock_Help_windows_Update(void * param)
{
	RussBlock_Help * myself=(RussBlock_Help *)param;
	gm_s32 px,py;
	if (getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2))//������������
	{
		if (myself->textBox.curPage>0)//�ı���ҳ
		{
			myself->textBox.curPage--;
		}
		//ˢ����Ļ
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	else if (getManagerPtr()->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))
	{
		if (myself->textBox.curPage<myself->textBox.page-1)//�ı���ҳ
		{
			myself->textBox.curPage++;		
		}
		//ˢ����Ļ
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	if (getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))//�����˵�
	{		
		myself->textBox.curPage = 0;
		RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_MENU);
	}
	if(SCREEN_IsPointerDown())//�������
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();//���������Ļ��
#ifdef GAME_240_320
		if(CdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
#endif
#ifdef GAME_176_220
			if(CdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
#endif
			{
				myself->textBox.curPage = 0;
				RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_MENU);
				
			}

	}
}