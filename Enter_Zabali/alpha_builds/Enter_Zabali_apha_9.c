#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#define n 10
#define plusHp 20
#define plusStm 15

//float* stm = (float*)malloc(sizeof(float)); 
float stm=0,hp=0,mHp=0,mStm=0;
float spd=0,atk=0;
int score=0;
char playerClass='p';
int roomlvl = 1;
char room[10][10];
int playerPosX, playerPosY;
int steps;
float eHp=0,eSpd=0,eAtk=0;
int hPotions=0, sPotions=0;
int highest=0, lastSession=0, currentSession=0;

char path = 46;
char player = 153;
char wall = 219;
char door = 254;
char hPot = 72;
char sPot = 83;


int titleScreen(int p);
void mainGame();
void genRoom();
void printRoom();
int movePlayer(char a);
int moveCheck(char a);
int borderCheck(char a);
void color(int c);
void instructions();
void stats(int p);
void gotoxy(int x, int y);
void border(int p);
void comment(int p);
void endScreen();
void noWalls(int p);
void charSprite(char p);
int charSelect();
void combat(int p);
int diceRoll(int d);
void enemySprite(int p);
void enemyStats(int p);
void inventory(int p);
int missCheck();
void genBossRoom();
void bossBattle();
void UL();
void DL();
void highScores();
void guide();

int main(){
	
	DL();
	srand(time(NULL));
	int state=1;
	
	while(state==1){
		
		switch(titleScreen(1)){
			case '1':
				hPotions=0;
				sPotions=0;
				gotoxy(37,24);printf("Loading Game"); Sleep(1000);
				playerClass=charSelect();
				mainGame();
				endScreen();
				gotoxy(31,25);system("pause");
				break;
			case '2':
				gotoxy(37,24);printf("Loading Scores"); Sleep(1000);
				highScores();
				break;
			case '3':
				gotoxy(37,24);printf("Loading"); Sleep(1000);
				guide();
				system("pause");
				break;
			case '4':
				UL();
				printf("Exiting"); Sleep(1000);
				system("cls");
				return 0;
			//default:
			//	printf("Invalid"); Sleep(1000);
		}
	}
}

//////////////////////////////////////////////// FUNCTIONS /////////////////////////////////////////////////////////////////

void mainGame(){	//Function where the input for the movement is taken

	char act;
	int True=0;
	int i;
	int key = 1;
	steps=0;
	
	if(roomlvl<20)
		genRoom();
	else
		genBossRoom();
	
	border(2);
	
	while(True != -1 && (stm > 0 && stm >.9 ) && (hp > 0 && hp >.9)){
		
		if(stm<=5)
			color(32);
		else if(hp<=5)
			color(31);
		else
			color(0);
			
		printRoom();
		stats(1);
		instructions();
		charSprite(playerClass);
		
		do{
			act=getch();
			act=toupper(act);
			
			if(act=='X'){
				key= -1;
			}
			else if(act=='E'){
				key = 1;
				inventory(1);
				inventory(0);
				fflush(stdin);
				//break;	
			}
			else if(act=='W'||act=='A'||act=='S'||act=='D'){
				key=0;
			}
			else{
				
			}
		}while(key!=0 && key!= -1);
		
		if(key==-1){
			roomlvl=1;
			playerPosX = -1;
			True=-1;
			stm=-1;
		}
		else if(key==0){
			steps+=1;
			if(steps%5==0){
				if(diceRoll(10)<=4){
					comment(3);
					combat(1);	
				}
			}
			True = movePlayer(act);
		}
	}
	fflush(stdin);
}

int diceRoll(int d){
	
	return(rand()%d+1);
		
}

int missCheck(){
	int chance;
	
	if(eSpd>spd)
		chance=1;
	else
		chance=2;
		
	if(diceRoll(10)<=chance)
		return 0; ///Enemy attack missed
	else
		return 1; ///Enemy attack hit
}

void combat(int p){
	int N;
	
	if(p==1)
		N = diceRoll(8);
	else
		N=9;
		
	int chance;
	int crit;
	char action;
	enemyStats(N);
	enemySprite(N);
	gotoxy(29,22);printf("[1] Attack");
	gotoxy(29,23);printf("[2] Dodge");
	gotoxy(29,24);printf("[3] Run Away");
	
	do{
		fflush(stdin);
		action=getch();
		switch(action){
			case '1': //Attack action
				stm-=.25;
				
				if(diceRoll(100)<=5) /////5% chance to crit///////
					crit=2;
				else
					crit=1;
					
				if(eSpd>spd){
					comment(1);
					if(missCheck()==1){
						hp-=eAtk;
						stats(1);
						enemyStats(-1);
						enemyStats(0);
					}
					else{
						comment(11);
					}
					Sleep(500);
					if(eHp>0){
						if(crit==2)
							comment(12);
						else
							comment(9);
						eHp-=(atk*crit);
						stats(1);
						enemyStats(-1);
						enemyStats(0);
					}
				}
				else{
					if(crit==2)
						comment(12);
					else
						comment(9);
					eHp-=(atk*crit);
					stats(1);
					enemyStats(-1);
					enemyStats(0);
						Sleep(500);
					if(eHp>0){
						comment(1);
						if(missCheck()==1){
							hp-=eAtk;
							stats(1);
							enemyStats(-1);
							enemyStats(0);
						}
						else{
							comment(11);
						}
					}
				}
				break;
			case '2'://Dodge action
				stm-=.25;
				
				if(spd>eSpd)
					chance=8;
				else
					chance=5;
					
				if(diceRoll(10)<=chance){
					comment(10);
					inventory(0);
					inventory(2);
					inventory(0);
					gotoxy(29,22);printf("[1] Attack");
					gotoxy(29,23);printf("[2] Dodge");
					gotoxy(29,24);printf("[3] Run Away");
				}
				else{
					comment(7);
					comment(1);
					hp-=eAtk;
					stats(1);
				}
				break;
			case '3'://Run away action
				stm-=.25;
				
				if(N==9)
					chance=-1;
				else if(eHp<=(eHp/2))
					chance=8;	
				else
					chance=6;
					
					
				if(N==4){
					comment(6);
					eHp=-100;
				}
				
				else{
					if(diceRoll(10)<=chance){
						comment(6);
						eHp=-100;	
					}
					else{
						comment(8);
						comment(1);
						hp-=eAtk;
						stats(1);
					}
				}
				break;
		}
	}while(eHp>0 && (hp>0 && hp>.9) && (stm>0 && stm >.9));
	
	///////////////////////////////////////EFFORT VALUES////////////////////////////////////////
	if(eHp!=100){
		if(N==1 || N==6){
			mHp+=.2;
			score+=20;
		}
		else if(N==2 || N==8){
			atk+=.2;
			score+=30;	
		}
		else if(N==3 || N==7 || N==5){
			spd+=.2;
			score+=25;	
		}
		else if(N==4){
			mStm+=.5;
			mHp+=.5;
			score+=10;	
		}
		else if(N==9){
			room[1][1]=path;
			score+=1000;
		}
	}
	
	//Sleep(500);
	enemySprite(0);
}

