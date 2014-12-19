#ifndef EM_RESOURCE_DATA_H
#define EM_RESOURCE_DATA_H
#include "coolbar_GAME_Type.h"
#ifdef GAME_240_320
typedef enum
{
	EM_IMG_A02_GIF,
	EM_IMG_BG01_GIF,
	EM_SND_0_MID,
	EM_END_OF_ID
}EM_E;
#ifndef USE_MMC_RES_EM
extern const unsigned char EM_Resource_Data[];
extern tResource EM_TResource_Data;
#else
extern tResource EM_TResource_Data;
#endif
#endif
#endif
