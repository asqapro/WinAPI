#include <iostream>
#include <ctime>
#include <windows.h> //windows API functionality

#define arenaWidth 28
#define arenaHeight 22

using namespace std;

void moveCursor(int x, int y){ //move console cursor
    COORD coord = {x, y}; //create COORD variable to hold x,y positions
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //set the console cursor position to x,y
}

void setConsoleColor(int color){ //set the console color's
    //1-15 set text color
    //16-25 set background color
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	SetConsoleTextAttribute(hstdout, color);
}

class GameArena{
    public:
    GameArena(){
        for(int iter = 0; iter < arenaHeight; iter++){
            moveCursor(0, iter);
            cout << "|";
        }
        for(int iter = 1; iter < arenaWidth+1; iter++){
            moveCursor(iter, arenaHeight-1);
            cout << "_";
        }
        for(int iter = arenaHeight-1; iter >= 0; iter--){
            moveCursor(arenaWidth, iter);
            cout << "|";
        }
        for(int iter = 0; iter < arenaWidth; iter++){
            for(int it = 0; it < arenaHeight; it++){
                filled[iter][it] = -2;
            }
        }
    }
    ~GameArena(){
        for(int it = 1; it < arenaWidth-1; it++){
            for(int iter = 0; iter < arenaHeight-1; iter++){
                moveCursor(it, iter);
                cout << " ";
            }
        }
    }
    int filled[arenaWidth][arenaHeight];
}arena;

class single_block{
    public:
    float xPos, yPos;
    void make(){
        for(int x = 0; x < arenaWidth; x++){
            for(int y = 0; y < arenaHeight;y++){
                if(arena.filled[x][y] == 1){
                    moveCursor(x+1, y-1);
                    cout << "_";
                    moveCursor(x, y);
                    cout << "|";
                    moveCursor(x+1, y);
                    cout << "_";
                    moveCursor(x+2, y);
                    cout << "|";
                    arena.filled[x][y] = 2;
                }
            }
        }
    }
    void destroy(){
        for(int x = 0; x < arenaWidth; x++){
            for(int y = 0; y < arenaHeight; y++){
                if(arena.filled[x][y] == 0){
                    moveCursor(x+1, y-1);
                    cout << " ";
                    moveCursor(x, y);
                    cout << " ";
                    moveCursor(x+1, y);
                    cout << " ";
                    moveCursor(x+2, y);
                    cout << " ";
                    arena.filled[x][y] = -1;
                }
            }
        }
    }
};

