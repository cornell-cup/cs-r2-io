#include <Servo.h>

#define LEFT_MOTOR_PIN  3
#define RIGHT_MOTOR_PIN 4
#define SERVO_PULSE_DELAY 20
#define SERVO_NEUTRAL_PULSE 1500
#define INPUT_BUFFER_SIZE 32

Servo lms, rms;

void setup() {
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  
  lms.attach(LEFT_MOTOR_PIN);
  rms.attach(RIGHT_MOTOR_PIN);
  
  Serial.begin(9600);
}

boolean started = false;
boolean homed = false;

unsigned long last_motor_pulse = 0;
int l_motor_pulse = 1500;
int r_motor_pulse = 1500;

char buffer[INPUT_BUFFER_SIZE];
int index = 0;

void loop() {
  // Read from serial
  if (Serial.available()) {
    buffer[index++] = Serial.read();
    boolean clear = false;
    if (buffer[index-1] == '\n' && buffer[index-2] == '\r') {
      // Strip the \r\n
      buffer[index-2] = 0;
      
      if (strncmp(buffer + 2, "start", 5)== 0) {
        started = true;
      }
      else if (strncmp(buffer + 2, "home", 4) == 0) {
        homed = true;
        // Setup motor
        if (buffer[0] == '1') {
          l_motor_pulse = SERVO_NEUTRAL_PULSE;
        }
        else {
          r_motor_pulse = SERVO_NEUTRAL_PULSE;
        }
      }
      else if (!started) {
        // Not started
        Serial.print("E1\r\n");
      }
      else if (!homed) {
        // Not homed
        Serial.print("E2\r\n");
      }
      else if (buffer[2] == 's') {
        // Set the speed
        int speed = atoi(buffer + 3) * 30;
        if (buffer[0] == '1') {
          l_motor_pulse = SERVO_NEUTRAL_PULSE + speed;
        }
        else {
          r_motor_pulse = SERVO_NEUTRAL_PULSE + speed;
        }
      }
      else if (buffer[2] == 'getp') {
        // TODO Encoder data
      }
      
      clear = true;
    }
    else if (index >= INPUT_BUFFER_SIZE) {
      clear = true;
    }

    if (clear) {
      // Clear the buffer
      index = 0;
    }
  }

  // Send a pulse to the servo
  unsigned long current_time = millis();
  unsigned long delta_time = current_time - last_motor_pulse;
  if (delta_time >= SERVO_PULSE_DELAY) {
    lms.writeMicroseconds(l_motor_pulse);
    rms.writeMicroseconds(r_motor_pulse);
    last_motor_pulse = current_time;
  }
}
