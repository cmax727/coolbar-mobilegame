#include "HitMole_Help.h"
#include "HitMole_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//��ʹ��������������Ϣ������ͼƬ������
void initHitMoleHelp(HitMole_Help* myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=HitMole_Help_Windows_Render;//��������
	myself->windows.UpdateCallBack=HitMole_Help_windows_Update;//��������
	myself->picLib=picLib;
	myself->border=picLib->GetImage(picLib,"border.gif");
	//ʹ���ı��༭����������
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,45,SCREEN_WIDTH-40,240);
	myself->textBox.SetDistance(&myself->textBox,20);
	myself->textBox.SetText(&myself->textBox,"    ������1-9����Ӧ9���ض��Ӵ�(��������ֱ�ӵ�),ȷ����������һ��,0����/����Ч,�������ͣ��������ؿ�ʼ���档\n    ����Ϸ����9���Ѷȣ�����ʼ���Ѷ�1����,��һ����20ֻ����,�Ժ�ÿ�ؼ�10ֻ�Ѷ�Ҳ������,�������ﵽ��Ӧ�ٷֱ�,�ſ��Թ���,ע�⣺��Ҫ�����\n    �Զ����ѡ���ʵ��Ѷ�,һ��ʼ��ʮ����,ÿ�ﵽһ���ķ���������һ����,©��һֻ����,����һֻ����,��Ҫ��һ����,ֱ������Ϊ0��Ϸ������\n    ����Ϸ(2Ԫ/10��)��ᱦ(28�ᱦ/��)��");
	
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,15,40,SCREEN_WIDTH-TEXT_SIZE*2,165);
	myself->textBox.SetText(&myself->textBox,"    ������1-9����Ӧ9���ض��Ӵ�(��������ֱ�ӵ�),ȷ����������һ��,0����/����Ч,�������ͣ��������ؿ�ʼ���档\n    ����Ϸ����9���Ѷȣ�����ʼ���Ѷ�1����,��һ����20ֻ����,�Ժ�ÿ�ؼ�10ֻ�Ѷ�Ҳ������,�������ﵽ��Ӧ�ٷֱ�,�ſ��Թ���,ע�⣺��Ҫ�����\n    �Զ����ѡ���ʵ��Ѷ�,һ��ʼ��ʮ����,ÿ�ﵽһ���ķ���������һ����,©��һֻ����,����һֻ����,��Ҫ��һ����,ֱ������Ϊ0��Ϸ������\n    ����Ϸ(2Ԫ/10��)��ᱦ(28�ᱦ/��)��");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
#endif
	HitMole_Loading_UpdateStep();
	
}
//���ư����н���
void HitMole_Help_Windows_Render(void * param)
{
	HitMole_Help* myself=(HitMole_Help *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
	
#ifdef GAME_240_320
	extOldGameManager->DrawString("����",25,SCREEN_WIDTH/2-20,15,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);//���ư�������
	extOldGameManager->DrawString("��һҳ",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
	extOldGameManager->DrawString("����",25,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT,0xffff00);
#endif 
#ifdef GAME_176_220 
	extOldGameManager->DrawString("����",25,SCREEN_WIDTH/2-20,10,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);//���ư�������
	if(myself->textBox.curPage == 0)
			extOldGameManager->DrawString(" ��",12,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-20,0xffff00);
		else if(myself->textBox.curPage == 3)
			extOldGameManager->DrawString(" ��",12,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-20,0xffff000);
		else
			extOldGameManager->DrawString("����",12,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-20,0xffff00);
	extOldGameManager->DrawString("����",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
#endif
	
}
//�������������н���
void HitMole_Help_windows_Update(void * param)
{
	HitMole_Help * myself=(HitMole_Help *)param;
	gm_s32 px,py;
	#ifdef	GAME_240_320
	myself->picLib->FillRect(myself->picLib,9,288,20,20,GAME_ToRGB(102,51,0));
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
	if (getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))//�����˵�
	{		
		myself->textBox.curPage = 0;
		HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
	}
#ifdef GAME_240_320
	if(SCREEN_IsPointerDown())//�������
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();//���������Ļ��
		if(MyCdRectPoint(185,290,227,308,px,py))
		{
			myself->textBox.curPage = 0;
			HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
		}
		if(MyCdRectPoint(8,290,68,308,px,py))
		{
			if (myself->textBox.curPage==1)//�ı���ҳ
			{
			myself->textBox.curPage=0;
			}else
			myself->textBox.curPage=1;
			DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
		}
	}
#endif

}


