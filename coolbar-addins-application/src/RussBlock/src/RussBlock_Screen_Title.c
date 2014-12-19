#include "RussBlock_Screen.h"
#include "DF_Record.h"
#include "RussBlock_Help.h"
#include "RussBlock_Title.h"
#include "RussBlock_TitleMenu.h"
#include "RussBlock_HighScore.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
/*
首次进入游戏时需要添加一些游戏中界面
*/

extern void russBlock_Title_init();
extern void russBlock_Title_Destroy();
extern void russBlock_Title_Logic();
extern void russBlock_Title_Render(tGraphics * g);
extern void russBlock_Title_Pause();
extern void russBlock_Title_Resume();
extern void russBlock_Title_LoadResource();


Manager * manager_my;
MemoryBlock *memoryblock_my;
DF_Record russBlockRecord;
gm_s32 russBlockHighScoreValue_CommonModel[12];
gm_s32 russBlockHighScoreValue_TimeModel[12];

gm_s16 russBlockTitleState;  
RussBlockTitle rushBlockTitle;
RussBlockTitleMenu russBlockTitleMenu;
RussBlock_Help russBlockTitleHelp;
RussBlock_HighScore russBlockHighScore;

static DF_DataPackage dataPackage;
tScreen RussBlock_Screen_Title =
{
	russBlock_Title_init,
	russBlock_Title_Destroy,
	russBlock_Title_Logic,
	russBlock_Title_Render,
	russBlock_Title_Pause,
	russBlock_Title_Resume,
	russBlock_Title_LoadResource
};

void russBlock_Title_init()
{

}
void russBlock_Title_Destroy()
{
	russBlockPicLib.Release(&russBlockPicLib);
}
//每个界面的刷新方法
void russBlock_Title_Logic()
{
	switch (russBlockTitleState)
	{
	case RUSSBLOCK_TITLE_STATE_SHOW_TITLE:
		rushBlockTitle.windows.DF_Update(&rushBlockTitle.windows);
		break;
	case RUSSBLOCK_TITLE_STATE_MENU:
		russBlockTitleMenu.windows.DF_Update(&russBlockTitleMenu.windows);
		break;
	case RUSSBLOCK_TITLE_STATE_HELP:
		russBlockTitleHelp.windows.DF_Update(&russBlockTitleHelp.windows);
	    break;
	case RUSSBLOCK_TITLE_STATE_HIGHSCORE:
		russBlockHighScore.windows.DF_Update(&russBlockHighScore.windows);
		break;		
	}
}
//每个界面的绘制方法
void russBlock_Title_Render(tGraphics * g)
{
	switch (russBlockTitleState)
	{
	case RUSSBLOCK_TITLE_STATE_SHOW_TITLE:
		rushBlockTitle.windows.DF_Render(&rushBlockTitle.windows);
		break;
	case RUSSBLOCK_TITLE_STATE_MENU:
		russBlockTitleMenu.windows.DF_Render(&russBlockTitleMenu.windows);
		break;
	case RUSSBLOCK_TITLE_STATE_HELP:
		russBlockTitleHelp.windows.DF_Render(&russBlockTitleHelp.windows);
		break;
	case RUSSBLOCK_TITLE_STATE_HIGHSCORE:
		russBlockHighScore.windows.DF_Render(&russBlockHighScore.windows);
		break;
	}
	getManagerPtr()->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}
void russBlock_Title_Pause()
{

}
void russBlock_Title_Resume()
{
	RussBlock_Title_ChangeState(russBlockTitleState);
}
//初使化游戏中每个界面
void russBlock_Title_LoadResource()
{
	Rect ur;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
	initDFPictureLibrary(&russBlockPicLib,20);
	initRussBlockTitle(&rushBlockTitle,ur,&russBlockPicLib);
	initRussBlockTitleMenu(&russBlockTitleMenu,ur,&russBlockPicLib);
	initRussBlockHelp(&russBlockTitleHelp,ur,&russBlockPicLib);
	initRussBlockHighScore(&russBlockHighScore,ur,&russBlockPicLib);
}
//游戏中各个界面得屏幕切换点
void RussBlock_Title_ChangeState(gm_s16 state)
{
	russBlockTitleState=state;
	switch (russBlockTitleState)
	{
	case RUSSBLOCK_TITLE_STATE_SHOW_TITLE:
		DF_SendMessage(&rushBlockTitle.windows,DF_WINDOWS_MSG_INVALITE,&rushBlockTitle.windows.DF_Windows_Rect);
		break;
	case RUSSBLOCK_TITLE_STATE_MENU:
		DF_SendMessage(&russBlockTitleMenu.windows,DF_WINDOWS_MSG_INVALITE,&russBlockTitleMenu.windows.DF_Windows_Rect);
	    break;
	case RUSSBLOCK_TITLE_STATE_HELP:
		DF_SendMessage(&russBlockTitleHelp.windows,DF_WINDOWS_MSG_INVALITE,&russBlockTitleHelp.windows.DF_Windows_Rect);
	    break;
	case RUSSBLOCK_TITLE_STATE_HIGHSCORE:
		DF_SendMessage(&russBlockHighScore.windows,DF_WINDOWS_MSG_INVALITE,&russBlockHighScore.windows.DF_Windows_Rect);
		break;
	}
}

