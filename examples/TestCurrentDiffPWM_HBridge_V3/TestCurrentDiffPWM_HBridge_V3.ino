int EN1 = 4;
int IN1 = 30;
int IN2 = 31;

int EN2 = 13;
int IN3 = 40;
int IN4 = 41;

int indicateLED = 23;

void setup() {
  // put your setup code here, to run once:

  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(indicateLED, OUTPUT);
  Serial.begin(9600);
  
 }

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for (int i = 0; i < 256; i+=50)
  {
    Serial.print("PWM value: ");
    Serial.println(i);
    
    digitalWrite(indicateLED, HIGH); // Turn the LED inditor on
    
    analogWrite(EN1, i);  // Set PWM value for the first motor
    analogWrite(EN2, i);  // Set PWM value for the second motor

    delay(10000);  // delay for 5s before going to the next i

    digitalWrite(indicateLED, LOW); // Turn the LED inditor on
    delay(1000);  // delay for 5s before going to the next i

  }
}
