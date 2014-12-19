#include "RussBlock_Screen.h"
#include "coolbar_GameUtil.h"
#include "coolbar_TextBox.h"
#include "DF_Util.h"
#include "coolbar_TextBox.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif


#ifdef GAME_240_320
#define RUSSBLOCK_INGAME_MENU_PX 74+15+8
#define RUSSBLOCK_INGAME_MENU_PY 100
#endif
#ifdef GAME_176_220
#define RUSSBLOCK_INGAME_MENU_PX 74+15+8-32
#define RUSSBLOCK_INGAME_MENU_PY 60
#endif

#define RUSSBLOCK_INGAME_MENU_STATE_NONE		0   //初始游戏菜单状态
#define RUSSBLOCK_INGAME_MENU_STATE_HELP        1   /*帮助*/

#define RUSSBLOCK_SHOWGIRL_STATE_HINT 0 
#define RUSSBLOCK_SHOWGIRL_STATE_SHOW 1	 /*正式显示状态*/

extern void RussBlock_InGame_LoadResource();
extern void RussBlock_InGame_Init();
extern void RussBlock_InGame_Destory();
extern void RussBlock_InGame_Logic();
extern void RussBlock_InGame_Render(tGraphics *g);
extern void RussBlock_InGame_Pause();
extern void RussBlock_InGame_Resume();

void RussBlockIngameMenuUpdate();
void RussBlockInGameMenuRender();
void RussBlockIngameDoSelectMenu();
void RussBlockInGameShowGirlHintRender(DF_PictureLibrary * picLib);
void RussBlock_Score_Paint();
void updateHighScore();
void updateGameData();
void InGame_Help_Render();
void InGame_Menu_Render();
void RussBlock_SMS_BuyBoom(BOOLEAN isSucess);
void RussBlock_SMS_BuyTime(BOOLEAN isSucess);
void RussBlock_SMS_BuySlowSpeed(BOOLEAN isSucess);
DF_Windows russBlockGame;//游戏主窗口，虚对象
TextBox russBlockTextBox;
RussBlockUi russBlockUi;
DF_PictureLibrary russBlockPicLib;//图片库对象
RussBlock_Map russBlockMap;


TextBox textBox;
TextBox textBox_Buy;
gm_s16 russBlockGameMenuShow; 
gm_s16 imgIngameMenu[3];
gm_s16 imgBottom;
gm_s16 imgGameOver;
gm_s16 imgHelp;
static gm_s16 imgMenuBar;
gm_s16 page=0;
gm_s8 russBlockMenuState;
gm_s16 russBlockSelectMenu;
gm_s8 russBlockShowGirlState;

gm_u8 flagUpdateRecord=false;
gm_u8 flag_GirlShow_Notify=false;
gm_u8 flag_GirlShow=false;    
gm_u8 flag_GameOver=false;
gm_s16 russBlockGirlGrade;   
gm_s16 imgMnTy;              
gm_s8  russBlockGameTime; /*游戏时间*/
gm_s32 russBlockProp[3];

gm_s16 w=5,timer_showgirl=0;
gm_s16 russBlockInGameState;


tScreen RussBlock_Screen_InGame =
{
	RussBlock_InGame_Init,
	RussBlock_InGame_Destory,
	RussBlock_InGame_Logic,
	RussBlock_InGame_Render,
	RussBlock_InGame_Pause,
	RussBlock_InGame_Resume,
	RussBlock_InGame_LoadResource,
};

