#include "CatLoveDog_InGame.h"
#include "CatLoveDog_Screen.h"
#include "coolbar_GameUtil.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
static Manager manager;
//酷吧音乐播放extVmAudioManager->vMAudioPlayForGame(HITMOLE_SHU2_MID,1);
//myself->fish_tTemp;未赋值
/*********************************ShowGame中protected void paint(Graphics g)方法********************************/
void initCatLoveDog_InGame(CatLoveDog_InGame * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repaintMax)
{
	extVmSysManager->VmSetFPS(50);
	initManager(&manager);
	initDFWindows(&myself->windows,windows_Rect,myself,myself,repaintMax);
	myself->windows.RenderCallBack=CatLoveDog_InGame_Windows_Render;
    myself->windows.UpdateCallBack=CatLoveDog_InGame_Windows_Update;
	myself->picLib=picLib;
	
	myself->windImg = myself->picLib->GetImage(picLib,"win.gif");
	CatLoveDog_Loading_UpdateStep();
	
	if(level == 1)
		myself->beijing = myself->picLib->GetImage(picLib,"beijing_0.gif");
	if(level == 2)
		myself->beijing = myself->picLib->GetImage(picLib,"beijing_1.gif");
	if(level == 3)
		myself->beijing = myself->picLib->GetImage(picLib,"beijing_2.gif");
	myself->catImg = myself->picLib->GetImage(picLib,"cat.gif");
	
	myself->dogImg = myself->picLib->GetImage(picLib,"dog.gif");
	
	CatLoveDog_Loading_UpdateStep();

	myself->fishImg = myself->picLib->GetImage(picLib,"yuci.gif");
	myself->boneImg = myself->picLib->GetImage(picLib,"gutou.gif");
	CatLoveDog_Loading_UpdateStep();

	myself->loseImg = myself->picLib->GetImage(picLib,"lose.gif");
	myself->bombImg = myself->picLib->GetImage(picLib,"baozha.gif");
	CatLoveDog_Loading_UpdateStep();
	
	myself->windImg = myself->picLib->GetImage(picLib,"wind.gif");
	myself->buttonImg = myself->picLib->GetImage(picLib,"button.gif");
	CatLoveDog_Loading_UpdateStep();

	myself->lifeImageD = myself->picLib->GetImage(picLib,"LifeD.gif");
	myself->lifeImageC = myself->picLib->GetImage(picLib,"LifeC.gif");
	CatLoveDog_Loading_UpdateStep();

	myself->liliangImg = myself->picLib->GetImage(picLib,"liliang.gif");
	
	myself->gameWin = false;
	myself->gameOver = false;
	myself->catBlood = 60;
	myself->cattu = 0;
	myself->dogBlood = 60;
	myself->dogtu = 0;
 	myself->SleepTimer = 50;
	myself->changelifeD = 0;
	myself->changelifeC = 0;
	myself->setColor = 30;
	CatLoveDog_Loading_UpdateStep();
	myself->bombRun = false;
	myself->bombFrame = 0;
	myself->bombShow = false;
	myself->angle =48;
	myself->catPX = 5;
	myself->alive = true;
	myself->isPause = false;
	CatLoveDog_Loading_UpdateStep();

	myself->windn = 0;
	myself->Wind_left = 10;
  	myself->Wind_right = 10;
  	myself->Wind_change = 0;
  	myself->Wind_v = 0;
	CatLoveDog_Loading_UpdateStep();

	myself->fishPX = 50;
	myself->fishPY = 500;
	myself->fishFrame = 0;
	myself->fish_v0 = 0;
	myself->fish_i = 0;
	myself->fishGo = false;
	myself->fish_t1 = 0;
	myself->fish_add1 = 3;
	myself->fishShow = false;
	myself->isFire = 0;
	CatLoveDog_Loading_UpdateStep();
	
	myself->bonePX = 500;
	myself->bonePY = 500;
	myself->boneFrame = 0;
	myself->bone_v02 = 0;
	myself->bone_add2 = 3;
	myself->boneGo = false;
	myself->bone_r = 0;
	myself->boneShow = false;
	myself->bone_i=0;
	myself->bombPX = 0;
	myself->bombPY = 0;
	myself->teshu = false;
	//myself->fish_tTemp = 0;
	//myself->bone_tTemp2 = 0;
	CatLoveDog_Loading_UpdateStep();
}

