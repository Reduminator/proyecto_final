/*
 *  Este código es para el MAESTRO dentro de una comunicación 
 *  con el protocolo de comunicación I2C
 */
#include <Wire.h>   // Incluimos la librería para la comunicación I2C
#include <SoftwareSerial.h>;

#define RxPin 4
#define TxPin 3

#define Bauds 9600

#define SL1_ADDR 2   // Definimos la dirección del esvlavo 1
#define SL2_ADDR 3   // Definimos la dirección del esvlavo 2

#define G_size 4  // Definimos el tamaño del saludo para el esclavo

#define Ans1_size 14  // Definimos el tamaño esperado de la respuesta del esclavo 1
#define Ans2_size 19  // Definimos el tamaño esperado de la respuesta del esclavo 2 

String saludo = "Hola"; // Creamos una variable String para la respuesta

SoftwareSerial UARTII(RxPin,TxPin);

void setup() {
  Wire.begin();     // Inicializamos la comunicación I2C, no necesita dirección por ser maestro

  Serial.begin(Bauds); // Inicializamos la comunicación serial a 9600 baudios
  UARTII.begin(Bauds); // Inicializamos una segunda comunicación uart a 9600 baudios
  Serial.println("Demostración de comunicación con I2C");
  UARTII.println("Demostración de comunicación con I2C");
}

void loop() {
  delay(50);          // Retraso de 50 milisegundos
  
  byte response1[G_size];    // Configuramos la variable byte en el tamaño correcto
  
  // Damos el formato de arreglo a saludo
  for(byte i = 0; i < G_size; i++) {
    response1[i] = (byte)saludo.charAt(i);
  }
  
  // Escribimos un mensaje para el esclavo 1
  Wire.beginTransmission(SL1_ADDR);    // Iniciamos la transmisión con I2C a la dirreción del esclavo SL_ADDR
  Wire.write(response1,sizeof(response1));
  Wire.endTransmission();             // Terminamos la transmisión

  // Escribimos un mensaje para el esclavo 2
  Wire.beginTransmission(SL2_ADDR);    // Iniciamos la transmisión con I2C a la dirreción del esclavo SL_ADDR
  Wire.write(response1,sizeof(response1));
  Wire.endTransmission();             // Terminamos la transmisión

  // Leemos respuesta del esclavo 1
  Wire.requestFrom(SL1_ADDR,Ans1_size); // Pedimos una respuesta del tamaño Ans_size al esclavo SL_ADDR
  // Guardamos los cáracteres de la respuesta en un String
  String responses1 = "";       // Creamos una variable del tipo String para guardar la respuesta
  while(Wire.available()){    // Entra en este bucle mientrashaya bytes disponibles en la comuicación
    char bs1 = Wire.read();
    responses1 += bs1;            // Vamos concatenando los cárteres recibidos en la reponse
  }
  delay(50);          // Retraso de 50 milisegundos
  Serial.print("Esclavo 1: ");
  Serial.println(responses1);   // Mostramos la respuesta del esclavo en el monitor serial
  
  // Leemos respuesta del esclavo 2
  Wire.requestFrom(SL2_ADDR,Ans2_size); // Pedimos una respuesta del tamaño Ans_size al esclavo SL_ADDR
  // Guardamos los cáracteres de la respuesta en un String
  String responses2 = "";       // Creamos una variable del tipo String para guardar la respuesta
  while(Wire.available()){    // Entra en este bucle mientrashaya bytes disponibles en la comuicación
    char bs2 = Wire.read();
    responses2 += bs2;            // Vamos concatenando los cárteres recibidos en la reponse
  }
  delay(50);          // Retraso de 50 milisegundos
  UARTII.print("Esclavo 2: ");
  UARTII.println(responses2);   // Mostramos la respuesta del esclavo en el monitor serial
}
