#ifdef COOLBAR_DYNAMIC_LOADING
#include "vmDlType.h"
#include "dynamicLoadingCore_ext.h"
#include "dl_app_Redefine.h"

gm_TRACE_fuc  gm_TRACE_T=PNULL;
gm_TRACE_fuc  gm_TRACE_TOld=PNULL;

static VmManager * extVmManager_p=PNULL;

VmIoManager * extVmIoManager=PNULL;
VmLcdManager  * extVmLcdManager =PNULL;
VmSysManager * extVmSysManager =PNULL;
VmTimeManager * extVmTimeManager =PNULL;
VmCtrlManager  * extVmCtrlManager =PNULL;
VmMemoryManager * extVmMemoryManager =PNULL;
VmBillingManager  * extVmBillingManager =PNULL;
VmScreenManager  * extVmScreenManager =PNULL;
VmDFScriptManager * extVmDFScriptManager=PNULL;
VmGameLcdManager * extVmGameLcdManager=PNULL;
VmGameUtilManager * extVmGameUtilManager=PNULL;
VmDFEnginelManager * extVmDFEnginelManager=PNULL;
VmAudioManager* extVmAudioManager=PNULL;
VmNetManager  * extVmNetManager =PNULL;
VmNetAppManager * extVmNetAppManager =PNULL;
Manager * extOldGameManager=PNULL;
VmGSensorManager* extVmGSensorManager=PNULL;
VmUcs2StrManager* extVmUcs2StrManager =PNULL;

sysCall t_sysCall = NULL;
/****************************************************************************
*
****************************************************************************/ 
typedef       void (*TScreenInit)(void );    
typedef       void (*TScreenDestory)(void );    
typedef       void (*TScreenLogic)(void );    
typedef       void (*TScreenRender)(VmGraphics *g); 
typedef       void (*TScreenPause)(void );    
typedef       void (*TScreenResume)(void );    
typedef       void (*TScreenLoadResource)(void ); //回掉资源加载

void game_reg(PFunction mainFun,PFunction exitFun)
{
       VmSysCallRegParam *regParam_p=PNULL;
	if(t_sysCall!=PNULL)
	{
		regParam_p= (VmSysCallRegParam *)t_sysCall;
	       regParam_p->mainFun=mainFun;
		regParam_p->exitFun=exitFun; 
		gm_TRACE_TOld=regParam_p->gmTrace_P;
    gm_TRACE_T = regParam_p->gmTrace_P;
		extVmManager_p=regParam_p->vmManager_p;
		extVmIoManager=extVmManager_p->VMGetIoManager();
	       extVmLcdManager=extVmManager_p->VMGetLcdManager();
		extVmSysManager=extVmManager_p->VMGetSysManager();
		extVmTimeManager=extVmManager_p->VMGetTimeManager();
		extVmCtrlManager=extVmManager_p->VMGetCtrlManager();
		extVmMemoryManager=extVmManager_p->VMGetMemoryManager();
		extVmBillingManager=extVmManager_p->VMGetBillingManager();
		extVmScreenManager=extVmManager_p->VMGetScreenManager();  
		extVmDFScriptManager=extVmManager_p->VMGetDFScriptManager();
		extVmGameLcdManager=extVmManager_p->VMGetGameLcdManager();
		extVmGameUtilManager=extVmManager_p->VMGetGameUtilManager();
		extVmDFEnginelManager=extVmManager_p->VMGetDFEnginelManager();
		extOldGameManager=(Manager *)extVmManager_p->VMGetGameManagerOld();
		extVmAudioManager=extVmManager_p->VMGetAudioManager();
    extVmNetManager = extVmManager_p->VMGetNetManager();
    extVmNetAppManager=extVmManager_p->VMGetNetAppManager();
    extVmGSensorManager=extVmManager_p->vMGetGSensorManager();
    extVmUcs2StrManager = extVmManager_p->VMGetUcs2StrManager();
	}
	else
	{
	  while(1);//死机
	}
}

void vmdlReleaseTextBox(TextBox * myself)
{
   if(myself->Release!=PNULL)
   {
   	myself->Release(myself);
   }
   	
}

void Game_SetSysCall(void *syscall)
{
  t_sysCall = syscall;
}

