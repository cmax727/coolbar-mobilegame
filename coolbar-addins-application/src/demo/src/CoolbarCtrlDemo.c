/*******************************************************************
  Copyright: Copyright (c) 2009 Coolbar, Inc. All Rights Reserved.
  
  FileName:CoolbarDemo.c
  
  Data:2009-5-13
  
  Auther:
  
  Description:酷吧的动态加载演示版本
   
***********************************************************************/
#include "vmDlSdk.h"
#include "CoolbarCtrlDemo.h"
#include "cbDemoRes_Resource_data.h"

#define EDITOR_MAX_INPUT 20

#ifdef CB_NEWEDITOR_EN

    VMWCHAR w_EditorOneBuf[EDITOR_MAX_INPUT*2+2]={0};
    VMCHAR  c_EditorOneBuf[EDITOR_MAX_INPUT*2+2] = {0};
    VmRectType editor_rect = {2, VM_MAINSCREEN_HEIGHT / 5, VM_MAINSCREEN_WIDTH - 4, VM_MAINSCREEN_HEIGHT / 5 +22 *3 /2};
    void Cbdemo_Single_Edit_Box_Entry(void);
    static void Cbdemo_Single_Edit_Box_show(void); 
    void Cbdemo_Full_Edit_Box_Entry(void);

#else
    static cbar_editor_t*  cbDemoEditBox_p = PNULL;
#endif // CB_NEWEDITOR_EN

static AppDemoResIDContextStruct  cbDemoImageCt ={0};
static CoolbarListBox* cbDemoMainList_p = PNULL;

static CB_PopBox *  cbDemoPopBox = PNULL;

static VmRectType rightSoftkeyRect = {COOLBAR_RIGHT_SOFTKEY_LEFT, COOLBAR_RIGHT_SOFTKEY_TOP, COOLBAR_RIGHT_SOFTKEY_RIGHT, COOLBAR_RIGHT_SOFTKEY_BOTTOM};

static void cbDemo_ScrInit(void);
static void cbDemoMainList(void);

static void cbDemoSingleEditBoxInit(void);
static void cbDemoOpenSingleEditBox(void);

static void cbDemoAlertPopInit(VMSTR msgText, VMSTR msgText2,  VmImageType  *imageIcon);

static void cbDemoFullScreenEditBoxInit(void);

static void cbDemoStartTimer(void);

static void cbDemoEditBoxBgScreenInit(void * myselfParam);

static VMBOOLEAN cbDemoEditBoxBgScreenLogic(void * myselfParam,VMUINT32 Msg_id,void * Param);
static void cbDemoEditBoxBgScreenRender(void * myselfParam);


static void cbDemoTimerDemoScreenInit(void * myselfParam);
static VMBOOLEAN cbDemoTimerDemoScreenLogic(void * myselfParam,VMUINT32 Msg_id,void * Param);
static void cbDemoTimerDemoScreenRender(void * myselfParam);
static void cbDemoTimerDemoScreenDestory(void * myselfParam);




static VmScreen cbDemoEditBoxBgScreen;/* =
{
    cbDemoEditBoxBgScreenInit,
    PNULL,
    cbDemoEditBoxBgScreenLogic,
    cbDemoEditBoxBgScreenRender,
    PNULL,
    PNULL, 
    PNULL
};*/

static VmScreen cbDemoTimerScreen;/*=
{
    cbDemoTimerDemoScreenInit,
    cbDemoTimerDemoScreenDestory,
    cbDemoTimerDemoScreenLogic,
    cbDemoTimerDemoScreenRender,
    PNULL,
    PNULL, 
    PNULL
};*/

/*File读写创建*/
static void cb_FileDemoScrInit(void *myself);
static void cb_FileDemoScrDestory(void *myself);
static VMUINT8 cb_FileDemoScrLogic(void *myself, VMUINT32 msgId, void *param);
static void cb_FileDemoScrRender(void *myself);
static VmScreen
cb_FileDemoScr;/* = 
{
	cb_FileDemoScrInit,
	cb_FileDemoScrDestory,
	cb_FileDemoScrLogic,
	cb_FileDemoScrRender,
	PNULL,
	PNULL,
	PNULL,
};*/
static void cb_HttpImageDisplayScrInit(void *myself);
static void cb_HttpImageDisplayScrDestory(void *myself);
static VMUINT8 cb_HttpImageDisplayScrLogic(void *myself, VMUINT32 msgId, void *param);
static void cb_HttpImageDisplayScrRender(void *myself);
static VmScreen
cb_HttpImageDisplayScr ;/*= 
{
	cb_HttpImageDisplayScrInit,
		cb_HttpImageDisplayScrDestory,
		cb_HttpImageDisplayScrLogic,
		cb_HttpImageDisplayScrRender,
		PNULL,
		PNULL,
		PNULL,
};*/


/**
  *创建资源中的图片
  */
static void cbDemo_CreateImage(void)
{
   tResource res;	
	//对应资源包的加载，酷吧的设计一共有两块，一块是公用资源的加载 ；二为每个应用或者游戏自身资源的加载

   #if defined(BILLING_USER_NEW) && !defined(COOLBAR_OLDH_PATCH)
	  extVmLcdManager->IMG_InitInnerDataPage();
    #endif
 
	//初始化酷吧内置资源，资源是公用的。
#ifndef USE_MMC_RES_CBDEMORES
	extVmLcdManager->IMG_InitDataPage(CbDemoRes_TResource_Data, 0);//每个游戏或者应用所对应的自身的资源包（模拟器）第二个参数 0表示从头文件读取
#else
	extVmLcdManager->IMG_InitDataPage(res, 1);//每个游戏或者应用所对应的自身的资源包（手机CBE) 第二个参数 1 表示T卡中加载的
#endif

     
	// 下面是创建应用或者游戏所应用的图片资源（公用和自带资源），通过Id建立相对应的图片
	extVmLcdManager->VMCreateImage(CBDEMORES_IMAGE_SOFTKEY_BG_GIF,&cbDemoImageCt.softKeyBar);

	extVmLcdManager->VMCreateImage(CBDEMORES_IMAGE_TITLE_BAR_GIF,&cbDemoImageCt.titleBar);	
	//for pop
	extVmLcdManager->VMCreateImage(CBDEMORES_IMAGE_POP_BG_GIF,&cbDemoImageCt.popBgImage);
	extVmLcdManager->VMCreateImage(CBDEMORES_IMAGE_PROMPT_ICON_ALERT_GIF,&cbDemoImageCt.popAlertIcon);
	extVmLcdManager->VMCreateImage(CBDEMORES_IMAGE_PROMPT_ICON_QUERY_GIF,&cbDemoImageCt.popQueryIcon);
	extVmLcdManager->VMCreateImage(CBDEMORES_IMAGE_PROMPT_ICON_SUCCESS_GIF,&cbDemoImageCt.popSuccIcon);
	extVmLcdManager->VMCreateImage(CBDEMORES_IMAGE_PROMPT_ICON_WRONG_GIF,&cbDemoImageCt.popFailIocn);	
	//for list
	extVmLcdManager->VMCreateImage(CBDEMORES_LISTICON_GIF,&cbDemoImageCt.listIconImage);
	extVmLcdManager->VMCreateImage(CBDEMORES_LIST_ICON_UNMBER_GIF,&cbDemoImageCt.listNumImage); 
}



