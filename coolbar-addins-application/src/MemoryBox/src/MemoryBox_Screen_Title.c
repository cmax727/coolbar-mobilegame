/************************************************************************************************
2010-5-20 zhaoliangqi
主菜单画面
***********************************************************************************************/
#include "MemoryBox_Screen.h"
#include "DF_Record.h"
#include "MemoryBox_Title.h"
#include "MemoryBox_About.h"
#include "MemoryBox_Help.h"
#include "MemoryBox_TitleMenu.h"
#include "MemoryBox_Exersice.h"
#include "MemoryBox_HighScore.h"
#include "MemoryBox_Pay.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
 
/*
首次进入游戏时需要添加一些游戏中界面
*/

extern void MemoryBox_Title_init(void);
extern void MemoryBox_Title_Destroy(void);
extern void MemoryBox_Title_Logic(void);
extern void MemoryBox_Title_Render(tGraphics * g);
extern void MemoryBox_Title_Pause(void);
extern void MemoryBox_Title_Resume(void);
extern void MemoryBox_Title_LoadResource(void);
extern void MemoryBox_Title_ChangeState(gm_s16 state);

extern void MemoryBox_Loading_LoadResource(void);
extern void MemoryBox_Loading_Init(void);
extern void MemoryBox_Loading_Destory(void);
extern void MemoryBox_Loading_Logic(void);
extern void MemoryBox_Loading_Render(tGraphics *g);
extern void MemoryBox_Loading_Pause(void);
extern void MemoryBox_Loading_Resume(void);

extern void MemoryBox_InGame_Init(void);
extern void MemoryBox_InGame_Destory(void);
extern void MemoryBox_InGame_Logic(void);
extern void MemoryBox_InGame_Render(tGraphics *g);
extern void MemoryBox_InGame_Pause(void);
extern void MemoryBox_InGame_Resume(void);
extern void MemoryBox_InGame_LoadResource(void);


Manager * manager_my;
MemoryBlock *memoryblock_my;
DF_Record memoryBoxRecord;
gm_s32 memoryBoxHighTimeValue[10];
gm_s32 memoryBoxHighScoreYear[10];
gm_s32 memoryBoxHighScoreMonth[10];
gm_s32 memoryBoxHighScoreDate[10];


gm_s16 memoryBoxTitleState;  
MemoryBoxTitle memoryBoxTitle;
MemoryBoxTitleMenu memoryBoxTitleMenu;
MemoryBox_About memoryBoxTitleAbout;
MemoryBox_Help memoryBoxHelp;
MemoryBoxExersice memoryBoxExersice;
MemoryBox_HighScore memoryBoxHighScore;
MemoryBox_Pay memoryBoxPay;

static DF_DataPackage dataPackage;
tScreen MemoryBox_Screen_Title;

void MemoryBox_Title_init(void)
{

}
void MemoryBox_Title_Destroy(void)
{
	vmdlReleaseTextBox(&memoryBoxTitleAbout.textBox);
	vmdlReleaseTextBox(&memoryBoxHelp.textBox);
	vmdlReleaseTextBox(&memoryBoxPay.textBox);
	allPicLib.Release(&allPicLib);
}
//每个界面的刷新方法
void MemoryBox_Title_Logic(void)
{
	switch (memoryBoxTitleState)
	{
	case MEMORYBOX_TITLE_STATE_SHOW_TITLE:
		memoryBoxTitle.windows.DF_Update(&memoryBoxTitle.windows);
		break;
	case MEMORYBOX_TITLE_STATE_MENU:
		memoryBoxTitleMenu.windows.DF_Update(&memoryBoxTitleMenu.windows);
		break;
	case MEMORYBOX_TITLE_STATE_ABOUT:
		memoryBoxTitleAbout.windows.DF_Update(&memoryBoxTitleAbout.windows);
		break;		
	case MEMORYBOX_TITLE_STATE_HELP:
		memoryBoxHelp.windows.DF_Update(&memoryBoxHelp.windows);
		break;
		case MEMORYBOX_TITLE_STATE_EXERSICE:
		memoryBoxExersice.windows.DF_Update(&memoryBoxExersice.windows);
		break;
	case MEMORYBOX_TITLE_STATE_HIGSCORE:
		memoryBoxHighScore.windows.DF_Update(&memoryBoxHighScore.windows);
		break;
	case MEMORYBOX_TITLE_STATE_PAY:
		memoryBoxPay.windows.DF_Update(&memoryBoxPay.windows);
		break;
	default:
		break;
	}
}
//每个界面的绘制方法
void MemoryBox_Title_Render(tGraphics * g)
{
	switch (memoryBoxTitleState)
	{
	case MEMORYBOX_TITLE_STATE_SHOW_TITLE:
		memoryBoxTitle.windows.DF_Render(&memoryBoxTitle.windows);
		break;
	case MEMORYBOX_TITLE_STATE_MENU:
		memoryBoxTitleMenu.windows.DF_Render(&memoryBoxTitleMenu.windows);
		break;		
	case MEMORYBOX_TITLE_STATE_ABOUT:
		memoryBoxTitleAbout.windows.DF_Render(&memoryBoxTitleAbout.windows);
		break;
	case MEMORYBOX_TITLE_STATE_HELP:
		memoryBoxHelp.windows.DF_Render(&memoryBoxHelp.windows);
		break;
	case MEMORYBOX_TITLE_STATE_EXERSICE:
		memoryBoxExersice.windows.DF_Render(&memoryBoxExersice.windows);
		break;
	case MEMORYBOX_TITLE_STATE_HIGSCORE:
		memoryBoxHighScore.windows.DF_Render(&memoryBoxHighScore.windows);
		break;
	case MEMORYBOX_TITLE_STATE_PAY:
		memoryBoxPay.windows.DF_Render(&memoryBoxPay.windows);
		break;
	default:
		break;
	}
	getManagerPtr()->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}
