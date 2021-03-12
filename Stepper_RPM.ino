float steps = 800; //pulses per revolution select that in your driver
float resolution = (float)360/steps; //the resolution its a constant always just define the steps
String RPM; //desired RPM it is an input from the serial monitor 
float T; //its the inverse of the frequency divided by two

void setup() {
  
  Serial.begin(115200); //Starts serial comunication
  DDRB = B000111; //Sets pin 8, 9 and 10  as outputs 13,12,11 as inputs
}

void loop() {
  
  if(Serial.available() > 0){ //Checks if theres is something to read from the serial monitor
      RPM = Serial.readString(); // reads the desired RPM from the serial, try that this value will always be a number 
      T = setRPM(RPM.toInt(), resolution); //calls a function to calculate the frecuency at the same time the rpm its set, need two parameters RPM in an integer format and the resolution variable, finally it is assigned to variable T
      Serial.println(RPM); //Prints the RPM needed
  }

  PORTB = B000011; // sets pin 8 and 9 HIGH
  delayMicroseconds(T); //The part of theperiod that pin 8 its High
  PORTB = B000010; //sets pin 9high and pin 8 LOW 
  delayMicroseconds(T);//The part of theperiod that pin 8 its Low
  
}


//This function calculates the period in terms of frequency and returns half of the period vale in microseconds
float setRPM(int rpm, float res){ 
  float freq = (float)rpm/((res/360)*60); //calculates the frequency to a related RPM
  float period = 1/freq; //calculates the inverse of the frequency A.K.A the period
  return (period*0.5)*1000000 ; // returns half of the period in microseconds
}
