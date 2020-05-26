#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#define n 10

//float* stm = (float*)malloc(sizeof(float)); 
float stm=0,hp=0,mHp=0,mStm=0;
float spd=0,atk=0;
int score=0;
char playerClass='p';
int roomlvl = 1;
char room[10][10];
int playerPosX, playerPosY;

char path = 46;
char player = 153;
char wall = 219;
char door = 254;
char hPot = 72;
char sPot = 83;


int titleScreen();
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
void combat();
int diceRoll(int d);
int steps;
void enemySprite(int p);

int main(){

	srand(time(NULL));
	int state=1;
	
	while(state==1){
		
		switch(titleScreen()){
			case '1':
				printf("Loading Game"); Sleep(1000);
				playerClass=charSelect();
				mainGame();
				endScreen();
				gotoxy(31,25);system("pause");
				break;
			case '2':
				printf("Loading Scores"); Sleep(1000);
				break;
			case '3':
				printf("Exiting"); Sleep(1000);
				system("cls");
				return 0;
			default:
				printf("Invalid"); Sleep(1000);
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
	
	genRoom();
	border(2);
	
	while(True != -1 && stm > 0 && hp > 0){
		
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
			else if(act=='W'||act=='A'||act=='S'||act=='D'){
				key=0;
			}
			else{
				key = 1;
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
					combat();	
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

void combat(){
	enemySprite(diceRoll(8));
}

void enemySprite(int p){
	if(p==1){
		gotoxy(29,17);printf("[GOBLIN]");
		gotoxy(29,18);system("pause");
		gotoxy(29,17);printf("                      ");
		gotoxy(29,18);printf("                               ");
	}
	else if(p==2){
		gotoxy(29,17);printf("[BEHOLDER]");
		gotoxy(29,18);system("pause");
		gotoxy(29,17);printf("                      ");
		gotoxy(29,18);printf("                               ");
	}
	else if(p==3){
		gotoxy(29,17);printf("[SKELETON]");
		gotoxy(29,18);system("pause");
		gotoxy(29,17);printf("                      ");
		gotoxy(29,18);printf("                               ");
	}
	else if(p==4){
		gotoxy(29,17);printf("[SLIME]");
		gotoxy(29,18);system("pause");
		gotoxy(29,17);printf("                      ");
		gotoxy(29,18);printf("                               ");
	}
	else if(p==5){
		gotoxy(29,17);printf("[WERERAT]");
		gotoxy(29,18);system("pause");
		gotoxy(29,17);printf("                      ");
		gotoxy(29,18);printf("                               ");
	}
	else if(p==6){
		gotoxy(29,17);printf("[GIANT SPIDER]");
		gotoxy(29,18);system("pause");
		gotoxy(29,17);printf("                      ");
		gotoxy(29,18);printf("                               ");
	}
	else if(p==7){
		gotoxy(29,17);printf("[VAMPIRE]");
		gotoxy(29,18);system("pause");
		gotoxy(29,17);printf("                      ");
		gotoxy(29,18);printf("                               ");
	}
	else if(p==8){
		gotoxy(29,17);printf("[ORC]");
		gotoxy(29,18);system("pause");
		gotoxy(29,17);printf("                      ");
		gotoxy(29,18);printf("                               ");
	}
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
			if(pots==0){
				room[roomY][roomX] = sPot;
				
				if(roomlvl%5==0)
					pots+=1;
				else
					pots+=2;	
			}
			else if(pots==1){
				room[roomY][roomX] = hPot;
				pots+=1;	
			}
		}
	}while(pots<2);
	
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
	fflush(stdin);
	sel=getch();
	
	switch(sel){
		case '1': //////Plebian/////
			charSprite(sel);
			mHp=hp=50;
			mStm=stm=60;
			atk=10;
			spd=15;
			hp-=10;
			break;
		case '2': ////////Knight////////
			charSprite(sel);
			mHp=hp=60;
			mStm=stm=60;
			atk=15;
			spd=10;
			hp-=10;
			break;
		case '3': ///////mage/////////
			charSprite(sel);
			mHp=hp=40;
			mStm=stm=40;
			atk=20;
			spd=15;
			hp-=10;
			break;
		case '4': ////////Thief/////////
			charSprite(sel);
			mHp=hp=50;
			mStm=stm=45;
			atk=15;
			spd=20;
			hp-=10;
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
			stm-=.5;
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
	if(room[playerPosY][playerPosX] == wall){
		//comment(1);
		return 0;
	}
	else if(room[playerPosY][playerPosX] == hPot){
		hp+=5;
		if(hp>mHp){
			hp-=(hp-mHp);	
		}
		return 2;
	}
	else if(room[playerPosY][playerPosX] == sPot){
		stm+=10;
		if(stm>mStm){
			stm-=(stm-mStm);
		}
		return 2;
	}
	else if(room[playerPosY][playerPosX] == door){
		comment(2);
		roomlvl += 1;
		mainGame();
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

int titleScreen(){
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
	
	gotoxy(37,20);printf("[1] START");
	gotoxy(37,21);printf("[2] HIGH SCRORES");
	gotoxy(37,22);printf("[3] EXIT\n");
	/*gotoxy(4,30);printf("Selection: ");
	scanf(" %d", &sel);*/
	gotoxy(38,23);sel=getch();
	
	return sel;

}

void instructions(){
	gotoxy(30,10);printf("-> use WASD to move                -> H = health potions");
	gotoxy(30,11);printf("-> %c are walls                     -> S = stamina potions", wall);
	gotoxy(30,12);printf("-> %c is the door to the next level", door);
	gotoxy(30,13);printf("-> press X to doubt     steps: %d",steps);
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
	if(p==1){ ////wall////
			printf("A wall is in the way"); Sleep(1000);
	}
	else if(p==2){ ////entering/////
			printf("Entering next level..."); Sleep(1000);
			score+=2;
	}
	else if(p==3){ ////can't move////
			printf("Can't move there"); Sleep(1000);
	}
	else if(p==4){
		printf("got potion"); Sleep(1000);	
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
	
	if(playerPosX==-1){
		gotoxy(30,20);printf("         -> You DIED <-");	
	}
	else if(stm==0){
		gotoxy(30,20);printf("-> You DIED due to EXHAUSTION <-");	
	}
	else if(hp==0){
		gotoxy(30,20);printf("-> You DIED due to BLOOD LOSS <-");	
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
