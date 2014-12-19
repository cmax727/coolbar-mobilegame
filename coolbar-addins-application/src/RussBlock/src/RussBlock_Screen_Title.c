#include "RussBlock_Screen.h"
#include "DF_Record.h"
#include "RussBlock_Help.h"
#include "RussBlock_Title.h"
#include "RussBlock_TitleMenu.h"
#include "RussBlock_HighScore.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
/*
�״ν�����Ϸʱ��Ҫ���һЩ��Ϸ�н���
*/

extern void russBlock_Title_init();
extern void russBlock_Title_Destroy();
extern void russBlock_Title_Logic();
extern void russBlock_Title_Render(tGraphics * g);
extern void russBlock_Title_Pause();
extern void russBlock_Title_Resume();
extern void russBlock_Title_LoadResource();


Manager * manager_my;
MemoryBlock *memoryblock_my;
DF_Record russBlockRecord;
gm_s32 russBlockHighScoreValue_CommonModel[12];
gm_s32 russBlockHighScoreValue_TimeModel[12];

gm_s16 russBlockTitleState;  
RussBlockTitle rushBlockTitle;
RussBlockTitleMenu russBlockTitleMenu;
RussBlock_Help russBlockTitleHelp;
RussBlock_HighScore russBlockHighScore;

static DF_DataPackage dataPackage;
tScreen RussBlock_Screen_Title =
{
	russBlock_Title_init,
	russBlock_Title_Destroy,
	russBlock_Title_Logic,
	russBlock_Title_Render,
	russBlock_Title_Pause,
	russBlock_Title_Resume,
	russBlock_Title_LoadResource
};

void russBlock_Title_init()
{

}
void russBlock_Title_Destroy()
{
	russBlockPicLib.Release(&russBlockPicLib);
}
//ÿ�������ˢ�·���
void russBlock_Title_Logic()
{
	switch (russBlockTitleState)
	{
	case RUSSBLOCK_TITLE_STATE_SHOW_TITLE:
		rushBlockTitle.windows.DF_Update(&rushBlockTitle.windows);
		break;
	case RUSSBLOCK_TITLE_STATE_MENU:
		russBlockTitleMenu.windows.DF_Update(&russBlockTitleMenu.windows);
		break;
	case RUSSBLOCK_TITLE_STATE_HELP:
		russBlockTitleHelp.windows.DF_Update(&russBlockTitleHelp.windows);
	    break;
	case RUSSBLOCK_TITLE_STATE_HIGHSCORE:
		russBlockHighScore.windows.DF_Update(&russBlockHighScore.windows);
		break;		
	}
}
//ÿ������Ļ��Ʒ���
void russBlock_Title_Render(tGraphics * g)
{
	switch (russBlockTitleState)
	{
	case RUSSBLOCK_TITLE_STATE_SHOW_TITLE:
		rushBlockTitle.windows.DF_Render(&rushBlockTitle.windows);
		break;
	case RUSSBLOCK_TITLE_STATE_MENU:
		russBlockTitleMenu.windows.DF_Render(&russBlockTitleMenu.windows);
		break;
	case RUSSBLOCK_TITLE_STATE_HELP:
		russBlockTitleHelp.windows.DF_Render(&russBlockTitleHelp.windows);
		break;
	case RUSSBLOCK_TITLE_STATE_HIGHSCORE:
		russBlockHighScore.windows.DF_Render(&russBlockHighScore.windows);
		break;
	}
	getManagerPtr()->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}
