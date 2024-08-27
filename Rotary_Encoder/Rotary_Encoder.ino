//Interrupt Pins:
//UNO - 2, 3
//MEGA - 2, 3, 18, 19, 20, 21

int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

void setup() {
  Serial.begin (9600);

  pinMode(encoderPin1, INPUT_PULLUP); 
  pinMode(encoderPin2, INPUT_PULLUP);

  // digitalWrite(encoderPin1, HIGH); //pullup
  // digitalWrite(encoderPin2, HIGH); //pullup

  // attachInterrupt(0, updateEncoder, FALLING); 
  // attachInterrupt(1, updateEncoder, FALLING);

}

void loop(){ 
  Serial.print(digitalRead(encoderPin1));
  Serial.println(digitalRead(encoderPin2));
  // delay(1000);
}


void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB
  int LSB = digitalRead(encoderPin2); //LSB

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time

  Serial.println("Interrupt");
}