class shape{
    protected: //only allow access to the movement functions within the class
    clock_t dropTimer; //drop clock
    single_block blocks[4][4]; //each shape has a maximum of 4 blocks. 4 x positions, 4 y positions
    int rotation; //rotation of the block
    int type; //block type (see docs for numbers mean)
    public: //only allow the move function to be accessed outside of the class
    int move(){ //wrappper for movement functions
        //if(!canDrop()){
        //    for(int i = 0; i < 4; i++){
        //        int x = (int)blocks[rotation][i].xPos;
        //        int y = (int)blocks[rotation][i].yPos;
        //        arena.filled[x][y] = 1;
        //    }
        //    draw();
        //    return 0;
        //}
        if((clock() - dropTimer) / (double)CLOCKS_PER_SEC > .5){ //every half second, drop piece one block
            //gameDrop(); //drop the piece
            dropTimer = clock(); //reset the drop clock
        }
        int userRotated = 0;
        //if(canRotate()){
            //userRotated = userRotate(); //check if the user wants to rotate the block
        //}
        int shiftAmt = 0; //how much the block was shifted (-1, 0, or 1)
        int dropAmt = 0; //how much the block was dropped (0 or 1)
        if(!userRotated){
            //shiftAmt = userShift(); //check if the user wants to shift the block, store direction in shiftAmt
            if(!shiftAmt){ //if shiftAmt is 0
                //if(!canDrop()){
                //    for(int i = 0; i < 4; i++){
                //        int x = (int)blocks[rotation][i].xPos;
                //        int y = (int)blocks[rotation][i].yPos;
                //        arena.filled[x][y] = 1;
                //    }
                //    draw();
                //    return 0;
                //}
                //dropAmt = userDrop(); //allow the user to drop the block, store in dropAmt
            }
        }
        dropAmt = userDrop();
        erase();
        draw();
        return 1;
    }
    protected: //don't allow the movement functions to be accessed outside of the class
    int canDrop(){ //function to check if the piece can drop
        for(int i = 0; i < 4; i++){ //loop from 0 to 3
            if(blocks[rotation][i].yPos+1 >= arenaHeight){//if any piece of the block would drop below the arena
                return 0; //return that it cannot drop
            }
            int x = blocks[rotation][i].xPos;
            int y = blocks[rotation][i].yPos;
            if(arena.filled[x][y+1] == 1 || arena.filled[x][y+1] == 2){ //if the spot the block is going to move to is filled
                return 0; //return that it cannot drop
            }
        }
        return 1; //return that it can drop
    }
    /*int canRotate(){
        for(int x = 0; x < 4; x++){ //loop from 0 to 3
            for(int y = 0; y < 4; y++){
                if(blocks[x][y].xPos == 0.1){ //if the position is unitialized
                    return 0; //return that nothing was changed
                }
                if(blocks[x][y].xPos <= 0){ //if any block in the new rotation would move it out of the arena
                    return 0; //return that nothing was changed
                }
                if(blocks[x][y].xPos+2 >= arenaWidth){ //same as above if statement
                    return 0; //return that nothing was changed
                }
                if(blocks[x][y].yPos+1 >= arenaHeight){ //same as above if statement
                    return 0; //return that nothing was changed
                }
                if(arena.filled[(int)blocks[x][y].xPos][(int)blocks[x][y].yPos+1] == 1 ||
                    arena.filled[(int)blocks[x][y].xPos][(int)blocks[x][y].yPos+1] == 2){
                    //if the spot the block is going to move to is filled
                    return 0; //return that it cannot drop
                }
            }
        }
        return 1;
    }*/
    void drop(){ //function to drop the piece
        for(int x = 0; x < 4; x++){ //loop from 0 to 3
            for(int y = 0; y < 4; y++){ //loop from 0 to 3
                if(blocks[x][y].yPos != 0.1){ //if the block's y position is initialized
                    //cout<<"A";
                    arena.filled[(int)blocks[x][y].xPos][(int)blocks[x][y].yPos] = 0;
                    blocks[x][y].yPos+=0; //drop it one space. do so for each loop, for every piece in the block
                    arena.filled[(int)blocks[x][y].xPos][(int)blocks[x][y].yPos+2] = 1;
                }
            }
        }
    }
    int gameDrop(){ //game's drop function. no user input
        drop(); //drop the piece 1 space
        return 1; //return that it dropped 1 space
    }
    int userDrop(){ //user's drop function. user input
        if((GetKeyState(VK_DOWN) & 0x80) != 0){ //if the user is pressing the down key
            drop(); //drop the piece 1 space
            return 1; //return that it dropped 1 space
        }
        return 0; //if the user did not press the down key, return that it did not move
    }
    int userShift(){ //user's shift function (left or right shift)
        if((GetKeyState(VK_LEFT) & 0x80) != 0){ //if the left key is pressed
            for(int i = 0; i < 4; i++){ //loop from 0 to 3
                if(blocks[rotation][i].xPos-1 <= 0 && blocks[rotation][i].xPos != 0.1){ //if the new position would be outside of the arena
                    return 0; //exit the function, return that it did not move any blocks
                }
                int x = blocks[rotation][i].xPos;
                int y = blocks[rotation][i].yPos;
                if(arena.filled[x-2][y] != 0){ //if the spot the block is going to move to is filled
                    return 0; //return that it cannot drop
                }
            }
            for(int i = 0; i < 4; i++){ //loop from 0 to 3
                for(int it = 0; it < 4; it++){ //loop from 0 to 3
                    if(blocks[i][it].xPos != 0.1){ //if the block's x position is not uninitialized
                        blocks[i][it].xPos--; //decrease the x position by 1
                        blocks[i][it].xPos--; //decrease the x position by 1
                    }
                }
            }
            return -1; //return that the positon was shifted 1 to the left
        }
        else if((GetKeyState(VK_RIGHT) & 0x80) != 0){ //if the right key is pressed
            for(int i = 0; i < 4; i++){ //loop from 0 to 3
                if(blocks[rotation][i].xPos+3 >= arenaWidth && blocks[rotation][i].xPos != 0.1){ //if the new position would be outside of the arena
                    //note: it is xPos+3 because the x p\\\\\\\\\\\\\\\\\\\\\\\\osition is this part of the piece -->|_|, so it needs to check past the other 2 pieces
                    return 0; //exit the function, return that it did not move any blocks
                }
                int x = blocks[rotation][i].xPos;
                int y = blocks[rotation][i].yPos;
                if(arena.filled[x+2][y] != 0){ //if the spot the block is going to move to is filled
                    return 0; //return that it cannot drop
                }
            }
            for(int i = 0; i < 4; i++){ //loop from 0 to 3
                for(int it = 0; it < 4; it++){ //loop from 0 to 3
                    if(blocks[i][it].xPos != 0.1){ //if the block's x position is not unitialized
                        blocks[i][it].xPos++; //increase the x position by 1
                        blocks[i][it].xPos++; //increase the x position by 1
                    }
                }
            }
            return 1; //return that the positon was shifted 1 to the right
        }
        return 0; //if it got here without moving blocks, return that it did not move any blocks
    }
    int userRotate(){ //user rotation functiom. user input
        if((GetKeyState(VK_UP) & 0x80) != 0 && type != 3){ //if the user presses the up key
            if(rotation == 0){ //if the rotation was 0
                rotation = 1; //set the rotation to 1
            }
            else if(rotation == 1){ //if the rotation was 1
                if(type == 0 || type == 4 || type == 6){ //if the type was 0, 4, or 6
                    rotation = 0; //set the new rotation to 0
                }
                else{ //if the type was anything else
                    rotation = 2; //set the new rotation to 2
                }
            }
            else if(rotation == 2){ //type 0,4,6 rotation will never be 2 or 3. if the rotation is 2
                rotation = 3; //set the new rotation to 3
            }
            else if(rotation == 3){ //if the rotation is 3
                rotation = 0; //set the rotation to 0
            }
            return 1; //if the up key was pressed and it reached here, a rotation happened, so return that a rotation happened
        }
        return 0; //if the up key was not pressed, return that nothing was changed
    }
    void erase(){ //function to call destroy function for individual blocks
        blocks[rotation][0].destroy(); //destroy first block
        //blocks[rotation][1].destroy(); //destroy second
        //blocks[rotation][2].destroy(); //destroy third
        //blocks[rotation][3].destroy(); //destroy fourth
    }
    void draw(){ //function to call make function for individual blocks
        blocks[rotation][0].make(); //make first block
        //blocks[rotation][1].make(); //make second block
        //blocks[rotation][2].make(); //make third block
        //blocks[rotation][3].make(); //make fourth block
    }
};

