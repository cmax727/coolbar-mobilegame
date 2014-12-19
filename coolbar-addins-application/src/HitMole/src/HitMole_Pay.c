/**************************************************************************************************************************************************
*compay:daicom
*name:zhaoliangqi
*
**************************************************************************************************************************************************/
#include "HitMole_Pay.h"
#include "HitMole_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
static Manager manager;
void initHitMolePay(HitMole_Pay * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{	
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=HitMole_Pay_Windows_Render;
	myself->windows.UpdateCallBack=HitMole_Pay_Windows_Update;
	myself->picLib = picLib;
	myself->border = picLib->GetImage(picLib,"border.gif");
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,170);
	myself->textBox.SetDistance(&myself->textBox,20);
	
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,15,40,SCREEN_WIDTH-TEXT_SIZE*2,165);
	
#endif
	myself->textBox.SetText(&myself->textBox,"�������һ�Ȥζ������һ���������Ϸ,����Ϸ����������Ц�����ܹ��������ķ�Ӧ�ٶȸ����������֣������ʹ�ö���(2Ԫ/10��)��ᱦ(28�ᱦ/��)֧���������㲥��ʼ���ܷ��񣬷����򲻿۷ѡ��ͷ��绰400-877-3373");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
}

static void HitMolebillingOnceCB(VMBOOLEAN isSuccess)
{
	if(isSuccess)
	{
		//�ɹ�
		//�����ݲ�����
		HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
		
	}
	else
	{
	       //ʧ��      �˳�
		extVmSysManager->VmEnterWinClose();					
	}		
}

void HitMolePayRender(HitMole_Pay * myself)
{	
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
	
#ifdef GAME_240_320
	extOldGameManager->DrawString("�ʷ���ʾ",20,SCREEN_WIDTH/2-40,15,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);//���ư�������
	extOldGameManager->DrawString("��һҳ",25,TOUCH_X_RIGHT-30,TOUCH_Y_RIGHT,0xffff00);
#endif 
#ifdef GAME_176_220 
	extOldGameManager->DrawString("�ʷ���ʾ",25,SCREEN_WIDTH/2-40,10,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);//���ư�������
	extOldGameManager->DrawString("��һҳ",25,TOUCH_X_RIGHT-20,TOUCH_Y_LEFT,0xffff00);
	//extOldGameManager->DrawString("��һҳ",25,TOUCH_X_RIGHT-30,TOUCH_Y_RIGHT,0xffff00);
#endif
	extOldGameManager->DrawString("�㲥",25,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);

}
void HitMole_Pay_Windows_Render(void * param)
{
	HitMole_Pay * myself =(HitMole_Pay *)param;
	 HitMolePayRender(myself);
}

void HitMole_Pay_Windows_Update(void * param)
{
	gm_s16 px,py;
	HitMole_Pay * myself =(HitMole_Pay *)param;
	char enterStr[60] = {0};
	HitMolePayRender(myself);
	if(myself->textBox.curPage == 1)
		{
		
//			sprintf((char*)enterStr,"�㲥�������%d��",extVmBillingManager->BILLING_GetValidDayByAppId(NETAPP_APP_HITMOLE,NETAPP_BILLING_METHOD_ONCE_MONTH));
			#ifdef GAME_240_320
			manager.DrawString(enterStr,40,TOUCH_X_LEFT,SCREEN_HEIGHT-60,0xff0000);
			myself->picLib->FillRect(myself->picLib,TOUCH_X_RIGHT-30,288,65,22,GAME_ToRGB(36,16,121));
			extOldGameManager->DrawString("����",25,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT,0xffff00);
			#endif
			#ifdef GAME_176_220
			myself->picLib->FillRect(myself->picLib,107,196,60,20,GAME_ToRGB(36,16,121));
			extOldGameManager->DrawString("����",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
			#endif
		}
	if(extOldGameManager->IsKeyDown(MF_KEY_LEFTSOFT))
	{
//		extVmBillingManager->BILLING_Pay3(NETAPP_APP_HITMOLE,NETAPP_BILLING_METHOD_ONCE_MONTH,HitMolebillingOnceCB,1,FALSE);
	}
	if(extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT) && myself->textBox.curPage==1)
	{	
		myself->textBox.curPage = 0;
		HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
	}else if(extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT) && myself->textBox.curPage==0)
	{
		myself->textBox.curPage = 1;
	}
	if(SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
#ifdef GAME_240_320
		if(MyCdRectPoint(166,290,225,308,px,py))
		{
			if(myself->textBox.curPage == 1)
			{
				myself->textBox.curPage = 0;
				HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
			}else
			{
				myself->textBox.curPage = 1;
			}
			
		}
		if(MyCdRectPoint(10,288,49,310,px,py))
		{
//			extVmBillingManager->BILLING_Pay3(NETAPP_APP_HITMOLE,NETAPP_BILLING_METHOD_ONCE_MONTH,HitMolebillingOnceCB,1,FALSE);
		}
#endif

	}
}

