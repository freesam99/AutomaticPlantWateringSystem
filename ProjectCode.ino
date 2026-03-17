#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 6

DHT dht(DHTPIN, DHTTYPE);

const int PUMP_PIN = 7;     // Relay module connected to D7
int moistureReading = 0;        // Variable to store sensor reading

/* macros defining LED pins */
#define GREEN_LED 2
#define YELLOW_LED 3
#define RED_LED 4
#define BLUE_LED 5

/* macros defining sensor, fan, pump, and button pins */
#define MOISTURE_SENSOR_PIN A0
#define FAN_PIN 8
//#define PUMP_PIN 6
#define PUMP_BUTTON_PIN 11
#define FAN_BUTTON_PIN 12

void fansON(){
  /* turns on fan */
  digitalWrite(FAN_PIN, HIGH);
}
void fansOFF(){
  /* turns off fan */
  digitalWrite(FAN_PIN, LOW);
}

void ledsOFF(){
  /* turns off all LEDS */
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void moistureWARNING(){
  /* yellow led on to indiate medium moisture level detected */
  digitalWrite(YELLOW_LED, HIGH);
}

void moistureOK(){
  /* green led on to indiate good moisture level detected */
  digitalWrite(GREEN_LED, HIGH);
}

void moistureLOW(){
  /* red led on to indiate very low moisture level detected */
  digitalWrite(RED_LED, HIGH);
}

void pumpON(){
  /* turn on the pump and blue LED */
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(PUMP_PIN, HIGH);
}

void pumpOFF(){
  /* turn off the pump and blue LED*/
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(PUMP_PIN, LOW);
}

void waterPlant(){
  /* turn on pump, with "dripping" behavior */
  pumpON();
  delay(3000); //pump water for 3 seconds, and then turn off the pump
  pumpOFF();
}

void setup() {
  Serial.begin(9600);  
  dht.begin();     
  pinMode(PUMP_PIN, OUTPUT); /* pump pin */
  digitalWrite(PUMP_PIN, HIGH); // Default: Relay OFF when Arduino starts

  /* LED pin setup */
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  /* fan, pump, and button pins setup */
  pinMode(FAN_PIN, OUTPUT);
  pinMode(FAN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PUMP_BUTTON_PIN, INPUT_PULLUP);
}

void loop(){

  int pumpButton = digitalRead(PUMP_BUTTON_PIN);
  Serial.println("-------------------------");

  /* turn off pump and LEDS on startup */
  pumpOFF();
  ledsOFF();

  moistureReading = analogRead(MOISTURE_SENSOR_PIN); //read in moisture levels from sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(true);
  float heatIndex = dht.computeHeatIndex(humidity, temperature, true); //compute heat index in fahrenheit
  
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Heat Index: ");
  Serial.println(heatIndex);

  /* display moisture values to serial monitor */
  Serial.print("Soil Moisture Value: ");
  Serial.println(moistureReading);

  /* process moisture values */
  if (moistureReading > 450) { 
    /* soil is DRY, turn on pump and blue LED indicating plant is being watered */
    moistureLOW();
    waterPlant();
  }
  else if(moistureReading >= 270 && moistureReading <= 450){
    /* soil is between DRY and WET (needs watering soon) */
    moistureWARNING();
  }
  else if(moistureReading < 270){
    /* soil is wet, moisture OK*/
    moistureOK();
  }

  /* turn on fan based on current temp/heat index */
  if(heatIndex > 75){
    fansON();
  }
  else{
    fansOFF();
  }

   /* manually control the fan using the button */
  int fanButton = digitalRead(FAN_BUTTON_PIN);
  if(fanButton == HIGH){
    fansON();
    Serial.println("Fan ON");
  }
  else{
    fansOFF();
    Serial.println("Fan OFF");
  }
  delay(1000);
}