class iShape : public shape{
    public:
    iShape(){
        dropTimer = clock();
        for(int it = 0; it < 4; it++){
            for(int iter = 0; iter < 4; iter++){
                blocks[it][iter].xPos = 0.1;
                blocks[it][iter].yPos = 0.1;
            }
        }
        type = 0;
        rotation = 0; //block is not rotated when spawned
        //0 rotation
        //left
        blocks[0][0].xPos = arenaWidth/2 - 2;
        blocks[0][0].yPos = 1;
        //center
        blocks[0][1].xPos = arenaWidth/2;
        blocks[0][1].yPos = 1;
        //right
        blocks[0][2].xPos = arenaWidth/2 + 2;
        blocks[0][2].yPos = 1;
        //far right
        blocks[0][3].xPos = arenaWidth/2 + 4;
        blocks[0][3].yPos = 1;
        //1 rotation
        //top
        blocks[1][0].xPos = arenaWidth/2;
        blocks[1][0].yPos = 1;
        //center
        blocks[1][1].xPos = arenaWidth/2;
        blocks[1][1].yPos = 2;
        //below center
        blocks[1][2].xPos = arenaWidth/2;
        blocks[1][2].yPos = 3;
        //bottom
        blocks[1][3].xPos = arenaWidth/2;
        blocks[1][3].yPos = 4;
        arena.filled[arenaWidth/2 - 2][1] = 1;
        arena.filled[arenaWidth/2][1] = 1;
        arena.filled[arenaWidth/2 + 2][1] = 1;
        arena.filled[arenaWidth/2 + 4][1] = 1;
        draw();
    }
};

