//Silly Ohm Meter - RnD LAB's

 int aPinIn = A0;             // Analogue Input on Arduino  
 int val = 0;               // The raw analogue value  
    
 void setup(){  
    
  Serial.begin(9600);
//  pinMode(aPinIn, INPUT);  
//  digitalWrite(aPinIn, HIGH);
 }  
    
 void loop(){  
  //delay(1000);                        // Delay for readability    
  val = analogRead(aPinIn);           // Read in val (0-1023)  
  if(val > 50) {
   Serial.println(val); 
  } 
 }  