void inventory(int p){
	char sel;
	
	if(p==0){
		for(int i=0;i<3;i++){
			gotoxy(29,22+i);printf("                                   ");	
		}
	}
	else if(p>=1){
		gotoxy(29,22);printf("[1] Health Potions: %d/10",hPotions);
		gotoxy(29,23);printf("[2] Stamina Potions: %d/10",sPotions);
		gotoxy(29,24);printf("[E] Exit");
	
		do{
			fflush(stdin);
			sel=getch();
			sel=toupper(sel);
			switch(sel){
				case '1':
					if(hPotions>0){
						hp+=plusHp;
						if(hp>mHp){
							hp-=(hp-mHp);	
						}
						hPotions-=1;
						stats(1);
						if(p==1){
							inventory(1);
							sel='E';
						}
						else
							sel='E';
						//break;
					}
					break;
				case '2':
					if(sPotions>0){
						stm+=plusStm;
						if(stm>mStm){
							stm-=(stm-mStm);	
						}
						sPotions-=1;
						stats(1);
						if(p==1){
							inventory(1);
							sel='E';
						}
						else
							sel='E';
						//break;
					}
					break;
			}
		}while(sel!='E');	
	}		
}

void enemyStats(int p){
	if(p==-1){
		gotoxy(29,18);printf("                                    ");
		gotoxy(29,19);printf("                                    ");
		gotoxy(29,20);printf("                                    ");
	}
	else if(p==1){//Goblin
		eHp=40;
		eAtk=5+diceRoll(6);
		eSpd=(spd*.5)+diceRoll(spd/2);
	}
	else if(p==2){//Beholder
		eHp=35;
		eAtk=2+diceRoll(6);
		eSpd=(spd*.5)+diceRoll(spd/2);
	}
	else if(p==3){//Skeleton
		eHp=20;
		eAtk=1+diceRoll(6);
		eSpd=(spd*.7)+diceRoll(spd/2);
	}
	else if(p==4){//Slime
		eHp=60;
		eAtk=1;
		eSpd=(spd*.1);
	}
	else if(p==5){//Wererat
		eHp=40;
		eAtk=3+diceRoll(6);
		eSpd=(spd*.55)+diceRoll(spd/2);
	}
	else if(p==6){//Giant Spider
		eHp=25;
		eAtk=2+diceRoll(6);
		eSpd=(spd*.5)+diceRoll(spd/2);
	}
	else if(p==7){//Vampire
		eHp=30;
		eAtk=2+diceRoll(6);
		eSpd=(spd*.65)+diceRoll(spd/2);
	}
	else if(p==8){//Orc
		eHp=35;
		eAtk=7+diceRoll(6);
		eSpd=(spd*.6)+diceRoll(spd/2);
	}
	else if(p==9){//Boss
		eHp=129;
		eAtk=23;
		eSpd=26;
	}
	gotoxy(29,18);printf("Health: %.0f",eHp);
	gotoxy(29,19);printf("Attack: %.0f",eAtk);
	gotoxy(29,20);printf("Speed : %.0f",eSpd);
}

void noWalls(int p){
	int i,j,k;
	
	if(p == 1){
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				room[i][j] = '0';
			}
		}
		
		for(i=7; i<10; i++){
			for(j=7; j<10; j++){
				room[i][j] = '0';
			}
		}
		
		for(i=0;i<10;i++){
			for(j=i;j<=i+1;j++){
				for(k=i;k<j+1;k++){
					room[j][k] = '0';
				}
			}
		}
	}
	else if(p == 2){
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				room[i][j] = path;
			}
		}
		
		for(i=7; i<10; i++){
			for(j=7; j<10; j++){
				room[i][j] = path;
			}
		}
		for(i=0;i<10;i++){
			for(j=i;j<=i+1;j++){
				for(k=i;k<j+1;k++){
					room[j][k] = path;
				}
			}
		}
	}
}

void genRoom(){ //Generates the positions in the room
	
	int i, roomX, roomY;
	int pots=0;
	
	for(i=0; i<n; i++){
		for(int j = 0; j<n; j++){
			room[i][j] = path;
		}
	}
	
	noWalls(1);
	
	for(i=0; i<=(n*2); i++){
		roomX=rand()%n;
		roomY=rand()%n;    
		
		if(room[roomY][roomX] == wall){
			i-=1;
		}
		else if(room[roomY][roomX] == path){
			room[roomY][roomX] = wall;
		}
	}
	noWalls(2);
	
	do{
		roomX=rand()%n;
		roomY=rand()%n;
		if(room[roomY][roomX] == path){
			if(roomlvl%2==0){
				if(pots<2){
					room[roomY][roomX] = sPot;
					pots+=1;	
				}
				else{
					room[roomY][roomX] = hPot;
					pots+=1;	
				}
			}
			else{
				room[roomY][roomX] = sPot;
				pots+=2;
			}
		}
	}while(pots<4);
	
	room[0][0] = player;
	playerPosX = 0;
	playerPosY = 0;
	room[n-1][n-1] = door;
}

void printRoom(){	//Prints out the board

	int k;
	for(int i=0; i<n; i++){
		gotoxy(7,4+i);
		for(int j=0; j<n; j++){
			printf("%c ", room[i][j]);
		}
		
	}
	
}

int charSelect(){ ///Selects your Claass/Character 
	char sel;
	char ans;
	border(1);
	gotoxy(33,7);printf("[ SELECT YOUR CLASS ]");
	gotoxy(33,9);printf("[1] Plebian");
	gotoxy(33,10);printf("[2] Knight");
	gotoxy(33,11);printf("[3] Mage");
	gotoxy(33,12);printf("[4] Thief");
	do{
		fflush(stdin);
		sel=getch();
	}while(sel!='1' && sel!='2' && sel!='3' && sel !='4');
	
	switch(sel){
		case '1': //////Plebian/////
			charSprite(sel);
			mHp=hp=45;
			mStm=stm=45;
			atk=15;
			spd=15;
			break;
		case '2': ////////Knight////////
			charSprite(sel);
			mHp=hp=50;
			mStm=stm=40;
			atk=20;
			spd=15;
			break;
		case '3': ///////mage/////////
			charSprite(sel);
			mHp=hp=45;
			mStm=stm=40;
			atk=20;
			spd=15;
			break;
		case '4': ////////Thief/////////
			charSprite(sel);
			mHp=hp=40;
			mStm=stm=45;
			atk=15;
			spd=20;
			break;
		default:
			gotoxy(10,20);printf("Invalid Selection");Sleep(1000);
			charSelect();	
	}
	
	comment(sel);
	do{
		fflush(stdin);
		ans=getch();
		ans=toupper(ans);
		if(ans=='Y'){
			playerClass=sel;
			return sel;
		}
		else if(ans=='N'){
			charSelect();
		}
	}while(ans!='N');
}

