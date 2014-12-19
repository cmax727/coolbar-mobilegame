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

	gm_s16 HighScore[3]; // ハイスコア( 初級、中級、上級 )
	gm_s16 Score; // スコア
	gm_s16 UndoScore; // 一つ前のスコア
	tRGB C_BACKGROUND; // チップ描画領域の背景色
	tRGB C_TEXTCOLOR; // 文字列表示色
	tRGB C_BACKGROUND_F; // カーソル位置の背景色
	tRGB C_TEXTCOLOR_F; // 文字列表示色(反転)
	gm_s16 xbase, ybase; // 枠をのぞいたチップ表示領域のオフセット
	gm_s16 cx, cy; // カーソル位置
	gm_s16 cw, ch; // チップサイズ
	gm_s16 GameLevel; // ゲームの難易度
	gm_s16 VRAM_WIDTH, VRAM_HEIGHT; // ゲーム難易度によって決まるフィールドサイズ
	gm_s16 ChainQueueX[12*10]; // 連鎖情報をしまうキューX座標( VRAM_WIDTH * VRAM_HEIGHT 個 )
	gm_s16 ChainQueueY[12*10]; // 連鎖情報をしまうキューY座標( VRAM_WIDTH * VRAM_HEIGHT 個 )
	gm_s16 ChainNum; // 連鎖した数
	gm_s16 VRAM[10][12]; // VRAM情報(チップのイメージIDを示す。存在しないときは -1 )
	gm_s16 VRAM_Undo[10][12]; // Undo用のVRAM
	gm_s16 VRAM_Start[10][12]; // Start時のマップを保存するためのVRAM
	gm_s16 Chip[11]; // 実際に表示するチップ
	gm_s16 ElAnime; // 消去用アニメーションチップ
	gm_s16 i_cursor; // カーソルチップ画像
// 	Font ScoreFont; // スコア表示用のフォント
// 	Font df; // デフォルトのフォント(12dot を探す)
// 	Font sf; // 小さいフォント(10dot を探す)
// 	String ChipNames[] = { "タイル", "玉", "ボンバーマン１", "ボンバーマン２", "数字", "図形", "ウェッビー" };
	gm_bool SoftKey1, SoftKey2, KeyUp, KeyDown, KeyLeft, KeyRight, KeyEnter; // キーイベント保存フラグ
	gm_bool finished; // ゲーム終了フラグ
	gm_bool quit; // メインループを抜けるフラグ
	gm_bool InPlaying; // ゲームプレイ中なら true

	gm_s16 chipCount;
	
// 	gm_bool gameexit;//判断游戏是否结束    	//
// 	gm_s16 jishi;									//
// 	gm_s16 score;//玩家分数    
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
// 	gm_s16 zhuangtai; //--进入游戏后的状态 0没有块被翻开，1有一个块被翻开，2两个块被翻开，此时禁止选择，3全部的块都被翻开，过关，4时间到 GAMEOVER
// 	gm_s16 mendis;//--难度选择上手型图标y方向移动的距离
// 	gm_s16 guangbiaox;//游戏过程中光标（白框）的位置:x(0-3）,y:(0-4)
// 	gm_s16 guangbiaoy;
// 	gm_s16 clipx1 ;//记录下被翻开的第一个块的x,y
// 	gm_s16 clipy1;
// 	gm_s16 clipx2 ;//记录下被翻开的第二个块的x,y
// 	gm_s16 clipy2;
// 	gm_s16 picw;   //--每个块的宽高
// 	gm_s16 pich;	//
// 	gm_s16 x0;  //--最左上块的位置
// 	gm_s16 y0;//
// 	gm_s16 opennum;//已经找到的图片对数
// 	gm_s16 sourcetime;//--剩余时间，练习模式下为使用时间
// 	gm_s16 temptime;//累加时间，每加10次为1秒
// 	gm_s16 starttime;
// 	gm_s16 tempstarttime;//确保两个图片翻开后1秒钟后再翻回去
// 	gm_bool ingame;//--是否正在游戏，让时间运行
// 	gm_bool soundopen;//--游戏声音开关
// 	gm_bool gameoverl;
// 	gm_s16 time;

}SameGamePlaying;

void SameGame_Playing_Init(SameGamePlaying * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repagm_s16Max);
void SameGame_Playing_Render(void *param);
void SameGame_Playing_Update(void * param);

#endif

