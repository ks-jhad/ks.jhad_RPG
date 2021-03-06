/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	キャラクター関連処理
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.>
#include <time.h>
#include <conio.h>
#include "main_IF.h"
#include "mainTbl.h"


//------------------------------------------------
//   内部関数
//------------------------------------------------
static UCHAR playerSet(UCHAR mob);
static void playerReady(UCHAR mob);
static void playerEnter(UCHAR mob);
static void playerIncre(UCHAR mob);

//————————————————————————
//	内部変数
//————————————————————————





//————————————————————————-
//		キャラ選択
//————————————————————————-
void playerMain(void)
{
	CHAR mob, sw;
		
	while(1){		
		mainDisp();
		mob = (PLAYER_NAME_MAX + mob) % PLAYER_NAME_MAX;
		printf("＋ーーーーキャラ を 選択ーーーー＋\n");
		for(int i = 0; i < PLAYER_NAME_MAX; i++){
			printf("｜		%s	%s			｜\n",(i == mob)?"→":" ",playerNameTbl[i]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		switch(comSet(&mob)){
			case CURSOR_ENTER:
				if(CHOICE_YES == playerSet(mob)){
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
//		キャラクター設定
//————————————————————————-
static UCHAR playerSet(UCHAR mob)
{
	CHAR i, choice;
	
	while(1){ 
		mainDisp();	
		printf(	"＋ーーーーーーーーーーーーーーー＋\n");
		for(i = 0; i < STATUS_MAX; i++){
			printf("｜	%s:	%d	→	%d		｜\n"
			,statusName[i]
			,(playerAll == ON)?(playerStuTbl[oldmob][i]):(0)
			,playerStuTbl[mob][i]);
		}
		printf(	"＋ーーーーーーーーーーーーーーー＋\n");
		printf("｜								｜\n");
		printf("｜		%s  				｜\n",playerName[mob]);
		printf("｜		にしますか？	  		｜\n");
		choice = ((CHOICE_MAX + choice) % CHOICE_MAX);
		for(i = 0; i < CHOICE_MAX; i++){
			printf("｜	%s ・%s		 		｜\n",(i == choice)?"→":"  ",choiceName[i]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		if(CURSOR_ENTER == comSet(&choice)){
			if(choice == CHOICE_YES){	
				if(playerAll == ON){
					playerReady(mob);
				}
				else{
					playerEnter(mob);
				}
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
		printf("｜		%s						｜\n",playerName[oldmob]);
		printf("｜		を選択済みです。		｜\n");
		printf("｜						 				｜\n");
		printf("｜		変更しますか？	 			｜\n");
		for(s = 0; s < CHOICE_MAX; s++){
			choice = ((CHOICE_MAX + choice) % CHOICE_MAX);
			printf("｜	%s ・%s				｜\n",(s == choice)?"→":"  ",choiceName[s]);
		}
		printf("＋ーーーーーーーーーーーーーーー＋\n");
		if(CURSOR_ENTER == comSet(&choice)){
			if(choice == CHOICE_YES){	
				playerEnter(mob);
			}
			break;
		}	
	}
}
//————————————————————————-
//		ステータス加算(キャラクター)
//————————————————————————-
static void playerIncre(UCHAR mob)
{
	if(playerAll == ON){
		player.strength	-= playerStuTbl[oldmob][STATUS_STRENGTH];
		player.defence	-= playerStuTbl[oldmob][STATUS_DEFENCE];
		player.maxHP		-= playerStuTbl[oldmob][STATUS_HP];
		player.maxMP		-= playerStuTbl[oldmob][STATUS_MP];
		player.agility	-= playerStuTbl[oldmob][STATUS_AGILITY];
		player.luck			-= playerStuTbl[oldmob][STATUS_RUCK];
	}
	player.strength	+= playerStuTbl[mob][STATUS_STRENGTH];
	player.defence	+= playerStuTbl[mob][STATUS_DEFENCE];
	player.maxHP		+= playerStuTbl[mob][STATUS_HP];
	player.maxMP		+= playerStuTbl[mob][STATUS_MP];
	player.agility	+= playerStuTbl[mob][STATUS_AGILITY];
	player.luck			+= playerStuTbl[mob][STATUS_RUCK];
	oldmob = mob;
	playerAll = ON;
}
 