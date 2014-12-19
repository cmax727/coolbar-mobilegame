#include "HitMole_Screen.h"
#include "HitMolePlay.h"
#include "coolbar_GameUtil.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

gm_s16 addlife[10]={100,300,600,1000,1500,2100,2800,3600,4500,5500};//�Զ���ʱ�������������Ҫ�ķ�����
gm_s16 chixushijianbiao[9]={10,10,10,7,7,7,5,5,5};//ÿ�ص�����ֵĳ���ʱ���
gm_s16 shunum[9]={20,30,40,50,60,70,80,90,100};//ÿ���Ѷ�������ֵĸ���
static Manager manager;
void initHitMoleplay(HitMoleplay * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repaintMax)
{
	initManager(&manager);
	initDFWindows(&myself->windows,windows_Rect,myself,myself,repaintMax);
	myself->windows.RenderCallBack=HitMole_Play_Windows_Render;
    myself->windows.UpdateCallBack=HitMole_Play_Windows_Update;
	myself->picLib=picLib;
	myself->score = 0;
	#ifdef GAME_240_320
		myself->biaotiweizhi=60;
		myself->chuiziweizhi=60;
		myself->x_point=4;
		myself->y_point=64;
		myself->x_jiange=80;
		myself->y_jiange=80;
		myself->dongwidth=70;
		myself->dongheight=60;
	#endif
	#ifdef GAME_176_220
		myself->biaotiweizhi=35;
		myself->chuiziweizhi=35;
		myself->x_point=3;
		myself->y_point=40;
		myself->x_jiange=60;
		myself->y_jiange=50;
		myself->dongwidth=50;
		myself->dongheight=42;
	#endif
		HitMole_Loading_UpdateStep();
		myself->keyifanhui=false;
		myself->pojilu=false;
		myself->gameexit=false;
		myself->gamepause=false;
		HitMole_Loading_UpdateStep();
		myself->soundopen=true;
		myself->jishi=0;
		HitMole_Loading_UpdateStep();
		myself->imglaba = picLib->GetImage(picLib,"laba.gif");
		myself->imgbeijing = picLib->GetImage(picLib,"beijing1.gif");
		HitMole_Loading_UpdateStep();
		myself->imgdishu=picLib->GetImage(picLib,"dishu1.gif"); 
		myself->imgchuizi=picLib->GetImage(picLib,"chuizi1.gif");
		myself->shuxintime = 0;
		HitMole_Loading_UpdateStep();
}

gm_u8 what_jiange(HitMoleplay * myself)
{
	gm_s16 jiange=0;
	   switch(level)
	{	
		 case 1:
		 jiange=15;
		 break;
		 case 2:
		 jiange=10 + Random(0,5);
		 break;
		 case 3:
		 jiange=4 +  Random(0,13);
		 break;
		 case 4:
		 jiange=9;
		 break;
		 case 5:
		 jiange=5 +  Random(0,6);
		 break;
		 case 6:
		 jiange=2 + Random(0,10);
		 break;
		 case 7:
		 jiange=6;
		 break;
		 case 8:
		 jiange=3 + Random(0,4);
		 break;
		 case 9:
		 jiange=1 + Random(0,6);
		 break;
		}
	return jiange;
}					   
//ÿ�ֳ�ʼ��
void init(HitMoleplay * myself)
{
	gm_s16 i;
	if(level<7 && level>=4)
	{
	  myself->imgdishu=myself->picLib->GetImage(myself->picLib,"dishu2.gif"); 
	  
	  myself->imgchuizi=myself->picLib->GetImage(myself->picLib,"chuizi2.gif");

	  myself->imgbeijing=myself->picLib->GetImage(myself->picLib,"beijing2.gif");

	}
	else if(level>=7)
	{
		myself->imgdishu=myself->picLib->GetImage(myself->picLib,"dishu3.gif"); 
	  
	    myself->imgchuizi=myself->picLib->GetImage(myself->picLib,"chuizi3.gif");

	    myself->imgbeijing=myself->picLib->GetImage(myself->picLib,"beijing3.gif");
	}
	myself->keyifanhui=false;
	myself->pojilu=false;
	myself->wanchang=false;
	myself->keyixiayiguan=false;
	myself->keyida=true;
	myself->gamepause=false;
	myself->chixushijian=chixushijianbiao[level-1];
	myself->totalshunum=shunum[level-1];
	myself->mustshunum=myself->totalshunum*percent/100;
	myself->jiangeshijian=what_jiange(myself);
	myself->chuxiandishunum=0;
	myself->dazhongdishunum=0;
	myself->jishi=0;
	myself->firsttime=10;
	if(gamestage == 4)
		myself->life = 10;
	for (i=0;i<9;i++)
	{
		myself->zhuangtai[i]=0;
		myself->chuizi[i]=0;
		myself->jizhongtime[i]=0;
	    myself->chixutime[i]=0;
	}	   
}

