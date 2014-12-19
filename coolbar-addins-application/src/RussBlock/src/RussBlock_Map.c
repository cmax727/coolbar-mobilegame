#include "RussBlock_Map.h"
#include "coolbar_GameUtil.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

 gm_s32 russBlockGameData [2][4];
 gm_u8  russBlockGameGrid [2][VERTICAL_BOXS][HORIZONTAL_BOXS];


Board Table_board[VERTICAL_BOXS][HORIZONTAL_BOXS]; //21*12

const gm_s8 nextboxTable [10]={1,3,5,7,9,11,12,14,17,18};  //初始化下个方块只能从这里选，因为框子显示不了其他的
const gm_u8 scoreTable[4]={10,30,60,100}; 
const gm_u8 speedDown[4]={8,12,16,19};      /*方块下落的4个等级速度*/
/*初始化方块内容*/
struct SHAPE shapes[MAX_BOX]=
{
    /*
    *   口     口口口   口口      口
    *   口     口         口  口口口
    *   口口              口        
    */

    {0x88,  0xc0,   RED,    1,  3},//0
    {0xe8,  0x0,    RED,    2,  0},//1
    {0xc4,  0x40,   RED,    3,  1},//2
    {0x2e,  0x0,    RED,    0,  2},//3
    /*
    *   口        口口 口口口
    *   口 口     口       口
    * 口口 口口口 口    
    */
    {0x44,  0xc0,   ORANGE, 5,  7},//4
    {0x8e,  0x0,    ORANGE, 6,  4},//5
    {0xc8,  0x80,   ORANGE, 7,  5},//6
    {0xe2,  0x0,    ORANGE, 4,  6},//7

    /*
    *   口
    *   口口
    *     口
    */
    {0x8c,  0x40,   YELLOW, 9,  9},//8
    {0x6c,  0x0,    YELLOW, 8,  8},//9

    /*
    *   口   
    * 口口   口口
    * 口       口口
    */
    {0x4c,  0x80,   GREEN,  11, 11},//10
    {0xc6,  0x0,    GREEN,  10, 10},//11

    /*
    *   口    口   口口口   口
    * 口口口  口口   口   口口
              口            口
    */        
    {0x4e,  0x0,    GRAY,   13, 15},//12
    {0x8c,  0x80,   GRAY,   14, 12},//13
    {0xe4,  0x0,    GRAY,   15, 13},//14
    {0x4c,  0x40,   GRAY,   12, 14},//15

    /*口
    * 口
    * 口
    * 口
    */
    {0x88,  0x88,   BLUE,   17, 17},  //16
    {0xf0,  0x0,    BLUE,   16, 16},  //17

    /*
    * 口口
    * 口口
    */

    {0xcc,  0x0,    PINK,   18, 18}     //18

};

 gm_s8 russBlockSpeed;   //方块下落速度 最高为5，最低为0（初级）


 gm_s32 russBlockHitNum;  //连击数

    
 gm_s8 current_box_numb;        /*保存当前方块编号*/
 gm_s32 Curbox_x,Curbox_y;/*x,y是保存方块的当前坐标的，是象素坐标*/
 gm_s32 lastBox_x,lastBox_y;
 gm_s8 nextbox,thirdbox;
 gm_u8 flag_newbox=false;    /*是否要产生新方块的标记0*/
 gm_u8 flag_fastfall=false;  //是否出现快速下落的动画    
 gm_u8 flag_slowfall=false;  /*慢速下降到底动画标志*/
 gm_u8 flag_eraseBox=false; /*消方块标志*/
 gm_u8 flag_canMagic=false;
 gm_u8 flag_DlaySpeed=false;
 gm_s32 lastBlockSpeed;
 gm_s32 delaySpeedCount;
 gm_s8 timerCnt;
 gm_s32 renderCount;
 gm_s32 j_line;
 gm_s8 eraseBosList[2]={0,0};/*记录消的行数 【0】为记录需要消的行数，【1】记录需要消哪一行*/