void genBossRoom(){// ,'$' ,wall
	for(int i=1;i<9;i++){
		for(int j=1;j<9;j++){
			room[i][j] = '$';	
		}
	}
	for(int i=2;i<10;i++){
		room[0][i] = wall;
	}
	for(int i=2;i<10;i++){
		room[i][0] = wall;
	}
	for(int i=1;i<10;i++){
		room[i][9] = wall;
	}
	for(int i=1;i<10;i++){
		room[9][i] = wall;
	}
	room[8][8] = 'O';
	room[1][1] = 'B';
	room[0][0] = player;
	room[0][1] = path;
	room[1][0] = path;
	playerPosX = 0;
	playerPosY = 0;
}

/////////////////////////////////////////////// MOVEMENT FUNCTIONS /////////////////////////////////////////////////////////

int movePlayer(char a){ //Moves the player
	
	int tempX = playerPosX;
	int tempY = playerPosY;
	int T,t=0;
	
	if(a == 'W'){
		//printf("Moving up");Sleep(1000);
		playerPosY -= 1;
	}
	else if(a == 'A'){
		//printf("Moving left");Sleep(1000);
		playerPosX -= 1;
	}
	else if(a == 'S'){
		//printf("Moving down");Sleep(1000);
		playerPosY += 1;
	}
	else if(a == 'D'){
		//printf("Moving right");Sleep(1000);
		playerPosX += 1;
	}
	
	T = moveCheck(a);

	if(T >= 1 && borderCheck(a) == 1){
		char temp;
		if(T==2){
			
			room[playerPosY][playerPosX] = room[tempY][tempX];
			room[tempY][tempX] = path;
			
		}
		else if(T==1){//swap positions
			stm-=.25;
			temp = room[tempY][tempX];
			room[tempY][tempX] = room[playerPosY][playerPosX];
			room[playerPosY][playerPosX] = temp;
		}
		
		
		return T;	
	}
	else{
		playerPosX = tempX;
		playerPosY = tempY;
		
		return T;	
	}
	
}

int moveCheck(char a){	// Check if the next position is a wall or a door
	char s;
	if(room[playerPosY][playerPosX] == wall){
		//comment(1);
		return 0;
	}
	else if(room[playerPosY][playerPosX] == hPot){
		comment(4);

		if(hPotions<10){
			hPotions+=1;
		}
		else{
			comment(5);
			hp+=plusHp;
			if(hp>mHp){
				hp-=(hp-mHp);	
			}
		}
		
		return 2;
	}
	else if(room[playerPosY][playerPosX] == sPot){
		comment(4);
		if(sPotions<10){
			sPotions+=1;	
		}
		else{
			comment(5);
			stm+=plusStm;
			if(stm>mStm){
				stm-=(stm-mStm);
			}
		}
			
		return 2;
	}
	else if(room[playerPosY][playerPosX] == door){
		room[playerPosY][playerPosX] = player;
		room[8][9] = path;
		room[9][8] = path;
		printRoom();
		comment(2);
		roomlvl += 1;
		mainGame();
	}
	else if(room[playerPosY][playerPosX] == 'B'){
		gotoxy(29,18); system("pause");
		comment(13);
		combat(0);
		printRoom();
	}
	else if(room[playerPosY][playerPosX] == '$'){
		comment(14);
		hp=-1000;
	}
	else
		return 1;
}

int borderCheck(char a){	// Check if the next position is the edge or corner of the room
	
	//Corners
	if(playerPosX < 0 && playerPosY < 0 && (a == 'W' || a == 'A')){
		//comment(3);
		return 0;	
	}
	else if(playerPosX < 0 && playerPosY > 9 && (a == 'S' || a == 'A')){
		//comment(3);
		return 0;
	}
	else if(playerPosX > 9 && playerPosY < 0 && (a == 'W' || a == 'D')){
		//comment(3);
		return 0;	
	}
	else if(playerPosX > 9 && playerPosY > 9 && (a == 'S' || a == 'D')){
		//comment(3);
		return 0;	
	}
	//Edges
	else{
		if(playerPosX < 0 && a == 'A'){
			//comment(3);
			return 0;
		}
		else if(playerPosX > 9 && a == 'D'){
			//comment(3);
			return 0;	
		}
		else if(playerPosY < 0 && a == 'W'){
			//comment(3);
			return 0;	
		}
		else if(playerPosY > 9 && a == 'S'){
			//comment(3);
			return 0;	
		}
	}
	
	return 1;
}

/////////////////////////////////////////////////////////////////G R A P H I C S//////////////////////////////////////////////

void gotoxy(int x, int y){
	printf("\e[%d;%df", y, x);
}

void color(int c){
	if(c==0)//RESET//
		printf("\033[0m");
	else if(c==131)//RED//
		printf("\033[1;31m");
	else if(c==132)//GREEN//
		printf("\033[1;32m");
	else if(c==133)//YELLOW//
		printf("\033[1;33m");
	else if(c==134)//BLUE//
		printf("\033[1;34m");
	else if(c==31)//DARK RED//
		printf("\033[0;31m");
	else if(c==32)//DARK GREEN//
		printf("\033[0;32m");
	else if(c==33)//DARK YELLOW//
		printf("\033[0;33m");
	else if(c==34)//DARK BLUE//
		printf("\033[0;34m");
}

