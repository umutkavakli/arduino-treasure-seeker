#include "treasure_seeker.h"
#include "Arduino.h"
#include "avr/io.h"
#include "util/delay.h"
#include "stdlib.h"
#include "time.h"
#include "hd44780/HD44780.hpp"
#include <avr/eeprom.h>
#include <LiquidCrystal.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int humanx = THRESHOLD/2, humany = THRESHOLD/2; //Start human character in the middle of map
int dinox, dinoy;
int robotx, roboty;
int sadx, sady;
int treasurex, treasurey;
int hor = 7, ver = 1;

int main(void)
{
	char str1[20];
	int status;
	int sec = 0;
	int min = 0;
	int start = 1;

	uint16_t seed = eeprom_read_word(0);
	randomSeed(seed++); //Returning random numbers every time to assign location of characters
	eeprom_write_word(0, seed);

	DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); //Setting LEDs as output
	PORTB |= (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB4) | (1<<PORTB5); //Setting LEDs as 1 - HIGH at the first time (Don't blink)
	DDRD &= ~(1<<DDD0) | ~(1<<DDD1) | ~(1<<DDD2) | ~(1<<DDD3); //Setting buttons as input

	characterInitializer();
	startCreatures();

	lcd.begin(16, 2); //Start LCD

	//To start press any button
	while(start){
		for(int i = 15; i >= 0; i--){
		    lcd.setCursor(i, 1);
		    lcd.print("PRESS TO START!");
		    lcd.setCursor(0, 0);
		    lcd.print("TREASURE  SEEKER");
		    lcd.setCursor(14, 0);
		    _delay_ms(400);
		    lcd.clear();
		    if (!(PIND & 1 << PIND0) || !(PIND & 1 << PIND1) || !(PIND & 1 << PIND2) || !(PIND & 1 << PIND3)){
		    	start = 0;
		    	break;
		    }
		  }
	}

	_delay_ms(500);
	lcd.setCursor(hor, ver);
	lcd.write(byte(0));

	while(1){

		if (!(PIND & 1 << PIND0)){
			toUp();
			_delay_ms(500);
		}

		if (!(PIND & 1 << PIND1)){
			toRight();
			_delay_ms(500);
		}

		if (!(PIND & 1 << PIND2)){
			toLeft();
			_delay_ms(500);
		}

		if (!(PIND & 1 << PIND3)){
			toDown();
			_delay_ms(500);
		}

		//If you find the treasure, return 1 to show that you won
		if (humanx == treasurex && humany == treasurey){
			status = 1;
			break;
		};

		//If you touch other creatures, return 0 to show that you lost
		if ((humanx == dinox && humany == dinoy) || (humanx == robotx && humany == roboty) || (humanx == sadx && humany == sady)){
			status = 0;
			break;
		}

		creatureChecker(treasurex, treasurey, 5, 11111000);
		creatureChecker(dinox, dinoy, 4, byte(1));
		creatureChecker(robotx, roboty, 3, byte(2));
		creatureChecker(sadx, sady, 2, byte(3));

		sec++;
	}

	min = sec / 60;
	sec = sec % 60;
	sprintf(str1, "TIME: %d:%d", min, sec);

	lcd.clear();
	lcd.setCursor(4,0);

	if (status)
		lcd.write("YOU WON!");
	else
		lcd.write("YOU LOST!");

	lcd.setCursor(0,1);
	lcd.print(str1);
}

void creatureChecker(int x, int y, int port, uint8_t creature){
	int distance;

	//To show all of the characters at the same time, when you are in the same rows or columns with other creatures or treasure
	if (humanx >= x && humanx - x <= 7 && humany - y >= 0 && humany - y <= 1){
			lcd.clear();
			lcd.setCursor(hor, ver);
			lcd.write(byte(0));

			if (7 - (humanx - x) <= x && y <= 1 && humany <= 1 && humanx <= 7)
				lcd.setCursor(7 - (humanx - x), y);
			else if (x <= 7 && y <= 1 && humany <= 1 )
				lcd.setCursor(x, y);
			else if (7 - (humanx - x) <= x && y >= 1 && x <= 7)
				lcd.setCursor(7 - (humanx - x), 1 - (humany - y));
			else if(x <= 7 && y >= 1)
				lcd.setCursor(x, 1 - (humany - y));
			else if (THRESHOLD - x < 7 && humanx - x <= 7 && y <= 1 && humany <= 1)
				lcd.setCursor(13 - (THRESHOLD - x), y);
			else if (THRESHOLD - x < 7 && humanx - x <= 7 && y >= 1)
				lcd.setCursor(13 - (THRESHOLD - x), 1 - (humany - y));
			else
				lcd.setCursor(7 - (humanx - x), 1 - (humany - y));
			lcd.write(creature);
			_delay_ms(100);

	}else if (humanx <= x && x - humanx <= 7 && humany - y >= 0 && humany - y <= 1){
			lcd.clear();
			lcd.setCursor(hor, ver);
			lcd.write(byte(0));

			//If statements to go to beginning and end of the lines
			if (x <= 7 && y <= 1 && humany <= 1)
				lcd.setCursor(x, y);
			else if (x <= 7 && y >= 1)
				lcd.setCursor(x, 1 - (humany - y));
			else if (THRESHOLD - x < 7 && x - humanx <= 7 && 7 - (x - humanx) <= THRESHOLD - x)
				lcd.setCursor(6 + (x - humanx), 1 - (humany - y));
			else if (THRESHOLD - humanx <= 7)
				lcd.setCursor(13 - (THRESHOLD - x), 1 - (humany - y));
			else
				lcd.setCursor(7 + (x - humanx), 1 - (humany - y));
			lcd.write(creature);
			_delay_ms(100);

	}else{
		//If there is no anything but your character, to show it
		lcd.clear();
		lcd.setCursor(hor, ver);
		lcd.write(byte(0));
		_delay_ms(100);
	}

	/*Calculating distance between your character and other creatures or treasure
	 * after that, to show proximity blink LED if it's close to you more than 15 units*/
	distance = sqrt(pow(humanx - x, 2) + pow(humany - y, 2));
	if (distance <= 10){
		PORTB ^= (1 << port);
		_delay_ms(100);
	}else{
		PORTB |= (1 << port);
	}
}

