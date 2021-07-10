int CE = 9;
int MO = 11;
int MI = 12;
int CSN = 10;
int SCK1 = 13;


void setup() {
  // put your setup code here, to run once:

  pinMode(CE,OUTPUT);
  pinMode(CSN,OUTPUT);
  pinMode(SCK1,OUTPUT);
  pinMode(MO,OUTPUT);
  pinMode(MI,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(CE,HIGH);
  digitalWrite(CSN,HIGH);
  digitalWrite(SCK1,HIGH);
  digitalWrite(MO,HIGH);
  digitalWrite(MI,HIGH);
}
