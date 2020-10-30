 
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI - comment this out to use with standard arduinos
#include <LiquidCrystal_I2C.h>          // for LCD w/ GPIO MODIFIED for the ATtiny85

#define GPIO_ADDR     0x27             // (PCA8574A A0-A2 @5V) typ. A0-A3 Gnd 0x20 / 0x38 for A - 0x27 is the address of the Digispark LCD modules.
#define startspeed 1000
#define speedup 10

LiquidCrystal_I2C lcd(GPIO_ADDR,16,2);  // set address & 16 chars / 2 lines

const int HIGHPIN = 4;
const int BUTTPIN = 1;
const int CHICKENROW = 2;
int speed;
int chickenLine ;
int uptimer;
int score;
bool gameover ;
byte chicken[8] = {
  // 0:dino chicken
    B00010,
    B00011,
    B01010,
    B11111,
    B11110,
    B01110,
    B00100,
    B00100};

    byte chickenUpSide[8] = {
  // 0:dino chicken
   B00100, 
   B00100,
   B01110,
   B11110,
   B11111,
   B01010,
   B00011,          
   B00010 
   };


 byte cactus1[8] = {
  // 0:dino chicken
    B00000,
    B00100,
    B10100,
    B01100,
    B00101,
    B00110,
    B00100,
    B00100};    

int cactuspos  ;


  
//I2C Address: 0x27 16col 2 rows
 
void setup() {
  // put your setup code here, to run once:
  ///added here 
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);


cactuspos =16;
chickenLine=1;
uptimer=0;
gameover=0;
score=0;
speed=startspeed;
pinMode(BUTTPIN, INPUT);
pinMode(HIGHPIN, OUTPUT); 
//glyphs[4][8]
    digitalWrite(HIGHPIN, HIGH);
     lcd.createChar(0,  chicken );
       lcd.createChar(1,  cactus1 );
         lcd.createChar(2,  chickenUpSide );
       
     
}



void loop() {
  // put your main code here, to run repeatedly:
lcd.clear();
bool but = digitalRead( BUTTPIN);

if(!gameover){
     lcd.setCursor(13, 0);
  lcd.print(  String(score));

if(but and chickenLine==1){chickenLine =0;}//and chickenLine==1 prevent holding button
else{chickenLine =1;}
 

lcd.setCursor(CHICKENROW, chickenLine);
  lcd.write(byte(0));


  lcd.setCursor( cactuspos, 1);
  lcd.write(byte(1));
  // 
 //lcd.print(msg);
if(cactuspos == CHICKENROW ){
  if(chickenLine ==1){
    
    gameover=true;
    }else{score+=1;}
  
  }
 delay(1000);
 if(cactuspos>1){
   cactuspos-=1;} else {cactuspos= 16; speed-=speedup;}
}
else{
  lcd.setCursor(CHICKENROW, chickenLine);
  lcd.write(byte(2));
   lcd.setCursor(5, 1);
  lcd.print("GAME OVER!!");
       lcd.setCursor(13, 0);
  lcd.print(  String(score));

  if(but){reset();}
  delay(2000);
  }
}


void reset() {
  // put your setup code here, to run once:
  ///added here 
 
 


cactuspos =16;
chickenLine=1;
uptimer=0;
gameover=0;
score=0;
speed=startspeed; 
      lcd.createChar(0,  chicken );
       lcd.createChar(1,  cactus1 );
         lcd.createChar(2,  chickenUpSide );
       
     
}
