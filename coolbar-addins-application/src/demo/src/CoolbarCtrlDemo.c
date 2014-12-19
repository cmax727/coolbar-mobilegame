/*******************************************************************
  Copyright: Copyright (c) 2009 Coolbar, Inc. All Rights Reserved.
  
  FileName:CoolbarDemo.c
  
  Data:2009-5-13
  
  Auther:
  
  Description:��ɵĶ�̬������ʾ�汾
   
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

/*File��д����*/
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
  *������Դ�е�ͼƬ
  */
static void cbDemo_CreateImage(void)
{
   tResource res;	
	//��Ӧ��Դ���ļ��أ���ɵ����һ�������飬һ���ǹ�����Դ�ļ��� ����Ϊÿ��Ӧ�û�����Ϸ������Դ�ļ���

   #if defined(BILLING_USER_NEW) && !defined(COOLBAR_OLDH_PATCH)
	  extVmLcdManager->IMG_InitInnerDataPage();
    #endif
 
	//��ʼ�����������Դ����Դ�ǹ��õġ�
#ifndef USE_MMC_RES_CBDEMORES
	extVmLcdManager->IMG_InitDataPage(CbDemoRes_TResource_Data, 0);//ÿ����Ϸ����Ӧ������Ӧ���������Դ����ģ�������ڶ������� 0��ʾ��ͷ�ļ���ȡ
#else
	extVmLcdManager->IMG_InitDataPage(res, 1);//ÿ����Ϸ����Ӧ������Ӧ���������Դ�����ֻ�CBE) �ڶ������� 1 ��ʾT���м��ص�
#endif

     
	// �����Ǵ���Ӧ�û�����Ϸ��Ӧ�õ�ͼƬ��Դ�����ú��Դ���Դ����ͨ��Id�������Ӧ��ͼƬ
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
  *�ͷŴ�����ͼƬ����Դ
  */
static void cbDemo_DestoryImage(void)
{
	//�������ô�����ͼƬ����Ҫ��ͼƬ��Ӧ�Ŀռ���ͷ�
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.softKeyBar);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.titleBar);
    
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.popBgImage);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.popAlertIcon);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.popQueryIcon);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.popSuccIcon);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.popFailIocn);
    
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.listIconImage);
    extVmLcdManager->VMDestoryImage(&cbDemoImageCt.listNumImage);

	//�ͷų�ʾ���ռ���صĿռ� �� extVmLcdManager->IMG_InitInnerDataPage ��extVmLcdManager->IMG_InitDataPage ��Ӧ
    extVmLcdManager->IMG_ReleaseDataPage();
}


static VMBOOLEAN cb_HttpGetReqDemo(void);
/*********************************************************************************************************
*                 -- List init and dispose Demo 
*
*
*
**********************************************************************************************************/
//List �ؼ��Ļص�����
static void cbDemoMainListCallBack(CoolbarListBox * myself, gm_u16 result)
{
	VMUINT16  index = cbDemoMainList_p->GethighlightIndex(cbDemoMainList_p); //�õ�LIST��ǰ�ĸ�����
	switch(result)
	{
	case COOLBAR_LIST_RESULT_SELCET:   // List����ѡ�й���ʱ�����Ƚ������LIST) ȷ��
	case COOLBAR_LIST_RESULT_OK:	   // ��� 	
	case COOLBAR_LIST_RESULT_MID:	   //�м��
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
				cbDemoAlertPopInit("��ӭPopBox", PNULL, &cbDemoImageCt.popSuccIcon); // Pop box Demo
				break;				
			case 3:
				extVmScreenManager->vmAddScreen(&cbDemoTimerScreen);   // Timer Demo
				break;
			case 4:  //�ļ����ļ��еĶ�д����
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
		
	case COOLBAR_LIST_RESULT_RETURN:  //�˳�List�ؼ�
		if(cbDemoMainList_p !=PNULL)
		{
			cbDemoMainList_p->Release(&cbDemoMainList_p); //�ر�list
			extVmSysManager->VmEnterWinClose();//�Ƴ�����Ӧ��
		}
#if 0 
		if(myself != PNULL)  //��ӦLIST�ؼ��ͷ�Ҳ��������д  ��ͨ��ȫ����������Ч��һ��
		{
			myself->Release(myself->myself_p);	//�ͷŵĲ���myself->myself_p һ��Ҫ����д		
		}	
#endif
		break;			
	case COOLBAR_LIST_RESULT_NOSELECT: //List����ѡ�й���ʱ�����Ƚ������LIST) δѡ��		
		break;	
	default:
		break;
	}
}

