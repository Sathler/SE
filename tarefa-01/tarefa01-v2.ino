#define LED_PIN 13
#define BUT1 7
#define BUT2 6

//Inicialização de variaveis

int frequencia = 1000, t=0;
int estado = 1;
int b1_press = 0, b1_unpress = 0, b2_press=0, b2_unpress = 0, b1_last=1, b2_last=1;
int tempo_atual = 0, tempo_anterior = 0, timer;

//Estados

void estado1(){
  digitalWrite(LED_PIN, HIGH);
  tempo_anterior = millis();
  estado = 1;
}
void estado2(){
  digitalWrite(LED_PIN, LOW);
  tempo_anterior = millis();
  estado = 2;
}
void estado3(){
  digitalWrite(LED_PIN, HIGH);
  tempo_anterior = millis();
  estado = 3;
}
void estado4(){
  digitalWrite(LED_PIN, LOW);
  tempo_anterior = millis();
  estado = 4;
}
void estado5(){
  digitalWrite(LED_PIN, LOW);
  estado = 5;
}

//Manipulação da frequencia do LED

void incrementarFrequencia(){
  frequencia += 200;
  if(frequencia > 3000){
    frequencia = 3000;
  }
}

void decrementarFrequencia(){
  frequencia -= 200;
  if(frequencia < 200){
    frequencia = 200;
  }
}

//Leitura da ação

void action(){
  int b1 = digitalRead(BUT1);
  int b2 = digitalRead(BUT2);
  if(b1 != b1_last){
    b1_last = b1;
    if(b1 == 1){
      b1_unpress = 1;
      b1_press = 0;
    }
    else{
      b1_unpress = 0;
      b1_press = 1;
    }
  }
  else{
    b1_unpress = 0;
    b1_press = 0;
  }
  if(b2 != b2_last){
    b2_last = b2;
    if(b2 == 1){
      b2_unpress = 1;
      b2_press = 0;
    }
    else{
      b2_unpress = 0;
      b2_press = 1;
    }
  }
  else{
    b2_unpress = 0;
    b2_press = 0;
  }
}

//Função que verifica se o LED deve piscar

int piscar(){
  return tempo_atual - tempo_anterior > frequencia?1:0;
}

void setup()
{
  //Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT1, INPUT);
  pinMode(BUT2, INPUT);
}

void loop()
{
  //Serial.println(estado);
  tempo_atual = millis();
  action();
  switch (estado){
    //ESTADO 1
    case 1:
      if(b1_press || b2_press){
        timer = millis();
        estado3();
      }
      else if(b1_unpress){
        incrementarFrequencia();
      }
      else if(b2_unpress){
        decrementarFrequencia();
      }
      else if(piscar()){
        estado2();
      }
      break;
    //ESTADO 2
    case 2:
      if(b1_press || b2_press){
        timer = millis();
        estado4();
      }
      else if(b1_unpress){
        incrementarFrequencia();
      }
      else if(b2_unpress){
        decrementarFrequencia();
      }
      else if(piscar()){
        estado1();
      }
      break;
    //ESTADO 3
    case 3:
      if(b1_press && millis() - timer < 500){
        estado5();
      }
      else if(b2_press && millis() - timer < 500){
        estado5();
      }
      else if(b2_unpress){
        decrementarFrequencia();
        estado1();
      }
      else if(b1_unpress){
        incrementarFrequencia();
        estado1();
      }
      else if(piscar()){
        estado4();
      }
      break;
    //ESTADO 4
    case 4:
      if(b1_press && millis() - timer < 500){
        estado5();
      }
      else if(b2_press && millis() - timer < 500){
        estado5();
      }
      else if(b2_unpress){
        decrementarFrequencia();
        estado2();
      }
      else if(b1_unpress){
        incrementarFrequencia();
        estado2();
      }
      else if(piscar()){
        estado3();
      }
      break;
    //ESTADO 5
    default:
      break;
  }
}

//Programa escrito por Vinicius Sathler e Igor Silva para a disciplina Software Embarcado 2019-2