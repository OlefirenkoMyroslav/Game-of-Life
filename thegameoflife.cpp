#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#define COLOR_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)
#define COLOR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED)
#define COLOR_WARNING SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN) 
#define COLOR_BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE)
#define COLOR_RESET SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)
#define WHITE_BACKGROUND 0x007
#define GREEN_TEXT 10
#define WHITE_BACKGROUND 15
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
#define ATTR1 037
#define ATTR2 031
#define MAXSIZE 100
#define FOREGROUND_YELLOW 14
using namespace std;
HDC hdc;
HANDLE h;

char*m[]={"Play", "Rules","About","Exit"};	
char*m1[]={"6","7","8","9","10","11","12","13","14","15"};
char*m2[]={"Arrows","Read from file","Exit"};
char*m3[]={"Start game","Enter new grid","Save grid to file","Exit"};
int i,j,x,y;
string choice;
string suz3;
string suz4;
string suz5;
char suz1=10;
int suz=1;
int gridsize;
bool grid[MAXSIZE][MAXSIZE];
bool gridtwo[MAXSIZE][MAXSIZE];
void printgrid(bool grid[MAXSIZE][MAXSIZE], int gridsize);
void comparegrid(bool grid[MAXSIZE][MAXSIZE],bool gridtwo[MAXSIZE][MAXSIZE]);
void obnulgrid(bool grid[MAXSIZE][MAXSIZE]);
void check(bool grid[MAXSIZE][MAXSIZE]);
void stan(bool grid[MAXSIZE][MAXSIZE],int gridsize);
void entergrid(bool grid[MAXSIZE][MAXSIZE],int gridsize);
void savegrid(bool grid[MAXSIZE][MAXSIZE]);
void draw(HANDLE h, COORD c, int k, int n, int len);
void ramka(HANDLE h,COORD t,COORD b);
void Play();
void Rules();
void About();
void draw_gridsize(HANDLE h, COORD c, int k, int n, int len);
void arrows();
void file();
void draw_way(HANDLE h, COORD c, int k, int n2, int len2);
void submenu();
void submenu2();
void submenu3();
int main(){
	const char* consoleTitle = "The Game of Life";
    SetConsoleTitleA(consoleTitle);
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	COORD source1 = {csbi.srWindow.Right,csbi.srWindow.Bottom};
	COORD b= source1;
	COORD t={0,0};
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	ramka(h,t,b);
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	COORD source = {(csbi.srWindow.Right / 2)-18, csbi.srWindow.Bottom / 2 };
	COORD current = source;
	int suz=1,k=0,n=4,len=10;
	char suz1=10;
    system("color F0");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_TEXT);
	draw(h,current,k,n,len);
    while (suz) {
        if (_kbhit()) {
            suz1 = _getch();
            switch (suz1) {
                case 27:
                    suz = 0;
                    break;
                case 13: {
                    switch (k) {
                        case 0:
                            Play();
                            break;
                        case 1:
                            Rules();
                            break;
                        case 2:
                            About();
                            break;
                        case 3:
                            suz = 0;
                    }
                    break;
                }
                case KEY_ARROW_RIGHT:
                	system("cls");
                	ramka(h,t,b);
                    if (k == n - 1) {
                        k = 0;
                    } else {
                        k++;
                    }
                    draw(h, current, k, n, len);
                    break;
                case KEY_ARROW_LEFT:
                	system("cls");
                	ramka(h,t,b);
                    if (k == 0) {
                        k = n - 1;
                    } else {
                        k--;
                    }
                    draw(h, current, k, n, len);
                    break;
            }
        }
    }
}
void printgrid(bool grid[MAXSIZE][MAXSIZE],int gridsize) {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_TEXT | (WHITE_BACKGROUND << 4));
	unsigned char c;
	COORD f = {0,0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), f);
	c = 201;
	cout << c; 

	for (int i = 1; i < gridsize+1; i++) {
		c = 205;
		cout << c; 
	}

	c = 187;
	cout << c << endl; 

	for (int i = 1; i < gridsize+1; i++) {
		c = 186;
		cout << c; 

		for (int j = 1; j < gridsize+1; j++) {
			if (grid[i][j] == true) {
				cout << "*";
			} else {
				cout << ".";
			}
		}

		c = 186;
		cout << c << endl; 
	}

	c = 200;
	cout << c; 

	for (int i = 1; i < gridsize+1; i++) {
		c = 205;
		cout << c; 
	}

	c = 188;
	cout << c << endl;

	COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_TEXT | (WHITE_BACKGROUND << 4));
}