void da_dishu(HitMoleplay * myself,gm_s16 index) {
		gm_s16 i;
		if (!myself->gamepause
				&& myself->chuizi[index] == 0
				&& myself->keyida
				&& (gamestage == 2 && myself->chuxiandishunum <= shunum[level - 1] || gamestage == 4)) {
			for (i = 0; i < 9; i++) {
				myself->chuizi[i] = 0;
			}
			myself->chuizi[index] = 1;// û�ҵ�����Ŀմ�

			if (myself->zhuangtai[index] == 2)// ����ɵЦ
			{
				if (myself->soundopen) 
					extVmAudioManager->vMAudioPlayForGame(HITMOLE_SHU1_MID,1);
				myself->chuizi[index] = 2;// ���Ӵ���

				myself->score += 10;
				myself->chixutime[index] = 0;
				myself->zhuangtai[index] = 4;// ���󱻴�Ĳ���
				if (gamestage == 2)
					myself->dazhongdishunum++;
				if (gamestage == 4) {
					for (i = 0; i < 9; i++)
						if (addlife[i] == myself->score)
							myself->life++;
				}
			}
			if (myself->zhuangtai[index] == 6)// ��������ɰ���Ц��
			{
				if (myself->soundopen) 
					extVmAudioManager->vMAudioPlayForGame(HITMOLE_SHU2_MID,1);	//���ֲ���
				myself->chuizi[index] = 2;
				if (gamestage == 2)
					myself->dazhongdishunum--;
				else if (myself->life > 0)
					myself->life--;
				myself->zhuangtai[index] = 8;// ���󱻴�ʱ�Ŀ���
				myself->chixutime[index] = 0;
			}
		}
		if (myself->jizhongtime[index] == 0 || myself->zhuangtai[index] == 0)
			myself->jizhongtime[index] = 1;
	}

	void dishu_random(HitMoleplay * myself,int index) {

		gm_s16 tempdishu = Random(0,4);
		if (tempdishu == 2)
			myself->bigorsmall[index] = false;
		else
			myself->bigorsmall[index] = true;
		if (myself->bigorsmall[index]) {
			myself->zhuangtai[index] = 1;// �����¶��ͷ
			myself->chuxiandishunum++;
		} else {
			myself->zhuangtai[index] = 5;
		}

		myself->chixutime[index] = 1;
	}