void RussBlock_InGame_Init()
{
	w=5;
	timer_showgirl=0;
	
}
void RussBlock_InGame_Destory()//释放图片
{
	russBlockPicLib.Release(&russBlockPicLib);
	//showMemoryUse();
}
//游戏中按键处理区域
void RussBlock_InGame_Logic()
{
	gm_s32 i=0,px,py;
	
	switch (russBlockInGameState)//当游戏状态在某个界面下
	{
	case RUSSBLOCK_INGAME_MAINSTATE_PLAYING:
		if(!flag_GameOver)
		russBlockGame.DF_Update(&russBlockGame);
		russBlockUi.windows.DF_Update(&russBlockUi.windows);
		if (flag_GirlShow)
		{
			russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_MOVING;
			russBlockShowGirlState=RUSSBLOCK_SHOWGIRL_STATE_HINT;
		}
		break;
	case RUSSBLOCK_INGAME_MAINSTATE_GAMEMENU:
		RussBlockIngameMenuUpdate();
		break;
	case RUSSBLOCK_INGAME_MAINSTATE_MOVING:
		switch (russBlockShowGirlState)
		{
		case RUSSBLOCK_SHOWGIRL_STATE_HINT:
			break;
		case RUSSBLOCK_SHOWGIRL_STATE_SHOW:
			if (getManagerPtr()->IsKeyDown(MF_KEY_ANY) ||SCREEN_IsPointerDown())
			{
				russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_PLAYING;
				flag_GirlShow=false;
			}
			break;
		}
		break;
	case RUSSBLOCK_INGAME_MAINSTATE_SCORE:
		if(!flagUpdateRecord)
		{
			flagUpdateRecord=true;
			updateHighScore();
			updateGameData();
		}
		if (getManagerPtr()->IsKeyDown(MF_KEY_ANY) ||SCREEN_IsPointerDown() )
		{
			russBlockTitleState = RUSSBLOCK_TITLE_STATE_MENU;
			russBlockTitleState =1;
			RussBlock_Screen_Next = &RussBlock_Screen_Title;
			russBlockLoadingStep = 0;
			russBlockLoadingStepTotal = 8;
			flagUpdateRecord=false;
			SCREEN_ChangeScreen(&RussBlock_Screen_Loading);
		}
		break;
	}
}
//游戏中绘制区域
void RussBlock_InGame_Render(tGraphics *g)
{
	switch (russBlockInGameState)//根据游戏中状态做相应绘制
	{
	case RUSSBLOCK_INGAME_MAINSTATE_PLAYING:
		russBlockGame.DF_Render(&russBlockGame);//绘制父窗口以及所关联所有窗口
		DF_SendMessage(&russBlockMap.windows,DF_WINDOWS_MSG_REPAINTALL,&russBlockMap.windows.DF_Windows_Rect);

		russBlockUi.windows.DF_Render(&russBlockUi.windows);
		DF_SendMessage(&russBlockUi.windows,DF_WINDOWS_MSG_REPAINTALL,&russBlockUi.windows.DF_Windows_Rect);
		if (flag_GameOver)//游戏结束
		{
			russBlockPicLib.DrawImageEx(&russBlockPicLib,imgGameOver,(SCREEN_WIDTH-russBlockPicLib.GetImageWidth(&russBlockPicLib,imgGameOver))>>1,(SCREEN_HEIGHT-russBlockPicLib.GetImageHeight(&russBlockPicLib,imgGameOver))>>1,true,0);
		if (timer_showgirl++>20)
		{
			timer_showgirl=0;
			russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_SCORE;
		}
		}
		break;
	case RUSSBLOCK_INGAME_MAINSTATE_SCORE:   /*积分显示界面*/
		russBlockGame.DF_Render(&russBlockGame);//绘制父窗口以及所关联所有窗口
		DF_SendMessage(&russBlockMap.windows,DF_WINDOWS_MSG_REPAINTALL,&russBlockMap.windows.DF_Windows_Rect);
		russBlockUi.windows.DF_Render(&russBlockUi.windows);
		DF_SendMessage(&russBlockUi.windows,DF_WINDOWS_MSG_REPAINTALL,&russBlockUi.windows.DF_Windows_Rect);
#ifdef GAME_240_320
		russBlockPicLib.DrawImage(&russBlockPicLib,imgBottom,0,SCREEN_HEIGHT-30);
#endif
#ifdef GAME_176_220
		russBlockPicLib.DrawImage(&russBlockPicLib,imgBottom,0,SCREEN_HEIGHT-22);
#endif
		RussBlock_Score_Paint();
		break;
	case RUSSBLOCK_INGAME_MAINSTATE_GAMEMENU:
		russBlockGame.DF_Render(&russBlockGame);//绘制父窗口以及所关联所有窗口
		DF_SendMessage(&russBlockMap.windows,DF_WINDOWS_MSG_REPAINTALL,&russBlockMap.windows.DF_Windows_Rect);
		russBlockUi.windows.DF_Render(&russBlockUi.windows);
		DF_SendMessage(&russBlockUi.windows,DF_WINDOWS_MSG_REPAINTALL,&russBlockUi.windows.DF_Windows_Rect);
#ifdef GAME_240_320
		russBlockPicLib.DrawImage(&russBlockPicLib,imgBottom,0,SCREEN_HEIGHT-30);
#endif
#ifdef GAME_176_220
		russBlockPicLib.DrawImage(&russBlockPicLib,imgBottom,0,SCREEN_HEIGHT-22);
#endif
		
		RussBlockInGameMenuRender();
		break;
	case RUSSBLOCK_INGAME_MAINSTATE_MOVING:			/*美女动画*/	
		switch (russBlockShowGirlState)
		{
		case RUSSBLOCK_SHOWGIRL_STATE_HINT:
			RussBlockInGameShowGirlHintRender(&russBlockPicLib);
			break;
		case RUSSBLOCK_SHOWGIRL_STATE_SHOW:
			flag_GirlShow=false;
			russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_PLAYING;		
		}
		break;
	}
	getManagerPtr()->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	
}
void RussBlock_InGame_Pause()
{

}
void RussBlock_InGame_Resume()
{
	DF_SendMessage(&russBlockMap.windows,DF_WINDOWS_MSG_INVALITE,&russBlockMap.windows.DF_Windows_Rect);
	DF_SendMessage(&russBlockUi.windows,DF_WINDOWS_MSG_INVALITE,&russBlockUi.windows.DF_Windows_Rect);
}
//初使化游戏中数据和资源加载
void RussBlock_InGame_LoadResource()
{
	Rect ur;	//初始化屏幕矩形
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;

#ifdef GAME_176_220
	ur.w = SCREEN_WIDTH;
	ur.y = 0;
	ur.h = SCREEN_HEIGHT;
#endif	
	initDFPictureLibrary(&russBlockPicLib,48);//初使化图片库
	RussBlock_Loading_UpdateStep();

	//初始化精灵模板库对象
	//.......暂略
	//初始话主窗口
	initDFWindows(&russBlockGame,ur,0,0,1);
	initRussBlockMap(&russBlockMap,ur,&russBlockPicLib,10);
	russBlockGame.DF_AttachWindows(&russBlockGame,&russBlockMap.windows,DF_WINDOWS_CREATE_TYPE_CHILD);
	RussBlock_Loading_UpdateStep();

	page=0;
#ifdef GAME_240_320
	initTextBox(&textBox,2*1024,20,50,SCREEN_WIDTH-40,200);
	textBox.SetDistance(&textBox,20);
	textBox.SetText(&textBox,RussBlock_TextResource_Help);
#endif // GAME_240_320
#ifdef GAME_176_220
	initTextBox(&textBox,2*1024,TEXT_SIZE*2,40,SCREEN_WIDTH-TEXT_SIZE*4,150);
	textBox.SetDistance(&textBox,20);
	textBox.SetText(&textBox,RussBlock_TextResource_Help);
#endif // GAME_240_320
	textBox.SetStyle(&textBox,TEXTBOX_ALIGN_LEFT);

#ifdef GAME_240_320
	initTextBox(&textBox_Buy,1024,45,120,170,100);
#endif
#ifdef GAME_176_220
	initTextBox(&textBox_Buy,1024,2*TEXT_SIZE,80,SCREEN_WIDTH-TEXT_SIZE*4,100);
#endif
	textBox_Buy.SetStyle(&textBox_Buy,TEXTBOX_ALIGN_LEFT);
	//加载些游戏图片资源
	imgIngameMenu[0]=russBlockPicLib.GetImage(&russBlockPicLib,"ingamemenu.gif");
	imgIngameMenu[1]=russBlockPicLib.GetImage(&russBlockPicLib,"cmd.gif");
	RussBlock_Loading_UpdateStep();
	imgMenuBar=russBlockPicLib.GetImage(&russBlockPicLib,"menubar.gif");
	imgBottom=russBlockPicLib.GetImage(&russBlockPicLib,"bottom.gif");
	imgMnTy=russBlockPicLib.GetImage(&russBlockPicLib,"mnty.gif");
	RussBlock_Loading_UpdateStep();
	imgGameOver=russBlockPicLib.GetImage(&russBlockPicLib,"gameover.gif");
	imgHelp=russBlockPicLib.GetImage(&russBlockPicLib,"help.gif");
	russBlockGameMenuShow=0;
	russBlockSelectMenu=0;
	flag_GirlShow=false;
	flag_GameOver=false;
	flagUpdateRecord=false;
	russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_PLAYING;
	initRussBlockUi(&russBlockUi,ur,&russBlockPicLib,0,0);

}

