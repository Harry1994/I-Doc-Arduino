
//Include libraries
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//TX HC-06 to Arduino Pin 10 and RX HC-06 to Arduino Pin 11 (wiring)
SoftwareSerial BTserial(10, 11); 

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  Serial.begin(9600); //Begin serial communication
  BTserial.begin(9600); //Begin Bluetooth communication

  Serial.println("Arduino Digital Temperature // Serial Monitor Version"); //Print a message

  sensors.begin();
}

void loop(void)
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures();  

  //Print messages to serial monitor
  Serial.print("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire

  //Print the message (data) sent via Bluetooth
  BTserial.print(sensors.getTempCByIndex(0));

  //Message has to end with a semikolon (;)
//  BTserial.print(";");
  
  //Update value every 10 secs.
  delay(10000);
}
