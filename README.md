# ArduinoWater
This project was created as a group project in the sixth semester of studying EE in the TH Nürnberg.
It contains the code to run a automatic watering system powered by an Arduino and an ESP8266. 

## Setup
The Arduino is connected to a pump and a humidity sensor. When the sensor measures the humidity the value gets send to the ESP via a serial connection.
If this value is under a certain threshold the arduino activates the pump and valves to water the plant. 

The ESP communicates with another local server, which is used to set the thresholds for up to three plants via a web dashboard. 