/**
  *释放创建的图片的资源
  */
static void cbDemo_DestoryImage(void)
{
	//销毁所用创建的图片，主要是图片对应的空间的释放
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.softKeyBar);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.titleBar);
    
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.popBgImage);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.popAlertIcon);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.popQueryIcon);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.popSuccIcon);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.popFailIocn);
    
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.listIconImage);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.listNumImage);

	//释放出示包空间相关的空间 与 extVmLcdManager->IMG_InitInnerDataPage 和extVmLcdManager->IMG_InitDataPage 对应
    extVmLcdManager->IMG_ReleaseDataPage();
}


static VMBOOLEAN cb_HttpGetReqDemo(void);
/*********************************************************************************************************
*                 -- List init and dispose Demo 
*
*
*
**********************************************************************************************************/
//List 控件的回调函数
static void cbDemoMainListCallBack(CoolbarListBox * myself, gm_u16 result)
{
	VMUINT16  index = cbDemoMainList_p->GethighlightIndex(cbDemoMainList_p); //得到LIST当前的高亮项
	switch(result)
	{
	case COOLBAR_LIST_RESULT_SELCET:   // List中有选中功能时。（比较特殊的LIST) 确认
	case COOLBAR_LIST_RESULT_OK:	   // 左键 	
	case COOLBAR_LIST_RESULT_MID:	   //中间键
		{				
			switch(index)
			{
			case 0:
				    cbDemoOpenSingleEditBox();            //Signle Edit Demo
				break;
			case 1:
				cbDemoFullScreenEditBoxInit();         // Edit Demo
				break;
			case 2:
				cbDemoAlertPopInit("欢迎PopBox", PNULL, &cbDemoImageCt.popSuccIcon); // Pop box Demo
				break;				
			case 3:
				extVmScreenManager->vmAddScreen(&cbDemoTimerScreen);   // Timer Demo
				break;
			case 4:  //文件和文件夹的读写创建
				extVmScreenManager->vmAddScreen(&cb_FileDemoScr);      // File Demo
				break;
			case 5:
				{
				    vm_log_debug("[demo] logic cb_HttpGetReqDemo ");
				    cb_HttpGetReqDemo();                                   // Http Demo
				}
			break;			
			default:				
				break;
			}			
		}
		break;
		
	case COOLBAR_LIST_RESULT_RETURN:  //退出List控件
		if(cbDemoMainList_p !=PNULL)
		{
			cbDemoMainList_p->Release(&cbDemoMainList_p); //关闭list
			extVmSysManager->VmEnterWinClose();//推出整个应用
		}
#if 0 
		if(myself != PNULL)  //对应LIST控件释放也可以这样写  和通过全部变量处理效果一样
		{
			myself->Release(myself->myself_p);	//释放的参数myself->myself_p 一定要这样写		
		}	
#endif
		break;			
	case COOLBAR_LIST_RESULT_NOSELECT: //List中有选中功能时。（比较特殊的LIST) 未选中		
		break;	
	default:
		break;
	}
}

// list 控件的初始化函数
static void cbDemoMainList(void)
{
    VMUINT16 item_pos = 0;
    Rect rect;  //list 控件的显示的区域坐标
    rect.x = 0;
    rect.y = extVmLcdManager->VMGetImageHeight(&cbDemoImageCt.titleBar);
    rect.w = VM_MAINSCREEN_WIDTH;
    rect.h = VM_MAINSCREEN_HEIGHT - extVmLcdManager->VMGetImageHeight(&cbDemoImageCt.titleBar) - extVmLcdManager->VMGetImageHeight(&cbDemoImageCt.softKeyBar);
   // list 控件的基础初始化函数
    extVmCtrlManager->InitCoolbarListBoxEx(&cbDemoMainList_p, 10, rect, COOLBAR_LIST_OPTION_STYLE_HAS_ICON, TRUE, cbDemoMainListCallBack);

    //设置list左边icon的图片
    cbDemoMainList_p->AddOptionImageList(cbDemoMainList_p,&cbDemoImageCt.listIconImage);
    cbDemoMainList_p->AddExtOptionImageList(cbDemoMainList_p, &cbDemoImageCt.listNumImage);	

    //设置字体颜色第二个参数为字体颜色，第三个参数是选中时的字体颜色
    cbDemoMainList_p->SetFontColor(cbDemoMainList_p,  Vm_WHITE_COLOR,  Vm_WHITE_COLOR);
    //设置背景色第二个参数为背景颜色，第三个参数是选中时的背景色
    cbDemoMainList_p->SetBackColor(cbDemoMainList_p, Vm_BLACK_COLOR,  Vm_BLUE_COLOR);	
    //设置title
    cbDemoMainList_p->AddTitleBar(cbDemoMainList_p, &cbDemoImageCt.titleBar, "Coolbar Demo");
    //设置软键栏 显示的文字
    cbDemoMainList_p->AddSoftkeyBar(cbDemoMainList_p, &cbDemoImageCt.softKeyBar, "确定", PNULL, "返回");
    //设置list各项的内容
    cbDemoMainList_p->AddOption(cbDemoMainList_p, "SingleEditBoxDemo", COOLBAR_LIST_NUMBER_ICON_INDEX);
    cbDemoMainList_p->AddOption(cbDemoMainList_p, "FullScreenEditBoxDemo", COOLBAR_LIST_NUMBER_ICON_INDEX);
    cbDemoMainList_p->AddOption(cbDemoMainList_p, "PopBoxDemo", COOLBAR_LIST_NUMBER_ICON_INDEX);
    cbDemoMainList_p->AddOption(cbDemoMainList_p, "TimerDemo", COOLBAR_LIST_NUMBER_ICON_INDEX);
    cbDemoMainList_p->AddOption(cbDemoMainList_p, "File Demo", COOLBAR_LIST_NUMBER_ICON_INDEX);
	cbDemoMainList_p->AddOption(cbDemoMainList_p, "HTTP Demo", COOLBAR_LIST_NUMBER_ICON_INDEX);

	cbDemoMainList_p->AddOption(cbDemoMainList_p, "Hello MTK", COOLBAR_LIST_NUMBER_ICON_INDEX);
    // 有选中功能的List,设置已经选中初始项 
    cbDemoMainList_p->SetSelectIndex(cbDemoMainList_p, 0, TRUE);
	//设置list刚开始的高亮项
    cbDemoMainList_p->SethighlightIndex(cbDemoMainList_p, 0);
}