void	GAME_ServiceExit(void)
{
    extVmSysManager->VmEnterWinClose();
}
tImage* IMG_CreateImageFormResRgb(tResource_RGB res)
{
    tResource tempRes={0};
    tempRes.data=	(gm_u8*)res.data;
    return extOldGameManager->CreateImage(tempRes);
}
gm_u16 IMG_GetHeight(tImage *pImage)
{
    return extOldGameManager->IMG_GetHeight(pImage);
}
gm_u16 IMG_GetWidth(tImage *pImage)
{
      return extOldGameManager->IMG_GetWidth(pImage);
}
void	GAME_SetClip(tGraphics *pG,gm_u16 x,gm_u16 y,gm_u16 width,gm_u16 height)
{
     extOldGameManager->SetClip(x,y,width,height);
}
tRGB GAME_ToRGB(const gm_u8 r,const  gm_u8 g,const  gm_u8 b)
{
   return extOldGameManager->GAME_ToRGB(r,g,b);
}
void	GAME_DrawLine(tGraphics* pG, gm_s16 x1, gm_s16 y1, gm_s16 x2, gm_s16 y2, tRGB color)
{
    extOldGameManager->GAME_DrawLine(pG,x1,y1,x2,y2,color);
}
void	GAME_DrawRect(tGraphics* pG, gm_s16 x, gm_s16 y, gm_s16 width, gm_s16 height, tRGB color)
{
     extOldGameManager->GAME_DrawRect(pG,x,y,width,height,color);
}
void	GAME_FillRect(tGraphics* pG, gm_s16 x, gm_s16 y,gm_u16 width,gm_u16 height, tRGB color)
{
    extOldGameManager->GAME_FillRect(pG,x,y,width,height,color);
}
tImage * IMG_CreateImageFormRes(tResource res)
{
       return extOldGameManager->CreateImage(res);
}
void IMG_Destory(tImage* pImage)
{
     extOldGameManager->ReleaseImage(pImage);
}
void GAME_DrawFullScreen(tImage* pImage)
{
      extOldGameManager->DrawFullScreen(pImage);
}

void GAME_DrawImageWithClip(tImage* pImage,short innerX,short innerY,
									short int w,short int h,short int x, short int y)
{
       extOldGameManager->DrawImage( pImage, innerX, innerY,w, h, x,  y);
}
void GAME_DrawImageClipAndAlpha(tImage* pImage,short innerX,short innerY,
										short int w,short int h,short int x, short int y)
{
      extOldGameManager->DrawImageEx( pImage, innerX, innerY,w, h, x,  y);
}
void	GAME_DrawImageNumber(tImage *pImage,gm_s32 number,
									gm_s16 width,gm_s16 height,
									gm_s16 distance,gm_s16 x,gm_s16 y,gm_u8 align)
{
      extOldGameManager->DrawNumber(pImage, number, width, height, distance, x, y, align);
}
void	GAME_DrawUI(tImage * pImage,gm_s16 x,gm_s16 y,gm_s16 width,gm_s16 height,gm_s16 cellNum)
{
      extOldGameManager->DrawUI( pImage, x, y, width, height,cellNum);
}
void	GAME_DrawUIHorizontal(tImage * pImage,gm_s16 x,gm_s16 y,gm_s16 width)
{
      extOldGameManager->DrawUIHorizontal( pImage, x, y, width);
}
void	GAME_DrawUISingleRepeat(tImage * pImage,gm_s16 x,gm_s16 y,gm_s16 width,gm_s16 height)
{
      extOldGameManager->DrawUISingleRepeat( pImage, x, y, width, height);
}
void	GAME_DrawUIFourXRepeat(tImage * pImage,gm_s16 x,gm_s16 y,gm_s16 width,gm_s16 height)
{
      extOldGameManager->DrawUIFourXRepeat( pImage, x, y, width, height);
}
void GAME_DrawString_ToChinese(tGraphics* pG, gm_u8* str, gm_s16 x, gm_s16 y,gm_u16 w,gm_u16 h,tRGB color) 
{
      extOldGameManager->GAME_DrawString_ToChinese(pG,  str,  x,  y, w, h, color);
}