void border(int p){
	int i, j;
	
	system("cls");
	
	if(p>=0){
		gotoxy(3,2);printf("%c", 201);
		gotoxy(89,2);printf("%c", 187);
		gotoxy(3,28);printf("%c", 200);
		gotoxy(89,28);printf("%c", 188);
		
		for(i = 0; i<85; i++){
			gotoxy(4+i,2);printf("%c", 205);
			gotoxy(4+i,28);printf("%c", 205);	
			
		}
		
		for(i=0; i<25; i++){
			gotoxy(3,3+i);printf("%c", 186);
			gotoxy(89,3+i);printf("%c", 186);
		}
	}
	if(p==1||p==2){
		/////////////////////////////PROTAG PORTRAIT///////////////////////
		gotoxy(5,16);printf("%c", 201);
		for(int i=0;i<21;i++)
			printf("%c", 205);
		printf("%c", 187);
	
		for(int i=0;i<10;i++){
			gotoxy(27,17+i);printf("%c", 186);
			gotoxy(5,17+i);printf("%c", 186);
		}
	
		gotoxy(5,27);printf("%c", 200);
		for(int i=0;i<21;i++)
			printf("%c", 205);
		printf("%c", 188);
	}
	if(p==2){////////////////////////////////////////DUNGEON PORTRAIT///////////////////////////////
		
		gotoxy(5,3);printf("%c", 201);
		for(i=0;i<=20;i++){
			printf("%c",205);	
		}
		printf("%c", 187);
		
		for(i=0;i<10;i++){
			gotoxy(5,4+i);printf("%c", 186);
			gotoxy(27,4+i);printf("%c", 186);	
		}
		
		gotoxy(5,14);printf("%c", 200);
		for(i=0;i<=20;i++){
			printf("%c", 205);	
		}
		printf("%c", 188);
		
		//TOP BAR//
		gotoxy(30,9);
		for(i=0;i<57;i++)
			printf("%c",205);
		
		////////////////////////////ENEMY PROTRAIT//////////////////////////////////
		gotoxy(65,16);printf("%c", 201);
		for(int i=0;i<21;i++)
			printf("%c", 205);
		printf("%c", 187);
		
		for(int i=0;i<10;i++){
			gotoxy(87,17+i);printf("%c", 186);
			gotoxy(65,17+i);printf("%c", 186);
		}
	
		gotoxy(65,27);printf("%c",200);
		for(int i=0;i<21;i++)
			printf("%c", 205);
		printf("%c", 188);
	
		//BOTTOM BAR//	
		gotoxy(29,21);
		for(int i=0;i<35;i++)
			printf("%c", 205);
	}
}

int titleScreen(int p){
	int sel;
	
	border(0);
	
	gotoxy(12,5);printf("             ______  ___   _  _______  ______  ______\n");
	gotoxy(12,6);printf("            |  ____||   | | ||__   __||  ____||  __  \\");
	gotoxy(12,7);printf("            | |__   | |\\ \\| |   | |   | |__   | |__| |");
	gotoxy(12,8);printf("            |  __|  | | \\   |   | |   |  __|  |  __  /");
	gotoxy(12,9);printf("            | |____ | |  \\  |   | |   | |____ | |  \\ \\");
	gotoxy(12,10);printf("            |______||_|   |_|   |_|   |______||_|   \\_\\");
	gotoxy(12,11);printf("        _______    _____   ______   _____   _       _______");
	gotoxy(12,12);printf("        \\____  /  /  _  \\ |  _   | /  _  \\ | |     |__   __|");
	gotoxy(12,13);printf("            / /  |  |_|  || |_|  ||  |_|  || |        | |");
	gotoxy(12,14);printf("           / /   |  ___  ||  _  < |  ___  || |        | |");
	gotoxy(12,15);printf("          / /____| |   | || |_|  || |   | || |____  __| |__");
	gotoxy(12,16);printf("         /______/|_|   |_||______||_|   |_||______||_______|");
	
	if(p==1){
		gotoxy(37,20);printf("[1] START");
		gotoxy(37,21);printf("[2] HIGH SCRORES");
		gotoxy(37,22);printf("[3] GUIDE");
		gotoxy(37,23);printf("[4] EXIT");
	}
	else if(p==2){
		gotoxy(32,20);printf("ALL TIME BEST ---------- %4d",highest);
		gotoxy(32,21);printf("LAST SESSION BEST: ----- %4d",lastSession);
		gotoxy(32,22);printf("CURRENT SESSION BEST: -- %4d",currentSession);
		gotoxy(32,23);printf("[4] BACK");
	}
	fflush(stdin);
	sel=getch();
	
	return sel;

}

void guide(){
	border(0);
	gotoxy(5,4);printf("\tThere are talks around town of stolen treasure which is apparently hoarded in ");
	gotoxy(5,5);printf("the depths of Zabali at [level 20] but no one is sure. Your quest is to obtain");
	gotoxy(5,6);printf("this rumored wealth, along the way you'll encouter different enemies which will");
	gotoxy(5,7);printf("give your stats bonuses once defeated. The local bookkeeper luckily has a record");
	gotoxy(5,8);printf("of the aforementioned bonuses:");
	
	gotoxy(5,10);printf("-> [Goblin] & [Giant Spider] gives +.2 to MAX HEALTH");
	gotoxy(5,12);printf("-> [Beholder] & [Orc] gives +.2 to ATTACK");
	gotoxy(5,14);printf("-> [Skeleton], [Wererat] & [Vampire] gives +.2 to SPEED");
	gotoxy(5,16);printf("-> [Slime] gives +.5 to MAX STAMINA & MAX HEALTH");
	
	gotoxy(5,18);printf("//////////////////////////////// BONUS TIP ///////////////////////////////////////");
	
	gotoxy(5,20);printf("->Your [attack] against enemies has a small chance to [crit]/deal double damage");
	
	gotoxy(5,22);printf("-> [Dodging] during [combat] will cause you to evade the enemy's [attack] and will");
	gotoxy(5,23);printf("give you a chance to use [stamina or health potions]");
	
	gotoxy(5,25);printf("-> [Failing] your [dodge] or [run away] attempt will leave you vulnerable to the");
	gotoxy(5,26);printf("[enemy's attack]  ");
}

void highScores(){
	int hs=1;
	while(hs==1){
		switch(titleScreen(2)){
			case '4':
				hs=0;
				break;
		}
	}
}

void instructions(){
	gotoxy(30,10);printf("-> [W][A][S][D] to move        -> H = Heal %d Health", plusHp);
	gotoxy(30,11);printf("-> [E] for Inventory           -> S = Heal %d stamina",plusStm);
	gotoxy(30,12);printf("-> press [X] to doubt");
	gotoxy(30,13);printf("-> %c = door to the next level & %c = walls", door, wall);
	//gotoxy(30,14);printf("-> %c = walls",wall);
}

void stats(int p){
	
	if(p==1){
	////////////PlayerName///////////////
		if(playerClass=='1'){
			gotoxy(30,4);printf("[Aljon the Plebian]");
		}
		else if(playerClass=='2'){
			gotoxy(30,4);printf("[Es-Teves the Knight]");
		}
		else if(playerClass=='3'){
			gotoxy(30,4);printf("[Willow the Mage]");
		}
		else if(playerClass=='4'){
			gotoxy(30,4);printf("[Huaki the Thief]");	
		}
	
	//////Hit Points//////
		gotoxy(38,5); 
		for(int i=0;i<mHp/2/2;i++)
			printf(" ");
		printf("|%3.0f/%3.0f",hp,mHp);
		gotoxy(30,5); printf("Health :");

		for(int i=0; i<(hp/2/2); i++){
			printf("%c", 254);
		}	
	
	////Stamina//////	
		gotoxy(38,6);
		for(int i=0;i<mStm/2/2;i++){
			printf(" ");
		}
		printf("|%3.0f/%3.0f", stm,mStm);
		gotoxy(30,6); printf("Stamina:");
		
		for(int i=0; i<(stm/2/2); i++){
			printf("%c", 254);
		}
	
	//////////////////////printing other stats/////////////////////
		gotoxy(30,7);printf("                                     ");
		gotoxy(30,8);printf("                                     ");
		gotoxy(30,7); printf("Attack : %.0f",atk);
		gotoxy(30,8); printf("Speed  : %.0f",spd);
		gotoxy(45,7); printf("Room: %d", roomlvl);
		gotoxy(45,8); printf("Score: %d", score);
	}
}

