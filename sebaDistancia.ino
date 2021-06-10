/****************************************************************
 * Nombre del modulo: sebaDistancia.ino
 * Descripcion: Detecta cuando algo se viene acercando, enviando
 *              una alerta mediante un led rojo. Mientras mas
 *              cerca, mas brillante es el led.
 * Re acondicinado por Nicolas Canales                                  
 * 10/06/21
 * 
 * Referencias:
 * https://www.luisllamas.es/debounce-interrupciones-arduino/
 * https://draeger-it.blog/arduino-lektion-103-laser-distanz-sensor-vl53lxx-v2/
 ***************************************************************/

 /* Librerias necesarias para sensor vl53lxx-v2 ****************/
#include <ComponentObject.h>
#include <RangeSensor.h>
#include <SparkFun_VL53L1X.h>
#include <vl53l1x_class.h>
#include <vl53l1_error_codes.h>

#include <Wire.h>
#include "SparkFun_VL53L1X.h"

/* Estos parametros fueron escogidos para una prueba de corta distancia ********************************/
#define TIME_DISTANCE 400 // Define la diferencia de tiempo en ms, entre muestra y muestra de distancia.
#define ERROR_DISTANCE 10 // Define la variacion permtida antes de alertar, en mm.
#define DIS_MIN 50 //Define la distancia minima para ajustar el brillo del led ROJO.
#define DIS_MAX 500 //Define la distancia maxima para ajustar el brillo del led ROJO. 

/* Asignacion de pines *****************************************/
const int button = 2; //Pin digital 2 para el boton
const int ledRed = 3; // Pin digital 3 para el led ROJO
const int ledBlue = 4;  // Pin digital 4 para el led Azul

/* Asignacion de varible para el sensor de distancia ***********/
SFEVL53L1X distanceSensor;

/* Variables auxiliares generales ******************************/
int brightness;

/* Variables auxiliares para DEBOUNCE del boton ****************/
const int timeThreshold = 150;
volatile int ISRCounter = 0;
int counter = 0;
long startTime = 0;


void setup() {
  Wire.begin();

  /* Configuracion de pines ************************************/
  pinMode(button, INPUT_PULLUP); // Boton configurado como entrada Pull UP
  pinMode(ledRed, OUTPUT);  // Alimentacion Led ROJO
  pinMode(ledBlue, OUTPUT); // Alimentacion Led AZUL

  /* Activando interrupciones para el manejo del boton *********/
  attachInterrupt(digitalPinToInterrupt(button), debounceCount, FALLING);

  /* Inicio de comunicacion serial con la consola **************/
  Serial.begin(115200);
  Serial.println("*********** Modulo sensor de Distancia ************");

  if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Fallo en el sensor de distancia");
    while (1)
      ;
  }
  Serial.println("Sensor listo para funcionar!");

  /* Definicion del estado inicial de los leds *****************/
  digitalWrite(ledRed, LOW);
  digitalWrite(ledBlue, LOW);
}

void loop() {

  /* Guarda el valor de la lectura del boton *******************/
  int lecturaBoton = digitalRead(2);

  /* Verifico estado del boton *********************************/
  if (counter != ISRCounter)
  {
    counter = ISRCounter;
    Serial.println(counter);
  }
  
  /* Si el contador del boton es impar se activa el sensor *****/
  if (counter%2 ==1) {
    Serial.println("Sensor Activado");
    
    distanceSensor.startRanging(); //Configuracion inicial para tomar medidas
    while (!distanceSensor.checkForDataReady())
    {
      delay(1);
    }
    
    int distance = distanceSensor.getDistance(); // Guarda el primer dato de distancia
    delay(TIME_DISTANCE);
    int distance2 = distanceSensor.getDistance(); // Guarda el segundo dato de distancia
    
    distanceSensor.clearInterrupt();  // Dejamos de solicitar datos
    distanceSensor.stopRanging();
    

    Serial.print("Distance1(mm): ");
    Serial.print(distance);
    Serial.print(" || ");
    Serial.print("Distance2(mm): ");
    Serial.println(distance2);
    
    /* Si algo se acerca, entra a este if **************************/
    if ( distance2 + ERROR_DISTANCE < distance) {
      brightness = map (distance2, DIS_MIN, DIS_MAX, 0, 255); // Escala la distancia a un parametro valido para el brillo del led
      analogWrite (ledRed, 255-brightness); 
      digitalWrite(ledBlue, LOW);
    } else { // En caso contrario, no hay alerta y el led AZUL indica que esta todo ok.
      digitalWrite(ledRed, LOW);
      digitalWrite(ledBlue, HIGH);
    }
  }else{
    digitalWrite(ledRed, LOW);  // Si el numero del contador es par, el sensor se desactiva y se apagan las luces
    digitalWrite(ledBlue, LOW);
  }

}

/* Funcion dedicada a eliminar el DEBOUNCE por software ***********/
void debounceCount()
{
  if (millis() - startTime > timeThreshold)
  {
    ISRCounter++;
    startTime = millis();
  }
}