class jShape : public shape{
    public:
    jShape(){
        dropTimer = clock();
        for(int it = 0; it < 4; it++){
            for(int iter = 0; iter < 4; iter++){
                blocks[it][iter].xPos = 0.1;
                blocks[it][iter].yPos = 0.1;
            }
            arena.filled[0][it] = 1;
        }
        type = 1;
        rotation = 0; //block is not rotated when spawned
        //0 rotation
        //left
        blocks[0][0].xPos = arenaWidth/2 - 2;
        blocks[0][0].yPos = 1;
        //center
        blocks[0][1].xPos = arenaWidth/2;
        blocks[0][1].yPos = 1;
        //right
        blocks[0][2].xPos = arenaWidth/2 + 2;
        blocks[0][2].yPos = 1;
        //bottom
        blocks[0][3].xPos = arenaWidth/2 + 2;
        blocks[0][3].yPos = 2;
        //1 rotation
        //left
        blocks[1][0].xPos = arenaWidth/2 - 2;
        blocks[1][0].yPos = 3;
        //top
        blocks[1][1].xPos = arenaWidth/2;
        blocks[1][1].yPos = 1;
        //center
        blocks[1][2].xPos = arenaWidth/2;
        blocks[1][2].yPos = 2;
        //bottom
        blocks[1][3].xPos = arenaWidth/2;
        blocks[1][3].yPos = 3;
        //2 rotation
        //top
        blocks[2][0].xPos = arenaWidth/2 - 2;
        blocks[2][0].yPos = 1;
        //left
        blocks[2][1].xPos = arenaWidth/2 - 2;
        blocks[2][1].yPos = 2;
        //center
        blocks[2][2].xPos = arenaWidth/2;
        blocks[2][2].yPos = 2;
        //right
        blocks[2][3].xPos = arenaWidth/2 + 2;
        blocks[2][3].yPos = 2;
        //3 rotation
        //top
        blocks[3][0].xPos = arenaWidth/2;
        blocks[3][0].yPos = 1;
        //center
        blocks[3][1].xPos = arenaWidth/2;
        blocks[3][1].yPos = 2;
        //bottom
        blocks[3][2].xPos = arenaWidth/2;
        blocks[3][2].yPos = 3;
        //right
        blocks[3][3].xPos = arenaWidth/2 + 2;
        blocks[3][3].yPos = 1;
        draw();
    }
};

class lShape : public shape{
    public:
    lShape(){
        dropTimer = clock();
        for(int it = 0; it < 4; it++){
            for(int iter = 0; iter < 4; iter++){
                blocks[it][iter].xPos = 0.1;
                blocks[it][iter].yPos = 0.1;
            }
            arena.filled[0][it] = 1;
        }
        type = 2;
        rotation = 0; //block is not rotated when spawned
        //0 rotation
        //bottom
        blocks[0][0].xPos = arenaWidth/2 - 2;
        blocks[0][0].yPos = 2;
        //left
        blocks[0][1].xPos = arenaWidth/2 - 2;
        blocks[0][1].yPos = 1;
        //center
        blocks[0][2].xPos = arenaWidth/2;
        blocks[0][2].yPos = 1;
        //right
        blocks[0][3].xPos = arenaWidth/2 + 2;
        blocks[0][3].yPos = 1;
        //1 rotation
        //left
        blocks[1][0].xPos = arenaWidth/2 - 2;
        blocks[1][0].yPos = 1;
        //top
        blocks[1][1].xPos = arenaWidth/2;
        blocks[1][1].yPos = 1;
        //center
        blocks[1][2].xPos = arenaWidth/2;
        blocks[1][2].yPos = 2;
        //bottom
        blocks[1][3].xPos = arenaWidth/2;
        blocks[1][3].yPos = 3;
        //2 rotation
        //left
        blocks[2][0].xPos = arenaWidth/2 - 2;
        blocks[2][0].yPos = 2;
        //center
        blocks[2][1].xPos = arenaWidth/2;
        blocks[2][1].yPos = 2;
        //right
        blocks[2][2].xPos = arenaWidth/2 + 2;
        blocks[2][2].yPos = 2;
        //top
        blocks[2][3].xPos = arenaWidth/2 + 2;
        blocks[2][3].yPos = 1;
        //3 rotation
        //top
        blocks[3][0].xPos = arenaWidth/2;
        blocks[3][0].yPos = 1;
        //center
        blocks[3][1].xPos = arenaWidth/2;
        blocks[3][1].yPos = 2;
        //bottom
        blocks[3][2].xPos = arenaWidth/2;
        blocks[3][2].yPos = 3;
        //right
        blocks[3][3].xPos = arenaWidth/2 + 2;
        blocks[3][3].yPos = 3;
        draw();
    }
};