void russBlock_Title_Pause()
{

}
void russBlock_Title_Resume()
{
	RussBlock_Title_ChangeState(russBlockTitleState);
}
//��ʹ����Ϸ��ÿ������
void russBlock_Title_LoadResource()
{
	Rect ur;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
	initDFPictureLibrary(&russBlockPicLib,20);
	initRussBlockTitle(&rushBlockTitle,ur,&russBlockPicLib);
	initRussBlockTitleMenu(&russBlockTitleMenu,ur,&russBlockPicLib);
	initRussBlockHelp(&russBlockTitleHelp,ur,&russBlockPicLib);
	initRussBlockHighScore(&russBlockHighScore,ur,&russBlockPicLib);
}
//��Ϸ�и����������Ļ�л���
void RussBlock_Title_ChangeState(gm_s16 state)
{
	russBlockTitleState=state;
	switch (russBlockTitleState)
	{
	case RUSSBLOCK_TITLE_STATE_SHOW_TITLE:
		DF_SendMessage(&rushBlockTitle.windows,DF_WINDOWS_MSG_INVALITE,&rushBlockTitle.windows.DF_Windows_Rect);
		break;
	case RUSSBLOCK_TITLE_STATE_MENU:
		DF_SendMessage(&russBlockTitleMenu.windows,DF_WINDOWS_MSG_INVALITE,&russBlockTitleMenu.windows.DF_Windows_Rect);
	    break;
	case RUSSBLOCK_TITLE_STATE_HELP:
		DF_SendMessage(&russBlockTitleHelp.windows,DF_WINDOWS_MSG_INVALITE,&russBlockTitleHelp.windows.DF_Windows_Rect);
	    break;
	case RUSSBLOCK_TITLE_STATE_HIGHSCORE:
		DF_SendMessage(&russBlockHighScore.windows,DF_WINDOWS_MSG_INVALITE,&russBlockHighScore.windows.DF_Windows_Rect);
		break;
	}
}

