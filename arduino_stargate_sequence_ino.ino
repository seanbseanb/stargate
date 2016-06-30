/* YourDuino Example: Relay Control 1.10
  Handles "Relay is active-low" to assure
  no relay activation from reset until
  application is ready.
   terry@yourduino.com */

/*-----( Import needed libraries )-----*/
/*-----( Declare Constants )-----*/
#define RELAY_ON 1
#define RELAY_OFF 0

#define SHORT_DELAY 500
#define MED_DELAY 1000
#define LONG_DELAY 20000


/*-----( Declare objects )-----*/
/*-----( Declare Variables )-----*/
#define Relay_1  2  // Arduino Digital I/O pin number
#define Relay_2  3
#define Relay_3  4
#define Relay_4  5
#define Relay_5  6
#define Relay_6  7
#define Relay_7  8
#define Relay_8  9

#include <Serial.h> 
//int byte = 33; 

void setup() {
  // put your setup code here, to run once:
//digitalWrite(Relay, HIGH);
//pinMode(Relay, OUTPUT);
//   Bridge.begin();
//  Console.begin(); 
//-------( Initialize Pins so relays are inactive at reset)----
  digitalWrite(Relay_1, RELAY_OFF);
  digitalWrite(Relay_2, RELAY_OFF);
  digitalWrite(Relay_3, RELAY_OFF);
  digitalWrite(Relay_4, RELAY_OFF);  
  digitalWrite(Relay_5, RELAY_OFF);
  digitalWrite(Relay_6, RELAY_OFF);
  digitalWrite(Relay_7, RELAY_OFF);
  digitalWrite(Relay_8, RELAY_OFF);  
  
//---( THEN set pins as outputs )----  
  pinMode(Relay_1, OUTPUT);   
  pinMode(Relay_2, OUTPUT);  
  pinMode(Relay_3, OUTPUT);  
  pinMode(Relay_4, OUTPUT);    
  pinMode(Relay_5, OUTPUT);   
  pinMode(Relay_6, OUTPUT);  
  pinMode(Relay_7, OUTPUT);  
  pinMode(Relay_8, OUTPUT);    

  delay(1000); //Check that all relays are inactive at Reset

  Serial.begin(9600);
   while (!Serial) {
    ; // wait for Serial port to connect.
  }

  Serial.println("STARTUP");

  delay(MED_DELAY);

// shave and a haircut

    digitalWrite(Relay_1, RELAY_ON); // qtr
    delay(SHORT_DELAY);
    delay(SHORT_DELAY);
    digitalWrite(Relay_1, RELAY_OFF); // 8th
    delay(SHORT_DELAY);
    digitalWrite(Relay_1, RELAY_ON); // 8th 
    delay(SHORT_DELAY);
    digitalWrite(Relay_1, RELAY_OFF); // qtr
    delay(SHORT_DELAY);
    delay(SHORT_DELAY);
    digitalWrite(Relay_1, RELAY_ON); // qtr
    delay(SHORT_DELAY);
    delay(SHORT_DELAY);
    delay(SHORT_DELAY); // qtr rest
    delay(SHORT_DELAY);
    digitalWrite(Relay_1, RELAY_OFF);
    delay(SHORT_DELAY); // qtr rest
    delay(SHORT_DELAY);
    digitalWrite(Relay_1, RELAY_ON);
    delay(SHORT_DELAY); // qtr rest
    delay(SHORT_DELAY);
    digitalWrite(Relay_1, RELAY_OFF);
    delay(SHORT_DELAY); // qtr rest
        delay(SHORT_DELAY);

delay(MED_DELAY);

for(int i=0;i<5;i++) {
    digitalWrite(Relay_1, RELAY_ON);
    delay(MED_DELAY);
    digitalWrite(Relay_1, RELAY_OFF);
    delay(MED_DELAY);
  };



}

void all_off() {

// shut them all off

  digitalWrite(Relay_1, RELAY_OFF);
  digitalWrite(Relay_2, RELAY_OFF);
  digitalWrite(Relay_3, RELAY_OFF);
  digitalWrite(Relay_4, RELAY_OFF);  
  digitalWrite(Relay_5, RELAY_OFF);
  digitalWrite(Relay_6, RELAY_OFF);
  digitalWrite(Relay_7, RELAY_OFF);
  digitalWrite(Relay_8, RELAY_OFF);  

}

void cycle_up() {
    
for(int i=2;i<9;i++) {
    digitalWrite(i, RELAY_OFF);
    delay(SHORT_DELAY);
    digitalWrite(i, RELAY_ON);
    delay(SHORT_DELAY);
  };

}

void cycle_down() {

  for(int i=9;i<2;i--) {
    digitalWrite(i, RELAY_ON);
    delay(SHORT_DELAY);
    digitalWrite(i, RELAY_OFF);
    delay(SHORT_DELAY);
  };

/*
  digitalWrite(Relay_1, RELAY_OFF);// set the Relay OFF
  delay(SHORT_DELAY);
  digitalWrite(Relay_2, RELAY_OFF);// set the Relay OFF
  delay(SHORT_DELAY);
  digitalWrite(Relay_3, RELAY_OFF);// set the Relay OFF
  delay(SHORT_DELAY);
  digitalWrite(Relay_4, RELAY_OFF);// set the Relay OFF
  delay(SHORT_DELAY);
  digitalWrite(Relay_5, RELAY_OFF);// set the Relay ON
  delay(SHORT_DELAY);
  digitalWrite(Relay_6, RELAY_OFF);// set the Relay ON
  delay(SHORT_DELAY);
  digitalWrite(Relay_7, RELAY_OFF);// set the Relay ON
*/

}

void loop() {
  // put your main code here, to run repeatedly:

// ok, so the main (top) chevron flashes every time one of the other chevrons
// is set, then it's 8 seconds or so til the next one fires. 
  Serial.println("hello, world!");

  all_off();

 for(int relaypin=2;relaypin<9;relaypin++) { // only the 2nd through 7th chevrons should cycle

    digitalWrite(Relay_1, RELAY_ON);
    delay(SHORT_DELAY);
    digitalWrite(Relay_1, RELAY_OFF);
    delay(SHORT_DELAY);
    
    digitalWrite(relaypin, RELAY_ON);// lock the chevron
    delay(SHORT_DELAY);
    digitalWrite(relaypin, RELAY_OFF);// lock the chevron
    delay(SHORT_DELAY);
    digitalWrite(relaypin, RELAY_ON);// lock the chevron

    digitalWrite(Relay_1, RELAY_ON);
    delay(SHORT_DELAY);
    digitalWrite(Relay_1, RELAY_OFF);
    delay(SHORT_DELAY);
 
    Serial.println("chevron ");
    Serial.println(relaypin);
    Serial.println(" locked! ");

    delay(MED_DELAY);              // wait for a second 

  };

  cycle_up();

  delay(LONG_DELAY);              // wait see all relays OFF  

  Serial.println("losing signal...!");

  cycle_down();
  
  delay(LONG_DELAY);              // wait see all relays OFF  
  
    Serial.println("connection lost...!");
  
}
