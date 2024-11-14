


//
const byte interruptPin = 2;

/**/
void irq_setup() {
  
  //
  Serial.begin(9600);

  //
  pinMode(2, INPUT);
  
  //
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptRequest, LOW);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), interruptRequest, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), interruptRequest, RISING);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), interruptRequest, FALLING);

}

/**/
void interruptRequest() {
  
  //
  Serial.println("Interrupt Request");

}