/*游戏中菜单处理*/
void RussBlockIngameMenuUpdate()
{
	gm_s32 px,py,i;
	switch (russBlockMenuState)
	{
	case RUSSBLOCK_INGAME_MENU_STATE_NONE:
		{
			if(getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2))
			{
				russBlockSelectMenu--;
				russBlockSelectMenu+=2;
				russBlockSelectMenu=(russBlockSelectMenu+1)%3;
			} 
			else if(getManagerPtr()->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))
			{
				russBlockSelectMenu++;
				russBlockSelectMenu+=2;
				russBlockSelectMenu=(russBlockSelectMenu+1)%3;
			}
			else if(getManagerPtr()->IsKeyDown(MF_KEY_5|MF_KEY_MID|MF_KEY_LEFTSOFT))
			{
				RussBlockIngameDoSelectMenu();
			}
			else if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))  //返回游戏中
			{
				russBlockGameMenuShow=0;
				russBlockMenuState=RUSSBLOCK_INGAME_MENU_STATE_NONE;
				russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_PLAYING;
			}
			if(SCREEN_IsPointerDown())//触摸功能操控菜单
			{
				px = SCREEN_GetPointerX();
				py = SCREEN_GetPointerY();
				if(CdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
					{
						russBlockGameMenuShow=0;
						russBlockMenuState=RUSSBLOCK_INGAME_MENU_STATE_NONE;
						russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_PLAYING;
					}
					if(CdRectPoint(TOUCH_X_LEFT,TOUCH_Y_LEFT,TOUCH_X1_LEFT,TOUCH_Y1_LEFT,px,py))
						RussBlockIngameDoSelectMenu();

						for (i=0;i<3;i++)
						{
							//RUSSBLOCK_INGAME_MENU_PX-32,RUSSBLOCK_INGAME_MENU_PY+30*i-40,
							if(CdRectPoint(RUSSBLOCK_INGAME_MENU_PX,RUSSBLOCK_INGAME_MENU_PY+30*i,RUSSBLOCK_INGAME_MENU_PX+50,RUSSBLOCK_INGAME_MENU_PY+30*i+13,px,py))

								{
									if (i==russBlockSelectMenu)
									{
										RussBlockIngameDoSelectMenu();
									}
									else
										russBlockSelectMenu=i;
								}
						}

			}
		}
		break;
	case RUSSBLOCK_INGAME_MENU_STATE_HELP://游戏中帮助

		if (getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))
		{
			page=0;
			textBox.curPage = 0;
            russBlockMenuState=RUSSBLOCK_INGAME_MENU_STATE_NONE;
		}

			if (getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2))
			{
				if (page)
				{
					page--;
					textBox.curPage--;
				}	
			}
			else if (getManagerPtr()->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))
			{
				if (page<textBox.page-1)
				{
					page++;
					textBox.curPage++;
				}
			}
			if(SCREEN_IsPointerDown())//触摸操作帮助
			{
				px = SCREEN_GetPointerX();
				py = SCREEN_GetPointerY();
				if(CdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))

					{
						page=0;
						textBox.curPage = 0;
						russBlockMenuState=RUSSBLOCK_INGAME_MENU_STATE_NONE;

					}

			}		
		break;
	}
}