void paint_gamebar(HitMoleplay * myself) {
		char buff[10];
		if(gamestage == 2)
		{
			sprintf((char*)buff,"%d/%d",myself->dazhongdishunum,myself->chuxiandishunum);
			manager.DrawString(buff,40,25,5,0xffff00);
		}
		else if(gamestage == 4)
		{
			sprintf((char*)buff,"%d",myself->life);
			manager.DrawString(buff,40,30,5,0xffff00);
		}
		sprintf((char*)buff,"�� ��%d",myself->score);
		manager.DrawString(buff,40,100,5,0xffff00);
		sprintf((char*)buff,"�Ѷ�%d",level);
		manager.DrawString(buff,40,190,5,0xffff00);
		#ifdef GAME_240_320
		if (myself->soundopen) 
			myself->picLib->DrawRegionEx(myself->picLib,myself->imglaba,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-30,
										0,0,30,30,true,0);
		else 
			myself->picLib->DrawRegionEx(myself->picLib,myself->imglaba,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-30,
										30,0,30,30,true,0);
		#endif
		#ifdef GAME_176_220
		if (myself->soundopen)
			myself->picLib->DrawRegionEx(myself->picLib,myself->imglaba,SCREEN_WIDTH/2-8,SCREEN_HEIGHT-16,
										0,0,16,16,true,0);
		else 
			myself->picLib->DrawRegionEx(myself->picLib,myself->imglaba,SCREEN_WIDTH/2-8,SCREEN_HEIGHT-16,
										16,0,16,16,true,0);
		#endif
	}

