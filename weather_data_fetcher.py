import serial
import requests
import time

# Configuration de la connexion série
ser = serial.Serial('COM3', 9600)  # Remplacez 'COM3' par votre port série
time.sleep(2)

cities = ["Paris", "London", "Lisbon", "Rome", "Moscow", "New York"]

def get_weather_data(city):
    api_key = "Votre_Cle_API"
    url = f"http://api.weatherapi.com/v1/current.json?key={api_key}&q={city}&aqi=no"
    response = requests.get(url)
    if response.status_code == 200:
        data = response.json()
        temp = data['current']['temp_c']
        condition = data['current']['condition']['text']
        return f"{city}: {temp}C, {condition}\n"
    else:
        return "Erreur de requête\n"

def update_weather_data():
    weather_data = ""
    for city in cities:
        weather_data += get_weather_data(city)
        time.sleep(1)  # Petite pause entre chaque requête
    ser.write(weather_data.encode())

# Mise à jour initiale au démarrage
update_weather_data()

# Mise à jour toutes les 4 heures
while True:
    time.sleep(14400)  # 4 heures = 14400 secondes
    update_weather_data()