void RussBlock_main(void)
{
	gm_s16 j,m;
#ifdef GAME_240_320
	DF_InitMemory(150*1024);	//设定游戏内存空间
#endif
#ifdef GAME_176_220
	DF_InitMemory(140*1024);
#endif
	initMemoryBlock(getMemoryBlockPtr(),1024*50);
	initDreamFactoryEngine();
	initDFDataPackage(&dataPackage,5);//游戏的资源包	
	dataPackage.DP_LoadPackage(&dataPackage,0);
	dataPackage.DP_DoLoading(&dataPackage,RussBlock_TResource_Data,1);
	DF_SetDataPackage(&dataPackage);

	memoryblock_my=getMemoryBlockPtr();

	manager_my=getManagerPtr();
    initManager(manager_my);
	
	initDFPictureLibrary(&russBlockPicLib,5);

	//初始话记录集
	initDFRecord(&russBlockRecord,"russBlockRecord",1024,8);
	russBlockRecord.Open(&russBlockRecord);
	if(russBlockRecord.recordNum!=7)  //写记录
	{
		russBlockRecord.ResetData(&russBlockRecord);//无效数据初始化记录
		/*普通模式*/
		russBlockRecord.AddRecord(&russBlockRecord,50);
		russBlockRecord.pointer = 0;
		for (j=0;j<12;j++)
		{
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_COMMONMODEL,0);
		}

		/*时间模式*/
		russBlockRecord.AddRecord(&russBlockRecord,50);
		russBlockRecord.pointer = 0;
		for (j=0;j<12;j++)
		{
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_TIMEMODEL,0);
		}
		/*写入道具*/
		russBlockRecord.AddRecord(&russBlockRecord,50);
		russBlockRecord.pointer = 0;
		for (j=0;j<3;j++)
		{
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_PROP,0);
			russBlockProp[j]=99;
		}
		/*写入普通模式网格数据*/
		russBlockRecord.AddRecord(&russBlockRecord,254);
		russBlockRecord.pointer=0;
		for (j=0;j<VERTICAL_BOXS;j++)
		{
			for (m=0;m<HORIZONTAL_BOXS;m++)
			{
				russBlockRecord.WriteByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_NOMAL,0);
			}
		}
		/*写入时间模式网格数据*/
		russBlockRecord.AddRecord(&russBlockRecord,254);
		russBlockRecord.pointer=0;
		for (j=0;j<VERTICAL_BOXS;j++)
		{
			for (m=0;m<HORIZONTAL_BOXS;m++)
			{
				russBlockRecord.WriteByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_TIME,0);
			}
		}


		/*普通模式记录 */
		russBlockRecord.AddRecord(&russBlockRecord,20);
		russBlockRecord.pointer=0;
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,1);  //等级
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,0);  //分数
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,0);  //消的层数
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,0);  //下落速度
		russBlockGameData[0][0]=1;
 
		/*时间模式记录*/
		russBlockRecord.AddRecord(&russBlockRecord,20);
		russBlockRecord.pointer=0;
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,1);  //等级
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,0);  //分数
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,0);  //消的层数
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,0);  //下落速度
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,BLOCK_TIME); //时间
		russBlockGameTime=BLOCK_TIME;
		russBlockGameData[1][0]=1;
	}
	else     //读记录
	{
			russBlockRecord.pointer=0;
			for (m=0;m<12;m++)
			{
				 russBlockHighScoreValue_CommonModel[m]=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_COMMONMODEL);
			}
			russBlockRecord.pointer=0;
			for(m=0;m<12;m++)
			{
				russBlockHighScoreValue_TimeModel[m]=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_TIMEMODEL);
			}
			russBlockRecord.pointer = 0;	
		    for (m=0;m<3;m++)
		    {
				russBlockProp[m]=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_PROP);
		    }

			russBlockRecord.pointer=0;
			for (j=0;j<VERTICAL_BOXS;j++)
			{
				for (m=0;m<HORIZONTAL_BOXS;m++)
					russBlockGameGrid[0][j][m]=russBlockRecord.ReadByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_NOMAL);
			}
			
			russBlockRecord.pointer=0;
			for (j=0;j<VERTICAL_BOXS;j++)
			{
				for (m=0;m<HORIZONTAL_BOXS;m++)
					russBlockGameGrid[1][j][m]=russBlockRecord.ReadByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_TIME);
			}
            
			russBlockRecord.pointer=0;
			for (j=0;j<4;j++)
			{
				russBlockGameData[0][j]=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL);
			}

			russBlockRecord.pointer=0;
			for (j=0;j<4;j++)
			{
				russBlockGameData[1][j]=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME);
			}
			russBlockGameTime=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME);
	}

	russBlockTitleState=RUSSBLOCK_TITLE_STATE_SHOW_TITLE;
	russBlockLoadingStep=0;
	russBlockLoadingStepTotal=16;
	RussBlock_Screen_Next=&RussBlock_Screen_Title;//记录下个屏幕点
	SCREEN_ChangeScreen(&RussBlock_Screen_Loading);//切换屏幕

}
//游戏退出,释放资源
void RussBlock_exit()
{
	updateGameData();
	dataPackage.DP_ReleasePackage(&dataPackage,0);
	russBlockRecord.Close(&russBlockRecord);
	russBlockPicLib.Release(&russBlockPicLib);
	DF_ReleaseMemory();

}

void   RussBlock_SMS_BuyOneMonth(BOOLEAN isSucess)//是否包月回调函数
{
	if(isSucess)
	{
		RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_MENU);
	}
}
/*
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dynamicLoadingCore_ext.h"
#pragma arm section code = "game_reg_main"
void game_reg_main(sysCall sys_call)//游戏进出口
{
	t_sysCall = sys_call;
	game_reg(RussBlock_main,RussBlock_exit);
}
#pragma arm section code
#endif

*/