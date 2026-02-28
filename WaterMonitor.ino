#define BLYNK_TEMPLATE_ID "TMPL3rphzExnA"
#define BLYNK_TEMPLATE_NAME "water level sensor"
#define BLYNK_AUTH_TOKEN "YOUR_TOKEN"


#include <BlynkSimpleEsp32.h>
#include <Wifi.h>
#include <WifiClient.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define MIN_DISTANCE 20.0   // can't go below this
#define MAX_DISTANCE 100.0  // tank height
float effective_range = MAX_DISTANCE - MIN_DISTANCE;

#define LED_PIN 23
#define RELAY_PIN 22

// WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

unsigned long previousMillis = 0;
const long blinkInterval = 400;
bool blinkState = false;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  Blynk.run();

  long duration;
  float distance_cm, percentage;
  String status;

  // Trigger sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(150);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo duration
  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  distance_cm = duration * 0.0343 / 2;

  // Handle percentage and status
  percentage = 0;
  status = "Sensor Error";
  digitalWrite(LED_PIN, LOW);
  digitalWrite(RELAY_PIN, HIGH);

  // reading check
  if (duration > 0 && distance_cm <= MAX_DISTANCE) {
    percentage = ((MAX_DISTANCE - distance_cm) / effective_range) * 100.0;

    if (distance_cm <= MIN_DISTANCE || percentage >= 90) {
      status = "Tank Full";
      digitalWrite(RELAY_PIN, HIGH);

      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= blinkInterval) {
        previousMillis = currentMillis;
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
      }
    
    } else if (percentage >= 50) {
      status = "Half Full";
      digitalWrite(LED_PIN, LOW);
      digitalWrite(RELAY_PIN, LOW);
    } else if (percentage > 20) {
      status = "Low Water";
      digitalWrite(LED_PIN, LOW);
      digitalWrite(RELAY_PIN, LOW);
    } else {
      status = "Very Low";
      digitalWrite(LED_PIN, LOW);
      digitalWrite(RELAY_PIN, HIGH);
    }
  }

  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.print(" cm\t");

  Serial.print("Level: ");
  Serial.print(percentage, 1);
  Serial.println(" %");
  Serial.println(status);

  Blynk.virtualWrite(V1, percentage);
  Blynk.virtualWrite(V2, status);

  delay(500);
}
