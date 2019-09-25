int aux, seg;
void setup() {
  aux = 0; seg = 0;
  TCCR0A = 0b00000010;
  TCCR0B = 0b00000101;
  OCR0A = 160;
  Serial.begin(9600);
}

void loop() {
  unsigned int t = TCNT0;
  if((TIFR0 &= (1<<OCF0A))>>OCF0A){
    aux++;
    TIFR0 |= (1<<OCF0A);
  }
  if(aux == 98){
    seg++;
    aux = 0;
  }
  Serial.println(seg);
}
