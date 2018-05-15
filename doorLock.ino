#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//when they line up, that's where a button was pressed


bool kill = false; //not yet implemented, at some point will halt the code and start over from the top when a certain signal is recieved.

char code[4]; //stores the code being worked with

char kyle[4] = {'1','3','3','7'}; //correct codes
bool kTru = true; //boolean for checking whether or not the code lines up

char par[4] = {'5','8','6','2'};
bool pTru = true;

char keys[ROWS][COLS] = { //required for setting up the keypad
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; //the row pins of the keypad
byte colPins[COLS] = {6, 5, 4, 3}; //the column pins of the keypad
//note: Connect in 3-10 order

int buzz =   11; //buzzer that buzzes

char key; //variable that essentially just holds a keypress so it can be moved into the code array


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //actually make the keypad


void buzzPing(int del, int p){ //turn on buzzer p amount of times, for del length of time
  for(int t = 0; t < p; t++){
    digitalWrite(buzz, HIGH);
    delay(del);
    digitalWrite(buzz, LOW);
    delay(100);
  }
}


void setup(){
  Serial.begin(9600); //just for testing purposes
  pinMode(buzz,OUTPUT);
  buzzPing(75,3);
}
  
void loop(){
  for(int i = 0; i < 4; i++){
    do {
      key = keypad.getKey();
    }
    while (not key);
    Serial.println("Grabbed key: " + String(key));
    buzzPing(50,1);
    code[i] = key;
  }
  delay(100);
  for(int u = 0; u < 4; u++){
    Serial.println("Checking row #" + String(u) + ',');
    Serial.println("Code: " + String(code[u]) + " Kyle: " + String(kyle[u]) +  " Parents: " + String(par[u]));
    if(code[u] != kyle[u]){ //check each value in the array to see if they line up
      kTru = false;
    } else if(code[u] != par[u]){
      pTru = false;
    }
    Serial.println("kTru: " + String(kTru) + ", pTru: " + String(pTru));
  }
  if(not kTru && not pTru){
    buzzPing(1000,1); //input didn't match an existing code
    
  }else{
    //this project never reached completion, this section was meant to open a door.
  }
  kTru = true;
  pTru = true;
}


