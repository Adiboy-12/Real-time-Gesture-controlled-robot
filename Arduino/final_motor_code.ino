#define LED_PIN 2 
// Built-in LED on ESP32  

// --- Motor 1 Pins --- 
int motor1PWM = 25; // PWM pin (ENA) 
int DIR1_PIN_MOTOR1 = 26; // Direction pin 1 
int motor1Sleep = 14; // Sleep pin  

// --- Motor 2 Pins --- 
int motor2PWM = 33; // PWM pin (ENB) 
int DIR1_PIN_MOTOR2 = 32; // Direction pin 1  
int DIR2_PIN_MOTOR2 = 35; // Direction pin 2 (added back) 
int motor2Sleep = 12; // Sleep pin  

// ------------------- Setup ------------------- 
void setup() { 
  Serial.begin(115200); 
  pinMode(LED_PIN, OUTPUT); 

  // Motor 1 
  pinMode(DIR1_PIN_MOTOR1, OUTPUT); 
  pinMode(motor1Sleep, OUTPUT); 
  
  // Motor 2 
  pinMode(DIR1_PIN_MOTOR2, OUTPUT); 
  pinMode(DIR2_PIN_MOTOR2, OUTPUT); 
  pinMode(motor2Sleep, OUTPUT); 

  digitalWrite(motor1Sleep, HIGH); 
  digitalWrite(motor2Sleep, HIGH); 

  stopMotors(); 
} 

// ------------------- Loop ------------------- 
void loop() { 
  if (Serial.available() > 0) { 
    String gesture = Serial.readStringUntil('\n'); 
    gesture.trim(); 
    digitalWrite(LED_PIN, HIGH); 
    Serial.println("Received: " + gesture); 
      
    if (gesture == "fist") { 
      Backward(); 
      Serial.println("Moving backward"); 
    } 
    else if (gesture == "peace") { 
      digitalWrite(LED_PIN, LOW); 
      turnRight(); 
    } 
    else if (gesture == "one") { 
      digitalWrite(LED_PIN, LOW); 
      turnLeft(); 
    } 
    else if (gesture == "stop" || gesture == "no gesture") { 
      digitalWrite(LED_PIN, LOW); 
      stopMotors(); 
    } 
    else if (gesture == "dislike") { 
      digitalWrite(LED_PIN, LOW); 
      Forward(); 
    } 
  } 
} 

// ------------------- Motor Functions ------------------- 
void stopMotors() { 
  digitalWrite(DIR1_PIN_MOTOR1, LOW); 
  analogWrite(motor1PWM, 0); 

  digitalWrite(DIR1_PIN_MOTOR2, LOW); 
  digitalWrite(DIR2_PIN_MOTOR2, LOW); 
  analogWrite(motor2PWM, 0); 

  Serial.println("NO MOTION"); 
} 

void turnRight() { 
  // Motor 1 Forward, Motor 2 Backward 
  digitalWrite(DIR1_PIN_MOTOR1, HIGH); 
  analogWrite(motor1PWM, 200); // speed (0-255) 

  digitalWrite(DIR1_PIN_MOTOR2, LOW); 
  digitalWrite(DIR2_PIN_MOTOR2, HIGH); 
  analogWrite(motor2PWM, 200); 

  Serial.println("Turning right"); 
} 

void Backward() { 
  // Both motors backward 
  digitalWrite(DIR1_PIN_MOTOR1, LOW); 
  analogWrite(motor1PWM, 200);  

  digitalWrite(DIR1_PIN_MOTOR2, LOW); 
  digitalWrite(DIR2_PIN_MOTOR2, HIGH); 
  analogWrite(motor2PWM, 200);  

  Serial.println("Moving Backward"); 
} 

void Forward() { 
  // Both motors forward 
  digitalWrite(DIR1_PIN_MOTOR1, HIGH); 
  analogWrite(motor1PWM, 200);  

  digitalWrite(DIR1_PIN_MOTOR2, HIGH); 
  digitalWrite(DIR2_PIN_MOTOR2, LOW); 
  analogWrite(motor2PWM, 200);  

  Serial.println("Moving Forward"); 
} 

void turnLeft() { 
  // Motor 1 Backward, Motor 2 Forward 
  digitalWrite(DIR1_PIN_MOTOR1, LOW); 
  analogWrite(motor1PWM, 200);  

  digitalWrite(DIR1_PIN_MOTOR2, HIGH); 
  digitalWrite(DIR2_PIN_MOTOR2, LOW); 
  analogWrite(motor2PWM, 200);  

  Serial.println("Turning left"); 
}