void MemoryBox_Title_Pause(void)
{

}
void MemoryBox_Title_Resume(void)
{
	MemoryBox_Title_ChangeState(memoryBoxTitleState);
}
//初使化游戏中每个界面
void MemoryBox_Title_LoadResource()
{
	Rect ur;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
	initDFPictureLibrary(&allPicLib,10);
	initMemoryBoxTitle(&memoryBoxTitle,ur,&allPicLib);
	initMemoryBoxTitleMenu(&memoryBoxTitleMenu,ur,&allPicLib);
	initMemoryBoxAbout(&memoryBoxTitleAbout,ur,&allPicLib);
	initMemoryBoxHelp(&memoryBoxHelp,ur,&allPicLib);
	initMemoryBoxExersice(&memoryBoxExersice,ur,&allPicLib);
	initMemoryBoxHighScore(&memoryBoxHighScore,ur,&allPicLib);
	initMemoryBoxPay(&memoryBoxPay,ur,&allPicLib);
}
//游戏中各个界面得屏幕切换点
void MemoryBox_Title_ChangeState(gm_s16 state)
{
	memoryBoxTitleState=state;
	switch (memoryBoxTitleState)
	{
	case MEMORYBOX_TITLE_STATE_SHOW_TITLE:
		DF_SendMessage(&memoryBoxTitle.windows,DF_WINDOWS_MSG_INVALITE,&memoryBoxTitle.windows.DF_Windows_Rect);
		break;
	case MEMORYBOX_TITLE_STATE_MENU:
		DF_SendMessage(&memoryBoxTitleMenu.windows,DF_WINDOWS_MSG_INVALITE,&memoryBoxTitleMenu.windows.DF_Windows_Rect);
		break;
	case MEMORYBOX_TITLE_STATE_ABOUT:
		DF_SendMessage(&memoryBoxTitleAbout.windows,DF_WINDOWS_MSG_INVALITE,&memoryBoxTitleAbout.windows.DF_Windows_Rect);
		break;
	case MEMORYBOX_TITLE_STATE_HELP:
		DF_SendMessage(&memoryBoxHelp.windows,DF_WINDOWS_MSG_INVALITE,&memoryBoxHelp.windows.DF_Windows_Rect);
		break;
	case MEMORYBOX_TITLE_STATE_EXERSICE:
		DF_SendMessage(&memoryBoxExersice.windows,DF_WINDOWS_MSG_INVALITE,&memoryBoxExersice.windows.DF_Windows_Rect);
		break;
	case MEMORYBOX_TITLE_STATE_HIGSCORE:
		DF_SendMessage(&memoryBoxHighScore.windows,DF_WINDOWS_MSG_INVALITE,&memoryBoxHighScore.windows.DF_Windows_Rect);
		break;
	case MEMORYBOX_TITLE_STATE_PAY:
		DF_SendMessage(&memoryBoxPay.windows,DF_WINDOWS_MSG_INVALITE,&memoryBoxPay.windows.DF_Windows_Rect);
		break;
	default:
		break;
	}
}

void MemoryBox_Save_Record(void)
{
		gm_s16 i;
		memoryBoxRecord.ResetData(&memoryBoxRecord);//无效数据初始化记录
		memoryBoxRecord.AddRecord(&memoryBoxRecord,50);
		memoryBoxRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			memoryBoxRecord.WriteInt(&memoryBoxRecord,0,memoryBoxHighTimeValue[i]);
		}

		memoryBoxRecord.AddRecord(&memoryBoxRecord,50);
		memoryBoxRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			memoryBoxRecord.WriteInt(&memoryBoxRecord,1,memoryBoxHighScoreYear[i]);
		}

		memoryBoxRecord.AddRecord(&memoryBoxRecord,50);
		memoryBoxRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			memoryBoxRecord.WriteInt(&memoryBoxRecord,2,memoryBoxHighScoreMonth[i]);
		}

		memoryBoxRecord.AddRecord(&memoryBoxRecord,50);
		memoryBoxRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			memoryBoxRecord.WriteInt(&memoryBoxRecord,3,memoryBoxHighScoreDate[i]);
		}
}
void MemoryBox_Read_Record(void)
{
	gm_s16 i;
	memoryBoxRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			memoryBoxHighTimeValue[i] = memoryBoxRecord.ReadInt(&memoryBoxRecord,0);
		}
		memoryBoxRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			memoryBoxHighScoreYear[i] = memoryBoxRecord.ReadInt(&memoryBoxRecord,1);
		}
		memoryBoxRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			memoryBoxHighScoreMonth[i] = memoryBoxRecord.ReadInt(&memoryBoxRecord,2);
		}
		memoryBoxRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			memoryBoxHighScoreDate[i] = memoryBoxRecord.ReadInt(&memoryBoxRecord,3);
		}
}