void RussBlockInGameMenuRender()
{
	switch (russBlockMenuState)
	{
	case RUSSBLOCK_INGAME_MENU_STATE_HELP:   InGame_Help_Render(); 	break;
	case RUSSBLOCK_INGAME_MENU_STATE_NONE:   InGame_Menu_Render();  break;
	}
}
static count;

extern void RussBlock_DrawMiddleString(gm_u8 * str,gm_s32 x,gm_s32 y,gm_u32 color);

void RussBlock_Score_Paint()//绘制得分
{
	gm_s8 i,m=0;
	char * str="按任意键继续";
	char * str_score[4]={"消去行数： ","连击数：   ","美女完成度：","游戏得分： "};
	if (russBlockUi.level<2) m=0;
	else if (1<russBlockUi.level&& russBlockUi.level<4) m=25;    /*2级*/
	else if (3<russBlockUi.level&& russBlockUi.level<7) m=50;	 /*4级*/
	else if (6<russBlockUi.level&& russBlockUi.level<10) m=75;   /*7级*/
	else if (russBlockUi.level>=10)  m=100;	 /*10级*/
#ifdef GAME_240_320
	RussBlock_MenuBar_Paint(&russBlockPicLib,imgMenuBar,5*MENUBARWIDTH,6*MENUBARHEIGHT,55);
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgHelp,77,63,0,80,92,20,TRUE,0);
	for (i=0;i<4;i++)
	{
		getManagerPtr()->DrawString(str_score[i],18,40,113+30*i,0xffffff);
		
	}
	getManagerPtr()->DrawString(manager_my->formatString("%d",russBlockUi.clearedlayer),6,140+15,113,0xffffff);
	getManagerPtr()->DrawString(manager_my->formatString("%d",russBlockUi.hitNum),6,140+15,113+30,0xffffff);

	getManagerPtr()->DrawString(manager_my->formatString("%d",m),6,140+15,113+60,0xffffff);
	getManagerPtr()->DrawString(" %",6,136+40,113+60,0xffffff);
	getManagerPtr()->DrawString(manager_my->formatString("%d",russBlockUi.score),6,140+15,113+90,0xffffff);
	if (count++%10>5)
		RussBlock_DrawMiddleString((gm_u8*)str,SCREEN_WIDTH>>1,305,0xffffff);
