/*
——————————————————
 メイン 処理
——————————————————
*/
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "time.h"
#include "conio.h"
#include "main_IF.h"
#include "mainTbl.h"

//————————————————————————
//   内部関数
//————————————————————————
static void space(void);
static void dispcls(void);
static void mainDisp(void);
static void comFin(void);
static void comChange(void);
static void playerMain(void);
static UCHAR playerSet(UCHAR mob);
static void playerReady(UCHAR mob);
static void playerEnter(UCHAR mob);
static void playerIncre(UCHAR mob);
static void playerDecre(void);
static void enwmyset(void);
static void itemMain(void);
static void itemSet(UCHAR item);
static UCHAR itemChoice(UCHAR com, UCHAR item);
static void itemReady(UCHAR com, UCHAR item);
static void itemEnter(UCHAR com, UCHAR item);
static void itemIncre(UCHAR com, UCHAR item);
static void itemDecre(UCHAR com, UCHAR item);
static void fightMain();
static void enemySubDisp();
static void enemySet();
static SHORT damage(UCHAR mob, UCHAR skill);
static void enemyDisp();
static void skillCalc(UCHAR mob, SHORT *str, SHORT *def, SHORT *hp, SHORT *agi, SHORT *lu);
static void fightMeinDisp(void);
static void fightDisp(void);
static void defenceDisp(CHAR *sw);
static void skillChoice(CHAR *sw);
static UCHAR skillEnter(CHAR skill);
static void skillDisp(CHAR skill);
static void enemyDisp(void);
static void baseSet(void);
//————————————————————————
//	内部変数
//————————————————————————
CHARACTER player;
CHARACTER enemy;
CHARACTER base;
static UCHAR oldmob;
static UCHAR playerAll;
static UCHAR itemAll;
static UCHAR itemSW;
static UCHAR olditem[ITEM_MAX];
static UCHAR defCnt;
static UCHAR skillAll;
static UCHAR skillKind[2][SKILL_MAX];
static UCHAR skillSW[2][SKILL_MAX];