// ����Ϸ����
void paint_game(HitMoleplay * myself) 
{
	char buff[30];
	gm_s16 i,j;
	gm_s32 gaodu,addmylife;
	myself->picLib->DrawImage(myself->picLib,myself->imgbeijing,0,0);//g.drawImage(beijing, 0, 0, Graphics.TOP | Graphics.LEFT);
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++) 
		{
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgdishu,myself->x_point + i * myself->x_jiange,
										 myself->y_point + j * myself->y_jiange,myself->zhuangtai[j * 3 + i] * myself->dongwidth,0,
										 myself->dongwidth,myself->dongheight,true,0);
		}
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++) 
		{
			if (level < 4) 
			{
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgchuizi,myself->x_point + i * myself->x_jiange + 5, 
											 myself->y_point + j* myself->y_jiange - 25, myself->chuizi[j * 3 + i] * myself->dongwidth, 0,
											 myself->dongwidth, myself->dongheight,true,0);
			} else {
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgchuizi,myself->x_point + i * myself->x_jiange + 8, 
											 myself->y_point + j* myself->y_jiange - 25, myself->chuizi[j * 3 + i] * myself->dongwidth, 0,
											 myself->dongwidth, myself->dongheight,true,0);
			}
		}
	}
	paint_gamebar(myself);
	#ifdef GAME_240_320
	if (myself->gamepause)
		manager.DrawString("����",20,TOUCH_X_LEFT + 5,TOUCH_Y_LEFT,0xffff00);
	else
		manager.DrawString("��ͣ",20,TOUCH_X_LEFT + 5,TOUCH_Y_LEFT,0xffff00);
		manager.DrawString("�˳�",20,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT, 0xffff00);	
	#endif
	#ifdef GAME_176_220
	if (myself->gamepause)
		manager.DrawString("����",20,TOUCH_X_LEFT-2,TOUCH_Y_LEFT,0xffff00);
	else
		manager.DrawString("��ͣ",20,TOUCH_X_LEFT-2,TOUCH_Y_LEFT,0xffff00);
		manager.DrawString("�˳�",20,TOUCH_X_RIGHT+2,TOUCH_Y_RIGHT, 0xffff00);	
	#endif
	if (myself->wanchang) 
	{
		if (myself->secondtime - myself->firsttime < 7) 
		{
			//1111
			gaodu = (myself->secondtime - myself->firsttime) * 10;
			myself->picLib->FillRect(myself->picLib,10, SCREEN_HEIGHT / 2 - gaodu, SCREEN_WIDTH - 20,gaodu * 2,0x99aa00);

		}

		else 
		{
			if (myself->secondtime == myself->firsttime + 7 && myself->soundopen && myself->dazhongdishunum >= myself->mustshunum) 
			{
					extVmAudioManager->vMAudioPlayForGame(HITMOLE_WIN_MID,1);
			}

			myself->keyixiayiguan = true;
			myself->picLib->FillRect(myself->picLib,10,SCREEN_HEIGHT / 2 - 70, SCREEN_WIDTH - 20,140,0x99aa00);
			if (myself->dazhongdishunum == myself->totalshunum) 
			{
				if (myself->secondtime == myself->firsttime + 7) 
				{

					myself->score += level * 100;
				}
				if (myself->score == 9900) 
				{
					manager.DrawString("������",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50, 0xffff00);
					manager.DrawString("9��һ��ʧ��û��",20,SCREEN_WIDTH / 2-85,SCREEN_HEIGHT / 2 - 10, 0xffff00);
					manager.DrawString("���˳�������", 20,SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 + 30, 0xffff00);
				}
				else 
				{
					manager.DrawString("������ȫ��", 20,SCREEN_WIDTH / 2-50,SCREEN_HEIGHT / 2 - 50,0xffff00);
					sprintf((char*)buff,"����%d��",level*100);
					manager.DrawString(buff,40,SCREEN_WIDTH / 2-50,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("��ȷ��������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30, 0xffff00);
				}
			}
			else if (myself->dazhongdishunum >= myself->mustshunum)
			{
				if (myself->secondtime == myself->firsttime + 7) 
				{

					myself->score += level * (percent - 50);
				}
				if (level == 9) 
				{
					manager.DrawString("ף����",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50, 0xffff00);
					manager.DrawString("���Ѿ���ͨ����",20, SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2 - 10, 0xffff00);
					manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30, 0xffff00);

				} 
				else 
				{
					manager.DrawString("��ϲ����",20,SCREEN_WIDTH / 2-40,SCREEN_HEIGHT / 2 - 50, 0xffff00);
					sprintf((char*)buff,"����%d��",level*(percent-50));
					manager.DrawString(buff,40,SCREEN_WIDTH / 2-50,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("��ȷ��������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30, 0xffff00);
				}
			}

			else if (myself->dazhongdishunum < myself->mustshunum) 
			{
				if (percent == 100)
				{
					if (myself->score < 2000) 
					{
						manager.DrawString("��Ҫ��",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("100%�ܻ�����ʧ��",20, SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 - 10,0xffff00);
					} 
					else if (myself->score < 5000)
					{
						manager.DrawString("����Ŷ",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("100%����ǧ������",20, SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 - 10,0xffff00);
					} 
					else 
					{
						manager.DrawString("���ְ�",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("100%���ܹ���ǧ",20, SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2 - 10,0xffff00);
					}
				}

				else {
					if (level == 1)
					{
						manager.DrawString("�ϴ����в��а�",20,SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("һ�ض�����ȥ",20, SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 - 10,0xffff00);
					} 
					else if (myself->score < 500) 
					{
						manager.DrawString("̫���",20,SCREEN_WIDTH / 2-40,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("�������������",20, SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 - 10,0xffff00);
					} 
					else if (myself->score < 1000) 
					{
						manager.DrawString("������Ŷ",20,SCREEN_WIDTH / 2-40,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("һǧ�ֶ�����",20, SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 - 10,0xffff00);

					} 
					else if (myself->score < 2000) 
					{
						manager.DrawString("�պϰ�",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("����ϰ��ϰ�����",20, SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 - 10,0xffff00);

					}
					else if (myself->score < 3000) 
					{
						manager.DrawString("����Ŷ",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("�������ͣ�Ŭ��",20, SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2 - 10,0xffff00);

					} 
					else if (myself->score < 4000) 
					{
						manager.DrawString("ǿ��",20,SCREEN_WIDTH / 2-20,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("��һ����Ǳ��",20, SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 - 10,0xffff00);
					}
					else if (myself->score < 5000)
					{
						manager.DrawString("�ð�Ŷ",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("���ǲ�Ҫ����Ŷ",20, SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2 - 10,0xffff00);
					}
					else 
					{
						manager.DrawString("��Ű�",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50,0xffff00);
						manager.DrawString("���Ǵ����ר��",20, SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2 - 10,0xffff00);
					}
				}
				manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30, 0xffff00);
				if (myself->score > hitMoleHighScoreValue[(percent - 60) / 10]) 
				{
					myself->pojilu = true;
					Update_Record((percent - 60) / 10,myself->score);
					Read_Record();
				}
				if (myself->pojilu) 
				{
					myself->picLib->FillRect(myself->picLib,10, SCREEN_HEIGHT / 2 - 70, SCREEN_WIDTH - 20,140,0x99aa00);
					manager.DrawString("��ϲ��",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50,0xffff00);
					manager.DrawString("�����Ƽ�¼��",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);

				}

			}
		}

	}
	
	if (myself->life == 0 && gamestage == 4) {
		if (myself->secondtime - myself->firsttime < 17) 
		{
			
			gaodu = (myself->secondtime - myself->firsttime - 10) * 10;
//			myself->picLib->FillRect(myself->picLib,10, SCREEN_HEIGHT / 2 - gaodu, SCREEN_WIDTH - 20,gaodu * 2,0x99aa00);
		}
		else 
		{
			myself->keyifanhui = true;
			myself->picLib->FillRect(myself->picLib,10, SCREEN_HEIGHT / 2 - 70, SCREEN_WIDTH - 20, 140,0x99aa00);
			if (level < 5) {
				if (myself->score < 500) 
				{
					manager.DrawString("�����",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50,0xffff00);
					manager.DrawString("�Ŵ���ô���",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);

				} 
				else if (myself->score < 2000)
				{
					manager.DrawString("�ü򵥰�",20,SCREEN_WIDTH / 2-40,SCREEN_HEIGHT / 2 - 50,0xffff00);
					manager.DrawString("������ս��",20,SCREEN_WIDTH / 2-50,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);

				} 
				else 
				{
					manager.DrawString("��ս�¸ߵ��Ѷ�",20,SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2 - 50,0xffff00);
					manager.DrawString("�����¼���ᱣ��",20,SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);
				}
			}
			else if (level == 9) 
			{
				if (myself->score < 100) 
				{
					manager.DrawString("��Ϸ���������ֵ�",20,SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 - 50,0xffff00);
					manager.DrawString("����������Ű��",20,SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);
				} 
				else if (myself->score < 500) 
				{
					manager.DrawString("���оͲ�Ҫ��ǿ",20,SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2 - 50,0xffff00);
					manager.DrawString("����ѶȲ��ʺ���",20,SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);
				}
				else if (myself->score < 1000)
				{
					manager.DrawString("������Ŷ",20,SCREEN_WIDTH / 2-40,SCREEN_HEIGHT / 2 - 50,0xffff00);
					manager.DrawString("����Ŭ�������",20,SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);
				} 
				else if (myself->score < 2000)
				{
					manager.DrawString("���˾�ЪЪ",20,SCREEN_WIDTH / 2-50,SCREEN_HEIGHT / 2 - 50,0xffff00);
					manager.DrawString("��Ҫ�Ѱ���Ū��Ŷ",20,SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);

				} 
				else 
				{
					manager.DrawString("�������",20,SCREEN_WIDTH / 2-40,SCREEN_HEIGHT / 2 - 50,0xffff00);
					manager.DrawString("��ϧû�и����Ѷ�",20,SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 - 10,0xffff00);
					manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);

				}

			} 
			else if (level < 9 && level > 4) 
			{
				manager.DrawString("���ĳɼ�Ϊ",20,SCREEN_WIDTH / 2-50,SCREEN_HEIGHT / 2 - 50,0xffff00);
				sprintf((char*)buff,"%d��",myself->score);
				manager.DrawString(buff,40,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 10,0xffff00);
				manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);

			}
			if(level>1)
			{
				if (myself->score > hitMoleHighScoreValue[level]) 
					{
						myself->pojilu = true;
						Update_Record(level,myself->score);
						Read_Record();
					}
			}
			if (myself->pojilu)
			{
				myself->picLib->FillRect(myself->picLib,10, SCREEN_HEIGHT / 2 - 70,SCREEN_WIDTH - 20, 140,0x99aa00);
				manager.DrawString("��ϲ��",20,SCREEN_WIDTH / 2-30,SCREEN_HEIGHT / 2 - 50,0xffff00);
				manager.DrawString("�����Ƽ�¼��",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 - 10,0xffff00);
				manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2 + 30,0xffff00);
			}

		}
	}
	
	if (myself->gamepause)
	{
		myself->picLib->FillRect(myself->picLib,10, 30, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 65,0x99aa00);
		manager.DrawString("��ͣ",20,SCREEN_WIDTH / 2-20, SCREEN_HEIGHT / 2 - 60,0xffff00);
		manager.DrawString("1-9�������",20,SCREEN_WIDTH / 2-55, SCREEN_HEIGHT / 2 - 40,0xffff00);
		manager.DrawString("0����/������",20,SCREEN_WIDTH / 2-60, SCREEN_HEIGHT / 2 - 20,0xffff00);
		if (gamestage == 2)
		{
			sprintf((char*)buff,"����һ��%d������",shunum[level - 1] );
			manager.DrawString(buff,20,SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2,0xffff00);
			sprintf((char*)buff,"��%d���ſɹ���",shunum[level - 1]*percent/100);
			manager.DrawString(buff,20,SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2+20,0xffff00);
			manager.DrawString("��Ҫ�����Ŷ",20,SCREEN_WIDTH / 2-60,SCREEN_HEIGHT / 2+40,0xffff00);
		} 
		else if (gamestage == 4) 
		{
			addmylife = 0;
			if (myself->score < 100)
				addmylife = 100;
			else if (myself->score < 300)
				addmylife = 300;
			else if (myself->score < 600)
				addmylife = 600;
			else if (myself->score < 1000)
				addmylife = 1000;
			else if (myself->score < 1500)
				addmylife = 1500;
			else if (myself->score < 2100)
				addmylife = 2100;
			else if (myself->score < 2800)
				addmylife = 2800;
			else if (myself->score < 3600)
				addmylife = 3600;
			else if (myself->score < 4500)
				addmylife = 4500;
			else if (myself->score < 5500)
				addmylife = 5500;
			if (myself->score >= 5500 && myself->life > 0)
				manager.DrawString("�����ټ�������",20,SCREEN_WIDTH / 2-70,SCREEN_HEIGHT / 2,0xffff00);
			else if (myself->life > 0)
			{
				sprintf((char *)buff,"��%d�ֽ���1����",addmylife);
				manager.DrawString(buff,20,SCREEN_WIDTH / 2-80,SCREEN_HEIGHT / 2 + 40,0xffff00);
			}
			else
				manager.DrawString("���˳�������",20,SCREEN_WIDTH / 2 - 50,SCREEN_HEIGHT / 2 + 40,0xffff00);
				manager.DrawString("©1�����1����",20,SCREEN_WIDTH / 2 - 70,SCREEN_HEIGHT / 2,0xffff00);
				manager.DrawString("���1�����1����",20,SCREEN_WIDTH / 2 - 80,SCREEN_HEIGHT / 2 + 20,0xffff00);
		}
	}
}

void keyPressed1(HitMoleplay * myself)
{
	//������
	#ifdef GAME_240_320
		gm_s16 px,py,j,i,m;
		m=0;
		if(SCREEN_IsPointerDown())
		{
			px = SCREEN_GetPointerX();
			py = SCREEN_GetPointerY();
			for(j=0;j<3;j++)
			{
				for(i=0;i<3;i++)
				{
					if(MyCdRectPoint(i*80,64+j*80,(i+1)*80,124+j*80,px,py))
					da_dishu(myself,m);
					m++;
				}
			}
			
		}
	#endif
	if(getManagerPtr()->IsKeyDown(MF_KEY_0))
	{
		if(myself->soundopen)
			myself->soundopen=false;
		else 
			myself->soundopen=true;
	}
	if(getManagerPtr()->IsKeyDown(MF_KEY_SHARP | MF_KEY_LEFTSOFT))
	{
		if(myself->gamepause)
			myself->gamepause=false;
		else 
			myself->gamepause=true;
	}
	if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))
	{
		HitMole_Screen_Next = &HitMole_Screen_Title;
		hitMoleTitleState = HITMOLE_TITLE_STATE_MENU;
		hitMoleLoadingStep = 0;
		hitMoleLoadingStepTotal = 16;
		SCREEN_ChangeScreen(&HitMole_Screen_Loading);
	}
	if(getManagerPtr()->IsKeyDown(MF_KEY_1))
		da_dishu(myself,0);
	if(getManagerPtr()->IsKeyDown(MF_KEY_2))
		da_dishu(myself,1);
	if(getManagerPtr()->IsKeyDown(MF_KEY_3))
		da_dishu(myself,2);
	if(getManagerPtr()->IsKeyDown(MF_KEY_4))
		da_dishu(myself,3);
	if(getManagerPtr()->IsKeyDown(MF_KEY_5))
		da_dishu(myself,4);
	if(getManagerPtr()->IsKeyDown(MF_KEY_6))
		da_dishu(myself,5);
	if(getManagerPtr()->IsKeyDown(MF_KEY_7))
		da_dishu(myself,6);
	if(getManagerPtr()->IsKeyDown(MF_KEY_8))
		da_dishu(myself,7);
	if(getManagerPtr()->IsKeyDown(MF_KEY_9))
		da_dishu(myself,8);
	if(getManagerPtr()->IsKeyDown(MF_KEY_MID))
	{
		if(gamestage==2&&myself->keyixiayiguan&&myself->chuxiandishunum==myself->totalshunum)
		{
		if(myself->dazhongdishunum >= myself->mustshunum&&level<9)
		{
			level++;
			init(myself);
		}
		else
		{
			HitMole_Screen_Next = &HitMole_Screen_Title;
			hitMoleTitleState = HITMOLE_TITLE_STATE_MENU;
			hitMoleLoadingStep = 0;
			hitMoleLoadingStepTotal = 16;
			SCREEN_ChangeScreen(&HitMole_Screen_Loading);
		}
		}
		if(gamestage==4&&myself->keyifanhui)
		{ 
			HitMole_Screen_Next = &HitMole_Screen_Title;
			hitMoleTitleState = HITMOLE_TITLE_STATE_MENU;
			hitMoleLoadingStep = 0;
			hitMoleLoadingStepTotal = 16;
			SCREEN_ChangeScreen(&HitMole_Screen_Loading);
		}
	}
	
}

void play_game(HitMoleplay * myself)
{	
	gm_s16 i;
	gm_bool keyi;
	if(myself->secondtime - myself->firsttime == myself->jiangeshijian && !myself->wanchang)
	{
		if(myself->chuxiandishunum<myself->totalshunum)
		{
			myself->firsttime=myself->jishi;
			myself->jiangeshijian=what_jiange(myself);
			keyi=true;
			while(keyi)
			{
				keyi=false;
				myself->dong=Random(0,8);
				if(myself->zhuangtai[myself->dong]>0)
				keyi=true;
			}
			dishu_random(myself,myself->dong);
		}
		else 
		{
			myself->wanchang=true;
			myself->firsttime=myself->jishi;
			myself->keyida=false;
		}
	}

	for(i=0;i<9;i++)
	{
		if(myself->chixutime[i]>0)
		{
			myself->chixutime[i]++;
			if(myself->chixutime[i]==3&&(myself->zhuangtai[i]==1||myself->zhuangtai[i]==5))
				myself->zhuangtai[i]++;
			if(myself->chixutime[i]==3+myself->chixushijian&&(myself->zhuangtai[i]==2||myself->zhuangtai[i]==6))
				myself->zhuangtai[i]++;
			if(myself->chixutime[i]==4+myself->chixushijian&&(myself->zhuangtai[i]==3||myself->zhuangtai[i]==7))
			{
				myself->zhuangtai[i]=0;
				myself->chixutime[i]=0;
			}
		}
		if(myself->jizhongtime[i]>0)
		{
			myself->jizhongtime[i]++;
			if(myself->jizhongtime[i]==6-(level-1)/3)//�����ҵ�Ŀ���,����Ҫ��һС��ʱ�����ʧ
				myself->chuizi[i]=0;
			if(myself->jizhongtime[i]==10-2*(level-1)/3)//�����Һ�,Ҫ��һС��ʱ�����ʧ
			{
				myself->jizhongtime[i]=0;
				if(myself->zhuangtai[i]==4||myself->zhuangtai[i]==8)
				myself->zhuangtai[i]=0;
			}
		}
		if(myself->zhuangtai[i]==0&&myself->chuizi[i]==2)
		myself->chuizi[i]=0;
		if(myself->zhuangtai[i]!=0&&myself->chuizi[i]==1)
		myself->chuizi[i]=0;
	}
}
	
	
void play_define(HitMoleplay * myself)
{
	gm_s16 i;
	gm_bool keyi;
	if(myself->secondtime - myself->firsttime==myself->jiangeshijian)
	{

		if(myself->life>0)
		{
			myself->firsttime=myself->jishi;
			myself->jiangeshijian=what_jiange(myself);
			keyi=true;
			while(keyi)
			{
				keyi=false;
				myself->dong=Random(0,8);
				if(myself->zhuangtai[myself->dong]>0)
				keyi=true;
			}
			dishu_random(myself,myself->dong);
		}
		else if(myself->life==0&&myself->keyida)
		{
			myself->firsttime=myself->jishi;
			myself->keyida=false;
		}
	}

	for(i=0;i<9;i++)
	{
		if(myself->chixutime[i]>0)
		{
			myself->chixutime[i]++;
			if(myself->chixutime[i]==3&&(myself->zhuangtai[i]==1||myself->zhuangtai[i]==5))
				myself->zhuangtai[i]++;
			if(myself->chixutime[i]==3+myself->chixushijian&&(myself->zhuangtai[i]==2||myself->zhuangtai[i]==6))
				myself->zhuangtai[i]++;
			if(myself->chixutime[i]==4+myself->chixushijian&&(myself->zhuangtai[i]==3||myself->zhuangtai[i]==7))
			{
				if(myself->zhuangtai[i]==3&&myself->life>0)
				myself->life--;//û��������,������1
				myself->zhuangtai[i]=0;
				myself->chixutime[i]=0;
			}
		}
		if(myself->jizhongtime[i]>0)
		{
			myself->jizhongtime[i]++;
			if(myself->jizhongtime[i]==6-(level-1)/3)//�����ҵ�Ŀ���,����Ҫ��һС��ʱ�����ʧ
				myself->chuizi[i]=0;
			if(myself->jizhongtime[i]==10-2*(level-1)/3)//�����Һ�,Ҫ��һС��ʱ�����ʧ
			{
				myself->jizhongtime[i]=0;
				if(myself->zhuangtai[i]==4||myself->zhuangtai[i]==8)
				myself->zhuangtai[i]=0;
			}
		}
		if(myself->zhuangtai[i]==0&&myself->chuizi[i]==2)
			myself->chuizi[i]=0;
		if(myself->zhuangtai[i]!=0&&myself->chuizi[i]==1)
			myself->chuizi[i]=0;
	}
}

void HitMole_Play_Windows_Render(void *param)
{
	HitMoleplay * myself = (HitMoleplay *)param;
	init(myself);
	paint_game(myself);
}
void HitMole_Play_Windows_Update(void * param)
{
	HitMoleplay * myself = (HitMoleplay *)param;
	if(myself->shuxintime/80 == 0 )
	{
		if (!myself->gamepause) {
			myself->jishi++;
			myself->secondtime = myself->jishi;
			if (gamestage == 2)
				play_game(myself);
			if (gamestage == 4)
				play_define(myself);
		}
		paint_game(myself);
		keyPressed1(myself);
	}
	else
		myself->shuxintime++;
}

