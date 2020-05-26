#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#define n 10

char playerClass;
int roomlvl = 1;
int playerlvl = 1;
char room[10][10];
int playerPosX, playerPosY;
float h;
float s;
char path = 46;
char player = 153;
char wall = 219;
char door = 254;


int titleScreen();
void mainGame();
void genRoom();
void printRoom();
int movePlayer(char a);
int moveCheck(char a);
int borderCheck(char a);
void color(int c);
void instructions();
void stats();
void gotoxy(int x, int y);
void border(int p);
void comment(int p);
void endScreen();
void noWalls(int p);
void charSprite(char p);
int charSelect();

int main(){

	srand(time(NULL));
	int state=1;
	
	while(state==1){
		h=50;
		s=4;
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
	genRoom();
	
	while(True != -1 && s > 0 && h > 0){
		border(1);
		printRoom();
		stats();
		instructions();
		charSprite(playerClass);
		
		do{
			act=getch();
			act=toupper(act);
			
			if(act=='`'){
				key= -1;
				playerPosX = -1;	
			}
			else if(act=='W'||act=='A'||act=='S'||act=='D'){
				key=0;
			}
			else{
				key = 1;
			}
		}while(key!=0 && key!= -1);
		
		if(key==0)
			True = movePlayer(act);
		else if(key==-1){
			True=-1;	
		}
		
	}
	fflush(stdin);
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
	
	for(i=0; i<n; i++){
		for(int j = 0; j<n; j++){
			room[i][j] = path;
		}
	}
	
	noWalls(1);
	
	for(i=0; i<=(n*2); i++){
		roomX=rand()%n+0;
		roomY=rand()%n+0;    
		
		if(room[roomY][roomX] == wall){
			i-=1;
		}
		else if(room[roomY][roomX] == path){
			room[roomY][roomX] = wall;
		}
	}
	
	noWalls(2);
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

/////////////////////////////////////////////// MOVEMENT FUNCTIONS /////////////////////////////////////////////////////////

int movePlayer(char a){ //Moves the player
	
	int tempX = playerPosX;
	int tempY = playerPosY;
	int T;
	
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
	
	if(T == 1 && borderCheck(a) == 1){
		
		//swap positions
		s-=.5;
		char temp = room[tempY][tempX];
		room[tempY][tempX] = room[playerPosY][playerPosX];
		room[playerPosY][playerPosX] = temp;
		
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
		comment(1);
		return 0;
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
		comment(3);
		return 0;	
	}
	else if(playerPosX < 0 && playerPosY > 9 && (a == 'S' || a == 'A')){
		comment(3);
		return 0;
	}
	else if(playerPosX > 9 && playerPosY < 0 && (a == 'W' || a == 'D')){
		comment(3);
		return 0;	
	}
	else if(playerPosX > 9 && playerPosY > 9 && (a == 'S' || a == 'D')){
		comment(3);
		return 0;	
	}
	//Edges
	else{
		if(playerPosX < 0 && a == 'A'){
			comment(3);
			return 0;
		}
		else if(playerPosX > 9 && a == 'D'){
			comment(3);
			return 0;	
		}
		else if(playerPosY < 0 && a == 'W'){
			comment(3);
			return 0;	
		}
		else if(playerPosY > 9 && a == 'S'){
			comment(3);
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
	if(c==1)//RESET//
		printf("\033[0m");
	else if(c==2)//RED//
		printf("\033[0;31m");
	else if(c==3)//GREEN//
		printf("\033[0;32m");
}

void border(int p){
	int i, j;
	
	system("cls");
	
	if(p==1){
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
}

int titleScreen(){
	int sel;
	
	border(1);
	
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
	gotoxy(30,10);printf("-> use WASD to move");
	gotoxy(30,11);printf("-> %c are walls", wall);
	gotoxy(30,12);printf("-> %c is the door to the next level", door);
	gotoxy(30,13);printf("-> press ""`"" (tilde) to quit");
}

void stats(){
	int i;
	gotoxy(30,4); printf("Room: %d", roomlvl);
	gotoxy(30,6); printf("Player Level: %d", playerlvl);
	gotoxy(30,7); printf("Health: ");
		color(2);
		
		if(h==.5)
			printf("Critical Health!!");
		else if(h==1||h==1.5)
			printf("Critical Health!");
		else if(h==2||h==2.5)
			printf("%c DANGER!!", 254);
		else if(h==3||h==3.5)
			printf("%c DANGER!", 254);
		else{
			for(i=0; i<(h/2/2); i++){
			printf("%c", 254);
		}	
		}
		color(1);
		
		gotoxy(30,8); printf("Stamina:");
		color(3);
		if(s==.5)
			printf("Critical Stamina!!");	
		else if(s==1||s==1.5)
			printf("Critical Stamina!");
		else if(s==2||s==2.5)
			printf("%c DANGER!!", 254);
		else if(s==3||s==3.5)
			printf("%c DANGER!", 254);
		else{
			for(i=0; i<(s/2/2); i++){
				printf("%c", 254);
			}
		}
		color(1);
}

void comment(int p){
	gotoxy(7,15);
	if(p==1){ ////wall////
			printf("A wall is in the way"); Sleep(1000);
	}
	else if(p==2){ ////entering/////
			printf("Entering next level..."); Sleep(1000);
	}
	else if(p==3){ ////can't move////
			printf("Can't move there"); Sleep(1000);
	}
	//////////Class Descriptions///////////////////
	else if(p==49){ ///Plebian
		gotoxy(27,18);printf("\tAljon was once a noble man. That didn't lasted when");
		gotoxy(27,19);printf("he was caught coercing a child to do unspeakable acts. ");
		gotoxy(27, 20);printf("Now exiled, and pushing his luck to find the rumored");
		gotoxy(27, 21);printf("tresure inside Zabali to start a new life or so he thought");
		gotoxy(27, 23);printf("+ Pedo");
		gotoxy(27, 24);printf("- Respect");
		
		gotoxy(27,26);printf("Select Aljon the Pleb [Y/N]?");	
	}
	else if(p==50){
		gotoxy(27,18);printf("\tSir Zakyr was sent to Zabali by his King Ramon to");
		gotoxy(27,19);printf("retrieve the rumored tresure inside, but are the rumors true?");
		gotoxy(27,21);printf("+ Health");
		gotoxy(27,22);printf("- Stamina");
		
		gotoxy(27,25);printf("Select Sir Zakyr [Y/N]?");
	}
}

void endScreen(){
	border(1);
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
		gotoxy(30,20);printf("-> You RAN away like a CHICKEN <-");	
	}
	else if(s==0){
		gotoxy(30,20);printf("-> You DIED due to EXHAUSTION <-");	
	}
	else if(h==0){
		gotoxy(30,20);printf("-> You DIED due to BLOOD LOSS <-");	
	}
}

int charSelect(){
	char sel;
	char ans;
	border(1);
	gotoxy(33,7);printf("[ SELECT YOUR CLASS ]");
	gotoxy(33,9);printf("[1] Plebian");
	gotoxy(33,10);printf("[2] Knight");
	gotoxy(33,11);printf("[3] Mage (unavailable)");
	gotoxy(33,12);printf("[4] Thief (unavailable)");
	fflush(stdin);
	sel=getch();
	
	switch(sel){
		case '1':
			charSprite(sel);
			//comment(sel+10);
			break;
		case '2':
			charSprite(sel);
			
			break;
				
		default:
			gotoxy(10,20);printf("Invalid Selection");Sleep(1000);
			charSelect();	
	}
	
	comment(sel);
	ans=getch();
	ans=toupper(ans);
	if(ans=='Y'){
		return sel;
	}
	else
		charSelect();
}

void charSprite(char p){
	if(p=='1'){
		gotoxy(4,17);printf(" ____________________");
		gotoxy(4,18);printf("|     ___________    |");
		gotoxy(4,19);printf("|   _|%c%c%c%c%c%c%c%c%c%c%c\\   |",178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(4,20);printf("|  /%c%c%c%c%c%c%c%c%c%c%c%c%c%c|  |",178,178,178,178,178,178,178,178,178,178,178,178,178,178);
		gotoxy(4,21);printf("| |%c%c%c|        %c/    |",178,178,178,178);
		gotoxy(4,22);printf("|  \\%c%c|  *  *  |     |",178,178);
		gotoxy(4,23);printf("|   _|_     ___|     |");
		gotoxy(4,24);printf("|  /%c%c%c|   |%c\\_      |",176,176,176,176);
		gotoxy(4,25);printf("| |%c%c%c%c%c|_|%c%c%c%c\\     |",176,176,176,176,176,176,176,176,176,176);
		gotoxy(4,26);printf("| |%c%c%c%c%c%c%c%c%c%c%c%c%c|    |",176,176,176,176,176,176,176,176,176,176,176,176,176);
		gotoxy(4,27);printf("|_|%c%c%c%c%c%c%c%c%c%c%c%c%c|____|",176,176,176,176,176,176,176,176,176,176,176,176,176);
	}
	if(p=='2'){
		gotoxy(4,17);printf(" ____________________");
		gotoxy(4,18);printf("|%c%c%c%c%c%c%c%c%c/\\%c%c%c%c%c%c%c%c%c|",176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176);
		gotoxy(4,19);printf("|%c%c%c%c%c/________\\%c%c%c%c%c|",176,176,176,176,176,176,176,176,176,176);
		gotoxy(4,20);printf("|%c%c%c%c//_ ===== _\\%c%c%c%c|",176,176,176,176,176,176,176,176);
		gotoxy(4,21);printf("|%c%c%c| \\  =====  /%c%c%c%c|",176,176,176,176,176,176,176);
		gotoxy(4,22);printf("|%c%c%c%c\\ \\_______/|%c%c%c%c|",176,176,176,176,176,176,176,176);
		gotoxy(4,23);printf("|%c%c%c%c%c\\________/%c%c%c%c%c|",176,176,176,176,176,176,176,176,176,176);
		gotoxy(4,24);printf("|%c%c/   __|%c%c%c|__   \\%c|",176,176,176,186,176,176);
		gotoxy(4,25);printf("|%c/   |_%c%c%c%c%c%c%c_|\\  \\|",176,205,205,205,206,205,205,205);
		gotoxy(4,26);printf("||  |    |%c%c%c|    \\  |",176,186,176);
		gotoxy(4,27);printf("||__|____|%c%c%c|___ |__|",176,186,176);	
	}
}
