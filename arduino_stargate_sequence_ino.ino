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

static int relays[8] = {
  Relay_1, Relay_2, Relay_3, Relay_4,
  Relay_5, Relay_6, Relay_7, Relay_8
};

#include <Serial.h> 

void relayOnOff(int relay, int delay = SHORT_DELAY, delayCount = 1)
{
  digitalWrite(relay, RELAY_ON); // qtr

  delay(delayCount * delay);
  digitalWrite(relay, RELAY_OFF);
}

void setup()
{
  // put your setup code here, to run once:
//-------( Initialize Pins so relays are inactive at reset)----
  all_off();
  
//---( THEN set pins as outputs )----  
  for (auto relay : relays)
  {
    pinMode(relay, OUTPUT);   
  }   

  delay(MED_DELAY); //Check that all relays are inactive at Reset

  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for Serial port to connect.
  }

  Serial.println("STARTUP");

  delay(MED_DELAY);

  // shave and a haircut.
  relayOnOff(Relay_1, SHORT_DELAY, 2);
  delay(SHORT_DELAY);
  relayOnOff(Relay_1);
  delay(SHORT_DELAY);
  delay(SHORT_DELAY);
  relayOnOff(Relay_1, SHORT_DEALY, 4);
  delay(SHORT_DELAY); // qtr rest
  delay(SHORT_DELAY);
  relayOnOff(Relay_1, SHORT_DELAY, 2);

  delay(SHORT_DELAY); // qtr rest
  delay(SHORT_DELAY);

  delay(MED_DELAY);

  for(int i=0; i<5; i++)
  {
    relayOnOff(Relay_1, MED_DELAY);
    delay(MED_DELAY);
  }
}

void all_off()
{
  // shut them all off
  for (auto relay : relays)
  {
    digitalWrite(relay, RELAY_OFF);
  }
}

void cycle_up()
{
  for (auto relay : relays)
  {
    digitalWrite(relay, RELAY_OFF);
    delay(SHORT_DELAY);
    digitalWrite(relay, RELAY_ON);
    delay(SHORT_DELAY);
  }
}

void cycle_down()
{
  for (auto relay : relays)
  {
    relayOnOff(relay);
    delay(SHORT_DELAY);
  };
}

void loop() {
  // put your main code here, to run repeatedly:

  // ok, so the main (top) chevron flashes every time one of the other chevrons
  // is set, then it's 8 seconds or so til the next one fires. 
  Serial.println("hello, world!");

  all_off();

  // only the 2nd through 7th chevrons should cycle
  for(int relay = Relay_1; relay < Relay_8; relay++)
  {
    relayOnOff(Relay_1);
    delay(SHORT_DELAY);
    
    relayOnOff(relay);

    delay(SHORT_DELAY);
    digitalWrite(relay, RELAY_ON);// lock the chevron

    relayOnOff(Relay_1);
    delay(SHORT_DELAY);
 
    Serial.println("chevron ");
    Serial.println(relay);
    Serial.println(relay != Relay_7 ? " encoded" : " locked! ");

    delay(MED_DELAY);  // wait for a second 
  }

  cycle_up();

  delay(LONG_DELAY);   // wait see all relays OFF  

  Serial.println("losing signal...!");

  cycle_down();
  
  delay(LONG_DELAY);    // wait see all relays OFF  
  
  Serial.println("connection lost...!");
}
