/************************************************************************************************
2010-5-20 zhaoliangqi
主菜单画面
***********************************************************************************************/
#include "SameGame_Screen.h"
#include "DF_Record.h"

#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

void SameGame_Title_Init(void)
{
}

void SameGame_Title_Destroy(void)
{
	allPicLib.Release(&allPicLib);
	
}

//每个界面的刷新方法
void SameGame_Title_Logic(void)
{
	switch (sameGameTitleState)
	{
	case SAMEGAME_STATE_LOGO:
		sameGameLogo.windows.DF_Update(&sameGameLogo.windows);
		break;
	case SAMEGAME_STATE_TITLEMENU:
		sameGameTitleMenu.windows.DF_Update(&sameGameTitleMenu.windows);
		break;
	case SAMEGAME_STATE_PLAYMENU:
		sameGamePlayMenu.windows.DF_Update(&sameGamePlayMenu.windows);
		break;		
	case SAMEGAME_STATE_COMPLETEMENU:
		sameGameCompleteMenu.windows.DF_Update(&sameGameCompleteMenu.windows);
		break;
	case SAMEGAME_STATE_CHANGECHIP:
		sameGameChangeChip.windows.DF_Update(&sameGameChangeChip.windows);
		break;
	case SAMEGAME_STATE_HIGSCORE:
		sameGameHighScore.windows.DF_Update(&sameGameHighScore.windows);
		break;
	default:
		break;
	}
}

//每个界面的绘制方法
void SameGame_Title_Render(tGraphics * g)
{
	switch (sameGameTitleState)
	{
	case SAMEGAME_STATE_LOGO:
		sameGameLogo.windows.DF_Render(&sameGameLogo.windows);
		break;
	case SAMEGAME_STATE_TITLEMENU:
		sameGameTitleMenu.windows.DF_Render(&sameGameTitleMenu.windows);
		break;
	case SAMEGAME_STATE_PLAYMENU:
		sameGamePlayMenu.windows.DF_Render(&sameGamePlayMenu.windows);
		break;		
	case SAMEGAME_STATE_COMPLETEMENU:
		sameGameCompleteMenu.windows.DF_Render(&sameGameCompleteMenu.windows);
		break;
	case SAMEGAME_STATE_CHANGECHIP:
		sameGameChangeChip.windows.DF_Render(&sameGameChangeChip.windows);
		break;
	case SAMEGAME_STATE_HIGSCORE:
		sameGameHighScore.windows.DF_Render(&sameGameHighScore.windows);
		break;
	default:
		break;
	}
	getManagerPtr()->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}

void SameGame_Title_Pause(void)
{
}

void SameGame_Title_Resume(void)
{
	SameGame_Title_ChangeState(sameGameTitleState);
}

//初使化游戏中每个界面
void SameGame_Title_LoadResource()
{
	Rect ur;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
	initDFPictureLibrary(&allPicLib,10);
	SameGame_Logo_Init(&sameGameLogo,ur,&allPicLib);
	SameGame_TitleMenu_Init(&sameGameTitleMenu,ur,&allPicLib);
	SameGame_PlayMenu_Init(&sameGamePlayMenu,ur,&allPicLib);
	SameGame_CompleteMenu_Init(&sameGameCompleteMenu,ur,&allPicLib);
	SameGame_ChangeChip_Init(&sameGameChangeChip,ur,&allPicLib);
	SameGame_HighScore_Init(&sameGameHighScore,ur,&allPicLib);
}

//游戏中各个界面得屏幕切换点
void SameGame_Title_ChangeState(gm_s16 state)
{
	sameGameTitleState=state;
	switch (sameGameTitleState)
	{
	case SAMEGAME_STATE_LOGO:
		DF_SendMessage(&sameGameLogo,DF_WINDOWS_MSG_INVALITE,&sameGameLogo.windows.DF_Windows_Rect);
		break;
	case SAMEGAME_STATE_TITLEMENU:
		DF_SendMessage(&sameGameTitleMenu.windows,DF_WINDOWS_MSG_INVALITE,&sameGameTitleMenu.windows.DF_Windows_Rect);
		break;
	case SAMEGAME_STATE_PLAYMENU:
		DF_SendMessage(&sameGamePlayMenu.windows,DF_WINDOWS_MSG_INVALITE,&sameGamePlayMenu.windows.DF_Windows_Rect);
		break;
	case SAMEGAME_STATE_COMPLETEMENU:
		DF_SendMessage(&sameGameCompleteMenu.windows,DF_WINDOWS_MSG_INVALITE,&sameGameCompleteMenu.windows.DF_Windows_Rect);
		break;
	case SAMEGAME_STATE_CHANGECHIP:
		DF_SendMessage(&sameGameChangeChip.windows,DF_WINDOWS_MSG_INVALITE,&sameGameChangeChip.windows.DF_Windows_Rect);
		break;
	case SAMEGAME_STATE_HIGSCORE:
		DF_SendMessage(&sameGameHighScore.windows,DF_WINDOWS_MSG_INVALITE,&sameGameHighScore.windows.DF_Windows_Rect);
		break;
	default:
		break;
	}
}