void comment(int p){
	gotoxy(7,15);
	if(p==1){ ////enemy attacking////
		printf("ENEMY [attack]!"); Sleep(500); gotoxy(7,15);
		printf("               ");
	}
	else if(p==2){ ////entering/////
		printf("Entering next level..."); Sleep(1000);
		score+=2;
	}
	else if(p==3){ ////can't move////
		printf("An ENEMY appears!"); Sleep(1000); gotoxy(7,15);
		printf("                 ");
	}
	else if(p==4){
		printf("Potion picked up."); Sleep(500); gotoxy(7,15);
		printf("                 ");	
	}
	else if(p==5){
		printf("Inventory full. Drinking potion."); Sleep(1500); gotoxy(7,15);
		printf("                                ");	
	}
	else if(p==6){
		printf("You [Ran away] like a chicken!"); Sleep(1500); gotoxy(7,15);
		printf("                              ");
	}
	else if(p==7){
		printf("[Dodge] FAILED"); Sleep(1000); gotoxy(7,15);
		printf("              ");	
	}
	else if(p==8){
		printf("[Run away] FAILED"); Sleep(1000); gotoxy(7,15);
		printf("                 ");	
	}
	else if(p==9){
		printf("YOU [attack]!"); Sleep(500); gotoxy(7,15);
		printf("             ");	
	}
	else if(p==10){
		printf("YOU [dodged]"); Sleep(1000); gotoxy(7,15);
		printf("            "); 	
	}
	else if(p==11){
		printf("ENEMY [attack] MISSED"); Sleep(1500); gotoxy(7,15);
		printf("                     ");	
	}
	else if(p==12){
		printf("YOU [attack] [CRIT]!!"); Sleep(1000); gotoxy(7,15);
		printf("                     ");
	}
	else if(p==13){
		gotoxy(29,18);
		printf("TE RE RET TET TET TET TE RE RE RET"); Sleep(2000); gotoxy(29,18);
		printf("                                  ");
	}
	else if(p==14){
		printf("THE RUMORS ARE TRUEEEEEE!"); Sleep(3000); gotoxy(29,18);
		printf("                         ");
	}
	//////////Class Descriptions///////////////////
	else if(p==49){ ///Plebian
		gotoxy(29,17);printf("\tAljon was once a noble man. That didn't lasted when");
		gotoxy(29,18);printf("he was caught coercing a child to do unspeakable acts. ");
		gotoxy(29,19);printf("Now exiled, and pushing his luck to find the rumored");
		gotoxy(29,20);printf("tresure inside Zabali to start a new life or so he thought");
		gotoxy(29,22);printf("Health:  %.0f\t\tAttack: %.0f",mHp,atk);
		gotoxy(29,23);printf("Stamina: %.0f\t\tSpeed:  %.0f",mStm,spd);
		
		gotoxy(29,25);printf("Select Aljon the Pleb [Y/N]?");	
	}
	else if(p==50){
		gotoxy(29,17);printf("\tEs-Teves is a loving and caring man. The city of");
		gotoxy(29,18);printf("Santos was hit by a raging flood, and is having a rough");
		gotoxy(29,19);printf("time recovering than expected. One day he overheard a");
		gotoxy(29,20);printf("rumored tresure found inside the depths of Zabali so");
		gotoxy(29,21);printf("he set forth in finding it in order to help in the city's");
		gotoxy(29,22);printf("recovery but are the rumors true?");
		
		gotoxy(29,24);printf("Health:  %.0f\t\tAttack: %.0f",mHp,atk);
		gotoxy(29,25);printf("Stamina: %.0f\t\tSpeed:  %.0f",mStm,spd);
		
		gotoxy(29,27);printf("Select Es-Teves the Knight [Y/N]?");
	}
	else if(p==51){
		gotoxy(29,17);printf("\tWillow's village was hit by a mysterious plague, she");
		gotoxy(29,18);printf("read in the necronomicon that there is a magical stone");
		gotoxy(29,19);printf("alongside the treasures of Zabali that can cure this");
		gotoxy(29,20);printf("plague. So she went on a quest to obtain this so called");
		gotoxy(29,21);printf("healing stone inside Zabali, but is it still there?");
		
		gotoxy(29,23);printf("Health:  %.0f\t\tAttack: %.0f",mHp,atk);
		gotoxy(29,24);printf("Stamina: %.0f\t\tSpeed:  %.0f",mStm,spd);
		
		gotoxy(29,26);printf("Select Willow the Mage [Y/N]?");
	}
	else if(p==52){
		gotoxy(29,17);printf("\tHuaki is not your typical thief for he is in love with");
		gotoxy(29,18);printf("with a princess named Cleo-in. Wanting to prove his worth");
		gotoxy(29,19);printf("to the princess he went on a quest to find the lost");
		gotoxy(29,20);printf("treasures of her Kingdom which was rumored to be hidden in");
		gotoxy(29,21);printf("the inner most depths of Zabali, but will he prevail?");
		
		gotoxy(29,23);printf("Health:  %.0f\t\tAttack: %.0f",mHp,atk);
		gotoxy(29,24);printf("Stamina: %.0f\t\tSpeed:  %.0f",mStm,spd);
		
		gotoxy(29,26);printf("Select Huaki the Thief [Y/N]?");
	}
}

