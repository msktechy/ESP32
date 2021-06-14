#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>


#define FIREBASE_HOST "Firebase_host_url"
#define FIREBASE_AUTH "Firebase_AUTH_KEY"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PSWD"

FirebaseData Firebasedata;
#define esp32_led 2
#define R1 23
#define DHTPIN 22     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
float Temp,Temp_cut_value,Humidity;
int dec = 2,Temp_cut_status,Power,d;
String path = "/Home";
 
void setup() {
   
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.begin(115200);

   delay(2000);
   
  for(int i=0;i<10;i++)
  {
    Serial.println("CONNECTING....................");
    delay(1000);
    if(WiFi.status()==WL_CONNECTED)
    break;
  }
  
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(Firebasedata, 1000 * 60);
  Serial.println("Firebase Connected");
  dht.begin();  
  pinMode(R1,OUTPUT);
  pinMode(esp32_led,OUTPUT);
  digitalWrite(R1,0);
  digitalWrite(esp32_led,0);
}

void loop() {

  if(WiFi.status()!=WL_CONNECTED)
  {
    ESP.restart();
  }

  Serial.println("Void loop Started");
  Temp = dht.readTemperature();
  Humidity = dht.readHumidity();
  if (Firebase.getInt(Firebasedata, path + "/AC/Delay"))
  {
    d = Firebasedata.intData();
  }
  if(Firebase.getInt(Firebasedata, path + "/AC/Power"))
  {
    Power = Firebasedata.intData();
  }
  if(Firebase.getInt(Firebasedata, path + "/AC/Temp_cut_status"))
  {
    Temp_cut_status = Firebasedata.intData();
  }
  if(Firebase.getFloat(Firebasedata, path + "/AC/Temp_cut_value"))
  {
    Temp_cut_value = Firebasedata.doubleData();
  }
  
  Firebase.setFloat(Firebasedata, path + "/AC/Humidity",Humidity);
  Firebase.setFloat(Firebasedata, path + "/AC/Temperature",Temp);
  
  Serial.println("All Values Set");

  Serial.print("Temp = ");
  Serial.print(Temp);
  Serial.print(" ,Humidity = ");
  Serial.print(Humidity);
  Serial.print(" ,Power = ");
  Serial.print(Power);
  Serial.print(" ,Delay = ");
  Serial.print(d);
  Serial.print(" ,Temp_cut_status = ");
  Serial.print(Temp_cut_status);
  Serial.print(" ,Temp_cut_value = ");
  Serial.println(Temp_cut_value);

  if((Temp<=Temp_cut_value)&&(Temp_cut_status == 1))
  {
    digitalWrite(R1,0);
    digitalWrite(esp32_led,0);
    Serial.print("Temp = ");
    Serial.print(Temp);
    Serial.print(" ,Humidity = ");
    Serial.print(Humidity);
    Serial.print(" ,Temp_cut_status = ");
    Serial.print(Temp_cut_status);
    Serial.print(" ,Temp_cut_value = ");
    Serial.println(Temp_cut_value);
  }
  if((Temp>Temp_cut_value)&&(Temp_cut_status == 1))
  {
    digitalWrite(R1,1);
    digitalWrite(esp32_led,1);
    Serial.print("Temp = ");
    Serial.print(Temp);
    Serial.print(" ,Humidity = ");
    Serial.print(Humidity);
    Serial.print(" ,Temp_cut_status = ");
    Serial.print(Temp_cut_status);
    Serial.print(" ,Temp_cut_value = ");
    Serial.println(Temp_cut_value);
  }
  if((Temp_cut_status == 0)&&(Power == 1))
  {
    digitalWrite(R1,1);
    digitalWrite(esp32_led,1);
    Serial.print("Temp = ");
    Serial.print(Temp);
    Serial.print(" ,Humidity = ");
    Serial.print(Humidity);
    Serial.print(" ,Temp_cut_status = ");
    Serial.print(Temp_cut_status);
    Serial.print(" ,Temp_cut_value = ");
    Serial.println(Temp_cut_value);
  }
    if((Temp_cut_status == 0)&&(Power == 0))
  {
    digitalWrite(R1,0);
    digitalWrite(esp32_led,0);
    Serial.print("Temp = ");
    Serial.print(Temp);
    Serial.print(" ,Humidity = ");
    Serial.print(Humidity);
    Serial.print(" ,Temp_cut_status = ");
    Serial.print(Temp_cut_status);
    Serial.print(" ,Temp_cut_value = ");
    Serial.println(Temp_cut_value);
  }
  
}
