int pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int LE = 10; int WE = 11; int OE = 12; int CE = 13;
int i = 0;

void changeInOut(int state) {
  for (i = 0; i < 8; ++i) {
    pinMode(pins[i], state);
  }
}

void latch_add(unsigned char add) {
  digitalWrite(LE, HIGH);
  changeInOut(OUTPUT);
  for (i = 0; i < 8; ++i) {
    digitalWrite(pins[i], add & (1 << i));
  }
  delayMicroseconds(100);
  digitalWrite(LE, LOW);
}

unsigned char read_eeprom(void) {
  unsigned char data = 0;
  changeInOut(INPUT);
  delayMicroseconds(200);
  digitalWrite(OE, HIGH);
  digitalWrite(CE, LOW);
  delayMicroseconds(50);
  digitalWrite(WE, HIGH);
  delayMicroseconds(200);
  digitalWrite(OE, LOW);
  delayMicroseconds(100);
  for (i = 0; i < 8; ++i) {
    //data = data * 2 + digitalRead(pins[i]);
    data |= ((digitalRead(pins[i])) << i);
    // Serial.println(digitalRead(pins[i]));
  }
  digitalWrite(OE, HIGH);
  digitalWrite(CE, HIGH);
  return data;
}

void write_eeprom(unsigned char d) {
  digitalWrite(OE, LOW); digitalWrite(CE, HIGH); digitalWrite(WE, HIGH);
  delayMicroseconds(100);
  digitalWrite(OE, HIGH);
  changeInOut(OUTPUT);
  for (i = 0; i < 8; ++i) {
    digitalWrite(pins[i], d & (1 << i));
  }
  digitalWrite(WE, LOW);
  delayMicroseconds(50);
  digitalWrite(CE, LOW);
  delayMicroseconds(200);
  digitalWrite(WE, HIGH);
  digitalWrite(OE, LOW);
  digitalWrite(CE, HIGH);
}

void setup() {
  const unsigned char data[] = {0xB2, 0x90, 0x11, 0x06, 0x80, 0xFA, 0x78, 0xFF, 0x79, 0xFF, 0xD9, 0xFE, 0xD8, 0xFA, 0x22};
  Serial.begin(9600);
  pinMode(WE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(LE, OUTPUT);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, HIGH); digitalWrite(WE, HIGH); digitalWrite(OE, LOW);
  digitalWrite(LE, HIGH); // digitalWrite(WE, HIGH); digitalWrite(OE, HIGH);
  unsigned char j = 0; unsigned char mydata = 0;
  delay(1000);
  Serial.println("begin");
  for (int j = 0; j < 1; j++) {
    latch_add(j); delayMicroseconds(200);
    //write_eeprom(data[j]);delayMicroseconds(200);Serial.println(j); //Serial.println(data[j], HEX);
    Serial.print(j); Serial.print(": "); mydata = read_eeprom(); Serial.println(mydata, HEX);

    delay(20);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