/******************************************************************
* FUNCTION	
*   GFX_DrawString_Chinese
****************************************************************************/ 
void GAME_DrawString_Chinese(char * str,gm_s16 length, gm_s16 x, gm_s16 y, gm_u32 color)
{
      extOldGameManager->DrawString(str,length,x,y,color);
}
gm_u16	GAME_GetStringWidth(char* str)
{
     return extVmLcdManager->VMGetStringWidth( str);
}
gm_u16 GAME_GetStringHeight(char* str)
{
     return extVmLcdManager->VMGetStringHeight( str);
}
int GAME_GetFontWidth()
{
     return extOldGameManager->GAME_GetFontWidth();
}
int GAME_GetFontHeight()
{
     return extOldGameManager->GAME_GetFontHeight();
}
void GAME_UpdateRectExt(tGraphics* pG,short int x, short int y,short int update_width,short int update_height)
{

}
void GAME_DrawGifImage(tGraphics* pG, tImage* pImage, short int x, short int y,short int framenum)
{
        if(pImage!=PNULL)
	{
	   GAME_DrawImageClipAndAlpha(pImage,0,0,pImage->width,pImage->height,x,y);
	}
}
void GAME_DrawImage(tGraphics* pG, tImage* pImage, short int x, short int y,short int image_width,short int image_height)
{
        if(pImage!=PNULL)
	{
	        GAME_DrawImageClipAndAlpha(pImage,0,0,pImage->width,pImage->height,x,y);
	}
}
void GAME_DrawImageNoAlpha(tGraphics* pG,tImage* pImage, short int x, short int y,short int image_width,short int image_height)
{
       if(pImage!=PNULL)
	{
	     GAME_DrawImageWithClip(pImage,0,0,pImage->width,pImage->height,x,y);
	}
}
void GAME_DrawImageBackGround(tGraphics* pG,tImage* pImage,
										gm_s16 x,gm_s16 y,
										short int image_width,short int image_height)
{
        if(pImage!=PNULL)
	{
	       GAME_DrawImageWithClip(pImage,0,0,pImage->width,pImage->height,x,y);
	}
}
void	GAME_DrawImageFromClip(tGraphics* pG, tImage *pImage, 
									gm_u16 x, gm_s16 y,
									gm_u16 imgWidth,gm_u16 imgHeight,
									gm_s16 clip_x, gm_s16 clip_y,
									gm_u16 width,gm_u16 height,
									gm_bool isAlpha,gm_u16 transform)
{
     if(pImage!=PNULL)
	{
		if(isAlpha)
		{
		     GAME_DrawImageClipAndAlpha(pImage,clip_x,clip_y,width,height,x,y);
		}
		else
		{
		     GAME_DrawImageWithClip(pImage,clip_x,clip_y,width,height,x,y);
		}
	}
}
gm_bool Storage_Date(char* filename,gm_u8* pBuffer, int nLenBuffer,gm_bool IsRead,gm_bool isPhone)
{
     return extVmGameUtilManager->Storage_Date(filename, pBuffer,  nLenBuffer, IsRead, isPhone);
}
void*   GAME_malloc(int size)
{
     return extOldGameManager->GAME_malloc( size);
}
void	GAME_free(void *pMem)
{
      extOldGameManager->GAME_free(pMem);
}
void* GAME_Image_malloc(int size)
{
     return extOldGameManager->GAME_Image_malloc( size);
}
void GAME_Image_free(void *pMem)
{
      extOldGameManager->GAME_Image_free(pMem);
}

