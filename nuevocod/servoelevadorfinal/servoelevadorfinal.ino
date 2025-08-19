#include <Servo.h>
#define SERVOPIN 3
int angulo=0;
Servo servoPuerta;



#define led1up 13
#define led2down 12
#define led2up 11
#define led3down 10
#define ledabrirpuerta 9

#define ledcerrarpuerta 8
#define ledpuertamovimiento 7
#define ledelevadorsube 6
#define ledelevadorbaja 5
#define ledelevadormueve 4
//definición de puertos para botones
#define boton1up 22
#define boton2down 24
#define boton2up 26
#define boton3down 28
#define botonpuertaabierta 30
#define botonpuertacerrada 32
#define botonpiso1 34
#define botonpiso2 36
#define botonpiso3 38
//definición de puerto para sensor
#define sensorPuerta 35 
//variables para botones externos
 int vp1up=0;
 int vp3down=0;
 int vp2down=0;
 int vp2up=0;
//variable para número de piso
int piso=1;
//variable dirección puerta (0 = cerrando; 1 = abriendo; 2 = detenido)
int direccionpuerta=2;
//variable de la condición de la puerta. 0 = cerrada; 1 = abierta; 2 =
int condicionpuerta=0;
//variable de la dirección del elevador (0 = subiendo; 1 = bajando; 2 moviendo; 3 = detenido)
int direccionelevador=0;
//variable para la condición del elevador. 0 = subiendo; 1 = bajando; 2 = moviendo; 3 = detenido
int condicionelevador=3;
//variable enclave piso
//variable para el sensor de la puerta (0 = hay un objeto, 1 = está libre)
int sensorp=1;
//definición de puertos de salida

