int sensorPin = A0;
int  sensorValue = 0 ;
int piezoPin = 9;

void setup(){
  pinMode(sensorPin, INPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(piezoPin, OUTPUT);
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);
  delay(5000);
  digitalWrite(7,LOW);
  Serial.begin(9600);
}


void loop(){
  sensorValue = analogRead (sensorPin);
  Serial.println(sensorValue);
  if (sensorValue<950){
    digitalWrite(piezoPin,HIGH);
    
  }
  else{

    digitalWrite(piezoPin,LOW);
  }
  }
   
