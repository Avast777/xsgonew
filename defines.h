#pragma once

/* Offset IDs */
#define ENTITY_LIST -5
#define LOCAL_PLAYER -4
#define GLOW -1
#define SENS 0
#define ENGINE 3
#define VIEWANGLES 4
#define MOUSE 5
#define RESOURCE -2

/* Client breaking offsets */
#define OFS_ID 0x64
#define OFS_DORMANT 0xED
#define OFS_TEAM 0xF4
#define OFS_HP 0x100
#define OFS_FLAGS 0x104
#define OFS_VEC_VIEW 0x108
#define OFS_VELOCITY 0x114
#define OFS_VEC_ORIGIN 0x138
#define OFS_MOUSE_ENABLE 0x30
#define OFS_SENS 0x2C
#define OFS_GLOW_COUNT 0xC
#define OFS_WRITE_SIZE 35
#define IN_GAME 0x6
#define BONE_HEAD 8
#define BONE_NECK 7
#define BONE_CHEST 6
#define VK_INSERTS 0x2D

#define CT_T_KNIFE_DIFF 24
#define T_FANCY_KNIFE_DIFF 60

/* Keybind IDs */
#define SLOAD_SLOT 16
#define SOUND_SLOT 18

#define KEY_BHOP 0
#define KEY_GLOW 1
#define KEY_SOUND 2
#define KEY_RECOIL 3
#define KEY_RADAR 4
#define KEY_TRIGGER 5
#define KEY_EXIT 6
#define KEY_PANIC 7

#define KEY_START 0
#define KEYS_SIZE 8

/* Setting IDs */
#define OTR_SLOAD 8
#define OTR_NOTIF 9
#define RANK_ENABLED 10
#define KNIFE_DISTANCE 11
#define SKIN_ENABLED 12

#define SKIN_START 13
#define SKIN_SIZE 35

#define SKIN_CTKNIFE 48
#define SKIN_TKNIFE 49

#define DEV_SCAN 50

#define SOUND_MODE 51
#define SOUND_RANGE 52

#define RADAR_ALIVE 53

#define RCS_YAW 54
#define RCS_PITCH 55
#define RCS_UPDATE 56

#define GLOW_ALLY 57
#define GLOW_ITEM 58
#define GLOW_BOMB 59

#define TRIGGER_DELAY 60
#define TRIGGER_OVER 61
#define TRIGGER_SCOPE 62
#define TRIGGER_AIR 63

#define BHOP_INIT_DELAY 64




#define AIM_START 65
#define AIM_SECT 10
#define SECTION_ITEMS 11
#define AIM_SIZE (SECTION_ITEMS * AIM_SECT)

#define CFG_SIZE AIM_START + AIM_SIZE

/* Other variables */
#define KEY_SIZE 32



bool randFunc(int & x, int & y) {
	for (int i = 0; i < 56; ++i) {
		x *= y;
		y += x;
	}

	return x == y;
}