/**/
gm_s32 getSinAngleValue(gm_s32 angle)
{
  	gm_s32 tempAngle,tempValue;
	gm_s32 res[31] = {0,5236,10453,15643,20791,25882,30902,35837,40674,45400,50000,54464,58779,62932,66913,70711,74314,77715,80902,83867,86603,
		89101,91355,93358,95106,96593,97815,98769,99452,99863,100000};
	tempAngle = (angle > 90 ? (180 - angle) : angle);
	//tempValue = ((Integer)(angleValue.get(String.valueOf(tempAngle)))).intValue();
	tempValue = res[tempAngle/3-1];
	//return 74314;
	return tempValue;
}
/**/

gm_s32 getCosAngleValue(gm_s32 angle)
 {
  	gm_s32 tempAngle,tempValue;
	gm_s32 res[31] = {0,5236,10453,15643,20791,25882,30902,35837,40674,45400,50000,54464,58779,62932,66913,70711,74314,77715,80902,83867,86603,
		89101,91355,93358,95106,96593,97815,98769,99452,99863,100000};
	tempAngle = (angle > 90 ? angle - 90 : 90 - angle);
	tempValue = res[tempAngle/3-1];
	//return 66913;
	//return 77715;
	return (angle <= 90 ? tempValue : (-tempValue));
 }

gm_s8 nextFrame(gm_s8 frame)
{
	gm_s8 temframe;
	if(frame == 3)
	{
		temframe =0;
	}
	else
	{
		temframe = frame+1;
	}
	return temframe;
}


void drawWind(CatLoveDog_InGame *myself)
{
	gm_s16 a,b;
	myself->windn = myself->windn+1;
    if (myself->windn % 100 == 1) {
      //myself->Wind_change =Math.abs( ran.nextInt()%50);
      myself->Wind_change = Random(0,49);
      if (myself->windn == 101) {
        myself->windn = 1;
      }
    } // 变化速度

	a = SCREEN_WIDTH/2;//(Contrl.game.screenw) / 2;
	b = 10;

    //g.setColor(241, 108, 5);
    if (myself->Wind_change % 2 == 0) { //左面
      //g.fillRect(a -50+ myself->Wind_change, b + 5, 50 - myself->Wind_change, 5);
      myself->picLib->FillRect(myself->picLib,a -50+ myself->Wind_change, b + 5, 50 - myself->Wind_change, 5,GAME_ToRGB(255,0,0));
      myself->Wind_v = myself->Wind_change;
    }
    
    if (myself->Wind_change % 2 == 1) { //右
      //g.fillRect( a, b + 5, myself->Wind_change, 5);
	  myself->picLib->FillRect(myself->picLib,a, b + 5, myself->Wind_change, 5,GAME_ToRGB(255,0,0));
      myself->Wind_v = -myself->Wind_change;
    }
}

/*****************************************************Fish中的方法***********************************************************/


void fishRun(CatLoveDog_InGame *myself) { //fish运动
	gm_s32 pianyi;
	if (myself->fishGo) {
      myself->fish_tTemp++;

      if (myself->fish_tTemp > 3) {
        myself->fish_t1 += 1;
        myself->fish_tTemp = 0;
        myself->fish_vx1 = getCosAngleValue(myself->angle) * myself->fish_v0 / 210000 -
            myself->Wind_v / 8;
        myself->fish_vy1 = getSinAngleValue(myself->angle) * myself->fish_v0 / 100000;
      }

      pianyi = (myself->fish_t1 * 400000);
      if (myself->fish_vy1 == 0) {
        pianyi = 0;
      }
      myself->fishPX += myself->fish_vx1 * myself->fish_t1 * 20000 / 100000+1;
      myself->fishPY = (100000 * myself->fishPY - (myself->fish_vy1 * myself->fish_t1 - 100000 * myself->fish_t1 * myself->fish_t1 + pianyi)) / 100000;
    }
  }

