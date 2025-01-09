#include <SoftwareSerial.h>

#define BT_RX 7
#define BT_TX 8
#define Horn 4
#define Ignition 5
#define Starter 6
#define Lights 9
#define Left_Indicator 10
#define Right_Indicator 11
#define BT_State 2
#define Photo_Res A0
#define OUTLED 13
#define Test 3

SoftwareSerial BT(BT_RX, BT_TX);

int cmd;
int Photo_Res_Threshold_Value = 600;
int Photo_Res_Value;
int Auto_Lamps = 0;
int indicator_state = 1;
int left_indicator_state = 1;
int right_indicator_state = 1;
int left_indicator_flag = 0;
int right_indicator_flag = 0;
int parking_flag = 0;

unsigned long previous_millis_on = 0, current_millis_on = 0;
unsigned long previous_millis_off = 0, current_millis_off = 0;
unsigned long Auto_Lamps_Delays = 2000;

unsigned long previous_millis_left_indicator_on = 0, current_millis_left_indicator_on = 0;
unsigned long previous_millis_left_indicator_off = 0, current_millis_left_indicator_off = 0;
unsigned long Indicator_Left_Delays = 500;

unsigned long previous_millis_right_indicator_on = 0, current_millis_right_indicator_on = 0;
unsigned long previous_millis_right_indicator_off = 0, current_millis_right_indicator_off = 0;
unsigned long Indicator_Right_Delays = 500;

unsigned long previous_millis_indicator_on = 0, current_millis_indicator_on = 0;
unsigned long previous_millis_indicator_off = 0, current_millis_indicator_off = 0;
unsigned long Indicator_Delays = 500;

bool Serialprint = 0;

void setup() {

  BT.begin(115200);
  Serial.begin(115200);

  pinMode(Horn, OUTPUT);
  pinMode(Ignition, OUTPUT);
  pinMode(Starter, OUTPUT);
  pinMode(Lights, OUTPUT);
  pinMode(Left_Indicator, OUTPUT);
  pinMode(Right_Indicator, OUTPUT);
  pinMode(BT_State,INPUT);
  pinMode(Photo_Res, INPUT);
  pinMode(OUTLED, OUTPUT);
  pinMode(Test, OUTPUT);
  digitalWrite(OUTLED, 0);

  digitalWrite(Test, 1);
  cmd = 'i';
  Auto_Lamps = 0;
}

void loop() {
  code();
  //delay(100);
}

