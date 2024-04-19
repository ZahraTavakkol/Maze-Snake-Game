#include <windows.h>
#include <conio.h>
#include <iostream>
#include <ctime>

#define ROW 20
#define COL 20
#define RAISE_SPEED 1.5
#define SPEED 800
#define WIN 60

using namespace std;

void showConsoleCursor (bool);
void clearScreen();
void gotoxy (int, int);
void sleep(int);

class Snake{

    public:   
    void execute();
    bool winCheck(int);
    bool validPress(int*, int*);
};

class Unit{

    const int SIZE = COL/10 + 1;

    public:
    int Length;
    int Speed = 1;

    int Food[2];
    int head[2];
    int direction[2];

    int Units[WIN][2];

    Unit(){
        Length = SIZE;
        generator();
        increaseSnakeLenght(0, head);
        newFood();
        showOrHideFood(true);
        printFeild();
        printWalls();
    }

    void generator();
    void increaseSnakeLenght(int, int*);
    void raiseSpeed();
    void printWalls();
    void printFeild();
    void showOrHideFood(bool);
    void newFood();
    bool movePlayer();
    bool foodCheck();
    bool failCheck(int*);
    
};

void Unit::generator(){
    const int Total = ROW * COL;
    int tail[4][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}};

    srand((unsigned) time(0));

    int i = rand()%(ROW - 2*SIZE-1);
    int j = rand()%(COL - 2*SIZE-1);

    i += (SIZE+1);
    j += (SIZE+1); 

    head[0] = i;
    head[1] = j;

    int e = rand()%4;
    for (int idx = 1; idx <= SIZE; idx++){
        int NewPos[2] = {i+idx*tail[e][0], j+idx*tail[e][1]};
        increaseSnakeLenght(idx, NewPos);
    }
    

    direction[0] = -1 * tail[e][0];
    direction[1] = -1 * tail[e][1];
}

void Unit::increaseSnakeLenght(int index, int* NewTail){
    Units[index][0] = NewTail[0];
    Units[index][1] = NewTail[1];
    
}

void Unit::raiseSpeed(){
    Speed += RAISE_SPEED;
}

void Unit::printFeild(){
    gotoxy((Units[0][1])*2, Units[0][0]);
    cout << '@';
    for(int idx = 1; idx < Length; idx++){
        gotoxy((Units[idx][1])*2, Units[idx][0]);
        cout << 'O';
    }
}

void Unit::printWalls(){
    for (int i = 1; i < ROW-1; i++){
        gotoxy (0, i);
        cout << "[]";
        gotoxy ((COL-1)*2, i);
        cout << "[]";
    }

    for (int j = 0; j < COL; j++){
        gotoxy(j*2, 0);
        cout << "[]";
        gotoxy(j*2, ROW-1);
        cout << "[]";
    }
}

bool Unit::movePlayer(){
    int NewPos[2];
    int CurPos[2];

    NewPos[0] = head[0] + direction[0];
    NewPos[1] = head[1] + direction[1];

    if (failCheck(NewPos)){

        for(int idx = 0; idx < Length; idx++){

            CurPos[0] = Units[idx][0];
            CurPos[1] = Units[idx][1];

            Units[idx][0] = NewPos[0];
            Units[idx][1] = NewPos[1];

            NewPos[0] = CurPos[0];
            NewPos[1] = CurPos[1];

        }

        head[0] = Units[0][0];
        head[1] = Units[0][1];
        
    }else{
        return false;
    }

    gotoxy(CurPos[1]*2, CurPos[0]);
    cout << " ";
    printFeild(); 

    return true;
}

void Unit::showOrHideFood(bool Show){
    if (Show == true){
        gotoxy(Food[1]*2, Food[0]);
        cout << '*';
    }
}

void Unit::newFood(){
    srand((unsigned) time(0));

    int array[2];

    do{
        array[0] = rand()%ROW;
        array[1] = rand()%COL;
    }while(!failCheck(array));

    Food[0] = array[0];
    Food[1] = array[1];
    
}


bool Unit::failCheck(int* NewPos){

    for(int idx = 0; idx < Length; idx++){
        if(Units[idx][0] == NewPos[0] && Units[idx][1] == NewPos[1]){
            return false;
        }
    }

    if (!((0 < NewPos[0] && NewPos[0] < ROW-1) && (0 < NewPos[1] && NewPos[1] < COL-1))){
        return false;
    }

    return true;
}

bool Unit::foodCheck(){
    if(Food[0] == head[0] && Food[1] == head[1]){
        Length +=1;
        increaseSnakeLenght(Length, Units[Length-1]);
        newFood();
        raiseSpeed();
        return true;
    }
    return false;
}


bool Snake::winCheck(int Length){
    if (Length == WIN){
        return false;
    }
    return true;
}

bool Snake::validPress(int* Move, int* direction){
    if ((Move[0] == -1*direction[0]) || (Move[1] == -1*direction[1])){
        return false;
    }
    return true;
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


void Snake::execute(){

    bool state = true;

    Unit unit;
    
    const int KEY_UP = 72;
    const int KEY_DOWN = 80;
    const int KEY_LEFT = 75;
    const int KEY_RIGHT = 77;
    int Move[2];

    Move[0] = unit.direction[0];
    Move[1] = unit.direction[1];
    while(true) {        
        sleep(SPEED/unit.Speed);
        
        if (kbhit()){
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
                    break;
            }
        }
        

        bool Valid = validPress(Move, unit.direction);
        if(Valid) {
            unit.direction[0] = Move[0];
            unit.direction[1] = Move[1];
        };

        state = unit.movePlayer();
        unit.foodCheck();
        unit.showOrHideFood(true);
        
        if (!state) {
            clearScreen();
            cout << "GAME OVER!";
            sleep(3000);
            break;
        };
        
        if (!winCheck(unit.Length)){
            clearScreen();
            cout << "YOU WON!";
            sleep(3000);
            break;
        };       
        
    }
}


int main(int argc, char** argv){
    showConsoleCursor (false);
    clearScreen();
    Unit unit;
    Snake snake;
    snake.execute();

    return 0;
}