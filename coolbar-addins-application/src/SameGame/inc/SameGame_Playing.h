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

	gm_s16 HighScore[3]; // ハイスコア( 兜��、嶄��、貧�� )
	gm_s16 Score; // スコア
	gm_s16 UndoScore; // 匯つ念のスコア
	tRGB C_BACKGROUND; // チップ宙鮫�I囃の嘘尚弼
	tRGB C_TEXTCOLOR; // 猟忖双燕幣弼
	tRGB C_BACKGROUND_F; // カ�`ソル了崔の嘘尚弼
	tRGB C_TEXTCOLOR_F; // 猟忖双燕幣弼(郡��)
	gm_s16 xbase, ybase; // ��をのぞいたチップ燕幣�I囃のオフセット
	gm_s16 cx, cy; // カ�`ソル了崔
	gm_s16 cw, ch; // チップサイズ
	gm_s16 GameLevel; // ゲ�`ムの�y叟業
	gm_s16 VRAM_WIDTH, VRAM_HEIGHT; // ゲ�`ム�y叟業によって�Qまるフィ�`ルドサイズ
	gm_s16 ChainQueueX[12*10]; // �B�i秤�鵑鬚靴泙Ε�ュ�`X恙��( VRAM_WIDTH * VRAM_HEIGHT �� )
	gm_s16 ChainQueueY[12*10]; // �B�i秤�鵑鬚靴泙Ε�ュ�`Y恙��( VRAM_WIDTH * VRAM_HEIGHT �� )
	gm_s16 ChainNum; // �B�iした方
	gm_s16 VRAM[10][12]; // VRAM秤��(チップのイメ�`ジIDを幣す。贋壓しないときは -1 )
	gm_s16 VRAM_Undo[10][12]; // Undo喘のVRAM
	gm_s16 VRAM_Start[10][12]; // Start�rのマップを隠贋するためのVRAM
	gm_s16 Chip[11]; // �g�Hに燕幣するチップ
	gm_s16 ElAnime; // ��肇喘アニメ�`ションチップ
	gm_s16 i_cursor; // カ�`ソルチップ鮫��
// 	Font ScoreFont; // スコア燕幣喘のフォント
// 	Font df; // デフォルトのフォント(12dot を冥す)
// 	Font sf; // 弌さいフォント(10dot を冥す)
// 	String ChipNames[] = { "タイル", "囁", "ボンバ�`マン１", "ボンバ�`マン２", "方忖", "�輟�", "ウェッビ�`" };
	gm_bool SoftKey1, SoftKey2, KeyUp, KeyDown, KeyLeft, KeyRight, KeyEnter; // キ�`イベント隠贋フラグ
	gm_bool finished; // ゲ�`ム�K阻フラグ
	gm_bool quit; // メインル�`プを�iけるフラグ
	gm_bool InPlaying; // ゲ�`ムプレイ嶄なら true

	gm_s16 chipCount;
	
// 	gm_bool gameexit;//登僅嗄老頁倦潤崩    	//
// 	gm_s16 jishi;									//
// 	gm_s16 score;//螺社蛍方    
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
// 	gm_s16 zhuangtai; //--序秘嗄老朔議彜蓑 0短嗤翠瓜鍬蝕��1嗤匯倖翠瓜鍬蝕��2曾倖翠瓜鍬蝕��緩扮鋤峭僉夲��3畠何議翠脅瓜鍬蝕��狛購��4扮寂欺 GAMEOVER
// 	gm_s16 mendis;//--佃業僉夲貧返侏夕炎y圭�鰔洞�議鉦宣
// 	gm_s16 guangbiaox;//嗄老狛殻嶄高炎�┛弯鬘�議了崔:x(0-3��,y:(0-4)
// 	gm_s16 guangbiaoy;
// 	gm_s16 clipx1 ;//芝村和瓜鍬蝕議及匯倖翠議x,y
// 	gm_s16 clipy1;
// 	gm_s16 clipx2 ;//芝村和瓜鍬蝕議及屈倖翠議x,y
// 	gm_s16 clipy2;
// 	gm_s16 picw;   //--耽倖翠議錐互
// 	gm_s16 pich;	//
// 	gm_s16 x0;  //--恷恣貧翠議了崔
// 	gm_s16 y0;//
// 	gm_s16 opennum;//厮将孀欺議夕頭斤方
// 	gm_s16 sourcetime;//--複噫扮寂��膳楼庁塀和葎聞喘扮寂
// 	gm_s16 temptime;//拙紗扮寂��耽紗10肝葎1昼
// 	gm_s16 starttime;
// 	gm_s16 tempstarttime;//鳩隠曾倖夕頭鍬蝕朔1昼嶝朔壅鍬指肇
// 	gm_bool ingame;//--頁倦屎壓嗄老��斑扮寂塰佩
// 	gm_bool soundopen;//--嗄老蕗咄蝕購
// 	gm_bool gameoverl;
// 	gm_s16 time;

}SameGamePlaying;

void SameGame_Playing_Init(SameGamePlaying * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repagm_s16Max);
void SameGame_Playing_Render(void *param);
void SameGame_Playing_Update(void * param);

#endif