void initRussBlockMap(RussBlock_Map * myself,Rect windows_Rect,DF_PictureLibrary *picLib,gm_s32 repaintMax)
{

    initDFWindows(&myself->windows,windows_Rect,myself,myself,repaintMax);
    myself->picLib=picLib;
    myself->windows.RenderCallBack=RussBlock_Map_Windows_Render;
    myself->windows.UpdateCallBack=RussBlock_Map_Windows_Update;

    myself->imgBack=myself->picLib->CreateImage(myself->picLib,SCREEN_WIDTH,SCREEN_HEIGHT);
    myself->picLib->SetGraphics(myself->picLib,myself->picLib->image[myself->imgBack]);
    RussBlock_Map_drawGrid(myself);
    myself->picLib->SetGraphics(myself->picLib,DF_DEFAULT_GRAPHICS);
    RussBlock_Loading_UpdateStep();
/*
    initDFActor(&myself->blockFallFast,0,0);
    initDFActor(&myself->blockFallSlow,0,0);
    initDFActor(&myself->blockErase,0,0);
*/
	//加载图片库
    myself->imgBlock[0]=picLib->GetImage(picLib,"b0.gif");
    myself->imgBlock[1]=picLib->GetImage(picLib,"b1.gif");
    RussBlock_Loading_UpdateStep();
    myself->imgBlock[2]=picLib->GetImage(picLib,"b2.gif");
    myself->imgBlock[3]=picLib->GetImage(picLib,"b3.gif");
    RussBlock_Loading_UpdateStep();
    myself->imgBlock[4]=picLib->GetImage(picLib,"b4.gif");
    myself->imgBlock[5]=picLib->GetImage(picLib,"b5.gif");
    RussBlock_Loading_UpdateStep();
    myself->imgBlock[6]=picLib->GetImage(picLib,"b6.gif");
    myself->imgTop=picLib->GetImage(picLib,"top.gif");

    RussBlock_Loading_UpdateStep();
   /*
   myself->blockFallFast.LoadActor(&myself->blockFallFast,myself->picLib,"fallfast.actor");
   myself->blockFallSlow.LoadActor(&myself->blockFallSlow,myself->picLib,"bzxg.actor");
   myself->blockErase.LoadActor(&myself->blockErase,myself->picLib,"erase.actor");
   */
    RussBlock_Loading_UpdateStep();
    RussBlock_Map_init(SYS_X+BEGIN_BOXS_X*BSIZE,SYS_Y,HORIZONTAL_BOXS,VERTICAL_BOXS);
}
void RussBlock_Map_init(gm_s32 x,gm_s32 y,gm_s32 m,gm_s32 n)
{
    gm_s32 i,j,oldx;
    oldx=x;
    for(j=0;j<n;j++)
    {
        for(i=0;i<m;i++)
        {
            Table_board[j][i].var=0;
            Table_board[j][i].color=0;
            Table_board[j][i].var=russBlockGameGrid[russBlockGameType][j][i];
            Table_board[j][i].color=Random(0,6);
        
            x+=BSIZE;
        }
        y+=BSIZE;
        x=oldx;
    }
    Curbox_x=x;
    Curbox_y=y;
    flag_newbox=false;  /*是否要产生新方块的标记0*/
    russBlockSpeed=russBlockGameData[russBlockGameType][3];     /*下落速度*/    
    russBlockHitNum=0;
    timerCnt=0;
    j_line=0;
    flag_newbox=false;      /*是否要产生新方块的标记0*/
    flag_fastfall=false;  //是否出现快速下落的动画  
    flag_slowfall=false;  /*慢速下降到底动画标志*/
    flag_eraseBox=false; /*消方块标志*/
    flag_canMagic=false;
    nextbox=MkNextBox(-1);
}

