#define LED_PIN 13
#define BUT_PIN_LOW 7
#define BUT_PIN_HIGH 6

unsigned long intervalo = 1000;
unsigned long currentTime = 0;
unsigned long previousTime = 0;
int led = LOW;
int parar = 0;
int cond_low, cond_high;
int but1 = 0, but2 = 0;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_PIN_LOW, INPUT);
  pinMode(BUT_PIN_HIGH, INPUT);
}

void loop()
{
  if (!parar)
  {
    int but_low = digitalRead(BUT_PIN_LOW);
    int but_high = digitalRead(BUT_PIN_HIGH);
    if (!but_low)
    {
      if (!cond_low)
      {
        but1 = millis();
        cond_low = 1;
        intervalo -= 100;
        if (intervalo <= 0)
        {
          intervalo = 100;
        }
      }
    }
    else
    {
      cond_low = 0;
    }
    if (!but_high)
    {
      if (!cond_high)
      {
        but2 = millis();
        cond_high = 1;
        intervalo += 100;
        if (intervalo >= 3000)
        {
          intervalo = 3000;
        }
      }
    }
    else
    {
      cond_high = 0;
    }
    currentTime = millis();
    if (currentTime - previousTime >= intervalo)
    {
      led = !led;
      previousTime = currentTime;
      digitalWrite(LED_PIN, led);
    }
    if ((but1 - but2 < 500 && but1 > but2) || (but2 - but1 < 500 && but2 > but1))
    {
      parar = 1;
    }
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
}

//Programa escrito por Vinicius Sathler e Igor Silva para a disciplina Software Embarcado 2019-2