void println() {
  Serial.println();
}

template <typename T, typename... Types>
void println(T first, Types... other) {
  Serial.print(first);
  println(other...) ;
}

class WaterTank {
  private:
    byte _length;
    byte _pins[7];

  public:
    WaterTank(byte pins[], int length = 7) {
      _length = length;
      _pins[_length] = {};
      for (int i = 0; i < _length; i++) {
        _pins[i] = pins[i];
      }
    }
    reset() {
      for (byte i = 0; i < _length; i++) {
        pinMode(_pins[i], INPUT);
      }
    }
    bool verifyStatusWhitSiblings(int arrayPosPin) {
      bool contin = true;

      for(byte i = 0; i < _length; i++) {
        if(contin) {
          const int pin = _pins[i];
          const int status = digitalRead(pin);
          Serial.print("[");
          Serial.print(pin);
          Serial.print("-");
          Serial.print(status);
          Serial.print("] ");
          if(i <= arrayPosPin && status == 0 && contin) {
            // return false;
            contin = false;
          } else if(i > arrayPosPin && status > 0 && contin) {
            // return false;
            contin = false;
          }
        }
      }
      Serial.println();

      return contin;
    }
    int getFilled() {
      const float length = _length;
      const float percentajeOfPin = 100 / length;
      for (int i = _length - 1; i >= 0; i--) {
        const int pin = _pins[i];
        const bool isOn = digitalRead(pin);
        if(pin == 24) {
          println("Checking: ", isOn);
        }
        if(isOn) {
          println("Verifing: ", pin);
          if(verifyStatusWhitSiblings(i)) {
            println("Verified: ", pin);
            const float percentaje = percentajeOfPin * (i + 1);
            return round(percentaje);
          }
        }
      }
      return 0;
    }
};

const byte bathroomTankInputs1[] = {7, 8, 9, 10, 11, 12, 13};
const WaterTank bathroomTank1(bathroomTankInputs1, 7);

const byte bathroomTankInputs2[] = {14, 15, 16, 17, 18, 19, 6};
const WaterTank bathroomTank2(bathroomTankInputs2, 6);

void setup() {
  Serial.begin(9600);
  bathroomTank1.reset();
  bathroomTank2.reset();
}

void loop() {
  println("--------------");
  println("Tank 1");
  const int percentaje1 = bathroomTank1.getFilled();
  println(percentaje1, "%");
  println("--------------");

  println("Tank 2");
  const int percentaje2 = bathroomTank2.getFilled();
  println(percentaje2, "%");
  println("--------------");

  delay(3000);
}
