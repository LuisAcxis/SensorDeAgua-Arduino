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
    byte _pins[7];
    byte _length = 7;

  public:
    WaterTank(byte pins[]) {
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

const byte bathroomTankInputs[] = {6, 7, 8, 9, 10, 11, 12};
const WaterTank bathroomTank(bathroomTankInputs);

void setup() {
  Serial.begin(9600);
  bathroomTank.reset();
}

void loop() {
  const int percentaje = bathroomTank.getFilled();
  println(percentaje, "%");
  println("--------------");
  delay(1000);
}
