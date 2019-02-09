int thermistorPin = A0;
int Vo;
float R1 = 1000; // value of R1 on board
float logR2, R2, T, vOut, tempRangeHigh, tempRangeLow;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; //steinhart-hart coeficients for thermistor
int tempOutPin = 3;
const int kelvin = 273.15;

void setup() {
  Serial.begin(9600);
  tempRangeHigh = 31;
  tempRangeLow = 25;
}

float kelvinify(float value) {
  return value + kelvin;
}

float deKelvinify(float value) {
  return value - kelvin;
}

void loop() {
  Vo = analogRead(thermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); //calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
//  T = T - 273.15; //convert Kelvin to Celcius

  Serial.print("Temperature: "); 
  Serial.print(deKelvinify(T));
  Serial.println(" c");

  // 0-5v output
  vOut = constrain((T - kelvinify(tempRangeLow)) * (255 / (tempRangeHigh - tempRangeLow)), 0, 255);
  
  Serial.println(vOut);
  analogWrite(tempOutPin, vOut);
  
  delay(1000);
}
