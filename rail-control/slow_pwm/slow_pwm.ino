int PWMpin = 5; // PWM output
int dirpin = 2; // DIR selection
int enpin = 3;  // EN enable pin

int readdir = 8; // Control dirpin
int readen = 9;  // Control enpin

void setup() {
  pinMode(PWMpin, OUTPUT);
  pinMode(dirpin, OUTPUT);
  pinMode(enpin, OUTPUT);
  
  digitalWrite(dirpin, LOW);
  digitalWrite(enpin, LOW);
  
  pinMode(readdir, INPUT_PULLUP);
  pinMode(readen, INPUT_PULLUP);
  
  digitalWrite(dirpin,digitalRead(readdir));
  digitalWrite(enpin,digitalRead(readen));
}

void loop() {
  // Generate 960 Hz PWM with 50% duty cycle
  analogWrite(PWMpin,128);
  digitalWrite(dirpin,digitalRead(readdir));
  digitalWrite(enpin,digitalRead(readen));
}
