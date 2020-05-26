#include <stdio.h>

void gotoxy(int x, int y){
	printf("\e[%d;%df", y, x);
}

void border(int p){
	int i, j;
	
	if(p>0){
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
		
		gotoxy(30,9);
		for(i=0;i<57;i++)
			printf("%c",205);
	}
	
	{/////////////////////////////PROTAG PORTRAIT///////////////////////
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
	
	//////////////////////////////BOTTOM SPACER///////////////////////////////
	gotoxy(29,21);
	for(int i=0;i<35;i++)
		printf("%c", 205);
	
	{////////////////////////////ENEMY PROTRAIT//////////////////////////////////
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
	}
		
}

int main(){
	system("cls");
	border(2);
		gotoxy(29,17);printf("[SanZakyr]");
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
	
	gotoxy(5,35);
}
