#include "MemoryBox_Help.h"
#include "MemoryBox_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//��ʹ��������������Ϣ������ͼƬ������
void initMemoryBoxHelp(MemoryBox_Help* myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=MemoryBox_Help_Windows_Render;//��������
	myself->windows.UpdateCallBack=MemoryBox_Help_windows_Update;//��������
	myself->picLib=picLib;
	//ʹ���ı��༭����������
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,200);
	myself->textBox.SetDistance(&myself->textBox,20);
	myself->textBox.SetText(&myself->textBox,"    ����Ϸ����9��,ÿ���ۼ�55���ʱ��,�涨ʱ�����ҳ�����,��ͬ��ͼ����������,��������Ʒ��򣬻������ּ�2��8��4��6�ֱ�����ϡ��¡������ƶ�,ȷ������5���㿪ѡ��Ŀ�.\n����Ϸ����֧��(2Ԫ/10��)��ᱦ֧��(28�ᱦ/��)");
	
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,16,18,SCREEN_WIDTH-TEXT_SIZE*2,185);
	myself->textBox.SetText(&myself->textBox,"    ����Ϸ����9��,ÿ���ۼ�55���ʱ��,�涨ʱ�����ҳ�����,��ͬ��ͼ����������,��������Ʒ��򣬻������ּ�2��8��4��6�ֱ�����ϡ��¡������ƶ�,ȷ������5���㿪ѡ��Ŀ�.\n����Ϸ����֧��(2Ԫ/10��)��ᱦ֧��(28�ᱦ/��)");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
#endif
	myself->imgback = picLib->GetImage(picLib,"bei.gif");
	MemoryBox_Loading_UpdateStep();
	
}
//���ư����н���
void MemoryBox_Help_Windows_Render(void * param)
{
	MemoryBox_Help* myself=(MemoryBox_Help *)param;
	myself->picLib->DrawFullScreen(myself->picLib,myself->imgback);
#ifdef GAME_240_320
	myself->picLib->FillRect(myself->picLib,20,50,200,250,GAME_ToRGB(102,51,0));
	myself->textBox.Render(&myself->textBox,0xffff00);//���ư�������
#endif 
#ifdef GAME_176_220 
	myself->textBox.Render(&myself->textBox,0xffff00);//���ư�������
	extOldGameManager->DrawString("�����¼���ҳ",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
#endif
	extOldGameManager->DrawString("����",25,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT+10,0xffff00);
}
//�������������н���
void MemoryBox_Help_windows_Update(void * param)
{
	MemoryBox_Help * myself=(MemoryBox_Help *)param;
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
		MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
	}
#ifdef GAME_240_320
	if(SCREEN_IsPointerDown())//�������
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();//���������Ļ��

		if(MBCdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
		{
			myself->textBox.curPage = 0;
			MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
		}
	}
#endif
}