#endif // GAME_240_320

#ifdef GAME_176_220
	RussBlock_MenuBar_Paint(&russBlockPicLib,imgMenuBar,4*MENUBARWIDTH,5*MENUBARHEIGHT,55-45);
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgHelp,47,63-45,0,72,83,18,TRUE,0);
	for (i=0;i<4;i++)
	{
		getManagerPtr()->DrawString(str_score[i],strlen(str_score[i]),30,60+30*i,0xffffff);

	}
	getManagerPtr()->DrawString(manager_my->formatString("%d",russBlockUi.clearedlayer),strlen(manager_my->formatString("%d",russBlockUi.clearedlayer)),100,61,0xffffff);
	getManagerPtr()->DrawString(manager_my->formatString("%d",russBlockUi.hitNum),strlen(manager_my->formatString("%d",russBlockUi.hitNum)),120,61+30,0xffffff);

	getManagerPtr()->DrawString(manager_my->formatString("%d",m),strlen(manager_my->formatString("%d",m)),120,61+60,0xffffff);
	getManagerPtr()->DrawString(" %",2,135,61+60,0xffffff);
	getManagerPtr()->DrawString(manager_my->formatString("%d",russBlockUi.score),strlen(manager_my->formatString("%d",russBlockUi.score)),100,61+90,0xffffff);
	if (count++%10>5)
		RussBlock_DrawMiddleString((gm_u8*)str,SCREEN_WIDTH>>1,209,0xffffff);
#endif 
}
void saveGame()
{
	russBlockRecord.pointer = 0;
	
}