void RussBlock_Map_Windows_Render(void *param)
{
    RussBlock_Map * myself=(RussBlock_Map *)param;
        
    //画背景图缓冲
    myself->picLib->DrawImage(myself->picLib,myself->imgBack,myself->windows.DF_Windows_Rect.x,myself->windows.DF_Windows_Rect.y);
    show_AllBlock( param);
    show_box(param,Curbox_x,Curbox_y,current_box_numb,shapes[current_box_numb].color);  //显示当前方块
    myself->picLib->DrawImage(myself->picLib,myself->imgTop,0,0);
#ifdef GAME_240_320
    show_box(param,37,6,nextbox,shapes[nextbox].color); //显示下个方块
    show_box(param,97,6,thirdbox,shapes[thirdbox].color); //显示下下个方块
#endif // GAME_240_320
#ifdef GAME_176_220
    show_box(param,17,2,nextbox,shapes[nextbox].color); //显示下个方块
    show_box(param,73,2,thirdbox,shapes[thirdbox].color); //显示下下个方块
#endif // GAME_240_320
   /* if (flag_fastfall)
    {
        if (myself->blockFallFast.currentFrameCount>=myself->blockFallFast.GetFrameNum(&myself->blockFallFast))
        {
            flag_fastfall=0;
        }
        myself->blockFallFast.Update(&myself->blockFallFast);

    }
    else if (flag_slowfall)
    {
        if (myself->blockFallSlow.currentFrameCount>=myself->blockFallSlow.GetFrameNum(&myself->blockFallSlow))
        {
            flag_slowfall=false;
        }
        myself->blockFallSlow.Update(&myself->blockFallSlow);
    }


    if (flag_fastfall)
    {
        myself->blockFallFast.RenderEx(&myself->blockFallFast,-lastBox_x-BSIZE,-lastBox_y);
    }
    else if (flag_slowfall)
    {
        myself->blockFallSlow.RenderEx(&myself->blockFallSlow,-lastBox_x-BSIZE,-lastBox_y);
    }*/
    if(flag_eraseBox)
    RussBlock_EraseBlock_Paint(myself,eraseBosList);
    //gm_TRACE("!!!!!!!!!Painted over Map!!!!!!!!!!\n");
}
static  gm_s16 keyTime_my =0;
void RussBlock_Map_Windows_Update(void * param)
{
    RussBlock_Map * myself=(RussBlock_Map *)param;
    gm_s16 px,py;
    setTimerCnt();    
    if(flag_eraseBox)
        RussBlock_EraseBlock_Run(myself,eraseBosList);

    if (getManagerPtr()->IsKeyDown(MF_KEY_LEFT|MF_KEY_4))   //按键操作left
    {
        keyTime_my=0;
        if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MOVELEFT) && !flag_slowfall)
        {Curbox_x-=BSIZE;}
    }
    else if (getManagerPtr()->IsKeyDown(MF_KEY_RIGHT|MF_KEY_6))  //按键操作right
    {
        keyTime_my=0;
        if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MOVERIGHT) && !flag_slowfall)
        {Curbox_x+=BSIZE;}
    }
    else if (getManagerPtr()->IsKeyDown(MF_KEY_DOWN |MF_KEY_8))  //按键操作down
    {
        keyTime_my=0;
        if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MOVEDOWN))
        {Curbox_y+=BSIZE;}
        else 
        {
            flag_newbox=true;
        }
    }
    else if (getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2)) //按键操作roll
    {
        if( !flag_slowfall && MoveAble(Curbox_x,Curbox_y,shapes[current_box_numb].next,MOVEROLL)  )
        {current_box_numb=shapes[current_box_numb].next;}
    }
    else if (getManagerPtr()->IsKeyDown(MF_KEY_MID|MF_KEY_5))      //直接下落
    {
        if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MOVETOBASE))
        {
        }
        else 
        {
            flag_newbox=true;
            Curbox_y=Curbox_y+(VERTICAL_BOXS-j_line)*BSIZE;
            lastBox_y=Curbox_y;
            lastBox_x=Curbox_x;
            flag_fastfall=true;
        }
    }
    else if (getManagerPtr()->IsKeyHold(MF_KEY_LEFT |MF_KEY_4))      //左hold
    {
        keyTime_my++;
        if(keyTime_my%2==0)
        {
        if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MOVELEFT) && !flag_slowfall )
        {Curbox_x-=BSIZE;}
        if (keyTime_my==100)
        {
            keyTime_my=0;
        }
        }
    }
    else if (getManagerPtr()->IsKeyHold(MF_KEY_RIGHT |MF_KEY_6))
    {
        keyTime_my++;
        if(keyTime_my%2==0)
        {
        if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MOVERIGHT)  && !flag_slowfall)
        {Curbox_x+=BSIZE;}
        if (keyTime_my==100)
        {
            keyTime_my=0;
        }
        }
    }
    else if (getManagerPtr()->IsKeyHold(MF_KEY_DOWN |MF_KEY_8))    //MOVEDOWNHOLD
    {
        keyTime_my++;
        if(keyTime_my%2==0)
        {
            if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MOVEDOWNHOLD))
            {
                Curbox_y+=BSIZE;
            }
            else 
            {
                flag_newbox=true;
            }
            if (keyTime_my==100)
            {
                keyTime_my=0;
            }
        }
    }  
    else if (getManagerPtr()->IsKeyDown(MF_KEY_LEFTSOFT))
    {
        russBlockGameMenuShow=1;
        russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_GAMEMENU;
    }
    if(SCREEN_IsPointerDown())//触摸操作
    {
        px = SCREEN_GetPointerX();//得到屏幕点
        py = SCREEN_GetPointerY();

        if(CdRectPoint(TOUCH_X_LEFT,TOUCH_Y_LEFT,TOUCH_X1_LEFT,TOUCH_Y1_LEFT,px,py))
            {
                russBlockGameMenuShow=1;
                russBlockInGameState=RUSSBLOCK_INGAME_MAINSTATE_GAMEMENU;
            }    }

    if(flag_newbox)     /*产生新方块*/
    {
        /*这时相当于方块到底部了,把其中出现点满一行的清去，置0*/
        MkNextBox(nextbox);
        nextbox=thirdbox;
#ifdef DEBUG_MY
        if (Random(0,9)%2)
        {
            thirdbox=18;
        }
        else
        thirdbox=17;
#else
        thirdbox=nextboxTable[Random(0,9)];
#endif // DEBUG_MY

        if(!MoveAble(Curbox_x,Curbox_y,current_box_numb,MOVEDOWN))/*刚生一下就到东西,游戏结束*/
        {
            show_box(param,Curbox_x,Curbox_y,current_box_numb,shapes[current_box_numb].color);
            flag_GameOver=true;
            russBlockUi.UpdateGirlFace(&russBlockUi,5);/*MM哭~~~~（>_<)~~~~ */
        }
        else
        {
            flag_newbox=false;
        }
        
    }
    else    /*自由下落*/
    {
        if ( timerCnt> (BLOCK_SPEED-russBlockSpeed))        /*如果下落计数超过设定值，则自由下落*/
        {
            if(MoveAble(Curbox_x,Curbox_y,current_box_numb,MOVEDOWN) && !flag_eraseBox)
            {
                Curbox_y+=BSIZE;
            }
            timerCnt=0;
        }
    }
}

