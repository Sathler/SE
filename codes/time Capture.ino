void setup() {
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);
  TCCR1A = 0;
  TCCR1B = 0b00000001;
  TIMSK1 = 0b00100000;
  SREG |= (1 << 7);
  Serial.begin(9600);
}

void loop() {
  unsigned int x = ICR1L + (ICR1H << 8);
  Serial.println(x);
}