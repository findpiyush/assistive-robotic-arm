// www.sciencebuddies.org

// declare variables
int flexsensorpin1 = A0;  
int sensor1;          

int flexsensorpin2 = A2;  
int sensor2; 

// LED pins
int red1 = 10;
int red2 = 11;
int red3 = 12;

int green1 = 7;
int green2 = 8;
int green3 = 9;

void setup() {

  pinMode(red1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(red3,OUTPUT);

  pinMode(green1,OUTPUT);
  pinMode(green2,OUTPUT);
  pinMode(green3,OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // -------- SENSOR 1 --------
  sensor1 = analogRead(flexsensorpin1);
  Serial.print("Sensor1: ");
  Serial.println(sensor1);

  if(sensor1 > 900){
    digitalWrite(red1,HIGH);
    digitalWrite(red2,HIGH);
    digitalWrite(red3,HIGH);
  }
  else if(sensor1 > 850){
    digitalWrite(red1,HIGH);
    digitalWrite(red2,HIGH);
    digitalWrite(red3,LOW);
  }
  else if(sensor1 > 800){
    digitalWrite(red1,HIGH);
    digitalWrite(red2,LOW);
    digitalWrite(red3,LOW);
  }
  else{
    digitalWrite(red1,LOW);
    digitalWrite(red2,LOW);
    digitalWrite(red3,LOW);
  }

  // -------- SENSOR 2 --------
  sensor2 = analogRead(flexsensorpin2);
  Serial.print("Sensor2: ");
  Serial.println(sensor2);

  if(sensor2 > 980){
    digitalWrite(green1,HIGH);
    digitalWrite(green2,HIGH);
    digitalWrite(green3,HIGH);
  }
  else if(sensor2 > 965){
    digitalWrite(green1,HIGH);
    digitalWrite(green2,HIGH);
    digitalWrite(green3,LOW);
  }
  else if(sensor2 > 950){
    digitalWrite(green1,HIGH);
    digitalWrite(green2,LOW);
    digitalWrite(green3,LOW);
    
  }
  else{
    digitalWrite(green1,LOW);
    digitalWrite(green2,LOW);
    digitalWrite(green3,LOW);
  }

  delay(200);
}