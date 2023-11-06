#include <Servo.h>  

#define trigPin 10
#define echoPin 11
#define buzzer 9 // Definindo o pino do buzzer

//Trabalho feito por Caio Sobrinho e Igor Ricci Constantino 

long duracao;
int distancia;

Servo meuServo; 

//Function para calcular a distancia medida pelo sensor ultrassonico
int calcularDistancia(){ 
  
  digitalWrite(trigPin, LOW); //Sensor está em estado "desligado"
  delayMicroseconds(2); //por 2 microssegundos

  digitalWrite(trigPin, HIGH); //Sensor funcionando
  delayMicroseconds(10); //tempo para o sinal sonoro ir e voltar, tempo necessário do disparo (10 ms)
  digitalWrite(trigPin, LOW); //começar a ouvir o eco

  duracao = pulseIn(echoPin, HIGH); //calcula o tempo para o pino echo do sensor ir de LOW para HIGH, ou seja, quanto tempo demora para identificar o pulso de som que voltou
  distancia= duracao*0.034/2; //distancia só da ida!!!

  return distancia;
}

void setup() {
  pinMode(trigPin, OUTPUT); //Seta o trig do ultrassom como de saida
  pinMode(echoPin, INPUT); // Seta o ultrassom como entrada  
  pinMode(buzzer, OUTPUT); // Definindo o pino do buzzer como saída
  Serial.begin(9600); 
  meuServo.attach(12); //Define a porta que o servo está acoplado
}

void loop() {
  //Servo o vai até 165 graus de giro
  for(int i=15;i<=165;i++){  
    meuServo.write(i); //imprime o angulo de rotação
    delay(25); //delay de rotação
    distancia = calcularDistancia();//Enquanto o servo estiver girando de 15 a 165 graus, ele vai calcular a distancia pelo sensor de ultrassom
  
    Serial.print(i); //Imprime no serial o angulo
    Serial.print(","); 
    Serial.print(distancia); //Depois mostra a distancia calculada pelo sensor ultrassom
    Serial.print("."); 

    if(distancia < 10){ // Se a distância for menor que 10 cm
      tone(buzzer, 1000); // O buzzer será ativado
      delay(80); // Espera um segundo
      noTone(buzzer); // Desliga o buzzer
    }
    else if(distancia > 10 && distancia < 20){
      tone(buzzer, 1000);
      delay(250);
      noTone(buzzer);
    }
    else if(distancia > 20 && distancia < 30){
      tone(buzzer, 1000);
      delay(500);
      noTone(buzzer);
    }
    else {
      noTone(buzzer); // Caso contrário, o buzzer será desativado
    }

  }

  //Vai repetir o mesmo processo só que agora o servo vai voltar para o inicio, ou seja, de 165 para 15 graus
  for(int i=165;i>15;i--){  
    meuServo.write(i); //mostra o angulo de rotação
    delay(25);
    distancia = calcularDistancia(); //Enquanto o servo estiver girando de 165 a 15 graus, ele vai calcular a distancia pelo sensor de ultrassom
    
    Serial.print(i); //Imprime no serial o angulo
    Serial.print(",");
    Serial.print(distancia); //imprime a distancia do sensor
    Serial.print(".");

    if(distancia < 10){ // Se a distância for menor que 10 cm
      tone(buzzer, 1000); // O buzzer será ativado
      delay(80); // Espera um segundo
      noTone(buzzer); // Desliga o buzzer
    }
    else if(distancia > 10 && distancia < 20){
      tone(buzzer, 1000);
      delay(250);
      noTone(buzzer);
    }
    else if(distancia > 20 && distancia < 30){
      tone(buzzer, 1000);
      delay(500);
      noTone(buzzer);
    }
    else {
      noTone(buzzer); // Caso contrário, o buzzer será desativado
    }
  }
}