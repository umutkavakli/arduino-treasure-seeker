// Do not remove the include below
#include "treasure_seeker.h"
#include "avr/io.h"
#include "util/delay.h"
#include "Arduino.h"
#include <LiquidCrystal.h>
#include "hd44780/HD44780.hpp"

#define THRESHOLD 51

void toUp();
void toDown();
void toRight();
void toLeft();
void characterInitializer();
void startCreatures();

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int humanx = THRESHOLD/2, humany = THRESHOLD/2;
int dinox, dinoy;
int robotx, roboty;
int sadx, sady;
int treasurex, treasurey;
int hor = 7, ver = 1;

int main(void)
{
	DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5);
	PORTB |= (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB4) | (1<<PORTB5);
	DDRD &= ~(1<<DDD0) | ~(1<<DDD1) | ~(1<<DDD2) | ~(1<<DDD3);

	randomSeed(analogRead(0));
	characterInitializer();
	startCreatures();

	lcd.begin(16, 2);
	lcd.setCursor(7,1);
	lcd.write(byte(0));



	while(1){

		if (!(PIND & 1 << PIND0)){
			toUp();
		}

		if (!(PIND & 1 << PIND1)){
			toRight();
		}

		if (!(PIND & 1 << PIND2)){
			toLeft();
		}

		if (!(PIND & 1 << PIND3)){
			toDown();
		}

		//if (humanx == treasurex && humany == treasurey) break;


		if (humanx >= treasurex && humany >= treasurey && humanx - treasurex <= 7 && humany - treasurey <= 1){
				lcd.clear();
				lcd.setCursor(hor, ver);
				lcd.write(byte(0));
				lcd.setCursor(7 - (humanx - treasurex), 1 - (humany-treasurey));
				lcd.write("*");
		}else if(humanx <= treasurex && humany >= treasurey && treasurex - humanx <= 6 && humany - treasurey <= 1){
				lcd.clear();
				lcd.setCursor(hor, ver);
				lcd.write(byte(0));
				lcd.setCursor(7+(treasurex-humanx), 1 - (humany-treasurey));
				lcd.write("*");
		}else{
			lcd.clear();
			lcd.setCursor(hor, ver);
			lcd.write(byte(0));
		}





	}

	lcd.clear();
	lcd.setCursor(4,0);
	lcd.write("YOU WON!");
}

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

	_delay_ms(500);

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

	_delay_ms(500);
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

	_delay_ms(500);
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

	_delay_ms(500);
}

void startCreatures(){
	dinox = random(THRESHOLD), dinoy = random(THRESHOLD);
	robotx = random(THRESHOLD), roboty = random(THRESHOLD);
	sadx = random(THRESHOLD), sady = random(THRESHOLD);
	treasurex = 30, treasurey = 30;
	_delay_ms(100);
}




void characterInitializer(){
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