void SameGame_Save_Record(void)
{
	gm_s16 i;
	sameGameRecord.ResetData(&sameGameRecord);//无效数据初始化记录
	sameGameRecord.AddRecord(&sameGameRecord,50);
	sameGameRecord.pointer = 0;
	for(i=0;i<3;i++)
		sameGameRecord.WriteInt(&sameGameRecord,0,sameGameHighTimeValue[i]);
}
void SameGame_Read_Record(void)
{
	gm_s16 i;
	sameGameRecord.pointer = 0;
	for(i=0;i<3;i++)
		sameGameHighTimeValue[i] = sameGameRecord.ReadInt(&sameGameRecord,0);
}

void SameGame_Update_Record(gm_s16 i,gm_s32 jilu)
{
	sameGameHighTimeValue[i] = jilu;
	SameGame_Save_Record();
}

char ss[2][40];
int x = 0;
void xx(){
	//ss[0] = "abc";
}
void SameGame_enter(void)
{
	gm_s8 i;
	/*
	*/
	//xx();
	x = sizeof(ss);
	sprintf(ss[0], "This is a boy");
	

	DF_InitMemory(150*1024);	//设定游戏内存空间

	initMemoryBlock(getMemoryBlockPtr(),1024*50);
	initDreamFactoryEngine();
	initDFDataPackage(&dataPackage,5);//游戏的资源包	
	dataPackage.DP_LoadPackage(&dataPackage,0);
#ifdef WIN32
	dataPackage.DP_DoLoading(&dataPackage,SameGame_TResource_Data,0);
#else
	dataPackage.DP_DoLoading(&dataPackage,SameGame_TResource_Data,1);
#endif
	DF_SetDataPackage(&dataPackage);

	memoryblock_my=getMemoryBlockPtr();
	manager_my=getManagerPtr();
    initManager(manager_my);

	initDFPictureLibrary(&allPicLib,20);
	initDFRecord(&sameGameRecord,"SameGameRecord",1024,1);
	sameGameRecord.Open(&sameGameRecord);
	if(sameGameRecord.recordNum != 1)
	{
		sameGameRecord.ResetData(&sameGameRecord);//无效数据初始化记录
		sameGameRecord.AddRecord(&sameGameRecord,50);
		sameGameRecord.pointer = 0;
		for(i=0;i<3;i++)
			sameGameHighTimeValue[i]=0;	

		SameGame_Save_Record();
	}
	SameGame_Read_Record();
	sameGameTitleState=SAMEGAME_STATE_LOGO;
	sameGameLoadingStep=0;
	sameGameLoadingStepTotal=16;

	vmtScreenInit(&sameGame_Screen_InGame,
	SameGame_InGame_Init,
	SameGame_InGame_Destory,
	SameGame_InGame_Logic,
	SameGame_InGame_Render,
	SameGame_InGame_Pause,
	SameGame_InGame_Resume,
	SameGame_InGame_LoadResource
	);

	vmtScreenInit(&sameGame_Screen_Loading,
	SameGame_Loading_Init,
	SameGame_Loading_Destory,
	SameGame_Loading_Logic,
	SameGame_Loading_Render,
	SameGame_Loading_Pause,
	SameGame_Loading_Resume,
	SameGame_Loading_LoadResource
	);

	vmtScreenInit(&sameGame_Screen_Title,
	SameGame_Title_Init,
	SameGame_Title_Destroy,
	SameGame_Title_Logic,
	SameGame_Title_Render,
	SameGame_Title_Pause,
	SameGame_Title_Resume,
	SameGame_Title_LoadResource
	);

	sameGame_Screen_Next=&sameGame_Screen_Title;//记录下个屏幕点
	SCREEN_ChangeScreen(&sameGame_Screen_Loading);//切换屏幕
}

//游戏退出,释放资源
void SameGame_exit()
{
	dataPackage.DP_ReleasePackage(&dataPackage,0);
	sameGameRecord.Close(&sameGameRecord);
	allPicLib.Release(&allPicLib);
	DF_ReleaseMemory();
}
/*
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dynamicLoadingCore_ext.h"
#pragma arm section code = "game_reg_main"
void game_reg_main(sysCall sys_call)//游戏进出口
{
	t_sysCall = sys_call;
	game_reg(SameGame_enter,SameGame_exit);
}
#pragma arm section code
#endif
*/