#include "RussBlock_PropShop.h"
#include "RussBlock_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"

#endif

gm_u8 flag_ShowBuy;
TextBox textBox_BuyProp;
gm_s16 selectIndex;

char * propString[3];

void	RussBlock_SMS_BuyProp(BOOLEAN isSucess);
void initRussBlockPropShop(RussBlock_PropShop * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	gm_s16 i;
	char * temp[3];
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->picLib=picLib;
	myself->windows.RenderCallBack=RussBlock_PropShop_Windows_Render;
	myself->windows.UpdateCallBack=RussBlock_PropShop_Windows_Update;
	flag_ShowBuy=false;
	myself->imgCmd=myself->picLib->GetImage(myself->picLib,"cmd.gif");
	myself->imgMenuBar=russBlockPicLib.GetImage(&russBlockPicLib,"menubar.gif");
	RussBlock_Loading_UpdateStep();
	myself->imgPropChoose=myself->picLib->GetImage(myself->picLib,"propchoose.gif");
	myself->imgPropBar=myself->picLib->GetImage(myself->picLib,"propbar.gif");
	RussBlock_Loading_UpdateStep();

	myself->imgUI[0]=myself->picLib->GetImage(myself->picLib,"help.gif");
	myself->imgUI[1]=myself->picLib->GetImage(myself->picLib,"cmd.gif");
	myself->imgUI[2]=myself->picLib->GetImage(myself->picLib,"bottom.gif");
	selectIndex=0;
	RussBlock_Loading_UpdateStep();


	{

		for (i=0;i<3;i++)
		{
			if (i==0)
				temp[0]=manager_my->formatString("   炸弹道具5个,信息费%d元",BILLING_GetPayNumByAppId(NETAPP_APP_RUSSBLOCK,NETAPP_BILLING_METHOD_ONCE));
			if(i==1)
				temp[1]=manager_my->formatString("   减速道具5个,信息费%d元",BILLING_GetPayNumByAppId(NETAPP_APP_RUSSBLOCK,NETAPP_BILLING_METHOD_ONCE));
			if(i==2)
				temp[2]=manager_my->formatString("   加时道具5个,信息费%d元",BILLING_GetPayNumByAppId(NETAPP_APP_RUSSBLOCK,NETAPP_BILLING_METHOD_ONCE));

			DF_Malloc((void **)&propString[i],strlen(temp[i])+1);
			memcpy(propString[i],temp[i],strlen(temp[i]));
			propString[strlen(temp[i])] = 0;
		}
#ifdef GAME_240_320
		initTextBox(&myself->textBox0,1024,30,59,SCREEN_WIDTH-3*TEXT_SIZE,200);
#endif
#ifdef GAME_176_220
		initTextBox(&myself->textBox0,1024,30,59-8,SCREEN_WIDTH-TEXT_SIZE*4,200);
#endif
		myself->textBox0.SetStyle(&myself->textBox0,TEXTBOX_ALIGN_LEFT);
		myself->textBox0.SetText(&myself->textBox0,propString[0]);
	}
	{
#ifdef GAME_240_320
		initTextBox(&myself->textBox1,1024,30,59+76,SCREEN_WIDTH-3*TEXT_SIZE,200);
#endif
#ifdef GAME_176_220
		initTextBox(&myself->textBox1,1024,30,52+14+31,SCREEN_WIDTH-TEXT_SIZE*4,200);
#endif
		myself->textBox1.SetStyle(&myself->textBox1,TEXTBOX_ALIGN_LEFT);
		myself->textBox1.SetText(&myself->textBox1,propString[1]);
	}
	{

#ifdef GAME_240_320
		initTextBox(&myself->textBox2,1024,30,55+76*2,SCREEN_WIDTH-3*TEXT_SIZE,200);
#endif
#ifdef GAME_176_220
		initTextBox(&myself->textBox2,1024,30,136+2,SCREEN_WIDTH-TEXT_SIZE*4,200);
#endif
		myself->textBox2.SetStyle(&myself->textBox2,TEXTBOX_ALIGN_LEFT);
		myself->textBox2.SetText(&myself->textBox2,propString[2]);
	}
	{
#ifdef GAME_240_320
		initTextBox(&textBox_BuyProp,1024,45,110,150,100);
#endif		
#ifdef GAME_176_220
		initTextBox(&textBox_BuyProp,1024,30,60,SCREEN_WIDTH-TEXT_SIZE*4,100);
#endif		
		textBox_BuyProp.SetStyle(&textBox_BuyProp,TEXTBOX_ALIGN_X_MIDDLE|TEXTBOX_ALIGN_Y_MIDDLE);
	}


	RussBlock_Loading_UpdateStep();
}