static void cbDemoOpenSingleEditBox(void)
{
    extVmScreenManager->vmAddScreen(&cbDemoEditBoxBgScreen);// 单行编辑框所对应的SCREEN加入Screen 数组
}

static void cbDemoEditBoxBgScreenInit(void * myselfParam)
{
	cbDemoSingleEditBoxInit(); //编辑框的
}

static VMBOOLEAN cbDemoEditBoxBgScreenLogic(void * myselfParam,VMUINT32 Msg_id,void * Param)
{
#ifndef CB_NEWEDITOR_EN
	return TRUE;
#else
	VMUINT8 returnVal = 1;
 	VMUINT32 key = 0;
 	switch(Msg_id)
 	{
 	case GAME_MSG_KEYDOWN:
 		{
 		    key =*(VMUINT32*)Param;
 		    switch(key)
 		   {
 		   case MF_KEY_LEFTSOFT:
 		   case MF_KEY_0:
                 case MF_KEY_1:
                 case MF_KEY_2:
                 case MF_KEY_3:
                 case MF_KEY_4:
                 case MF_KEY_5:
                 case MF_KEY_6:
                 case MF_KEY_7:
                 case MF_KEY_8:
                 case MF_KEY_9:
                 case MF_KEY_MID:
                      Cbdemo_Single_Edit_Box_Entry();
                      break;
                      
                 case MF_KEY_RIGHTSOFT:
                      extVmScreenManager->vmDeleteScreen(&cbDemoEditBoxBgScreen);
                      break;
            }
        }
        break;
   case GAME_MSG_TP_PRESS_DOWN:
 		{
 			   VmPointType point = {0};
 			   point.x = (VMUINT16)(*(VMUINT32 *)Param)&0xffff;
 			   point.y = (VMUINT16)((*(VMUINT32 *)Param)>>16)&0xffff;					
                        if(extVmLcdManager->VMWinPointIsInRect(point, rightSoftkeyRect))
			   {
			       key=MF_KEY_RIGHTSOFT;
			       cbDemoEditBoxBgScreenLogic(PNULL,GAME_MSG_KEYDOWN,&key);
			       break;
			    }
			    
			    else if(extVmLcdManager->VMWinPointIsInRect(point, editor_rect))
			   {
                           Cbdemo_Single_Edit_Box_Entry();
                           break;
			    }
			}
			break;
		default:
		    break;
    }
	return TRUE;

#endif
}
static void cbDemoEditBoxBgScreenRender(void * myselfParam)
{
	VmRectType rect = {0, 0, VM_MAINSCREEN_WIDTH - 1, VM_MAINSCREEN_HEIGHT - 1};// 区域坐标

	extVmLcdManager->VMFillRect(rect, Vm_BLACK_COLOR);//画背景色
	
	//draw title start
	extVmCtrlManager->VmPubDrawWinTitle(&cbDemoImageCt.titleBar, "Single EditBox Demo");
	//draw title end
	extVmLcdManager->VMDrawString("请输入:", 2, VM_MAINSCREEN_HEIGHT /5 - extVmLcdManager->VMGetFontHeight(TRUE) *3 /2, Vm_YELLOW_COLOR);

	#ifdef CB_NEWEDITOR_EN
        Cbdemo_Single_Edit_Box_show();

       //软键盘
	extVmCtrlManager->VmPubDrawSoftkeyBar(&cbDemoImageCt.softKeyBar,PNULL,PNULL,extVmLcdManager->VmResGetDefTxt(VM_IM_TXT_RETURN));		
	
    #endif//CB_NEWEDITOR_EN

}

#ifndef CB_NEWEDITOR_EN
// 编辑框的回调函数
static void cbDemoEditBoxCallbackFunc(cbar_editor_t *myself, cbar_editor_result_t result_id)
{
	VMCHAR  strBuf[20 + 2] = {0};
	cbar_editor_data_gb_t dataBuf = {0};
	
	dataBuf.gb_str_ptr = strBuf;
	//得到编辑框中的内容，编码为GB 
	myself->get_edit_str_gb(myself, &dataBuf, 20);
	dataBuf.gb_str_len = strlen((char*)dataBuf.gb_str_ptr); //输入长度
	
	switch(result_id)
	{
	case    CBAR_EDITOR_RESULT_OK:
		{
			if(dataBuf.gb_str_len == 0)//输入为空
			{
				cbDemoAlertPopInit("请输入信息", PNULL, &cbDemoImageCt.popAlertIcon);
				break;
			}
		}
		
	case CBAR_EDITOR_RESULT_CANCEL:
		if(PNULL != cbDemoEditBox_p)//退出编辑框界面
		{
			cbDemoEditBox_p->destory(&cbDemoEditBox_p);
			cbDemoEditBox_p = PNULL;
			extVmScreenManager->vmDeleteScreen(&cbDemoEditBoxBgScreen);
		}
		break;
	default:		
		break;
	}
}
#endif

static void cbDemoSingleEditBoxInit(void)
{
#ifndef  CB_NEWEDITOR_EN
	//编辑框所对应的输入区域的坐标
	VmRectType rect = {2, VM_MAINSCREEN_HEIGHT / 5, VM_MAINSCREEN_WIDTH - 4, VM_MAINSCREEN_HEIGHT / 5 + 22 *3 /2};

	cbar_editor_param_t param = {0};
    //编辑框的有效的输入法（可选）
	param.allow_im_type = CBAR_IM_TYPE_DIGIT |CBAR_IM_TYPE_PINYIN |CBAR_IM_TYPE_UPPER_CHAR |CBAR_IM_TYPE_LOWER_CHAR|CBAR_IM_TYPE_STROKE;
	param.first_im_mode = CBAR_IM_MODE_DIGIT;     //默认的输入法
	param.max_char_num = 20;                      //允许的输入的最大值
	param.gb_str_ptr = PNULL;                     //初始的字符数据
	//编辑框基本初始化函数
	extVmCtrlManager->cbar_create_single_txt_editor(&cbDemoEditBox_p, &param, rect, cbDemoEditBoxCallbackFunc);

	//编辑框中按键的内容和相关的背景图片
	cbDemoEditBox_p->add_softkey_bar(cbDemoEditBox_p, 
												&cbDemoImageCt.softKeyBar,
												"确定",
												"确定",
												PNULL,
												"返回",
												"删除"
												);
	//标题相关的属性
	cbDemoEditBox_p->add_title_bar(cbDemoEditBox_p, &cbDemoImageCt.titleBar, "EditBox Demo");
	//编辑框的光标的有效性，主要为多个编辑框，来回切换时
	cbDemoEditBox_p->set_active(cbDemoEditBox_p, TRUE);
#else
     vm_memset((VMSTR)c_EditorOneBuf,0,sizeof(c_EditorOneBuf));
#endif

}

