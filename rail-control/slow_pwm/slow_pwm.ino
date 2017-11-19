int PWMpin = 11; // PWM output
int dirpin = 2; // DIR selection
int enpin = 3;  // EN enable pin

#define ENABLE LOW
#define DISABLE HIGH

void setup() {
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  //TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
  TCCR2B = _BV(CS20);
  /*TCCR1B = 0;//_BV(CS01);
  TCNT1 = 0;
  OCR1A = 249;

  TCCR1A |= (1 << WGM12);
  TCCR1B |= (1 << CS12);
  TIMSK2 |= (1 << OCIE1A);*/
  
  Serial.begin(115200);
  
  pinMode(PWMpin, OUTPUT);
  pinMode(dirpin, OUTPUT);
  pinMode(enpin, OUTPUT);
  
  digitalWrite(dirpin, HIGH);
  digitalWrite(enpin, HIGH);
  
  
  Serial.write("ready\n");
}

void move_motor(bool motor_dir, int motor_time) {
  Serial.print("Starting moving for ");
  Serial.println(motor_time);
  
  digitalWrite(dirpin, motor_dir);
  digitalWrite(enpin, ENABLE);
  //analogWrite(PWMpin,128);

  delay(motor_time);

  digitalWrite(enpin, DISABLE);
  Serial.println("End moving");
}

void fetchSerial() {
  if (Serial.available()) {
    char dir[1] = "";
    bool motor_dir = 0;
    char str[6] = "";
    Serial.readBytes(dir, 1);
    Serial.write("DIR:");

    if (dir[0] == 'L') {
      Serial.write("LEFT");
      motor_dir = LOW;
    } else if (dir[0] == 'R') {
      Serial.write("RIGHT");
      motor_dir = HIGH;
    } else {
      Serial.write("unknown option\n");
      return;  
    }

    Serial.readBytes(str, 5);
    Serial.write("\nTIME: ");
    int dur = String(str).toInt();
    Serial.println(dur);

    move_motor(motor_dir, dur);
  } 
}

void loop() {
  fetchSerial();

  //bool dir_gpio = digitalRead(readdir);
  //bool en_gpio = digitalRead(readen);
  
  // Generate 960 Hz PWM with 50% duty cycle
  analogWrite(PWMpin,128);
  
}
