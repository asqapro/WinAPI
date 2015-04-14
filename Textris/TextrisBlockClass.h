#include <curses.h>
#include <string>
#include <vector>

using namespace std;

class blockStruct{
    public:
        void initB(){
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

    string single(string spaces, int count);
};

class left_L_shape : blockStruct{
    public:
        string left_L_up;
        string left_L_down;
        string left_L_left;
        string left_L_right;

        void make_left_L(int piece, WINDOW *win);
        string rotate();
};

class right_L_shape : blockStruct{
    public:
        string right_L_up;
        string right_L_down;
        string right_L_left;
        string right_L_right;

        void make_right_L();

        string rotate();
};

class square_shape : blockStruct{
    public:
        string square;

        void make_square();
};

class line_shape : blockStruct{
    public:
        string line_up;
        string line_down;

        void make_line();

        string rotate();
};

class T_shape : blockStruct{
    public:
        string T_up;
        string T_down;
        string T_left;
        string T_right;

        void make_T();

        string rotate();
};

class left_Z_shape : blockStruct{
    public:
        string left_Z_up;
        string left_Z_down;

        void make_left_Z();

        string rotate();
};

class right_Z_shape : blockStruct{
    public:
        string right_Z_up;
        string right_Z_down;

        void make_right_Z();

        string rotate();
};