void comparegrid(bool grid[MAXSIZE][MAXSIZE],bool gridtwo[MAXSIZE][MAXSIZE]){
    for(int i=0; i<gridsize;i++)
    {
        for(int j=0; j<gridsize;j++)
        {
                gridtwo[i][j] = grid[i][j];
        }
    }
}
void obnulgrid(bool grid[MAXSIZE][MAXSIZE],int gridsize){
	for(int i=0;i<gridsize;i++)
	{
		for(int j=0;j<gridsize;j++)
		{
			grid[i][j]=false;
		}
	}
}
void stan(bool grid[MAXSIZE][MAXSIZE], int gridsize){
    comparegrid(grid,gridtwo);
    bool changed = true;
    while (true){
    	COORD pos={0,gridsize+2};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    	cout<<"Do you want to click on enter or just wait? Enter c/w";
        cin >> choice;
        if (choice == "c" || choice == "C" || choice == "w" || choice == "W") {
            break;
        }
        cout << "Invalid input. Enter c/w: ";
    }
    if(choice == "c" || choice == "C")
    {
    	system("cls");
    	printgrid(grid,gridsize);
    	COORD pos = {0, 0};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        while(true){
        int iKey = _getch();
            if (iKey == KEY_ESC) {
                break; // Caaa?oaiea i?ia?aiiu ii ia?aoe? eeaaeoe ESC
            }
            if(iKey==KEY_ARROW_LEFT){
            	system("cls");
            	Play();
			}
            if (iKey == KEY_ENTER) {
                comparegrid(grid, gridtwo);
        for (int i = 1; i <= gridsize; i++) {
            for (int j = 1; j <= gridsize; j++) {
                int alive = 0;
                if (grid[i-1][j-1]) alive++;
                if (grid[i-1][j]) alive++;
                if (grid[i-1][j+1]) alive++;
                if (grid[i][j-1]) alive++;
                if (grid[i][j+1]) alive++;
                if (grid[i+1][j-1]) alive++;
                if (grid[i+1][j]) alive++;
                if (grid[i+1][j+1]) alive++;

                if (!grid[i][j] && alive == 3) {
                    gridtwo[i][j] = true;
                    changed = true;
                } else if (grid[i][j] && (alive < 2 || alive > 3)) {
                    gridtwo[i][j] = false;
                    changed = true;
                } else {
                    gridtwo[i][j] = grid[i][j];
                }
            }
        }
        comparegrid(gridtwo, grid);
        printgrid(grid,gridsize);
        COORD pos3 = {gridsize+2, 3};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos3);
		cout<<"Press <-(Key_arrow_left) to leave to menu";
        Sleep(500);
		bool allFalse= true;
            for (int i = 1; i <= gridsize; i++) {
                for (int j = 1; j <= gridsize; j++) {
                    if(grid[i][j]==true) {
                    	allFalse=false;
                        break;
                    }
                }
            }

            // If all cells are false, end the game
            if (allFalse==true) {
            	system("cls");
                cout << "Game over!" << endl;
                while(true){
                cout<<"You wanna start new game or exit?Enter n/e";
                cin>>suz3;
                if (suz3 == "n" || suz3 == "N" || suz3 == "e" || suz3 == "E") {
            	break;
        		}	
        		cout << "Invalid input. Enter n/e:";
				}
                if(suz3=="n"||suz3=="N"){
                	Play();
				}
				else if(suz3=="e"||suz3=="E"){
					exit(0);
				}
            }
        }
    }
	}
    if(choice == "w" || choice == "W")
    {
    	system("cls");
    	COORD pos = {0, 0};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        while (true) {
        comparegrid(grid, gridtwo);
        for (int i = 1; i <= gridsize; i++) {
            for (int j = 1; j <= gridsize; j++) {
                int alive = 0;
                if (grid[i-1][j-1]) alive++;
                if (grid[i-1][j]) alive++;
                if (grid[i-1][j+1]) alive++;
                if (grid[i][j-1]) alive++;
                if (grid[i][j+1]) alive++;
                if (grid[i+1][j-1]) alive++;
                if (grid[i+1][j]) alive++;
                if (grid[i+1][j+1]) alive++;

                if (!grid[i][j] && alive == 3) {
                    gridtwo[i][j] = true;
                    changed = true;
                } else if (grid[i][j] && (alive < 2 || alive > 3)) {
                    gridtwo[i][j] = false;
                    changed = true;
                } else {
                    gridtwo[i][j] = grid[i][j];
                }
            }
        }
        comparegrid(gridtwo, grid);
        printgrid(grid,gridsize);
        COORD pos3 = {gridsize+2, 3};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos3);
		cout<<"Press <-(Key_arrow_left) to leave to menu";
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        	system("cls");
            Play();
        }
        Sleep(500);
	bool allFalse = true;
            for (int i = 1; i <= gridsize; i++) {
                for (int j = 1; j <= gridsize; j++) {
                    if (grid[i][j]) {
                        allFalse = false;
                        break;
                    }
                }
                if (!allFalse) {
                    break;
                }
            }

            // If all cells are false, end the game
            if (allFalse==true) {
            	system("cls");
                cout << "Game over!" << endl;
                while(true){
                cout<<"You wanna start new game or exit?Enter n/e";
                cin>>suz4;
                if (suz4 == "n" || suz4 == "N" || suz4 == "e" || suz4 == "E") {
            	break;
        		}	
        		cout << "Invalid input. Enter n/e:";
				}
                if(suz4=="n"||suz4=="N"){
                	Play();
				}
				else if(suz4=="e"||suz4=="E"){
					exit(0);
				}
            }
        }
    }
	}
