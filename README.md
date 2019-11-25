# Flower Control
[![Arduino UNO](https://img.shields.io/badge/Arduino%20UNO-R3-blue.svg)](https://www.arduino.cc/)

Universtity arduino project  
This is simple project to plants condition monitoring. 

## Capabilities
- Color indication of temperature
- Spraying a plant depending on air humidity
- Watering a plant depending on soil moisture


## Accessories
- 1x Arduino UNO R3
- 1x DC in
- 1x Soil sensor
- 1x Bread board
- 1x DHT11 temperature and humidity control
- 2x Relay
- 2x Water pump
- 3x LED (red, yellow, green)
- 4x Hoses

## Config
- `CONFIG_TEMP_GOOD`   - default `25.0`. The temperature above which the green diode will turn on
- `CONFIG_TEMP_NORMAL` - default `18.0`. The temperature above which the yellow diode will turn on
- `CONFIG_HUMIDITY_AIR_NORMAL` - default `50`. Humidity at which there will be spraying
- `CONFIG_HUMIDITY_SOIL_NORMAL`   - default `700`. Soil moisture at which will be watering 
- `CONFIG_WATERING_TIME` - default `8`. Irrigation pump run time
- `CONFIG_SPRAYING_TIME` - default `4`. Spray pump Run time
- `CONFIG_CHECK_TIME` - default `30`. Sensor polling time

## Scheme

![Flower control scheme](https://raw.githubusercontent.com/Igga/Arduino-flower-control/master/img/scheme.png)

