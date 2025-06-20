// Opel Corsa Z10XE sufni tuning 4500-nal tiltsa a gyujtast

unsigned long previousTime = 0;
int maxFrequency = 112; // 4500 RPM = 112.5 Hz (approx.)
//solid state relay
#define mosfetPin 7
//fordulatmero
#define tachPin 3 


int rpm = 0;
int limiterDelay = 50; // Frekvencia(milyen hamar kapcsol)

float measureFrequency() {
  float highTime = pulseIn(tachPin, HIGH);
  float lowTime = pulseIn(tachPin, LOW);
  float frequency = 1000 / ((highTime / 1000) + (lowTime / 1000));
  return frequency;
}

void setup() {
  Serial.begin(9600);
  pinMode(mosfetPin, OUTPUT);
  digitalWrite(mosfetPin, LOW);
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long freq1 = measureFrequency();
  unsigned long freq2 = measureFrequency();
  unsigned long avgFreq;

  if (abs(freq1 - freq2) < 8) {
    avgFreq = (freq1 + freq2) / 2;
    rpm = avgFreq * 40; // 3 hengeresre jellemzo csak
  }

  Serial.print("RPM = "); //lenyegtelen hisz ott lesz a motorterbe de jo ha van
  Serial.println(rpm);

  if ((avgFreq > maxFrequency) && (currentTime - previousTime >= limiterDelay)) {
    digitalWrite(mosfetPin, HIGH);
    digitalWrite(mosfetPin, LOW);
    previousTime = currentTime;
  } else {
    digitalWrite(mosfetPin, LOW);
  }
}
