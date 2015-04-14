////////////////////////////////////////////////////////////
// Copyright (c) 2009 Rodrigo Castro (redkiing)
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//     1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//
//     2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//
//     3. This notice may not be removed or altered from any source
//     distribution.
//
// Rodrigo Castro redkiing.wordpress.com
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// uInterface.cpp
////////////////////////////////////////////////////////////

#include "uInterface.h"

UInterface::UInterface (Board &boardRef): board(boardRef)
{
    // No movements have been made
    nbTurns = 0;
    // The game starts with the yellow player
    nextPlayer = Yellow;
}

UInterface::~UInterface(){}

void UInterface::placeInColumn(const sf::Input &input)
{
    // Get the column where the user has clicked
    // This is just an approximation, as the columns have a little offset
    // This will work only if the user clicks inside the circle
    column = float(input.GetMouseX())/board.getWindowWidth()*BOARD_X_SIZE+1;
    //If it is game over, create a new one
    if(gameStatus == EndOfGame)
    {
        board.restart();
        nbTurns = 0;
        gameStatus = Full;
    }
    else
    {
        // Try to place the token in the desired column
        gameStatus = board.addTokenInColumn(column, nextPlayer);
        // If the column wasn't already full, continue playing
        if(gameStatus != Full)
        {
            nbTurns++;
            // Change the nextplayer
            if(nextPlayer == Yellow)
                nextPlayer = Red;
            else
                nextPlayer = Yellow;
            // if the board is full: game over!!
            if(nbTurns == BOARD_X_SIZE*BOARD_Y_SIZE)
                gameStatus = EndOfGame;
        }
    }
}