void RussBlockIngameDoSelectMenu()//游戏中菜单操作
{
	Rect ur;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
	switch (russBlockSelectMenu)
	{
	case 0:
		russBlockGameMenuShow=0;
		russBlockMenuState=RUSSBLOCK_INGAME_MENU_STATE_NONE;
		russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_PLAYING;
		break;
	case 1:    //help 
		russBlockMenuState=RUSSBLOCK_INGAME_MENU_STATE_HELP;
		page=0;
		//textBox.SetText(&textBox,RussBlock_TextResource_Help[page]);
		textBox.SetText(&textBox,RussBlock_TextResource_Help);
		break;
	case 2:     //quit
		russBlockTitleState = RUSSBLOCK_TITLE_STATE_MENU;
		russBlockTitleState =1;
		RussBlock_Screen_Next = &RussBlock_Screen_Title;
		russBlockLoadingStep = 0;
		russBlockLoadingStepTotal = 8;
		SCREEN_ChangeScreen(&RussBlock_Screen_Loading);
		updateHighScore();
		updateGameData();
		break;
	}
}

void RussBlockInGameShowGirlHintRender(DF_PictureLibrary * picLib)
{
	gm_s16 i;
	gm_s16 x=0,y=0,h=10,y1;
	y=SCREEN_HEIGHT/2-3*h;
	y1=SCREEN_HEIGHT/2;
	for (i=0;i<3;i++)
	{
		picLib->FillRect(picLib,0,y,w,h,GAME_ToRGB(255,0,0));
		picLib->FillRect(picLib,0,y+h,w,h,GAME_ToRGB(255,0,255));
		picLib->FillRect(picLib,0,y+h*2,w,h,GAME_ToRGB(0,255,255));
	}
	for (i=0;i<3;i++)
	{
		picLib->FillRect(picLib,SCREEN_WIDTH-w,y1,w,h,GAME_ToRGB(0,255,255));
		picLib->FillRect(picLib,SCREEN_WIDTH-w,y1+h,w,h,GAME_ToRGB(0,255,0));
		picLib->FillRect(picLib,SCREEN_WIDTH-w,y1+h*2,w,h,GAME_ToRGB(255,255,0));
	}
	if (w<SCREEN_WIDTH)
	{
		w*=2;
		if (w>SCREEN_WIDTH)
		{
			w=SCREEN_WIDTH;
		}
	}
	else
	{
		for (i=0;i<3;i++)
		{
			picLib->FillRect(picLib,0,y,SCREEN_WIDTH,h,GAME_ToRGB(255,0,0));
			picLib->FillRect(picLib,0,y+h,SCREEN_WIDTH,h,GAME_ToRGB(255,0,255));
			picLib->FillRect(picLib,0,y+h*2,SCREEN_WIDTH,h,GAME_ToRGB(0,0,255));
		}
		for (i=0;i<3;i++)
		{
			picLib->FillRect(picLib,SCREEN_WIDTH-w,y1,SCREEN_WIDTH,h,GAME_ToRGB(0,255,255));
			picLib->FillRect(picLib,SCREEN_WIDTH-w,y1+h,SCREEN_WIDTH,h,GAME_ToRGB(0,255,0));
			picLib->FillRect(picLib,SCREEN_WIDTH-w,y1+h*2,SCREEN_WIDTH,h,GAME_ToRGB(255,255,0));
		}
		picLib->DrawImageEx(picLib,imgMnTy,(SCREEN_WIDTH-picLib->GetImageWidth(picLib,imgMnTy))>>1,(SCREEN_HEIGHT-picLib->GetImageHeight(picLib,imgMnTy))>>1,true,0);
		timer_showgirl++;
		if (timer_showgirl>15)
		{
			russBlockShowGirlState=RUSSBLOCK_SHOWGIRL_STATE_SHOW;
			timer_showgirl=0;
			w=5;
		}
	}
	
}