gm_u16 MF_GetBlackDay(void)
{
     return extOldGameManager->MF_GetBlackDay();
}
gm_u16 MF_GetBlackMonth(void)
{
     return extOldGameManager->MF_GetBlackMonth();
}
gm_u16	MF_GetBlackYear(void)
{
     return extOldGameManager->MF_GetBlackYear();
}
unsigned long TIME_GetTime(void)
{
     return extOldGameManager->TIME_GetTime();
}
int MF_SDL_GetTicks(void )
{
     return TIME_GetTime( );
}
void GAME_RefresScreen(void)
{
       extOldGameManager->GAME_RefresScreen();
}
void initManager(Manager * manager)
{
      extVmManager_p->VMInitGameManagerOld((void *)manager);
}
gm_u8* GAME_ZhiFei(gm_u8 mMoney)
{
     return extOldGameManager->GAME_ZhiFei( mMoney);
}
gm_bool CdRect(int sx1, int sy1, int sx2, int sy2, int dx1, int dy1, int dx2, int dy2) 
{
     return extOldGameManager->CdRect( sx1,  sy1,  sx2,  sy2,  dx1,  dy1,  dx2,  dy2) ;
}
gm_bool CdRectPoint( int sx1, int sy1, int sx2, int sy2,  int dx, int dy) 
{
     return extOldGameManager->CdRectPoint(  sx1,  sy1,  sx2,  sy2,   dx,  dy) ;
}
gm_bool CdRect2( int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh) 
{
     return extOldGameManager->CdRect2(  sx,  sy,  sw,  sh,  dx,  dy,  dw,  dh); 
}
gm_bool CdRectPoint2(int sx, int sy, int sw, int sh, int dx, int dy) 
{
     return extOldGameManager->CdRectPoint2( sx,  sy,  sw,  sh,  dx,  dy) ;
}
gm_s16 Abs(gm_s16 n)
{
     return extOldGameManager->Abs(n);
}
gm_s16 Max(gm_s16 a, gm_s16 b)
{
     return extOldGameManager->Max( a,  b);
}
gm_s16 Min(gm_s16 a, gm_s16 b)
{
     return extOldGameManager->Min( a,  b);
}
void MF_ItoIndex(unsigned long int num, unsigned char* pDestArray)
{
      
}
gm_s16 Random(gm_s16 begin, gm_s16 end)
{
     return extOldGameManager->Random( begin,  end);
}
gm_s32 Sqrt(gm_s32 num) 
{
     return extOldGameManager->Sqrt( num) ;
}
void initMemoryBlock(MemoryBlock * myself,gm_s32 size)
{
      extOldGameManager->initMemoryBlock(myself,size);
}
void* MF_MemoryBlock_Malloc(MemoryBlock* myself, gm_s32 size)
{
     return myself->Malloc(myself,size);
}
void MF_MemoryBlock_Reset(MemoryBlock * myself)
{
      myself->Reset( myself);
}
void MF_MemoryBlock_Release(MemoryBlock * myself)
{
      myself->Release( myself);
}
void initListener(Listener * myself,MemoryBlock * memoryBlock,gm_s16 maxRepaint)
{
      extVmGameLcdManager->initListener( myself, memoryBlock, maxRepaint);
}
void releaseListener(Listener * myself)
{
      myself->releaseListener( myself);
}
void talkRepaintListener(Listener * myself,gm_s16 x,gm_s16 y,gm_s16 w,gm_s16 h)
{
   myself->talkRepaintListener(myself, x, y, w, h);
}
void initTalker(Talker * myself,Listener* talkTo)
{
      talkTo->initTalker((void *)myself, talkTo);
}
void initSprite(Sprite * myself,gm_s16 x,gm_s16 y)
{
      extOldGameManager->initSprite(myself, x, y);
}
void releaseSprite(Sprite * myself)
{
    
}
void SCREEN_ChangeScreen(tScreen* next)
{
      extOldGameManager->SCREEN_ChangeScreen(next);
}
gm_bool SCREEN_IsKeyDown(unsigned long int TheKey) 
{
     return extOldGameManager->IsKeyDown( TheKey) ;
}
/*gm_bool SCREEN_IsKeyUp(unsigned long int TheKey) 
{
     return extOldGameManager->SCREEN_IsKeyUp( TheKey) ;

}*/
gm_bool SCREEN_IsKeyHold(unsigned long int TheKey) 
{
     return extOldGameManager->IsKeyHold( TheKey) ;
}
gm_bool SCREEN_IsPointerHold(void) 
{
     return extOldGameManager->SCREEN_IsPointerHold() ;
}
gm_bool SCREEN_IsPointerDown(void) 
{
     return extOldGameManager->SCREEN_IsPointerDown() ;
}
gm_bool SCREEN_IsPointerUp(void) 
{
     return extOldGameManager->SCREEN_IsPointerUp() ;
}
gm_bool SCREEN_IsPointerDrag(void) 
{
     return extOldGameManager->SCREEN_IsPointerDrag() ;
}
short int SCREEN_GetPointerX(void)
{
     return extOldGameManager->SCREEN_GetPointerX();
}
short int SCREEN_GetPointerY(void)
{
     return extOldGameManager->SCREEN_GetPointerY();
}
MemoryBlock* getMemoryBlockPtr(void)
{
     return extVmMemoryManager->mF_GetGMemoryBlockPtr();
}
Manager* getManagerPtr(void)
{
     return extOldGameManager;
}
gm_u16 * Game_GetLCDBuffer(void )
{
     return extOldGameManager->Game_GetLCDBuffer( );
}
gm_u8* GetStreamDataFormRes(tResource res)
{
     return extOldGameManager->GetStreamDataFormRes( res);
}
/*void GAME_EnableDrag(unsigned char enable)
{
     return extOldGameManager->GAME_EnableDrag( enable);
}*/
void GAME_SetKeyEnable(unsigned char  enable)
{
     //return extOldGameManager->GAME_SetKeyEnable(   enable);
}
void initTextBox(TextBox * myself,gm_s16 memorySize,gm_s16 x,gm_s16 y,gm_s16 w,gm_s16 h)
{
      extOldGameManager->initTextBox( myself, memorySize, x, y, w, h);
}
gm_s32 getTextLine(char * text,gm_s32 showWidth)
{
     return extVmGameLcdManager->getTextLine(text, showWidth);
}
int  GAME_GetFontWidth_char(void)
{
     return extOldGameManager->GAME_GetFontWidth_char();
}
int  GAME_GetFontHeight_char(void)
{
     return extOldGameManager->GAME_GetFontHeight_char();
}
void initDFPictureLibrary(DF_PictureLibrary * myself,int maxImageNum)
{
      extOldGameManager->initDFPictureLibrary( myself, maxImageNum);
}
void DF_SendMessage(DF_Windows * target,short message,void * param)
{
      target->DF_SendMessage( target, message, param);
}
void initDreamFactoryEngine(void)
{
      extOldGameManager->initDreamFactoryEngine();
}
void DF_SetDataPackage(DF_DataPackage * pkg)
{
      extOldGameManager->DF_SetDataPackage( pkg);
}
DF_DataPackage * DF_GetDataPackage(void)
{
     return extOldGameManager->DF_GetDataPackage();
}
gm_s16 DF_File_ReadShort(DF_FILE  file)
{
     return extOldGameManager->DF_File_ReadShort(  file);
}

