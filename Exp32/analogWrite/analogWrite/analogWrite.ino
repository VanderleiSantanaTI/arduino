int ledPin = 11; // Pino do LED
int brightness = 0; // Variável para controlar o brilho do LED

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Aumenta o brilho gradualmente
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);
    delay(10); // Pequeno atraso para controlar a velocidade da variação do brilho
  }
  
  // Diminui o brilho gradualmente
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(10); // Pequeno atraso para controlar a velocidade da variação do brilho
  }
}