void updateGameData()//游戏中死亡后记录更新
{
	gm_s16 m,j;
	if (flag_GameOver)//游戏中死亡
	{
		russBlockRecord.pointer=0;
		for (j=0;j<VERTICAL_BOXS;j++)
		{
			for (m=0;m<HORIZONTAL_BOXS;m++)
			{
				russBlockGameGrid[russBlockGameType][j][m]=0;
				if (russBlockGameType==GAMETYPE_NOMAL)
				{
					russBlockRecord.WriteByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_NOMAL,0);
				}
				else
					russBlockRecord.WriteByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_TIME,0);
			}	
		}
		russBlockRecord.pointer=0;
		for (j=0;j<4;j++)
		{
			russBlockGameData[russBlockGameType][j]=0;
			if (russBlockGameType==GAMETYPE_NOMAL)
			{
				if (j==0)
				{
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,1);
				}
				else
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,0);
			}

			else
			{
				if (j==0)
				{
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,1);
				}
				else
				russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,0);
			}
		}
		if (russBlockGameType!=GAMETYPE_NOMAL)
		{
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,60);
			russBlockGameTime=60;
		}
				russBlockGameData[1][0]=1;
		russBlockGameData[0][0]=1;
	}

	else   //从菜单退出
	{
		copyGrid();
		russBlockRecord.pointer=0;
		for (j=0;j<VERTICAL_BOXS;j++)
		{
			for (m=0;m<HORIZONTAL_BOXS;m++)
				if (russBlockGameType==GAMETYPE_NOMAL)
				{
					russBlockRecord.WriteByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_NOMAL,russBlockGameGrid[russBlockGameType][j][m]);
				}
				else
					russBlockRecord.WriteByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_TIME,russBlockGameGrid[russBlockGameType][j][m]);

		}
		
		russBlockRecord.pointer=0;
		//for (j=0;j<4;j++)
		{
			if (russBlockGameType==GAMETYPE_NOMAL)
			{
				russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,russBlockUi.level);
				
				russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,russBlockUi.score);
	
				russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,russBlockUi.clearedlayer);
	
				russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,russBlockSpeed);
			

			}
			else
			{
				//russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,0);
				russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,russBlockUi.level);
				russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,russBlockUi.score);
				russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,russBlockUi.clearedlayer);
				russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,russBlockSpeed);
				russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,russBlockGameTime);
			}
			russBlockGameData[russBlockGameType][0]=russBlockUi.level;
			russBlockGameData[russBlockGameType][1]=russBlockUi.score;
			russBlockGameData[russBlockGameType][2]=russBlockUi.clearedlayer;
			russBlockGameData[russBlockGameType][3]=russBlockSpeed;
		}
	}
}

void updateProp()  //更新道具到记录
{
	gm_s16 j;
	russBlockRecord.pointer = 0;
	for (j=0;j<3;j++)			/*更新道具*/
	{
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_PROP,russBlockProp[j]);
	}
}


