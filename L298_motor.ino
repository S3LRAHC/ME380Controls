// Motor A
int In1 = 4;
int In2 = 5;
int ENA = 2;
int SPEED_A = 255; // 255 is max

// Motor B
int In3 = 6;
int In4 = 7;
int ENB = 3;
int SPEED_B = 255; 

// Motor C (Winch)
int In5 = 9;
int In6 = 10;
int ENC = 8; 
int SPEED_C = 255; 

void setup() {
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(In5, OUTPUT);
  pinMode(In6, OUTPUT);
  pinMode(ENC, OUTPUT);

  // Start serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {
  // Check if data is available to read from the serial port
  if (Serial.available()) {
    char command = Serial.read();  // Read the incoming byte

    switch (command) {
      case 'd':  // Rotate clockwise
        stopMotorA();
        stopMotorB();
        rotateClockwise();
        break;

      case 's':  // Rotate anticlockwise
        stopMotorA();
        stopMotorB();
        rotateAnticlockwise();
        break;

      case 'a':  // Stop Motor A
        stopMotorA();
        break;

      case 'c':  // Clockwise Motor B
        stopMotorB();
        moveClockwiseMotorB();
        break;

      case 'x':  // Anti-clockwise Motor B
        stopMotorB();
        moveAntiClockwiseMotorB();
        break;

      case 'z':  // Stop Motor B
        stopMotorB();
        break;

      case 'k':  // Both Motors Clockwise (move Backward)
        stopMotorA();
        stopMotorB();
        stopMotorC();
        moveBothMotorsClockwise();
        break;

      case 'i':  // Both Motors Anti-clockwise (move Forward)
        stopMotorA();
        stopMotorB();
        stopMotorC();
        moveBothMotorsAntiClockwise();
        break;

      case 'o':  // Stop all motors
        stopMotorA();
        stopMotorB();
        stopMotorC();
        break;

      case 'u': // Lower winch
        moveClockwiseMotorC();
        break;

      case 'y': // Raise winch
        moveAntiClockwiseMotorC();
        break;
    }
  }
}

void moveBothMotorsClockwise() {
  for (int speed = 0; speed <= SPEED_A; speed++) {
    // Check if new serial data is available
    if (Serial.available()) {
      char newCommand = Serial.read(); // Read the new command
      if (newCommand == 'o') {
        stopMotorA();
        stopMotorB();
        return; // Exit the function immediately
      }
    }
    
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(ENA, speed);

    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    analogWrite(ENB, speed);

    Serial.print("Motors A & B Clockwise Speed: ");
    Serial.println(speed);
  }
}

void moveBothMotorsAntiClockwise() {
  for (int speed = 0; speed <= SPEED_A; speed++) {
    // Check if new serial data is available
    if (Serial.available()) {
      char newCommand = Serial.read(); // Read the new command
      if (newCommand == 'o') {
        stopMotorA();
        stopMotorB();
        return; // Exit the function immediately
      }
    }
    
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(ENA, speed);

    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(ENB, speed);

    Serial.print("Motors A & B Anti-Clockwise Speed: ");
    Serial.println(speed);
  }
}

void moveClockwiseMotorA() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  for (int speed = 0; speed <= SPEED_A; speed++) {
      // Check if new serial data is available
      if (Serial.available()) {
        char newCommand = Serial.read(); // Read the new command
        if (newCommand == 'o') {
          stopMotorA();
          stopMotorB();
          return; // Exit the function immediately
        }
      }
      
      analogWrite(ENA, speed);
      Serial.print("Motor A Clockwise Speed: ");
      Serial.println(speed);
  }
}

void moveAntiClockwiseMotorA() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  for (int speed = 0; speed <= SPEED_A; speed++) {
      // Check if new serial data is available
      if (Serial.available()) {
        char newCommand = Serial.read(); // Read the new command
        if (newCommand == 'o') {
          stopMotorA();
          stopMotorB();
          return; // Exit the function immediately
        }
      }
      
      analogWrite(ENA, speed);
      Serial.print("Motor A Anti-Clockwise Speed: ");
      Serial.println(speed);
  }
}

void moveClockwiseMotorB() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  for (int speed = 0; speed <= SPEED_B; speed++) {
      // Check if new serial data is available
      if (Serial.available()) {
        char newCommand = Serial.read(); // Read the new command
        if (newCommand == 'o') {
          stopMotorA();
          stopMotorB();
          return; // Exit the function immediately
        }
      }

      analogWrite(ENB, speed);
      Serial.print("Motor B Clockwise Speed: ");
      Serial.println(speed);  
  }
}

void moveAntiClockwiseMotorB() {
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  for (int speed = 0; speed <= SPEED_B; speed++) {
      // Check if new serial data is available
      if (Serial.available()) {
        char newCommand = Serial.read(); // Read the new command
        if (newCommand == 'o') {
          stopMotorA();
          stopMotorB();
          return; // Exit the function immediately
        }
      }
      
      analogWrite(ENB, speed);
      Serial.print("Motor B Anti-Clockwise Speed: ");
      Serial.println(speed);
  }
}

void moveClockwiseMotorC() {
  digitalWrite(In5, HIGH);
  digitalWrite(In6, LOW);
  for (int speed = 0; speed <= SPEED_C; speed++) {
      // Check if new serial data is available
      if (Serial.available()) {
        char newCommand = Serial.read(); // Read the new command
        if (newCommand == 'o') {
          stopMotorA();
          stopMotorB();
          stopMotorC();
          return; // Exit the function immediately
        }
      }

      analogWrite(ENC, speed);
      Serial.print("Motor C Clockwise Speed: ");
      Serial.println(speed);
  }
}

void moveAntiClockwiseMotorC() {
  digitalWrite(In5, LOW);
  digitalWrite(In6, HIGH);
  for (int speed = 0; speed <= SPEED_C; speed++) {
      // Check if new serial data is available
      if (Serial.available()) {
        char newCommand = Serial.read(); // Read the new command
        if (newCommand == 'o') {
          stopMotorA();
          stopMotorB();
          stopMotorC();
          return; // Exit the function immediately
        }
      }

      analogWrite(ENC, speed);
      Serial.print("Motor C Anti-Clockwise Speed: ");
      Serial.println(speed);
  }
}

void rotateClockwise() {
  for (int speed = 0; speed <= SPEED_A; speed++) {
    // Check if new serial data is available
    if (Serial.available()) {
      char newCommand = Serial.read(); // Read the new command
      if (newCommand == 'o') {
        stopMotorA();
        stopMotorB();
        return; // Exit the function immediately
      }
    }
    
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(ENA, speed);

    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(ENB, speed);

    Serial.print("Motors A & B Anti-Clockwise Speed: ");
    Serial.println(speed);
  }
}

void rotateAnticlockwise() {
  for (int speed = 0; speed <= SPEED_A; speed++) {
    // Check if new serial data is available
    if (Serial.available()) {
      char newCommand = Serial.read(); // Read the new command
      if (newCommand == 'o') {
        stopMotorA();
        stopMotorB();
        return; // Exit the function immediately
      }
    }
    
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(ENA, speed);

    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    analogWrite(ENB, speed);

    Serial.print("Motors A & B Anti-Clockwise Speed: ");
    Serial.println(speed);
  }
}

void stopMotorA() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  analogWrite(ENA, 0);
}

void stopMotorB() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  analogWrite(ENB, 0);
}

void stopMotorC() {
  digitalWrite(In5, LOW);
  digitalWrite(In6, LOW);
  analogWrite(ENC, 0);
}
