
#include <Servo.h>
#include <IRremote.h>


const int READ_PIN = A1;
const int LED_PIN = 6;
const int SERVO_PIN = 9;
const int IR_RECEIVE_PIN = 14;
IRrecv IrReceiver(IR_RECEIVE_PIN);
Servo myservo;

void setup() {
  pinMode(READ_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  myservo.attach(SERVO_PIN);
  IrReceiver.enableIRIn();
  IrReceiver.blink13(true);
}

void test() {
  for (int x = 50; x < 140; x++) {
    myservo.write(x);
    delay(55);
  }
  
  for (int x = 0; x < 1000; x++) {
      int v = analogRead(READ_PIN);
      Serial.println(v);
      if (x % 100 == 0)
        Serial.println(500);
  }
}

void loop() {
//  test();
  if (ir())
    go();
}

void go() {
  digitalWrite(LED_PIN, HIGH);
  myservo.write(140);
  
  delay(5000);
  
  digitalWrite(LED_PIN, LOW);
  myservo.write(50);
}

bool ir() {
  if (IrReceiver.decode()) {
    bool ret = on(IrReceiver.results.value);
    IrReceiver.resume();
    return ret;
  }
  return false;
}

bool on(uint32_t value) {
    return value == 0xFF906F || // bright up
           value == 0xFFB847 || // bright down
           value == 0xFFF807 || // off
           value == 0xFFB04F || // on
           value == 0xFF9867 || // R
           value == 0xFFD827 || // G
           value == 0xFF8877 || // B
           value == 0xFFA857 || // M
           value == 0xFFE817 || // 
           value == 0xFF48B7 || // 
           value == 0xFF6897 || // 
           value == 0xFFB24D || // FLASH
           value == 0xFF02FD || // 
           value == 0xFF32CD || // 
           value == 0xFF20DF || // 
           value == 0xFF00FF || // STROBE
           value == 0xFF50AF || // 
           value == 0xFF7887 || // 
           value == 0xFF708F || // 
           value == 0xFF58A7 || // FADE
           value == 0xFF38C7 || // 
           value == 0xFF28D7 || // 
           value == 0xFFF00F || // 
           value == 0xFF30CF || // SMOOTH
           value == 0xFFFFFFFF;
}
