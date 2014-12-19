/************************************************************************************************
2010-5-20 zhaoliangqi
主菜单画面
***********************************************************************************************/
#include "HitMole_Screen.h"
#include "DF_Record.h"
#include "HitMole_Title.h"
#include "HitMole_About.h"
#include "HitMole_Help.h"
#include "HitMole_TitleMenu.h"
#include "HitMole_User-defined.h"
#include "HitMole_SelectLevel.h"
#include "HitMole_HighScore.h"
#include "HitMole_Pay.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
 
/*
首次进入游戏时需要添加一些游戏中界面
*/

extern void HitMole_Title_init(void);
extern void HitMole_Title_Destroy(void);
extern void HitMole_Title_Logic(void);
extern void HitMole_Title_Render(tGraphics * g);
extern void HitMole_Title_Pause(void);
extern void HitMole_Title_Resume(void);
extern void HitMole_Title_LoadResource(void);
extern void HitMole_Title_ChangeState(gm_s16 state);

extern void HitMole_Loading_LoadResource(void);
extern void HitMole_Loading_Init(void);
extern void HitMole_Loading_Destory(void);
extern void HitMole_Loading_Logic(void);
extern void HitMole_Loading_Render(tGraphics *g);
extern void HitMole_Loading_Pause(void);
extern void HitMole_Loading_Resume(void);

extern void HitMole_InGame_Init(void);
extern void HitMole_InGame_Destory(void);
extern void HitMole_InGame_Logic(void);
extern void HitMole_InGame_Render(tGraphics *g);
extern void HitMole_InGame_Pause(void);
extern void HitMole_InGame_Resume(void);
extern void HitMole_InGame_LoadResource(void);


Manager * manager_my;
MemoryBlock *memoryblock_my;
DF_Record hitMoleRecord;
gm_s32 hitMoleHighScoreValue[10];
gm_s32 hitMoleHighScoreYear[10];
gm_s32 hitMoleHighScoreMonth[10];
gm_s32 hitMoleHighScoreDate[10];


gm_s16 hitMoleTitleState;  
HitMoleTitle hitMoleTitle;
HitMole_About hitMoleTitleAbout;
HitMoleTitleMenu hitMoleTitleMenu;
HitMole_Help hitMoleHelp;
SelectLevel selectLevel;
UserDefine userDefine;
HitMole_HighScore hitMoleHighScore;
HitMole_Pay hitMolePay;


static DF_DataPackage dataPackage;
tScreen HitMole_Screen_Title;

void HitMole_Title_init(void)
{

}
void HitMole_Title_Destroy(void)
{
	vmdlReleaseTextBox(&hitMoleTitleAbout.textBox);
	vmdlReleaseTextBox(&hitMoleHelp.textBox);
	vmdlReleaseTextBox(&hitMolePay.textBox);
	allPicLib.Release(&allPicLib);
}
//每个界面的刷新方法
void HitMole_Title_Logic(void)
{
	switch (hitMoleTitleState)
	{
	case HITMOLE_TITLE_STATE_SHOW_TITLE:
		hitMoleTitle.windows.DF_Update(&hitMoleTitle.windows);
		break;
	case HITMOLE_TITLE_STATE_MENU:
		hitMoleTitleMenu.windows.DF_Update(&hitMoleTitleMenu.windows);
		break;
	case HITMOLE_TITLE_STATE_ABOUT:
		hitMoleTitleAbout.windows.DF_Update(&hitMoleTitleAbout.windows);
		break;
	case HITMOLE_TITLE_STATE_HELP:
		hitMoleHelp.windows.DF_Update(&hitMoleHelp.windows);
		break;
	case HITMOLE_TITLE_STATE_USERSET:
		userDefine.windows.DF_Update(&userDefine.windows);
		break;
	case HITMOLE_TITLE_STATE_SELECT:
		selectLevel.windows.DF_Update(&selectLevel.windows);
		break;
	case HITMOLE_TITLE_STATE_HIGSCORE:
		hitMoleHighScore.windows.DF_Update(&hitMoleHighScore.windows);
		break;
	case HITMOLE_TITLE_STATE_PAY:
		hitMolePay.windows.DF_Update(&hitMolePay.windows);
		break;
	}
}
//每个界面的绘制方法
void HitMole_Title_Render(tGraphics * g)
{
	switch (hitMoleTitleState)
	{
	case HITMOLE_TITLE_STATE_SHOW_TITLE:
		hitMoleTitle.windows.DF_Render(&hitMoleTitle.windows);
		break;
	case HITMOLE_TITLE_STATE_MENU:
		hitMoleTitleMenu.windows.DF_Render(&hitMoleTitleMenu.windows);
		break;
	case HITMOLE_TITLE_STATE_ABOUT:
		hitMoleTitleAbout.windows.DF_Render(&hitMoleTitleAbout.windows);
		break;
	case HITMOLE_TITLE_STATE_HELP:
		hitMoleHelp.windows.DF_Render(&hitMoleHelp.windows);
		break;
	case HITMOLE_TITLE_STATE_USERSET:
		userDefine.windows.DF_Render(&userDefine.windows);
		break;
	case HITMOLE_TITLE_STATE_SELECT:
		selectLevel.windows.DF_Render(&selectLevel.windows);
		break;
	case HITMOLE_TITLE_STATE_HIGSCORE:
		hitMoleHighScore.windows.DF_Render(&hitMoleHighScore.windows);
		break;
	case HITMOLE_TITLE_STATE_PAY:
		hitMolePay.windows.DF_Render(&hitMolePay.windows);
		break;
	}
	getManagerPtr()->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}
