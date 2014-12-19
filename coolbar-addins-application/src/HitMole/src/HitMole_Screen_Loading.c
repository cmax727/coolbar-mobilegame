/***********************************************************************************************************************
����ҳ��
***********************************************************************************************************************/
#include "HitMole_Screen.h"   //��������Ŀ����Ϊ�� ��ͼƬ����Դ��������
#include "DF_PictureLibrary.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
	 void HitMole_Loading_LoadResource(void);
	 void HitMole_Loading_Init(void);
	 void HitMole_Loading_Destory(void);
	 void HitMole_Loading_Logic(void);
	 void HitMole_Loading_Render(tGraphics *g);
	 void HitMole_Loading_Pause(void);
	 void HitMole_Loading_Resume(void);
#ifdef __WIN_32
	extern BOOL 	GAME_Update();
#endif
	
	tScreen HitMole_Screen_Loading;
	
	tScreen * HitMole_Screen_Next;
	
	gm_s32 hitMolemageLoading[2];
	 gm_s16 hitMoleLoadingStep;
	 gm_s16 hitMoleLoadingStepTotal;
	gm_s8 hitMoleLoadingRepaintAll;
	gm_s8 hitMoleLoadingRepaintStep;
	
	DF_PictureLibrary HitMoleLoadingPicLib;  //��Screen����ͼƬ��
	
	
	//��SCREEN_CHANGE()�������õ�ʱ�� ����
	void HitMole_Loading_Init(void)
	{
		//��ʼ��ͼƬ��,�ͷ���ǰ�ù�������ͼƬ
		allPicLib.Release(&allPicLib);		
		//�����ڴ�
		memoryblock_my->Reset((void *)memoryblock_my);
		initDFPictureLibrary(&HitMoleLoadingPicLib,5);
		hitMolemageLoading[0] = HitMoleLoadingPicLib.GetImage(&HitMoleLoadingPicLib,"loading.gif");
		hitMolemageLoading[1] = HitMoleLoadingPicLib.GetImage(&HitMoleLoadingPicLib,"loading1.gif");
		
		hitMoleLoadingRepaintAll = 1;
	}
	
	void HitMole_Loading_Destory()//����load��ͼƬ
	{
		HitMoleLoadingPicLib.Release(&HitMoleLoadingPicLib);
	}
	
	//���෽�� �����߳�ѭ������  
	void HitMole_Loading_Logic(void)
	{
		GAME_SetKeyEnable(0);
		HitMole_Loading_Render(0);	
		HitMole_Screen_Next->NotifyLoadResource();   // ֪ͨ�¸���Ļ���������Դ �����UniversalWal_Screen_Title ���ONFF_Title_LoadResource������
		//���� ������Ϸ���� ǰ�и�������Դ�Ľ���
		SCREEN_ChangeScreen(HitMole_Screen_Next);
		GAME_SetKeyEnable(1);
	}
	
	void HitMole_Loading_Render(tGraphics *g)//����loading������
	{
		gm_s32 w;
		w=hitMoleLoadingStep/hitMoleLoadingStepTotal;	
		if(hitMoleLoadingRepaintAll)
		{
			HitMoleLoadingPicLib.FillRect(&HitMoleLoadingPicLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,DF_RGB565(102,51,0));
#ifdef GAME_240_320
			HitMoleLoadingPicLib.DrawImageEx(&HitMoleLoadingPicLib,hitMolemageLoading[0],(SCREEN_WIDTH-106)>>1,180,1,0);
			HitMoleLoadingPicLib.DrawRegion(&HitMoleLoadingPicLib,hitMolemageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*hitMoleLoadingStep/hitMoleLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			HitMoleLoadingPicLib.DrawImageEx(&HitMoleLoadingPicLib,hitMolemageLoading[0],(SCREEN_WIDTH-106)>>1,120,1,0);
			HitMoleLoadingPicLib.DrawRegion(&HitMoleLoadingPicLib,hitMolemageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*hitMoleLoadingStep/hitMoleLoadingStepTotal,7);
#endif
			hitMoleLoadingRepaintAll = 0;
		}
		if(hitMoleLoadingRepaintStep)
		{
			if(hitMoleLoadingStep<=hitMoleLoadingStepTotal)
#ifdef GAME_240_320
				HitMoleLoadingPicLib.DrawRegion(&HitMoleLoadingPicLib,hitMolemageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*hitMoleLoadingStep/hitMoleLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			HitMoleLoadingPicLib.DrawRegion(&HitMoleLoadingPicLib,hitMolemageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*hitMoleLoadingStep/hitMoleLoadingStepTotal,7);
#endif
			hitMoleLoadingRepaintStep = 0;
		}
	}
	
	void HitMole_Loading_Pause(void)
	{
	}
	
	void HitMole_Loading_Resume(void)
	{
	}
	
	void HitMole_Loading_LoadResource(void)
	{
	}
	
	//������Ļ��ʾ
	void HitMole_Loading_UpdateStep(void)
	{
		hitMoleLoadingStep++;
		if(hitMoleLoadingStep>hitMoleLoadingStepTotal)
			hitMoleLoadingStep = hitMoleLoadingStepTotal;
		hitMoleLoadingRepaintStep = 1;
		HitMole_Loading_Render(0);
#ifdef __WIN_32
		GAME_Update();
		SDL_Delay(50);
#else
		GAME_RefresScreen();
#endif
	}
	
	