static void cbDemoFullScreenEditBoxInit(void)
{
#ifndef  CB_NEWEDITOR_EN
	cbar_editor_param_t param = {0};
    //编辑框的有效的输入法（可选），默认输入法，最大长度，初始值
	param.allow_im_type = CBAR_IM_TYPE_DIGIT |CBAR_IM_TYPE_PINYIN |CBAR_IM_TYPE_UPPER_CHAR |CBAR_IM_TYPE_LOWER_CHAR|CBAR_IM_TYPE_STROKE;
	param.first_im_mode = CBAR_IM_MODE_DIGIT;
	param.max_char_num = 20;
	param.gb_str_ptr = PNULL;
	
	extVmCtrlManager->cbar_create_txt_editor(&cbDemoEditBox_p, &param, cbDemoEditBoxCallbackFunc);
    //编辑框中按键的内容和相关的背景图片
	cbDemoEditBox_p->add_softkey_bar(cbDemoEditBox_p, 
												&cbDemoImageCt.softKeyBar,
												"确定",
												"确定",
												PNULL,
												"返回",
												"删除"
												);
	// 标题相关的属性
	cbDemoEditBox_p->add_title_bar(cbDemoEditBox_p, &cbDemoImageCt.titleBar, "EditBox Demo");
	////编辑框的光标的有效性，主要为多个编辑框，来回切换时
	cbDemoEditBox_p->set_active(cbDemoEditBox_p, TRUE);

#else
     vm_memset((VMSTR)c_EditorOneBuf,0,sizeof(c_EditorOneBuf));
     Cbdemo_Full_Edit_Box_Entry();
#endif

}


//pop start
// Pop box 的回调函数
static void cbDemoPopCallBack(CB_PopBox * myself, gm_u16 result)
{
	switch(result)
	{
		case COOLBAR_POP_RESULT_OK:	     // 确认可选POP中，确认的应答
			break;
		case COOLBAR_POP_RESULT_RETURN:  // 返回
		case COOLBAR_POP_RESULT_TIMEOUT: //定时器到时
			if(cbDemoPopBox !=PNULL)
			{
				cbDemoPopBox->Release(&cbDemoPopBox);
				cbDemoPopBox=PNULL;
			}			
			break;		
		
		default:
			break;
	}
	
}
#ifdef COOLBAR_240_320
//pop position start
#define  STOCK_POP_BOX_X 24
#define  STOCK_POP_BOX_Y 110
#define  STOCK_POP_BOX_WIDTH 190
#define  STOCK_POP_BOX_HEIGHT 99
#elif defined COOLBAR_176_220
//pop position start
#define  STOCK_POP_BOX_X 15
#define  STOCK_POP_BOX_Y 70
#define  STOCK_POP_BOX_WIDTH 145
#define  STOCK_POP_BOX_HEIGHT 79
//pop positon end
#elif defined COOLBAR_240_400
//pop position start
#define  STOCK_POP_BOX_X 24
#define  STOCK_POP_BOX_Y 150
#define  STOCK_POP_BOX_WIDTH 190
#define  STOCK_POP_BOX_HEIGHT 99
#elif defined COOLBAR_128_160
//pop position start
#define  STOCK_POP_BOX_X 6
#define  STOCK_POP_BOX_Y 50
#define  STOCK_POP_BOX_WIDTH 116
#define  STOCK_POP_BOX_HEIGHT 58
//pop positon end
#endif
static void cbDemoAlertPopInit(VMSTR msgText, VMSTR msgText2,  VmImageType  *imageIcon)
{
	PopBoxParam params={0};	
	Rect rect;    

	// POP的坐标，一般还是用默认值比较好
	rect.x = STOCK_POP_BOX_X;
	rect.y = STOCK_POP_BOX_Y;
	rect.w = STOCK_POP_BOX_WIDTH;
	rect.h = STOCK_POP_BOX_HEIGHT;  
	
	params.poprect = rect;
	params.msgText = msgText; //显示的内容
	params.msgText2= msgText2;
	params.rightText = "关闭";//右键内容
	params.background=&cbDemoImageCt.popBgImage; // 背景图片， 背景图片为空，就会用默认的背景色填充显示的区域
	params.imageIcon=imageIcon;                  //显示的的小ICON的图片
	params.timer = 2000;                            //定时器的值
	params.imageSoftBar =&cbDemoImageCt.softKeyBar; // 左右软键的背景图片
	params.softTextColor = Vm_BLACK_COLOR;          //软键的文字

	if(cbDemoPopBox !=PNULL)//预处理
	{
		cbDemoPopBox->Release(&cbDemoPopBox);
		cbDemoPopBox = PNULL;
	}
	extVmCtrlManager->CbPopBox_InitEx(&cbDemoPopBox, &params, cbDemoPopCallBack);  

}



//timer Demo start
static VMCHAR g_timer_demo_buf[] = "欢迎使用coolbar 平台开发产品";
static VMUINT16 cur_draw_offset = 0;
static VMUINT16 cbDemoTimerId = VM_RETUREN_ERR_TIMEID;

static void cbDemoHandleTimer(void *args)
{
    if(cur_draw_offset < strlen((char*)g_timer_demo_buf) - 5)
    {
        if((VMUINT8)g_timer_demo_buf[cur_draw_offset] >= 0x80)
        {
            cur_draw_offset += 2;
        }
        else
        {
            cur_draw_offset++;
        }
    }
    else
    {
        cur_draw_offset = 0;
    }

    //重新启动timer
    cbDemoTimerId = VM_RETUREN_ERR_TIMEID;
    cbDemoStartTimer();
}
static void cbDemoStartTimer(void)
{
	if(VM_RETUREN_ERR_TIMEID == cbDemoTimerId)
	{
		cbDemoTimerId = extVmTimeManager->VMStartTimer(1000, cbDemoHandleTimer, PNULL);
	}
}
static void cbDemoStopTimer(void)
{
    if(VM_RETUREN_ERR_TIMEID != cbDemoTimerId)
    {
        extVmTimeManager->VMStopTimer(cbDemoTimerId);
        cbDemoTimerId = VM_RETUREN_ERR_TIMEID;
    }
    
}
static void cbDemoTimerDemoScreenInit(void * myselfParam)
{
    cur_draw_offset = 0;
    cbDemoStartTimer();
}

