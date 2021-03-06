/**********************************************************************************************************************
Logo界面
***********************************************************************************************************************/
#include "SameGame_Logo.h"
#include "SameGame_Screen.h"
#include "coolbar_game_lcd.h"
#include "dl_app_Redefine.h"
#include "../..//gif/inc/coolbar_Gif.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//游戏中logo界面初使化和加载
extern void func(int index){
	while ( true){
		if (getManagerPtr()->IsKeyDown(MF_KEY_MID))
			GAME_ServiceExit();
	}
}
int iThread = 0;
char * szFunc = "func";
void SameGame_Logo_Init(SameGameLogo * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{	
	
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,500);
	myself->windows.RenderCallBack=SameGame_Logo_Render;
	myself->windows.UpdateCallBack=SameGame_Logo_Update;
	myself->picLib=picLib;
	myself->timer = 0;
	
	myself->imgLogo=myself->picLib->GetImage(myself->picLib,"2.gif");
	
	XS_Init();
	
	XS_RegisterHostAPIFunc(3,szFunc , func);
//	XS_LoadScript(szFunc, &iThread, 10);
	XS_CallScriptFunc(3,szFunc);

	SameGame_Loading_UpdateStep();
}	





void SameGame_Logo_Render(void * param){

	SameGameLogo * myself=(SameGameLogo *)param;
	
	int ss;
	tImage * img, *img2;
	int xn;
//	char * s3s = (char*)szData;
	
	img = myself->picLib->image[myself->imgLogo];
	
// 	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(238,242,251));
// 	myself->picLib->DrawImageEx(myself->picLib,myself->imgLogo,(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgLogo))/2,
// 		(SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgLogo))/2,true,0);
// 	
	//img2 =extVmLcdManager->IMG_CreateImageFormStream(rawData, img);
//	img =extVmLcdManager->IMG_CreateImageFormStream(rawData, img);
	myself->picLib->DrawImageEx(myself->picLib,myself->imgLogo,(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgLogo))/2,
		 (SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgLogo))/2,true,1);
	GAME_RefresScreen();
	ss =  myself->picLib->CreateImage(myself->picLib, 240, 320);
 	img2 = myself->picLib->image[ss];
	

	//CoolbarGetGifInfo(0,1000,0,0);

	GAME_RefresScreen();
 	
 	myself->picLib->FillRect(myself->picLib,0,0,200,300,GAME_ToRGB(10,100,100));

	myself->picLib->SetGraphics(myself->picLib, img2);
	

	GAME_RefresScreen();
	
	
// 	extVmLcdManager->VMDrawImageEx(img,0 ,0);
	myself->picLib->SetGraphics(myself->picLib, DF_DEFAULT_GRAPHICS);
	
	GAME_RefresScreen();
//	extVmLcdManager->VMDrawStandardImageEx(img2, 0, 0, 0, 168, 56, rawData, 4586, STAND_GIF);
	myself->picLib->DrawImageEx(myself->picLib,ss, 0,0,true,1);
	GAME_RefresScreen();
	
	
}

void SameGame_Logo_Render_new(void * param)
{
	VMUINT16 fileName[100] ={0};
	VMFILE fileHandler;
	VMUINT16 demoDir[]={'k','h','i',0};
	VMUINT16 demoFile[] = {'d','0','.','d','a','t',0};
	VMUINT16  demoLen = 0;	


	int x = 0;
	int dx, dx2,ss;
	int len;
	void * pData ;
	/* Untitled1 (9/15/2011 10:18:09 PM)
   StartOffset: 00000066, EndOffset: 000009E0, Length: 0000097B */


	SameGameLogo * myself=(SameGameLogo *)param;
	tImage *img, *img2;
	unsigned short *  iData, * iData2;
	VMUINT16 filepath[50];
	unsigned char bbuf[4096];

	
// 	img = myself->picLib->image[myself->imgLogo];
// 	iData = img->data;
// 	for ( x = 0; x < 1000; x++){
// 		dx = iData[x];
// 	}
// 	ss = myself->picLib->CreateImage(myself->picLib, 1, 1);
// 	img2 = myself->picLib->image[ss];
// 	
// 	dx2 = img2->data;
// 	
// 	
// 	
// 	//GAME_RefresScreen();
// 	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(238,242,251));
// 	myself->picLib->DrawImageEx(myself->picLib,myself->imgLogo,(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgLogo))/2,
// 		(SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgLogo))/2,true,0);
// 
// 	//******
// 	
// 	//		DataInputStream dis = null;
// 
// 	if(!extVmIoManager->Vm_file_direxist(VM_FS_MMC,demoDir))//VM_FS_MMC ?¨¦¡À?
// 	{
// 		extVmIoManager->Vm_file_mkdir(VM_FS_MMC,demoDir);
// 	}
// 
// 	demoLen = extVmUcs2StrManager->VmutStrlenUcs2((VMUINT16 *)demoDir);
// 	vm_memset(fileName,0,sizeof(fileName));
// 	extVmUcs2StrManager->VmutStrcatUcs2(fileName,demoDir);  
// 	fileName[demoLen] = L'\\';//
// 	demoLen++;
//  	extVmUcs2StrManager->VmutStrcatUcs2((fileName+demoLen),demoFile);
// // 
// // 			extVmSysManager->GetCoolbarDirPath(filepath);
// // 	 		len = extVmUcs2StrManager->VmutStrlenUcs2(filepath);
// // 	 		filepath[len] = VM_PATH_SEPARATOR;
// // 	 		extVmUcs2StrManager->VmutStrcatUcs2(filepath , "..\a.d");
// // 
// // 	 		fileHandler = extVmIoManager->Vm_file_open(VM_FS_MMC,fileName,"w+");//???t¡À¡ê¡ä?
// // 	 		if(fileHandler >= 0)
// // 	 			extVmIoManager->Vm_file_close(fileHandler);
// 
// 
// 	fileHandler = extVmIoManager->Vm_file_open(VM_FS_MMC,fileName,"w+");
// 	if(fileHandler >= 0)
// 	{
// 		//vm_memset(bbuf,0,4096);
// 		
// 		len = extVmIoManager->Vm_file_write((void*)img->data, img->data,fileHandler);
// 		extVmIoManager->Vm_file_close(fileHandler); 		
// 	}
// 	
// 
// 
// // 	GAME_RefresScreen();
// 	pData = malloc(img->width * img->height * 2);
// 	tRes.data = pData;
	
// 	pData = malloc(1* 1* 2);
// 	
// 	tRes.data = (VMINT16*)img->data;
// 	tResource
	
 	
 	GAME_RefresScreen();
// 
// 	getManagerPtr()->TIME_Sleep(10000);
// 	x = 0;s
}
//游戏中logo界面按键
void SameGame_Logo_Update(void * param)
{
	SameGameLogo * myself = (SameGameLogo *)param;
	myself->timer++;
	return;
	if (getManagerPtr()->IsKeyDown(MF_KEY_ANY)||SCREEN_IsPointerDown()||myself->timer == 30 )
	{
		SameGame_Title_ChangeState(SAMEGAME_STATE_TITLEMENU);
	}
}

