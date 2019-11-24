#include <DHT.h>

/***********
 * CONFIG *
 **********/
#define CONFIG_TEMP_GOOD            25.0
#define CONFIG_TEMP_NORMAL          18.0
#define CONFIG_HUMIDITY_AIR_NORMAL  50
#define CONFIG_HUMIDITY_SOIL_NORMAL 700
#define CONFIG_WATERING_TIME        8
#define CONFIG_SPRAYING_TIME        4
#define CONFIG_CHECK_TIME           30
/****************************************/

#define SENSOR_PIN A0
#define DHT_PIN 3
#define RELAY_WATERING_PIN 5
#define RELAY_SPRAYING_PIN 6
#define RED_PIN 9
#define YELLOW_PIN 10
#define GREEN_PIN 11

DHT dht(DHT_PIN, DHT11);

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  pinMode(RELAY_WATERING_PIN, OUTPUT);
  pinMode(RELAY_SPRAYING_PIN, OUTPUT);
  digitalWrite(RELAY_WATERING_PIN, LOW);
  digitalWrite(RELAY_SPRAYING_PIN, LOW);
  
  dht.begin();
  Serial.begin(1200);

  Serial.println("**** POLIVALKA v0.0.2 ****");
}

void loop() {
  float humidity;
  float temperature;
  int   soil; 

  readSensors(&humidity, &temperature, &soil);
  if (isnan(humidity) || isnan(temperature) || isnan(soil))
  {
    Serial.println("Read error");
    onDiods();
    delay(1000);
    loop();
  }
  writeInfo(humidity, temperature, soil);  
  
  checkTemperature(temperature);
  checkWatering(soil);
  checkSpraying(humidity);
  
  delay(CONFIG_CHECK_TIME * 1000);
}

void checkTemperature(float temperature)
{
  offDiods();
  if (temperature > CONFIG_TEMP_GOOD)
     digitalWrite(GREEN_PIN, HIGH);
  else if (temperature > CONFIG_TEMP_NORMAL)
    digitalWrite(YELLOW_PIN, HIGH); 
  else
    digitalWrite(RED_PIN, HIGH);
}

void checkWatering(int soil)
{
  if (soil < CONFIG_HUMIDITY_SOIL_NORMAL)
    return ;
  Serial.println("LOW SOIL HUMIDITY!");
  digitalWrite(RELAY_WATERING_PIN, HIGH);
  delay(CONFIG_WATERING_TIME * 1000);
  digitalWrite(RELAY_WATERING_PIN, LOW);
}

void checkSpraying(float humidity)
{
  if (humidity > CONFIG_HUMIDITY_AIR_NORMAL)
    return ;
  Serial.println("LOW AIR HUMIDITY!");  
  digitalWrite(RELAY_SPRAYING_PIN, HIGH);
  delay(CONFIG_SPRAYING_TIME * 1000);
  digitalWrite(RELAY_SPRAYING_PIN, LOW);
}

void readSensors(float *humidity, float *temperature, int *soil)
{
  *humidity = dht.readHumidity();
  *temperature = dht.readTemperature();
  *soil = analogRead(SENSOR_PIN);
}

void writeInfo(float humanidity, float temperature, int soil)
{
  Serial.println("-----");
  Serial.print("Air humidity: ");
  Serial.print(humanidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C\t");
  Serial.print("Soil humidity: ");
  Serial.println(soil);
  Serial.println("-----");
}

void offDiods(void)
{
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}

void onDiods(void)
{
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(YELLOW_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
}
