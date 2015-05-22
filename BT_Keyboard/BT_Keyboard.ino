#include <SoftwareSerial.h>

#define RX_PIN 8
#define TX_PIN 9
#define BT_SPEED 9600
#define BT_DELAY 10
#define MAX_COMMAND_LEN 8

String Command;
byte i = 0;

SoftwareSerial BT(RX_PIN,TX_PIN);

void setup() {
  BT.begin(BT_SPEED);
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  while (BT.available()) {
    delay(BT_DELAY);
    char c = BT.read();
    Command += c;
    i++;
    if ( i >= MAX_COMMAND_LEN ) break;
  }
  if ( i == 1 ) {
    Keyboard.print(Command);
  } else {
    if ( Command.substring(0,3) == "RET" ) {
      Keyboard.press( KEY_RETURN );
      Keyboard.release();
    }
    else if ( Command.substring(0,5) == "MOUSE" ) {
      // doing some mouse movement
      byte x = 0;
      byte y = 0;    
      if ( Command[5] == 'U' )
        y = Command.substring(6,8).toInt() * -1;
      if ( Command[5] == 'D' )
        y = Command.substring(6,8).toInt();
      if ( Command[5] == 'L' )
        x = Command.substring(6,8).toInt() * -1;
      if ( Command[5] == 'R' )
        x = Command.substring(6,8).toInt();
      Mouse.move(x, y);  
    }
  }
  i = 0;  
  Command = "";
}