static VMBOOLEAN cbDemoTimerDemoScreenLogic(void * myselfParam,VMUINT32 Msg_id,void * param)
{

	VMUINT8  returnVal =TRUE;

	switch(Msg_id)
	{
		case VM_MSG_KEYDOWN://按键消息处理
		{
			gm_u32 key=*(gm_u32*)param;
			switch(key)
			{
				case MF_KEY_MID:
				case MF_KEY_LEFTSOFT:	  	
					break;	

				case MF_KEY_RIGHTSOFT:	  	
					extVmScreenManager->vmDeleteScreen(&cbDemoTimerScreen);
					break;	   
					
				default:
	
					break;
			}
		}
			break;

		case VM_MSG_TP_PRESS_DOWN: //tp消息处理
			{
				VmPointType point = {0};
				gm_u32  keyType = 0;
				point.x = (VMINT16)(*(VMUINT32 *)param)&0xffff;
				point.y = (VMINT16)((*(VMUINT32 *)param)>>16)&0xffff;

				if(extVmLcdManager->VMWinPointIsInRect(point, rightSoftkeyRect))
				{
					keyType = MF_KEY_RIGHTSOFT;
					cbDemoTimerDemoScreenLogic(myselfParam, VM_MSG_KEYDOWN, &keyType);
					break;
				}
				break;
			}
		
		default:
	
			break;
	}	
	return returnVal;

}
static void cbDemoTimerDemoScreenRender(void * myselfParam)
{
    VmRectType rect = {0, 0, VM_MAINSCREEN_WIDTH - 1, VM_MAINSCREEN_HEIGHT - 1};


    //draw background
    extVmLcdManager->VMFillRect(rect, Vm_BLACK_COLOR);

    //draw title 
    extVmCtrlManager->VmPubDrawWinTitle(&cbDemoImageCt.titleBar, "Timer Demo");

    //draw Soft key Bar
    extVmCtrlManager->VmPubDrawSoftkeyBar(&cbDemoImageCt.softKeyBar, "确定", PNULL, "返回");

    //draw text
    extVmLcdManager->VMDrawStringClipAlign((VMSTR)g_timer_demo_buf + cur_draw_offset, VM_MAINSCREEN_WIDTH / 4, VM_MAINSCREEN_HEIGHT /3 , VM_MAINSCREEN_WIDTH / 2, VM_ALIGN_LEFT, Vm_YELLOW_COLOR);
}

static void cbDemoTimerDemoScreenDestory(void * myselfParam)
{
    cur_draw_offset = 0;
    cbDemoStopTimer();
}
/********************************************************************
*Function: 1: File create and write
*          2: File open and read
*******************************************************************/
const VMUINT16 demoDir[]={'d','e','m','o',0};
const VMUINT16 demoFile[] = {'d','e','m','o','F','i','l','e',0};
const VMCHAR  demoStr[] = "coolbar platform demo\n 1: file create and write\n 2: file read open and write";
static VMUINT8   strDemo[150] = {0};
static void cb_FileDemoScrInit(void *myself)
{
    VMUINT16  fileName[FILE_NAME_LENS] = {0};   
    VMUINT16  fileNameLength = 0;
	VMUINT32  writeLen = 0;  
    VMFILE    fileHandler = -1;
	VMUINT16  demoLen = 0;	
	VMUINT32   strLen = 0;
	
    //判断文件所在的文件夹是否存在
	if(!extVmIoManager->Vm_file_direxist(VM_FS_MMC,demoDir))//VM_FS_MMC 可变
	{
		extVmIoManager->Vm_file_mkdir(VM_FS_MMC,demoDir);
	}
	vm_memset(strDemo,0,sizeof(strDemo));
	demoLen = extVmUcs2StrManager->VmutStrlenUcs2((VMUINT16 *)demoDir);
	vm_memset(fileName,0,sizeof(fileName));
	extVmUcs2StrManager->VmutStrcatUcs2(fileName,demoDir);  
    fileName[demoLen] = L'\\';//这个也要注意平台差异，BREW平台笔记特殊 '/'
	demoLen++;
	extVmUcs2StrManager->VmutStrcatUcs2((fileName+demoLen),demoFile);
	if(!extVmIoManager->Vm_file_exist(VM_CURR_DEV,fileName))   
	{
		fileHandler = extVmIoManager->Vm_file_open(VM_FS_MMC,fileName,"w+");//文件保存
		if(fileHandler >= 0)
		{
			strLen  =vm_strlen(demoStr);
			writeLen =  extVmIoManager->Vm_file_write((void*)demoStr,strLen,fileHandler);
			if( strLen == writeLen)// you must judge 
			{
				extVmIoManager->Vm_file_close(fileHandler); //OK
			}
			else
			{
				extVmIoManager->Vm_file_close(fileHandler); // FALSE				
			}			
		}
	}
	else
	{
		fileHandler = extVmIoManager->Vm_file_open(VM_FS_MMC,fileName,"r");//文件读取
		if(fileHandler >= 0)
		{
			strLen  =vm_strlen(demoStr);
			vm_memset(strDemo,0,sizeof(strDemo));
			writeLen = extVmIoManager->Vm_file_read((void*)strDemo,strLen,fileHandler);
			if( strLen == writeLen)// you must judge 
			{
				extVmIoManager->Vm_file_close(fileHandler); //OK
			}
			else
			{
				extVmIoManager->Vm_file_close(fileHandler); // FALSE				
			}		
		}		
	}
	
}
static void 
cb_FileDemoScrDestory(void *myself)
{

}
static VMUINT8 
cb_FileDemoScrLogic(void *myself, VMUINT32 msgId, void *param)
{		
	VMUINT32 key = 0;
	switch(msgId)
	{
	case GAME_MSG_KEYDOWN:
		{
			key =*(VMUINT32*)param;
			switch(key)
			{
			case MF_KEY_RIGHTSOFT:			
				extVmScreenManager->vmDeleteScreen(&cb_FileDemoScr);
				break;
			default:				
				break;
			}
			break;
		}
	case GAME_MSG_TP_PRESS_DOWN:
		{
			VmPointType point = {0};
			point.x = (VMUINT16)(*(VMUINT32 *)param)&0xffff;
			point.y = (VMUINT16)((*(VMUINT32 *)param)>>16)&0xffff;		//TP的坐标	
			if(extVmLcdManager->VMWinPointIsInRect(point, rightSoftkeyRect)) // 判断TP的坐标是否在响应的区域中
			{
				key  = MF_KEY_RIGHTSOFT;
				cb_FileDemoScrLogic(PNULL, VM_MSG_KEYDOWN, &key);					
			}
				break;
		}
		break;
	default:	
		break;
	}

	return TRUE;
}
static void 
cb_FileDemoScrRender(void *myself)
{
	VmRectType rect = {0, 0, VM_MAINSCREEN_WIDTH - 1, VM_MAINSCREEN_HEIGHT - 1};    
	VMUINT8 strLen =  vm_strlen(strDemo);
    extVmLcdManager->VMFillRect(rect, Vm_BLACK_COLOR);    
    extVmCtrlManager->VmPubDrawWinTitle(&cbDemoImageCt.titleBar, "File Demo");//TITLE
	
	if(strLen)
	{
		extVmLcdManager->VMDrawStringRect((VMSTR)strDemo,VM_MAINSCREEN_WIDTH /20,VM_MAINSCREEN_HEIGHT /10,VM_MAINSCREEN_WIDTH*9/10,VM_MAINSCREEN_HEIGHT*9/10,Vm_YELLOW_COLOR);
    }
	else
	{
		extVmLcdManager->VMDrawStringRect((VMSTR)"File is create",VM_MAINSCREEN_WIDTH /20,VM_MAINSCREEN_HEIGHT /10,VM_MAINSCREEN_WIDTH*9/10,VM_MAINSCREEN_HEIGHT*9/10,Vm_YELLOW_COLOR);
	
	}
    extVmCtrlManager->VmPubDrawSoftkeyBar(&cbDemoImageCt.softKeyBar, PNULL, PNULL, "返回"); //SOFTKEY
	
}
/*********************************************************************************************************
*                 --HTTP GET req and dispose
*
*
*
**********************************************************************************************************/
static VMUINT32 httpNetConnectId = 0;           //网络连接的ID需要保留，连接过程中用户主动取消时，根据ID需要网络连接
VMUINT8  * pPicRecDate =  PNULL;                //收到的图片数据
VMUINT32  receivedDataLen = 0;                  //收到的数据长度   
#define   PIC_URL  "http://wallpaper.6636.com/wallpicclient/download.aspx?pictureid=17092&width=240&height=320"   //网络申请的URL
#define   PICVIEW_PIC_DATA_SIZE   60*1024       //数据的最大值，超出的话，改数据直接丢弃。
static VmImageType downloadPic = {0};           //图片下载后，解码后所用。