void fishMove(CatLoveDog_InGame *myself) {

   if (!myself->isPause) {
	 myself->fish_i++;
   }
   if (myself->fish_i % 3 == 0) {
	 myself->fish_i = 0;
	 myself->fishFrame = nextFrame(myself->fishFrame);
   }

 }

//fish 超出屏幕范围后重置各个参数
void fishOut(CatLoveDog_InGame *myself) {
    if (myself->fishPY >= SCREEN_HEIGHT|| myself->fishPX >= SCREEN_WIDTH) {
      myself->fish_t1 = 0;

      myself->fishGo = false;
      myself->fish_v0 = 0; //恢复能量和力量的初始状态.
      myself->fish_add1 = 3;
      myself->fishShow = false;
      myself->fishPX = 15 + myself->catPX;
      myself->fishPY = 235;
      //Contrl.game.cat.setFrame(0);
      //Contrl.game.isFire=0;
      myself->isFire = 0;
      //setVisible(true);
      //System.gc(); //回收没用的资源.
    }
  }

void DrawPower(CatLoveDog_InGame *myself) { //画鱼的起始能量
    //g.drawImage(Contrl.menu.liliang,(Contrl.game.screenw - Contrl.game.beijing[0].getWidth()) / 2+2 ,
              //(Contrl.game.screenh - Contrl.game.beijing[0].getHeight()) / 2 + 77,0);
    myself->picLib->DrawImageEx(myself->picLib,myself->liliangImg,2,77,true,0);
    //g.setColor(0xff0000);
    //g.fillRect( (Contrl.game.screenw - Contrl.game.beijing[0].getWidth()) / 2 +5,
    //          (Contrl.game.screenh - Contrl.game.beijing[0].getHeight()) / 2 + 105+50+40-v0+10,
    //          5,v0-10);
    myself->picLib->FillRect(myself->picLib,5,205-myself->fish_v0,5,myself->fish_v0-10,GAME_ToRGB(255,0,0));
  }

//碰撞检测
void fishHit(CatLoveDog_InGame *myself) {
	gm_bool pengzhuang;
	pengzhuang = CdRect2(myself->fishPX,myself->fishPY,25,25,190,225,35,40);
    if (pengzhuang && myself->fishShow) {
          //good.start();
          extVmAudioManager->vMAudioPlayForGame(CATLOVEDOG_GOOD_MID,1);
          myself->changelifeD = myself->changelifeD+3;
          //Contrl.game.cat.setFrame(2);
		  myself->cattu = 2;
          //Contrl.game.dog.setFrame(3);
          myself->dogtu = 3;
		  myself->fishShow = false;
		  //myself->fishPX = 50;
		  //myself->fishPY = 500;
    }
    return;

  }

void fishDrawSelf(CatLoveDog_InGame *myself) 
{
    if (!myself->isPause) 
	{
      DrawPower(myself);
      fishMove(myself);
      fishRun(myself);
      fishHit(myself);
      fishOut(myself);
    }
 }
/******************************************************Bone Class***********************************************************/
/**/
void boneRun(CatLoveDog_InGame *myself)
{
	gm_s32 pianyi;
	if (myself->boneGo) 
	{
        myself->bone_tTemp2++;  //控制时间变化频率
        if (myself->bone_tTemp2 >3) 
		{
          myself->bone_t2+= 1;
          myself->bone_tTemp2 = 0;
          myself->bone_vx2 = getCosAngleValue(myself->angle) * myself->bone_v02 / 210000+ myself->Wind_v /8;
          myself->bone_vy2 = getSinAngleValue(myself->angle) * myself->bone_v02 / 100000 ;

       }

       pianyi = (myself->bone_t2 * 400000);//Y方向的高度偏移
        if (myself->bone_vy2 == 0)
		{
            pianyi = 0;
        }
        myself->bonePX = myself->bonePX-myself->bone_vx2*myself->bone_t2*20000/100000;
      	myself->bonePY= (100000 *myself->bonePY - (myself->bone_vy2 * myself->bone_t2 - 100000 * myself->bone_t2 * myself->bone_t2 +pianyi-100000)) / 100000;
    }

}