void RussBlock_PropShop_Windows_Render(void * param)
{
	RussBlock_PropShop * myself=(RussBlock_PropShop *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
#ifdef GAME_240_320
	RussBlock_MenuBar_Paint(myself->picLib,myself->imgMenuBar,MENUBARWIDTH*6,MENUBARHEIGHT*7,9+5);
	myself->textBox0.Render(&myself->textBox0,0xffffff);
	myself->textBox1.Render(&myself->textBox1,0xffffff);
	myself->textBox2.Render(&myself->textBox2,0xffffff);

	myself->picLib->DrawRegionEx(myself->picLib,myself->imgPropBar,28,52,0,0,25,25,true,0);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgPropBar,28,52+77,50,0,25,25,true,0);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgPropBar,28,47+77*2,25,0,25,25,true,0);


	myself->picLib->DrawRegionEx(myself->picLib,myself->imgUI[0],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgUI[0]))>>1,9+7+5,0,0,92,20,true,0);
	myself->picLib->DrawImage(myself->picLib,myself->imgUI[2],0,SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgUI[2]));
	
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgUI[1],206,301,0,39,25,13,true,0);// 返回
	if (!flag_ShowBuy)
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgUI[1],9,301,0,26,25,13,true,0);// 购买
	else
		myself->picLib->DrawRegionEx(myself->picLib,myself->imgUI[1],9,301,0,0,25,13,true,0);// 确定


	if (selectIndex==0)
	myself->picLib->DrawImageEx(myself->picLib,myself->imgPropChoose,25,49,true,0);
	else if (selectIndex==1)
	myself->picLib->DrawImageEx(myself->picLib,myself->imgPropChoose,25,126,true,0);
	else if (selectIndex==2)
	myself->picLib->DrawImageEx(myself->picLib,myself->imgPropChoose,25,198,true,0);

	if (flag_ShowBuy)
	{
		RussBlock_MenuBar_Paint(myself->picLib,myself->imgMenuBar,MENUBARWIDTH*6,MENUBARHEIGHT*4,83);
		textBox_BuyProp.Render(&textBox_BuyProp,0xffffff);
	}

#endif // GAME_240_320
#ifdef GAME_176_220
	RussBlock_MenuBar_Paint(myself->picLib,myself->imgMenuBar,MENUBARWIDTH*4,MENUBARHEIGHT*5,5);
	myself->textBox0.Render(&myself->textBox0,0xffffff);
	myself->textBox1.Render(&myself->textBox1,0xffffff);
	myself->textBox2.Render(&myself->textBox2,0xffffff);

	myself->picLib->DrawRegionEx(myself->picLib,myself->imgPropBar,28+3,52-8+1,36,0,18,18,true,0);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgPropBar,28+3,52+7+35,0,0,18,18,true,0);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgPropBar,28+3,52+7+75,18,0,18,18,true,0);


	myself->picLib->DrawRegionEx(myself->picLib,myself->imgUI[0],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgUI[0]))>>1,13,0,0,83,18,true,0);
	myself->picLib->DrawImage(myself->picLib,myself->imgUI[2],0,SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgUI[2]));

	myself->picLib->DrawRegionEx(myself->picLib,myself->imgUI[1],148,203,0,39,25,13,true,0);// 返回
	if (!flag_ShowBuy)
		myself->picLib->DrawRegionEx(myself->picLib,myself->imgUI[1],3,203,0,26,25,13,true,0);// 购买
	else
		myself->picLib->DrawRegionEx(myself->picLib,myself->imgUI[1],3,203,0,0,25,13,true,0);//确定


	if (selectIndex==0)
		myself->picLib->DrawImageEx(myself->picLib,myself->imgPropChoose,25+2,49-8,true,0);
	else if (selectIndex==1)
		myself->picLib->DrawImageEx(myself->picLib,myself->imgPropChoose,27,52+7+31,true,0);
	else if (selectIndex==2)
		myself->picLib->DrawImageEx(myself->picLib,myself->imgPropChoose,27,126+4,true,0);

	if (flag_ShowBuy)
	{
		RussBlock_MenuBar_Paint(myself->picLib,myself->imgMenuBar,MENUBARWIDTH*4,MENUBARHEIGHT*3,50);
		textBox_BuyProp.Render(&textBox_BuyProp,0xffffff);
	}