void endScreen(){
	border(0);
	color(0);
	gotoxy(25,5);printf("   _______ ");
	gotoxy(25,6);printf(" /  _____ \\   _____   ___    ___  ______");
	gotoxy(25,7);printf("| |      |_| /  _  \\ |   \\  /   ||  ____|");
	gotoxy(25,8);printf("| |    ____ |  |_|  || |\\ \\/ /| || |");
	gotoxy(25,9);printf("| |   |__  ||  ___  || | \\__/ | ||  __|");
	gotoxy(25,10);printf("|  \\_____| || |   | || |      | || |____");
	gotoxy(26,11);printf("\\________/ |_|   |_||_|      |_||______|");
	gotoxy(26,12);printf("  ______");
	gotoxy(26,13);printf(" /  __  \\  ___      ___ ______  ______");
	gotoxy(26,14);printf("|  |  |  | \\  \\    /  /|  ____||  __  \\");
	gotoxy(26,15);printf("|  |  |  |  \\  \\  /  / | |__   | |__| |");
	gotoxy(26,16);printf("|  |  |  |   \\  \\/  /  |  __|  |  __  /");
	gotoxy(26,17);printf("|  |__|  |    \\    /   | |____ | |  \\ \\");
	gotoxy(26,18);printf(" \\______/      \\__/    |______||_|   \\_\\");
	
	gotoxy(30,20);printf("       -> Score: %4d <-",score);
	
	if(score>currentSession){
		currentSession=score;	
	}
	if(currentSession>highest){
		highest=currentSession;	
	}
	
}