static void
cb_HttpGetReqCbDemo(VMUINT8 * buffer,VMUINT32 bufLen,VMUINT32 totalLen,NetRequestResultType result)
{
       vm_log_debug("[demo] connect bufLen=%d,totalLen=%d,result=%x",bufLen,totalLen,result);
	if( (result == HTTP_RETRY)||(result == HTTP_CANCEL))         //网络异常
	{
	       vm_log_debug("[demo] connect error 2");
		return;
	}	
	if(totalLen >PICVIEW_PIC_DATA_SIZE)                          //下载的数据超出默认的最大值
	{	
	       vm_log_debug("[demo] connect long");
		extVmNetManager->CancelHttpConnect(httpNetConnectId);    // 取消对应的网络接连
		httpNetConnectId = 0;				                    
		receivedDataLen = 0;
		vm_memset(pPicRecDate,0,PICVIEW_PIC_DATA_SIZE);
		return;
	}	
	if(result == NETREQUEST_ERROR)                                // 网络申请直接失败
	{
	       vm_log_debug("[demo] connect error 3 ");
		httpNetConnectId = 0;	
		receivedDataLen = 0;		
		vm_memset(pPicRecDate,0,PICVIEW_PIC_DATA_SIZE);
		return;
	}
	vm_memcpy((pPicRecDate + receivedDataLen),buffer,bufLen);             //保存收到的网络数据 对于图片信息而言,与发送彩信相似，包发送
	receivedDataLen += bufLen;                                            //数据处理
	if((HTTP_ALL_RECEIVED == result)&&(receivedDataLen == totalLen))      //网络请求的数据已经全部接受完
	{
	       vm_log_debug("[demo] connect all receive");
		httpNetConnectId = 0;	
		extVmScreenManager->vmAddScreen(&cb_HttpImageDisplayScr);
    }		
	
}

static VMBOOLEAN
cb_HttpGetReqDemo(void)
{
	VMBOOLEAN returnVal =  FALSE;
	VMUINT8 updateUrl[NETWORKAPP_URL_LENGTH] = {0};
	NetCallBackType    pFun = PNULL;
	vm_log_debug("[demo] cb_HttpGetReqDemo ");
	vm_memset(updateUrl,0,sizeof(updateUrl));
	pFun = cb_HttpGetReqCbDemo;    	               //网络申请的回调函数
	if(httpNetConnectId != 0)                    
	{
		extVmNetManager->CancelHttpConnect(httpNetConnectId);		
	}
	httpNetConnectId = 0;
	if(PNULL == pPicRecDate)
	{
		pPicRecDate = extVmMemoryManager->mF_MallocGmemoryBlock(PICVIEW_PIC_DATA_SIZE);   // 申请保存下载的数据的空间
	}

	vm_memset(pPicRecDate,0,PICVIEW_PIC_DATA_SIZE);
    receivedDataLen = 0;

	sprintf((VMCHAR*)updateUrl,PIC_URL);           // 网络申请的URL
	returnVal = extVmNetManager->GetHttpData((char*)updateUrl,pFun,&httpNetConnectId); // 建立网络的请求(get type)
    //extVmNetManager->PostHttpData();  HTTP POST 接口 ; post 与 get 方式处理差不多 
	if(returnVal == FALSE)                         //网络请求直接失败，需要注意
	{
	       vm_log_debug("[demo] connect error");
		httpNetConnectId = 0;
	}
				
}


static void cb_HttpImageDisplayScrInit(void *myself)
{
	downloadPic.height = VM_MAINSCREEN_HEIGHT;
	downloadPic.width =  VM_MAINSCREEN_WIDTH;
	downloadPic.imageType = BMP_IMAGE_TYPE;
	//第二种内存申请方式，建议用这种内存申请方式。没有什么限制。主要为申请和释放的顺序，以便减少内存碎片。
	downloadPic.data = (VMUINT16 *)extVmMemoryManager->mallocBigMen(VM_MAINSCREEN_HEIGHT*VM_MAINSCREEN_WIDTH*2+2000);
	if(PNULL != downloadPic.data)
	{
		vm_memset(downloadPic.data,0,VM_MAINSCREEN_HEIGHT*VM_MAINSCREEN_WIDTH*2+2000);
		extVmLcdManager->VMDrawStandardImageEx(&downloadPic,
			0,
			0,
			0,
			VM_MAINSCREEN_WIDTH,
			VM_MAINSCREEN_HEIGHT,
			pPicRecDate,
			receivedDataLen,
			STAND_JPG);                     //根据下载的图片数据，创建对应的图片
	}
}
static void cb_HttpImageDisplayScrDestory(void *myself)
{
	if(PNULL != downloadPic.data)              //释放空间
	{
		extVmMemoryManager->freeBigMen((void*)downloadPic.data);
		downloadPic.data = PNULL;
	}	
}
static VMUINT8 cb_HttpImageDisplayScrLogic(void *myself, VMUINT32 msgId, void *param)
{
	VMUINT32 key = 0;
	switch(msgId)
	{
	case GAME_MSG_KEYDOWN:                   //按键消息的处理
		{
			key =*(VMUINT32*)param;          //按键的键值
			switch(key)// 
			{
			case MF_KEY_RIGHTSOFT:			// 右键 其他相关按键的处理，只需添加相应的CASE
				extVmScreenManager->vmDeleteScreen(&cb_HttpImageDisplayScr);
				break;
			default:				
				break;
			}
			break;
		}
	case GAME_MSG_TP_PRESS_DOWN:  //TP消息的处理
		{
			VmPointType point = {0};
			point.x = (VMUINT16)(*(VMUINT32 *)param)&0xffff;
			point.y = (VMUINT16)((*(VMUINT32 *)param)>>16)&0xffff;			
			if(extVmLcdManager->VMWinPointIsInRect(point, rightSoftkeyRect))
			{
				key  = MF_KEY_RIGHTSOFT;
				cb_HttpImageDisplayScrLogic(PNULL, VM_MSG_KEYDOWN, &key);					
			}
			break;
		}
		break;
	default:	
		break;
	}
	
	return TRUE;
	
}