gm_s32 DF_File_ReadInt(DF_FILE file)
{
     return extOldGameManager->DF_File_ReadInt( file);
}
void DF_ReadStringEx(char ** Des,char* Src,int * pointer)
{
      extOldGameManager->DF_ReadStringEx( Des, Src, pointer);
}

char * DF_File_ReadString(DF_FILE  file)
{
     return extOldGameManager->DF_File_ReadString(  file);
}

void DF_File_ReadToBuffer(DF_FILE  file,char * buffer,gm_s32 dataSize)
{
      extOldGameManager->DF_File_ReadToBuffer(  file,buffer, dataSize);
}

char * DF_ReadString2(char*data,int * pointer)
{
     return extOldGameManager->DF_ReadString2(data, pointer);
}
/****************************************************************************
*
****************************************************************************/ 
void initDFRecord(DF_Record * myself,
					char * filename,
					gm_s16 size,
					gm_s16 maxRecordNum)
{
      extOldGameManager->initDFRecord( myself,
					 filename,
					 size,
					 maxRecordNum);
}

/****************************************************************************
*
****************************************************************************/ 
void initDFWindows(DF_Windows * myself,
						Rect DF_Windows_Rect,
						void * UpdateParam,
						void * RenderParam,
						int repaintMax)
{
      extOldGameManager->initDFWindows( myself,
						 DF_Windows_Rect,
						 UpdateParam,
						 RenderParam,
						 repaintMax);
}

/****************************************************************************
*
****************************************************************************/ 
MemoryBlock * DF_GetMemoryBlock()
{
     return extOldGameManager->DF_GetMemoryBlock();
}

/****************************************************************************
*
****************************************************************************/ 
gm_s16 DF_ReadShort(char*data,int * pointer)
{
     return extOldGameManager->ReadShort(data, pointer);
}

/****************************************************************************
*
****************************************************************************/ 
int DF_ReadInt(char*data,int * pointer)
{
     return extOldGameManager->DF_ReadInt(data, pointer);
}

/****************************************************************************
*
****************************************************************************/ 
char * DF_ReadString(char*data,int * pointer)
{
     return extOldGameManager->DF_ReadString(data, pointer);
}

/****************************************************************************
*
****************************************************************************/ 
tResource DF_GetStreamTResource(char * fileName)
{
     return extOldGameManager->DF_GetStreamTResource( fileName);
}

/****************************************************************************
*
****************************************************************************/ 
void initDFSpriteLibrary(DF_SpriteLibrary * myself,short maxSpriteNum)
{
      extOldGameManager->initDFSpriteLibrary( myself, maxSpriteNum);
}

/****************************************************************************
*
****************************************************************************/ 
void initDFMapVScollBuffer(DF_MapVScollBuffer * myself,
								DF_PictureLibrary * picLib,
								Rect 			windows_Rect,
								int 				repaintMax,
								int 				exWidth,
								int 				tileHeight)
{
      extOldGameManager->initDFMapVScollBuffer(myself,picLib,windows_Rect,repaintMax,exWidth,tileHeight);
}

/****************************************************************************
*
****************************************************************************/ 
void initDFScene(DF_Scene * 			myself,
					Rect 				windows_Rect,
					DF_PictureLibrary*		picLib,
					char * 				sceName,
					int 					repaintMax,
					int 					bufferType,
					DecodeLabelCallBack 	decodeLabelCallBack)
{
      extOldGameManager->initDFScene(myself,windows_Rect,picLib,sceName,repaintMax,bufferType,decodeLabelCallBack);
}

/****************************************************************************
*
****************************************************************************/ 
gm_s32 DF_Cos(gm_s32 degree)
{
     return extOldGameManager->DF_Cos( degree);
}

/****************************************************************************
*
****************************************************************************/ 
gm_s32 DF_Sin(gm_s32 degree)
{
     return extOldGameManager->DF_Sin( degree);
}

/****************************************************************************
*
****************************************************************************/ 
gm_s32 DF_Degree(gm_s32 dx,gm_s32 dy)
{
     return extOldGameManager->DF_Degree(dx,dy);
}