void savegrid(bool grid[MAXSIZE][MAXSIZE]){
    FILE* fp;
    fp = fopen("grid.txt", "w"); 
    for(int i=1; i<gridsize; i++){
        for(int j=1; j<gridsize; j++){
            if(grid[i][j] == true){
                fprintf(fp, "%d %d\n", i, j); 
            }
        }
    }
    fclose(fp);
}
void draw(HANDLE h, COORD c, int k, int n, int len) {
    COORD cc = c;
    int maxLen = 0;  
    
    for (int i = 0; i < n; i++) {
        int currentLen = strlen(m[i]);
        if (currentLen > maxLen) {
            maxLen = currentLen;
        }
    }

   
    len = maxLen + 4; 

    for (int i = 0; i < n; i++) {
        cc.X = c.X + i * len;
        SetConsoleCursorPosition(h, cc);
        SetConsoleTextAttribute(h, GREEN_TEXT | (WHITE_BACKGROUND << 4));
        cout << m[i];
    }

    cc.X = c.X + k * len;
    SetConsoleTextAttribute(h, ATTR2 | (WHITE_BACKGROUND << 4));
    SetConsoleCursorPosition(h, cc);
    cout << m[k];
}
void draw_gridsize(HANDLE h, COORD c, int k, int n2, int len2) {
    COORD cc = c;
    int maxLen = 0;  
    
    for (int i = 0; i < n2; i++) {
        int currentLen = strlen(m1[i]);
        if (currentLen > maxLen) {
            maxLen = currentLen;
        }
    }

   
    len2 = maxLen + 4; 

    for (int i = 0; i < n2; i++) {
        cc.X = c.X + i * len2;
        SetConsoleCursorPosition(h, cc);
        SetConsoleTextAttribute(h, GREEN_TEXT | (WHITE_BACKGROUND << 4));
        cout << m1[i];
    }

    cc.X = c.X + k * len2;
    SetConsoleTextAttribute(h, ATTR2 | (WHITE_BACKGROUND << 4));
    SetConsoleCursorPosition(h, cc);
    cout << m1[k];
}
void draw_way(HANDLE h, COORD c, int k, int n3, int len3) {
    COORD cc = c;
    int maxLen = 0;  
    
    for (int i = 0; i < n3; i++) {
        int currentLen = strlen(m2[i]);
        if (currentLen > maxLen) {
            maxLen = currentLen;
        }
    }

   
    len3 = maxLen + 4; 

    for (int i = 0; i < n3; i++) {
        cc.X = c.X + i * len3;
        SetConsoleCursorPosition(h, cc);
        SetConsoleTextAttribute(h, GREEN_TEXT | (WHITE_BACKGROUND << 4));
        cout << m2[i];
    }

    cc.X = c.X + k * len3;	
    SetConsoleTextAttribute(h, ATTR2 | (WHITE_BACKGROUND << 4));
    SetConsoleCursorPosition(h, cc);
    cout << m2[k];
}
void draw_start(HANDLE h, COORD c, int k4, int n4, int len4) {
    COORD cc = c;
    int maxLen = 0;  
    
    for (int i = 0; i < n4; i++) {
        int currentLen = strlen(m3[i]);
        if (currentLen > maxLen) {
            maxLen = currentLen;
        }
    }

   
    len4 = maxLen + 4; 

    for (int i = 0; i < n4; i++) {
        cc.X = c.X + i * len4;
        SetConsoleCursorPosition(h, cc);
        SetConsoleTextAttribute(h, GREEN_TEXT | (WHITE_BACKGROUND << 4));
        cout << m3[i];
    }

    cc.X = c.X + k4 * len4;	
    SetConsoleTextAttribute(h, ATTR2 | (WHITE_BACKGROUND << 4));
    SetConsoleCursorPosition(h, cc);
    cout << m3[k4];
}
void Play() {
    system("cls");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN_TEXT | (WHITE_BACKGROUND << 4));
    CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	COORD source2= {csbi.srWindow.Right,csbi.srWindow.Bottom};
	COORD b2= source2;
    COORD f1={0,0};
    COORD current2={ (csbi.srWindow.Right / 2)-30, csbi.srWindow.Bottom / 2 };
    ramka(h,f1,b2);
    submenu();
    COORD temp={(csbi.srWindow.Right / 2)-15, (csbi.srWindow.Bottom / 2)-7 };
    system("cls");
    ramka(h,f1,b2);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),temp);
	cout << "Choose the way to enter cells on grid";
	submenu2();
    system("cls");
	COORD temp4={0,0};
	COORD right1={csbi.srWindow.Right,csbi.srWindow.Bottom};
	ramka(h,temp4,right1);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(csbi.srWindow.Right / 2)-15, (csbi.srWindow.Bottom / 2)-7});
    cout << "Grid is done.Choose what you want to do next" << endl;
	submenu3();
}
void Rules(){
	system("cls");
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	ramka(h,{0,0},{csbi.srWindow.Right,csbi.srWindow.Bottom});
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {1, 1});
	cout<<"1.Any live cell with fewer than two live neighbours dies, as if by underpopulation."<<endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {1, 2});
	cout<<"2.Any live cell with two or three live neighbours lives on to the next generation."<<endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {1, 3});
	cout<<"3.Any live cell with more than three live neighbours dies, as if by overpopulation."<<endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {1, 4});
	cout<<"4.Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction."<<endl;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {1, 5});
	cout<<"5.The game ends when there is no cells on grid or cells got in infinity cycle";
	
}	
void About(){
	system("cls");
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	ramka(h,{0,0},{csbi.srWindow.Right,csbi.srWindow.Bottom});
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {1, 1});
	cout<<"Created by Olefirenko Myroslav,IASA 124";
}
void ramka(HANDLE h, COORD t, COORD b) {
	int lenx=b.X-t.X-2,leny=b.Y-t.Y;
    COORD f=t;
	unsigned char c;
    SetConsoleCursorPosition(h, f);
	c = 457;
	cout<<c; 
	f.X++; c=461;
	for(int i = 0; i <lenx; i++){
		cout<<c;
	}
	c=443; 
	cout<<c<<endl;
	c=442;
	f=t;	
	f.Y++;
		for(int i=0;i<leny-1;i++){
			SetConsoleCursorPosition(h, f);
			f.Y++;
			cout<<c;
		}
	c=456;
	COORD temp={0,leny};
	SetConsoleCursorPosition(h, temp);
	cout<<c;
	c=461;
	for(int i=1;i<lenx+1;i++) cout<<c;
	c=444;
	cout<<c;
	COORD temp1={lenx+1,1};
	SetConsoleCursorPosition(h, temp1);
	c=442;
	f=temp1;	
	for(i=1;i<leny;i++){
		SetConsoleCursorPosition(h,f);
		f.Y++;
		cout<<c;
	}
}
void arrows(){
		system("cls");
        printgrid(grid, gridsize);
        COORD pos = {1, 1};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        COORD temp7={gridsize+3,3};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),temp7);
        cout<<"To set cell press ENTER,to complete the arrangement of cells press ESC";
        int x = 1, y = 1;
        while (true) {
            int iKey = _getch();
            if (iKey == KEY_ESC) {
                break; // Caaa?oaiea i?ia?aiiu ii ia?aoe? eeaaeoe ESC
            }
            if (iKey == KEY_ENTER) {
                if (grid[x][y] == false) {
                    grid[x][y] = true;
                    printgrid(grid, gridsize);
                    COORD temp7={gridsize+3,3};
        			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),temp7);
        			cout<<"To set cell press ENTER,to complete the arrangement of cells press ESC";
                } else {
                    grid[x][y] = false;
                    printgrid(grid, gridsize);
                    COORD temp7={gridsize+3,3};
        			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),temp7);
        			cout<<"To set cell press ENTER,to complete the arrangement of cells press ESC";
                }
            } else if (iKey == KEY_ARROW_DOWN && x < gridsize) {
                x++;
                printgrid(grid, gridsize);
                COORD temp7={gridsize+3,3};
        		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),temp7);
        		cout<<"To set cell press ENTER,to complete the arrangement of cells press ESC";
            } else if (iKey == KEY_ARROW_UP && x > 1) {
                x--;
                printgrid(grid, gridsize);
                COORD temp7={gridsize+3,3};
        		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),temp7);
        		cout<<"To set cell press ENTER,to complete the arrangement of cells press ESC";
            } else if (iKey == KEY_ARROW_RIGHT && y < gridsize) {
                y++;
                printgrid(grid, gridsize);
                COORD temp7={gridsize+3,3};
        		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),temp7);
        		cout<<"To set cell press ENTER,to complete the arrangement of cells press ESC";
            } else if (iKey == KEY_ARROW_LEFT && y > 1) {
                y--;
                printgrid(grid, gridsize);
                COORD temp7={gridsize+3,3};
        		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),temp7);
        		cout<<"To set cell press ENTER,to complete the arrangement of cells press ESC";
            }
            pos = {y, x};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        }
}
void file(){
	FILE* fp;
        fp = fopen("grid.txt", "r"); 
        int x, y;
        while(fscanf(fp, "%d %d", &x, &y) != EOF){ 
            grid[x][y] = true; 
        }
        fclose(fp); 
        printgrid(grid,gridsize);
        sleep(1.5);
}
	void submenu(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int k=0,n2=10,len2=10;
    int suz6=1;
	char suz7=10;
	COORD current2={ (csbi.srWindow.Right / 2)-30, csbi.srWindow.Bottom / 2 };
    draw_gridsize(h,current2,k,n2,len2);
    COORD temp={(csbi.srWindow.Right / 2)-15, (csbi.srWindow.Bottom / 2)-7 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),temp);
    cout<<"Choose the size of grid";
    while(suz6){
        if (_kbhit()) {
            suz7 = _getch();
            switch (suz7) {
                case KEY_ESC:
                    suz6 = 0;
                    exit(0);
                case KEY_ENTER: {
                    switch (k) {
                        case 0:
                            gridsize=6;
                            suz6=0;
                            break;
                        case 1:
                            gridsize=7;
                            suz6=0;
                            break;
                        case 2:
                            gridsize=8;
                            suz6=0;
                            break;
                        case 3:
                            gridsize=9;
                            suz6=0;
                            break;
                        case 4:
                        	gridsize=10;
                        	suz6=0;
                        	break;
                        case 5:
                        	gridsize=11;
                        	suz6=0;
                        	break;
                        case 6:
                        	gridsize=12;
                        	suz6=0;
                        	break;
                        case 7:
                        	gridsize=13;
                        	suz6=0;
                        	break;
                        case 8:
                        	gridsize=14;
                        	suz6=0;
                        	break;
                        case 9:
                        	gridsize=15;
                        	suz6=0;
                        	break;
                        case 10:
                        	suz6=0;
                    }
                    break;
                }
                case KEY_ARROW_RIGHT:
                    if (k == n2 - 1) {
                        k = 0;
                    } else {
                        k++;
                    }
                    draw_gridsize(h, current2, k, n2, len2);
                    break;
                case KEY_ARROW_LEFT:
                    if (k == 0) {
                        k = n2 - 1;
                    } else {
                        k--;
                    }
                    draw_gridsize(h, current2, k, n2, len2);
                    break;
            }
        }
}
}
void submenu2(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int k1=0,n3=3,len3=10;
    int p1=1;
	char p2=10;
    COORD f2={0,0};
    COORD c2={ (csbi.srWindow.Right / 2)-20, csbi.srWindow.Bottom / 2 };
	draw_way(h,c2,k1,n3,len3);
    while(p1) {
        if (_kbhit()) {
            p2 = _getch();
            switch (p2) {
                case 27:
                    p1 = 0;
                    break;
                case 13: {
                    switch (k1) {
                        case 0:
                            arrows();
                            p1 = 0;
                            break;
                        case 1:
                            file();
                            p1 = 0;
                            break;
                        case 2:
                            exit(0);
                    }
                    break;
                }
                case KEY_ARROW_RIGHT:
                    if (k1 == n3 - 1) {
                        k1 = 0;
                    } else {
                        k1++;
                    }
                    draw_way(h,c2,k1,n3,len3);
                    break;
                case KEY_ARROW_LEFT:
                    if (k1 == 0) {
                        k1 = n3 - 1;
                    } else {
                        k1--;
                    }
                    draw_way(h,c2,k1,n3,len3);
                    break;
            }
        }
    }
}
void submenu3(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int bal1=1,k5=0,n5=4,len5=10;
	char bal2=10;
	COORD temp3={ (csbi.srWindow.Right / 2)-20, csbi.srWindow.Bottom / 2 };
    draw_start(h,temp3,k5,n5,len5);
    while (bal1) {
        if (_kbhit()) {
            bal2 = _getch();
            switch (bal2) {
                case 27:
                    bal1 = 0;
                    break;
                case 13: {
                    switch (k5) {
                        case 0:
                            printgrid(grid, gridsize);
    						stan(grid, gridsize);
                            break;
                        case 1:
                            obnulgrid(grid,gridsize);
    						Play();
                            break;
                        case 2:
                            savegrid(grid);
                            Play();
                            break;
                        case 3:
                            suz = 0;
                            exit(0);
                    }
                    break;
                }
                case KEY_ARROW_RIGHT:
                    if (k5 == n5 - 1) {
                        k5 = 0;
                    } else {
                        k5++;
                    }
                    draw_start(h,temp3,k5,n5,len5);
                    break;
                case KEY_ARROW_LEFT:
                    if (k5 == 0) {
                        k5 = n5 - 1;
                    } else {
                        k5--;
                    }
                    draw_start(h, temp3, k5, n5, len5);
                    break;
            }
        }
    }
}
