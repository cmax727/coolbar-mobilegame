/************************************************************************************************
2010-5-20 zhaoliangqi
主菜单画面
***********************************************************************************************/
#include "CatLoveDog_Screen.h"
#include "CatLoveDog_Help.h"
#include "CatLoveDog_Title.h"
#include "CatLoveDog_TitleMenu.h"
#include "CatLoveDog_Pay.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
 
extern void CatLoveDog_Title_init(void);
extern void CatLoveDog_Title_Destroy(void);
extern void CatLoveDog_Title_Logic(void);
extern void CatLoveDog_Title_Render(tGraphics * g);
extern void CatLoveDog_Title_Pause(void);
extern void CatLoveDog_Title_Resume(void);
extern void CatLoveDog_Title_LoadResource(void);
extern void CatLoveDog_Title_ChangeState(gm_s16 state);

extern void CatLoveDog_Loading_LoadResource(void);
extern void CatLoveDog_Loading_Init(void);
extern void CatLoveDog_Loading_Destory(void);
extern void CatLoveDog_Loading_Logic(void);
extern void CatLoveDog_Loading_Render(tGraphics *g);
extern void CatLoveDog_Loading_Pause(void);
extern void CatLoveDog_Loading_Resume(void);

extern void CatLoveDog_InGame_Init(void);
extern void CatLoveDog_InGame_Destory(void);
extern void CatLoveDog_InGame_Logic(void);
extern void CatLoveDog_InGame_Render(tGraphics *g);
extern void CatLoveDog_InGame_Pause(void);
extern void CatLoveDog_InGame_Resume(void);
extern void CatLoveDog_InGame_LoadResource(void);


Manager * manager_my;
MemoryBlock *memoryblock_my;

gm_s16 CatLoveDogTitleState;  
CatLoveDogTitle catLoveDogTitle;
CatLoveDogTitleMenu catLoveDogTitleMenu;
CatLoveDog_Help catLoveDogTitleHelp;
CatLoveDog_Pay catLoveDogTitilePay;

static DF_DataPackage dataPackage;
tScreen CatLoveDog_Screen_Title;

void CatLoveDog_Title_init(void)
{

}
void CatLoveDog_Title_Destroy(void)
{
	vmdlReleaseTextBox(&catLoveDogTitleHelp.textBox);
	vmdlReleaseTextBox(&catLoveDogTitilePay.textBox);
	catLoveDogPicLib.Release(&catLoveDogPicLib);
}
void CatLoveDog_Title_Logic(void)
{
	switch (CatLoveDogTitleState)
	{
	case CatLoveDog_TITLE_STATE_SHOW_TITLE:
		catLoveDogTitle.windows.DF_Update(&catLoveDogTitle.windows);
		break;
	case CatLoveDog_TITLE_STATE_MENU:
		catLoveDogTitleMenu.windows.DF_Update(&catLoveDogTitleMenu.windows);
		break;
	case CatLoveDog_TITLE_STATE_HELP:
		catLoveDogTitleHelp.windows.DF_Update(&catLoveDogTitleHelp.windows);
	    break;
	case CatLoveDog_TITLE_STATE_PAY:
		catLoveDogTitilePay.windows.DF_Update(&catLoveDogTitilePay.windows);
		break;
	}
}
void CatLoveDog_Title_Render(tGraphics * g)
{
	switch (CatLoveDogTitleState)
	{
	case CatLoveDog_TITLE_STATE_SHOW_TITLE:
		catLoveDogTitle.windows.DF_Render(&catLoveDogTitle.windows);
		break;
	
	case CatLoveDog_TITLE_STATE_MENU:
		catLoveDogTitleMenu.windows.DF_Render(&catLoveDogTitleMenu.windows);
		break;
	
	case CatLoveDog_TITLE_STATE_HELP:
		catLoveDogTitleHelp.windows.DF_Render(&catLoveDogTitleHelp.windows);
		break;
	case CatLoveDog_TITLE_STATE_PAY:
		catLoveDogTitilePay.windows.DF_Render(&catLoveDogTitilePay.windows);
		break;
	}
	getManagerPtr()->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}
