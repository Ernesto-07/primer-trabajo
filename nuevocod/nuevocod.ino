long tiempoanterior = 0;
long tiempoactual = 0;
long tiemporeal = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("listo");
  tiempoanterior=millis();
  tiempoactual=millis();
  tiemporeal=tiempoactual-tiempoanterior;


}

void loop() {
  // put your main code here, to run repeatedly:

}