/**/
void addPower(CatLoveDog_InGame *myself) { //加骨头的速度。
    myself->bone_v02 += myself->bone_add2;
   if (myself->bone_v02 >= 60 || myself->bone_v02 <= 0) myself->bone_add2 = -myself->bone_add2;
}

/**/
void boneMove(CatLoveDog_InGame *myself) {
	/*
  	gm_s16 i =0;
    if (!myself->isPause)
      i++;
    if (i % 1 == 0) {
      i = 0;
      myself->boneFrame = nextFrame(myself->boneFrame);
    }*/
	if (!myself->isPause) {
	 myself->bone_i++;
   }
   if (myself->bone_i % 3 == 0) {
	 myself->bone_i = 0;
	 myself->boneFrame = nextFrame(myself->boneFrame);
   }
 }

//骨头与猫碰撞
void boneHit2(CatLoveDog_InGame *myself) {
     if (CdRect2(myself->bonePX,myself->bonePY,25,25,myself->catPX,225,55,55)) {
       extVmAudioManager->vMAudioPlayForGame(CATLOVEDOG_BAD_MID,1);                          
       myself->changelifeC +=3;
	   myself->cattu = 3;
	   myself->dogtu =2;
	   //myself->bonePY = 500;
	   //myself->bonePX = 500;
	   myself->boneShow = false;
     }
   }


void boneOut(CatLoveDog_InGame *myself)//骨头超出屏幕重置
{
   if ( myself->bonePY > SCREEN_HEIGHT || myself->bonePX > SCREEN_WIDTH)
   {
    	myself->boneShow = false;
  		myself->bone_v02=0;//恢复能量和力量的初始状态.
 		myself->bone_v02++;
 		myself->boneGo = false;
 		myself->bone_t2 = 0;
 		myself->bonePX = 165;//重新放置骨头的位置
 		myself->bonePY = 221;
 		//this.setVisible(true);
 		//Contrl.game.dog.setFrame(0);
 		myself->dogtu = 0;
		//System.gc();
  }
}

// 骨头随难度等级变化的人工智能部分
/**/
void boneAI(CatLoveDog_InGame *myself) 
{
	gm_s8 x;
	switch(level)
	{
		case 1:
			x = 80;
			break;
		case 2:
			x = 60;
			break;
		case 3:
			x = 43;
			break;

	}
	if (myself->bone_r < 100)
		myself->bone_r++;
	if (myself->bone_r == 100) {
		myself->bone_r = 0;
		myself->bone_r++;
	}
	if (myself->bone_r%x == 0)// 控制投掷频率
	{
		myself->boneGo = true;
		//Contrl.game.lm.append(Contrl.game.bone);
		myself->boneShow = true;
		//etPosition(x2, y2);
		//myself->bonePX = myself->bonePX;
		//myself->bonePY = myself->bonePY;
		//Contrl.game.dog.setFrame(1);
		myself->dogtu =1;
	}
	myself->bone_vx2 =myself->bone_vx2+20;
	// 下面的程序是用来调整一些风力过大 或者随机速度不合适的时候，骨头投掷的状态
	if (myself->Wind_v == -myself->Wind_change
			&& myself->Wind_change > 7) {
		myself->bone_v02 = 50;
	}
	if (level == 3) {
		myself->bone_vx2 = getCosAngleValue(myself->angle) * 34 / 210000;
		myself->bone_vy2 = getSinAngleValue(myself->angle) * myself->bone_v02 / 100000;
		myself->bonePX = myself->bonePX-myself->bone_vx2 * myself->bone_t2 * 30000 / 100000;
		myself->bonePY = (100000 * myself->bonePY - (myself->bone_vy2 * myself->bone_t2 - 100000 * myself->bone_t2 * myself->bone_t2 + 70000)) / 100000;

	}
}

