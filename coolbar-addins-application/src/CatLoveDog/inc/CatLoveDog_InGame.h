/**************************************************************************************************************************************************
*compay:daicom
*name:zhaoliangqi
*filename:CatLoveDog_InGame.h
*������Ϸ���廭��
**************************************************************************************************************************************************/

#ifndef CATLOVEDOG_INGAME_H
#define CATLOVEDOG_INGAME_H
#include "DF_Windows.h"
#include "DF_PictureLibrary.h"

typedef struct CATLOVEDOG_INGAME
{
	DF_PictureLibrary * picLib;
	DF_Windows windows;											 
	/*******************************************showgame�еı���*********************************************************************/
    gm_s8 SleepTimer; 												/////////////////��ʼˢ��ʱ��
    gm_s8 changelifeD; 												/////////////////��Ѫ��
    gm_s8 changelifeC;
    gm_s8 setColor;
    gm_bool bombRun;
    gm_s16 angle;
    gm_bool alive; 													////���������ж��߳��Ƿ����
    gm_bool isPause;
	gm_bool gameWin;
	gm_bool gameOver;
    
    //ͼƬ
    gm_s16 catImg; 													///////////////////���ͼƬ
    gm_s16 dogImg;
    gm_s16 fishImg;
    gm_s16 boneImg;
    gm_s16 winImg;
    gm_s16 loseImg;
    gm_s16 bombImg;
    gm_s16 windImg;
    gm_s16 buttonImg;
    gm_s16 button;
    gm_s16 beijing;													//��Ϸ����ͼƬ
	gm_s16 lifeImageD;												//��ʾ��Ѫ��ͼ��
	gm_s16 lifeImageC;												//��ʾèѪ��ͼ��
	gm_s16 catPX;													//è��λ��X����
	gm_s8 cattu;													//è��ʾ��ͼ��
	gm_s8 dogtu;													//����ʾ��ͼ��
	gm_s16 isFire;

	/***************************************************Fish��************************************************************/
	gm_s16 fishPX;													//��̵�X����
	gm_s16 fishPY;													//��̵�X����
	gm_bool fishShow;												//�Ƿ���ʾ���
	gm_s8 fishFrame;												//��̵ڼ�֡
	gm_s16 fish_v0;
	gm_s16 fish_i;
	gm_bool fishGo;
	gm_s16 fish_tTemp;
	gm_s16 fish_t1;
	gm_s16 fish_vx1;
	gm_s16 fish_vy1;
	gm_s16 fish_add1;
	
	/***************************************************Bone��************************************************************/
	gm_s16 bonePX;													//��ͷ��X����
	gm_s16 bonePY;													//��ͷ��X����
	gm_bool boneShow;												//�Ƿ���ʾ��ͷ
	gm_s8 boneFrame;												//��ͷ�ڼ�֡
	gm_s16 bone_v02; //��ʼ�ٶ�
  	gm_s16 bone_add2;//���ٶ�
	gm_bool boneGo;	//�Ƿ��˶�
	gm_s16 bone_tTemp2;
	gm_s16 bone_vx2; 
	gm_s16 bone_vy2; //��ͷ�ٶ�
    gm_s16 bone_t2; //��ͷ�׳�ʱ��
  	gm_s16 bone_r;
	gm_s8 bone_i;
	gm_s16 bombFrame;
	gm_bool bombShow;

	
	/***************************************************Wind��************************************************************/
	gm_s16 windn;
	gm_s16 Wind_left;
  	gm_s16 Wind_right;
  	gm_s16 Wind_change;
  	gm_s16 Wind_v;

	/*************************************************LifeC .Class***********************************************************/
	gm_s16 LifeC_lifewc;
	gm_s16 catBlood;												//è��Ѫ��
	
	/*************************************************LifeD.Class***********************************************************/
	gm_s16 dogBlood;												//����Ѫ��
	gm_s16 LifeD_lifew;
    gm_s16 liliangImg;

	gm_s8 bombPX;													//��ըX����
	gm_s8 bombPY;													//��ըY����

	gm_bool teshu;
	//public Sprite cat;		
    //public Sprite dog;
    //public Sprite bomb;
    //public Wind wind;
    //LifeD lifeD;
    //LifeC lifeC;
}CatLoveDog_InGame;

extern void initCatLoveDog_InGame(CatLoveDog_InGame * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repaintMax);
void CatLoveDog_InGame_Windows_Render(void *param);
void CatLoveDog_InGame_Windows_Update(void * param);

#endif

