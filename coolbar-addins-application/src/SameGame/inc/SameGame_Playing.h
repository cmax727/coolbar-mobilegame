#ifndef SAMEGAME_PLAY_H
#define SAMEGAME_PLAY_H

#include "DF_Windows.h"
#include "DF_PictureLibrary.h"
#include "SameGame_Screen.h"
#include "SameGame_PlayMenu.h"

extern gm_s16 completeState;

typedef struct SAMEGAME_PLAYING
{
	DF_PictureLibrary * picLib;
	DF_Windows windows;

	gm_s16 HighScore[3]; // �ϥ�������( �������м����ϼ� )
	gm_s16 Score; // ������
	gm_s16 UndoScore; // һ��ǰ�Υ�����
	tRGB C_BACKGROUND; // ���å��軭�I��α���ɫ
	tRGB C_TEXTCOLOR; // �����б�ʾɫ
	tRGB C_BACKGROUND_F; // ���`����λ�äα���ɫ
	tRGB C_TEXTCOLOR_F; // �����б�ʾɫ(��ܞ)
	gm_s16 xbase, ybase; // ����Τ��������åױ�ʾ�I��Υ��ե��å�
	gm_s16 cx, cy; // ���`����λ��
	gm_s16 cw, ch; // ���åץ�����
	gm_s16 GameLevel; // ���`����y�׶�
	gm_s16 VRAM_WIDTH, VRAM_HEIGHT; // ���`���y�׶Ȥˤ�äƛQ�ޤ�ե��`��ɥ�����
	gm_s16 ChainQueueX[12*10]; // �B�i���򤷤ޤ�����`X����( VRAM_WIDTH * VRAM_HEIGHT �� )
	gm_s16 ChainQueueY[12*10]; // �B�i���򤷤ޤ�����`Y����( VRAM_WIDTH * VRAM_HEIGHT �� )
	gm_s16 ChainNum; // �B�i������
	gm_s16 VRAM[10][12]; // VRAM���(���åפΥ���`��ID��ʾ�������ڤ��ʤ��Ȥ��� -1 )
	gm_s16 VRAM_Undo[10][12]; // Undo�ä�VRAM
	gm_s16 VRAM_Start[10][12]; // Start�r�Υޥåפ򱣴椹�뤿���VRAM
	gm_s16 Chip[11]; // �g�H�˱�ʾ������å�
	gm_s16 ElAnime; // ��ȥ�å��˥�`�������å�
	gm_s16 i_cursor; // ���`������å׻���
// 	Font ScoreFont; // ��������ʾ�äΥե����
// 	Font df; // �ǥե���ȤΥե����(12dot ��̽��)
// 	Font sf; // С�����ե����(10dot ��̽��)
// 	String ChipNames[] = { "������", "��", "�ܥ�Щ`�ޥ�", "�ܥ�Щ`�ޥ�", "����", "����", "�����åө`" };
	gm_bool SoftKey1, SoftKey2, KeyUp, KeyDown, KeyLeft, KeyRight, KeyEnter; // ���`���٥�ȱ���ե饰
	gm_bool finished; // ���`��K�˥ե饰
	gm_bool quit; // �ᥤ���`�פ�i����ե饰
	gm_bool InPlaying; // ���`��ץ쥤�Фʤ� true

	gm_s16 chipCount;
	
// 	gm_bool gameexit;//�ж���Ϸ�Ƿ����    	//
// 	gm_s16 jishi;									//
// 	gm_s16 score;//��ҷ���    
// 	gm_s16 rand;
// 	gm_s16 imgLog[2];
// 	gm_s16 imgLaba;
// 	gm_s16 imgBeijing;
// 	gm_s16 imgTupian;
// 	gm_s16 imgDipian;
// 	gm_s16 imgBei;
// 	gm_s16 imgGuangbiao;
// 	gm_s16 imgGameOver;
// 	gm_s16 imgWin;
// 	gm_s16 imgPojilu;
// 	gm_s16 imgQueingfanhui;
// 	gm_s16 imgJinxingxiayiguan;
// 	gm_s16 screenwidth;
// 	gm_s16 screenheight;
// 	gm_bool pojilu;								//
// 	gm_s16 zhuangtai; //--������Ϸ���״̬ 0û�п鱻������1��һ���鱻������2�����鱻��������ʱ��ֹѡ��3ȫ���Ŀ鶼�����������أ�4ʱ�䵽 GAMEOVER
// 	gm_s16 mendis;//--�Ѷ�ѡ��������ͼ��y�����ƶ��ľ���
// 	gm_s16 guangbiaox;//��Ϸ�����й�꣨�׿򣩵�λ��:x(0-3��,y:(0-4)
// 	gm_s16 guangbiaoy;
// 	gm_s16 clipx1 ;//��¼�±������ĵ�һ�����x,y
// 	gm_s16 clipy1;
// 	gm_s16 clipx2 ;//��¼�±������ĵڶ������x,y
// 	gm_s16 clipy2;
// 	gm_s16 picw;   //--ÿ����Ŀ��
// 	gm_s16 pich;	//
// 	gm_s16 x0;  //--�����Ͽ��λ��
// 	gm_s16 y0;//
// 	gm_s16 opennum;//�Ѿ��ҵ���ͼƬ����
// 	gm_s16 sourcetime;//--ʣ��ʱ�䣬��ϰģʽ��Ϊʹ��ʱ��
// 	gm_s16 temptime;//�ۼ�ʱ�䣬ÿ��10��Ϊ1��
// 	gm_s16 starttime;
// 	gm_s16 tempstarttime;//ȷ������ͼƬ������1���Ӻ��ٷ���ȥ
// 	gm_bool ingame;//--�Ƿ�������Ϸ����ʱ������
// 	gm_bool soundopen;//--��Ϸ��������
// 	gm_bool gameoverl;
// 	gm_s16 time;

}SameGamePlaying;

void SameGame_Playing_Init(SameGamePlaying * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repagm_s16Max);
void SameGame_Playing_Render(void *param);
void SameGame_Playing_Update(void * param);

#endif

