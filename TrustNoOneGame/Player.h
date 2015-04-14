#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class player{
    public:
    int locationX;
    int locationY;
    int playerNumber;
    //int locationZ;/
    player(){}
    player(int x, int y){
        locationX = x;
        locationY = y;
    }
};

extern player* playerList; //defined in Client.cpp

#endif // PLAYER_H_INCLUDED