void setup(){
Serial.begin(9600);
Serial.println("listo");

servoPuerta.attach(SERVOPIN);
servoPuerta.write(125);

 pinMode(led1up,OUTPUT);
 pinMode(led2down,OUTPUT);
 pinMode(led2up,OUTPUT);
 pinMode(led3down,OUTPUT);
 pinMode(ledabrirpuerta,OUTPUT);
 pinMode(ledcerrarpuerta,OUTPUT);
 pinMode(ledpuertamovimiento,OUTPUT);
 pinMode(ledelevadorsube,OUTPUT);
 pinMode(ledelevadorsube,OUTPUT);
 pinMode(ledelevadorbaja,OUTPUT);
 pinMode(ledelevadormueve,OUTPUT);
 //definición de puertos de entrada
 pinMode(boton1up,INPUT_PULLUP);
 pinMode(boton2down,INPUT_PULLUP);
 pinMode(boton2up,INPUT_PULLUP);
 pinMode(boton3down,INPUT_PULLUP);
 pinMode(botonpuertaabierta,INPUT_PULLUP);
 pinMode(botonpuertacerrada,INPUT_PULLUP);
 pinMode(botonpiso1,INPUT_PULLUP);
 pinMode(botonpiso2,INPUT_PULLUP);
 pinMode(botonpiso3,INPUT_PULLUP);
 //definición de puerto de entrada del sensor
 pinMode(sensorPuerta, INPUT_PULLUP);
}
//función para abrir la puerta.
void abrirpuerta(){
   servoPuerta.write(165);
   delay(200);
 /* 
 digitalWrite(ledabrirpuerta,1);
 digitalWrite(ledcerrarpuerta,0);*/
 digitalWrite(ledpuertamovimiento,1);
 direccionpuerta=1;
 condicionpuerta=2;

}
//función para detener las puertas
void detenerpuerta(){
 digitalWrite(ledpuertamovimiento,0);
 if (direccionpuerta==0)
 condicionpuerta=0;
 else
 condicionpuerta=1;
 direccionpuerta=2;
  digitalWrite(ledabrirpuerta,0);
  digitalWrite(ledcerrarpuerta,0);
}
//función para cerrar la puerta
void cerrarpuerta(){
    servoPuerta.write(125);
delay(200);
 /* digitalWrite(ledabrirpuerta,0);
 digitalWrite(ledcerrarpuerta,1);*/
 digitalWrite(ledpuertamovimiento,1);
 direccionpuerta=0;
 condicionpuerta=2;
}
//función para bajar el elevador
void bajarelevador(){
 digitalWrite(ledelevadorsube,0);
 digitalWrite(ledelevadorbaja,1);
 digitalWrite(ledelevadormueve,1);
 direccionelevador=1;
 condicionelevador=2;
}
//función para detener el elevador
void detenerelevador(){
 digitalWrite(ledelevadorsube,0);
 digitalWrite(ledelevadorbaja,0);
 digitalWrite(ledelevadormueve,0);
 condicionelevador=3; 
}
//función para subir el elevador
void subirelevador(){
 digitalWrite(ledelevadorsube,1);
 digitalWrite(ledelevadorbaja,0);
 digitalWrite(ledelevadormueve,1);
 direccionelevador=0;
 condicionelevador=2;
}
void loop() {
 //SENSOR DE PUERTA; Medida de Seguridad (por ello va al comienzo)
 if(digitalRead(sensorPuerta)==0 & condicionpuerta==2 & direccionpuerta==0){
 abrirpuerta();
 sensorp=0;
 }
 if(digitalRead(botonpuertaabierta)==0 & !sensorp){
 detenerpuerta();
 sensorp=1;
 }
 if(digitalRead(botonpiso1)==0 & piso!=1){
  piso=1;
  Serial.println(piso);
 }
  if(digitalRead(botonpiso2)==0 & piso!=2){
  piso=2;
    Serial.println(piso);
 }
   if(digitalRead(botonpiso3)==0 & piso!=3){
  piso=3;
    Serial.println(piso);
 }

 //PISO 1
 if((digitalRead(boton1up)==0 || vp1up) & sensorp){
 if(vp1up==0) vp1up=1;
 if(digitalRead(led1up)==0 & (piso!=1 || (piso==1 & condicionelevador==2))) digitalWrite(led1up,1);
 if(piso==1){
 if(condicionelevador==3){
 digitalWrite(led1up,0);
 if(condicionpuerta==0 & direccionpuerta==2){
 abrirpuerta();
 detenerpuerta();
 vp1up=0;
 direccionelevador=0;
 }/*
 if(digitalRead(botonpuertaabierta)==0){
 detenerpuerta();
 vp1up=0;
 direccionelevador=0;
 }*/
 }else if(direccionelevador==1){
 detenerelevador();
 }
 }
 if((piso==2 || piso==3) & !vp2down){
 if(condicionpuerta==0 & direccionelevador==1){
 bajarelevador();
 }
 if(condicionpuerta==1 & condicionelevador==3 & direccionelevador==1){
 cerrarpuerta();
  detenerpuerta();
 }/*
 if(digitalRead(botonpuertacerrada)==0 & condicionpuerta==2){
 detenerpuerta();
 }*/


 }
 }
 //PISO 3
 if((digitalRead(boton3down)==0 || vp3down) & sensorp){
 if(vp3down==0) vp3down=1;
 if(digitalRead(led3down)==0 & (piso!=3 || (piso==3 & condicionelevador==2))) digitalWrite(led3down,1);
if(piso==3){
 if(condicionelevador==3){
 digitalWrite(led3down,0);
 if(condicionpuerta==0 & direccionpuerta==2){
 abrirpuerta();
 detenerpuerta();
 vp3down=0;
 direccionelevador=1;
 Serial.println(condicionelevador);
 }/*
 if(digitalRead(botonpuertaabierta)==0){
 detenerpuerta();
 vp3down=0;
 direccionelevador=1;
 }*/
 }else if(direccionelevador==0){
 detenerelevador();
 }
 }
 if((piso==2 || piso==1) & !vp2up){
 if(condicionpuerta==0 & direccionelevador==0){
 subirelevador();
 }
 if(condicionpuerta==1 & condicionelevador==3 & direccionelevador==0){
 cerrarpuerta();
  detenerpuerta();
 }/*
 if(digitalRead(botonpuertacerrada)==0 & condicionpuerta==2){
 detenerpuerta();

 }*/

 }
 }
 //PISO 2 UP
 if((digitalRead(boton2up)==0 || vp2up) & sensorp){
 if(vp2up==0) vp2up=1;
 if(digitalRead(led2up)==0 & (piso!=2 || (piso==2 & condicionelevador==2))) digitalWrite(led2up,1);
 if(piso==2 & direccionelevador==0){
 if(condicionelevador==3){
 digitalWrite(led2up,0);
 if(condicionpuerta==0 & direccionpuerta==2){
 abrirpuerta();
 }
 if(digitalRead(botonpuertaabierta)==0){
 detenerpuerta();
 vp2up=0;
 direccionelevador=0;
 }
 }else {
 detenerelevador();
 }
 }
 if(piso==3 & !vp3down & !vp2down){
 if(condicionpuerta==0 & direccionelevador==1){
 bajarelevador();
 }
 if(condicionpuerta==1 & condicionelevador==3 &
direccionelevador==1){
 cerrarpuerta();
 }
 if(digitalRead(botonpuertacerrada)==0 & condicionpuerta==2){
 detenerpuerta();
 }
 
 }
 if(piso==1){
 if(condicionpuerta==0 & direccionelevador==0){
 subirelevador();
 }
 if(condicionpuerta==1 & condicionelevador==3 &
direccionelevador==0){
 cerrarpuerta();
 }
 if(digitalRead(botonpuertacerrada)==0 & condicionpuerta==2){
 detenerpuerta();
 }
 
 }
 }
 //PISO 2 DOWN
 if((digitalRead(boton2down)==0 || vp2down) & sensorp){
 if(vp2down==0) vp2down=1;
 if(digitalRead(led2down)==0 & (piso!=2 || (piso==2 &
condicionelevador==2))) digitalWrite(led2down,1);
 if(piso==2 & direccionelevador==1){
 if(condicionelevador==3){
 digitalWrite(led2down,0);
 if(condicionpuerta==0 & direccionpuerta==2){
 abrirpuerta();
 }
 if(digitalRead(botonpuertaabierta)==0){
 detenerpuerta();
 vp2down=0;
 direccionelevador=1;
 }
 }else if(direccionelevador==1){
 detenerelevador();
 }
 }
 if(piso==3){
 if(condicionpuerta==0 & direccionelevador==1){
 bajarelevador();
 }
 if(condicionpuerta==1 & condicionelevador==3 &
direccionelevador==1){
 cerrarpuerta();
 }
 if(digitalRead(botonpuertacerrada)==0 & condicionpuerta==2){
 detenerpuerta();
 }

 }
 if(piso==1 & !vp2up & !vp1up){
 if(condicionpuerta==0 & direccionelevador==0){
 subirelevador();
 }
 if(condicionpuerta==1 & condicionelevador==3 &
direccionelevador==0){
 cerrarpuerta();
 }
 if(digitalRead(botonpuertacerrada)==0 & condicionpuerta==2){
 detenerpuerta();
 }

 }
 }
 }
