const int ledPin = 13;
const int buttonPin = 2;


const int dotLength = 500;
const int dashLength = 1000;

const int pauseLength = 500;
const int spaceLength = 2000;

const char alphabet[] = "abcdefghijklmnopqrstuv\0";
const char morse[] = ".-  -...-.-.-.. .   ..-.--. ......  .----.- .-..--  -.  --- .--.--.-.-. ... -   ..- ...-.-- -..--.----..";
const int maxMorseLength = 4;










int messageIndex = 0;
int charIndex = 0;
// only supports lowercase alphabetical characters
const char message[] = "hello world\0";



int getLetterIndex(char c) {
  int index = 0;
  while (alphabet[index] != '\0') {
    if (alphabet[index] == c) {
      return index;
    }

    index++;
  }

  return -1;
}

void writeDash() {
  digitalWrite(ledPin, HIGH);
  delay(dashLength);
  digitalWrite(ledPin, LOW);
  delay(pauseLength);
}

void writeSpace() {
  delay(spaceLength);
}

void writeDot() {
  digitalWrite(ledPin, HIGH);
  delay(dotLength);
  digitalWrite(ledPin, LOW);
  delay(pauseLength);
}




void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {



    if (message[messageIndex] == '\0') return;
    

    if (message[messageIndex] == ' ') {
      messageIndex++;
      charIndex = 0;
      writeSpace();
      return;
    }


    int letterIndex = getLetterIndex(message[messageIndex]);
    if (letterIndex == -1) return;

    char * morseChars = &morse[(letterIndex * maxMorseLength)];


    char currentSymbol = ' ';
    if (charIndex < maxMorseLength) {
      currentSymbol = morseChars[charIndex];
    }



    if (currentSymbol == ' ') {
      charIndex = 0;
      messageIndex++;


      return;
    }



    if (currentSymbol == '-') {
      writeDash();
    } else {
      writeDot();
    }

    charIndex++;
  } else {
    messageIndex = 0;
    charIndex = 0;
  }
}