//————————————————————————-
//		 
//————————————————————————-
static void enemySubDisp(void)
{
	space();printf("										\n");
	space();printf("					  ■■■■■■		\n");
	space();printf("					■■■■■■■■		\n");
	space();printf("					■■■□□■□■		\n");
	space();printf("				  ■□■□□□■□□□	\n");
	space();printf("				  ■□■■□□□■□□□	\n");
	space();printf("				  ■■□□□□■■■■	\n");
	space();printf("					  □□□□□□□		\n");
	space();printf("					■■■■■■■■    \n");
	space();printf("				  ■■■■■■■■■■   \n");
	space();printf("				■■■■■■■■■■■■	\n");
	space();printf("				□□■■□■■□■■□□	\n");
	space();printf("				□□□■■■■■■□□□	\n");
	space();printf("				□□■■■■■■■■□□	\n");
	space();printf("				    ■■■    ■■■		\n");
	space();printf("				  ■■■        ■■■	\n");
	space();printf("				■■■			  ■■■	\n");
	space();printf("										\n");
	space();printf("				※画像はイメージです※\n");
	space();printf("										\n");
	space();printf("										\n");
}
static void staDisp()
{
	space();printf("＋ーーーーーーーーーーーーーーーーーーーーーーーーーーー＋\n");	
	space();printf("｜					！！敵が現れた！！					｜\n");	
	space();printf("＋ーーーーーーーーーーーーーーーーーーーーーーーーーーー＋\n");	
	getch();
}
static void enemySet()
{
	SHORT s;
	
	srand(time(NULL));
	s = rand() % ENEMY_KIND_MAX;
	enemy.strength	= enemyStuTbl[s][STATUS_STRENGTH];
	enemy.defence	= enemyStuTbl[s][STATUS_DEFENCE];
	enemy.maxHP		= enemyStuTbl[s][STATUS_HP];
	enemy.maxMP		= enemyStuTbl[s][STATUS_MP];
	enemy.agility	= enemyStuTbl[s][STATUS_AGILITY];
	enemy.luck		= enemyStuTbl[s][STATUS_RUCK];
}
//————————————————————————-
//		 画面クリア関数
//————————————————————————-
 extern void dispcls(void)
{
	system("cls");
}
static void space(void)
{
	printf("				");	
}
//————————————————————————-
//			 
//————————————————————————-
static UCHAR comSet(CHAR *command)
{	
	CHAR ch = getch();
	switch(ch){
		case CURSOR_ENTER:	break;
		case CURSOR_BACK:	break;
		case CURSOR_UP:		*command += 1;	break;
		case CURSOR_DOWN:	*command -= 1;	break;
	}
	return(ch);
}
//————————————————————————-
//			 メインディスプレイ
//————————————————————————-
static void mainDisp(void)
{	
	dispcls();		
	printf(	"＋ーーーーーステータスーーーーー＋\n");
	printf("｜	キャラ	:%s			｜\n"
	,(playerAll == ON)?playerName[oldmob]:"未選択	");
	for(UCHAR i = 0; i < ITEM_MAX; i++){
		printf("｜	%s:%s	｜\n",itemName[i]
		,((itemAll >> i) & 0x01)?
		itemNameTbl[i][olditem[i]] :
		"未選択			");
	}
	if(player.strength	< 0)	player.strength	= 0;
	if(player.defence	< 0)	player.defence	= 0;
	if(player.maxHP		< 0)	player.maxHP	= 0;
	if(player.maxMP		< 0)	player.maxMP	= 0;
	if(player.agility	< 0)	player.agility	= 0;
	if(player.luck		< 0)	player.luck		= 0;	
	printf("｜	%s:	%d				｜\n",statusName[STATUS_STRENGTH]	,player.strength);
	printf("｜	%s:	%d				｜\n",statusName[STATUS_DEFENCE]		,player.defence	);
	printf("｜	%s:	%d				｜\n",statusName[STATUS_HP]			,player.maxHP	);
	printf("｜	%s:	%d				｜\n",statusName[STATUS_MP]			,player.maxMP	);
	printf("｜	%s:	%d				｜\n",statusName[STATUS_AGILITY]		,player.agility	);
	printf("｜	%s:	%d				｜\n",statusName[STATUS_RUCK]		,player.luck	);
	printf(	"＋ーーーーーーーーーーーーーーー＋\n");
}
//————————————————————————-
//			 最終決定
//————————————————————————-
static void comFin(void)
{
	CHAR choice, s, ch;
		
	while(1){
		mainDisp();
		if(playerAll == OFF){
			printf("＋ーーーーーーーーーーーーーーー＋\n");
			printf("｜	キャラクターを選択			｜\n");
			printf("｜	してください。				｜\n");
			printf("＋ーーーーーーーーーーーーーーー＋\n");
			getch();
			break;
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		printf("｜	上記でいいですか？			｜\n");
		printf("｜	(これ以降変更できません)	｜\n");
		choice = ((CHOICE_MAX + choice) % CHOICE_MAX);
		for(s = 0; s < CHOICE_MAX; s++){
			printf("｜	%s ・%s		 		｜\n",(s == choice)?"→":"  ",choiceName[s]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		if(CURSOR_ENTER == comSet(&choice)){
			if(CHOICE_YES == choice){	baseSet();fightMain();break;	}				
			else					{	comChange();		}
		}
	}
}
//————————————————————————-
//		変更
//————————————————————————-
static void comChange(void)
{
	CHAR com, sw;
		
	while(1){		
		mainDisp();
		com = (MAIN_COM_F + com) % MAIN_COM_F;
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		printf("｜		どれを変更しますか？	｜\n");
		for(int i = 0; i < MAIN_COM_F; i++){
			printf("｜		%s	%s		｜\n"
			,(i == com)?"→":" ",mainCommand[i]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		if(CURSOR_ENTER == comSet(&com)){
			if(MAIN_COM_C == com)	{playerMain();}
			if(MAIN_COM_E == com)	{itemSW = OFF;itemMain();}
			break;
		}
	}
}
//————————————————————————-
//			 メインループ
//————————————————————————-
int main()
{	
	CHAR command, i;
	while(1){		
		mainDisp();
		command = (MAIN_COM_MAX + command) % MAIN_COM_MAX;
		printf("＋ーーーーーー 選択 ーーーーーー＋\n");
		for(i = 0; i < MAIN_COM_MAX; i++){
			printf("｜		%s	%s		｜\n",(i == command)?"→":" ",mainCommand[i]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		switch(comSet(&command)){
			case CURSOR_ENTER:
				if(MAIN_COM_C == command){playerMain();}
				if(MAIN_COM_E == command){itemSW = OFF;itemMain();}
				if(MAIN_COM_F == command){comFin();}
				break;
			case CURSOR_BACK:
				break;
		}
	}
}
/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	キャラクター関連処理
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
//————————————————————————-
//		キャラ選択
//————————————————————————-
static void playerMain(void)
{
	CHAR mob, sw;
		
	while(1){		
		mainDisp();
		mob = (PLAYER_NAME_MAX + mob) % PLAYER_NAME_MAX;
		printf("＋ーーーーキャラ を 選択ーーーー＋\n");
		for(int i = 0; i < PLAYER_NAME_MAX; i++){
			printf("｜		%s	%s			｜\n"
			,(i == mob)?"→":" ",playerName[i]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		switch(comSet(&mob)){
			case CURSOR_ENTER:
				if(CHOICE_YES == playerSet(mob)){ sw = ON;break; }
			case CURSOR_BACK:
				sw = ON;
				break;
		}
		if(sw)	break;	
	}
}
//————————————————————————-
//		キャラクター設定
//————————————————————————-
static UCHAR playerSet(UCHAR mob)
{
	CHAR i, s, ch, choice;
	
	while(1){ 
		mainDisp();	
		printf(	"＋ーーーーーーーーーーーーーーー＋\n");
		for(i = 0; i < STATUS_MAX; i++){
			printf("｜	%s:	%d	→	%d		｜\n"
			,statusName[i]
			,(playerAll == ON)?playerStuTbl[oldmob][i]: 0
			,playerStuTbl[mob][i]);
		}
		printf(	"＋ーーーーーーーーーーーーーーー＋\n");
		printf("｜								｜\n");
		printf("｜		%s  				｜\n",playerName[mob]);
		printf("｜		にしますか？	  		｜\n");
		choice = ((CHOICE_MAX + choice) % CHOICE_MAX);
		for(s = 0; s < CHOICE_MAX; s++){
			printf("｜	%s ・%s		 		｜\n",(s == choice)?"→":"  ",choiceName[s]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		if(CURSOR_ENTER == comSet(&choice)){
			if(choice == CHOICE_YES){	
				if(playerAll == ON)	playerReady(mob);
				else				playerEnter(mob);
			}
			return(choice);
		}	
	}	
}
//————————————————————————-
//		キャラクター決定
//————————————————————————-
static void playerEnter(UCHAR mob)
{
	playerIncre(mob);
	mainDisp();
	printf("＋ーーーーーーーーーーーーーーー＋\n");
	printf("｜		  		  		  		｜\n");
	printf("｜		%s  				｜\n",playerName[mob]);
	printf("｜		を選択しました			｜\n");
	printf("｜						  		｜\n");
	printf("＋ーーーーーーーーーーーーーーー＋\n");
	getch();
}
//————————————————————————-
//		キャラクター変更
//————————————————————————-
static void playerReady(UCHAR mob)
{
	CHAR choice, ch, s;
	
	while(1){
		mainDisp();
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		printf("｜		%s  				｜\n",playerName[oldmob]);
		printf("｜		を選択済みです。   		｜\n");
		printf("｜						  		｜\n");
		printf("｜		変更しますか？	  		｜\n");
		for(s = 0; s < CHOICE_MAX; s++){
			choice = ((CHOICE_MAX + choice) % CHOICE_MAX);
			printf("｜	%s ・%s		  		｜\n",(s == choice)?"→":"  ",choiceName[s]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		if(CURSOR_ENTER == comSet(&choice)){
			if(choice == CHOICE_YES){	
				playerDecre();
				playerEnter(mob);
				break;
			}
		}	
	}
}
//————————————————————————-
//		ステータス加算(キャラクター)
//————————————————————————-
static void playerIncre(UCHAR mob)
{
	player.strength	+= playerStuTbl[mob][STATUS_STRENGTH];
	player.defence	+= playerStuTbl[mob][STATUS_DEFENCE];
	player.maxHP	+= playerStuTbl[mob][STATUS_HP];
	player.maxMP	+= playerStuTbl[mob][STATUS_MP];
	player.agility	+= playerStuTbl[mob][STATUS_AGILITY];
	player.luck		+= playerStuTbl[mob][STATUS_RUCK];
	oldmob	 		 = mob;
	playerAll		 = ON;
}
//————————————————————————-
//		ステータス減算(キャラクター)
//————————————————————————-
static void playerDecre(void)
{
	player.strength	-= playerStuTbl[oldmob][STATUS_STRENGTH];
	player.defence	-= playerStuTbl[oldmob][STATUS_DEFENCE];
	player.maxHP	-= playerStuTbl[oldmob][STATUS_HP];
	player.maxMP	-= playerStuTbl[oldmob][STATUS_MP];
	player.agility	-= playerStuTbl[oldmob][STATUS_AGILITY];
	player.luck		-= playerStuTbl[oldmob][STATUS_RUCK];
}	
/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	アイテム関連処理
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
//————————————————————————-
//		アイテム選択
//————————————————————————-
static void itemMain(void)
{
	CHAR item, sw;
		
	while(1){
		mainDisp();
		item = (ITEM_MAX + item) % ITEM_MAX;
		printf("＋ーーーーアイテムを選択ーーーー＋\n");
		for(int i = 0; i < ITEM_MAX; i++){
			printf("｜		%s	%s			｜\n"
			,(i == item)?"→":" ",itemName[i]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		switch(comSet(&item)){
			case CURSOR_ENTER:
				itemSet(item);
				break;
			case CURSOR_BACK:
				sw = ON;
				break;
		}
		if((itemSW)||(sw))	break;
	}
}
//————————————————————————-
//		 アイテム設定
//————————————————————————-
static void itemSet(UCHAR item)
{
	CHAR i, com, sw;
	
	while(1){
		mainDisp();
		com = (ITEM_NAME_MAX + com) % ITEM_NAME_MAX;
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		for(i = 0; i < ITEM_NAME_MAX; i++){
			printf("｜		%s	%s	｜\n",(i == com)?"→":" ",itemNameTbl[item][i]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		switch(comSet(&com)){
			case CURSOR_ENTER:
				if(CHOICE_YES == itemChoice(com, item)){
					sw = ON;
				}
				break;
			case CURSOR_BACK:
				sw = ON;
				break;
		}
		if(sw)	break;	
	}
}
//————————————————————————-
//		アイテム確認
//————————————————————————-
static UCHAR itemChoice(UCHAR com, UCHAR item)
{
	CHAR i, s, choice;
	
	while(1){
		mainDisp();	
		printf(	"＋ーーーーーーーーーーーーーーー＋\n");
		for(i = 0; i < STATUS_MAX; i++){
			printf("｜	%s:	%d	→	%d		｜\n"
			,statusName[i]
			,((itemAll >> item) & 0x01)?itemStuTbl[item][olditem[item]][i]: 0
			,itemStuTbl[item][com][i]);
		}
		printf(	"＋ーーーーーーーーーーーーーーー＋\n");
		printf("｜								｜\n");
		printf("｜		%s  		｜\n",itemNameTbl[item][com]);
		printf("｜		にしますか？	  		｜\n");
		choice = ((CHOICE_MAX + choice) % CHOICE_MAX);
		for(s = 0; s < CHOICE_MAX; s++){
			printf("｜	%s ・%s		 		｜\n",(s == choice)?"→":"  ",choiceName[s]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		if(CURSOR_ENTER == comSet(&choice)){
			if(choice == CHOICE_YES){	
				if((itemAll >> item) & 0x01)	itemReady(com, item);
				else							itemEnter(com, item);
			}
			return(choice);					
		}	
	}	
}
//————————————————————————-
//		アイテム決定
//————————————————————————-
static void itemEnter(UCHAR com, UCHAR item)
{
	itemIncre(com, item);
	mainDisp();
	printf("＋ーーーーーーーーーーーーーーー＋\n");
	printf("｜		  		  		  		｜\n");
	printf("｜		%s  		｜\n",itemNameTbl[item][com]);
	printf("｜		を装備しました			｜\n");
	printf("｜						  		｜\n");
	printf("＋ーーーーーーーーーーーーーーー＋\n");
	getch();
}
//————————————————————————-
//		アイテム変更
//————————————————————————-
static void itemReady(UCHAR com, UCHAR item)
{
	CHAR choice, s;
	
	while(1){
		mainDisp();
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		printf("｜		%s  		｜\n",itemNameTbl[item][olditem[item]]);
		printf("｜		を装備済みです。   		｜\n");
		printf("｜						  		｜\n");
		printf("｜		変更しますか？	  		｜\n");
		for(s = 0; s < CHOICE_MAX; s++){
			choice = ((CHOICE_MAX + choice) % CHOICE_MAX);
			printf("｜	%s ・%s		  		｜\n",(s == choice)?"→":"  ",choiceName[s]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		if(CURSOR_ENTER == comSet(&choice)){
				if(choice == CHOICE_YES){ itemDecre(com, item); itemEnter(com, item); break;}
				else					{ itemSW = ON;	break; }
				break;	
		}
	}
}
//————————————————————————-
//		ステータス加算(アイテム)
//————————————————————————-
static void itemIncre(UCHAR com, UCHAR item)
{
	player.strength	+= itemStuTbl[item][com][STATUS_STRENGTH];
	player.defence	+= itemStuTbl[item][com][STATUS_DEFENCE];
	player.maxHP	+= itemStuTbl[item][com][STATUS_HP];
	player.maxMP	+= itemStuTbl[item][com][STATUS_MP];
	player.agility	+= itemStuTbl[item][com][STATUS_AGILITY];
	player.luck		+= itemStuTbl[item][com][STATUS_RUCK];
	olditem[item]	 = com;
	itemAll			|= ((0x01 << item) & 0x0f);
	(itemAll == 0x0f)? (itemSW = ON) : (itemSW = OFF);
}
//————————————————————————-
//		ステータス減算(アイテム)
//————————————————————————-
static void itemDecre(UCHAR com, UCHAR item)
{
	player.strength	-= itemStuTbl[item][olditem[item]][STATUS_STRENGTH];
	player.defence	-= itemStuTbl[item][olditem[item]][STATUS_DEFENCE];
	player.maxHP	-= itemStuTbl[item][olditem[item]][STATUS_HP];
	player.maxMP	-= itemStuTbl[item][olditem[item]][STATUS_MP];
	player.agility	-= itemStuTbl[item][olditem[item]][STATUS_AGILITY];
	player.luck		-= itemStuTbl[item][olditem[item]][STATUS_RUCK];		
}	
/*	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	戦闘関連処理
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
//————————————————————————-
//			 戦闘前ステータス基準値
//————————————————————————-
static void baseSet(void)
{
	defCnt = 3;
	base.strength	= player.strength;
	base.defence	= player.defence;
	base.maxHP		= player.maxHP;
	base.maxMP		= player.maxMP;
	base.agility	= player.agility;	
	base.luck		= player.luck;			
}
//————————————————————————-
//			 戦闘前ステータス基準値
//————————————————————————-
static void baseReSet(UCHAR mob)
{
	UCHAR i;
	if(ATTACK_PLAYER == mob){
		for(i = 0; i < SKILL_MAX; i++){
			if((skillSW[mob][i] == ON)&&(skillKind[mob][i] == 0)){
				switch(i){
					case SKILL_1:
						player.strength	= base.strength;
						break;
					case SKILL_2:
						player.strength	= base.strength;
						break;
					case SKILL_3:
						player.strength	= base.strength;
						break;
					case SKILL_4:
						player.strength	= base.strength;
						break;
					case SKILL_5:
						player.strength	= base.strength;
						break;
					case SKILL_6:
						player.strength	= base.strength;
						break;
					case SKILL_7:
						player.strength	= base.strength;
						break;
					case SKILL_8:
						player.strength	= base.strength;
						break;					
				}
			}
		}
	}
	else{
		for(i = 0; i < SKILL_MAX; i++){
			if((skillSW[mob][i] == ON)&&(skillKind[mob][i] == 0)){
				switch(i){
					case SKILL_1:
						player.strength	= base.strength;
						break;
					case SKILL_2:
						player.strength	= base.strength;
						break;
					case SKILL_3:
						player.strength	= base.strength;
						break;
					case SKILL_4:
						player.strength	= base.strength;
						break;
					case SKILL_5:
						player.strength	= base.strength;
						break;
					case SKILL_6:
						player.strength	= base.strength;
						break;
					case SKILL_7:
						player.strength	= base.strength;
						break;
					case SKILL_8:
						player.strength	= base.strength;
						break;					
				}
			}
		}
	}
}
static void fightMain(void)
{
	int i, cnt = 0;
	CHAR ch, comf = 0, sw = OFF;
	enemySet();	
	while(1){
		dispcls();
		fightMeinDisp();
		if(cnt == 0){
			staDisp();
			dispcls();
			fightMeinDisp();
		}
		comf = (FIGHT_COM_MAX + comf) % FIGHT_COM_MAX;
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		for(i = 0; i < FIGHT_COM_MAX; i++){
			printf("｜		%s	%s		｜\n",(i == comf)?"→":" ",fightCommand[i]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		if(CURSOR_ENTER == comSet(&comf)){
			switch(comf){
				case FIGHT_COM_F:
					fightDisp();
					sw = ON;
					break;
				case FIGHT_COM_D:
					defenceDisp(&sw);
					break;
				case FIGHT_COM_S:
					skillChoice(&sw);
					break;
				case FIGHT_COM_I:
					break;
			}
			if(sw){
				enemyDisp();
			}
		}	
		cnt++;
	}
}
//————————————————————————-
//		戦闘ディスプレイ
//————————————————————————-
static void fightMeinDisp(void)
{		
	printf(	"＋ーーーー %s ーーーー＋",(playerAll == ON)?playerName[oldmob]:"未選択		");
	space();printf("＋ーーーーーーー敵ーーーーーー＋\n");
	if(player.maxHP		< 0)	player.maxHP	= 0;
	if(player.maxMP		< 0)	player.maxMP	= 0;
	printf("｜	%s:	%d				｜",statusName[STATUS_HP]		,player.maxHP	);space();
	printf("｜	%s:	%d		  ｜\n",statusName[STATUS_HP]			,enemy.maxHP	);
	printf("｜	%s:	%d				｜",statusName[STATUS_MP]		,player.maxMP	);space();
	printf("｜	%s:	%d			  ｜\n",statusName[STATUS_MP]		,enemy.maxMP	);
	
	printf(	"＋ーーーーーーーーーーーーーーー＋");space();printf(	"＋ーーーーーーーーーーーーーー＋");	
	enemySubDisp();
}
//————————————————————————-
//		ダメージ計算
//————————————————————————-
static SHORT damage(UCHAR mob, UCHAR skill)
{
	SHORT str, def, *hp, agi, lu;
	SHORT dam, dambase, oldHP;
	SHORT damMax = 10,damMin = 1;
	
	if(ATTACK_PLAYER == mob){
		str = player.strength;
		def = enemy.defence;
		hp  = &enemy.maxHP;
		agi = enemy.agility;
		lu  = player.luck;
	}
	else{
		str = enemy.strength;
		def = player.defence;
		hp = &player.maxHP;
		agi = player.agility;
		lu  = enemy.luck;
	}	
	// スキル使用
	if(ATTACK_NORMAL != skill)	skillCalc(mob, &str, &def, hp, &agi, &lu);
	// ダメージ計算		
	srand(time(NULL));
	dambase = str - (def / 2);
	if(dambase > damMax){		
		damMin = dambase / 4;
		damMax = dambase;
	}
	dam = damMin + rand() % (damMax - damMin);
	if(rand() % 500 < lu)	dam = dam*2;
	oldHP = *hp;
	*hp -= dam;
	if(*hp < 0){
		dam = oldHP;
		*hp = 0;
	}
	return (dam);
}
static SHORT lastSkill(UCHAR mob, UCHAR skill)
{	
	if(ATTACK_PLAYER == mob){
		player.strength	= player.strength * skillParaTbl[skill][0];  
		player.defence	= player.defence / skillParaTbl[skill][1];
 		player.maxHP	= player.maxHP + skillParaTbl[skill][2];
		player.agility	= player.agility * skillParaTbl[skill][3];
		player.luck		= player.luck * skillParaTbl[skill][4];
		player.maxMP	= 0;
	}
	else{
	}	
}	
//————————————————————————-
//		 スキル発動時攻撃計算
//————————————————————————-
static void skillCalc(UCHAR mob, SHORT *str, SHORT *def, SHORT *hp, SHORT *agi, SHORT *lu)
{
	UCHAR i;
	SHORT st, de, h, ag, l;
	
	for(i = 0; i < SKILL_MAX; i++){
		if((skillAll >> i) & 0x01)	break;
	}
	st = skillParaTbl[i][0];
	de = skillParaTbl[i][1];
	h  = skillParaTbl[i][2];
	ag = skillParaTbl[i][3];
	l  = skillParaTbl[i][4];
	
	if(st != 0){
		if(10 < st)							*str = *str + abs(st);
		else if(-10 > st)					*str = *str - abs(st);
		else if((10 > st)&&(0 < st))		*str = *str / abs(st);
		else if((-10 < st)&&(0 > st))		*str = *str * abs(st);
	}
	if(de != 0){
		if(10 < de)							*def = *def + abs(st);
		else if(-10 > de)					*def = *def - abs(de);
		else if((10 > de)&&(de > 0))		*def = *def / abs(st);
		else if((-10 < de)&&(de < 0))		*def = *def * abs(st);
	}
	if(h != 0){
		if(10 < h)							*hp = *hp + abs(h);
		else if(-10 > h)					*hp = *hp - abs(h);
		else if((10 > h)&&(h > 0))			*hp = *hp / abs(h);
		else if((-10 < h)&&(h < 0))			*hp = *hp * abs(h);
	}
	if(ag != 0){
		if(10 < ag)							*agi = *agi + abs(ag);
		else if(-10 > ag)					*agi = *agi - abs(ag);
		else if((10 > ag)&&(0 < ag))		*agi = *agi / abs(ag);
		else if((-10 < ag)&&(0 > ag))		*agi = *agi * abs(ag);
	}
	if(l != 0){
		if(10 < l)							*lu = *lu + abs(l);
		else if(-10 > l)					*lu = *lu - abs(l);
		else if((10 > l)&&(0 < l))			*lu = *lu / abs(l);
		else if((-10 < l)&&(0 > l))			*lu = *lu * abs(l);
	}
}
static void fightDisp()
{
	dispcls();
	fightMeinDisp();
	printf("＋ーーーーーーーーーーーーーーーーー＋\n");
	printf("｜	%sのこうげき!！  		｜\n",playerName[oldmob]);
	printf("＋ーーーーーーーーーーーーーーーーー＋\n");
	getch();
	dispcls();
	fightMeinDisp();
	srand(time(NULL));
	if(rand() % 500 < enemy.agility){
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		printf("｜		こうげきはかわされてしまった  ｜\n");
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");	
	}
	else{
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		printf("｜	%dのダメージを与えた！！  	｜\n",damage(ATTACK_PLAYER, ATTACK_NORMAL));
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
	}
	getch();
}

static void defenceDisp(CHAR *sw)
{
	CHAR s, choice, ch;
	
	if(defCnt <= 0){
		dispcls();
		fightMeinDisp();
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		printf("｜	これ以上は使用できません	｜\n");
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		getch();
		*sw = OFF;
	}
	else{
		while(1){
			dispcls();
			fightMeinDisp();
			printf("＋ーーーーーーーーーーーーーーー＋\n");
			printf("｜	防御力が2倍になります。		｜\n");
			printf("｜	(あと%D回使用できます)		｜\n",defCnt);
			printf("｜	使用しますか？				｜\n");
			for(s = 0; s < CHOICE_MAX; s++){
					choice = ((CHOICE_MAX + choice) % CHOICE_MAX);
					printf("｜	%s ・%s		  		｜\n",(s == choice)?"→":"  ",choiceName[s]);
			}
			printf("＋ーーーーーーーーーーーーーーー＋\n");
			if(CURSOR_ENTER  == comSet(&choice)){
				if(CHOICE_YES == choice){
					dispcls();
					fightMeinDisp();
					printf("＋ーーーーーーーーーーーーーーーー＋\n");
					printf("｜		相手の攻撃に備えています。｜\n");
					printf("＋ーーーーーーーーーーーーーーーー＋\n");
					player.defence = player.defence * 2; 
					defCnt = defCnt -1;
					getch();
					*sw = ON;
				}
				else{
					*sw = OFF;
				}
				break;
			}
		}
	}		
}
static void skillChoice(CHAR *sw)
{
	CHAR skill, s, jdg = OFF;
	
	while(1){
		dispcls();
		fightMeinDisp();	
		skill = (SKILL_MAX + skill) % SKILL_MAX;
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		for(s = 0; s < SKILL_MAX; s++){
			printf("｜	%s	%s 		  	｜\n",(s == skill)?"→":" ",skillNameTbl[s]);
		}
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		switch(comSet(&skill)){
			case CURSOR_ENTER:
				if(CHOICE_YES == skillEnter(skill)){
					*sw = ON;
					jdg = ON;
				}
				break;
			case CURSOR_BACK:
				*sw = OFF;
				jdg = ON;
				break;
		}
		if(jdg)	break;
	}	
}
static UCHAR skillEnter(CHAR skill)
{	
	CHAR s, choice;
	
	while(1){
		dispcls();
		fightMeinDisp();	
		printf("＋ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー＋\n");
		printf("｜	%s	｜\n",skillDescTbl[skill]);
		printf("｜	使用MP	%d															｜\n",skillParaTbl[skill][5]);
		printf("｜																		｜\n");
		printf("｜		使用しますか？		  								  			｜\n");
		for(s = 0; s < CHOICE_MAX; s++){
			choice = ((CHOICE_MAX + choice) % CHOICE_MAX);
			printf("｜	%s ・%s														｜\n",(s == choice)?"→":"  ",choiceName[s]);
		}
		printf("＋ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー＋\n");
		if(CURSOR_ENTER == comSet(&choice)){
			if(CHOICE_YES == choice){
				if(player.maxMP - (SHORT)(skillParaTbl[skill][5]) < 0){
					printf("＋ーーーーーーーーーーーーーーーーー＋\n");
					printf("｜	MPが足りません  				｜\n");
					printf("＋ーーーーーーーーーーーーーーーーー＋\n");
					getch();
					return(CHOICE_NO);
				}
				else if(ON == skillSW[ATTACK_PLAYER][skill]){
					printf("＋ーーーーーーーーーーーーーーーーー＋\n");
					printf("｜	まだ発動できません  				｜\n");
					printf("｜	発動可能まで残り%2dターン  		｜\n",skillKind[ATTACK_PLAYER][skill]);
					printf("＋ーーーーーーーーーーーーーーーーー＋\n");
					getch();
					return(CHOICE_NO);
				}
				skillAll = ((0x01 << skill) & 0xff);
				skillDisp(skill);
				return(CHOICE_YES);
			}
			return(CHOICE_NO);	
		}
	}		
}
static void skillDisp(CHAR skill)
{
	dispcls();
	fightMeinDisp();
	printf("＋ーーーーーーーーーーーーーーーーー＋\n");
	printf("｜	%sはスキル   		｜\n",playerName[oldmob]);
	printf("｜	%sを発動!！  		｜\n",skillNameTbl[skill]);
	printf("＋ーーーーーーーーーーーーーーーーー＋\n");
	player.maxMP = player.maxMP - (SHORT)(skillParaTbl[skill][5]);
	if(player.maxMP < 0)	player.maxMP = 0;
	skillKind[ATTACK_PLAYER][skill] = skillTurnTbl[skill];
	skillSW[]ATTACK_PLAYER[skill] = ON;
	getch();
	dispcls();
	fightMeinDisp();
	switch(skillAll){
		case SKL_1:
		case SKL_2:
		case SKL_3:
		case SKL_4:
			printf("＋ーーーーーーーーーーーーーーーーー＋\n");
			printf("｜	%dポイントのダメージを与えた！！  	｜\n",damage(ATTACK_PLAYER, ATTACK_SKILL));
			printf("＋ーーーーーーーーーーーーーーーーー＋\n");
			break;
		case SKL_5:
			printf("d\n");
			break;
		case SKL_6:
			printf("e\n");
			break;
		case SKL_7:
			printf("f\n");
			break;
		case SKL_8:
			printf("＋ーーーーーーーーーーーーーーーーー＋\n");
			printf("｜	%dポイント回復した｜\n",damage(ATTACK_PLAYER, ATTACK_SKILL));
			printf("＋ーーーーーーーーーーーーーーーーー＋\n");
			break;
	}
	skillAll = 0;
	getch();
}
static void enemyDisp()
{
	CHAR s, i;
	
	dispcls();
	fightMeinDisp();
	srand(time(NULL));
	s = rand() % 100;	
	if(s < 60){
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		printf("｜		てきのこうげき!！  		｜\n");
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		getch();
		dispcls();
		fightMeinDisp();
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		printf("｜	%dのダメージをうけた！！  	｜\n",damage(ATTACK_ENEMY, ATTACK_NORMAL));
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");	
		getch();
	}
	else if(s < 75){
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		printf("｜		てきは守りを固めた!！  		｜\n");
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		enemy.defence = enemy.defence * 2; 
		getch();
	}
	else if(s < 99){
		srand(time(NULL));
		i = rand() % SKILL_MAX;
		skillAll = ((skillAll >> i) & 0x01);	
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		printf("｜		てきはスキルを発動した!！  		｜\n");
		printf("｜		%s  		｜\n",skillDescEnTbl[i]);
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		getch();
		dispcls();
		fightMeinDisp();
		switch(skillAll){
			case SKL_1:
			case SKL_2:
			case SKL_3:
			case SKL_4:
				printf("＋ーーーーーーーーーーーーーーーーー＋\n");
				printf("｜	%dポイントのダメージを与えた！！  	｜\n",damage(ATTACK_PLAYER, ATTACK_SKILL));
				printf("＋ーーーーーーーーーーーーーーーーー＋\n");
				break;
			case SKL_5:
				printf("d\n");
				break;
			case SKL_6:
				printf("e\n");
				break;
			case SKL_7:
				printf("f\n");
				break;
			case SKL_8:
				printf("＋ーーーーーーーーーーーーーーーーー＋\n");
				printf("｜	%dポイント回復した｜\n",damage(ATTACK_PLAYER, ATTACK_SKILL));
				printf("＋ーーーーーーーーーーーーーーーーー＋\n");
				break;
		}
		skillAll = 0;
		getch();	
	}
	else{
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		printf("｜	てきは激怒した！！  				｜\n");
		printf("＋	（5ターンの間攻撃力が10倍）＋\n");
		printf("＋ーーーーーーーーーーーーーーーーー＋\n");
		getch();
	}		
}	
	