static void cb_HttpImageDisplayScrRender(void *myself)
{
    if(PNULL != downloadPic.data)
	{
		extVmLcdManager->VMDrawImageEx(&downloadPic,0,0);
	}
	else
	{
		extVmLcdManager->VMDrawStandardImage(0,0,0,VM_MAINSCREEN_WIDTH,VM_MAINSCREEN_HEIGHT, pPicRecDate,receivedDataLen,STAND_JPG);
	}
	extVmCtrlManager->VmPubDrawSoftkeyBar(&cbDemoImageCt.softKeyBar, PNULL, PNULL, "返回"); //SOFTKEY
}
/*********************************************************************************************************
*
*     -- coolbar Demo 的入口和退出主函数
*                    
*
**********************************************************************************************************/
void cb_Gb2Ucs2Demo(void);
void CoolBarDemo_Enter(void)
{
	//加载资源时，需要的内存，一般比资源的bin文件大20K左右比较合适
	#ifdef COOLBAR_OLDH_PATCH
	extVmMemoryManager->dF_InitMemory(300*1024);
	//在V3版本里，相关代码是放在资源里的，故该函数初始化必须放在资源初始化之前,df_InitMemory之后!!!!!!
	initMemoryBlock(getMemoryBlockPtr(),1024*5);//由于有2个datapackage，故必须初始化（V3内核有bug），如果需要改变大小，请调整或释放重新初始化
	dlpatchManagerPtr->initDreamFactoryEngine();
       IMG_InitDataPageWithCode(CbDemoRes_TResource_Data,1);
	#else
	extVmMemoryManager->dF_InitMemory(60*1024);
	#endif

       vm_log_debug("CoolBarDemo_Enter");
	cbDemo_ScrInit();

#ifndef COOLBAR_MTK6225_PLATFORM
	gddiInitGifCodec();
#ifndef COOLBAR_OLDH_PATCH
	gddiInitJpgCodec();
#endif
#endif
	
    //创建图片资源
    cbDemo_CreateImage();


	
    cbDemoMainList();

    //内存申请的第一种方式，对于每个应用或者游戏.gmemory只能同时存在一个。只能整体申请和释放。
    //对于已经申请的内存块，可以重新进行分块申请使用。对于每个分块只能进行赋值操作。   尽量少用
	extVmMemoryManager->mF_InitGmemoryBlock(PICVIEW_PIC_DATA_SIZE +1000);     //保存网络下载的图片资源
	extVmMemoryManager->mF_resetGmemoryBlock();    //此函数使用后，所有的分块都已经无效，分块指针都必须PNULL	
	cb_Gb2Ucs2Demo();  //just for demo
}


void CoolBarDemo_Exit(void)
{
	if(httpNetConnectId != 0)                                //在网络链接的过程中，此时按挂机键时
	{
      extVmNetManager->CancelHttpConnect(httpNetConnectId);  // 取消已经建立的网络连接
	  httpNetConnectId = 0;                                  
	}
    //释放图片资源占用的资源
    cbDemo_DestoryImage();                                   // 与 cbDemo_CreateImage()  对应

    //释放分配的内存
    extVmMemoryManager->dF_ReleaseMemory();                  // 与 extVmMemoryManager->dF_InitMemory()        对应
	extVmMemoryManager->mF_ReleaseGmemoryBlock();            // 与 extVmMemoryManager->mF_InitGmemoryBlock()  对应
}
/*********************************************************************************************************
*
*                        CBE的主入口和离开函数
*1: 对于Enter和EXIT函数的函数名，应用必须相同唯一。动态加载的时候，是以函数指针的形式初始化                 
*
**********************************************************************************************************/
#ifndef WIN32
VmMainFunction vMGetMainEnterFuct(void)   //函数名（函数指针）固定唯一，不可改变。
{
    return CoolBarDemo_Enter;              //实际的入口函数
}

VmMainFunction vMGetMainExitFuct(void)    //同上
{
    return CoolBarDemo_Exit;               //实际的退出函数
}
#endif
/*********************************************************************************************************
*
*          -- coolbar GB->UCS2 and  UCS2->GB DEMO
*1: 接口封装后，由于平台的差异，转化后是否添加0，对于空间最好预留2个字节的空间
*
**********************************************************************************************************/
#define MAX_LEN 10 
void
cb_Gb2Ucs2Demo(void)
{	
	VMSTR pGbStr = "字符编码转化";
	VMUINT16 ucs2Str[MAX_LEN+1] = {0} ;
	VMCHAR   gbStr[2*(MAX_LEN+1)] = {0};		
	extVmLcdManager->VMGB2UCS2(pGbStr,ucs2Str,MAX_LEN);                  //多保留两个字节的空间，主要是平台的差异，对于GB->UCS2，
	                                                                     //转化后，是否添加0的处理。
	extVmLcdManager->VMUCS2GB((VMWSTR)ucs2Str,(VMSTR)gbStr,MAX_LEN*2);   //同上
}