void RussBlock_main(void)
{
	gm_s16 j,m;
#ifdef GAME_240_320
	DF_InitMemory(150*1024);	//�趨��Ϸ�ڴ�ռ�
#endif
#ifdef GAME_176_220
	DF_InitMemory(140*1024);
#endif
	initMemoryBlock(getMemoryBlockPtr(),1024*50);
	initDreamFactoryEngine();
	initDFDataPackage(&dataPackage,5);//��Ϸ����Դ��	
	dataPackage.DP_LoadPackage(&dataPackage,0);
	dataPackage.DP_DoLoading(&dataPackage,RussBlock_TResource_Data,1);
	DF_SetDataPackage(&dataPackage);

	memoryblock_my=getMemoryBlockPtr();

	manager_my=getManagerPtr();
    initManager(manager_my);
	
	initDFPictureLibrary(&russBlockPicLib,5);

	//��ʼ����¼��
	initDFRecord(&russBlockRecord,"russBlockRecord",1024,8);
	russBlockRecord.Open(&russBlockRecord);
	if(russBlockRecord.recordNum!=7)  //д��¼
	{
		russBlockRecord.ResetData(&russBlockRecord);//��Ч���ݳ�ʼ����¼
		/*��ͨģʽ*/
		russBlockRecord.AddRecord(&russBlockRecord,50);
		russBlockRecord.pointer = 0;
		for (j=0;j<12;j++)
		{
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_COMMONMODEL,0);
		}

		/*ʱ��ģʽ*/
		russBlockRecord.AddRecord(&russBlockRecord,50);
		russBlockRecord.pointer = 0;
		for (j=0;j<12;j++)
		{
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_TIMEMODEL,0);
		}
		/*д�����*/
		russBlockRecord.AddRecord(&russBlockRecord,50);
		russBlockRecord.pointer = 0;
		for (j=0;j<3;j++)
		{
			russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_PROP,0);
			russBlockProp[j]=99;
		}
		/*д����ͨģʽ��������*/
		russBlockRecord.AddRecord(&russBlockRecord,254);
		russBlockRecord.pointer=0;
		for (j=0;j<VERTICAL_BOXS;j++)
		{
			for (m=0;m<HORIZONTAL_BOXS;m++)
			{
				russBlockRecord.WriteByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_NOMAL,0);
			}
		}
		/*д��ʱ��ģʽ��������*/
		russBlockRecord.AddRecord(&russBlockRecord,254);
		russBlockRecord.pointer=0;
		for (j=0;j<VERTICAL_BOXS;j++)
		{
			for (m=0;m<HORIZONTAL_BOXS;m++)
			{
				russBlockRecord.WriteByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_TIME,0);
			}
		}


		/*��ͨģʽ��¼ */
		russBlockRecord.AddRecord(&russBlockRecord,20);
		russBlockRecord.pointer=0;
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,1);  //�ȼ�
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,0);  //����
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,0);  //���Ĳ���
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL,0);  //�����ٶ�
		russBlockGameData[0][0]=1;
 
		/*ʱ��ģʽ��¼*/
		russBlockRecord.AddRecord(&russBlockRecord,20);
		russBlockRecord.pointer=0;
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,1);  //�ȼ�
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,0);  //����
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,0);  //���Ĳ���
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,0);  //�����ٶ�
		russBlockRecord.WriteInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME,BLOCK_TIME); //ʱ��
		russBlockGameTime=BLOCK_TIME;
		russBlockGameData[1][0]=1;
	}
	else     //����¼
	{
			russBlockRecord.pointer=0;
			for (m=0;m<12;m++)
			{
				 russBlockHighScoreValue_CommonModel[m]=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_COMMONMODEL);
			}
			russBlockRecord.pointer=0;
			for(m=0;m<12;m++)
			{
				russBlockHighScoreValue_TimeModel[m]=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_TIMEMODEL);
			}
			russBlockRecord.pointer = 0;	
		    for (m=0;m<3;m++)
		    {
				russBlockProp[m]=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_PROP);
		    }

			russBlockRecord.pointer=0;
			for (j=0;j<VERTICAL_BOXS;j++)
			{
				for (m=0;m<HORIZONTAL_BOXS;m++)
					russBlockGameGrid[0][j][m]=russBlockRecord.ReadByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_NOMAL);
			}
			
			russBlockRecord.pointer=0;
			for (j=0;j<VERTICAL_BOXS;j++)
			{
				for (m=0;m<HORIZONTAL_BOXS;m++)
					russBlockGameGrid[1][j][m]=russBlockRecord.ReadByte(&russBlockRecord,RUSSBLOCK_RECORD_ID_GRID_TIME);
			}
            
			russBlockRecord.pointer=0;
			for (j=0;j<4;j++)
			{
				russBlockGameData[0][j]=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL);
			}

			russBlockRecord.pointer=0;
			for (j=0;j<4;j++)
			{
				russBlockGameData[1][j]=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME);
			}
			russBlockGameTime=russBlockRecord.ReadInt(&russBlockRecord,RUSSBLOCK_RECORD_ID_GAMEDATA_TIME);
	}

	russBlockTitleState=RUSSBLOCK_TITLE_STATE_SHOW_TITLE;
	russBlockLoadingStep=0;
	russBlockLoadingStepTotal=16;
	RussBlock_Screen_Next=&RussBlock_Screen_Title;//��¼�¸���Ļ��
	SCREEN_ChangeScreen(&RussBlock_Screen_Loading);//�л���Ļ

}
//��Ϸ�˳�,�ͷ���Դ
void RussBlock_exit()
{
	updateGameData();
	dataPackage.DP_ReleasePackage(&dataPackage,0);
	russBlockRecord.Close(&russBlockRecord);
	russBlockPicLib.Release(&russBlockPicLib);
	DF_ReleaseMemory();

}

void   RussBlock_SMS_BuyOneMonth(BOOLEAN isSucess)//�Ƿ���»ص�����
{
	if(isSucess)
	{
		RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_MENU);
	}
}
/*
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dynamicLoadingCore_ext.h"
#pragma arm section code = "game_reg_main"
void game_reg_main(sysCall sys_call)//��Ϸ������
{
	t_sysCall = sys_call;
	game_reg(RussBlock_main,RussBlock_exit);
}
#pragma arm section code
#endif

*/