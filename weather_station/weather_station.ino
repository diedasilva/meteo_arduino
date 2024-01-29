#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialisation de l'écran LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Ajustez l'adresse 0x27 selon votre module

// Potentiomètre
const int potPin = 34; // Pin analogique pour le potentiomètre

void setup() {
  Serial.begin(115200);

  // Initialisation de l'écran LCD
  lcd.init();
  lcd.backlight();

  // Affichez un message de bienvenue
  lcd.setCursor(0,0);
  lcd.print("Meteo Station");
  lcd.setCursor(0,1);
  lcd.print("Waiting Data...");
}

void loop() {
  int potValue = analogRead(potPin); // Lire la valeur du potentiomètre
  String city = getCityFromPotValue(potValue); // Obtenir le nom de la ville

  if (Serial.available()) {
    String weatherData = Serial.readStringUntil('\n');
    if (weatherData.startsWith(city)) { // Vérifier si les données correspondent à la ville sélectionnée
      lcd.clear();
      lcd.print(weatherData);
    }
  }
}

String getCityFromPotValue(int value) {
  int segmentSize = 4096 / 6; // Pour six villes
  if (value < segmentSize) return "Paris";
  else if (value < segmentSize * 2) return "London";
  else if (value < segmentSize * 3) return "Lisbon";
  else if (value < segmentSize * 4) return "Rome";
  else if (value < segmentSize * 5) return "Moscow";
  else return "New York";
}
