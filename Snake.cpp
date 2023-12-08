#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#define underline "\033[4m"
#define nounderline "\033[0m"
using namespace std;

class Snake;
class Walls;
class Fruit;
class Game;

void gotoxy(int x, int y)
{
    COORD Position;
	Position.X = x;
	Position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO CSBI;
    if(GetConsoleScreenBufferInfo(hConsoleOutput, &CSBI))
    {
        return CSBI.dwCursorPosition;
    }
    else
	{
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

class Snake
{
    
    char KeyEnter = '\0';
	char LastKeyEnter = '\0';

public:

    friend class game;
    friend class Walls;
    friend int Menu(Walls& Walls);

	vector<int> x, y;
    int Size = 1;
    
    char Button1='w', Button2='a', Button3 = 's', Button4 = 'd';
    int clo = 50;
    int c = 219;
    clock_t time=clock();
    snake() {}

    void AddLength()
	{
		x.push_back(x[Size-1]);
		y.push_back(Size-1);
	}

    int getX()
	{
		return x[0];
	}
    int getY()
	{
		return y[0];
	}

    void Initiation()
	{
        x.push_back(50);
		y.push_back(11);
    }

    void Move()
	{
    	HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(col, 14);
        
        gotoxy(x.back(), y.back());

        printf(" ");

        for (int i = Size - 1; i > 0; i--)
		{
            x[i] = x[i - 1];
            y[i] = y[i - 1];
        }
        LastKeyEnter = KeyEnter;
        if (Size > 1)
        {
            gotoxy(x[1], y[1]);
            printf("%c", c);
        }
    }

    void Move2()
	{
        time = clock();
        while ((clock() < time + clo) && !_kbhit());

        if (clock() < time + clo)
		{
            KeyEnter = _getch();
            if ((KeyEnter == Button4) && (LastKeyEnter == Button2))
                KeyEnter = Button2;
            else if ((KeyEnter == Button1) && (LastKeyEnter == Button3))
                KeyEnter = Button3;
            else if ((KeyEnter == Button3) && (LastKeyEnter == Button1))
                KeyEnter = Button1;
            else if ((KeyEnter == Button2) && (LastKeyEnter == Button4))
                KeyEnter = Button4;
        }
    }

    void Move3()
	{
		if (KeyEnter == Button3)
		{
			Move();
			gotoxy(x[0], ++y[0]);
			printf("%c", 31);
	    }
		else if (KeyEnter == Button1)
		{
			Move();
			gotoxy(x[0], --y[0]);
			printf("%c", 30);
        }
	    else if (KeyEnter == Button2)
		{
	
			Move();
			gotoxy(--x[0], y[0]);
			printf("%c", 17);
	    }
    	else if (KeyEnter == Button4)
		{

			Move();
			gotoxy(++x[0], y[0]);
			printf("%c", 16);
        }
    }

    void Wrap()
	{
        if (x[0] == 0)
		{
			gotoxy(x[0], y[0]);
			printf("%c", 186); x[0] = 99;
		}
        if (x[0] == 100)
		{
			gotoxy(x[0], y[0]);
			printf("%c", 186); x[0] = 1;
		}
        if (y[0] == 0)
		{
			gotoxy(x[0], y[0]);
			printf("%c", 205); y[0] = 20;
		}
        if (y[0] == 21)
		{
			gotoxy(x[0], y[0]);
			printf("%c", 205); y[0] = 1;
		}


        if (x[0] == 0)
		{
			gotoxy(x[0], y[0]);
			printf("%c", 186); x[0] = 99;
		}
        if (x[0] == 100)
		{
			gotoxy(x[0], y[0]);
			printf("%c", 186); x[0] = 1;
		}
        if (y[0] == 25)
		{
			gotoxy(x[0], y[0]);
			printf("%c", 205); y[0] = 45;
		}
        if (y[0] == 46)
		{
			gotoxy(x[0], y[0]);
			printf("%c", 205); y[0] = 26;
		}
    }
};

class Fruit
{
public:

    int FruitX;
	int FruitY;

    void Spawn(Snake &obj)
	{
        srand(time(0));
        FruitY = (rand() % 18) + 1;
        FruitX = (rand() % 98) + 1;
    }
    
    void Display()
	{
        gotoxy(FruitX, FruitY);
        printf("%c", (char)254);
    }
};

class Walls : public Fruit
{

public:

	COORD Position;

	void Border()
	{
    	HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(col, 2);
    	
		Position = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
		
        for (int c = 0;c <= 100;c++)
		{
            if (c == 0)
                printf("%c", 201);
            else if (c == 100)
                printf("%c", 187);
            else
                printf("%c", 205);
        }
        for (int c = Position.Y;c < Position.Y + 20;c++)
		{
            gotoxy(Position.X, c + 1);
            printf("%c", 186);
            gotoxy(Position.X + 100, c + 1);
            printf("%c", 186);
        }
        gotoxy(Position.X, Position.Y + 21);
        for (int c = 0;c <= 100;c++)
		{
            if (c == 0)
                printf("%c", 200);
            else if (c == 100)
                printf("%c", 188);
            else
                printf("%c", 205);
        }
    }
	
	virtual void Border(Snake &obj)
	{
         HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);

         SetConsoleTextAttribute(col, 2);
        
		Position = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
      
        for (int c = 0;c <= 100;c++)
		{
            if (c == 0)
                printf("%c", 201);
            else if (c == 100)
                printf("%c", 187);
            else
                printf("%c", 205);
        }
        for (int c = Position.Y;c <Position.Y+ 20;c++)
		{
            gotoxy(Position.X, c + 1);
            printf("%c", 186);
            gotoxy(Position.X+100, c + 1);
            printf("%c", 186);
        }
        gotoxy(Position.X, Position.Y + 21);
        
        for (int c = 0;c <= 100;c++)
		{
            if (c == 0)
                printf("%c", 200);
            else if (c == 100)
                printf("%c", 188);
            else
                printf("%c", 205);
        }
    }
	
    virtual int Check(int &FX, int &FY, vector<int> &X, vector<int>  &Y, int Size)
	{
        for (int i = 0; i < Size; i++)
        {
            if (FX == X[i] && FY == Y[i])
            {
                return 1;
            }
        }
        return 0;
    }


    int Over(int X, int Y, int Size, Snake& obj)
	{
        int a = 10;

        gotoxy(40, a);
        printf("Game Over\n");
        gotoxy(40, a + 1);
        printf("%cScore : %d   ", 179, Size - 1);

        gotoxy(0, 22);
        while (_getch() != 13){}
        return 1;
    }

    int Over2(Snake& obj)
	{
    	for (int i = 4; i < obj.Size; i++)
    	{
			if (obj.x[0] == obj.x[i] && obj.y[0] == obj.y[i])	
			{
				gotoxy(obj.x[0], obj.y[0]);
				cout << "X";
            	return Over(obj.x[0], obj.y[0], obj.Size, obj);	
			}
        }
        return 0;
    }
};

class Game
{
   
public:

	int gscore() { return 1; }
    
	int PlayGame(bool a,bool b,int cc)
	{
        
		int h=1;
        
        Walls Walls0;

        Walls *Walls1=&Walls0;
        Snake Snake1;
        Snake1.c=cc;

        gotoxy(0, 0);

        Snake1.Initiation();

		Walls1->Border(Snake1);

    	gotoxy(Snake1.x[0], Snake1.y[0]); cout << "X";

    	do
		{
			Walls1->Spawn(Snake1);
        } while (Walls1->Check(Walls1->FruitX, Walls1->FruitY, Snake1.x, Snake1.y, Snake1.Size));
        Walls1->Display();

		while (1)
		{
            	
            	
            	 gotoxy(103,h);
                    printf("%cPlayer %d", 179,a+1);
                    gotoxy(103,h+1);
                    printf("%cScore : %d   ", 179, Snake1.Size - 1);
            	
            	

                do
				{
            		Snake1.Move2();
                	Snake1.Move3();
					Snake1.Wrap(); 

                    if (Walls1->Over2(Snake1) == 1)
						return (Snake1.Size - 1);

                } while ((Snake1.getX() != Walls1->FruitX) || (Snake1.getY() != Walls1->FruitY));

                Snake1.AddLength();
                gotoxy(Snake1.x[Snake1.Size], Snake1.y[Snake1.Size]);
                printf("%c", 254);
                Snake1.Size++;

                do
				{
                    Walls1->Spawn(Snake1);
                } while (Walls1->Check(Walls1->FruitX, Walls1->FruitY, Snake1.x, Snake1.y, Snake1.Size));

                Walls1->Display();
        }
    }
};






void Title(Walls &Walls)
{
	Walls.Border();
//    gotoxy(48, 10);
//    cout << "game";
//    _getch();
      
    gotoxy(5, 2);
    cout << "0 0 0 0 0";
    gotoxy(5, 3);
    cout << "0       0";
    gotoxy(5, 4);
    cout << "0           0       0   0 0 0 0   0     0   0 0 0 0   0 0 0 0   0   0    0   0 0 0 0";
    gotoxy(5, 5);
    cout << "0 0 0 0 0   0       0      0      0     0   0         0     0   0   00   0   0      ";
    gotoxy(5, 6);
    cout << "        0   0       0      0      0 0 0 0   0 0 0     0 0 0 0   0   0  0 0   0  0  0";
    gotoxy(5, 7);
    cout << "0       0   0       0      0      0     0   0         0  0      0   0   00   0     0";
    gotoxy(5, 8);
    cout << "0 0 0 0 0   0 0 0   0      0      0     0   0 0 0 0   0     0   0   0    0   0 0 0 0";
	
	gotoxy(5, 11);
	cout << "            0 0 0 0 0 "; 
	gotoxy(5, 12);
	cout << "            0       0";
	gotoxy(5, 13);
	cout << "            0           0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0   0    0   0 0 0 0   0 0 0 0";
	gotoxy(5, 14);
	cout << "            0 0 0 0 0   0         0     0   0     0   0         00   0      0      0";
	gotoxy(5, 15);
	cout << "                    0   0 0 0     0 0 0 0   0 0 0 0   0 0 0     0  0 0      0      0 0 0 0";
	gotoxy(5, 16);
	cout << "            0       0   0         0  0      0         0         0   00      0            0" ;
	gotoxy(5, 17);
	cout << "            0 0 0 0 0   0 0 0 0   0     0   0         0 0 0 0   0    0      0      0 0 0 0";
    _getch();

    system("cls");
}




int Menu(Walls& Walls,int c)
{
    bool check = false;
    string str;
    int x = 0, x2 = 0, x3 = 0, mx2 = 0, mx3 = 0;
    int y = 9;
    char Key;

    Walls.Border();

    gotoxy(45, y - 1);
    cout << underline << "MENU" << nounderline;

    gotoxy(45, y + 1);
    cout << "Start Game";

    gotoxy(45, y + 2);
    cout << "";

    gotoxy(45, y + 3);
    cout << "View Score Board";

    gotoxy(45, y + 4);
    cout << "Credits";

    y = 10;

    while (1)
	{

        gotoxy(42, y); cout << "->";

        Key = _getch();

        if (Key == 's' && check == 0)
		{
			gotoxy(42, y);
			cout << "  ";
			y++;
			if (y > 13)
				y = 10;
		}
        else if (Key == 'w' && check == 0)
		{
			gotoxy(42, y);
			cout << "  ";
			y--;
			if(y < 10)
				y = 13;
		}
		else if (y == 10 && Key == 'd')
		{
			return 1;
		}
        else if (y == 11 && Key == 'd')
		{
			return 2;
		}
        else if (y == 12 && Key == 'd')
		{
		    check = true;
		    fstream file("score.txt", ios::in);
		
		    system("cls");
		    Walls.Border();
		    gotoxy(44, 9);
		    cout << "Player";
		    x = 11;
		
		    while (getline(file, str))
			{
		        x2 = stoi(str);
		        if (mx2 < x2) mx2 = x2;
		        gotoxy(44, x); cout << x2;
		        ++x;
		        getline(file, str);
		    }
		
		    file.close();
		}

        else if (y == 13 && Key == 'd') {
            system("cls");
            Walls.Border();
            gotoxy(45, 8);
            cout << underline << "TAS Developers" << nounderline;

            gotoxy(45, 10);
            cout << "Talha Durrani 22k-4144";

            gotoxy(45, 11);
            cout << "Asadullah 22k-4138";

            gotoxy(45, 12);
            cout << "Shozab Mehdi 22k-4522";

        }
        else if (y == 14 && Key == 'd')
		{

            gotoxy(55, 14);
            cout << "enter character ascii value : "; cin >> c;
            gotoxy(55, 14);
            cout << "                                       ";
        }

        else if (Key == 'a')
		{
            check = false;
            y = 9;
            gotoxy(42, y - 1);

            cout << underline << "           " << nounderline;

            gotoxy(42, y + 1);
            cout << "       ";

            gotoxy(42, y + 2);
            cout << "       ";

            gotoxy(42, y + 3);
            cout << "          ";

            system("cls");
            Walls.Border();

            gotoxy(45, y - 1);
            cout << underline << "MENU" << nounderline;

            gotoxy(45, y + 1);
            cout << "Start Game";

            gotoxy(45, y + 2);
            cout << "";

            gotoxy(45, y + 3);
            cout << "View Score Board";

            gotoxy(45, y + 4);
            cout << "Credits";

            y = 10;
        }

        else if (Key == 13)
			break;
    }

    system("cls");
    return 0;
}

int main()
{
	
	
	
    bool  a = 0, d = 0;
    
	
	int b = 0, c = 219, Player=0, ans=1;

    fstream file("score.txt", ios::app);


    Walls Walls;
   
    
    int check=0;
    
    Title(Walls);
    
    while(ans)
	{
		
	    check=0;
	    
	    while(check!=1)
		{
		   check=Menu(Walls, c);          
		   system("cls");
	    }
	    
	    
	    
	    Game Game;
		Player = Game.PlayGame(0,d,c);
	    
	    
		gotoxy(25,17);
		
		
		cout<<"do you want to continue? if yes than press 1 else 0";
		
		gotoxy(25,18); 
		
		cin>>ans;
		
		system("cls");
	}
    
	file.close();

}