void dogDrawSelf(CatLoveDog_InGame *myself)
{
	if(!myself->isPause)
	{
		addPower(myself);
		boneRun(myself);
		boneMove(myself);
		boneHit2(myself);
		boneOut(myself);
		if(!myself->bombShow)
			boneAI(myself);
	  }

}

void Press_fire(CatLoveDog_InGame *myself) {
    /*用numfire控制猫的投掷状态
      等于0，鱼刺环宇初始状态；等于1，力量条开始上下移动；等于2，鱼猫做投掷动作，鱼刺飞出*/
        switch (myself->isFire) {
            case 0:
                myself->fish_v0 = 0;
                myself->fishShow = false;
                break;
            case 1: //力量条变化.
                myself->fish_v0 += myself->fish_add1;
                if (myself->fish_v0 >= 105 || myself->fish_v0 <= 0) 
				{
                    myself->fish_add1 = -myself->fish_add1;
                }
                myself->cattu = 0;
                break;
            case 2:
                myself->cattu = 1;
                myself->fishGo = true;
               	myself->fishShow = true;
                break;
            default:
                break;
        }
    }

/*
private void bombMove() { //爆炸效果
        if (bombRun == true) {
            if (bomb.getFrame() == 3) {
                bombRun = false;
                lm.remove(bomb);
            } else {
                bomb.nextFrame();
            }
        }
        return;
    }
*/

void bombMove(CatLoveDog_InGame *myself) { 																//爆炸效果
     if (myself->bombRun == true) {
	 	//myself->picLib->DrawRegionEx(myself->picLib,myself->bombImg,myself->bombPX,myself->bombPY,25*myself->bombFrame,0,25,25,true,0);
		myself->bombShow = true;
	   if (myself->bombFrame == 3) {
                myself->bombRun = false;
                myself->bombShow = false;
       } else{
                myself->bombFrame = nextFrame(myself->bombFrame);
     	}
     }
     return;
}

void bomb(CatLoveDog_InGame *myself) 
{ // 碰撞爆炸
	int a,b;
	a = myself->bonePX;
    b = myself->bonePY;
    if (CdRect2(myself->bonePX,myself->bonePY,25,25,myself->fishPX,myself->fishPY,25,25) && a > myself->catPX + 15 &&
                a < 180 - 15 && myself->fishGo && myself->boneGo) 
    {
    	myself->teshu = true;
    	myself->bombShow = true;
        myself->bombRun = true;
            //lm.append(bomb);
        myself->bombFrame =0;
            //Contrl.game.bomb.setPosition(a, b);
        myself->bombPX= a;
		myself->bombPY = b;
            //fish.setVisible(false);
        myself->fishShow = false;
            //bone.setVisible(false);
        myself->boneShow = false;
		//myself->bombPX = myself->bonePX ;
		//myself->bombPY = myself->bonePY ;
		myself->fishPX = 50;
		myself->fishPY = 500;
			//myself->fishGo =false;
			//myself->boneGo = false;
     }
}

//胜利
void DrawWin(CatLoveDog_InGame *myself) 
{
        if (myself->dogBlood == myself->changelifeD) 
		{
            extVmAudioManager->vMAudioPlayForGame(CATLOVEDOG_WIN_MID,1);
			myself->alive = false;
            myself->changelifeC = 0;
            myself->changelifeD = 0;
			myself->gameWin = true;
			extVmSysManager->VmSetFPS(100);
			myself->picLib->DrawFullScreen(myself->picLib,myself->winImg);
			//myself->picLib->DrawRegionEx(myself->picLib,myself->buttonImg,0,SCREEN_HEIGHT-18,0,36,48,18,true,0);
			myself->isPause = true;
        }
    }



//失败
void DrawOver(CatLoveDog_InGame *myself) {
        if (myself->catBlood == myself->changelifeC) {
            myself->alive = false;
           	myself->changelifeC = 0;
            myself->changelifeD = 0;
			myself->gameOver = true;
			extVmSysManager->VmSetFPS(100);
			myself->picLib->DrawFullScreen(myself->picLib,myself->loseImg);
			//myself->picLib->DrawRegionEx(myself->picLib,myself->buttonImg,0,SCREEN_HEIGHT-18,0,36,48,18,true,0);
			myself->isPause = true;
        }
}

