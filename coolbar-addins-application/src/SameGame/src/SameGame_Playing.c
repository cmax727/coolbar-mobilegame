#include "SameGame_Screen.h"
#include "SameGame_Playing.h"
#include "coolbar_GameUtil.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
void Sleeping_2(int x){
	getManagerPtr()->TIME_Sleep(x);

}
void CopyVRAM(SameGamePlaying * myself, gm_s16 dest[10][12], gm_s16 src[10][12])
{
	gm_s16 i, j;
	for (i = 0; i < myself->VRAM_WIDTH; i++)
	{
		for (j = 0; j < myself->VRAM_HEIGHT; j++)
		{
			dest[j][i] = src[j][i]; // コピー
		}
	}
}

void LoadChip(SameGamePlaying * myself)
{
	gm_s16 i,j,rnd;

	switch(level)
	{
	case 0:
		switch(shape)
		{
		case 0:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"0_0_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"0_0_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"0_0_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"0_0_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"0_0_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"0_0_5.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"0_0_6.gif");
			break;
		case 1:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"1_0_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"1_0_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"1_0_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"1_0_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"1_0_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"1_0_5.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"1_0_6.gif");
			break;
		case 2:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"2_0_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"2_0_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"2_0_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"2_0_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"2_0_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"2_0_5.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"2_0_6.gif");
			break;
		case 3:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"3_0_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"3_0_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"3_0_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"3_0_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"3_0_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"3_0_5.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"3_0_6.gif");
			break;
		case 4:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"4_0_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"4_0_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"4_0_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"4_0_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"4_0_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"4_0_5.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"4_0_6.gif");
			break;
		case 5:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"5_0_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"5_0_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"5_0_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"5_0_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"5_0_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"5_0_5.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"5_0_6.gif");
			break;
		case 6:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"6_0_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"6_0_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"6_0_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"6_0_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"6_0_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"6_0_5.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"6_0_6.gif");
			break;
		}
		myself->chipCount = 6;
		break;

	case 1:
		switch(shape)
		{
		case 0:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"0_1_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"0_1_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"0_1_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"0_1_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"0_1_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"0_1_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"0_1_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"0_1_7.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"0_1_8.gif");
			break;
		case 1:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"1_1_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"1_1_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"1_1_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"1_1_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"1_1_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"1_1_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"1_1_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"1_1_7.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"1_1_8.gif");
			break;
		case 2:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"2_1_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"2_1_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"2_1_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"2_1_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"2_1_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"2_1_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"2_1_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"2_1_7.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"2_1_8.gif");
			break;
		case 3:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"3_1_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"3_1_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"3_1_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"3_1_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"3_1_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"3_1_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"3_1_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"3_1_7.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"3_1_8.gif");
			break;
		case 4:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"4_1_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"4_1_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"4_1_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"4_1_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"4_1_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"4_1_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"4_1_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"4_1_7.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"4_1_8.gif");
			break;
		case 5:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"5_1_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"5_1_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"5_1_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"5_1_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"5_1_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"5_1_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"5_1_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"5_1_7.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"5_1_8.gif");
			break;
		case 6:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"6_1_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"6_1_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"6_1_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"6_1_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"6_1_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"6_1_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"6_1_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"6_1_7.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"6_1_8.gif");
			break;
		}
		myself->chipCount = 8;
		break;

	case 2:
		switch(shape)
		{
		case 0:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"0_2_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"0_2_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"0_2_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"0_2_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"0_2_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"0_2_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"0_2_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"0_2_7.gif");
			myself->Chip[8] = myself->picLib->GetImage(myself->picLib,"0_2_8.gif");
			myself->Chip[9] = myself->picLib->GetImage(myself->picLib,"0_2_9.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"0_2_10.gif");
			break;
		case 1:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"1_2_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"1_2_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"1_2_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"1_2_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"1_2_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"1_2_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"1_2_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"1_2_7.gif");
			myself->Chip[8] = myself->picLib->GetImage(myself->picLib,"1_2_8.gif");
			myself->Chip[9] = myself->picLib->GetImage(myself->picLib,"1_2_9.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"1_2_10.gif");
			break;
		case 2:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"2_2_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"2_2_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"2_2_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"2_2_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"2_2_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"2_2_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"2_2_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"2_2_7.gif");
			myself->Chip[8] = myself->picLib->GetImage(myself->picLib,"2_2_8.gif");
			myself->Chip[9] = myself->picLib->GetImage(myself->picLib,"2_2_9.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"2_2_10.gif");
			break;
		case 3:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"3_2_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"3_2_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"3_2_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"3_2_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"3_2_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"3_2_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"3_2_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"3_2_7.gif");
			myself->Chip[8] = myself->picLib->GetImage(myself->picLib,"3_2_8.gif");
			myself->Chip[9] = myself->picLib->GetImage(myself->picLib,"3_2_9.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"3_2_10.gif");
			break;
		case 4:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"4_2_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"4_2_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"4_2_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"4_2_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"4_2_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"4_2_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"4_2_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"4_2_7.gif");
			myself->Chip[8] = myself->picLib->GetImage(myself->picLib,"4_2_8.gif");
			myself->Chip[9] = myself->picLib->GetImage(myself->picLib,"4_2_9.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"4_2_10.gif");
			break;
		case 5:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"5_2_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"5_2_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"5_2_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"5_2_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"5_2_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"5_2_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"5_2_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"5_2_7.gif");
			myself->Chip[8] = myself->picLib->GetImage(myself->picLib,"5_2_8.gif");
			myself->Chip[9] = myself->picLib->GetImage(myself->picLib,"5_2_9.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"5_2_10.gif");
			break;
		case 6:
			myself->Chip[0] = myself->picLib->GetImage(myself->picLib,"6_2_0.gif");
			myself->Chip[1] = myself->picLib->GetImage(myself->picLib,"6_2_1.gif");
			myself->Chip[2] = myself->picLib->GetImage(myself->picLib,"6_2_2.gif");
			myself->Chip[3] = myself->picLib->GetImage(myself->picLib,"6_2_3.gif");
			myself->Chip[4] = myself->picLib->GetImage(myself->picLib,"6_2_4.gif");
			myself->Chip[5] = myself->picLib->GetImage(myself->picLib,"6_2_5.gif");
			myself->Chip[6] = myself->picLib->GetImage(myself->picLib,"6_2_6.gif");
			myself->Chip[7] = myself->picLib->GetImage(myself->picLib,"6_2_7.gif");
			myself->Chip[8] = myself->picLib->GetImage(myself->picLib,"6_2_8.gif");
			myself->Chip[9] = myself->picLib->GetImage(myself->picLib,"6_2_9.gif");
			myself->ElAnime = myself->picLib->GetImage(myself->picLib,"6_2_10.gif");
			break;
		}
		myself->chipCount = 10;
		break;
	}

	myself->cw = myself->picLib->GetImageWidth(myself->picLib, myself->Chip[0]);
	myself->ch = myself->picLib->GetImageHeight(myself->picLib, myself->Chip[0]);

	switch(level)
	{
	case 0:
		myself->VRAM_WIDTH=7;
		myself->VRAM_HEIGHT=6;
		myself->xbase += ((SCREEN_WIDTH - myself->xbase) - myself->VRAM_WIDTH * myself->cw) / 2;
		myself->ybase += ((SCREEN_HEIGHT - myself->ybase) - myself->VRAM_HEIGHT * myself->ch) / 2;
		break;
	case 1:
		myself->VRAM_WIDTH=10;
		myself->VRAM_HEIGHT=8;
		myself->xbase += ((SCREEN_WIDTH - myself->xbase) - myself->VRAM_WIDTH * myself->cw) / 2;
		myself->ybase += ((SCREEN_HEIGHT - myself->ybase) - myself->VRAM_HEIGHT * myself->ch) / 2;
		break;
	case 2:
		myself->VRAM_WIDTH=12;
		myself->VRAM_HEIGHT=10;
		myself->xbase += ((SCREEN_WIDTH - myself->xbase) - myself->VRAM_WIDTH * myself->cw) / 2;
		myself->ybase += ((SCREEN_HEIGHT - myself->ybase) - myself->VRAM_HEIGHT * myself->ch) / 2;
		break;
	}

	if (newGame == 1)
	{
		for (i = 0; i < myself->VRAM_WIDTH; i++) {
			for (j = 0; j < myself->VRAM_HEIGHT; j++) {
				rnd = Random(0, myself->chipCount-1);
				myself->VRAM[j][i] = myself->VRAM_Undo[j][i] = myself->VRAM_Start[j][i] = rnd % 3;
			}
		}
	}
	else if (newGame == 2)
	{
		CopyVRAM(myself,myself->VRAM,myself->VRAM_Start);
		CopyVRAM(myself,myself->VRAM_Undo,myself->VRAM_Start);
	}
}
 
void DetectChain(SameGamePlaying * myself, int sx, int sy, int kind)
{
	// 範囲外なら終了
	if (sx < 0 || sx > myself->VRAM_WIDTH - 1)
		return;
	if (sy < 0 || sy > myself->VRAM_HEIGHT - 1)
		return;
	
	// 指定された場所がkindと同じ種類ならキューに追加する
	if (myself->VRAM[sy][sx] == kind)
	{
		int i;
		for (i = 0; i < myself->ChainNum; i++)
		{
			if (myself->ChainQueueX[i] == sx && myself->ChainQueueY[i] == sy)
				return;
		}
		myself->ChainQueueX[myself->ChainNum] = sx;
		myself->ChainQueueY[myself->ChainNum] = sy;
		myself->ChainNum++;
		
		DetectChain(myself, sx, sy - 1, kind); // 上
		DetectChain(myself, sx, sy + 1, kind); // 下
		DetectChain(myself, sx - 1, sy, kind); // 左
		DetectChain(myself, sx + 1, sy, kind); // 右
	}
}

void DrawAll(SameGamePlaying * myself, gm_bool cf)
{
	gm_s16 i, j, sx;
	VMSTR score;

	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,myself->C_BACKGROUND);

	// VRAMにしたがってチップを描画
	for (i = 0; i < myself->VRAM_WIDTH; i++)
	{
		for (j = 0; j < myself->VRAM_HEIGHT; j++)
		{
			int stat = myself->VRAM[j][i];
			if (stat != -1) {
				// 消去アニメーションかどうかを調べる
				if ((stat & 0x000F0000) != 0)
				{
					myself->picLib->DrawImageEx(myself->picLib, myself->ElAnime, myself->xbase + i * myself->cw, myself->ybase + j * myself->ch, true, 0);
				}
				else if ((stat & 0x0000FF00) != 0) // 選択アニメーションかどうかを調べる
				{
					int cid = (stat & 0xFF) + myself->chipCount / 2;
					myself->picLib->DrawImageEx(myself->picLib, myself->Chip[cid], myself->xbase + i * myself->cw, myself->ybase + j * myself->ch, true, 0);
				}
				else
				{
					myself->picLib->DrawImageEx(myself->picLib, myself->Chip[stat], myself->xbase + i * myself->cw, myself->ybase + j * myself->ch, true, 0);
				}
			}
		}
	}
	// カーソル描画
	if (cf)
		myself->picLib->DrawImageEx(myself->picLib, myself->i_cursor, myself->xbase + (2 * myself->cx + 1) * (myself->cw / 2), myself->ybase + (2 * myself->cy + 1) * (myself->ch / 2), false, 0);

	getManagerPtr()->DrawString("Score",40,0,myself->ybase-24,myself->C_TEXTCOLOR);
	score = manager_my->formatString("%d",myself->Score);
	sx = extVmLcdManager->VMGetStringWidth(score);
	getManagerPtr()->DrawString(score,40,SCREEN_WIDTH-sx,myself->ybase-24,myself->C_TEXTCOLOR);

	getManagerPtr()->DrawString("复原",40, 0,SCREEN_HEIGHT-extVmLcdManager->VMGetStringHeight("复原"),0xFFFF00);
	getManagerPtr()->DrawString("菜单",40, SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("菜单"),SCREEN_HEIGHT-extVmLcdManager->VMGetStringHeight("菜单"),0xFFFF00);
}


void Eliminate(SameGamePlaying * myself)
{
	gm_s16 i;
	if (myself->ChainNum <= 1)
	{
		myself->ChainNum = 0;
		return;
	}
	
	// すべて一度に変化するアニメーション
	for (i = 0; i < myself->ChainNum; i++)
	{
		myself->VRAM[myself->ChainQueueY[i]][myself->ChainQueueX[i]] = 0x00010000;
	}
	DrawAll(myself, false);
	Sleeping_2(30);
	
	// 最終的には非表示にする
	for (i = 0; i < myself->ChainNum; i++)
	{
		myself->VRAM[myself->ChainQueueY[i]][myself->ChainQueueX[i]] = -1;
	}
	myself->UndoScore = myself->Score;
	myself->Score += ((myself->ChainNum - 1) * (myself->ChainNum - 1) * 10);
}

void PackSpace(SameGamePlaying * myself)
{
	gm_s16 i, j; // , k;
	gm_bool flag = true;
	// 縦方向の落下
	while (flag)
	{
		flag = false;
		for (i = 0; i < myself->VRAM_WIDTH; i++)
		{
			for (j = 0; j < myself->VRAM_HEIGHT - 1; j++)
			{
				if (myself->VRAM[j][i] != -1 && myself->VRAM[j + 1][i] == -1)
				{
					myself->VRAM[j + 1][i] = myself->VRAM[j][i];
					myself->VRAM[j][i] = -1;
					flag = true;
				}
			}
		}
		DrawAll(myself, false);
		Sleeping(30);
	}
	// 横方向の移動
	flag = true;
	while (flag)
	{
		flag = false;
		for (i = 0; i < myself->VRAM_WIDTH - 1; i++)
		{
			// 縦方向の落下はすべて処理済なので一番下が空なら１列すべて空になる
			if (myself->VRAM[myself->VRAM_HEIGHT - 1][i] == -1 && myself->VRAM[myself->VRAM_HEIGHT - 1][i + 1] != -1)
			{
				for (j = 0; j < myself->VRAM_HEIGHT; j++)
				{
					myself->VRAM[j][i] = myself->VRAM[j][i + 1];
					myself->VRAM[j][i + 1] = -1;
				}
				flag = true;
			}
		}
		DrawAll(myself, false);
		Sleeping(30);
	}
}

gm_bool Impossible(SameGamePlaying * myself)
{
	gm_s16 i, j;
	// 指定された場所の上下左右に自分と同じチップがあればまだ手詰まりにはならない
	for (i = 0; i < myself->VRAM_WIDTH - 1; i++)
	{
		for (j = 0; j < myself->VRAM_HEIGHT; j++)
		{
			if (myself->VRAM[j][i] == -1)
				continue;
			if (myself->VRAM[j][i] == myself->VRAM[j][i + 1])
				return false;
		}
	}

	for (i = 0; i < myself->VRAM_WIDTH; i++)
	{
		for (j = 0; j < myself->VRAM_HEIGHT - 1; j++)
		{
			if (myself->VRAM[j][i] == -1)
				continue;
			if (myself->VRAM[j][i] == myself->VRAM[j + 1][i])
				return false;
		}
	}

	return true;
}

void PopupBalloon(int time)
{
	Sleeping(time);

	sameGameTitleState = SAMEGAME_STATE_COMPLETEMENU;
	sameGame_Screen_Next=&sameGame_Screen_Title;
	SCREEN_ChangeScreen(&sameGame_Screen_Loading);
}

void KeyClear(SameGamePlaying * myself)
{
	myself->SoftKey1 = myself->SoftKey2 = myself->KeyUp = myself->KeyDown = myself->KeyLeft = myself->KeyRight = myself->KeyEnter = false;
}

void CheckComplete(SameGamePlaying * myself)
{
	gm_s16 mid;

	// 終了条件のチェック
	if (myself->VRAM[myself->VRAM_HEIGHT - 1][0] == -1)
 		completeState = 2; // パーフェクト
	else if (Impossible(myself))
 		completeState = 1; // 手詰まり

	if (completeState != 0)
	{
		if (myself->HighScore[myself->GameLevel] < myself->Score)
		{
			myself->HighScore[myself->GameLevel] = myself->Score;
			SameGame_Update_Record(myself->GameLevel,myself->Score);
			SameGame_Read_Record();
			PopupBalloon(1000);
		}
		else
		{
			PopupBalloon(1000);
		}

		KeyClear(myself);
	}
}

void Actions(SameGamePlaying * myself)
{
	if (myself->KeyEnter)
	{
		// すでに消されているところなら何もしない
		if (myself->VRAM[myself->cy][myself->cx] != -1 && myself->ChainNum > 1) {
			CopyVRAM(myself, myself->VRAM_Undo, myself->VRAM); // VRAM_Undo ← VRAM
			Eliminate(myself);
			PackSpace(myself);
			CheckComplete(myself);
		}
	}
	else if (myself->KeyUp)
	{
		if (myself->cy != 0)
			myself->cy--;
	}
	else if (myself->KeyDown)
	{
		if (myself->cy != myself->VRAM_HEIGHT - 1)
			myself->cy++;
	}
	else if (myself->KeyLeft)
	{
		if (myself->cx != 0)
			myself->cx--;
	}
	else if (myself->KeyRight)
	{
		if (myself->cx != myself->VRAM_WIDTH - 1)
			myself->cx++;
	}
	else if (myself->SoftKey1)
	{
		if (myself->InPlaying)
		{
			CopyVRAM(myself, myself->VRAM, myself->VRAM_Undo); // VRAM ← VRAM_Undo
			myself->Score = myself->UndoScore;
		}
	}
	else if (myself->SoftKey2)
	{
		sameGameTitleState = SAMEGAME_STATE_PLAYMENU;
		sameGame_Screen_Next=&sameGame_Screen_Title;
		SCREEN_ChangeScreen(&sameGame_Screen_Loading);
	}
	KeyClear(myself);
}

void Main_While(SameGamePlaying * myself)
{
	gm_s16 i,j;
	myself->ChainNum = 0;
	if (myself->VRAM[myself->cy][myself->cx] != -1)
		DetectChain(myself, myself->cx, myself->cy, myself->VRAM[myself->cy][myself->cx]);
	if (myself->ChainNum > 1) {
		// HighLightOn
		for (i = 0; i < myself->ChainNum; i++) {
			if (myself->VRAM[myself->ChainQueueY[i]][myself->ChainQueueX[i]] < 0x100)
				myself->VRAM[myself->ChainQueueY[i]][myself->ChainQueueX[i]] += 0x100;
		}
		DrawAll(myself, true);
		// HighLightOff
		for (i = 0; i < myself->VRAM_WIDTH; i++) {
			for (j = 0; j < myself->VRAM_HEIGHT; j++) {
				if (myself->VRAM[j][i] >= 0x100)
					myself->VRAM[j][i] -= 0x100;
			}
		}
	} else {
		myself->ChainNum = 0;
		DrawAll(myself, true);
	}
	Actions(myself);
}

void SameGame_KeyPressed(SameGamePlaying * myself) 
{
	gm_s16 px, py, i, j;
	if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))//按右软键返回主菜单
		myself->SoftKey2 = true;
	if(getManagerPtr()->IsKeyDown(MF_KEY_LEFTSOFT))//按右软键返回主菜单
		myself->SoftKey1 = true;
	if(getManagerPtr()->IsKeyDown(MF_KEY_2 | MF_KEY_UP))//按上下左右移动光标
		myself->KeyUp = true;
	if(getManagerPtr()->IsKeyDown(MF_KEY_8 | MF_KEY_DOWN)) 
		myself->KeyDown = true;
	if(getManagerPtr()->IsKeyDown(MF_KEY_4 | MF_KEY_LEFT))
		myself->KeyLeft = true;
	if(getManagerPtr()->IsKeyDown(MF_KEY_6 | MF_KEY_RIGHT))
		myself->KeyRight = true;
	if(getManagerPtr()->IsKeyDown(MF_KEY_5 | MF_KEY_MID))//按空格键选择块
		myself->KeyEnter = true;
	if(SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX() - myself->xbase;
		py = SCREEN_GetPointerY() - myself->ybase;
		for(i=0;i<myself->VRAM_WIDTH;i++)
		{
			for(j=0;j<myself->VRAM_HEIGHT;j++)
			{
				if(CdRectPoint(i*myself->cw,j*myself->ch,(i+1)*myself->cw, (j+1)*myself->ch,px,py))
				{
					myself->cx = i;
					myself->cy = j;
					myself->picLib->DrawImageEx(myself->picLib, myself->i_cursor, myself->xbase + (2 * myself->cx + 1) * (myself->cw / 2), myself->ybase + (2 * myself->cy + 1) * (myself->ch / 2), false, 0);
					myself->KeyEnter = true;
				}
			}
		}
	}
}

void SameGame_Playing_Init(SameGamePlaying * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repaintMax)
{
	gm_s16 i;
	initDFWindows(&myself->windows,windows_Rect,myself,myself,repaintMax);
	myself->windows.RenderCallBack=SameGame_Playing_Render;
    myself->windows.UpdateCallBack=SameGame_Playing_Update;
	myself->picLib=picLib;
	
	myself->C_BACKGROUND = GAME_ToRGB(0,146,0);
	myself->C_TEXTCOLOR = GAME_ToRGB(255,255,255);
	myself->C_BACKGROUND_F = GAME_ToRGB(228,36,20);
	myself->C_TEXTCOLOR_F = GAME_ToRGB(0,0,0);
	myself->i_cursor = myself->picLib->GetImage(myself->picLib,"cursor.gif");
	myself->xbase = 0;
	myself->ybase = 20;
	myself->Score = 0;
	myself->InPlaying = true;
	myself->GameLevel = level;
	myself->cx = myself->cy = myself->cw = myself->ch = 0;
	for (i=0; i<3; i++)
		myself->HighScore[i] = sameGameHighTimeValue[i];
	
	LoadChip(myself);
}

void SameGame_Playing_Render(void *param)
{
	SameGamePlaying * myself = (SameGamePlaying *)param;
	Main_While(myself);
}

void SameGame_Playing_Update(void * param)
{
	SameGamePlaying * myself = (SameGamePlaying *)param;
	SameGame_KeyPressed(myself);
	Main_While(myself);
}

