// Incluimos librería
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
//creamos objeto para pantalla lcd 20x4

LiquidCrystal_I2C lcd(0x3f,20,4);

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

#define soil1 1

/humedad minima para dar alarma en % si el valor del sensor es menor a este valor se dara alarma con buzzer y led para 4 planta {30,30,30,30} por default
int minimo[3]={30,30,30,30};
int cont=0;

byte Grado[8]={
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};
byte Luz[8]={
  B01110,
  B10001,
  B10101,
  B10101,
  B01010,
  B01110,
  B01010,
  B00100,
};
byte Planta[8]={
  B10101,
  B10101,
  B01110,
  B00100,
  B11111,
  B10001,
  B01010,
  B01110,
};
void setup() {
 lcd.init(); // put your setup code here, to run once:
 lcd.backlight();
 lcd.createChar(0,Grado);
 lcd.createChar(1,Luz);
 lcd.createChar(2,Planta);
 dht.begin();

 
}

void loop() {
  if(cont<4){
    //se miden los parametros con sensores
  int humidity=dht.readHumidity();
  float temperature = dht.readTemperature();
  int lectura[8]={map(analogRead(soil1),0,880,0,100),map(analogRead(2),0,880,0,100),map(analogRead(3),0,880,0,100),map(analogRead(4),0,880,0,100)};
  int light=map(analogRead(A0),0,763,0.0,100.0);
  lcd.clear();
  //se muestra temperatura
  lcd.setCursor(0,0);
  lcd.print("T");
  lcd.setCursor(1,0);
  lcd.write(byte(0));
  lcd.setCursor(2,0);
  lcd.print(":");
  lcd.setCursor(3,0);
  lcd.print(temperature);
  lcd.setCursor(7,0);
  lcd.write(byte(0));
  lcd.setCursor(8,0);
  lcd.print("C");
  // se muestra humedad humedad
  lcd.setCursor(10,0);
  lcd.print("HR:");
  lcd.setCursor(13,0);
  lcd.print(humidity);
  lcd.setCursor(15,0);
  lcd.print("%");

  // se muestra intensidad de luz
  lcd.setCursor(10,1);
  lcd.write(byte(1));
  lcd.setCursor(12,1);
  lcd.print(":");
  lcd.setCursor(13,1);
  lcd.print(light);
  lcd.setCursor(15,1);
  lcd.print("%");
  
  
  //se muestra medición humedad de suelo 
  if(lectura[cont]>minimo[cont]){
  lcd.setCursor(0,1);
  lcd.write(byte(2));
  lcd.setCursor(1,1);
  lcd.print(cont+1);
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print(lectura[cont]);
  lcd.setCursor(8,1);
  lcd.print("%");
  }
  if(lectura[cont]<minimo[cont]){
  lcd.setCursor(0,1);
  lcd.write(byte(2));
  lcd.setCursor(1,1);
  lcd.print(cont+1);
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print("DRY");

  int cont2=0;
  while(cont2<5){
  tone(3,440.0);
  digitalWrite(4,HIGH);
  delay(500);
  noTone(3);
  digitalWrite(4,LOW);
  delay(500);
  cont2++;
  }
  }
  cont++;
  delay(5000);
  }
  if(cont==4){
    cont=0;
  }
  }