void bombShowPaint(gm_s16 a,gm_s16 b,CatLoveDog_InGame *myself)
{
	myself->picLib->DrawRegionEx(myself->picLib,myself->bombImg,a,b,25*myself->bombFrame,0,25,25,true,0);
}

void paint(CatLoveDog_InGame *myself) {
			gm_s16 num,i,a,b;
			
			//g.setColor(0, 0, setColor);
			//g.fillRect(0, 0, screenw, screenh);
			myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(0,0,myself->setColor));
			myself->picLib->DrawImage(myself->picLib,myself->beijing,0,0);

			/////画风向条背景
			myself->picLib->DrawImageEx(myself->picLib,myself->windImg,(SCREEN_WIDTH - myself->picLib->GetImageWidth(myself->picLib,myself->windImg))/2,
				(SCREEN_HEIGHT- myself->picLib->GetImageHeight(myself->picLib,myself->windImg))/2 -143,true,0);
			//lifeD.LifeD(g, changelifeD); ///////////////画玩家的生命值
			num=(myself->dogBlood-myself->changelifeD)*5/myself->dogBlood;
    		for(i=0;i<num;i++)
    		{
    			#ifdef GAME_240_320
        		//g.drawImage(Contrl.menu.LifeImageD,(Contrl.game.screenw-Contrl.game.beijing[0].getWidth())/2+165+this.Blood-12*i,(Contrl.game.screenh-Contrl.game.beijing[0].getHeight())/2+280,Graphics.TOP | Graphics.LEFT);
				myself->picLib->DrawImage(myself->picLib,myself->lifeImageD,165+myself->dogBlood-12*i,280);
				#endif
			}
			
			//lifeC.LifeC(g, changelifeC);
			num=(myself->catBlood-myself->changelifeC)*5/myself->catBlood;
    		for(i=0;i<num;i++)
    		{
    			#ifdef GAME_240_320
				//g.drawImage(Contrl.menu.LifeImageC,(Contrl.game.screenw-Contrl.game.beijing[0].getWidth())/2+5+12*i,(Contrl.game.screenh-Contrl.game.beijing[0].getHeight())/2+280,Graphics.TOP | Graphics.LEFT);
				myself->picLib->DrawImage(myself->picLib,myself->lifeImageC,5+12*i,280);
				#endif
			}

			myself->picLib->DrawRegionEx(myself->picLib,myself->catImg,myself->catPX,225,55*myself->cattu,0,55,55,true,0);
			
            myself->picLib->DrawRegionEx(myself->picLib,myself->dogImg,180,225,55*myself->dogtu,0,55,55,true,0);
			bombMove(myself);
			drawWind(myself);
			//fish.DrawSelf(g);
			fishDrawSelf(myself);
			//bone.DrawSelf(g);
			dogDrawSelf(myself);
			if(myself->fishShow == true)
			{
				myself->picLib->DrawRegionEx(myself->picLib,myself->fishImg,myself->fishPX,myself->fishPY,myself->fishFrame*25,0,25,25,true,0);
			}
			if(myself->boneShow == true)
			{
				myself->picLib->DrawRegionEx(myself->picLib,myself->boneImg,myself->bonePX,myself->bonePY,myself->boneFrame*25,0,25,25,true,0);
			}

			Press_fire(myself);

			bomb(myself);
			if(myself->teshu)
			{
				a= myself->bonePX;
				b= myself->bonePY; 
			}
			if(myself->bombShow == true)
				bombShowPaint(a,b,myself);
			if(myself->teshu)
			{
				myself->bonePX = 500;
				myself->bonePY = 500;
				myself->teshu = false;			
			}
			DrawOver(myself);
			DrawWin(myself);

			if (myself->alive) {
				if (!myself->isPause) {
					
					myself->picLib->DrawRegionEx(myself->picLib,myself->buttonImg,SCREEN_WIDTH-48,SCREEN_HEIGHT-18,0,0,48,18,true,0);
				} else {
					
					myself->picLib->DrawRegionEx(myself->picLib,myself->buttonImg,SCREEN_WIDTH-48,SCREEN_HEIGHT-18,0,18,48,18,true,0);
					
					myself->picLib->DrawRegionEx(myself->picLib,myself->buttonImg,0,SCREEN_HEIGHT-18,0,36,48,18,true,0);
				}
			} else {
				
				myself->picLib->DrawRegionEx(myself->picLib,myself->buttonImg,0,SCREEN_HEIGHT-18,0,36,48,18,true,0);
			}
			
		}

