#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int n = 10;
int roomlvl = 1;
int playerlvl = 0;
char room[10][10];
int playerPosX = 0, playerPosY = 0;
int h;
int s;
char path = 46;
char player = 153;
char wall = 219;//206
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
void endScreen(int p);

int main(){
	
	srand(time(NULL));
	int state=1;
	
	while(state==1){
		h=100;
		s=50;
		switch(titleScreen()){
			case 1:
				system("cls");
				mainGame();
				fflush(stdin);
				printf("\n\n");system("pause");
				break;
			case 2:
				printf("High Scores"); Sleep(1000);
				break;
			case 3:
				printf("Exit"); Sleep(1000);
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
	
	genRoom();
	
	do{
		//system("cls");
		border(1);
		printRoom();
		stats();
		instructions();
		
		
		act=getch();
			act=toupper(act);
		//printf("Your action = %c\n", act);
		True = movePlayer(act);	
	}while(True != -1 && s > 0);
	
	endScreen(1);
	fflush(stdin);
	
}

void genRoom(){ //Generates the positions in the room
	
	int roomX, roomY;
	
	for(int i=0; i<n; i++){
		for(int j = 0; j<n; j++){
			room[i][j] = path;
		}
	}
	
	room[0][0] = player;
	playerPosX = 0;
	playerPosY = 0;
	room[n-1][n-1] = door;
	
	for(int i=0; i<n*(1); i++){
		roomX=rand()%n+0;
		roomY=rand()%n+0;
		
		if(room[roomY][roomX] == wall){
			i--;
		}
		else if(room[roomY][roomX] == path){
			room[roomY][roomX] = wall;	
		}	
	}
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
		s-=1;
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

int borderCheck(char a){	// Check if the next position is the edge of the room
	
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
	gotoxy(37,22);printf("[3] EXIT");
	fflush(stdin);
	gotoxy(4,30);printf("Selection: ");
	scanf(" %d", &sel);
	
	return sel;

}

void instructions(){
	gotoxy(30,11);printf("-> use WASD to move");
	gotoxy(30,12);printf("-> %c are walls", wall);
	gotoxy(30,13);printf("-> %c is the door to the next level", door);
}

void stats(){
	int i;
	gotoxy(30,4); printf("Room: %d", roomlvl);
	gotoxy(30,6); printf("Player Level: %d", playerlvl);
	gotoxy(30,7); printf("Health:\t");
		color(2);
		
		if(h==1)
			printf("|");
		else if(h<=3)
			printf("%c DANGER", 219);
		else{
			for(i=0; i<(h/2/2); i++){
			printf("%c", 219);
		}	
		}
		color(1);
		
		gotoxy(30,8); printf("Stamina:\t");
		color(3);
		if(s==1)
			printf("|");
		else if(s<=3)
			printf("%c DANGER", 219);
		else{
			for(i=0; i<(s/2/2); i++){
				printf("%c", 219);
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
}

void endScreen(int p){
	border(1);
	gotoxy(25,5);printf("   _______ ");
	gotoxy(25,6);printf(" /  _____ \\   _____   ___    ___  ______   ");
	gotoxy(25,7);printf("| |      |_| /  _  \\ |   \\  /   ||  ____| ");
	gotoxy(25,8);printf("| |    ____ |  |_|  || |\\ \\/ /| || |__    ");
	gotoxy(25,9);printf("| |   |__  ||  ___  || | \\__/ | ||  __|   ");
	gotoxy(25,10);printf("|  \\_____| || |   | || |      | || |____  ");
	gotoxy(26,11);printf(" \\________/ |_|   |_||_|      |_||______|  ");
	gotoxy(26,12);printf("  ______");
	gotoxy(26,13);printf(" /  __  \\  ___      ___ ______  ______");
	gotoxy(26,14);printf("|  |  |  | \\  \\    /  /|  ____||  __  \\");
	gotoxy(26,15);printf("|  |  |  |  \\  \\  /  / | |__   | |__| |");
	gotoxy(26,16);printf("|  |  |  |   \\  \\/  /  |  __|  |  __  /");
	gotoxy(26,17);printf("|  |__|  |    \\    /   | |____ | |  \\ \\");
	gotoxy(26,18);printf(" \\______/      \\__/    |______||_|   \\_\\");
	
}
