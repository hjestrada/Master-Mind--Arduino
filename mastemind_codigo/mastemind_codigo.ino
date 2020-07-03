const int numReadings = 100;
int index = 0;                  // el índice de la lectura actual
int average = 0;                // la media
int total = 0;
int readings[numReadings];      // la lectura de la entrada analógica

// array suavisado lectura

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorPin1 = A1; 
int sensorAlcohol = A2; 
int sensorValue = 0;  // variable to store the value coming from the sensor
int  valor = 0;
int arranque = 8;
int luces = 9;
int bloqueo=11;
int apagarluces = 10;
int incomingByte = 0;
double tempA = 0;
int aux = 0;
char x; //guarda la trama de envio

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(arranque, OUTPUT);
  pinMode(luces, OUTPUT);
  pinMode(apagarluces, OUTPUT);
    pinMode(bloqueo, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  enviarDato();
  delay(10);
  leerDato();
  delay(10);

}


void enviarDato() {
double Lectura_Alcohol=Lec_Alcohol();
double lectura_tempA = Lec_tempA();
double  lectura_tempM= Lec_tempM();

  Serial.print(lectura_tempA);
  Serial.print(";");
  Serial.print(lectura_tempM);
   Serial.print(";");
     Serial.print(Lectura_Alcohol);
  Serial.println();
      
  delay(1);
  Serial.flush();
}

void leerDato() {

  byte dato = Serial.read();//Guardamos en dato el valor leido del puerto serie
  switch (dato) {
    
    case '1'://ENCENDER MOTOR Arranque
      digitalWrite(11, LOW); // apagar motor
      digitalWrite(8, HIGH);
      delay(3000);
      digitalWrite(8, LOW);
      Serial.flush();
      break;
      
    case '2':
      digitalWrite(8, LOW); // apagar motor
      digitalWrite(11, HIGH); // apagar motor
      Serial.flush();
      break;

    case '3': // luces altas
      digitalWrite(10, LOW);
      digitalWrite(9, HIGH); //Si es '2' apagamos el led
      Serial.flush();
      break;

    case '4': // lucesbajsas
      digitalWrite(10, LOW);
      digitalWrite(9, LOW); //Si es '2' apagamos el led
      Serial.flush();
      break;

    case '5'://LUCES APAGADAS
      digitalWrite(10, HIGH); //Si es '2' apagamos el led
      Serial.flush();
      break;

    case '6':// APAGAR LUCES
      digitalWrite(10, LOW); //Si es '2' apagamos el led
      Serial.flush();
      break;



  }
}

double  Lec_tempA() {
  total = total - readings[index];
  readings[index] = analogRead(sensorPin);
  total = total + readings[index];
  index = index + 1;
  if (index >= numReadings)
    index = 0;
  average = total / numReadings;
  tempA = (5.0 * average * 100.0) / 1024.0;
  return tempA;
}
double Lec_tempM(){
  double aux_temp= analogRead(sensorPin1);
    double motor= (5.0 * aux_temp* 100.0) / 1024.0;
    return motor;
    
}

double Lec_Alcohol(){
  
   double senAlcohol=analogRead(sensorAlcohol);
    return senAlcohol;
}








