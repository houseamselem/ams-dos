


#define ANALOG_PIN 0

//
int val = 0, minVal = -1, maxVal = -1, mapVal = 0;

/**/
void calibrate_setup() {
  
  //
  pinMode(ANALOG_PIN, INPUT);

}

/**/
void calibrate_loop() {
  
  //
  val = analogRead(ANALOG_PIN);

  //
  calibrate();

  //
  mapVal = map(val, minVal, maxVal, 0, 7);
  
  //
  Serial.println("A0: " + String(val) + "\t\tMIN: " + String(minVal) + "\tMAX: " + String(maxVal) + "\t\tMAP: " + String(mapVal));

}

/**/
void calibrate() {

  //
  if (minVal == -1 && maxVal == -1) {

    //
    if (val == 0) {
                  
      //
      minVal = val;
      maxVal = val + 1;
    
    }
    else {
     
      //
      minVal = val - 1;
      maxVal = val;
      
    }
      
  }
  else if (val > maxVal) {

    //
    maxVal = val;
    
  }
  else if (val < minVal) {

    //
    minVal = val;
    
  }
    
}
