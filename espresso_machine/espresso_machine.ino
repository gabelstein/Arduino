// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


int button     = 0;
int button_prev = 1;
int input  = 0;
int pos_cursor = 0;
int toogle_pos[] = {}:

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

float tmpis = 10.5;
int tmp_is_coord = 0;
float tmpgoal = 92.5;
int tmp_goal_coord = 16;

int weight_is = 0;
int weight_is_coord = 14;
int weight_goal = 35;
int weight_goal_coord = 30;

int shot_time = 18;
int shot_time_coord = 10;

int preinf_time = 4;
int preinf_time_coord = 7;

void print_int_at_pos(int val, int pos) {
  char buffer [2];
  set_cursor_to_pos(pos);
  sprintf (buffer, "%02u", val);
  lcd.print(buffer);
  set_cursor_to_pos(pos_cursor);
}

void print_float_at_pos(float val, int pos) {
  char buffer [4];
  set_cursor_to_pos(pos);
  dtostrf(val,2,1,buffer);                         
  lcd.print(buffer);
  set_cursor_to_pos(pos_cursor);
}

void set_cursor_to_pos(int pos) {
  int cursor_x = pos%16;
  int cursor_y = pos/16;
  lcd.setCursor(cursor_x, cursor_y);
}


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  set_cursor_to_pos(pos_cursor);
  
  print_float_at_pos(tmpis, tmp_is_coord);
  print_float_at_pos(tmpgoal, tmp_goal_coord);
  print_int_at_pos(weight_is, weight_is_coord);
  print_int_at_pos(weight_goal, weight_goal_coord);
  
  print_int_at_pos(shot_time, shot_time_coord);
  print_int_at_pos(preinf_time, preinf_time_coord);


}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
  set_cursor_to_pos(pos_cursor);
  print_float_at_pos(tmpis, tmp_is_coord);
  print_int_at_pos(weight_is, weight_is_coord);
  lcd.blink();

button = read_LCD_buttons();  // read the buttons
if (button != button_prev) {
  button_action(button);
   button_prev = button;
}
   
 }

int read_LCD_buttons() {
 input = analogRead(0);      // Analogwert lesen

 if (input > 1000) return btnNONE; 
 if (input < 50)   return btnRIGHT;  
 if (input < 250)  return btnUP; 
 if (input < 450)  return btnDOWN; 
 if (input < 650)  return btnLEFT; 
 if (input < 850)  return btnSELECT;  
 return btnNONE;  
}

void button_action(int button) {
  switch (button)          
   {
     case btnRIGHT:
       {
       pos_cursor = (pos_cursor + 1);
       break;
       }
     case btnLEFT:
       {
      pos_cursor = (pos_cursor - 1);     
      break;
       }
     case btnUP:
       {
       pos_cursor = (pos_cursor - 16);
       break;
       }
     case btnDOWN:
       {
       pos_cursor = (pos_cursor + 16);
       break;
       }
     case btnSELECT:
       {
       lcd.print("SELECT");
       break;
       }
   }
}