//Following 4 functions controls where you are going and show it in a navigation with right side of LCD, when you push the buttons
void toUp(){
	if (humany != 0) humany--;

	if (humany <= 1){
		ver = humany;
		lcd.clear();
		lcd.setCursor(hor, ver);
		lcd.write(byte(0));
	}else{
		ver = 1;
		lcd.clear();
		lcd.setCursor(hor, ver);
		lcd.write(byte(0));
	}

	lcd.setCursor(15, 0);
	lcd.write(byte(4));

	if (humany < 10){
		lcd.setCursor(14, 1);
		lcd.println(0);
		lcd.setCursor(15, 1);
		lcd.println(humany);
	}else{
		lcd.setCursor(14, 1);
		lcd.println(humany);
	}
}

void toDown(){
	if (humany != THRESHOLD) humany++;

	if (humany <= 1){
		ver = humany;
		lcd.clear();
		lcd.setCursor(hor, ver);
		lcd.write(byte(0));
	}

	lcd.setCursor(15, 0);
	lcd.write(byte(5));

	if (humany < 10){
		lcd.setCursor(14, 1);
		lcd.println(0);
		lcd.setCursor(15, 1);
		lcd.println(humany);
	}else{
		lcd.setCursor(14, 1);
		lcd.println(humany);
	}
}

void toRight(){
	if (humanx != THRESHOLD) humanx++;

	if ((THRESHOLD - humanx) <= 6){
		hor = 13-(THRESHOLD-humanx);
		lcd.clear();
		lcd.setCursor(hor, ver);
		lcd.write(byte(0));
	}else if(humanx <= 7){
		hor = humanx;
		lcd.clear();
		lcd.setCursor(hor, ver);
		lcd.write(byte(0));
	}

	lcd.setCursor(15, 0);
	lcd.write(byte(6));

	if (humanx < 10){
		lcd.setCursor(14, 1);
		lcd.println(0);
		lcd.setCursor(15, 1);
		lcd.println(humanx);
	}else{
		lcd.setCursor(14, 1);
		lcd.println(humanx);
	}
}

void toLeft(){
	if (humanx != 0) humanx--;

	if (humanx <= 7){
		hor = humanx;
		lcd.clear();
		lcd.setCursor(hor, ver);
		lcd.write(byte(0));
	}else if((THRESHOLD - humanx) <= 6){
		hor = 13-(THRESHOLD-humanx);
		lcd.clear();
		lcd.setCursor(hor, ver);
		lcd.write(byte(0));
	}

	lcd.setCursor(15, 0);
	lcd.write((byte)7);

	if (humanx < 10){
		lcd.setCursor(14, 1);
		lcd.println(0);
		lcd.setCursor(15, 1);
		lcd.println(humanx);
	}else{
		lcd.setCursor(14, 1);
		lcd.println(humanx);
	}
}

void startCreatures(){
	//Assign random location numbers in x and y dimensions from 0 to THRESHOLD
	dinox = random()%THRESHOLD, dinoy = random()%THRESHOLD;
	robotx = random()%THRESHOLD, roboty = random()%THRESHOLD;
	sadx = random()%THRESHOLD, sady = random()%THRESHOLD;
	treasurex = random()%THRESHOLD, treasurey = random()%THRESHOLD;
	_delay_ms(100);
}

void characterInitializer(){
	//Creating characters to use in the LCD screen
	  static byte characters[] = {
			  // HUMAN
			  B01110,
			  B01110,
			  B10101,
			  B01110,
			  B00100,
			  B01110,
			  B10001,
			  B10001,
			  // DINO
			  B01110,
			  B10111,
			  B11110,
			  B11111,
			  B11000,
			  B11111,
			  B11010,
			  B10010,
			  // ROBOT
			  B11111,
			  B11111,
			  B10101,
			  B11111,
			  B00100,
			  B11011,
			  B11011,
			  B11011,
			  // SAD
			  B00000,
			  B00000,
			  B00000,
			  B01010,
			  B00000,
			  B01110,
			  B10001,
			  B00000,
			  // UP
			  B00100,
			  B01110,
			  B10101,
			  B00100,
			  B00100,
			  B00100,
			  B00100,
			  B00000,
			  // DOWN
			  B00100,
			  B00100,
			  B00100,
			  B00100,
			  B10101,
			  B01110,
			  B00100,
			  B00000,
			  // RIGHT
			  B01000,
			  B00100,
			  B00010,
			  B11111,
			  B00010,
			  B00100,
			  B01000,
			  B00000,
			  // LEFT
			  B00010,
			  B00100,
			  B01000,
			  B11111,
			  B01000,
			  B00100,
			  B00010,
			  B00000,
	  };

	  for (int i = 0; i < 8; i++) {
	  	  lcd.createChar(i, &characters[i * 8]);
	  }
	  _delay_ms(100);
}