/*刷新下个方块区域*/
void RussBlock_Flush_NextBloc(void * param)
{
    RussBlock_Map * myself=(RussBlock_Map *)param;
    myself->picLib->DrawImage(myself->picLib,myself->imgTop,0,0);
    show_box(myself,37,6,nextbox,shapes[nextbox].color); //显示下个方块
    show_box(myself,97,6,thirdbox,shapes[thirdbox].color); //显示下下个方块
}

/*画网格*/
void RussBlock_Map_drawGrid(void * param)
{
    RussBlock_Map * myself=param;
    gm_s32 i=0,j;
#ifdef GAME_240_320
    //填充游戏区域内的底色
    myself->picLib->FillRect(myself->picLib,BLOCKAREAX,BLOCKAREAY,155,258+50,GAME_ToRGB(36,19,121)); //99->19
    for (i=0;i<VERTICAL_BOXS+1;i++)
    {
        for (j=0;j<HORIZONTAL_BOXS+1;j++)
        {
            myself->picLib->FillRect(myself->picLib,BLOCKAREAX,BLOCKAREAY+12*i,145,1,GAME_ToRGB(39,47,153));
            myself->picLib->FillRect(myself->picLib,BLOCKAREAX+12*j,BLOCKAREAY,1,252,GAME_ToRGB(39,47,153));
        }
    }
#endif
#ifdef GAME_176_220
    //填充游戏区域内的底色
    myself->picLib->FillRect(myself->picLib,BLOCKAREAX-2,BLOCKAREAY,155-84+45,160+14,GAME_ToRGB(36,19,121)); //99->19
    for (i=0;i<VERTICAL_BOXS+1;i++)
    {
        for (j=0;j<HORIZONTAL_BOXS+1;j++)
        {
            myself->picLib->FillRect(myself->picLib,BLOCKAREAX,BLOCKAREAY+9*i,109,1,GAME_ToRGB(39,47,153));
            myself->picLib->FillRect(myself->picLib,BLOCKAREAX+9*j,BLOCKAREAY,1,172,GAME_ToRGB(39,47,153));
        }
    }
#endif
}

static void RussBlock_Map_SetSpecifiedGrid(void * param,gm_s8 beginrow,gm_s8 row,gm_u8 isDraw)
{
    RussBlock_Map * myself=param;
    gm_s32 i,j;
        for (i=beginrow;i<beginrow+row;i++)
        {
            for (j=0;j<HORIZONTAL_BOXS;j++)
            {
                //Table_board[i][j].isDraw=isDraw;
                Table_board[i][j].var=isDraw;
            }
        }
}


/*方块下落到底通知播放动画*/
void BlockDowned()
{
      flag_slowfall=true;
      lastBox_y=Curbox_y;
      lastBox_x=Curbox_x;
}


/* 返回下个方块号*/
gm_s32 MkNextBox(gm_s32 box_numb)
{
    gm_s32 mask=128,t_boardx,t_boardy,n,m;
    t_boardx=(Curbox_x-SYS_X)/BSIZE;
    t_boardy=(Curbox_y-SYS_Y)/BSIZE;
    if(box_numb!=-1)
    {
    for(n=0;n<4;n++)
    {
        for(m=0;m<4;m++)
        {
            if( ((shapes[current_box_numb].box[n/2]) & mask) )/*设置游戏板*/
            {
                Table_board[t_boardy+n][t_boardx+m].var=1;/*这里设制游戏板*/
                Table_board[t_boardy+n][t_boardx+m].color=shapes[current_box_numb].color;/*这里设制游戏板*/
            }
            //mask=mask/(2);
            mask>>=1;
            if(mask==0)mask=128;
        }
    }
    }
    setFullRow(t_boardy);
    if (!flag_eraseBox)  russBlockHitNum=0;  /*若无消层则清空连击记录*/

    Curbox_x=SYS_X+BEGIN_BOXS_X*BSIZE,Curbox_y=SYS_Y;/*再次初始化座标*/
    if(box_numb==-1)
    {
#ifdef DEBUG_MY
        box_numb=17;
        thirdbox=17;
#else
        box_numb=nextboxTable[Random(0,9)];
        thirdbox=nextboxTable[Random(0,9)];
#endif

    }
    current_box_numb=box_numb;   //产生了当前方块
    flag_newbox=false;
#ifdef DEBUG_MY
        return(17);  
#else
        return(nextboxTable[Random(0,9)]);     //再随机产生下个方块
#endif

}

