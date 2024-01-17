#include <Arduino.h>
#include <BluetoothSerial.h>
#include <EEPROM.h>
#include "esp32-hal-ledc.h"
#include "SmartReliefPro.h"
#define Hot 5 
#define Vibro 4
BluetoothSerial ESP_BT; // создиние объекта для Bluetooth
SmartRelief MyRele;
SmartReliefVal Vals;
int RelePins[]={Hot,Vibro};
/// Статус подключения bluetooth 
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
    ESP_BT.print("Client Connected");}
  else {ESP_BT.print("Client Disconnected");
  Vals.interval = 
  }}

void setup() {
EEPROM.begin(512);  // Инициализация EEPROM с размером 512 байт
EEPROM.write(Vals.address, Vals.incoming);  // Запись данных
EEPROM.write(Vals.address2,Vals.interval);
EEPROM.commit();   // Сохранение изменений
Vals.incoming = EEPROM.read(Vals.address);   // Чтение данных
Vals.interval = EEPROM.read(Vals.address2);
EEPROM.end(); 
Serial.begin(9600);
MyRele.ReleInit(2,RelePins);
////подключим шим
ledcSetup(Vals.ledChannel, Vals.frequency, Vals.resolution);
// подключаем ШИМ-канал к пину светодиода:                                         
ledcAttachPin(RelePins[2], Vals.ledChannel);
  for(int i = 0; i < maxIndex; i++)
    Vals.coefficient[i] = Vals.coefficientSet1[i];
///////////////////////
  ESP_BT.begin("SmartRelief V2.0"); //Название устройсва Bluetooth
   ESP_BT.register_callback(callback);
   Vals.previousMillis1 = millis();
   Vals.previousMillis2 = millis();
}

void loop() {
    if (ESP_BT.available())//Проверяем, получаем ли мы что-нибудь по Bluetooth
 {Vals.incoming = ESP_BT.read(); //Считываем что мы получаем
/////// Настройка режимов
switch(Vals.incoming){
   case 1:
  Vals.ZONE1=true;
  break;
   case 2:
  Vals.ZONE1=false; digitalWrite(RelePins[2], LOW);
  break;
   case 3:
  Vals.ZONE2=true;
  break;
   case 4:
  Vals.ZONE2=false; digitalWrite(RelePins[1],LOW);
  break;
   case 5:
  Vals.interval = Vals.A;
  break;
   case 6:
  Vals.interval = Vals.B;
  break;
   case 7:
  Vals.interval = Vals.C;
  break;
   case 8:
  Vals.interval = Vals.D;
  break;
  ///////  выбор анимаций вибрации 
    case 9:
    MyRele.pulse1_FastInSlowOut(2);
  break;
    case 10:
    MyRele.pulse3_SOSBlink(2);
  break;
    case 11:
    MyRele.pulse4_BlinkThrice(2);
  break;
    case 12:
    MyRele.pulse5_FadeIn(2);
  break;
    case 13:
    MyRele.pulse8_GradualBuild(2);
  break;
    case 14:
    MyRele.pulse10_DarkFlash(2);
  break;
    case 15:
    MyRele.pulse11_BlinkDecreasing(2);
  break;
    case 16:
    MyRele.pulse12_Heartbeat(2);
  break;
    case 17:
    MyRele.pulse13_BlinkIncreasing(2);
  break;
    case 18:
    MyRele.pulse14_Raindrops(2);
  break;
    case 19:
    MyRele.pulse16_TransmissionRandomBrightness(2);
  break;
    case 20:
    MyRele.pulse17_Lightning(2);
  break;
    case 21:
    MyRele.pulse18_TransmissionFixedBrightness(2);
  break;
    case 22:
    MyRele.pulse17_Lightning(2);
  break;
    case 23:
    MyRele.pulse18_TransmissionFixedBrightness(2);
  break;
    case 24:
    MyRele.pulse19_StaircaseContinuous(2);
  break;
    case 25:
    MyRele.pulse21_StaircaseBlink(2);
  break; 
   case 26:
    MyRele.pulse23_BlinkSlow(2);
  break; 
   case 27:
    MyRele.pulse24_BlinkFast(2);
  break;
   case 28:
    MyRele.pulse25_PulseSlow(2);
  break;
   case 29:
    MyRele.pulse26_PulseFast(2);
  break;
}
 }
 if(Vals.ZONE1==true){
  MyRele.VibroMode(2);
 }
 if(Vals.ZONE2==true){
  MyRele.HeatZone(1);
 }
 
}