/****************************************************************************
*
****************************************************************************/ 
gm_bool DF_CollectionTest(Rect rect1,Rect rect2)
{
     return extOldGameManager->DF_CollectionTest(rect1,rect2);
}
/****************************************************************************
*
****************************************************************************/ 
DF_MapVScollBuffer* DF_GetSceneMapVScollBufferPtr(void)
{
     return extVmDFEnginelManager->GetSceneMapVScollBufferPtr();
}
DF_MapRenderBuffer * DF_GetDF_MapRenderBufferPtr(void)
{
     return extVmDFEnginelManager->GetDF_MapRenderBufferPtr();
}
/****************************************************************************
*
****************************************************************************/ 
void initDFActor(DF_Actor * myself,gm_s16 x,gm_s16 y)
{
      extOldGameManager->initDFActor(myself, x, y);
}
/****************************************************************************
*
****************************************************************************/ 
void initDFDataPackage(DF_DataPackage * myself,gm_s16 maxLoadPackage)
{
      extOldGameManager->initDFDataPackage(myself,maxLoadPackage);
}
void DF_InitMemory(gm_u32 size)
{
      extVmMemoryManager->dF_InitMemory(size);
}

void DF_ReleaseMemory()
{
     extVmMemoryManager->dF_ReleaseMemory();
}
#ifndef WIN32
gm_bool DF_Malloc_IN(void ** pointer,gm_u32 size)
{
     return extVmMemoryManager->dF_Malloc_In(pointer, size);
}
#endif
void DF_Free(void ** pointer)
{
      extVmMemoryManager->dF_Free(pointer);
}


Script*  XS_Init (void)
{
     return extOldGameManager->XS_Init();
}
void XS_ShutDown (void)
{
      extOldGameManager->XS_ShutDown();
}
int XS_LoadScript ( char * pstrFilename, int * iThreadIndex, int iThreadTimeslice )
{
      extOldGameManager->XS_LoadScript(pstrFilename,iThreadIndex,iThreadTimeslice );
}
void XS_ResetScript ( int iThreadIndex )
{
      extOldGameManager->XS_ResetScript(  iThreadIndex );
}
void XS_RunScripts ( int iTimesliceDur )
{
      extOldGameManager->XS_RunScripts(  iTimesliceDur );
}
void XS_CallScriptFunc ( int iThreadIndex, char * pstrName )
{
      extOldGameManager->XS_CallScriptFunc(iThreadIndex,  pstrName);
}
void XS_InvokeScriptFunc ( int iThreadIndex, char * pstrName )
{
      extOldGameManager->XS_InvokeScriptFunc(iThreadIndex,  pstrName);
}
void XS_RegisterHostAPIFunc ( int iThreadIndex, char * pstrName, HostAPIFuncPntr fnFunc )
{
      extOldGameManager->XS_RegisterHostAPIFunc(iThreadIndex,  pstrName,  fnFunc);
}
void XS_StartScript ( int iThreadIndex )
{
      extOldGameManager->XS_StartScript(iThreadIndex);
}
void XS_StopScript ( int iThreadIndex )
	{
      extOldGameManager->XS_StopScript(iThreadIndex);
}
void XS_PauseScript ( int iThreadIndex, int iDur )
	{
      extOldGameManager->XS_PauseScript(iThreadIndex,iDur);
}
void XS_UnpauseScript ( int iThreadIndex )
{
      extOldGameManager->XS_UnpauseScript(iThreadIndex);
}
int XS_GetReturnValueAsInt ( int iThreadIndex )
{
     return extOldGameManager->XS_GetReturnValueAsInt(iThreadIndex);
}
float XS_GetReturnValueAsFloat ( int iThreadIndex )
{
     return extOldGameManager->XS_GetReturnValueAsFloat(iThreadIndex);
}
char * XS_GetReturnValueAsString ( int iThreadIndex )
{
     return extOldGameManager->XS_GetReturnValueAsString(iThreadIndex);
}
void XS_ReturnFromHost ( int iThreadIndex, int iParamCount )
{
      extOldGameManager->XS_ReturnFromHost(iThreadIndex,iParamCount);
}
void XS_ReturnIntFromHost ( int iThreadIndex, int iParamCount, int iInt )
{
      extOldGameManager->XS_ReturnIntFromHost(iThreadIndex,  iParamCount,  iInt);
}
void XS_ReturnFloatFromHost ( int iThreadIndex, int iParamCount, float fFloat )
{
      extOldGameManager->XS_ReturnFloatFromHost(iThreadIndex,  iParamCount,  fFloat);
}
void XS_ReturnStringFromHost ( int iThreadIndex, int iParamCount, char * pstrString )
{
      extOldGameManager->XS_ReturnStringFromHost(iThreadIndex,  iParamCount,  pstrString);
}
int XS_GetParamAsInt ( int iThreadIndex, int iParamIndex )
{
     return extOldGameManager->XS_GetParamAsInt(iThreadIndex,iParamIndex);
}
float XS_GetParamAsFloat ( int iThreadIndex, int iParamIndex )
{
     return extOldGameManager->XS_GetParamAsFloat(iThreadIndex,iParamIndex);
}
char * XS_GetParamAsString ( int iThreadIndex, int iParamIndex )
{
     return extOldGameManager->XS_GetParamAsString(iThreadIndex,iParamIndex);
}



