#include <curses.h>
#include <string>
#include <vector>

using namespace std;

class blockStruct{
    public:
    void initB(){
        single_single = single("", 1);
        single_double = single("", 2);
        single_triple = single("", 3);
        single_quad = single("", 4);
    }
    string single_single;
    protected:
    int x_pos;
    int y_pos;
    int size_x;
    int size_y;
    int rotation;


    string single_double;
    string single_triple;
    string single_quad;

    string single(string spaces, int count){
        string block;
        block += spaces;
        for(int x = 0; x < count; x++){
            block += " _ ";
        }
        block += "\n";
        block += spaces;
        for(int x = 0; x < count; x++){
            block += "|_|";
        }
        return block;
    }
};

class left_L_shape : blockStruct{
    public:
        string left_L_up;
        string left_L_down;
        string left_L_left;
        string left_L_right;

        void make_left_L(int piece, WINDOW *win){
            switch(piece){
                case 1:
                {
                    //left_L_up = (single("", 1) + "\n" + single("", 1) + "\n" + single("", 2));
                    //wvline(win, '-', 10);
                    //whline(win, '_', 10 - 1);
                    string abc = "a";
                    wprintw(win, abc.c_str());
                    //mvvline(30, 30, '|', 3);
                    break;
                }
                case 2:
                    left_L_down = (single("", 2) + "\n" + single("   ", 1) + "\n" + single("   ", 1));
                    break;
                case 3:
                    left_L_left = (single("      ", 1) + "\n" + single("", 3));
                    break;
                case 4:
                    left_L_right = (single("", 3) + "\n" + single("", 1));
                    break;
            }
        }

        string rotate(){
            switch(rotation){
                case 1: //piece is "up"
                    rotation = 4; //flip it right
                    return left_L_right;
                case 2: //piece is "down"
                    rotation = 3;
                    return left_L_left;
                case 3: //piece is facing "left"
                    rotation = 1;
                    return left_L_up;
                case 4: //piece is facing "right"
                    rotation = 2;
                    return left_L_down;
            }
        }
};

class right_L_shape : blockStruct{
    public:
        string right_L_up;
        string right_L_down;
        string right_L_left;
        string right_L_right;

        void make_right_L(){
            right_L_up = ("   " + single_single + "\n   " + single_single + "\n" + single_double);
            right_L_down = (single_double + "\n" + single_single + "\n" + single_single);
            right_L_left = (single_triple + "\n      " + single_single);
            right_L_right = (single_single + "\n" + single_triple);
        }

        string rotate(){
            switch(rotation){
                case 1: //piece is "up"
                    rotation = 4;
                    return right_L_right;
                case 2: //piece is "down"
                    rotation = 3;
                    return right_L_left;
                case 3: //piece is facing "left"
                    rotation = 1;
                    return right_L_up;
                case 4: //piece is facing "right"
                    rotation = 2;
                    return right_L_down;
            }
        }
};

class square_shape : blockStruct{
    public:
        string square;

        void make_square(){
            square = (single_double + "\n" + single_double);
        }
};

class line_shape : blockStruct{
    public:
        string line_up;
        string line_down;

        void make_line(){
            line_up = (single_single + "\n" + single_single + "\n" + single_single + "\n" + single_single);
            line_down = (single_quad);
        }

        string rotate(){
            switch(rotation){
                case 1: //piece is "up"
                    rotation = 2;
                    return line_down;
                case 2: //piece is "down"
                    rotation = 1;
                    return line_up;
            }
        }
};

class T_shape : blockStruct{
    public:
        string T_up;
        string T_down;
        string T_left;
        string T_right;

        void make_T(){
            T_up = ("   " + single_single + "\n" + single_triple);
            T_down = (single_triple + "\n   " + single_single);
            T_left = ("   " + single_single + "\n" + single_double + "\n   " + single_single);
            T_right = (single_single + "\n" + single_double + "\n" + single_single);
        }

        string rotate(){
            switch(rotation){
                case 1: //piece is "up"
                    rotation = 4;
                    return T_right;
                case 2: //piece is "down"
                    rotation = 3;
                    return T_left;
                case 3: //piece is facing "left"
                    rotation = 1;
                    return T_up;
                case 4: //piece is facing "right"
                    rotation = 2;
                    return T_down;
            }
        }
};

class left_Z_shape : blockStruct{
    public:
        string left_Z_up;
        string left_Z_down;

        void make_left_Z(){
            left_Z_up = ("   " + single_single + "\n" + single_double + "\n" + single_single);
            left_Z_down = (single_double + "\n   " + single_double);
        }

        string rotate(){
            switch(rotation){
                case 1: //piece is "up"
                    rotation = 2;
                    return left_Z_down;
                case 2: //piece is "down"
                    rotation = 1;
                    return left_Z_up;
            }
        }
};

class right_Z_shape : blockStruct{
    public:
        string right_Z_up;
        string right_Z_down;

        void make_right_Z(){
            right_Z_up = (single_single + "\n" + single_double + "\n   " + single_single);
            right_Z_down = ("   " + single_double + "\n" + single_double);
        }

        string rotate(){
            switch(rotation){
                case 1: //piece is facing "up"
                    rotation = 2;
                    return right_Z_down;
                case 2: //piece is facing "down"
                    rotation = 1;
                    return right_Z_up;
            }
        }
};