void HitMole_Title_Pause(void)
{

}
void HitMole_Title_Resume(void)
{
	HitMole_Title_ChangeState(hitMoleTitleState);
}
//初使化游戏中每个界面
void HitMole_Title_LoadResource()
{
	Rect ur;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
	initDFPictureLibrary(&allPicLib,10);
	initHitMoleTitle(&hitMoleTitle,ur,&allPicLib);
	initHitMoleTitleMenu(&hitMoleTitleMenu,ur,&allPicLib);
	initHitMoleAbout(&hitMoleTitleAbout,ur,&allPicLib);
	initHitMoleHelp(&hitMoleHelp,ur,&allPicLib);
	initUserDefine(&userDefine,ur,&allPicLib);
	initSelectLevel(&selectLevel,ur,&allPicLib);
	initHitMoleHighScore(&hitMoleHighScore,ur,&allPicLib);
	initHitMolePay(&hitMolePay,ur,&allPicLib);
}
//游戏中各个界面得屏幕切换点
void HitMole_Title_ChangeState(gm_s16 state)
{
	hitMoleTitleState=state;
	switch (hitMoleTitleState)
	{
	case HITMOLE_TITLE_STATE_SHOW_TITLE:
		DF_SendMessage(&hitMoleTitle.windows,DF_WINDOWS_MSG_INVALITE,&hitMoleTitle.windows.DF_Windows_Rect);
		break;
	case HITMOLE_TITLE_STATE_MENU:
		DF_SendMessage(&hitMoleTitleMenu.windows,DF_WINDOWS_MSG_INVALITE,&hitMoleTitleMenu.windows.DF_Windows_Rect);
		break;
	case HITMOLE_TITLE_STATE_ABOUT:
		DF_SendMessage(&hitMoleTitleAbout.windows,DF_WINDOWS_MSG_INVALITE,&hitMoleTitleAbout.windows.DF_Windows_Rect);
		break;
	case HITMOLE_TITLE_STATE_HELP:
		DF_SendMessage(&hitMoleHelp.windows,DF_WINDOWS_MSG_INVALITE,&hitMoleHelp.windows.DF_Windows_Rect);
		break;
	case HITMOLE_TITLE_STATE_USERSET:
		DF_SendMessage(&userDefine.windows,DF_WINDOWS_MSG_INVALITE,&userDefine.windows.DF_Windows_Rect);
		break;
	case HITMOLE_TITLE_STATE_SELECT:
		DF_SendMessage(&selectLevel.windows,DF_WINDOWS_MSG_INVALITE,&selectLevel.windows.DF_Windows_Rect);
		break;
	case HITMOLE_TITLE_STATE_HIGSCORE:
		DF_SendMessage(&hitMoleHighScore.windows,DF_WINDOWS_MSG_INVALITE,&hitMoleHighScore.windows.DF_Windows_Rect);
		break;
	case HITMOLE_TITLE_STATE_PAY:
		DF_SendMessage(&hitMolePay.windows,DF_WINDOWS_MSG_INVALITE,&hitMolePay.windows.DF_Windows_Rect);
		break;
	}
}

