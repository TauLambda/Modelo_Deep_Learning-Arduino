#include <Servo.h>
#include <TM1637Display.h>

const int trigPin = 9; // Pin del sensor ultrasónico conectado al pin TRIG
const int echoPin = 10; // Pin del sensor ultrasónico conectado al pin ECHO
long duration;
int distance;

Servo myServo;
#define CLK 2 // Pin de reloj para el display
#define DIO 3 // Pin de datos para el display
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(11); // Pin del servo motor
  myServo.write(0); // Posicionar el servo en 0 grados al inicio
  display.setBrightness(0x0a); // Establecer brillo del display (ajustar según sea necesario)
  display.showNumberDec(0); // Mostrar 0 al inicio
}

void loop() {
  // Generar pulso ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer el tiempo de viaje del eco del sensor
  duration = pulseIn(echoPin, HIGH);

  // Calcular la distancia en centímetros
  distance = duration * 0.034 / 2;

  Serial.println(distance);

  display.showNumberDec(distance); // Mostrar la distancia en el display de 7 segmentos

  // Si la distancia es menor a 20 cm, mover el servo
  if (distance < 20) {
    // Mover el servo a 0 grados
    myServo.write(0);
    delay(500); // Esperar medio segundo
  } else {
    // Si la distancia es mayor a 20 cm, mover el servo a 90 grados
    myServo.write(40);
    delay(500); // Esperar medio segundo
  }
}

