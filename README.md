Name: Rubangakene samuel
RegNo:23/u/3568/gim
StudentNo: 2301003568
# Electricity-energy-saver-system
The system is designed to save electricity power in a home setting.

# Automated Light Control System

This project is designed to control the lighting in two rooms based on motion detection and ambient light levels. It uses ultrasonic sensors to detect motion and LDR (Light Dependent Resistor) sensors to measure light levels. The system turns on the lights when motion is detected and the room is dark, and turns them off after a specified timeout period if no motion is detected.

## Hardware Components

- ESP32 or Arduino board
- Ultrasonic sensors (2 units)
- LDR sensors (2 units)
- Relay modules (2 units)
- LED lights or other lighting devices (2 units)
- Jumper wires and breadboard

## Pin Configuration

### Room 1
- **Trig Pin for Ultrasonic Sensor**: 27
- **Echo Pin for Ultrasonic Sensor**: 32
- **LDR Sensor Analog Input Pin**: 33
- **Relay Module Control Pin**: 19

### Room 2
- **Trig Pin for Ultrasonic Sensor**: 18
- **Echo Pin for Ultrasonic Sensor**: 25
- **LDR Sensor Analog Input Pin**: 35
- **Relay Module Control Pin**: 26

## Constants

- **Light Threshold**: 500 (Threshold value for darkness)
- **Timeout**: 5000 ms (30 minutes in milliseconds)

## Variables

- `lastMotionTime1`: Stores the last time motion was detected in Room 1.
- `lastMotionTime2`: Stores the last time motion was detected in Room 2.

## Setup

The `setup` function initializes the pin modes and ensures that the lights are off at the start.

```cpp
void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(ldrPin1, INPUT);
  pinMode(relayPin1, OUTPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ldrPin2, INPUT);
  pinMode(relayPin2, OUTPUT);

  Serial.begin(9600);

  digitalWrite(relayPin1, LOW);  // Ensure light in Room 1 is off at start
  digitalWrite(relayPin2, LOW);  // Ensure light in Room 2 is off at start
}
```

## Distance Measurement

The `getDistance` function measures the distance using the ultrasonic sensor.

```cpp
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;  // Convert to cm
  Serial.println(distance);
  return distance;
}
```

## Main Loop

The `loop` function continuously checks the LDR and ultrasonic sensor values for both rooms. If the light level is below the threshold and motion is detected within 100 cm, the light is turned on. If no motion is detected for the timeout period, the light is turned off.

```cpp
void loop() {
  // Room 1
  int ldrValue1 = analogRead(ldrPin1);
  long distance1 = getDistance(trigPin1, echoPin1);

  if (ldrValue1 <= lightThreshold && distance1 < 100) {  // Assuming 100 cm as motion detection threshold
    digitalWrite(relayPin1, HIGH);  // Turn on light in Room 1
    lastMotionTime1 = millis();     // Reset timer for Room 1
    Serial.print(ldrValue1);
  }

  if (millis() - lastMotionTime1 > timeout) {
    digitalWrite(relayPin1, LOW);   // Turn off light in Room 1 after timeout
  }

  // Room 2
  int ldrValue2 = analogRead(ldrPin2);
  long distance2 = getDistance(trigPin2, echoPin2);

  if (ldrValue2 <= lightThreshold && distance2 < 100) {  // Assuming 100 cm as motion detection threshold
    digitalWrite(relayPin2, HIGH);  // Turn on light in Room 2
    lastMotionTime2 = millis();     // Reset timer for Room 2
  }

  if (millis() - lastMotionTime2 > timeout) {
    digitalWrite(relayPin2, LOW);   // Turn off light in Room 2 after timeout
  }

  Serial.print("Distance detected is: ");
  Serial.println(distance1);
  Serial.println("LDR1 value is: ");
  Serial.println(ldrValue1);
  delay(1000);  // Check sensors every second
}
```

## Serial Output

The system prints the distance detected and LDR values to the serial monitor for debugging purposes.
