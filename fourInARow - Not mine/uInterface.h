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
// uInterface.h
////////////////////////////////////////////////////////////

#ifndef UI
#define UI

#include "board.h"

class UInterface
{
    public:
        // Constructor
        UInterface(Board &boardRef);

        // Destructor
        ~UInterface();

        // Called when the mouse has clicked inside the screen
        void placeInColumn(const sf::Input &input);

    private:
        // the column where the mouse clicks the screen
        unsigned int column;

        // A reference to the board, created in the main loop
        Board &board;

        // The total number of tokens the players have placed
        int nbTurns;

        // The color of the next token to be placed
        Token nextPlayer;

        // Whether the game has finished, a token has been placed
        // or it couldn't be placed in a column
        Move gameStatus;
};

#endif
