#include "ONFF_Help.h"
#include "ONFF_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
void initONFFHelp(ONFF_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=ONFF_Help_Windows_Render;
	myself->windows.UpdateCallBack=ONFF_Help_windows_Update;
	myself->picLib=picLib;
	myself->border = picLib->GetImage(picLib,"border.gif");
	ONFF_Loading_UpdateStep();
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,200);
	myself->textBox.SetDistance(&myself->textBox,20);
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,25,40,SCREEN_WIDTH-TEXT_SIZE*3,135);
#endif
	myself->textBox.SetText(&myself->textBox,"    ���˵������п����������������ÿ������ը���������ּ�2/8ѡ����/��ѡ����ּ�4/6��С/������ֵ��\n    ��Ϸ��4�أ���Ϸ�����п��ԳԽ�����Ʒ�ͼ�ǿ�ӵ���ÿ��200�ֽ���һ����������������Ʒ��򣬻������ּ�5��8��7��9�ֱ�����ϡ��¡������ƶ������ּ�0�ͷ�ը�����������ͣ��Ϸ��");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
}
void ONFF_Help_Windows_Render(void * param)
{
	ONFF_Help * myself=(ONFF_Help *)param;
	
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
#ifdef GAME_240_320
	extOldGameManager->DrawString("����",25,SCREEN_WIDTH/2-20,15,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);
	extOldGameManager->DrawString("��һҳ",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
	extOldGameManager->DrawString("����",25,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT,0xffff00);
#endif 
#ifdef GAME_176_220 
	extOldGameManager->DrawString("����",25,SCREEN_WIDTH/2-20,10,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);
	if(myself->textBox.curPage == 0)
			extOldGameManager->DrawString(" ��",12,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-20,0xffff00);
		else if(myself->textBox.curPage == 3)
			extOldGameManager->DrawString(" ��",12,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-20,0xffff000);
		else
			extOldGameManager->DrawString("����",12,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-20,0xffff00);
	extOldGameManager->DrawString("����",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
#endif
	
	
}

void ONFF_Help_windows_Update(void * param)
{
	ONFF_Help * myself=(ONFF_Help *)param;
	gm_s32 px,py;
	#ifdef GAME_240_320
		myself->picLib->FillRect(myself->picLib,9,288,20,20,GAME_ToRGB(36,19,121));
	#endif
	#ifdef GAME_176_220
		myself->picLib->FillRect(myself->picLib,9,195,20,20,GAME_ToRGB(36,19,121));
	#endif
	#ifdef	GAME_240_320
		if(myself->textBox.curPage == 0)
			extOldGameManager->DrawString("��һҳ",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
		else
			extOldGameManager->DrawString("��һҳ",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
		if (getManagerPtr()->IsKeyDown(MF_KEY_LEFTSOFT))//������������
		{
			if (myself->textBox.curPage==1)//�ı���ҳ
			{
				myself->textBox.curPage=0;
			}else
				myself->textBox.curPage=1;
			//ˢ����Ļ
			DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
		}
	#endif
	#ifdef	GAME_176_220
		if(myself->textBox.curPage >= 0 && myself->textBox.curPage <= 3)
		{
			if (getManagerPtr()->IsKeyDown(MF_KEY_UP | MF_KEY_2))//�ı���ҳ
			{
				myself->textBox.curPage--;
				if(myself->textBox.curPage < 0)
					myself->textBox.curPage = 0;
			}
			else if(getManagerPtr()->IsKeyDown(MF_KEY_DOWN | MF_KEY_8))
			{
				myself->textBox.curPage++;
				if(myself->textBox.curPage > 3)
					myself->textBox.curPage = 3;
			}
			DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
		}
			//ˢ����Ļ
	#endif
	if (extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT))
	{		
		myself->textBox.curPage = 0;
		ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
	}
#ifdef GAME_240_320
	if(SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
		if(CdRectPoint3(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))

			{
				myself->textBox.curPage = 0;
				ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
				
			}

	}
	
#endif

}