void MemoryBox_Update_Record(gm_s16 i,gm_s32 jilu)
{
	memoryBoxHighTimeValue[i] = jilu;
	memoryBoxHighScoreYear[i] = MF_GetBlackYear();
	memoryBoxHighScoreMonth[i] = MF_GetBlackMonth();
	memoryBoxHighScoreDate[i] =  MF_GetBlackDay();
	MemoryBox_Save_Record();
}

void MemoryBox_enter(void)
{
	gm_s8 i;
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
#ifdef WIN32
	dataPackage.DP_DoLoading(&dataPackage,MemoryBox_TResource_Data,0);
#else
	dataPackage.DP_DoLoading(&dataPackage,MemoryBox_TResource_Data,1);
#endif
	DF_SetDataPackage(&dataPackage);

	memoryblock_my=getMemoryBlockPtr();
	manager_my=getManagerPtr();
    initManager(manager_my);
	
	initDFPictureLibrary(&allPicLib,20);
	initDFRecord(&memoryBoxRecord,"memoryBoxRecord",1024,5);
	memoryBoxRecord.Open(&memoryBoxRecord);
	if(memoryBoxRecord.recordNum != 4)
	{
		memoryBoxRecord.ResetData(&memoryBoxRecord);//无效数据初始化记录
		memoryBoxRecord.AddRecord(&memoryBoxRecord,50);
		memoryBoxRecord.pointer = 0;
		for(i=0;i<9;i++)
		{
			memoryBoxHighTimeValue[i]=300;
		}
			memoryBoxHighTimeValue[9]=700;
		for(i=0;i<10;i++)
		{
			memoryBoxHighScoreYear[i]=0;
		}
		for(i=0;i<10;i++)
		{
			memoryBoxHighScoreMonth[i]=0;
		}
		for(i=0;i<10;i++)
		{
			memoryBoxHighScoreDate[i]=0;
		}
		MemoryBox_Save_Record();
	}
	MemoryBox_Read_Record();
	memoryBoxTitleState=MEMORYBOX_TITLE_STATE_SHOW_TITLE;
	memoryBoxLoadingStep=0;
	memoryBoxLoadingStepTotal=16;
	
	vmtScreenInit(&MemoryBox_Screen_InGame,
	MemoryBox_InGame_Init,
	MemoryBox_InGame_Destory,
	MemoryBox_InGame_Logic,
	MemoryBox_InGame_Render,
	MemoryBox_InGame_Pause,
	MemoryBox_InGame_Resume,
	MemoryBox_InGame_LoadResource
	);
	
	vmtScreenInit(&MemoryBox_Screen_Loading,
	MemoryBox_Loading_Init,
	MemoryBox_Loading_Destory,
	MemoryBox_Loading_Logic,
	MemoryBox_Loading_Render,
	MemoryBox_Loading_Pause,
	MemoryBox_Loading_Resume,
	MemoryBox_Loading_LoadResource
	);
	
	vmtScreenInit(&MemoryBox_Screen_Title,
	MemoryBox_Title_init,
	MemoryBox_Title_Destroy,
	MemoryBox_Title_Logic,
	MemoryBox_Title_Render,
	MemoryBox_Title_Pause,
	MemoryBox_Title_Resume,
	MemoryBox_Title_LoadResource
	);
	MemoryBox_Screen_Next=&MemoryBox_Screen_Title;//记录下个屏幕点
	SCREEN_ChangeScreen(&MemoryBox_Screen_Loading);//切换屏幕

}

//游戏退出,释放资源
void MemoryBox_exit()
{
	dataPackage.DP_ReleasePackage(&dataPackage,0);
	memoryBoxRecord.Close(&memoryBoxRecord);
	allPicLib.Release(&allPicLib);
	DF_ReleaseMemory();

}

void   MemoryBox_SMS_BuyOneMonth(BOOLEAN isSucess)//是否包月回调函数
{
	if(isSucess)
	{
		MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
	}
}
/*
#ifndef WIN32
VmMainFunction vMGetMainEnterFuct(void)   //函数名（函数指针）固定唯一，不可改变。
{
    return ONFF_enter;              //实际的入口函数
}

VmMainFunction vMGetMainExitFuct(void)    //同上
{
    return ONFF_exit;               //实际的退出函数
}
#endif 


#ifdef COOLBAR_DYNAMIC_LOADING
#include "dynamicLoadingCore_ext.h"
#pragma arm section code = "game_reg_main"
void game_reg_main(sysCall sys_call)//游戏进出口
{
	t_sysCall = sys_call;
	game_reg(MemoryBox_enter,MemoryBox_exit);
}
#pragma arm section code
#endif
*/
