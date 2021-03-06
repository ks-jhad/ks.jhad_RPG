/*
——————————————————
 メイン 処理
——————————————————
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
static void itemMain(void);
static void itemSet(UCHAR item);
static UCHAR itemChoice(UCHAR com, UCHAR item);
static void itemReady(UCHAR com, UCHAR item);
static void itemEnter(UCHAR com, UCHAR item);
static void itemIncre(UCHAR com, UCHAR item);
static void itemDecre(UCHAR com, UCHAR item);

//————————————————————————
//	内部変数
//————————————————————————