/*********************************************************************************************************
*
*              -- coolbar audio play demo  (音频播放)
* 1: 对于音频播放接口，我们目前只支持MTK和展讯W平台;
* 2: BREW平台和展讯其他平台播放效果很差，不提供接口功能
**********************************************************************************************************/
#ifndef COOLBAR_OLDH_PATCH
VMUINT8 audioData[] = {1,2,3,1,2,3,1,3,1,2,3,1};//音频资源 
void 
cb_AudioPlayDemo(void)
{
	extVmAudioManager->vMAudioSetVolume(0,1);            //volume的范围为0，1，2，3，4，5，6 ，
	                                                     //immediate 的值为1;改动立即生效;0:下次播放生效
    extVmAudioManager->vMAudioPlayByData(audioData,0);   //pData 播放的资源
                                                         //repeats 播放的次数 0 循环播放，N 播放N次
    extVmAudioManager->vMAudioPlayForGame(30,0);         //res 的音频资源和图片一起打包，资源从T卡加载 游戏专用
    extVmAudioManager->vMAudioPlayForApp(30,0);          //res 的音频资源和图片一起打包，资源从T卡加载 应用专用
}           
#endif
/*********************************************************************************************************
*
**********************************************************************************************************/ 
static void cbDemo_ScrInit(void)
{
       vmScreenInit(&cbDemoEditBoxBgScreen,
	cbDemoEditBoxBgScreenInit,
	PNULL,
	cbDemoEditBoxBgScreenLogic,
	cbDemoEditBoxBgScreenRender,
	PNULL,
	PNULL,
	PNULL	
	);


	vmScreenInit(&cbDemoTimerScreen,
	cbDemoTimerDemoScreenInit,
	cbDemoTimerDemoScreenDestory,
	cbDemoTimerDemoScreenLogic,
	cbDemoTimerDemoScreenRender,
	PNULL,
	PNULL,
	PNULL	
	);

	vmScreenInit(&cb_FileDemoScr,
	cb_FileDemoScrInit,
	cb_FileDemoScrDestory,
	cb_FileDemoScrLogic,
	cb_FileDemoScrRender,
	PNULL,
	PNULL,
	PNULL	
	);
   

	vmScreenInit(&cb_HttpImageDisplayScr,
	cb_HttpImageDisplayScrInit,
	cb_HttpImageDisplayScrDestory,
	cb_HttpImageDisplayScrLogic,
	cb_HttpImageDisplayScrRender,
	PNULL,
	PNULL,
	PNULL	
	);

}

#ifdef CB_NEWEDITOR_EN
// 编辑框的回调函数
static void cbDemoEditBoxCallbackFunc2(CBInputResult result, VMWCHAR *wsbuf)
{

    switch (result)
    {
    case CBINPUT_OK: // get user input
    	{
            vm_memset(c_EditorOneBuf,0,sizeof(c_EditorOneBuf));
            extVmLcdManager->VMUCS2GB(w_EditorOneBuf,c_EditorOneBuf,sizeof(c_EditorOneBuf));
	     if(vm_strlen(c_EditorOneBuf) == 0)//输入为空
	     {
			cbDemoAlertPopInit("请输入信息", PNULL, &cbDemoImageCt.popAlertIcon);
			break;
	      }
    	}
        break;
    case CBINPUT_CANCEL:
        break;
    default:
        break;
    }
}

 void
Cbdemo_Single_Edit_Box_Entry(void)
{
	CBInputTextParam param = {0};
    
      vm_memset(w_EditorOneBuf,0,sizeof(w_EditorOneBuf));
      extVmLcdManager->VMGB2UCS2((VMSTR)c_EditorOneBuf,(VMWSTR)w_EditorOneBuf,EDITOR_MAX_INPUT*2+1);
	param.ucs2buf_p = w_EditorOneBuf;
	param.buflen = EDITOR_MAX_INPUT*2+1;
	param.gbTitleStr_p = "单行编辑框";
	param.inputType = CBIMTYPE_ALL;
	param.firstMode = CBIMMODE_SCN;

	extVmSysManager->vmInputText(cbDemoEditBoxCallbackFunc2, &param);
}

extern void
cbar_draw_v_line(VMUINT16 x, VMUINT16 y1, VMUINT16 y2, VmColorType color)
{
    VmPointType start_point;
    VmPointType end_point;

    start_point.x = x;
    start_point.y = y1;
    end_point.x = x;
    end_point.y = y2;
    
    extVmLcdManager->VMDrawLine(start_point, end_point, color);
}

extern void
Cbdemo_display_editor(VmRectType rect, VmColorType framecolor, VmColorType fillcolor, VMSTR gbstr, VmColorType strcolor, VmColorType cursorcolor, VMBOOLEAN isactive)
{
    VMUINT16 startpos = 0;
    VMUINT16 strdispwidth = 0;
    VMUINT16 x, y;
    
    extVmLcdManager->VMFillRect(rect, fillcolor);
    extVmLcdManager->VMDrawRect(rect, framecolor);
    
    strdispwidth =rect.right - rect.left + 1 - 3;
    while (strdispwidth < extVmLcdManager->VMGetStringWidth(&gbstr[startpos]))
    {
        if (gbstr[startpos] >= 0x80)
        {
	     startpos += 2;
	 }
	 else
	 {
             startpos++;
        }
    }
    x = rect.left + 1;
    y = rect.top +(rect.bottom -rect.top + 1 - extVmLcdManager->VMGetFontHeight(1)) / 2;
    extVmLcdManager->VMDrawString(&gbstr[startpos], x, y, strcolor);

    if (isactive)
    {
        cbar_draw_v_line(x+extVmLcdManager->VMGetStringWidth(&gbstr[startpos])+1, y, y+extVmLcdManager->VMGetFontHeight(1), cursorcolor);
    }
}
static void
Cbdemo_Single_Edit_Box_show(void)
{
           Cbdemo_display_editor(editor_rect, 
            Vm_BLACK_COLOR,
            Vm_WHITE_COLOR, 
            (VMSTR)c_EditorOneBuf, 
            Vm_BLACK_COLOR, 
            Vm_RED_COLOR, 
            TRUE);
}


static void cbDemoEditBoxCallbackFunc3(CBInputResult result, VMWCHAR *wsbuf)
{

    switch (result)
    {
    case CBINPUT_OK: // get user input
    	{
            vm_memset(c_EditorOneBuf,0,sizeof(c_EditorOneBuf));
            extVmLcdManager->VMUCS2GB(w_EditorOneBuf,c_EditorOneBuf,sizeof(c_EditorOneBuf));
	     if(vm_strlen(c_EditorOneBuf) == 0)//输入为空
	     {
			cbDemoAlertPopInit("请输入信息", PNULL, &cbDemoImageCt.popAlertIcon);
			break;
	      }
    	}
        break;
    case CBINPUT_CANCEL:
        break;
    default:
        break;
    }
}


 void
Cbdemo_Full_Edit_Box_Entry(void)
{
	CBInputTextParam param = {0};
    
      vm_memset(w_EditorOneBuf,0,sizeof(w_EditorOneBuf));
      extVmLcdManager->VMGB2UCS2((VMSTR)c_EditorOneBuf,(VMWSTR)w_EditorOneBuf,EDITOR_MAX_INPUT*2+1);
	param.ucs2buf_p = w_EditorOneBuf;
	param.buflen = EDITOR_MAX_INPUT*2+1;
	param.gbTitleStr_p = "全屏编辑框";
	param.inputType = CBIMTYPE_ALL;
	param.firstMode = CBIMMODE_SCN;

	extVmSysManager->vmInputText(cbDemoEditBoxCallbackFunc3, &param);
}
#endif
