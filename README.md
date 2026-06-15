# ESP32 Smart Home Automation System

## Overview

A Smart Home Automation System developed using ESP32 that automatically controls home appliances based on environmental conditions.

## Features

* Automatic room light control using LDR
* Temperature-controlled fan using DHT22
* OLED display for live monitoring
* Push-button appliance control
* Real-time sensor monitoring

## Components Used

* ESP32
* LDR Sensor
* DHT22 Temperature Sensor
* SSD1306 OLED Display
* LEDs
* Push Buttons

## Working Principle

1. The LDR detects ambient light levels.
2. When the environment becomes dark, the room light turns ON automatically.
3. The DHT22 continuously monitors temperature.
4. When the temperature exceeds the threshold, the fan turns ON automatically.
5. The OLED displays temperature, light status, and appliance status.

## Project Images

### Circuit Diagram

![Circuit Diagram](circuit.png)

### OLED Output

![OLED Output](oled_output.png)


## Future Enhancements

* Wi-Fi dashboard
* Mobile application control
* MQTT integration
* Cloud data logging
* Voice assistant support

## Author

Shunmathi