/****************************************************************************
*
****************************************************************************/ 
void SCREEN_NotifyLoadResource(tScreen* LoadScreen_p)
{
      extOldGameManager->SCREEN_NotifyLoadResource(LoadScreen_p);
}

/****************************************************************************
*
****************************************************************************/ 
void MF_resetGmemoryBlock(void)
{
      extVmMemoryManager->mF_resetGmemoryBlock();
}

/****************************************************************************
*
****************************************************************************/ 
void* MF_MallocGmemoryBlock(gm_s32 size)
{
     return extVmMemoryManager->mF_MallocGmemoryBlock(size);
}

/****************************************************************************
*
****************************************************************************/ 
void setText(TextBox * myself,char * text)
{
      myself->SetText(myself,text);
}

/****************************************************************************
*
****************************************************************************/ 
void initDFMap(DF_Map * myself,
				Rect windows_Rect,
				DF_PictureLibrary * picLib,
				char * mapName,
				int repaintMax)
{
      extOldGameManager->initDFMap(myself,windows_Rect,picLib,mapName,repaintMax);
}
/****************************************************************************
*
****************************************************************************/ 


/****************************************************************************
*
****************************************************************************/ 
void initDFMapRenderBuffer(DF_MapRenderBuffer * myself,
								DF_PictureLibrary * picLib,
								Rect windows_Rect,
								int repaintMax)
{
      extOldGameManager->initDFMapRenderBuffer(myself,picLib,windows_Rect,repaintMax);
}

/****************************************************************************
*
****************************************************************************/ 
unsigned long int Get_CurKeyDownState(void)
{
     return extOldGameManager->Get_CurKeyDownState();
}
/****************************************************************************
*说明: 以下是BILL CALL
****************************************************************************/
/****************************************************************************
*
****************************************************************************/ 
VMUINT16 BILLING_GetPayNumByAppId(NETAPP_BILLING_APPID_TYPE appID,
													NETAPP_BILLING_METHOD_TYPE method)
{
     return extOldGameManager->BILLING_GetPayNumByAppId(appID,method); 
}

/****************************************************************************
*
****************************************************************************/ 
VMUINT32 BILLING_GetRemainDay(NETAPP_BILLING_APPID_TYPE appID,
											NETAPP_BILLING_METHOD_TYPE method)
{
     return extOldGameManager->BILLING_GetRemainDay(appID,method); 
}

/****************************************************************************
*
****************************************************************************/ 
void   BILLING_Pay(NETAPP_BILLING_APPID_TYPE 		appID,
						NETAPP_BILLING_METHOD_TYPE 		method,
						Billing_callback_func_t 				callBackFun )
{
	  extOldGameManager->BILLING_Pay(appID,method,callBackFun); 				
}
/****************************************************************************
*
****************************************************************************/ 
void   BILLING_PayMoreTimes(NETAPP_BILLING_APPID_TYPE appID,
									NETAPP_BILLING_METHOD_TYPE method,
									Billing_callback_func_t callBackFun ,
									VMUINT16 times)
{
      extOldGameManager->BILLING_PayMoreTimes(appID,method,callBackFun,times);
}
/**************************************************************************
* 函数名称： BILLING_IsRegisterBillingInfo
* 功能描述： 该函数用于查询是否注册了包月付费业务
* 参数说明： 
* 返 回 值： 
* 其它说明：WINGTECH版权所有！ 无 
**************************************************************************/
VMBOOLEAN BILLING_IsRegisterBillingInfo(NETAPP_BILLING_APPID_TYPE appID)
{
     return extOldGameManager->BILLING_IsRegisterBillingInfo(appID);
}
/**************************************************************************
* 函数名称： BILLING_RegisterBillingInfo
* 功能描述：本函数用于包月计费的应用。
            包月计费应用使用前，应用首先需要调用该函数注册计费信息
* 参数说明： 
* 返 回 值： 
* 其它说明：WINGTECH版权所有！ 无
**************************************************************************/
VMBOOLEAN BILLING_RegisterBillingInfo(NETAPP_BILLING_APPID_TYPE appID, VMUINT32 tryTime)
{
     return extOldGameManager->BILLING_RegisterBillingInfo(appID,tryTime);
}
/**************************************************************************
* 函数名称： BILLING_SetBillingStatus
* 功能描述： 本函数用于包月计费的应用。
             应用可以通过调用该函数来开启或者关闭付费状态。
* 参数说明： 
* 返 回 值： 
* 其它说明：WINGTECH版权所有！ 无
**************************************************************************/
VMBOOLEAN BILLING_SetBillingStatus(NETAPP_BILLING_APPID_TYPE  appID,    NETAPP_BILLING_STATUS_TYPE billingStatus)
{
     return extOldGameManager->BILLING_SetBillingStatus(appID,billingStatus);
}

