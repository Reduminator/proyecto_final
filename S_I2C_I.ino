/*
 *  Este código es para el ESCLAVO dentro de una comunicación 
 *  con el protocolo de comunicación I2C
 */
#include <Wire.h>   // Incluimos la librería para la comunicación I2C

#define SL_ADDR 2   // Definimos la dirección del esvlavo

#define Ans_size 14  // Definimos el tamaño esperado de la respuesta del esclavo 

String answer = "Hola, Que hay?"; // Creamos una variable String para la respuesta

void setup() {
  Wire.begin(SL_ADDR);    // Inicializamos la comunicación I2C y especificamos nuestra dirección como esclavo

  Wire.onRequest(requestEvent); // Declaramos una función que se ejecuta cuando recibimos un requerimiento de algún maestro

  Wire.onReceive(receiveEvent); // Declaramos una función que se ejecuta cuando recibimos un dato de algún maestro

  Serial.begin(9600);           // Inicializamos la comunicación serial a 9600 baudios
  Serial.println("Demostación de comunicación I2C");
}

void receiveEvent() {
  Serial.println("Maestro: ");
  // Guardamos los cáracteres de la respuesta en un String
  String response1 = "";       // Creamos una variable del tipo String para guardar la respuesta
  while(Wire.available()){    // Entra en este bucle mientrashaya bytes disponibles en la comuicación
    char b = Wire.read();
    response1 += b;            // Vamos concatenando los cárteres recibidos en la reponse
  }
  Serial.println(response1);
}

void requestEvent() {
  byte response[Ans_size];    // Configuramos la variable byte en el tamaño correcto

  // Damos el formato de arreglo a answer
  for(byte i = 0; i < Ans_size; i++) {
    response[i] = (byte)answer.charAt(i);
  }
  Wire.write(response,sizeof(response));
}
void loop() {
  delay(50);  // Retraso en el loop de 50 milisegundos
}