void code() {
  current_millis_on = millis();
  current_millis_off = millis();
  //current_millis_indicator_on = millis();
  current_millis_indicator_off = millis();
  current_millis_left_indicator_off = millis();
  current_millis_right_indicator_off = millis();

  Photo_Res_Value = analogRead(Photo_Res);
  if (Serialprint == 1) {
    Serial.println(Photo_Res_Value);
  }
  //Serial.println(Photo_Res_Value);

  if (BT.available()) {
    cmd = BT.read();
  }

  if (Auto_Lamps == 1) {
    if (((current_millis_on - previous_millis_on) >= Auto_Lamps_Delays) && (Photo_Res_Value > Photo_Res_Threshold_Value)) {
      digitalWrite(Lights, 1);
      previous_millis_off = millis();
    }
    if (((current_millis_off - previous_millis_off) >= Auto_Lamps_Delays) && (Photo_Res_Value <= Photo_Res_Threshold_Value)) {
      digitalWrite(Lights, 0);
      previous_millis_on = millis();
    }
  }
  if (cmd == 'A') {
    Auto_Lamps = 1;
  }
  if (cmd == 'a') {
    Auto_Lamps = 0;
  }
  if (cmd == 'B')  //Ignition On
  {
    digitalWrite(Ignition, 1);
  }
  if (cmd == 'i')  //Ignition Off
  {
    digitalWrite(Ignition, 0);
    digitalWrite(Starter, 0);
    analogWrite(Lights, 0);
    digitalWrite(Left_Indicator, 1);
    digitalWrite(Right_Indicator, 1);
    Auto_Lamps = 0;
  }
  if (cmd == 'H')  //Horn On
  {
    digitalWrite(Horn, 1);
  }
  if (cmd == 'h')  //Horn Off
  {
    digitalWrite(Horn, 0);
  }
  if (cmd == 'C')  //Starter On
  {
    digitalWrite(Starter, 1);
  }
  if (cmd == 'c')  //Starter Off
  {
    digitalWrite(Starter, 0);
  }
  if (cmd == 'T')  //Lights On
  {
    digitalWrite(Lights, 1);
  }
  if (cmd == 't')  //Lights Off
  {
    digitalWrite(Lights, 0);
  }
  if (cmd == 'L')  //Left_Indicator On
  {
    left_indicator_flag = 1;
  }
  if (left_indicator_flag == 1)  //Left_Indicator On
  {
    if ( left_indicator_state == 0)
    {
    if ( (millis() - previous_millis_left_indicator_on) >= Indicator_Left_Delays)
      {
        left_indicator_state = 1;// change the state of LED
        previous_millis_left_indicator_on = millis();// remember Current millis() time
      }
    }
    if (right_indicator_state == 1)
    {
      if ( (millis() - previous_millis_left_indicator_on) >= Indicator_Left_Delays)
      {
        left_indicator_state = 0;// change the state of LED
        previous_millis_left_indicator_on = millis();// remember Current millis() time
      }
    }
    digitalWrite(Left_Indicator, left_indicator_state);
  }
  if (cmd == 'l')  //Left_Indicator Off
  {
    left_indicator_flag = 0;
  }
  if (left_indicator_flag == 0)  //Left_Indicator On
  {
    digitalWrite(Left_Indicator, 1);
  }
  if (cmd == 'R')  //Right_Indicator On
  {
  right_indicator_flag = 1;
  }
  
  if (right_indicator_flag == 1)  //Right_Indicator On
  {
    if (right_indicator_state == 0)
    {
      if ( (millis() - previous_millis_right_indicator_on) >= Indicator_Right_Delays)
      {
        right_indicator_state = 1;// change the state of LED
        previous_millis_right_indicator_on = millis();// remember Current millis() time
      }
    }
    if (right_indicator_state == 1)
    {
      if ( (millis() - previous_millis_right_indicator_on) >= Indicator_Right_Delays)
      {
        right_indicator_state = 0;// change the state of LED
        previous_millis_right_indicator_on = millis();// remember Current millis() time
      }
    }
    digitalWrite(Right_Indicator, right_indicator_state);
  }
  if (cmd == 'r')  //Right_Indicator Off
  {
    right_indicator_flag = 0;
  }
  if(right_indicator_flag == 0)
  {
    digitalWrite(Right_Indicator, 1);
  }
  if (cmd == 'P')  //Parking Indicator On
  {
    parking_flag = 1;
  }
  if(parking_flag == 1)
  {
    if ( indicator_state == 0)
    {
      if ( (millis() - previous_millis_indicator_on) >= Indicator_Delays)
      {
        indicator_state = 1;// change the state of LED
        previous_millis_indicator_on = millis();// remember Current millis() time
      }
    }
    if (indicator_state == 1)
    {
      if ( (millis() - previous_millis_indicator_on) >= Indicator_Delays)
      {
        indicator_state = 0;// change the state of LED
        previous_millis_indicator_on = millis();// remember Current millis() time
      }
    }
    digitalWrite(Right_Indicator, indicator_state);
    digitalWrite(Left_Indicator, indicator_state);
  }
  if (cmd == 'p')  //Parking Indicator Off
  {
    parking_flag = 0;
  }
  if(parking_flag == 0)
  {
    digitalWrite(Right_Indicator, 1);
    digitalWrite(Left_Indicator, 1);
  }
}
