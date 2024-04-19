#include <windows.h>
#include <conio.h>
#include <iostream>
#include <ctime>

#define ROW 10
#define COL 10

using namespace std;

class Maze {

    public:
    bool State = true;
    bool winCheck(char);
    bool bombCheck(char);
    void execute();
    
};

class Cell{

    public:
    char Matrix[ROW][COL];
    int CurPos[2];
    
    Cell(){
        generator();
        bool flag = false;
        for (int i = 0; i < ROW; i++){
            for (int j = 0; j < COL; j++){
                if (Matrix[i][j] == 'P'){
                    CurPos[0] = i;
                    CurPos[1] = j;
                    flag = true;
                    break;
                }
            }if (flag == true){break;}
        }
    }
    
    char Moveplayer(int*);
    void printWalls();
    void printFeild();
    void generator();

};

void showConsoleCursor (bool);
void clearScreen();
void gotoxy (int, int);
void sleep(int);


void Cell::generator(){
    const int Total = ROW * COL;
    char element[4] = {'W','B','P','E'};
    int break_point[4] = {Total/4, Total/6, 1, 1};
    int i, j;
    srand((unsigned) time(0));
    for (int e = 0; e < 4; e++){
        for (int n=0; n < Total; n++){
            if (n == break_point[e]){
                break;
            }
            i = rand()%10;
            j = rand()%10;
            Matrix[i][j] = element[e];
        }
    }
}

void Cell::printFeild(){
    
    for (int i = 0; i <= ROW; i++){
        for (int j = 0; j <= COL; j++){
            if (Matrix[i][j] == 'W'){
                gotoxy ((j+1)*2, i+1);
                cout << "[]";
            }else if (Matrix[i][j] == 'B'){
                gotoxy ((j+1)*2, i+1);
                cout << "b";
            }else if (Matrix[i][j] == 'E'){
                gotoxy ((j+1)*2, i+1);
                cout << "$";
            } else if (Matrix[i][j] == 'P'){
                gotoxy ((j+1)*2, i+1);
                cout << "@";
            }
        }
    }
    
}

void Cell::printWalls(){

    for (int i = 1; i <= ROW; i++){
        gotoxy (0, i);
        cout << "[]";
        gotoxy ((COL+1)*2, i);
        cout << "[]";
    }

    for (int j = 0; j <= COL+1; j++){
        gotoxy(j*2, 0);
        cout << "[]";
        gotoxy(j*2, ROW+1);
        cout << "[]";
    }


}

char Cell::Moveplayer(int* Direction){
    int NewPos[2];

    NewPos[0] = CurPos[0] + Direction[0];
    NewPos[1] = CurPos[1] + Direction[1];

    char character = Matrix[NewPos[0]][NewPos[1]];

    if (!((0 <= NewPos[0] && NewPos[0] <= ROW) && (0 <= NewPos[1] && NewPos[1] <= COL))){
        character = 'W';
    }

    if (character != 'W'){

        Matrix[CurPos[0]][CurPos[1]] = ' ';
        Matrix[NewPos[0]][NewPos[1]] = 'P';

        CurPos[0] = NewPos[0];
        CurPos[1] = NewPos[1];
        
        clearScreen();
        printFeild(); 
        printWalls();  
        
    }  
    return character;
}

bool Maze::winCheck(char Character){

    if (Character == 'E'){
        clearScreen ();
        cout << "YOU WON!";
        sleep(1000);
        State = false;
    } 

    return State;
}

bool Maze::bombCheck(char Character){

    if (Character == 'B'){
        clearScreen ();
        cout << "BOMB!";
        sleep(1000);
        State = false;
    } 

    return State;
}

void gotoxy (int x, int y) {
    static HANDLE h = NULL;
    if (!h) {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

void clearScreen () {
    system("cls");
}

void sleep (int mili) {
    Sleep(mili);
}

void showConsoleCursor (bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Maze::execute(){

    bool State = true;
    

    Cell cell;

    const int KEY_UP = 72;
    const int KEY_DOWN = 80;
    const int KEY_LEFT = 75;
    const int KEY_RIGHT = 77;

    int Move[2];

    clearScreen();
    cell.printFeild();
    cell.printWalls();
    showConsoleCursor (false);

    while(true) {
        
        switch((getch())) {
            case KEY_UP:
                Move[0] = -1;
                Move[1] = 0;
                break;
            case KEY_DOWN:
                Move[0] = 1;
                Move[1] = 0;
                break;
            case KEY_LEFT:
                Move[0] = 0;
                Move[1] = -1;
                break;
            case KEY_RIGHT:
                Move[0] = 0;
                Move[1] = 1;
                break;
            default:
                continue;
            
        }

        char Character = cell.Moveplayer(Move);
        State = bombCheck(Character);
        State = winCheck(Character);

        if (!State){
            break;
        }
    }
}


int main(int argc, char** argv){
    Maze maze;
    maze.execute();
    return 0;
}