class oShape : public shape{
    public:
    oShape(){
        dropTimer = clock();
        for(int it = 0; it < 4; it++){
            for(int iter = 0; iter < 4; iter++){
                blocks[it][iter].xPos = 0.1;
                blocks[it][iter].yPos = 0.1;
            }
            arena.filled[0][it] = 1;
        }
        type = 3;
        rotation = 0; //block is not rotated when spawned. o shape is never rotated
        //0 rotation
        //below left
        blocks[0][0].xPos = arenaWidth/2 - 2;
        blocks[0][0].yPos = 2;
        //left
        blocks[0][1].xPos = arenaWidth/2 - 2;
        blocks[0][1].yPos = 1;
        //center
        blocks[0][2].xPos = arenaWidth/2;
        blocks[0][2].yPos = 1;
        //below center
        blocks[0][3].xPos = arenaWidth/2;
        blocks[0][3].yPos = 2;
        draw();
    }
};

class sShape : public shape{
    public:
    sShape(){
        dropTimer = clock();
        for(int it = 0; it < 4; it++){
            for(int iter = 0; iter < 4; iter++){
                blocks[it][iter].xPos = 0.1;
                blocks[it][iter].yPos = 0.1;
            }
            arena.filled[0][it] = 1;
        }
        type = 4;
        rotation = 0; //block is not rotated when spawned
        //0 rotation
        //left
        blocks[0][0].xPos = arenaWidth/2 - 2;
        blocks[0][0].yPos = 2;
        //bottom
        blocks[0][1].xPos = arenaWidth/2;
        blocks[0][1].yPos = 2;
        //center
        blocks[0][2].xPos = arenaWidth/2;
        blocks[0][2].yPos = 1;
        //right
        blocks[0][3].xPos = arenaWidth/2 + 2;
        blocks[0][3].yPos = 1;
        //1 rotation
        //bottom
        blocks[1][0].xPos = arenaWidth/2;
        blocks[1][0].yPos = 3;
        //center
        blocks[1][1].xPos = arenaWidth/2;
        blocks[1][1].yPos = 2;
        //right
        blocks[1][2].xPos = arenaWidth/2 + 2;
        blocks[1][2].yPos = 2;
        //top
        blocks[1][3].xPos = arenaWidth/2 + 2;
        blocks[1][3].yPos = 1;
        draw();
    }
};

