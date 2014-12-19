#ifndef HITMOLE_PLAY_H
#define HITMOLE_PLAY_H

#include "DF_Windows.h"
#include "HitMole_Screen.h"
#include "DF_PictureLibrary.h"
typedef struct HITMOLE_PLAY
{
  DF_PictureLibrary * picLib;
  DF_Windows windows;
  gm_s32 shuxintime;
  gm_bool gameexit;//判断游戏是否结束
  gm_bool soundopen;//是否允许播放声音
  gm_s32 jishi;
  gm_s32 firsttime;
  gm_s32 secondtime;//计时器
  gm_s32 score;//玩家分数
  gm_s8 life;//自定义时玩家的生命数
  gm_s8 gamestage;//游戏状态：-1 LOGO画面，0 游戏菜单，1 游戏百分比选择，2 正在游戏，3 自定义难度选择，4 自定义游戏
  	        //5 帮助，6 关于，7排行榜,8 GAME OVER, 9 通关画面；
  gm_s16 biaotiweizhi;//=60;标题的初始位置    
  gm_s16 chuiziweizhi;//=biaotiweizhi;
  gm_s16 imgdishu;
  gm_s16 imgchuizi;
  gm_s16 imgicon;
  gm_s16 imglaba;
  gm_s16 imgbeijing;
  gm_s16 x_point;//=4;左上地洞的x坐标
  gm_s16 y_point;//=64;左上地洞的y坐标
  gm_s16 x_jiange;//=80;每个地洞的左右间隔
  gm_s16 y_jiange;//=80;每个地洞的上下间隔
  gm_u8 dongwidth;//=70;
  gm_u8 dongheight;//=60;
  gm_u8 level;//游戏难度
  gm_s16 chixushijian;//每只地鼠的出现的持续时间
  gm_s16 chixutime[9];//
  gm_s16 jizhongtime[9];
  
  gm_bool wanchang;//是否打完一关
  gm_s16 jiangeshijian;//每只地鼠出现的间隔时间
  gm_s8 percent;//过关需要的百分比
  gm_bool gamepause;//游戏是否暂停
  gm_bool keyixiayiguan;//一关过后是否可以按确定键下一关
 
  gm_s16 totalshunum;//
  gm_s16 mustshunum;//
  gm_s16 dazhongdishunum;//已经打中的地鼠的个数
  gm_s16 chuxiandishunum;//已经出现的地鼠个数；
  gm_bool bigorsmall[9];//出现的是棕鼠，还是白鼠
  gm_u8 zhuangtai[9];//判断每个洞的状态，0 空的洞，1 棕鼠刚露出头，2 棕鼠傻笑，3 棕鼠头刚缩回去，4 棕鼠被打的惨样
                           //5 白鼠刚露出头，6 白鼠天真可爱的笑脸，7 白鼠头刚缩回去，8 白鼠被打时的哭样,只有在状态2和6时打才算打中；
  gm_s16 dong;
  gm_s8 chuizi[9];//判断每个洞上是否有锤子， 0表示没锤子， 1表示正常的锤子，2表示砸中地鼠时的锤子（有砸中效果）
  gm_s16 screenwidth;
  gm_s16 screenheight;
  //private String[] helpstring;
  gm_bool keyida;
  //private int helppage=1;
  gm_bool keyifanhui;//=false;
  gm_bool pojilu;//=false;

}HitMoleplay;
extern void initHitMoleplay(HitMoleplay * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repaintMax);
void HitMole_Play_Windows_Render(void *param);
void HitMole_Play_Windows_Update(void * param);
#endif