/*   删除一行满的情况
*   这里的y为具体为满的一行
*/
gm_s32 DelFullRow(gm_s32 y)
{
    /*该行游戏板往下移一行*/
    gm_s32 n,top=0;             /*top保存的是当前最高点,出现一行全空就表示为最点了,移动是到最高点结束*/
    gm_s8 m,totoal;
    for(n=y;n>=0;n--)/*从当前行往上看*/
    {
        totoal=0;
        for(m=0;m<HORIZONTAL_BOXS;m++)
        {
            if(!Table_board[n][m].var)totoal++;             /*没占有方格+1*/
            {
                if (n-1<0)
                {
                    gm_TRACE("-1");
                }
                Table_board[n][m].var=Table_board[n-1][m].var;
                Table_board[n][m].color=Table_board[n-1][m].color;
            }
        }
        if(totoal==HORIZONTAL_BOXS) /*发现上面有连续的空行提前结束,是因为检测到了最上面的空白行*/
        {
            top=n;
            break;
        }
    }
    return(top);/*返回最高点*/
}

/*魔法消除最底下4行*/
gm_u8 setFullRow_Magic()
{
    gm_s32 n,m,total,rows=0,full_numb;
    gm_u8 isBreak=true;
    for (n=VERTICAL_BOXS-1;n>=VERTICAL_BOXS-5 && isBreak;n--)
    {
        total=0;
        for (m=0;m<HORIZONTAL_BOXS &&isBreak;m++)
        {
            if (!Table_board[n][m].var)
            {
                total++;
                if (total==HORIZONTAL_BOXS)   
                {
                    if (n==VERTICAL_BOXS-1)  /*目前无方块可消除*/
                    {
                        eraseBosList[0]=0;
                        eraseBosList[1]=0;
                        gm_TRACE("消除魔法释放错误！目前无方块可消除！\n");
                        return false;
                    }
                    isBreak=false;
                    eraseBosList[1]=n+1;
                }
            }
        }
        if (isBreak)
        {
            rows++;
        }
    
    }

    if (total==HORIZONTAL_BOXS)     //说明有空行,小于或等于4行
    {
        flag_eraseBox=true;
        eraseBosList[0]=rows;
        if (russBlockProp[GAME_PROP_BOMB])
        russBlockProp[GAME_PROP_BOMB]--;
    }
    else   //相反情况,大于4行
    {
        flag_eraseBox=true;
        eraseBosList[0]=4;
        eraseBosList[1]=VERTICAL_BOXS-4;
        if (russBlockProp[GAME_PROP_BOMB])
            russBlockProp[GAME_PROP_BOMB]--;

    }

    full_numb=eraseBosList[0];
    russBlockUi.clearedlayer+=full_numb; 

    //if(!(russBlockUi.clearedlayer%BLOCK_ERASE)) 
    if(russBlockUi.clearedlayer/BLOCK_ERASE>russBlockUi.lastClearedLayer/BLOCK_ERASE)   /*升级判断*/
    {
        russBlockUi.level++; 
        if(russBlockSpeed<4*4 && russBlockUi.level%2==0)
            russBlockSpeed+=4;
        if (russBlockUi.level==SHOWGIRL_LEVEL_ONE|| russBlockUi.level==SHOWGIRL_LEVEL_TWO ||russBlockUi.level==SHOWGIRL_LEVEL_THREE ||russBlockUi.level==SHOWGIRL_LEVEL_FOUR) 
        {        

            flag_GirlShow_Notify=true;
        }
    }
    russBlockUi.score+=scoreTable[full_numb-1];
    russBlockUi.lastClearedLayer=russBlockUi.clearedlayer;

    russBlockUi.UpdateGirlFace(&russBlockUi,full_numb);
    russBlockUi.UpdateClearedLayer(&russBlockUi);
    russBlockUi.UpdateScore(&russBlockUi);
    russBlockUi.UpdateLevel(&russBlockUi);
    return TRUE;

}


/************************************************************************/
/*消方块逻辑和特效  */    
/************************************************************************/