class tShape : public shape{
    public:
    tShape(){
        dropTimer = clock();
        for(int it = 0; it < 4; it++){
            for(int iter = 0; iter < 4; iter++){
                blocks[it][iter].xPos = 0.1;
                blocks[it][iter].yPos = 0.1;
            }
            arena.filled[0][it] = 1;
        }
        type = 5;
        rotation = 0; //block is not rotated when spawned
        //0 rotation
        //left
        blocks[0][0].xPos = arenaWidth/2 - 2;
        blocks[0][0].yPos = 1;
        //center
        blocks[0][1].xPos = arenaWidth/2;
        blocks[0][1].yPos = 1;
        //bottom
        blocks[0][2].xPos = arenaWidth/2;
        blocks[0][2].yPos = 2;
        //right
        blocks[0][3].xPos = arenaWidth/2 + 2;
        blocks[0][3].yPos = 1;
        //1 rotation
        //left
        blocks[1][0].xPos = arenaWidth/2 - 2;
        blocks[1][0].yPos = 2;
        //center
        blocks[1][1].xPos = arenaWidth/2;
        blocks[1][1].yPos = 2;
        //top
        blocks[1][2].xPos = arenaWidth/2;
        blocks[1][2].yPos = 1;
        //bottom
        blocks[1][3].xPos = arenaWidth/2;
        blocks[1][3].yPos = 3;
        //2 rotation
        //left
        blocks[2][0].xPos = arenaWidth/2 - 2;
        blocks[2][0].yPos = 2;
        //center
        blocks[2][1].xPos = arenaWidth/2;
        blocks[2][1].yPos = 2;
        //top
        blocks[2][2].xPos = arenaWidth/2;
        blocks[2][2].yPos = 1;
        //right
        blocks[2][3].xPos = arenaWidth/2+2;
        blocks[2][3].yPos = 2;
        //3 rotation
        //top
        blocks[3][0].xPos = arenaWidth/2;
        blocks[3][0].yPos = 1;
        //center
        blocks[3][1].xPos = arenaWidth/2;
        blocks[3][1].yPos = 2;
        //bottom
        blocks[3][2].xPos = arenaWidth/2;
        blocks[3][2].yPos = 3;
        //right
        blocks[3][3].xPos = arenaWidth/2 + 2;
        blocks[3][3].yPos = 2;
        draw();
    }
};

class zShape : public shape{
    public:
    zShape(){
        dropTimer = clock();
        for(int it = 0; it < 4; it++){
            for(int iter = 0; iter < 4; iter++){
                blocks[it][iter].xPos = 0.1;
                blocks[it][iter].yPos = 0.1;
            }
            arena.filled[0][it] = 1;
        }
        type = 6;
        rotation = 0; //block is not rotated when spawned
        //0 rotation
        //left
        blocks[0][0].xPos = arenaWidth/2 - 2;
        blocks[0][0].yPos = 1;
        //center
        blocks[0][1].xPos = arenaWidth/2;
        blocks[0][1].yPos = 1;
        //bottom
        blocks[0][2].xPos = arenaWidth/2;
        blocks[0][2].yPos = 2;
        //right
        blocks[0][3].xPos = arenaWidth/2 + 2;
        blocks[0][3].yPos = 2;
        //1 rotation
        //center
        blocks[1][0].xPos = arenaWidth/2;
        blocks[1][0].yPos = 2;
        //bottom
        blocks[1][1].xPos = arenaWidth/2;
        blocks[1][1].yPos = 3;
        //right
        blocks[1][2].xPos = arenaWidth/2 + 2;
        blocks[1][2].yPos = 2;
        //top
        blocks[1][3].xPos = arenaWidth/2 + 2;
        blocks[1][3].yPos = 1;
        draw();
    }
};

int main()
{
    srand(time(NULL));
    while(true){
    //rand() % 7 + 1
        int x = 1;
        switch(x){
            case 1:{
                setConsoleColor(10);
                iShape piece;
                while(piece.move()){
                    Sleep(100);
                }
                break;
            }
            case 2:{
                setConsoleColor(14);
                jShape piece;
                while(piece.move()){
                    Sleep(100);
                }
                break;
            }
            case 3:{
                setConsoleColor(11);
                lShape piece;
                while(piece.move()){
                    Sleep(100);
                }
                break;
            }
            case 4:{
                setConsoleColor(12);
                oShape piece;
                while(piece.move()){
                    Sleep(100);
                }
                break;
            }
            case 5:{
                setConsoleColor(13);
                sShape piece;
                while(piece.move()){
                    Sleep(100);
                }
                break;
            }
            case 6:{
                setConsoleColor(7);
                tShape piece;
                while(piece.move()){
                    Sleep(100);
                }
                break;
            }
            case 7:{
                setConsoleColor(15);
                zShape piece;
                while(piece.move()){
                    Sleep(100);
                }
                break;
            }
        }
    }
    Sleep(100000);
    return 0;
}
