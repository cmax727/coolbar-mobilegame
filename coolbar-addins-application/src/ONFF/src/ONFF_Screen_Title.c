/************************************************************************************************
2010-5-20 zhaoliangqi
主菜单画面
***********************************************************************************************/
#include "ONFF_Screen.h"
#include "ONFF_Help.h"
#include "ONFF_Title.h"
#include "ONFF_TitleMenu.h"
#include "ONFF_About.h"
#include "ONFF_Set.h"
#include "ONFF_Pay.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
 
extern void ONFF_Title_init(void);
extern void ONFF_Title_Destroy(void);
extern void ONFF_Title_Logic(void);
extern void ONFF_Title_Render(tGraphics * g);
extern void ONFF_Title_Pause(void);
extern void ONFF_Title_Resume(void);
extern void ONFF_Title_LoadResource(void);
extern void ONFF_Title_ChangeState(gm_s16 state);

extern void ONFF_Loading_LoadResource(void);
extern void ONFF_Loading_Init(void);
extern void ONFF_Loading_Destory(void);
extern void ONFF_Loading_Logic(void);
extern void ONFF_Loading_Render(tGraphics *g);
extern void ONFF_Loading_Pause(void);
extern void ONFF_Loading_Resume(void);

extern void ONFF_InGame_Init(void);
extern void ONFF_InGame_Destory(void);
extern void ONFF_InGame_Logic(void);
extern void ONFF_InGame_Render(tGraphics *g);
extern void ONFF_InGame_Pause(void);
extern void ONFF_InGame_Resume(void);
extern void ONFF_InGame_LoadResource(void);


Manager * manager_my;
MemoryBlock *memoryblock_my;

gm_s16 oNFFTitleState;  
ONFFTitle oNFFTitle;
ONFFTitleMenu oNFFTitleMenu;
ONFF_Help oNFFTitleHelp;
ONFF_About oNFFTitleAbout;
ONFF_Pay oNFFTitilePay;
ONFFSet oNFFTitleSet;

gm_s8  gamePlayerlife = 4;
gm_s8  gamePlayerbomb = 2;
gm_s8  gameMusic = 0;

static DF_DataPackage dataPackage;
tScreen ONFF_Screen_Title;

void ONFF_Title_init(void)
{
}
void ONFF_Title_Destroy(void)
{
	vmdlReleaseTextBox(&oNFFTitleHelp.textBox);
	vmdlReleaseTextBox(&oNFFTitleAbout.textBox);
	vmdlReleaseTextBox(&oNFFTitilePay.textBox);
	oNFFPicLib.Release(&oNFFPicLib);
}
void ONFF_Title_Logic(void)
{
	switch (oNFFTitleState)
	{
	case ONFF_TITLE_STATE_SHOW_TITLE:
		oNFFTitle.windows.DF_Update(&oNFFTitle.windows);
		break;
	case ONFF_TITLE_STATE_MENU:
		oNFFTitleMenu.windows.DF_Update(&oNFFTitleMenu.windows);
		break;
	case ONFF_TITLE_STATE_HELP:
		oNFFTitleHelp.windows.DF_Update(&oNFFTitleHelp.windows);
	    break;
	case ONFF_TITLE_STATE_ABOUT:
		oNFFTitleAbout.windows.DF_Update(&oNFFTitleAbout.windows);
		break;	
	case ONFF_TITLE_STATE_SET:
		oNFFTitleSet.windows.DF_Update(&oNFFTitleSet.windows);
		break;
	case ONFF_TITLE_STATE_PAY:
		oNFFTitilePay.windows.DF_Update(&oNFFTitilePay.windows);
		break;
	}
}
void ONFF_Title_Render(tGraphics * g)
{
	switch (oNFFTitleState)
	{
	case ONFF_TITLE_STATE_SHOW_TITLE:
		oNFFTitle.windows.DF_Render(&oNFFTitle.windows);
		break;
	case ONFF_TITLE_STATE_MENU:
		oNFFTitleMenu.windows.DF_Render(&oNFFTitleMenu.windows);
		break;
	case ONFF_TITLE_STATE_HELP:
		oNFFTitleHelp.windows.DF_Render(&oNFFTitleHelp.windows);
		break;
	case ONFF_TITLE_STATE_ABOUT:
		oNFFTitleAbout.windows.DF_Render(&oNFFTitleAbout.windows);
		break;
	case ONFF_TITLE_STATE_SET:
		oNFFTitleSet.windows.DF_Render(&oNFFTitleSet.windows);
		break;
	case ONFF_TITLE_STATE_PAY:
		oNFFTitilePay.windows.DF_Render(&oNFFTitilePay.windows);
		break;
	}
	getManagerPtr()->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}