#endif 
}
void buySelect()
{
	char * str;
	if(!flag_ShowBuy)
	{
		if(selectIndex==0)
			str="炸弹";
		else if(selectIndex==1)
			str="减速";
		else if(selectIndex==2)
			str="加时";
		textBox_BuyProp.SetText(&textBox_BuyProp,manager_my->formatString("购买%s道具5个,信息费%d元",str,BILLING_GetPayNumByAppId(NETAPP_APP_RUSSBLOCK,NETAPP_BILLING_METHOD_ONCE)));
		flag_ShowBuy=true;
	}
	else
	{
		BILLING_Pay(NETAPP_APP_RUSSBLOCK,NETAPP_BILLING_METHOD_ONCE,RussBlock_SMS_BuyProp);

	}
}

void RussBlock_PropShop_Windows_Update(void * param)
{
	RussBlock_PropShop * myself=(RussBlock_PropShop *)param;
	Rect ur;
	gm_s32 px,py;
#ifdef GAME_240_320
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
#endif
#ifdef GAME_176_220
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
#endif
	if (!flag_ShowBuy&& getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2))
	{
		selectIndex--;
		selectIndex+=2;
		selectIndex=(selectIndex+1)%3;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if (!flag_ShowBuy&& getManagerPtr()->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))
	{
		selectIndex++;
		selectIndex+=2;
		selectIndex=(selectIndex+1)%3;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if (getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))
	{
		if (!flag_ShowBuy)
		RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_MENU);
		else flag_ShowBuy=false;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);

		DF_Free((void**)&propString[0]);
		DF_Free((void**)&propString[1]);
		DF_Free((void**)&propString[2]);		
	}
	else if (getManagerPtr()->IsKeyDown(MF_KEY_LEFTSOFT |MF_KEY_MID))/*购买*/
	{
		buySelect();
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);

	}

	if(SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();

		if(CdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))

			{
				if (!flag_ShowBuy)
					RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_MENU);
				else flag_ShowBuy=false;
				DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
			}

			if(CdRectPoint(TOUCH_X_LEFT,TOUCH_Y_LEFT,TOUCH_X1_LEFT,TOUCH_Y1_LEFT,px,py))

			{
				buySelect();
				DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);

			}
#ifdef GAME_240_320
			if(!flag_ShowBuy&& CdRectPoint(22,50,44,72,px,py))
#endif
#ifdef GAME_176_220
			if(!flag_ShowBuy&& CdRectPoint(28,43,50,63,px,py))
#endif
			{
				if (selectIndex==0)
				{
					buySelect();
				}
				else selectIndex=0;
				DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);

			}

#ifdef GAME_240_320
			else if (!flag_ShowBuy&& CdRectPoint(22,122,44,146,px,py))
#endif
#ifdef GAME_176_220
			else if (!flag_ShowBuy&& CdRectPoint(29,93,49,112,px,py))
#endif
			{
				if (selectIndex==1)
				{
					buySelect();
				}
				else selectIndex=1;
				DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);

			}
#ifdef GAME_240_320
			else if (!flag_ShowBuy&&CdRectPoint(22,192,44,216,px,py))
#endif
#ifdef GAME_176_220
			else if ( !flag_ShowBuy&& CdRectPoint(30,133,48,151,px,py))
#endif
			{
				if (selectIndex==2)
				{
					buySelect();
				}
				else selectIndex=2;
				DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);

			}
	}
}

void	RussBlock_SMS_BuyProp(BOOLEAN isSucess)
{
	gm_s16 i;
	if(isSucess)
	{

		russBlockProp[selectIndex]+=5;
		flag_ShowBuy=false;
		russBlockRecord.pointer = 0;
		for (i=0;i<3;i++)
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_PROP,russBlockProp[i]);
		gm_TRACE("购买了道具 %d 。目前个数= %d \n",selectIndex,russBlockProp[selectIndex]);
	}
	else
	{
		textBox_BuyProp.SetText(&textBox_BuyProp,"购买失败了!");
	}
}