/***********************************************************************************************************************
����ҳ��
***********************************************************************************************************************/
#include "ONFF_Screen.h"   //��������Ŀ����Ϊ�� ��ͼƬ����Դ��������
#include "DF_PictureLibrary.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
	 void ONFF_Loading_LoadResource(void);
	 void ONFF_Loading_Init(void);
	 void ONFF_Loading_Destory(void);
	 void ONFF_Loading_Logic(void);
	 void ONFF_Loading_Render(tGraphics *g);
	 void ONFF_Loading_Pause(void);
	 void ONFF_Loading_Resume(void);
#ifdef __WIN_32
	extern BOOL 	GAME_Update();
#endif
	
	tScreen ONFF_Screen_Loading;
	
	tScreen * ONFF_Screen_Next;
	
	gm_s32 oNFFImageLoading[2];
	 gm_s16 oNFFLoadingStep;
	 gm_s16 oNFFLoadingStepTotal;
	gm_s8 oNFFLoadingRepaintAll;
	gm_s8 oNFFLoadingRepaintStep;
	gm_s32 oNFFImageHintWidth;
	gm_s32 oNFFImageHintHeight;
	
	DF_PictureLibrary ONFFLoadingPicLib;  //��Screen����ͼƬ��
	
	
	//��SCREEN_CHANGE()�������õ�ʱ�� ����
	void ONFF_Loading_Init(void)
	{
		//��ʼ��ͼƬ��,�ͷ���ǰ�ù�������ͼƬ
		oNFFPicLib.Release(&oNFFPicLib);		
		//�����ڴ�
		memoryblock_my->Reset((void *)memoryblock_my);
		initDFPictureLibrary(&ONFFLoadingPicLib,5);
		oNFFImageLoading[0] = ONFFLoadingPicLib.GetImage(&ONFFLoadingPicLib,"loading.gif");
		oNFFImageLoading[1] = ONFFLoadingPicLib.GetImage(&ONFFLoadingPicLib,"loading1.gif");
		
		oNFFLoadingRepaintAll = 1;
	}
	
	void ONFF_Loading_Destory()//����load��ͼƬ
	{
		ONFFLoadingPicLib.Release(&ONFFLoadingPicLib);
	}
	
	//���෽�� �����߳�ѭ������  
	void ONFF_Loading_Logic(void)
	{
		GAME_SetKeyEnable(0);
		ONFF_Loading_Render(0);	
		ONFF_Screen_Next->NotifyLoadResource();   // ֪ͨ�¸���Ļ���������Դ �����UniversalWal_Screen_Title ���ONFF_Title_LoadResource������
		//���� ������Ϸ���� ǰ�и�������Դ�Ľ���
		SCREEN_ChangeScreen(ONFF_Screen_Next);
		GAME_SetKeyEnable(1);
	}
	
	void ONFF_Loading_Render(tGraphics *g)//����loading������
	{
		gm_s32 w;
		w=oNFFLoadingStep/oNFFLoadingStepTotal;	
		if(oNFFLoadingRepaintAll)
		{
			ONFFLoadingPicLib.FillRect(&ONFFLoadingPicLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,DF_RGB565(36,19,121));
#ifdef GAME_240_320
			ONFFLoadingPicLib.DrawImageEx(&ONFFLoadingPicLib,oNFFImageLoading[0],(SCREEN_WIDTH-106)>>1,180,1,0);
			ONFFLoadingPicLib.DrawRegion(&ONFFLoadingPicLib,oNFFImageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*oNFFLoadingStep/oNFFLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			ONFFLoadingPicLib.DrawImageEx(&ONFFLoadingPicLib,oNFFImageLoading[0],(SCREEN_WIDTH-106)>>1,120,1,0);
			ONFFLoadingPicLib.DrawRegion(&ONFFLoadingPicLib,oNFFImageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*oNFFLoadingStep/oNFFLoadingStepTotal,7);
#endif
			oNFFLoadingRepaintAll = 0;
		}
		if(oNFFLoadingRepaintStep)
		{
			if(oNFFLoadingStep<=oNFFLoadingStepTotal)
#ifdef GAME_240_320
				ONFFLoadingPicLib.DrawRegion(&ONFFLoadingPicLib,oNFFImageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*oNFFLoadingStep/oNFFLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			ONFFLoadingPicLib.DrawRegion(&ONFFLoadingPicLib,oNFFImageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*oNFFLoadingStep/oNFFLoadingStepTotal,7);
#endif
			oNFFLoadingRepaintStep = 0;
		}
	}
	
	void ONFF_Loading_Pause(void)
	{
	}
	
	void ONFF_Loading_Resume(void)
	{
	}
	
	void ONFF_Loading_LoadResource(void)
	{
	}
	
	//������Ļ��ʾ
	void ONFF_Loading_UpdateStep(void)
	{
		oNFFLoadingStep++;
		if(oNFFLoadingStep>oNFFLoadingStepTotal)
			oNFFLoadingStep = oNFFLoadingStepTotal;
		oNFFLoadingRepaintStep = 1;
		ONFF_Loading_Render(0);
#ifdef __WIN_32
		GAME_Update();
		SDL_Delay(50);
#else
		GAME_RefresScreen();
#endif
	}
	
	


