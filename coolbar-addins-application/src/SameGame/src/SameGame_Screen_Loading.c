/***********************************************************************************************************************
����ҳ��
***********************************************************************************************************************/
#include "SameGame_Screen.h"   //��������Ŀ����Ϊ�� ��ͼƬ����Դ��������
#include "DF_PictureLibrary.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

#ifdef __WIN_32
	extern BOOL 	GAME_Update();
#endif
	
//��SCREEN_CHANGE()�������õ�ʱ�� ����
void SameGame_Loading_Init(void)
{
	//��ʼ��ͼƬ��,�ͷ���ǰ�ù�������ͼƬ
	allPicLib.Release(&allPicLib);		
	//�����ڴ�
	memoryblock_my->Reset((void *)memoryblock_my);
	initDFPictureLibrary(&SameGameLoadingPicLib,5);
	
	sameGameLoadingRepaintAll = 1;
}

void SameGame_Loading_Destory()//����load��ͼƬ
{
	SameGameLoadingPicLib.Release(&SameGameLoadingPicLib);
}

//���෽�� �����߳�ѭ������  
void SameGame_Loading_Logic(void)
{
	gm_s32 w;
	GAME_SetKeyEnable(0);
	SameGame_Loading_Render(0);	
	sameGame_Screen_Next->NotifyLoadResource();   // ֪ͨ�¸���Ļ���������Դ �����UniversalWal_Screen_Title ���ONFF_Title_LoadResource������
	//���� ������Ϸ���� ǰ�и�������Դ�Ľ���
	SCREEN_ChangeScreen(sameGame_Screen_Next);
	GAME_SetKeyEnable(1);
	
	w=sameGameLoadingStep/sameGameLoadingStepTotal;	
	if(sameGameLoadingRepaintAll)
	{
		SameGameLoadingPicLib.FillRect(&SameGameLoadingPicLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,DF_RGB565(102,51,0));
		sameGameLoadingRepaintAll = 0;
	}
	if(sameGameLoadingRepaintStep)
	{
		sameGameLoadingRepaintStep = 0;
	}
}

void SameGame_Loading_Render(tGraphics *g)//����loading������
{

}

void SameGame_Loading_Pause(void)
{
}

void SameGame_Loading_Resume(void)
{
}

void SameGame_Loading_LoadResource(void)
{
}

//������Ļ��ʾ
void SameGame_Loading_UpdateStep(void)
{
	sameGameLoadingStep++;
	if(sameGameLoadingStep>sameGameLoadingStepTotal)
		sameGameLoadingStep = sameGameLoadingStepTotal;
	sameGameLoadingRepaintStep = 1;
	SameGame_Loading_Render(0);
	#ifdef __WIN_32
		GAME_Update();
		SDL_Delay(50);
	#else
		GAME_RefresScreen();
	#endif
}
	
	