void RussBlock_EraseBlock_Paint(void * param,gm_s8 arr[])
{
    RussBlock_Map * myself=(RussBlock_Map *)param;
	/*
#ifdef GAME_240_320
    if (eraseBosList[0]==1)
        myself->blockErase.RenderEx(&myself->blockErase,-(SCREEN_WIDTH/2-35),-(arr[1]*BSIZE+SYS_Y+4));
    else
    myself->blockErase.RenderEx(&myself->blockErase,-(SCREEN_WIDTH/2-35),-(arr[1]*BSIZE+SYS_Y+BSIZE));

#endif 
#ifdef GAME_176_220
    if (eraseBosList[0]==1)
        myself->blockErase.RenderEx(&myself->blockErase,-(SCREEN_WIDTH/2-35),-(arr[1]*BSIZE+SYS_Y+4));
    else
        myself->blockErase.RenderEx(&myself->blockErase,-(SCREEN_WIDTH/2-35),-(arr[1]*BSIZE+SYS_Y+BSIZE));

#endif
  */
}
/*找到一行满的情况*/
void setFullRow(gm_s32 t_boardy)
{
    gm_s32 n,full_numb=0,top=0;         /*top保存的是当前方块的最高点*/
    gm_s8 m,full_layer=0;
    /*
    t_boardy 口       5
    口       6
    口口口口口口   7
    n  口口口口口口   8
    */
    //test_bordy=t_boardy;
    for(n=t_boardy+3;n>=t_boardy;n--)
    {
        if(n<0 || n>=VERTICAL_BOXS ){continue;} /*超过低线了*/
        for(m=0;m<HORIZONTAL_BOXS;m++)          /*水平的方向*/
        {
            if(!Table_board[n][m].var)break;        /*发现有一个是空就跳过该行*/
        }
        if(m==HORIZONTAL_BOXS)                  /*找到满行了*/
        {
            eraseBosList[0]++;
            eraseBosList[1]=n;
            full_numb++;
        }
    }


    if(full_numb)
    {
        gm_s32 oldx,x=SYS_X,y=BSIZE*top+SYS_Y;
        oldx=x;
        flag_eraseBox=true;

        {
            russBlockHitNum++;         
            if (russBlockHitNum>1)       /*有连击*/
            {
                russBlockUi.flag_hit=true;    /*开启UI里显示连击特效的开关*/
                russBlockUi.hitNum++;
                switch (russBlockHitNum)
                {
                case 2:
                case 3:
                case 4:
                    russBlockUi.score+=scoreTable[full_numb-1]*russBlockHitNum;
                    break;
                default:
                    russBlockUi.score+=scoreTable[full_numb-1]*5;
                    break;
                }
            }
            else/*加分数*/   //无连击
                russBlockUi.score+=scoreTable[full_numb-1];
        }

        russBlockUi.clearedlayer+=full_numb; 
    //  if(!(russBlockUi.clearedlayer%BLOCK_ERASE))  
        if(russBlockUi.clearedlayer/BLOCK_ERASE>russBlockUi.lastClearedLayer/BLOCK_ERASE)//消去20行升级
        {
            russBlockUi.level++; 
            if(russBlockSpeed<4*4 && russBlockUi.level%2==0)
                russBlockSpeed+=4;
            if (russBlockUi.level==SHOWGIRL_LEVEL_ONE|| russBlockUi.level==SHOWGIRL_LEVEL_TWO ||russBlockUi.level==SHOWGIRL_LEVEL_THREE ||russBlockUi.level==SHOWGIRL_LEVEL_FOUR) 
            {        
                flag_GirlShow_Notify=true;
            }
        }
        russBlockUi.lastClearedLayer=russBlockUi.clearedlayer;
        russBlockUi.UpdateGirlFace(&russBlockUi,full_numb);
        russBlockUi.UpdateClearedLayer(&russBlockUi);
        russBlockUi.UpdateScore(&russBlockUi);
        russBlockUi.UpdateLevel(&russBlockUi);

    }
}
void RussBlock_EraseBlock_Run(void * param,gm_s8 arr[])
{
    RussBlock_Map * myself=(RussBlock_Map *)param;
    gm_s8 i,n,m,full_numb=0,top=0;
   // if (eraseBosList[0]>0)
    //myself->blockErase.ChangeAction(&myself->blockErase,eraseBosList[0]-1);
   // if (myself->blockErase.currentFrameCount>=myself->blockErase.GetFrameNum(&myself->blockErase))
    //{
        flag_eraseBox=false;
        RussBlock_Map_SetSpecifiedGrid(param,eraseBosList[1],eraseBosList[0],1);/*设为可见，消去*/
        for(i=eraseBosList[1];i<eraseBosList[1]+eraseBosList[0];i++)   /*消去整行方块*/
        {
            DelFullRow(i);
        }
        if (GAMETYPE_TIME==russBlockGameType)   /*是时间模式根据消的层数加时间*/
        {
            switch (eraseBosList[0])
            {
            case 1:
                russBlockGameTime+=2;
                break;
            case 2:
                russBlockGameTime+=5;
                break;
            case 3:
                russBlockGameTime+=10;
                break;
            case 4:
                russBlockGameTime+=20;
                break;
            }
            if (russBlockGameTime>BLOCK_TIME)
            {
                russBlockGameTime=BLOCK_TIME;
            }
        }
        eraseBosList[0]=0;
        eraseBosList[1]=0;
        flag_canMagic=false;
        //gm_TRACE("set flag_canMagic=false");

        russBlockUi.UpdateRect(&russBlockUi,0,0,SCREEN_WIDTH,SCREEN_HEIGHT-39);
        if(flag_GirlShow_Notify)    /*美女脱衣开始*/
        {
            flag_GirlShow=true;
            flag_GirlShow_Notify=false;
        }
   // }
/*    else if (myself->blockErase.currentFrameCount>=1 
    && myself->blockErase.currentFrameCount<myself->blockErase.GetFrameNum(&myself->blockErase))  /*暂时使待消去行的方块不可见*/
  /*  {

        RussBlock_Map_SetSpecifiedGrid(param,eraseBosList[1],eraseBosList[0],0);
    }*/
   // myself->blockErase.Update(&myself->blockErase);
}

