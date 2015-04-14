#include <curses.h>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

vector<string>::iterator it;
vector<int>::iterator iter, iter2;

class block_class{
    public:
    int x_pos;
    int y_pos;
    int rotation;
    int current_piece;
    vector<int> positions;

    void init(int y, int x, int current){
        y_pos = y;
        x_pos = x;
        rotation = 1;
        current_piece = current;
        make();
    }

    void make(){
        switch(current_piece){
            case 1: //left_L;
            {
                make_left_L();
            }
            case 2: //right_L
            {
                make_right_L();
            }
            case 3: //square
            {
                make_square();
            }
            case 4: //line
            {
                make_line();
            }
            case 5: //T
            {
                make_T();
            }
            case 6: //left_Z
            {
                make_left_Z();
            }
            case 7: //right_Z
            {
                make_right_Z();
            }
        }
    }

    void destroy(){
        int y;
        int x;
        for(iter = positions.begin(); iter != positions.end(); iter++){
            iter2 = iter;
            iter2++;
            y = *iter;
            x = *iter2;
            mvaddch(y, x, ' ');
        }
        refresh();
        positions.clear();
    }

    void bottomed(){
        positions.clear();
    }

    void make_single(){
        mvhline(y_pos, x_pos+1, '_', 1);
        positions.push_back(y_pos);
        positions.push_back(x_pos+1);
        mvvline(y_pos+1, x_pos, '|', 1);
        positions.push_back(y_pos+1);
        positions.push_back(x_pos);
        mvvline(y_pos+1, x_pos+2, '|', 1);
        positions.push_back(y_pos+1);
        positions.push_back(x_pos+2);
        mvhline(y_pos+1, x_pos+1, '_', 1);
        positions.push_back(y_pos+1);
        positions.push_back(x_pos+1);
    }

    void rotate(){
        if(rotation == 4){
            rotation -= 3;
        }
        else{
            rotation += 1;
        }
        make();
    }

    void make_left_L(){
        switch(rotation){
            case 1: //left_L_up
            {
                make_single();
                y_pos += 1;
                make_single();
                y_pos += 1;
                make_single();
                x_pos += 2;
                make_single();
                y_pos -= 2;
                x_pos -= 2;
                break;
            }
            case 2: //left_L_right
            {
                make_single();
                x_pos += 2;
                make_single();
                x_pos += 2;
                make_single();
                y_pos += 1;
                x_pos -= 4;
                make_single();
                y_pos -= 1;
                break;
            }
            case 3: //left_L_down
            {
                make_single();
                x_pos += 2;
                make_single();
                y_pos += 1;
                make_single();
                y_pos += 1;
                make_single();
                x_pos -= 2;
                y_pos -= 2;
                break;
            }
            case 4: //left_L_left
            {
                y_pos += 1;
                make_single();
                x_pos += 2;
                make_single();
                x_pos += 2;
                make_single();
                y_pos -= 1;
                make_single();
                x_pos -= 4;
                break;
            }
        }
        refresh();
    }

    void make_right_L(){

    }

    void make_square(){

    }

    void make_line(){

    }

    void make_T(){

    }

    void make_left_Z(){

    }

    void make_right_Z(){

    }
};

class area_class{
    public:
    void make_area(int x_bounds, int y_bounds){
        mvhline(56, (LINES/2), '_', x_bounds);
        mvvline(2, (LINES/2), '|', y_bounds);
        mvvline(2, (LINES/2 + x_bounds), '|', y_bounds);
        refresh();
    }
};

int main(){
    int counter = 0;

    block_class current_piece;
    area_class area;

    vector<string> placed;

	int ch;

	initscr();			/* Start curses mode 		*/
    resize_term(57, 80);
    string msg = "Press ESC to exit.";
    printw(msg.c_str());
	start_color();			/* Start the color functionality */
	cbreak();			/* Line buffering disabled, Pass on
					 * every thing to me 		*/
	keypad(stdscr, TRUE);		/* need F1 	*/
	noecho();
	nodelay(stdscr, TRUE);

    area.make_area(30, 56);

    current_piece.init(1, LINES/2 + 30/2, 1);

    while(true){
        ch = getch();
        if(ch == 27){
            break;
        }
        if(counter < 10){
            if(ch == KEY_UP){
                current_piece.rotate();
                current_piece.destroy();
            }
            if(ch == KEY_RIGHT){
                if(current_piece.x_pos+3 < 30){
                    current_piece.x_pos += 3;
                    current_piece.destroy();
                }
            }
            if(ch == KEY_LEFT){
                if(current_piece.x_pos-3 > 0){
                    current_piece.x_pos -= 3;
                    current_piece.destroy();
                }
            }
            if(ch == KEY_DOWN){
                current_piece.y_pos += 3;
                current_piece.destroy();
            }
            if(ch == ' '){
                current_piece.y_pos = 50;
                current_piece.destroy();
            }
            current_piece.make();
            if(current_piece.y_pos >= 50){
                current_piece.bottomed();
                current_piece.init(1, LINES/2 + 30/2, 1);
                counter = 10;
            }
            Sleep(100);
        }
        else{
            current_piece.y_pos += 3;
            current_piece.destroy();
            counter = 0;
        }
        counter++;
    }
    endwin();
    return 0;
}