/**************************************************************************
* 函数名称： BILLING_GetBillingStatus
* 功能描述： 本函数用于包月计费的应用。
             应用可以通过调用该函数来获取付费状态。
* 参数说明： 
* 返 回 值： 
* 其它说明： WINGTECH版权所有！ 无
**************************************************************************/
NETAPP_BILLING_STATUS_TYPE  BILLING_GetBillingStatus(NETAPP_BILLING_APPID_TYPE  appID)
{
     return extOldGameManager->BILLING_GetBillingStatus(appID);
}
/**************************************************************************
* 函数名称： BILLING_IsNeedPay
* 功能描述： 本函数用于包月计费的应用。
             应用可以通过调用该函数来判断应用是否需要付费。
* 参数说明： 
* 返 回 值： 
* 其它说明：WINGTECH版权所有！ 无
**************************************************************************/
VMBOOLEAN  BILLING_IsNeedPay(NETAPP_BILLING_APPID_TYPE appID)
{
     return extOldGameManager->BILLING_IsNeedPay(appID);
}
/**************************************************************************
* 函数名称： BILLING_IsInTryStatus
* 功能描述： 本函数用于包月计费的应用。
             应用可以通过调用该函数来判断应用当前是否还处于试用期。
* 参数说明： 
* 返 回 值： 
* 其它说明：WINGTECH版权所有！ 无
**************************************************************************/
VMBOOLEAN  BILLING_IsInTryStatus(NETAPP_BILLING_APPID_TYPE appID)
{
     return extOldGameManager->BILLING_IsInTryStatus(appID);
}

/****************************************************************************
*								2611
*************************************************************************** 
void BIllING_OpenBillingPromptWin(NETAPP_BILLING_APPID_TYPE  appID)
{
      extOldGameManager->BIllING_OpenBillingPromptWin(appID);
}
*/
void gm_ASSERT_TOld(char    *file,    VMUINT32  line   )
{

	//gm_TRACE_T("assert at file:%s,line:%d",file,line);
	while(1);	
}


gm_bool  DF_Malloc_IN_DL(void ** pointer,gm_u32 size)
{
     extVmMemoryManager->dF_Malloc_In(pointer,size);
}
void gm_ASSERT_T(char    *file,    VMUINT32  line   )
{
  if(extVmSysManager!=PNULL)
  {
    extVmSysManager->vMAssert(file,line);
  }		
}


void gddiInitJpgCodec(void)
{
  
}

void gddiInitGifCodec(void)
{
  
}

void vmMainreg(void *param_p)
{

}

void  vmScreenInit
       (VmScreen *scr_p,ScreenInit init,ScreenDestory Destory,
        ScreenLogic Logic,ScreenRender Render,ScreenPause Pause,
        ScreenResume Resume,ScreenLoadResource LoadR
        )  
{
	scr_p->screenInit=init; 
	scr_p->screenDestory=Destory; 
	scr_p->screenLogic=Logic; 
	scr_p->screenRender=Render; 
	scr_p->screenPause=Pause; 
	scr_p->screenResume=Resume; 
	scr_p->screenLoadResource=LoadR;
}
void  vmScreenInitEx(VmScreen *scr_p,ScreenInit init,ScreenDestory Destory,
       ScreenLogic Logic,ScreenRender Render)  
{
	scr_p->screenInit=init; 
	scr_p->screenDestory=Destory; 
	scr_p->screenLogic=Logic; 
	scr_p->screenRender=Render; 
	scr_p->screenPause=PNULL; 
	scr_p->screenResume=PNULL; 
	scr_p->screenLoadResource=PNULL;
}

void  vmtScreenInit(tScreen *scr_p,TScreenInit init,TScreenDestory Destory,
        TScreenLogic Logic,TScreenRender Render,TScreenPause Pause,
        TScreenResume Resume,TScreenLoadResource LoadR
        )  
{
	scr_p->NotifyInit=init; 
	scr_p->NotifyDestory=Destory; 
	scr_p->NotifyLogic=Logic; 
	scr_p->NotifyRender=Render; 
	scr_p->NotifyPause=Pause; 
	scr_p->NotifyResume=Resume; 
	scr_p->NotifyLoadResource=LoadR;
}
#endif