/* 判断是否可以移动
* x,y为当前方块位置
* box_numb为方块号
* direction 方向标志 
*/
gm_u8 MoveAble(gm_s32 x,gm_s32 y,gm_s32 box_numb,gm_s32 direction)
{
    gm_s32 n,m,t_boardx,t_boardy,j;         /*t_boardx 当前方块最左边在游戏板的位置*/
    gm_u8 isbreak=true;
    gm_s32 mask;
    if(direction==MOVELEFT)             /*如果向左移*/
    {
        mask=128;
        x-=BSIZE;
        t_boardx=(x-SYS_X)/BSIZE;
        t_boardy=(y-SYS_Y)/BSIZE;
        for(n=0;n<4;n++)
        {
            for(m=0;m<4;m++)    /*看最左边四个单元*/
            {
                if((shapes[box_numb].box[n/2]) & mask)/*最左边有方块并且当前游戏板也有方块*/
                {
                    if((x+BSIZE*m)<SYS_X)return(false);/*碰到最左边了*/
                    else if(Table_board[t_boardy+n][t_boardx+m].var)
                    {
                        return(false);
                    }
                }
                //mask=mask/(2);
                mask>>=1;
                if(mask==0)mask=128;
            }
        }
        return(true);
    }
    else if(direction==MOVERIGHT)       /*如果向右移*/
    {
        x+=BSIZE;
        t_boardx=(x-SYS_X)/BSIZE;
        t_boardy=(y-SYS_Y)/BSIZE;
        mask=128;
        for(n=0;n<4;n++)
        {
            for(m=0;m<4;m++)    /*看最右边四个单元*/
            {
                if((shapes[box_numb].box[n/2]) & mask)/*最右边有方块并且当前游戏板也有方块*/
                {
                    if((x+BSIZE*m)>=(SYS_X+BSIZE*HORIZONTAL_BOXS) )return(false);/*碰到最右边了*/
                    else if( Table_board[t_boardy+n][t_boardx+m].var)
                    {
                        return(false);
                    }
                }
                //mask=mask/(2);
                mask>>=1;
                if(mask==0)mask=128;
            }
        }
        return(true);
    }
    else if(direction==MOVEDOWN || direction==MOVEDOWNHOLD)     /*如果向下移*/
    {
        y+=BSIZE;
        t_boardx=(x-SYS_X)/BSIZE;
        t_boardy=(y-SYS_Y)/BSIZE;
        mask=128;
        for(n=0;n<4;n++)
        {
            for(m=0;m<4;m++)    /*看最下边四个单元*/
            {
                if((shapes[box_numb].box[n/2]) & mask)/*最下边有方块并且当前游戏板也有方块*/
                {
                    if((y+BSIZE*n)>=(SYS_Y+BSIZE*VERTICAL_BOXS) 
                        ||  Table_board[t_boardy+n][t_boardx+m].var
                        )
                    {
                        flag_newbox=true;
                        BlockDowned();
                        break;
                    }
                }
                mask>>=1;/*这样可以得到每隔八位的mask 0001 0000,16 和 0000 0001*/
                if(mask==0)mask=128;
            }
        }
        if(flag_newbox)
        {
            return(false);
        }
        else
            return(true);
    }
    else if (direction==MOVETOBASE) /*直接快速移动到底*/
    {
        for (j=VERTICAL_BOXS;j>0&& isbreak;j--)
        {
            y+=BSIZE;
            t_boardx=(x-SYS_X)/BSIZE;
            t_boardy=(y-SYS_Y)/BSIZE;
            mask=128;
            for(n=0;n<4&& isbreak;n++)
            {
                for(m=0;m<4&& isbreak;m++)  /*看最下边四个单元*/
                {
                    if((shapes[box_numb].box[n/2]) & mask)/*最下边有方块并且当前游戏板也有方块*/
                    {
                        if(  (y+BSIZE*n)>=(SYS_Y+BSIZE*VERTICAL_BOXS) || Table_board[t_boardy+n][t_boardx+m].var)
                        {
                             flag_newbox=true;
                             isbreak=false;
                             j_line=j;
                             break;
                        }
                    }
                    //mask=mask/(2);/*这样可以得到每隔八位的mask 0001 0000,16 和 0000 0001*/
                    mask>>=1;
                    if(mask==0)mask=128;
                }
            }
        }

        if(flag_newbox)
        {
            return(false);
        }
        else
            return(true);

    
    }
    else if(direction==MOVEROLL)        /*转动*/
    {
        t_boardx=(x-SYS_X)/BSIZE;
        t_boardy=(y-SYS_Y)/BSIZE;
        mask=128;
        for(n=0;n<4;n++)
        {
            for(m=0;m<4;m++)    /*看最下边四个单元*/
            {
                if((shapes[box_numb].box[n/2]) & mask)/*最下边有方块并且当前游戏板也有方块*/
                {
                    if((y+BSIZE*n)>=(SYS_Y+BSIZE*VERTICAL_BOXS) )return(false);/*碰到最下边了*/
                    if((x+BSIZE*n)>=(SYS_X+BSIZE*HORIZONTAL_BOXS) )return(false);/*碰到最左边了*/
                    if((x+BSIZE*m)>=(SYS_X+BSIZE*HORIZONTAL_BOXS) )/*碰到最右边了*/
                    {
                        if (box_numb==17)     /*是横直棍*/
                        {
                            Curbox_x-=BSIZE*3;
                        }
                        else
                        Curbox_x-=BSIZE;
                        return(true);
                    }
                    else if( Table_board[t_boardy+n][t_boardx+m].var)
                    {
                        return(false);
                    }
                }
                //mask=mask/(2);/*这样可以得到每隔八位的mask 0001 0000,16 和 0000 0001*/
                mask>>=1;
                if(mask==0)mask=128;
            }
        }
        return(true);
    }
    else
    {
        return(false);
    }

}

