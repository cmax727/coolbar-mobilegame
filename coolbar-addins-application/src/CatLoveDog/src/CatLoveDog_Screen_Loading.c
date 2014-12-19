/***********************************************************************************************************************
����ҳ��
***********************************************************************************************************************/
#include "CatLoveDog_Screen.h"   //��������Ŀ����Ϊ�� ��ͼƬ����Դ��������
#include "DF_PictureLibrary.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
	 void CatLoveDog_Loading_LoadResource(void);
	 void CatLoveDog_Loading_Init(void);
	 void CatLoveDog_Loading_Destory(void);
	 void CatLoveDog_Loading_Logic(void);
	 void CatLoveDog_Loading_Render(tGraphics *g);
	 void CatLoveDog_Loading_Pause(void);
	 void CatLoveDog_Loading_Resume(void);
#ifdef __WIN_32
	extern BOOL 	GAME_Update();
#endif
	
	tScreen CatLoveDog_Screen_Loading;
	
	tScreen * CatLoveDog_Screen_Next;
	
	gm_s32 CatLoveDogImageLoading[2];
	 gm_s16 catLoveDogLoadingStep;
	 gm_s16 catLoveDogLoadingStepTotal;
	gm_s8 catLoveDogLoadingRepaintAll;
	gm_s8 catLoveDogLoadingRepaintStep;
	gm_s32 CatLoveDogImageHintWidth;
	gm_s32 CatLoveDogImageHintHeight;
	
	DF_PictureLibrary catLoveDogLoadingPicLib;  //��Screen����ͼƬ��
	
	
	//��SCREEN_CHANGE()�������õ�ʱ�� ����
	void CatLoveDog_Loading_Init(void)
	{
		//��ʼ��ͼƬ��,�ͷ���ǰ�ù�������ͼƬ
		catLoveDogPicLib.Release(&catLoveDogPicLib);		
		//�����ڴ�
		memoryblock_my->Reset((void *)memoryblock_my);
		initDFPictureLibrary(&catLoveDogLoadingPicLib,5);
		CatLoveDogImageLoading[0] = catLoveDogLoadingPicLib.GetImage(&catLoveDogLoadingPicLib,"loading.gif");
		CatLoveDogImageLoading[1] = catLoveDogLoadingPicLib.GetImage(&catLoveDogLoadingPicLib,"loading1.gif");
		
		catLoveDogLoadingRepaintAll = 1;
	}
	
	void CatLoveDog_Loading_Destory()//����load��ͼƬ
	{
		catLoveDogLoadingPicLib.Release(&catLoveDogLoadingPicLib);
	}
	
	//���෽�� �����߳�ѭ������  
	void CatLoveDog_Loading_Logic(void)
	{
		GAME_SetKeyEnable(0);
		CatLoveDog_Loading_Render(0);	
		CatLoveDog_Screen_Next->NotifyLoadResource();   // ֪ͨ�¸���Ļ���������Դ �����UniversalWal_Screen_Title ���CatLoveDog_Title_LoadResource������
		//���� ������Ϸ���� ǰ�и�������Դ�Ľ���
		SCREEN_ChangeScreen(CatLoveDog_Screen_Next);
		GAME_SetKeyEnable(1);
	}
	
	void CatLoveDog_Loading_Render(tGraphics *g)//����loading������
	{
		gm_s32 w;
		w=catLoveDogLoadingStep/catLoveDogLoadingStepTotal;	
		if(catLoveDogLoadingRepaintAll)
		{
			catLoveDogLoadingPicLib.FillRect(&catLoveDogLoadingPicLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,DF_RGB565(36,19,121));
#ifdef GAME_240_320
			catLoveDogLoadingPicLib.DrawImageEx(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[0],(SCREEN_WIDTH-106)>>1,180,1,0);
			catLoveDogLoadingPicLib.DrawRegion(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*catLoveDogLoadingStep/catLoveDogLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			catLoveDogLoadingPicLib.DrawImageEx(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[0],(SCREEN_WIDTH-106)>>1,120,1,0);
			catLoveDogLoadingPicLib.DrawRegion(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*catLoveDogLoadingStep/catLoveDogLoadingStepTotal,7);
#endif
			catLoveDogLoadingRepaintAll = 0;
		}
		if(catLoveDogLoadingRepaintStep)
		{
			if(catLoveDogLoadingStep<=catLoveDogLoadingStepTotal)
#ifdef GAME_240_320
				catLoveDogLoadingPicLib.DrawRegion(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*catLoveDogLoadingStep/catLoveDogLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			catLoveDogLoadingPicLib.DrawRegion(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*catLoveDogLoadingStep/catLoveDogLoadingStepTotal,7);
#endif
			catLoveDogLoadingRepaintStep = 0;
		}
	}
	
	void CatLoveDog_Loading_Pause(void)
	{
	}
	
	void CatLoveDog_Loading_Resume(void)
	{
	}
	
	void CatLoveDog_Loading_LoadResource(void)
	{
	}
	
	//������Ļ��ʾ
	void CatLoveDog_Loading_UpdateStep(void)
	{
		catLoveDogLoadingStep++;
		if(catLoveDogLoadingStep>catLoveDogLoadingStepTotal)
			catLoveDogLoadingStep = catLoveDogLoadingStepTotal;
		catLoveDogLoadingRepaintStep = 1;
		CatLoveDog_Loading_Render(0);
#ifdef __WIN_32
		GAME_Update();
		SDL_Delay(50);
#else
		GAME_RefresScreen();
#endif
	}
	
	