void catLoveDogkeyPressed(CatLoveDog_InGame *myself)
{
	gm_s16 px,py;
 	if (!myself->isPause) 
	{
	   if(extOldGameManager->IsKeyDown(MF_KEY_LEFT|MF_KEY_4) && myself->catPX > -10)
	   		myself->catPX = myself->catPX-2;
		if(extOldGameManager->IsKeyDown(MF_KEY_RIGHT|MF_KEY_6) && myself->catPX < 80)
	   		myself->catPX = myself->catPX+2;
		if(extOldGameManager->IsKeyDown(MF_KEY_MID|MF_KEY_5)) myself->isFire++;
		if(extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT)) myself->isPause = true;
		#ifdef GAME_240_320
			if(SCREEN_IsPointerDown())
				{
					px = SCREEN_GetPointerX();
					py = SCREEN_GetPointerY();
					if(CdRectPoint2(190,300,50,20,px,py)) myself->isPause = true;
				}
		#endif
 	}
	else
	{
		if(extOldGameManager->IsKeyDown(MF_KEY_LEFTSOFT))
		{
					myself->alive = false;
                    myself->cattu = 0;
                    myself->dogtu = 0;
                    myself->fishShow = false;
					myself->boneShow = false;
                    myself->changelifeC = 0;
                    myself->changelifeD = 0;
                    myself->isPause = false;
					extVmSysManager->VmSetFPS(100);
					CatLoveDog_Screen_Next = &CatLoveDog_Screen_Title;
					CatLoveDogTitleState = CatLoveDog_TITLE_STATE_MENU;
					catLoveDogLoadingStep = 0;
					catLoveDogLoadingStepTotal = 16;
					SCREEN_ChangeScreen(&CatLoveDog_Screen_Loading);
		}
		#ifdef GAME_240_320
			if(SCREEN_IsPointerDown())
				{
					px = SCREEN_GetPointerX();
					py = SCREEN_GetPointerY();
					if(CdRectPoint2(0,300,50,20,px,py))
					{
						myself->alive = false;
                   	    myself->cattu = 0;
                        myself->dogtu = 0;
                        myself->fishShow = false;
					    myself->boneShow = false;
                        myself->changelifeC = 0;
                        myself->changelifeD = 0;
                        myself->isPause = false;
					    extVmSysManager->VmSetFPS(100);
					    CatLoveDog_Screen_Next = &CatLoveDog_Screen_Title;
					    CatLoveDogTitleState = CatLoveDog_TITLE_STATE_MENU;
					    catLoveDogLoadingStep = 0;
					    catLoveDogLoadingStepTotal = 16;
					    SCREEN_ChangeScreen(&CatLoveDog_Screen_Loading);
					}
				}
		#endif
		if(extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT)) 
		{
			myself->isPause = false;
		}
		#ifdef GAME_240_320
			if(SCREEN_IsPointerDown())
				{
					px = SCREEN_GetPointerX();
					py = SCREEN_GetPointerY();
					if(CdRectPoint2(190,300,50,20,px,py)) myself->isPause = false;
				}
		#endif
	}
		
}

void CatLoveDog_InGame_Windows_Render(void *param)
{
	CatLoveDog_InGame *myself = (CatLoveDog_InGame *)param;
	paint(myself);

}
void CatLoveDog_InGame_Windows_Update(void * param)
{
	
	CatLoveDog_InGame *myself = (CatLoveDog_InGame *)param;	
	
	if(myself->alive)
		paint(myself);
	catLoveDogkeyPressed(myself);

}

