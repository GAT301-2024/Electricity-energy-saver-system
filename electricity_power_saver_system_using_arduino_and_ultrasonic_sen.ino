const int trigPin1 = 27;            // Trigger pin for the ultrasonic sensor in Room 1
const int echoPin1 = 32;            // Echo pin for the ultrasonic sensor in Room 1
const int ldrPin1 = 33;             // LDR sensor analog input pin for the light sensor in Room 1
const int relayPin1 = 19;           // Relay module control pin output for the light in Room 1

const int trigPin2 = 18;            // Trigger pin for the ultrasonic sensor in Room 2
const int echoPin2 = 25;            // Echo pin for the ultrasonic sensor in Room 2
const int ldrPin2 = 35;             // LDR sensor analog input pin for the light sensor in Room 2
const int relayPin2 = 26;           // Relay module control pin output for the light in Room 2

const int lightThreshold =500;     // Threshold value for darkness
const long timeout = 5000;       // 30 minutes in milliseconds

unsigned long lastMotionTime1 = 0;
unsigned long lastMotionTime2 = 0;

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
  Serial.print("distance dectected is: ");  
  Serial.println(distance1);
  Serial.println("ldr1 value is: ");
  Serial.println(ldrValue1);
  delay(1000);  // Check sensors every second
}