// list �ؼ��ĳ�ʼ������
static void cbDemoMainList(void)
{
    VMUINT16 item_pos = 0;
    Rect rect;  //list �ؼ�����ʾ����������
    rect.x = 0;
    rect.y = extVmLcdManager->VMGetImageHeight(&cbDemoImageCt.titleBar);
    rect.w = VM_MAINSCREEN_WIDTH;
    rect.h = VM_MAINSCREEN_HEIGHT - extVmLcdManager->VMGetImageHeight(&cbDemoImageCt.titleBar) - extVmLcdManager->VMGetImageHeight(&cbDemoImageCt.softKeyBar);
   // list �ؼ��Ļ�����ʼ������
    extVmCtrlManager->InitCoolbarListBoxEx(&cbDemoMainList_p, 10, rect, COOLBAR_LIST_OPTION_STYLE_HAS_ICON, TRUE, cbDemoMainListCallBack);

    //����list���icon��ͼƬ
    cbDemoMainList_p->AddOptionImageList(cbDemoMainList_p,&cbDemoImageCt.listIconImage);
    cbDemoMainList_p->AddExtOptionImageList(cbDemoMainList_p, &cbDemoImageCt.listNumImage);	

    //����������ɫ�ڶ�������Ϊ������ɫ��������������ѡ��ʱ��������ɫ
    cbDemoMainList_p->SetFontColor(cbDemoMainList_p,  Vm_WHITE_COLOR,  Vm_WHITE_COLOR);
    //���ñ���ɫ�ڶ�������Ϊ������ɫ��������������ѡ��ʱ�ı���ɫ
    cbDemoMainList_p->SetBackColor(cbDemoMainList_p, Vm_BLACK_COLOR,  Vm_BLUE_COLOR);	
    //����title
    cbDemoMainList_p->AddTitleBar(cbDemoMainList_p, &cbDemoImageCt.titleBar, "Coolbar Demo");
    //��������� ��ʾ������
    cbDemoMainList_p->AddSoftkeyBar(cbDemoMainList_p, &cbDemoImageCt.softKeyBar, "ȷ��", PNULL, "����");
    //����list���������
    cbDemoMainList_p->AddOption(cbDemoMainList_p, "SingleEditBoxDemo", COOLBAR_LIST_NUMBER_ICON_INDEX);
    cbDemoMainList_p->AddOption(cbDemoMainList_p, "FullScreenEditBoxDemo", COOLBAR_LIST_NUMBER_ICON_INDEX);
    cbDemoMainList_p->AddOption(cbDemoMainList_p, "PopBoxDemo", COOLBAR_LIST_NUMBER_ICON_INDEX);
    cbDemoMainList_p->AddOption(cbDemoMainList_p, "TimerDemo", COOLBAR_LIST_NUMBER_ICON_INDEX);
    cbDemoMainList_p->AddOption(cbDemoMainList_p, "File Demo", COOLBAR_LIST_NUMBER_ICON_INDEX);
	cbDemoMainList_p->AddOption(cbDemoMainList_p, "HTTP Demo", COOLBAR_LIST_NUMBER_ICON_INDEX);

	cbDemoMainList_p->AddOption(cbDemoMainList_p, "Hello MTK", COOLBAR_LIST_NUMBER_ICON_INDEX);
    // ��ѡ�й��ܵ�List,�����Ѿ�ѡ�г�ʼ�� 
    cbDemoMainList_p->SetSelectIndex(cbDemoMainList_p, 0, TRUE);
	//����list�տ�ʼ�ĸ�����
    cbDemoMainList_p->SethighlightIndex(cbDemoMainList_p, 0);
}


static void cbDemoOpenSingleEditBox(void)
{
    extVmScreenManager->vmAddScreen(&cbDemoEditBoxBgScreen);// ���б༭������Ӧ��SCREEN����Screen ����
}

