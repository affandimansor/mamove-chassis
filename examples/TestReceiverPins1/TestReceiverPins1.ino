int CE = 49;
int CSN = 50;
int SCK1 = 51;
int MO = 52;
int MI = 53;


void setup() {
  // put your setup code here, to run once:

  pinMode(CE,OUTPUT);
  pinMode(CSN,OUTPUT);
  pinMode(SCK,OUTPUT);
  pinMode(MO,OUTPUT);
  pinMode(MI,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(CE,HIGH);
  digitalWrite(CSN,HIGH);
  digitalWrite(SCK,HIGH);
  digitalWrite(MO,HIGH);
  digitalWrite(MI,HIGH);
}
