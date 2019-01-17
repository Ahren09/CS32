// main.cpp


//I included a lot of stuff here. Should include them in their separate files
//Since We only create a Game object and call its function, we should only include its .h
//This is way more intuitive than considering its entire function call and include files needed by g
#include "Game.h"

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

      // Play the game
    g.play();
}