static void cbDemoEditBoxBgScreenInit(void * myselfParam)
{
	cbDemoSingleEditBoxInit(); //�༭���
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
	VmRectType rect = {0, 0, VM_MAINSCREEN_WIDTH - 1, VM_MAINSCREEN_HEIGHT - 1};// ��������

	extVmLcdManager->VMFillRect(rect, Vm_BLACK_COLOR);//������ɫ
	
	//draw title start
	extVmCtrlManager->VmPubDrawWinTitle(&cbDemoImageCt.titleBar, "Single EditBox Demo");
	//draw title end
	extVmLcdManager->VMDrawString("������:", 2, VM_MAINSCREEN_HEIGHT /5 - extVmLcdManager->VMGetFontHeight(TRUE) *3 /2, Vm_YELLOW_COLOR);

	#ifdef CB_NEWEDITOR_EN
        Cbdemo_Single_Edit_Box_show();

       //�����
	extVmCtrlManager->VmPubDrawSoftkeyBar(&cbDemoImageCt.softKeyBar,PNULL,PNULL,extVmLcdManager->VmResGetDefTxt(VM_IM_TXT_RETURN));		
	
    #endif//CB_NEWEDITOR_EN

}

#ifndef CB_NEWEDITOR_EN
// �༭��Ļص�����
static void cbDemoEditBoxCallbackFunc(cbar_editor_t *myself, cbar_editor_result_t result_id)
{
	VMCHAR  strBuf[20 + 2] = {0};
	cbar_editor_data_gb_t dataBuf = {0};
	
	dataBuf.gb_str_ptr = strBuf;
	//�õ��༭���е����ݣ�����ΪGB 
	myself->get_edit_str_gb(myself, &dataBuf, 20);
	dataBuf.gb_str_len = strlen((char*)dataBuf.gb_str_ptr); //���볤��
	
	switch(result_id)
	{
	case    CBAR_EDITOR_RESULT_OK:
		{
			if(dataBuf.gb_str_len == 0)//����Ϊ��
			{
				cbDemoAlertPopInit("��������Ϣ", PNULL, &cbDemoImageCt.popAlertIcon);
				break;
			}
		}
		
	case CBAR_EDITOR_RESULT_CANCEL:
		if(PNULL != cbDemoEditBox_p)//�˳��༭�����
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
	//�༭������Ӧ���������������
	VmRectType rect = {2, VM_MAINSCREEN_HEIGHT / 5, VM_MAINSCREEN_WIDTH - 4, VM_MAINSCREEN_HEIGHT / 5 + 22 *3 /2};

	cbar_editor_param_t param = {0};
    //�༭�����Ч�����뷨����ѡ��
	param.allow_im_type = CBAR_IM_TYPE_DIGIT |CBAR_IM_TYPE_PINYIN |CBAR_IM_TYPE_UPPER_CHAR |CBAR_IM_TYPE_LOWER_CHAR|CBAR_IM_TYPE_STROKE;
	param.first_im_mode = CBAR_IM_MODE_DIGIT;     //Ĭ�ϵ����뷨
	param.max_char_num = 20;                      //�������������ֵ
	param.gb_str_ptr = PNULL;                     //��ʼ���ַ�����
	//�༭�������ʼ������
	extVmCtrlManager->cbar_create_single_txt_editor(&cbDemoEditBox_p, &param, rect, cbDemoEditBoxCallbackFunc);

	//�༭���а��������ݺ���صı���ͼƬ
	cbDemoEditBox_p->add_softkey_bar(cbDemoEditBox_p, 
												&cbDemoImageCt.softKeyBar,
												"ȷ��",
												"ȷ��",
												PNULL,
												"����",
												"ɾ��"
												);
	//������ص�����
	cbDemoEditBox_p->add_title_bar(cbDemoEditBox_p, &cbDemoImageCt.titleBar, "EditBox Demo");
	//�༭��Ĺ�����Ч�ԣ���ҪΪ����༭�������л�ʱ
	cbDemoEditBox_p->set_active(cbDemoEditBox_p, TRUE);
#else
     vm_memset((VMSTR)c_EditorOneBuf,0,sizeof(c_EditorOneBuf));
#endif

}

static void cbDemoFullScreenEditBoxInit(void)
{
#ifndef  CB_NEWEDITOR_EN
	cbar_editor_param_t param = {0};
    //�༭�����Ч�����뷨����ѡ����Ĭ�����뷨����󳤶ȣ���ʼֵ
	param.allow_im_type = CBAR_IM_TYPE_DIGIT |CBAR_IM_TYPE_PINYIN |CBAR_IM_TYPE_UPPER_CHAR |CBAR_IM_TYPE_LOWER_CHAR|CBAR_IM_TYPE_STROKE;
	param.first_im_mode = CBAR_IM_MODE_DIGIT;
	param.max_char_num = 20;
	param.gb_str_ptr = PNULL;
	
	extVmCtrlManager->cbar_create_txt_editor(&cbDemoEditBox_p, &param, cbDemoEditBoxCallbackFunc);
    //�༭���а��������ݺ���صı���ͼƬ
	cbDemoEditBox_p->add_softkey_bar(cbDemoEditBox_p, 
												&cbDemoImageCt.softKeyBar,
												"ȷ��",
												"ȷ��",
												PNULL,
												"����",
												"ɾ��"
												);
	// ������ص�����
	cbDemoEditBox_p->add_title_bar(cbDemoEditBox_p, &cbDemoImageCt.titleBar, "EditBox Demo");
	////�༭��Ĺ�����Ч�ԣ���ҪΪ����༭�������л�ʱ
	cbDemoEditBox_p->set_active(cbDemoEditBox_p, TRUE);

#else
     vm_memset((VMSTR)c_EditorOneBuf,0,sizeof(c_EditorOneBuf));
     Cbdemo_Full_Edit_Box_Entry();
#endif

}


//pop start
// Pop box �Ļص�����
static void cbDemoPopCallBack(CB_PopBox * myself, gm_u16 result)
{
	switch(result)
	{
		case COOLBAR_POP_RESULT_OK:	     // ȷ�Ͽ�ѡPOP�У�ȷ�ϵ�Ӧ��
			break;
		case COOLBAR_POP_RESULT_RETURN:  // ����
		case COOLBAR_POP_RESULT_TIMEOUT: //��ʱ����ʱ
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

	// POP�����꣬һ�㻹����Ĭ��ֵ�ȽϺ�
	rect.x = STOCK_POP_BOX_X;
	rect.y = STOCK_POP_BOX_Y;
	rect.w = STOCK_POP_BOX_WIDTH;
	rect.h = STOCK_POP_BOX_HEIGHT;  
	
	params.poprect = rect;
	params.msgText = msgText; //��ʾ������
	params.msgText2= msgText2;
	params.rightText = "�ر�";//�Ҽ�����
	params.background=&cbDemoImageCt.popBgImage; // ����ͼƬ�� ����ͼƬΪ�գ��ͻ���Ĭ�ϵı���ɫ�����ʾ������
	params.imageIcon=imageIcon;                  //��ʾ�ĵ�СICON��ͼƬ
	params.timer = 2000;                            //��ʱ����ֵ
	params.imageSoftBar =&cbDemoImageCt.softKeyBar; // ��������ı���ͼƬ
	params.softTextColor = Vm_BLACK_COLOR;          //���������

	if(cbDemoPopBox !=PNULL)//Ԥ����
	{
		cbDemoPopBox->Release(&cbDemoPopBox);
		cbDemoPopBox = PNULL;
	}
	extVmCtrlManager->CbPopBox_InitEx(&cbDemoPopBox, &params, cbDemoPopCallBack);  

}



//timer Demo start
static VMCHAR g_timer_demo_buf[] = "��ӭʹ��coolbar ƽ̨������Ʒ";
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

    //��������timer
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
		case VM_MSG_KEYDOWN://������Ϣ����
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

		case VM_MSG_TP_PRESS_DOWN: //tp��Ϣ����
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
    extVmCtrlManager->VmPubDrawSoftkeyBar(&cbDemoImageCt.softKeyBar, "ȷ��", PNULL, "����");

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
	
    //�ж��ļ����ڵ��ļ����Ƿ����
	if(!extVmIoManager->Vm_file_direxist(VM_FS_MMC,demoDir))//VM_FS_MMC �ɱ�
	{
		extVmIoManager->Vm_file_mkdir(VM_FS_MMC,demoDir);
	}
	vm_memset(strDemo,0,sizeof(strDemo));
	demoLen = extVmUcs2StrManager->VmutStrlenUcs2((VMUINT16 *)demoDir);
	vm_memset(fileName,0,sizeof(fileName));
	extVmUcs2StrManager->VmutStrcatUcs2(fileName,demoDir);  
    fileName[demoLen] = L'\\';//���ҲҪע��ƽ̨���죬BREWƽ̨�ʼ����� '/'
	demoLen++;
	extVmUcs2StrManager->VmutStrcatUcs2((fileName+demoLen),demoFile);
	if(!extVmIoManager->Vm_file_exist(VM_CURR_DEV,fileName))   
	{
		fileHandler = extVmIoManager->Vm_file_open(VM_FS_MMC,fileName,"w+");//�ļ�����
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
		fileHandler = extVmIoManager->Vm_file_open(VM_FS_MMC,fileName,"r");//�ļ���ȡ
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
			point.y = (VMUINT16)((*(VMUINT32 *)param)>>16)&0xffff;		//TP������	
			if(extVmLcdManager->VMWinPointIsInRect(point, rightSoftkeyRect)) // �ж�TP�������Ƿ�����Ӧ��������
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
    extVmCtrlManager->VmPubDrawSoftkeyBar(&cbDemoImageCt.softKeyBar, PNULL, PNULL, "����"); //SOFTKEY
	
}
/*********************************************************************************************************
*                 --HTTP GET req and dispose
*
*
*
**********************************************************************************************************/
static VMUINT32 httpNetConnectId = 0;           //�������ӵ�ID��Ҫ���������ӹ������û�����ȡ��ʱ������ID��Ҫ��������
VMUINT8  * pPicRecDate =  PNULL;                //�յ���ͼƬ����
VMUINT32  receivedDataLen = 0;                  //�յ������ݳ���   
#define   PIC_URL  "http://wallpaper.6636.com/wallpicclient/download.aspx?pictureid=17092&width=240&height=320"   //���������URL
#define   PICVIEW_PIC_DATA_SIZE   60*1024       //���ݵ����ֵ�������Ļ���������ֱ�Ӷ�����
static VmImageType downloadPic = {0};           //ͼƬ���غ󣬽�������á�

static void
cb_HttpGetReqCbDemo(VMUINT8 * buffer,VMUINT32 bufLen,VMUINT32 totalLen,NetRequestResultType result)
{
       vm_log_debug("[demo] connect bufLen=%d,totalLen=%d,result=%x",bufLen,totalLen,result);
	if( (result == HTTP_RETRY)||(result == HTTP_CANCEL))         //�����쳣
	{
	       vm_log_debug("[demo] connect error 2");
		return;
	}	
	if(totalLen >PICVIEW_PIC_DATA_SIZE)                          //���ص����ݳ���Ĭ�ϵ����ֵ
	{	
	       vm_log_debug("[demo] connect long");
		extVmNetManager->CancelHttpConnect(httpNetConnectId);    // ȡ����Ӧ���������
		httpNetConnectId = 0;				                    
		receivedDataLen = 0;
		vm_memset(pPicRecDate,0,PICVIEW_PIC_DATA_SIZE);
		return;
	}	
	if(result == NETREQUEST_ERROR)                                // ��������ֱ��ʧ��
	{
	       vm_log_debug("[demo] connect error 3 ");
		httpNetConnectId = 0;	
		receivedDataLen = 0;		
		vm_memset(pPicRecDate,0,PICVIEW_PIC_DATA_SIZE);
		return;
	}
	vm_memcpy((pPicRecDate + receivedDataLen),buffer,bufLen);             //�����յ����������� ����ͼƬ��Ϣ����,�뷢�Ͳ������ƣ�������
	receivedDataLen += bufLen;                                            //���ݴ���
	if((HTTP_ALL_RECEIVED == result)&&(receivedDataLen == totalLen))      //��������������Ѿ�ȫ��������
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
	pFun = cb_HttpGetReqCbDemo;    	               //��������Ļص�����
	if(httpNetConnectId != 0)                    
	{
		extVmNetManager->CancelHttpConnect(httpNetConnectId);		
	}
	httpNetConnectId = 0;
	if(PNULL == pPicRecDate)
	{
		pPicRecDate = extVmMemoryManager->mF_MallocGmemoryBlock(PICVIEW_PIC_DATA_SIZE);   // ���뱣�����ص����ݵĿռ�
	}

	vm_memset(pPicRecDate,0,PICVIEW_PIC_DATA_SIZE);
    receivedDataLen = 0;

	sprintf((VMCHAR*)updateUrl,PIC_URL);           // ���������URL
	returnVal = extVmNetManager->GetHttpData((char*)updateUrl,pFun,&httpNetConnectId); // �������������(get type)
    //extVmNetManager->PostHttpData();  HTTP POST �ӿ� ; post �� get ��ʽ������ 
	if(returnVal == FALSE)                         //��������ֱ��ʧ�ܣ���Ҫע��
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
	//�ڶ����ڴ����뷽ʽ�������������ڴ����뷽ʽ��û��ʲô���ơ���ҪΪ������ͷŵ�˳���Ա�����ڴ���Ƭ��
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
			STAND_JPG);                     //�������ص�ͼƬ���ݣ�������Ӧ��ͼƬ
	}
}
static void cb_HttpImageDisplayScrDestory(void *myself)
{
	if(PNULL != downloadPic.data)              //�ͷſռ�
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
	case GAME_MSG_KEYDOWN:                   //������Ϣ�Ĵ���
		{
			key =*(VMUINT32*)param;          //�����ļ�ֵ
			switch(key)// 
			{
			case MF_KEY_RIGHTSOFT:			// �Ҽ� ������ذ����Ĵ���ֻ�������Ӧ��CASE
				extVmScreenManager->vmDeleteScreen(&cb_HttpImageDisplayScr);
				break;
			default:				
				break;
			}
			break;
		}
	case GAME_MSG_TP_PRESS_DOWN:  //TP��Ϣ�Ĵ���
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
	extVmCtrlManager->VmPubDrawSoftkeyBar(&cbDemoImageCt.softKeyBar, PNULL, PNULL, "����"); //SOFTKEY
}
/*********************************************************************************************************
*
*     -- coolbar Demo ����ں��˳�������
*                    
*
**********************************************************************************************************/
void cb_Gb2Ucs2Demo(void);
void CoolBarDemo_Enter(void)
{
	//������Դʱ����Ҫ���ڴ棬һ�����Դ��bin�ļ���20K���ұȽϺ���
	#ifdef COOLBAR_OLDH_PATCH
	extVmMemoryManager->dF_InitMemory(300*1024);
	//��V3�汾���ش����Ƿ�����Դ��ģ��ʸú�����ʼ�����������Դ��ʼ��֮ǰ,df_InitMemory֮��!!!!!!
	initMemoryBlock(getMemoryBlockPtr(),1024*5);//������2��datapackage���ʱ����ʼ����V3�ں���bug���������Ҫ�ı��С����������ͷ����³�ʼ��
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
	
    //����ͼƬ��Դ
    cbDemo_CreateImage();


	
    cbDemoMainList();

    //�ڴ�����ĵ�һ�ַ�ʽ������ÿ��Ӧ�û�����Ϸ.gmemoryֻ��ͬʱ����һ����ֻ������������ͷš�
    //�����Ѿ�������ڴ�飬�������½��зֿ�����ʹ�á�����ÿ���ֿ�ֻ�ܽ��и�ֵ������   ��������
	extVmMemoryManager->mF_InitGmemoryBlock(PICVIEW_PIC_DATA_SIZE +1000);     //�����������ص�ͼƬ��Դ
	extVmMemoryManager->mF_resetGmemoryBlock();    //�˺���ʹ�ú����еķֿ鶼�Ѿ���Ч���ֿ�ָ�붼����PNULL	
	cb_Gb2Ucs2Demo();  //just for demo
}


