/*
——————————————————
 メインヘッダー
——————————————————
*/
#ifndef MAIN_IF_H
#define MAIN_IF_H

//
typedef unsigned int		UINT;
typedef unsigned char		UCHAR;
typedef unsigned short		USHORT;
typedef unsigned long		ULONG;
typedef char				CHAR;
typedef short				SHORT;
typedef long				LONG;

#define CURSOR_UP		49	// 1
#define CURSOR_DOWN		50	// 2
#define CURSOR_ENTER	10	// エンター 
#define CURSOR_BACK		32	// スペース
#define MOZI_BYTE		4
#define MOZI_2			MOZI_BYTE * 2 + 1	// 2文字
#define MOZI_3			MOZI_BYTE * 3 + 1	// 3文字
#define MOZI_4			MOZI_BYTE * 4 + 1	// 4文字
#define MOZI_5			MOZI_BYTE * 5 + 1	// 5文字
#define MOZI_6			MOZI_BYTE * 6 + 1	// 6文字
#define MOZI_7			MOZI_BYTE * 7 + 1	// 7文字
#define MOZI_8			MOZI_BYTE * 8 + 1	// 8文字
#define MOZI_9			MOZI_BYTE * 9 + 1	// 9文字
#define MOZI_10			MOZI_BYTE * 10 + 1	// 10文字
#define MOZI_25			MOZI_BYTE * 25 + 1	// 25文字
#define SKL_1			0x01
#define SKL_2			0x02
#define SKL_3			0x04
#define SKL_4			0x08
#define SKL_5			0x10
#define SKL_6			0x20
#define SKL_7			0x40
#define SKL_8			0x80



typedef struct{
	SHORT strength;	// 攻撃力
	SHORT defence;	// 防御力
	SHORT maxHP;	// HP
	SHORT maxMP;	// MP
	SHORT agility;	// 素早さ
	SHORT luck;		// 運
}CHARACTER;
//————————————————-
enum {
	OFF = 0,			//
	ON,					//
};
//————————————————-
enum {
	ATTACK_PLAYER = 0,			//
	ATTACK_ENEMY,
	ATTACK_NORMAL,				//
	ATTACK_SKILL,				//
};
//————————————————-
enum {
	ITEM_WEAPON = 0,	// 武器
	ITEM_ARMOR,			// 防具
	ITEM_DECOR,			// アクセサリー
	ITEM_CRYSTL,		// 水晶
	ITEM_MAX,			//
};
//————————————————-
enum {
	MAIN_COM_C = 0,		// キャラクター選択
	MAIN_COM_E,			// アイテム選択
	MAIN_COM_F,			// たたかう
	MAIN_COM_MAX,
};
//————————————————-
enum {
	FIGHT_COM_F = 0,		// キャラクター選択
	FIGHT_COM_D,			// アイテム選択
	FIGHT_COM_S,			// たたかう
	FIGHT_COM_I,
	FIGHT_COM_MAX,
};
//————————————————-
enum {
	CHOICE_YES = 0,		//
	CHOICE_NO,			//
	CHOICE_MAX,			//
};
//————————————————-
enum {
// アイテム個数
	ITEM_NAME_1 = 0,	//
	ITEM_NAME_2,		//
	ITEM_NAME_3,		//
	ITEM_NAME_4,		//
	ITEM_NAME_5,		//
	ITEM_NAME_MAX,		
};	
//————————————————-
enum {
// スキル個数
	SKILL_1 = 0,	//
	SKILL_2,		//
	SKILL_3,		//
	SKILL_4,		//
	SKILL_5,		//
	SKILL_6,		//
	SKILL_7,		//
	SKILL_8,		//
	SKILL_MAX,		
};	
//————————————————-
enum {
	// プレイヤー役職
	PLAYER_NAME_1 = 0,
	PLAYER_NAME_2,
	PLAYER_NAME_3,
	PLAYER_NAME_4,
	PLAYER_NAME_5,	
	PLAYER_NAME_MAX,
};
//————————————————-	
enum {
	STATUS_STRENGTH = 0,// 攻撃力
	STATUS_DEFENCE,		// 防御力
	STATUS_HP,			// HP
	STATUS_MP,			// MP
	STATUS_AGILITY,		// 素早さ
	STATUS_RUCK,		// 運
	STATUS_MAX,
};
//————————————————-	
enum {
	ENEMY_KIND_1 = 0,
	ENEMY_KIND_2,
	ENEMY_KIND_3,
	ENEMY_KIND_4,
	ENEMY_KIND_5,
	ENEMY_KIND_MAX,
};	
//————————————————————————
//   宣言
//————————————————————————
extern void basket();
extern const CHAR itemName[ITEM_MAX][MOZI_3];
extern const CHAR statusName[STATUS_MAX][MOZI_3];
extern const CHAR playerName[PLAYER_NAME_MAX][MOZI_4];
extern const CHAR itemNameTbl[ITEM_MAX][ITEM_NAME_MAX][MOZI_7];
extern const SHORT itemTbl[ITEM_MAX][ITEM_NAME_MAX][STATUS_MAX];
extern const SHORT playerTbl[PLAYER_NAME_MAX][STATUS_MAX];
extern const CHAR fightCommand[FIGHT_COM_MAX][MOZI_4];
extern const SHORT skillParaTbl[SKILL_MAX][STATUS_MAX];
extern const CHAR skillTurnTbl[SKILL_MAX];
extern const UCHAR skillNameTbl[SKILL_MAX][MOZI_10];
extern const UCHAR skillDescTbl[SKILL_MAX][MOZI_25];
#endif
