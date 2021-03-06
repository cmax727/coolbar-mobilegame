#ifndef CBDEMORES_RESOURCE_DATA_H
#define CBDEMORES_RESOURCE_DATA_H
#include "coolbar_GAME_Type.h"
#ifndef WIN32
#define USE_MMC_RES_CBDEMORES
#endif
#ifdef GAME_176_220
typedef enum
{
	CBDEMORES_IMAGE_POP_BG_GIF,
	CBDEMORES_IMAGE_PROMPT_ICON_ALERT_GIF,
	CBDEMORES_IMAGE_PROMPT_ICON_QUERY_GIF,
	CBDEMORES_IMAGE_PROMPT_ICON_SUCCESS_GIF,
	CBDEMORES_IMAGE_PROMPT_ICON_WRONG_GIF,
	CBDEMORES_IMAGE_SOFTKEY_BG_GIF,
	CBDEMORES_IMAGE_TITLE_BAR_GIF,
	CBDEMORES_LISTICON_GIF,
	CBDEMORES_LIST_ICON_UNMBER_GIF,
	VM_TXT_NO_T_CARD,
	VM_IM_TXT_OK,
	VM_IM_TXT_RETURN,
	VM_IM_TXT_CANCEL,
	VM_IM_TXT_OPEN,
	VM_IM_TXT_CLOSE,
	VM_IM_TXT_DEL,
	CBDEMORES_END_OF_ID
}CBDEMORES_E;
#ifndef USE_MMC_RES_CBDEMORES
extern const unsigned char CbDemoRes_Resource_Data[];
extern tResource CbDemoRes_TResource_Data;
#else
extern tResource CbDemoRes_TResource_Data;
#endif
#endif
#ifdef GAME_240_320
typedef enum
{
	CBDEMORES_IMAGE_POP_BG_GIF,
	CBDEMORES_IMAGE_PROMPT_ICON_ALERT_GIF,
	CBDEMORES_IMAGE_PROMPT_ICON_QUERY_GIF,
	CBDEMORES_IMAGE_PROMPT_ICON_SUCCESS_GIF,
	CBDEMORES_IMAGE_PROMPT_ICON_WRONG_GIF,
	CBDEMORES_IMAGE_SOFTKEY_BG_GIF,
	CBDEMORES_IMAGE_TITLE_BAR_GIF,
	CBDEMORES_LISTICON_GIF,
	CBDEMORES_LIST_ICON_UNMBER_GIF,
	VM_TXT_NO_T_CARD,
	VM_IM_TXT_OK,
	VM_IM_TXT_RETURN,
	VM_IM_TXT_CANCEL,
	VM_IM_TXT_OPEN,
	VM_IM_TXT_CLOSE,
	VM_IM_TXT_DEL,
	CBDEMORES_END_OF_ID
}CBDEMORES_E;
#ifndef USE_MMC_RES_CBDEMORES
extern const unsigned char CbDemoRes_Resource_Data[];
extern tResource CbDemoRes_TResource_Data;
#else
extern tResource CbDemoRes_TResource_Data;
#endif
#endif
#endif
