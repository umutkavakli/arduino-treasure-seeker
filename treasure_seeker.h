// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _treasure_seeker_H_
#define _treasure_seeker_H_
#include "Arduino.h"
//add your includes for the project treasure_seeker here
#define LINEX_LEFT 0
#define LINEX_RIGHT 51
#define LINEY_UPPER 0
#define LINEY_LOWER 51


//end of add your includes here


//add your function definitions for the project treasure_seeker here
void toUp();
void toDown();
void toRight();
void toLeft();
void characterInitializer();



//Do not add code below this line
#endif /* _treasure_seeker_H_ */