void CoolBarDemo_Exit(void)
{
	if(httpNetConnectId != 0)                                //���������ӵĹ����У���ʱ���һ���ʱ
	{
      extVmNetManager->CancelHttpConnect(httpNetConnectId);  // ȡ���Ѿ���������������
	  httpNetConnectId = 0;                                  
	}
    //�ͷ�ͼƬ��Դռ�õ���Դ
    cbDemo_DestoryImage();                                   // �� cbDemo_CreateImage()  ��Ӧ

    //�ͷŷ�����ڴ�
    extVmMemoryManager->dF_ReleaseMemory();                  // �� extVmMemoryManager->dF_InitMemory()        ��Ӧ
	extVmMemoryManager->mF_ReleaseGmemoryBlock();            // �� extVmMemoryManager->mF_InitGmemoryBlock()  ��Ӧ
}
/*********************************************************************************************************
*
*                        CBE������ں��뿪����
*1: ����Enter��EXIT�����ĺ�������Ӧ�ñ�����ͬΨһ����̬���ص�ʱ�����Ժ���ָ�����ʽ��ʼ��                 
*
**********************************************************************************************************/
#ifndef WIN32
VmMainFunction vMGetMainEnterFuct(void)   //������������ָ�룩�̶�Ψһ�����ɸı䡣
{
    return CoolBarDemo_Enter;              //ʵ�ʵ���ں���
}

