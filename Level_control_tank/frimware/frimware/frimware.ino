const int chargingPumpPin = 11;      // Arduino pin connected to charging pump relay module
const int dischargingPumpPin = 12;  // Arduino pin connected to discharging pump relay module
const int triggerPin = 9;           // Arduino pin connected to ultrasonic sensor trigger
const int echoPin = 10;             // Arduino pin connected to ultrasonic sensor echo

void setup() {
  pinMode(chargingPumpPin, OUTPUT);       // Set the charging pump pin as an output
  pinMode(dischargingPumpPin, OUTPUT);    // Set the discharging pump pin as an output
  pinMode(triggerPin, OUTPUT);            // Set the trigger pin as an output
  pinMode(echoPin, INPUT);                // Set the echo pin as an input
  Serial.begin(9600);                     // Initialize Serial communication
}

void loop() {
  // Check if there is any data available to read from the serial port
  if (Serial.available() > 0) {
    // Read the incoming command
    int command = Serial.parseInt();
    
    // Process the command
    if (command == 1) {
      // Turn on the charging pump
      digitalWrite(chargingPumpPin, HIGH);
      digitalWrite(dischargingPumpPin, LOW);
    } else if (command == -1) {
      // Turn on the discharging pump
      digitalWrite(chargingPumpPin, LOW);
      digitalWrite(dischargingPumpPin, HIGH);
    } else if (command == 0) {
      // Turn off both pumps
      digitalWrite(chargingPumpPin, LOW);
      digitalWrite(dischargingPumpPin, LOW);
    }
  }
  
  // Read the distance from the ultrasonic sensor
float duration;
float distance_cm;

digitalWrite(triggerPin, LOW);
delayMicroseconds(2);
digitalWrite(triggerPin, HIGH);
delayMicroseconds(10);
digitalWrite(triggerPin, LOW);
duration = (float)pulseIn(echoPin, HIGH);
distance_cm = duration / 29.0 / 2.0;    // Convert the duration to distance in centimeters

  // Send the distance data to LabVIEW
  Serial.print(distance_cm);   // Stream the distance data continuously without markers
  Serial.println();
  delay(500);
}