void charSprite(char p){
	
	if(p=='1'){
		//
		gotoxy(6,17);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177);
		gotoxy(6,18);printf("%c%c%c%c|%c%c%c%c%c%c%c%c%c%c\\%c%c%c%c%c",177,177,177,177,178,178,178,178,178,178,178,178,178,178,177,177,177,177,177);
		gotoxy(6,19);printf("%c%c/%c%c%c%c%c%c%c%c%c%c%c%c%c|%c%c%c%c",177,177,178,178,178,178,178,178,178,178,178,178,178,178,178,177,177,177,177);
		gotoxy(6,20);printf("%c|%c%c%c%c%c       %c/%c%c%c%c%c",177,178,178,178,178,178,178,177,177,177,177,177);
		gotoxy(6,21);printf("%c%c\\%c%c| (.  .) |%c%c%c%c%c%c",177,177,178,178,177,177,177,177,177,177);
		gotoxy(6,22);printf("%c%c%c%c\\_ ___.___/%c%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177);
		gotoxy(6,23);printf("%c%c/%c%c%c|   |%c%c\\%c%c%c%c%c%c%c",177,177,176,176,176,176,176,177,177,177,177,177,177,177);
		gotoxy(6,24);printf("%c|%c%c%c%c%c|_|%c%c%c%c%c\\%c%c%c%c%c",177,176,176,176,176,176,176,176,176,176,176,177,177,177,177,177);
		gotoxy(6,25);printf("%c|%c|%c%c%c%c%c%c%c%c%c|%c|%c%c%c%c%c",177,176,176,176,176,176,176,176,176,176,176,176,177,177,177,177,177);
		gotoxy(6,26);printf("%c| |%c%c%c%c%c%c%c%c%c| |%c%c%c%c%c",177,176,176,176,176,176,176,176,176,176,177,177,177,177,177);
	}
	if(p=='2'){
		//
		gotoxy(6,17);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177);
		gotoxy(6,18);printf("%c%c%c%c%c/________\\%c%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177,177	);
		gotoxy(6,19);printf("%c%c%c%c/  ___  __ \\%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177);
		gotoxy(6,20);printf("%c%c%c| \\|_. \\/._|/%c%c%c%c%c",177,177,177,177,177,177,177,177);
		gotoxy(6,21);printf("%c%c%c%c\\    \\ -/  |%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177);
		gotoxy(6,22);printf("%c%c%c%c%c\\___|__|_/%c%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177,177);
		gotoxy(6,23);printf("%c%c/   __|%c%c%c|__   \\%c%c",177,177,176,186,176,177,177);
		gotoxy(6,24);printf("%c/   |%c%c%c%c%c%c%c%c%c|\\  \\%c",177,176,205,205,205,206,205,205,205,176,177);
		gotoxy(6,25);printf("|  |    |%c%c%c|    \\  |",176,186,176,177);
		gotoxy(6,26);printf("|__|\\___|%c%c%c|___/|__|",176,186,176);
	}
	if(p=='3'){
		//
		gotoxy(6,17);printf("%c%c%c/   ________\\%c%c%c%c%c",177,177,177,177,177,177,177,177);
		gotoxy(6,18);printf("%c%c/  _/   ______  \\%c%c",177,177,177,177);
		gotoxy(6,19);printf("%c/__/  __/$$$$$$\\_/%c%c",177,177,177);
		gotoxy(6,20);printf("|/%c/  /$$$$$$$$$$$|%c%c",177,177,177);
		gotoxy(6,21);printf("%c%c%c\\_$$$|      |$$|%c%c",177,177,177,177,177);
		gotoxy(6,22);printf("%c%c%c/$$$/  ^  ^ |$$\\%c%c",177,177,177,177,177);
		gotoxy(6,23);printf("%c%c|$$$$\\___-___/$$$|%c",177,177,177);
		gotoxy(6,24);printf("%c%c\\$$/%c%c%c\\   /%c%c\\$/%c%c",177,177,176,176,176,176,176,177,177);
		gotoxy(6,25);printf("%c%c%c\\|%c%c%c%c%c\\|/%c%c%c%c|%c%c%c",177,177,177,176,176,176,176,176,176,176,176,176,177,177,177);
		gotoxy(6,26);printf("%c%c%c%c|\\%c%c%c%c%c%c%c%c%c%c/|%c%c%c",177,177,177,177,176,176,176,176,176,176,176,176,176,176,177,177,177);
	}
	if(p=='4'){
		//
		gotoxy(6,17);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177);
		gotoxy(6,18);printf("%c%c%c/    __  __  \\%c%c%c%c",177,177,177,177,177,177,177);
		gotoxy(6,19);printf("%c%c|/\\  /  \\/  \\  |%c%c%c",177,177,177,177,177);
		gotoxy(6,20);printf("%c%c%c%c|  | .___. \\ |%c%c%c",177,177,177,177,177,177,177);
		gotoxy(6,21);printf("%c%c%c%c\\  |_/%c%c%c\\_| |%c%c%c",177,177,177,177,176,176,176,177,177,177);
		gotoxy(6,22);printf("%c%c%c%c%c\\__\\%c%c%c%c%c/_/%c%c%c%c",177,177,177,177,177,176,176,176,176,176,177,177,177,177);
		gotoxy(6,23);printf("%c%c%c/%c\\ \\  \\%c/   /%c\\%c%c",177,177,177,176,176,176,177,177);
		gotoxy(6,24);printf("%c%c%c|%c%c\\__\\___/_/%c%c|%c%c",177,177,177,176,176,176,176,177,177);
		gotoxy(6,25);printf("%c%c%c|%c|%c%c%c%c|/O/%c%c|%c|%c%c",177,177,177,176,176,176,176,176,176,176,176,177,177);
		gotoxy(6,26);printf("%c%c%c|%c|%c%c%c%c/O/|%c%c|%c|%c%c",177,177,177,176,176,176,176,176,176,176,176,177,177);
	}
}

void enemySprite(int p){
	if(p==0){
		for(int i=0;i<4;i++){
			gotoxy(29,17+i);printf("                                    ");
		}
		for(int i=0;i<5;i++){
			gotoxy(29,22+i);printf("                                    ");	
		}
		for(int i=0;i<10;i++){
			gotoxy(66,17+i);
				printf("                     ");

		}
	}
	else if(p==1){
		gotoxy(29,17);printf("[GOBLIN]");
		gotoxy(66,17);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,18);printf("%c%c%c/|%c/         \\%c/|%c",178,178,178,178,178,178);
		gotoxy(66,19);printf("%c%c%c| |  0\\ /0   |/ |%c",178,178,178,178);
		gotoxy(66,20);printf("%c%c%c%c\\|   <       _/%c%c",178,178,178,178,178,178);
		gotoxy(66,21);printf("%c%c%c%c%c| _/\\_/\\_  |%c%c%c%c",178,178,178,178,178,178,178,178,178);
		gotoxy(66,22);printf("%c%c/%c%c\\__________|%c%c\\%c",178,178,176,176,176,176,178);
		gotoxy(66,23);printf("%c|%c%c%c%c%c%c%c\\~~/%c%c%c%c%c%c%c\\",178,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176);
		gotoxy(66,24);printf("%c|%c%c\\%c%c%c\\ ~_\\%c%c%c%c/%c%c|",178,176,176,176,176,176,176,176,176,176,176,176);
		gotoxy(66,25);printf("%c|~~|%c%c%c%c\\/%c%c%c%c%c%c|~~|",178,176,176,176,176,176,176,176,176,176,176);
		gotoxy(66,26);printf("%c|__|%c%c%c%c%c%c%c%c%c%c%c%c|__|",178,176,176,176,176,176,176,176,176,176,176,176,176);
		
	}
	else if(p==2){
		gotoxy(29,17);printf("[BEHOLDER]");
		gotoxy(66,17);printf("%c||\\\\%c%c%c\\\\%c%c||%c%c%c%c//%c",178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,18);printf("%c\\0%c\\\\/ _  __    //%c%c",178,178,178,178);
		gotoxy(66,19);printf("%c%c%c%c/   |\\/ |   // \\%c",178,178,178,178,178);
		gotoxy(66,20);printf("%c%c%c%c|   |%c__|      |%c",178,178,178,178,219,178);
		gotoxy(66,21);printf("====| __________   |%c",178);
		gotoxy(66,22);printf("%c%c%c%c||%c/\\%c/\\%c/\\%c|  |%c",178,178,178,178,176,176,176,176,178);
		gotoxy(66,23);printf("%c%c%c//\\_______\\\\_||/%c%c",178,178,178,178,178,178);
		gotoxy(66,24);printf("%c%c%c||%c%c%c%c%c%c%c%c||%c||%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,25);printf("%c%c%c|_===0%c%c%c%c//%c\\\\%c%c%c",178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,26);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c0%c%c//%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
	}
	else if(p==3){
		gotoxy(29,17);printf("[SKELETON]");
		gotoxy(66,17);printf("%c%c%c%c%c%c%c/        \\%c%c%c%c",178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,18);printf("%c%c%c%c%c%c|  0\\ /0   |%c%c%c",178,178,178,178,178,178,178,178,178);
		gotoxy(66,19);printf("%c%c%c%c%c%c|    ^    |%c%c%c%c",178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,20);printf("%c%c%c%c%c%c%c\\ _|_|_ |%c%c%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,21);printf("%c%c%c%c%c%c%c|__|_|__/%c%c%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,22);printf("%c%c%c%c%c%c%c%c%c%c%c||%c%c%c%c%c%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,23);printf("%c%c%c%c|_|_________|_|%c%c",178,178,178,178,178,178);
		gotoxy(66,24);printf("%c%c%c%c%c||___| |___||%c%c%c",178,178,178,178,178,178,178,178);
		gotoxy(66,25);printf("%c%c%c%c%c|%c\\__|_|__/%c|%c%c%c",178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,26);printf("%c%c%c%c%c|%c%c%c%c%c||%c%c%c%c|%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
	}
	else if(p==4){
		gotoxy(29,17);printf("[SLIME]");
		gotoxy(66,17);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,18);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c/ \\%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,19);printf("%c%c%c%c%c%c%c%c%c%c%c%c/__   /%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,20);printf("%c%c%c%c/|        /|  \\%c%c",178,178,178,178,178,178);
		gotoxy(66,21);printf("%c%c%c/_|_______/ |  /%c%c",178,178,178,178,178);
		gotoxy(66,22);printf("%c%c|  |       | | /%c%c%c",178,178,178,178,178);
		gotoxy(66,23);printf("%c%c|  |.   . _|_|  \\%c%c",178,178,178,178);
		gotoxy(66,24);printf("%c%c| /   -    | / _/%c%c",178,178,178,178);
		gotoxy(66,25);printf("%c%c|/_________|/_/%c%c%c%c",178,178,178,178,178,178);
		gotoxy(66,26);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
	}
	else if(p==5){
		gotoxy(29,17);printf("[WERERAT]");
		gotoxy(66,17);printf("%c%c|%c\\%c%c%c%c%c/%c|%c%c%c%c%c%c%c%c",178,178,177,178,178,178,178,178,177,178,178,178,178,178,178,178,178);
		gotoxy(66,18);printf("%c%c\\%c/%c%c%c%c/%c%c/%c%c%c%c%c\\%c%c",178,178,177,176,176,176,176,177,177,176,176,176,176,176,178,178);
		gotoxy(66,19);printf("%c%c%c|%c0\\/0%c%c%c%c%c%c%c%c%c%c|%c",178,178,178,176,176,176,176,176,176,176,176,176,176,176,178);
		gotoxy(66,20);printf("%c%c/%c%c%c%c%c%c%c%c%c%c%c/%c%c%c%c|%c",178,178,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,178);
		gotoxy(66,21);printf("%c%cO%c%c%c%c%c/   |  |%c%c%c|%c",178,178,176,176,176,176,176,176,176,176,178);
		gotoxy(66,22);printf("%c%c%c|_|%c\\|_._|_._\\%c%c|%c",178,178,178,178,176,176,178);
		gotoxy(66,23);printf("%c%c%c%c%c%c%c|%c|%c_|_%c%c%c|%c|%c",178,178,178,178,178,178,178,176,176,176,176,176,176,178);
		gotoxy(66,24);printf("%c%c%c%c%c%c%c|%c|%c_|_%c%c%c|%c|%c",178,178,178,178,178,178,178,176,176,176,176,176,176,178);
		gotoxy(66,25);printf("%c%c%c%c%c%c%c|%c|%c_|_%c%c%c|%c|%c",178,178,178,178,178,178,178,176,176,176,176,176,176,178);
		gotoxy(66,26);printf("%c%c%c%c%c%c%c|%c|%c%c%c%c%c%c%c|%c|%c",178,178,178,178,178,178,178,176,176,176,176,176,176,176,176,176,178);
	}
	else if(p==6){
		gotoxy(29,17);printf("[GIANT SPIDER]");
		gotoxy(66,17);printf("%c|  |     |     |  |%c",178,178,178);
		gotoxy(66,18);printf("/\\  \\  _______  /  /\\");
		gotoxy(66,19);printf("%c/\\_ /  :\\ /:  \\__/\\%c",176,176);
		gotoxy(66,20);printf("/%c/%c|  __: :__  |%c\\%c\\",178,176,176,178);
		gotoxy(66,21);printf("%c/%c/| /%c%c\\_/%c%c\\ |\\%c\\%c",178,176,176,176,176,176,176,178);
		gotoxy(66,22);printf("/%c/%c/\\|  |%c|  |/\\%c\\%c\\",176,177,178,177,176);
		gotoxy(66,23);printf("%c/%c/%c/|  |%c|  |\\%c\\%c\\%c",176,177,176,178,176,177,176);
		gotoxy(66,24);printf("%c|%c|%c|%c\\/%c%c%c\\/%c|%c|%c|%c",176,178,176,178,178,178,178,178,176,178,176);
		gotoxy(66,25);printf("%c|%c|%c|%c%c%c%c%c%c%c%c%c|%c|%c|%c",176,178,176,178,178,178,178,178,178,178,178,178,176,178,176);
		gotoxy(66,26);printf("%c|%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c|%c",176,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,176);
	}
	else if(p==7){
		gotoxy(29,17);printf("[VAMPIRE]");
		gotoxy(66,17);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,18);printf("%c%c%c|%c%c%c%c%c%c%c%c%c%c%c%c%c|%c%c%c",178,178,178,177,177,177,177,177,177,177,177,177,177,177,177,177,178,178,178);
		gotoxy(66,19);printf("%c%c%c%c\\%c  0\\/0  %c%c%c|%c%c%c",178,178,178,178,177,177,177,177,178,178,178);
		gotoxy(66,20);printf("%c%c%c%c%c| ______  \\%c|%c%c%c",178,178,178,178,178,177,178,178,178);
		gotoxy(66,21);printf("%c%c%c%c%c||_V__V_|  |%c%c%c%c",178,178,178,178,178,178,178,178,178);
		gotoxy(66,22);printf("%c%c%c%c%c\\__________/%c%c%c%c",178,178,178,178,178,178,178,178,178);
		gotoxy(66,23);printf("%c%c%c%c%c%c%c%c%c|  :|%c%c%c%c%c%c%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,24);printf("%c%c%c%c/\\__/%c\\/%c%c\\___/\\%c",178,178,178,178,176,176,176,178);
		gotoxy(66,25);printf("%c%c%c%c|%c|%c%c%c|%c%c%c%c%c%c|%c|%c",178,178,178,178,176,176,176,176,176,176,176,176,176,176,176,178);
		gotoxy(66,26);printf("%c%c%c%c|%c\\%c%c%c|%c%c%c%c%c%c|%c|%c",178,178,178,178,176,176,176,176,176,176,176,176,176,176,176,178);
	}
	else if(p==8){
		gotoxy(29,17);printf("[ORC]");
		gotoxy(66,17);printf("%c%c%c%c%c%c%c%c/|%c%c%c%c%c%c%c%c/\\%c",178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(66,18);printf("%c%c%c%c%c%c/         \\/ |%c",178,178,178,178,178,178,178);
		gotoxy(66,19);printf("%c%c%c%c%c|___ ___   /  /%c",178,178,178,178,178,178);
		gotoxy(66,20);printf("%c%c%c%c%c\\|0\\ /0| | __/%c%c",178,178,178,178,178,178,178);
		gotoxy(66,21);printf("%c%c%c/%c%c\\  V    / /    ",178,178,178,176,176);
		gotoxy(66,22);printf("%c%c|%c%c%c|/\\___/\\ |   / ",178,178,176,176,176);
		gotoxy(66,23);printf("%c%c|%c%c/\\_______/   |  ",178,178,176,176);
		gotoxy(66,24);printf("%c%c%c| | \\ \\ |      |  ",178,178,178);
		gotoxy(66,25);printf("%c%c%c\\  \\_\\_\\|__.___/\\ ",178,178,178);
		gotoxy(66,26);printf("%c%c%c|__||_|\\_\\__|__||_",178,178,178);
	}
	else if(p==9){
		gotoxy(29,17);printf("[SANS-ZAKYR]");
		gotoxy(66,17);printf("%c%c%c%c%c/         \\%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177);
		gotoxy(66,18);printf("%c%c%c%c|           |%c%c%c%c",177,177,177,177,177,177,177,177);
		gotoxy(66,19);printf("%c%c%c%c|   %c   %c   |%c%c%c%c",177,177,177,177,219,178,177,177,177,177);
		gotoxy(66,20);printf("%c%c%c%c%c| _  ^  _ |%c%c%c%c%c",177,177,177,177,177,177,177,177,177,177);
		gotoxy(66,21);printf("%c%c%c%c%c| \\%c%c%c%c%c/ |%c%c%c%c%c",177,177,177,177,177,178,177,178,177,178,177,177,177,177,177);
		gotoxy(66,22);printf("%c%c/%c%c%c\\_______/%c%c%c\\%c%c",177,177,178,178,178,178,178,178,177,177);
		gotoxy(66,23);printf("/%c%c%c\\%c%c%c\\ _ /%c%c%c/%c%c%c\\",176,176,176,178,178,178,178,178,178,176,176,176);
		gotoxy(66,24);printf("|%c%c%c|%c%c|%c| |%c|%c%c|%c%c%c|",176,176,176,176,176,177,177,176,176,176,176,176);
		gotoxy(66,25);printf("|%c%c/%c%c%c|%c| |%c|%c%c%c\\%c%c|",176,176,176,176,176,177,177,176,176,176,176,176);
		gotoxy(66,26);printf("|%c%c|%c%c%c|%c| |%c|%c%c%c|%c%c|",176,176,176,176,176,177,177,176,176,176,176,176);
	}
}

//////////////////////////////////////////////////////File Saving/////////////////////////////////////////////////////

void UL(){
	FILE *fp;
	
	fp=fopen("highScores.fl","w+");
	fprintf(fp,"%d\n%d", highest, currentSession);

	fclose(fp);
}

void DL(){
	FILE *fp;
	
	fp=fopen("highScores.fl","r+");
	fscanf(fp,"%d\n%d", &highest, &lastSession);
	
	fclose(fp);
}
