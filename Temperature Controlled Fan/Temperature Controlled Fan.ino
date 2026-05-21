#include <DHTesp.h> // Include the DHT library for ESP32

// Define the DHT sensor pin
#define DHT_PIN 22 // Example pin (you can change it to your actual pin)

// Initialize a DHT object
DHTesp dht;
const float t = 33.5; // Use 'int' for variable type and add 'int' before 't'

void setup() {
  Serial.begin(9600); // Start serial communication
  dht.setup(DHT_PIN, DHTesp::DHT11); // Initialize the DHT sensor with the pin and type
  pinMode(23, OUTPUT);
  pinMode(21, OUTPUT);
}

void loop() {
  // Read temperature and humidity values
  float temperature = dht.getTemperature();
  float humidity = dht.getHumidity();
 

  // Check if any reads failed and exit early (to try again)
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000); // Wait for 2 seconds before retrying
    return;
  }

  // Display temperature and humidity values on the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  if (temperature > t) { // Added space after 'if' and corrected 'digtialWrite' to 'digitalWrite'
    digitalWrite(23, LOW);
  } else {
    digitalWrite(23,HIGH);
  }

  delay(2000); // Wait for 2 seconds before taking another reading
}