void CatLoveDog_Title_Pause(void)
{

}
void CatLoveDog_Title_Resume(void)
{
	CatLoveDog_Title_ChangeState(CatLoveDogTitleState);
}
void CatLoveDog_Title_LoadResource()
{
	Rect ur;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
	initDFPictureLibrary(&catLoveDogPicLib,10);
	
	initCatLoveDogTitle(&catLoveDogTitle,ur,&catLoveDogPicLib);
	initCatLoveDogTitleMenu(&catLoveDogTitleMenu,ur,&catLoveDogPicLib);	
	initCatLoveDogHelp(&catLoveDogTitleHelp,ur,&catLoveDogPicLib);
	initCatLoveDog_Pay(&catLoveDogTitilePay,ur,&catLoveDogPicLib);
}
void CatLoveDog_Title_ChangeState(gm_s16 state)
{
	CatLoveDogTitleState=state;
	switch (CatLoveDogTitleState)
	{
	case CatLoveDog_TITLE_STATE_SHOW_TITLE:
		DF_SendMessage(&catLoveDogTitle.windows,DF_WINDOWS_MSG_INVALITE,&catLoveDogTitle.windows.DF_Windows_Rect);
		break;
	case CatLoveDog_TITLE_STATE_MENU:
		DF_SendMessage(&catLoveDogTitleMenu.windows,DF_WINDOWS_MSG_INVALITE,&catLoveDogTitleMenu.windows.DF_Windows_Rect);
	    break;
	case CatLoveDog_TITLE_STATE_HELP:
		DF_SendMessage(&catLoveDogTitleHelp.windows,DF_WINDOWS_MSG_INVALITE,&catLoveDogTitleHelp.windows.DF_Windows_Rect);
	    break;
	case CatLoveDog_TITLE_STATE_PAY:
		DF_SendMessage(&catLoveDogTitilePay.windows,DF_WINDOWS_MSG_INVALITE,&catLoveDogTitilePay.windows.DF_Windows_Rect);
		break;
	}
}

void CatLoveDog_enter(void)
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
	dataPackage.DP_DoLoading(&dataPackage,CatLoveDog_TResource_Data,1);
#else
	dataPackage.DP_DoLoading(&dataPackage,CatLoveDog_TResource_Data,1);
#endif
	DF_SetDataPackage(&dataPackage);

	memoryblock_my=getMemoryBlockPtr();

	manager_my=getManagerPtr();
    initManager(manager_my);
	
	initDFPictureLibrary(&catLoveDogPicLib,20);
	CatLoveDogTitleState=CatLoveDog_TITLE_STATE_SHOW_TITLE;
	catLoveDogLoadingStep=0;
	catLoveDogLoadingStepTotal=16;

	vmtScreenInit(&CatLoveDog_Screen_InGame,
	CatLoveDog_InGame_Init,
	CatLoveDog_InGame_Destory,
	CatLoveDog_InGame_Logic,
	CatLoveDog_InGame_Render,
	CatLoveDog_InGame_Pause,
	CatLoveDog_InGame_Resume,
	CatLoveDog_InGame_LoadResource
	);
	
	vmtScreenInit(&CatLoveDog_Screen_Loading,
	CatLoveDog_Loading_Init,
	CatLoveDog_Loading_Destory,
	CatLoveDog_Loading_Logic,
	CatLoveDog_Loading_Render,
	CatLoveDog_Loading_Pause,
	CatLoveDog_Loading_Resume,
	CatLoveDog_Loading_LoadResource
	);
	
	vmtScreenInit(&CatLoveDog_Screen_Title,
	CatLoveDog_Title_init,
	CatLoveDog_Title_Destroy,
	CatLoveDog_Title_Logic,
	CatLoveDog_Title_Render,
	CatLoveDog_Title_Pause,
	CatLoveDog_Title_Resume,
	CatLoveDog_Title_LoadResource
	);
	CatLoveDog_Screen_Next=&CatLoveDog_Screen_Title;
	SCREEN_ChangeScreen(&CatLoveDog_Screen_Loading);

}
void CatLoveDog_exit()
{
	dataPackage.DP_ReleasePackage(&dataPackage,0);
	catLoveDogPicLib.Release(&catLoveDogPicLib);
	DF_ReleaseMemory();

}

/*
#ifndef WIN32
VmMainFunction vMGetMainEnterFuct(void)   //函数名（函数指针）固定唯一，不可改变。
{
    return CatLoveDog_enter;              //实际的入口函数
}

VmMainFunction vMGetMainExitFuct(void)    //同上
{
    return CatLoveDog_exit;               //实际的退出函数
}
#endif 
*/
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dynamicLoadingCore_ext.h"
#pragma arm section code = "game_reg_main"
void game_reg_main(sysCall sys_call)
{
	t_sysCall = sys_call;
	game_reg(CatLoveDog_enter,CatLoveDog_exit);
}
#pragma arm section code
#endif
