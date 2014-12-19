#ifndef MEMORYBOX_PLAY_H
#define MEMORYBOX_PLAY_H

#include "DF_Windows.h"
#include "MemoryBox_Screen.h"
#include "DF_PictureLibrary.h"
typedef struct MEMORYBOX_PLAY
{
	DF_PictureLibrary * picLib;
  	DF_Windows windows;
    gm_bool gameexit;//�ж���Ϸ�Ƿ����    	//
    gm_s16 jishi;									//
    gm_s16 score;//��ҷ���    
    gm_s16 rand;
    gm_s32 imgLog[2];
	gm_s32 imgLaba;
	gm_s32 imgBeijing;
	gm_s32 imgTupian;
	gm_s32 imgDipian;
	gm_s32 imgBei;
	gm_s32 imgGuangbiao;
	gm_s32 imgGameOver;
	gm_s32 imgWin;
	gm_s32 imgPojilu;
	gm_s32 imgQueingfanhui;
	gm_s32 imgJinxingxiayiguan;
    gm_s32 screenwidth;
    gm_s32 screenheight;
    gm_bool pojilu;								//
    gm_s16 zhuangtai; //--������Ϸ���״̬ 0û�п鱻������1��һ���鱻������2�����鱻��������ʱ��ֹѡ��3ȫ���Ŀ鶼�����������أ�4ʱ�䵽 GAMEOVER
    gm_s16 mendis;//--�Ѷ�ѡ��������ͼ��y�����ƶ��ľ���
    gm_s16 guangbiaox;//��Ϸ�����й�꣨�׿򣩵�λ��:x(0-3��,y:(0-4)
    gm_s16 guangbiaoy;
    gm_s16 clipx1 ;//��¼�±������ĵ�һ�����x,y
    gm_s16 clipy1;
    gm_s16 clipx2 ;//��¼�±������ĵڶ������x,y
    gm_s16 clipy2;
    gm_s16 picw;   //--ÿ����Ŀ��
    gm_s16 pich;	//
    gm_s16 x0;  //--�����Ͽ��λ��
    gm_s16 y0;//
    gm_s16 opennum;//�Ѿ��ҵ���ͼƬ����
    gm_s16 sourcetime;//--ʣ��ʱ�䣬��ϰģʽ��Ϊʹ��ʱ��
    gm_s16 temptime;//�ۼ�ʱ�䣬ÿ��10��Ϊ1��
    gm_s16 starttime;
    gm_s16 tempstarttime;//ȷ������ͼƬ������1���Ӻ��ٷ���ȥ
    gm_bool ingame;//--�Ƿ�������Ϸ����ʱ������
    gm_bool soundopen;//--��Ϸ��������
    gm_bool gameoverl;
	gm_s32 time;

}MemoryBoxplay;
extern void initMemoryBoxplay(MemoryBoxplay * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repaintMax);
void MemoryBox_Play_Windows_Render(void *param);
void MemoryBox_Play_Windows_Update(void * param);
#endif