void updateHighScore()//更新排行榜分数
{
	gm_s16 i=0,j=0,m=0,n=0;
	russBlockRecord.pointer = 0;
	if (russBlockGameType==GAMETYPE_NOMAL)
	{

		for (;i<12;i+=2)
		{
			if (russBlockHighScoreValue_CommonModel[i]<=russBlockUi.score)
			{
				break;
			}
		}
		if (i<12)
		{
			for (n=12-2;n>i;n-=2)
			{
				russBlockHighScoreValue_CommonModel[n]=russBlockHighScoreValue_CommonModel[n-2];
				russBlockHighScoreValue_CommonModel[n+1]=russBlockHighScoreValue_CommonModel[n-1];
			}
			russBlockHighScoreValue_CommonModel[i]=russBlockUi.score;
			russBlockHighScoreValue_CommonModel[i+1]=russBlockUi.clearedlayer;
		}

		for (j=0;j<12;j++)
		{
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_COMMONMODEL,russBlockHighScoreValue_CommonModel[j]);//
		}
	}
	else 
	{
		for (;i<12;i+=2)
		{
			if (russBlockHighScoreValue_TimeModel[i]<=russBlockUi.score)
			{
				break;
			}
		}
		if (i<12)
		{
			for (n=12-2;n>i;n-=2)
			{
				russBlockHighScoreValue_TimeModel[n]=russBlockHighScoreValue_TimeModel[n-2];
				russBlockHighScoreValue_TimeModel[n+1]=russBlockHighScoreValue_TimeModel[n-1];
			}
			russBlockHighScoreValue_TimeModel[i]=russBlockUi.score;
			russBlockHighScoreValue_TimeModel[i+1]=russBlockUi.clearedlayer;
		}

		for (j=0;j<12;j++)
		{
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_TIMEMODEL,russBlockHighScoreValue_TimeModel[j]);//
		}
	}
	russBlockRecord.pointer = 0;
	for (j=0;j<3;j++)			/*更新道具*/
	{
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_PROP,russBlockProp[j]);
	}
}
//游戏中帮助绘制
void InGame_Help_Render()
{
	
#ifdef GAME_240_320
	RussBlock_MenuBar_Paint(&russBlockPicLib,imgMenuBar,6*MENUBARWIDTH,7*MENUBARHEIGHT,14);
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgHelp,(SCREEN_WIDTH-russBlockPicLib.GetImageWidth(&russBlockPicLib,imgHelp))>>1,9+7+5,0,40,92,20,true,0);
	textBox.Render(&textBox,0xffffff);
	getManagerPtr()->DrawString("按上下键翻页",20,64,298,0xffffff);
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgIngameMenu[1],206,301,0,39,25,13,true,0);//返回
#endif 
#ifdef GAME_176_220
	RussBlock_MenuBar_Paint(&russBlockPicLib,imgMenuBar,4*MENUBARWIDTH,5*MENUBARHEIGHT,5);
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgHelp,(SCREEN_WIDTH-russBlockPicLib.GetImageWidth(&russBlockPicLib,imgHelp))>>1,9+4,0,36,83,18,true,0);
	textBox.Render(&textBox,0xffffff);
	getManagerPtr()->DrawString("按上下键翻页",12,45 ,202,0xffffff);
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgIngameMenu[1],148,203,0,39,25,13,true,0);//返回
#endif 
}
void InGame_Menu_Render()//游戏中菜单绘制
{
	gm_s16 i;
#ifdef GAME_240_320
	RussBlock_MenuBar_Paint(&russBlockPicLib,imgMenuBar,3*MENUBARWIDTH,4*MENUBARHEIGHT,57);
	for (i=0;i<3;i++)
	{
		russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgIngameMenu[0],RUSSBLOCK_INGAME_MENU_PX,RUSSBLOCK_INGAME_MENU_PY+30*i,0,(russBlockSelectMenu==i?13+26*i:26*i),49,13,true,0);
	}
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgIngameMenu[1],9,301,0,0,25,13,true,0);//确定
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgIngameMenu[1],206,301,0,39,25,13,true,0);//返回
#endif
#ifdef GAME_176_220
	RussBlock_MenuBar_Paint(&russBlockPicLib,imgMenuBar,3*MENUBARWIDTH,4*MENUBARHEIGHT,20);
	for (i=0;i<3;i++)
	{
		russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgIngameMenu[0],RUSSBLOCK_INGAME_MENU_PX,RUSSBLOCK_INGAME_MENU_PY+30*i,0,(russBlockSelectMenu==i?13+26*i:26*i),49,13,true,0);
	}
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgIngameMenu[1],3,203,0,0,25,13,true,0);//确定
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,imgIngameMenu[1],148,203,0,39,25,13,true,0);//返回
#endif
}
//短信购买回调函数
void	RussBlock_SMS_BuyBoom(BOOLEAN isSucess)
{
	if(isSucess)
	{
		russBlockProp[GAME_PROP_BOMB]+=5;
		russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_PLAYING;
	}
	else
	{
		textBox.SetText(&textBox,"购买失败了!");
	}
}
//短信购买回调函数
void	RussBlock_SMS_BuySlowSpeed(BOOLEAN isSucess)
{
	if(isSucess)
	{

		russBlockProp[GAME_PROP_SLOWSPEED]+=5;
		russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_PLAYING;
	}
	else
	{
		textBox.SetText(&textBox,"购买失败了!");
	}
}
//短信购买回调函数
void	RussBlock_SMS_BuyTime(BOOLEAN isSucess)
{
	if(isSucess)
	{

		russBlockProp[GAME_PROP_EXTANDTIME]+=5;
		russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_PLAYING;

	}
	else
	{
		textBox.SetText(&textBox,"购买失败了!");
		//universalWarMenuState = UNIVERSALWAR_INGAME_MENU_STATE_HINT;
	}
}