void show_AllBlock(void * param)
{
    RussBlock_Map *myself=(RussBlock_Map *)param;
    gm_s32 i,j;
    for(j=0;j<VERTICAL_BOXS;j++)
    {
        for(i=0;i<HORIZONTAL_BOXS;i++)
        {
            if (Table_board[j][i].var /*&& Table_board[j][i].isDraw*/)
            {
                //gm_TRACE("Table_board[j][i].var==1 j==%d i==%d color==%d ",j,i,Table_board[j][i].color);
                if(!flag_GameOver)
                myself->picLib->DrawImage(myself->picLib,myself->imgBlock[Table_board[j][i].color],i*BSIZE+SYS_X,j*BSIZE+SYS_Y);
                else
                myself->picLib->DrawImage(myself->picLib,myself->imgBlock[PINK],i*BSIZE+SYS_X,j*BSIZE+SYS_Y);

            }

        }

    }
}


/*
显示指定的方块
*/
void show_box(void *param,gm_s32 x,gm_s32 y,gm_s32 box_numb,gm_u8 color)
{
    RussBlock_Map *myself=param;
    gm_s32 i=0,ii=0,ls_x=x;
    if(box_numb<0 || box_numb>=MAX_BOX)/*指定的方块不存在*/
        box_numb=MAX_BOX/2;

    //setfillstyle(SOLID_FILL,color);
    /********************************* 
    *   移位来判断第哪一位是1
    *   方块是每1行用半个字节来表示
    *   128d=1000 0000b
    */
    for(ii=0;ii<2;ii++) 
    {
        gm_s32 mask=128;
        for(i=0;i<8;i++)
        {
            if(i%4==0 && i!=0)              /*表示转到方块的下一行了*/
            {
                y+=BSIZE;
                x=ls_x;
            }
            /*左移后得到的是最高位*/
            if((shapes[box_numb].box[ii])&mask)
            {
                if(!flag_GameOver)
                myself->picLib->DrawImage(myself->picLib,myself->imgBlock[color],x,y);
                else
                myself->picLib->DrawImage(myself->picLib,myself->imgBlock[PINK],x,y);
            }
            x+=BSIZE;
            //mask/=2;
            mask>>=1;
        }
        y+=BSIZE;
        x=ls_x;
    }
}

void setTimerCnt()
{
    renderCount=(renderCount+1)%100;
    timerCnt++;
    if(russBlockGameType==GAMETYPE_TIME)
    {
        if (renderCount%10==0) 
        {
            if(russBlockGameTime>0)
                russBlockGameTime--;
            else
            {
                flag_GameOver=true;
                russBlockUi.UpdateGirlFace(&russBlockUi,5);/*MM哭~~~~（>_<)~~~~ */
            }
        }

    }
    if(flag_DlaySpeed)
    {
        if(delaySpeedCount++>300)  /*减速道具到时间*/
        {
            russBlockSpeed=lastBlockSpeed;
            delaySpeedCount=0;
            flag_DlaySpeed=false;
        }
    }
    
}

void copyGrid()
{
    gm_u8 j,m;
    for(j=0;j<VERTICAL_BOXS;j++)
    {
        for(m=0;m<HORIZONTAL_BOXS;m++)
            russBlockGameGrid[russBlockGameType][j][m]=Table_board[j][m].var;
    }
}
