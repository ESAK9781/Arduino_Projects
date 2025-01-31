#define DOT '.'
#define DASH '-'
#define ENDC ' '
#define ENDW '|'


const char current_message[] = "hello world";


const int beatLength = 400;

const int ledPin = 13;
const int buttonPin = 2;

const int dotLength = beatLength;
const int dashLength = 3 * beatLength;

const int endBitLength = beatLength;
const int endCharLength = 3 * beatLength;
const int spaceLength = 7 * beatLength;

const char alphabet[] = "abcdefghijklmnopqrstuvwxyz\0";
char morseCode[] = ".-  -...-.-.-.. .   ..-.--. ......  .----.- .-..--  -.  --- .--.--.-.-. ... -   ..- ...-.-- -..--.----..";
const int maxMorseLength = 4;
char * encodedString;
int playLocation = 0;
bool isFreed = true;


int getLetterIndex(char c) {
    int index = 0;
    while (alphabet[index] != '\0') {
        if (alphabet[index] == c) return index;

        index++;
    }

    return -1;
}

char * getMorse(char c) {
    int index = getLetterIndex(c);

    if (index == -1) return NULL;

    return &morseCode[index * maxMorseLength];
}

char * writeMorseCharacter(char c, char * write, bool writeSpace) {
    if (writeSpace) {
        write[0] = ENDC;
        write++;
    }

    char * encoded = getMorse(c);
    if (encoded == NULL) return write;


    for (int i = 0; i < maxMorseLength; i++) {
        if (encoded[i] == ' ') break;
    
        char toWrite = ENDC;
        switch (encoded[i]) {
            case '-':
                toWrite = DASH;
                break;
            case '.':
                toWrite = DOT;
                break;
            default:
                printf("Error encoding character '%c'\n", c);
                break;
        }

        write[0] = toWrite;
        write++;
    }


    return write;
}

char * convertToMorse(char * message) {
    int letters = 0;
    int spaces = 0;

    int messageSize = 0;
    while (message[messageSize] != '\0') {
        if (message[messageSize] == ' ') {
            spaces++;
        } else {
            letters++;
        }

        messageSize++;
    }

    int necessarySize = spaces + (letters * (maxMorseLength + 1)) + 1;

    char * morse = calloc(necessarySize, sizeof(char));
    char * writeLoc = morse;
    bool wordEnd = true;

    for (int i = 0; i < messageSize; i++) {
        char c = message[i];
        
        if (c == ' ') {
            writeLoc[0] = ENDW;
            writeLoc++;
            wordEnd = true;
            continue;
        }

        writeLoc = writeMorseCharacter(c, writeLoc, !wordEnd);
        wordEnd = false;
    }

    writeLoc[0] = '\0';


    return morse;
}






void writeDash() {
  digitalWrite(ledPin, HIGH);
  delay(dashLength);
  digitalWrite(ledPin, LOW);
  delay(endBitLength);
}

void writeSpace() {
  delay(spaceLength);
}

void writeDot() {
  digitalWrite(ledPin, HIGH);
  delay(dotLength);
  digitalWrite(ledPin, LOW);
  delay(endBitLength);
}

void writeEndC() {
  delay(endCharLength);
}




void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    if (isFreed) {
      encodedString = convertToMorse(current_message);
      isFreed = false;
    }

    if (encodedString[playLocation] == '\0') return;

    switch (encodedString[playLocation]) {
      case DOT:
        writeDot();
        break;
      case DASH:
        writeDash();
        break;
      case ENDC:
        writeEndC();
        break;
      case ENDW:
        writeSpace();
        break;
      default:
        break;
    }

    playLocation++;


  } else {
    playLocation = 0;
    if (!isFreed) {
      free(encodedString);
      isFreed = true;
    }
  }
}
