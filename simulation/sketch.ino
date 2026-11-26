
const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int speakerPin = 10;
const int numButtons = 8;

const int ledPins[] = {A0, A1, A2, A3, A4, 11, 12, 13};
const int melodyButton = A5;

const int noteFrequencies[] = {
  262, 294, 330, 349,
  392, 440, 494, 523
};

void setup() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(speakerPin, OUTPUT);
  pinMode(melodyButton, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(melodyButton) == LOW) {
    delay(30);

    if (digitalRead(melodyButton) == LOW) {
      playMelody();

      while (digitalRead(melodyButton) == LOW) {
        delay(10);
      }
    }
  }

  for (int i = 0; i < numButtons; i++) {

    if (digitalRead(buttonPins[i]) == LOW) {
      delay(30);

      if (digitalRead(buttonPins[i]) == LOW) {

        digitalWrite(ledPins[i], HIGH);

        tone(speakerPin, noteFrequencies[i]);

        while (digitalRead(buttonPins[i]) == LOW) {
          delay(10);
        }

        noTone(speakerPin);
        digitalWrite(ledPins[i], LOW);
      }
    }
  }
}

void playMelody() {

  int melody[] = {
    262, 294, 330, 262,
    262, 294, 330, 262,
    330, 349, 392,
    330, 349, 392,
    392, 440, 392, 349, 330, 262,
    262, 392, 262
  };

  int noteDuration[] = {
    400, 400, 400, 400,
    400, 400, 400, 400,
    400, 400, 800,
    400, 400, 800,
    300, 300, 300, 300, 600, 800,
    500, 500, 800
  };

  int sizeMelody = sizeof(melody) / sizeof(melody[0]);

  for (int i = 0; i < sizeMelody; i++) {

    int duration = noteDuration[i];

    tone(speakerPin, melody[i]);

    digitalWrite(ledPins[i % numButtons], HIGH);

    delay(duration);

    noTone(speakerPin);

    digitalWrite(ledPins[i % numButtons], LOW);

    delay(80);
  }
}