void ONFF_Title_Pause(void)
{

}
void ONFF_Title_Resume(void)
{
	ONFF_Title_ChangeState(oNFFTitleState);
}
void ONFF_Title_LoadResource()
{
	Rect ur;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
	initDFPictureLibrary(&oNFFPicLib,10);
	initONFFTitle(&oNFFTitle,ur,&oNFFPicLib);
	initONFFTitleMenu(&oNFFTitleMenu,ur,&oNFFPicLib);
	initONFFHelp(&oNFFTitleHelp,ur,&oNFFPicLib);
	initONFFAbout(&oNFFTitleAbout,ur,&oNFFPicLib);
	initONFFSet(&oNFFTitleSet,ur,&oNFFPicLib);
	initONFFPay(&oNFFTitilePay,ur,&oNFFPicLib);
}
void ONFF_Title_ChangeState(gm_s16 state)
{
	oNFFTitleState=state;
	switch (oNFFTitleState)
	{
	case ONFF_TITLE_STATE_SHOW_TITLE:
		DF_SendMessage(&oNFFTitle.windows,DF_WINDOWS_MSG_INVALITE,&oNFFTitle.windows.DF_Windows_Rect);
		break;
	case ONFF_TITLE_STATE_MENU:
		DF_SendMessage(&oNFFTitleMenu.windows,DF_WINDOWS_MSG_INVALITE,&oNFFTitleMenu.windows.DF_Windows_Rect);
	    break;
	case ONFF_TITLE_STATE_HELP:
		DF_SendMessage(&oNFFTitleHelp.windows,DF_WINDOWS_MSG_INVALITE,&oNFFTitleHelp.windows.DF_Windows_Rect);
	    break;
	case ONFF_TITLE_STATE_ABOUT:
		DF_SendMessage(&oNFFTitleAbout.windows,DF_WINDOWS_MSG_INVALITE,&oNFFTitleAbout.windows.DF_Windows_Rect);
		break;
	case ONFF_TITLE_STATE_PAY:
		DF_SendMessage(&oNFFTitilePay.windows,DF_WINDOWS_MSG_INVALITE,&oNFFTitilePay.windows.DF_Windows_Rect);
		break;
	}
}

void ONFF_enter(void)
{
#ifdef GAME_240_320
	DF_InitMemory(150*1024);	
#endif
#ifdef GAME_176_220
	DF_InitMemory(140*1024);
#endif
	initMemoryBlock(getMemoryBlockPtr(),1024*50);
	initDreamFactoryEngine();
	initDFDataPackage(&dataPackage,5);
	dataPackage.DP_LoadPackage(&dataPackage,0);
#ifdef WIN32
	dataPackage.DP_DoLoading(&dataPackage,ONFF_TResource_Data,1);
#else
	dataPackage.DP_DoLoading(&dataPackage,ONFF_TResource_Data,1);
#endif
	DF_SetDataPackage(&dataPackage);

	memoryblock_my=getMemoryBlockPtr();

	manager_my=getManagerPtr();
    initManager(manager_my);
	
	initDFPictureLibrary(&oNFFPicLib,20);
	oNFFTitleState=ONFF_TITLE_STATE_SHOW_TITLE;
	oNFFLoadingStep=0;
	oNFFLoadingStepTotal=16;

	vmtScreenInit(&ONFF_Screen_InGame,
	ONFF_InGame_Init,
	ONFF_InGame_Destory,
	ONFF_InGame_Logic,
	ONFF_InGame_Render,
	ONFF_InGame_Pause,
	ONFF_InGame_Resume,
	ONFF_InGame_LoadResource
	);
	
	vmtScreenInit(&ONFF_Screen_Loading,
	ONFF_Loading_Init,
	ONFF_Loading_Destory,
	ONFF_Loading_Logic,
	ONFF_Loading_Render,
	ONFF_Loading_Pause,
	ONFF_Loading_Resume,
	ONFF_Loading_LoadResource
	);
	
	vmtScreenInit(&ONFF_Screen_Title,
	ONFF_Title_init,
	ONFF_Title_Destroy,
	ONFF_Title_Logic,
	ONFF_Title_Render,
	ONFF_Title_Pause,
	ONFF_Title_Resume,
	ONFF_Title_LoadResource
	);
	ONFF_Screen_Next=&ONFF_Screen_Title;
	SCREEN_ChangeScreen(&ONFF_Screen_Loading);

}
void ONFF_exit()
{
	dataPackage.DP_ReleasePackage(&dataPackage,0);
	oNFFPicLib.Release(&oNFFPicLib);
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
void game_reg_main(sysCall sys_call)
{
	t_sysCall = sys_call;
	game_reg(ONFF_enter,ONFF_exit);
}
#pragma arm section code
#endif
*/