VmMainFunction vMGetMainExitFuct(void)    //ͬ��
{
    return CoolBarDemo_Exit;               //ʵ�ʵ��˳�����
}
#endif
/*********************************************************************************************************
*
*          -- coolbar GB->UCS2 and  UCS2->GB DEMO
*1: �ӿڷ�װ������ƽ̨�Ĳ��죬ת�����Ƿ����0�����ڿռ����Ԥ��2���ֽڵĿռ�
*
**********************************************************************************************************/
#define MAX_LEN 10 
void
cb_Gb2Ucs2Demo(void)
{	
	VMSTR pGbStr = "�ַ�����ת��";
	VMUINT16 ucs2Str[MAX_LEN+1] = {0} ;
	VMCHAR   gbStr[2*(MAX_LEN+1)] = {0};		
	extVmLcdManager->VMGB2UCS2(pGbStr,ucs2Str,MAX_LEN);                  //�ౣ�������ֽڵĿռ䣬��Ҫ��ƽ̨�Ĳ��죬����GB->UCS2��
	                                                                     //ת�����Ƿ����0�Ĵ���
	extVmLcdManager->VMUCS2GB((VMWSTR)ucs2Str,(VMSTR)gbStr,MAX_LEN*2);   //ͬ��
}

/*********************************************************************************************************
*
*              -- coolbar audio play demo  (��Ƶ����)
* 1: ������Ƶ���Žӿڣ�����Ŀǰֻ֧��MTK��չѶWƽ̨;
* 2: BREWƽ̨��չѶ����ƽ̨����Ч���ܲ���ṩ�ӿڹ���
**********************************************************************************************************/
#ifndef COOLBAR_OLDH_PATCH
VMUINT8 audioData[] = {1,2,3,1,2,3,1,3,1,2,3,1};//��Ƶ��Դ 
void 
cb_AudioPlayDemo(void)
{
	extVmAudioManager->vMAudioSetVolume(0,1);            //volume�ķ�ΧΪ0��1��2��3��4��5��6 ��
	                                                     //immediate ��ֵΪ1;�Ķ�������Ч;0:�´β�����Ч
    extVmAudioManager->vMAudioPlayByData(audioData,0);   //pData ���ŵ���Դ
                                                         //repeats ���ŵĴ��� 0 ѭ�����ţ�N ����N��
    extVmAudioManager->vMAudioPlayForGame(30,0);         //res ����Ƶ��Դ��ͼƬһ��������Դ��T������ ��Ϸר��
    extVmAudioManager->vMAudioPlayForApp(30,0);          //res ����Ƶ��Դ��ͼƬһ��������Դ��T������ Ӧ��ר��
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
// �༭��Ļص�����
static void cbDemoEditBoxCallbackFunc2(CBInputResult result, VMWCHAR *wsbuf)
{

    switch (result)
    {
    case CBINPUT_OK: // get user input
    	{
            vm_memset(c_EditorOneBuf,0,sizeof(c_EditorOneBuf));
            extVmLcdManager->VMUCS2GB(w_EditorOneBuf,c_EditorOneBuf,sizeof(c_EditorOneBuf));
	     if(vm_strlen(c_EditorOneBuf) == 0)//����Ϊ��
	     {
			cbDemoAlertPopInit("��������Ϣ", PNULL, &cbDemoImageCt.popAlertIcon);
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
	param.gbTitleStr_p = "���б༭��";
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
	     if(vm_strlen(c_EditorOneBuf) == 0)//����Ϊ��
	     {
			cbDemoAlertPopInit("��������Ϣ", PNULL, &cbDemoImageCt.popAlertIcon);
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
	param.gbTitleStr_p = "ȫ���༭��";
	param.inputType = CBIMTYPE_ALL;
	param.firstMode = CBIMMODE_SCN;

	extVmSysManager->vmInputText(cbDemoEditBoxCallbackFunc3, &param);
}
#endif
