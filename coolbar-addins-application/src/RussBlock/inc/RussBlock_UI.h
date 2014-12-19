/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* �ļ����ƣ�RussBlock_UI.h

�˹�������Ϸ��UI���棬���ɼ�����Ϸ����Ҫˢ������������Ϸ�ٶ�,����ȥˢ����Ļ
*******************************************************************/

#ifndef RUSSBLOCK_UI_H
#define RUSSBLOCK_UI_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
//#include "DF_Actor.h"




typedef struct RUSSBLOCK_UI 
{
	gm_s32 score;  //��ҵ÷�
	gm_s32 clearedlayer; //��������
	gm_s32 level;   //��ҵȼ�

	gm_s32 lastClearedLayer;   //�ϴ����Ĳ���
	gm_s32 hitNum;  //������
	gm_bool flag_hit;     /*����������־*/
	gm_s16 hitCount;	/*����������ʾ����*/
	gm_bool flag_action;   /*Ů���沿�����Ƿ񼤻�*/
	gm_s16 action;      /*Ů���������ͱ�־ 0Ϊ���� 1Ϊ��1�� 2Ϊ��2�� 3Ϊ��3�� 4Ϊ��4�� 5Ϊʧ��*/
	//DF_Actor actorGirlFace;
//#ifdef GAME_240_320
	gm_s16 imgUI[5];//UI�����е�ͼƬ��
	gm_s16 imgGirl;
	gm_s16 imgHiteffect;   //����Ч��ͼ
	gm_s16 imgTime;
	gm_s16 imgPropBar;
	gm_s16 imgPropNum;
	gm_s16 imgPropKey;
	gm_s16 imgCmd;
	gm_s16 imgClear;
//#endif
	DF_Windows windows;//UI�д���
	DF_PictureLibrary *picLib;//UI��ͼƬ��
	//UI��ˢ������
	void (*UpdateScore)(struct RUSSBLOCK_UI *myself);
	void (*UpdateClearedLayer)(struct RUSSBLOCK_UI * myself);
	void (*UpdateLevel)(struct RUSSBLOCK_UI * myself);
	void (*UpdateRect)(struct RUSSBLOCK_UI * myself,gm_s16 x,gm_s16 y,gm_s16 w,gm_s16 h);
	void (*UpdateGirlFace)(struct RUSSBLOCK_UI * myself,gm_s16 action);
	void (*UpdateNextBlockArea)(struct RUSSBLOCK_MAP * myself);
}RussBlockUi;
//UI��ˢ�º���
extern void initRussBlockUi(RussBlockUi * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib,gm_s32 score,gm_s32 clearedlayer);
void RussBlock_UI_Windows_Render(void * param);
void RussBlock_UI_Windows_Update(void * param);
void RussBlock_UI_UpdateScore(RussBlockUi * myself);
void RussBlock_UI_UpdateClearedLayer(RussBlockUi * myself);
void RussBlock_UI_UpdateLevel(RussBlockUi * myself);
void RussBlock_UI_UpdateRect(RussBlockUi * myself,gm_s16 x,gm_s16 y,gm_s16 w,gm_s16 h);
void RussBlock_UI_UpdateGirlFace(RussBlockUi * myself,gm_s16 action);/*�ⲿ���ã�Ů������仯*/
static void UpdateGirlFace1(void * param);

#endif