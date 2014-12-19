/*******************************************************************
  Copyright: Copyright (c) 2009 Coolbar, Inc. All Rights Reserved.
  
  FileName:CoolbarDemo.h
  
  Data:2009-5-13
  
  Auther:
  
  Description:酷吧的动态加载演示版本
   
***********************************************************************/
#if !defined(__COOLBAR_CTRL_DEMO_H__)
#define __COOLBAR_CTRL_DEMO_H__


typedef struct
{
	VmImageType  softKeyBar;
	VmImageType  titleBar;

	//for list
	VmImageType  listIconImage;
	VmImageType  listNumImage;

	//for pop
	VmImageType  popBgImage;
	VmImageType  popAlertIcon;
	VmImageType  popFailIocn;
	VmImageType  popQueryIcon;
	VmImageType  popWaitIocn;
	VmImageType  popSuccIcon;
    
}AppDemoResIDContextStruct;


#endif /*__COOLBAR_CTRL_DEMO_H__*/
/* End Of File*/