void Save_Record(void)
{
		gm_s16 i;
		hitMoleRecord.ResetData(&hitMoleRecord);//无效数据初始化记录
		hitMoleRecord.AddRecord(&hitMoleRecord,50);
		hitMoleRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			hitMoleRecord.WriteInt(&hitMoleRecord,0,hitMoleHighScoreValue[i]);
		}

		hitMoleRecord.AddRecord(&hitMoleRecord,50);
		hitMoleRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			hitMoleRecord.WriteInt(&hitMoleRecord,1,hitMoleHighScoreYear[i]);
		}

		hitMoleRecord.AddRecord(&hitMoleRecord,50);
		hitMoleRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			hitMoleRecord.WriteInt(&hitMoleRecord,2,hitMoleHighScoreMonth[i]);
		}

		hitMoleRecord.AddRecord(&hitMoleRecord,50);
		hitMoleRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			hitMoleRecord.WriteInt(&hitMoleRecord,3,hitMoleHighScoreDate[i]);
		}
}
void Read_Record(void)
{
	gm_s16 i;
	hitMoleRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			hitMoleHighScoreValue[i] = hitMoleRecord.ReadInt(&hitMoleRecord,0);
		}
		hitMoleRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			hitMoleHighScoreYear[i] = hitMoleRecord.ReadInt(&hitMoleRecord,1);
		}
		hitMoleRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			hitMoleHighScoreMonth[i] = hitMoleRecord.ReadInt(&hitMoleRecord,2);
		}
		hitMoleRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			hitMoleHighScoreDate[i] = hitMoleRecord.ReadInt(&hitMoleRecord,3);
		}
}

void Update_Record(gm_s16 i,gm_s32 jilu)
{
	hitMoleHighScoreValue[i] = jilu;
	hitMoleHighScoreYear[i] = MF_GetBlackYear();
	hitMoleHighScoreMonth[i] = MF_GetBlackMonth();
	hitMoleHighScoreDate[i] =  MF_GetBlackDay();
	Save_Record();
}

void HitMole_enter(void)
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
	dataPackage.DP_DoLoading(&dataPackage,HitMole_TResource_Data,0);
#else
	dataPackage.DP_DoLoading(&dataPackage,HitMole_TResource_Data,1);
#endif
	DF_SetDataPackage(&dataPackage);

	memoryblock_my=getMemoryBlockPtr();
	manager_my=getManagerPtr();
    initManager(manager_my);
	
	initDFPictureLibrary(&allPicLib,20);
	initDFRecord(&hitMoleRecord,"hitMoleRecord",1024,5);
	hitMoleRecord.Open(&hitMoleRecord);
	if(hitMoleRecord.recordNum != 4)
	{
		hitMoleRecord.ResetData(&hitMoleRecord);//无效数据初始化记录
		hitMoleRecord.AddRecord(&hitMoleRecord,50);
		hitMoleRecord.pointer = 0;
		for(i=0;i<10;i++)
		{
			hitMoleHighScoreValue[i]=0;
		}
		for(i=0;i<10;i++)
		{
			hitMoleHighScoreYear[i]=0;
		}
		for(i=0;i<10;i++)
		{
			hitMoleHighScoreMonth[i]=0;
		}
		for(i=0;i<10;i++)
		{
			hitMoleHighScoreDate[i]=0;
		}
		Save_Record();
	}
	Read_Record();
	hitMoleTitleState=HITMOLE_TITLE_STATE_SHOW_TITLE;
	hitMoleLoadingStep=0;
	hitMoleLoadingStepTotal=16;
	
	vmtScreenInit(&HitMole_Screen_InGame,
	HitMole_InGame_Init,
	HitMole_InGame_Destory,
	HitMole_InGame_Logic,
	HitMole_InGame_Render,
	HitMole_InGame_Pause,
	HitMole_InGame_Resume,
	HitMole_InGame_LoadResource
	);
	
	vmtScreenInit(&HitMole_Screen_Loading,
	HitMole_Loading_Init,
	HitMole_Loading_Destory,
	HitMole_Loading_Logic,
	HitMole_Loading_Render,
	HitMole_Loading_Pause,
	HitMole_Loading_Resume,
	HitMole_Loading_LoadResource
	);
	
	vmtScreenInit(&HitMole_Screen_Title,
	HitMole_Title_init,
	HitMole_Title_Destroy,
	HitMole_Title_Logic,
	HitMole_Title_Render,
	HitMole_Title_Pause,
	HitMole_Title_Resume,
	HitMole_Title_LoadResource
	);
	HitMole_Screen_Next=&HitMole_Screen_Title;//记录下个屏幕点
	SCREEN_ChangeScreen(&HitMole_Screen_Loading);//切换屏幕

}

//游戏退出,释放资源
void HitMole_exit()
{
	dataPackage.DP_ReleasePackage(&dataPackage,0);
	hitMoleRecord.Close(&hitMoleRecord);
	allPicLib.Release(&allPicLib);
	DF_ReleaseMemory();

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
	game_reg(HitMole_enter,HitMole_exit);
}
#pragma arm section code
#endif
*/