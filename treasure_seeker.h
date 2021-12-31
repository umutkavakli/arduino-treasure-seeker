// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _treasure_seeker_H_
#define _treasure_seeker_H_
#include "Arduino.h"
//add your includes for the project treasure_seeker here
#define THRESHOLD 51


//end of add your includes here


//add your function definitions for the project treasure_seeker here
void toUp();
void toDown();
void toRight();
void toLeft();
void characterInitializer();
void startCreatures();
void creatureChecker(int x, int y, int port, uint8_t creature);


//Do not add code below this line
#endif /* _treasure_seeker_H_ */
