# AutomaticPlantWateringSystem
Developed by: Matthew Frayre, Samantha Freeland, Bryon Orellana, and Lorenz Wilkins 
Univeristy of Colorado Denver
Course: CSCI 3515 Internet of Things
Instructor: John Pace 

# Abstract 
Automating plant care has become increasingly relevant in today's time-strapped lifestyle. This
project presents a low-cost, Arduino-based automatic plant watering system designed to monitor
soil moisture and activate a watering pump when needed. Motivated by personal experience and
the growing trend of smart home automation, our system utilizes sensors, actuators, and visual
feedback mechanisms to maintain optimal soil conditions for optimal plant health. The system's
modular design and intuitive feedback make it an accessible solution for plant enthusiasts of all
skill levels. This report details our motivation, design, implementation, and future improvements
for the system.

# 1. Introduction and Motivation 
In today's fast-paced world, even basic responsibilities such as watering plants can fall by the
wayside. One of our group members experienced this firsthand when a beloved bonsai, a Snow
Rose, died due to prolonged dryness. This personal loss served as the primary motivation for our
project: to develop an automatic plant watering system that ensures consistent plant care, even
when life gets hectic.

Many plant enthusiasts struggle to maintain a consistent watering schedule, especially those
juggling school, work, and personal commitments. Our goal was to design a system that
automates essential plant care tasks such as monitoring soil moisture and watering the plant
when necessary. Not only does this system help prevent overwatering and underwatering, but it
also saves users from the financial and emotional cost of losing plants. If you own plants, you
understand how defeating it can feel when you unintentionally kill a plant. Additionally, this
kind of smart automation can be a steppingstone into broader home automation practices.

# 2. Project Overview and System Design 
Our automatic plant watering system uses an Arduino Uno R3 as the central controller. The
design includes the following major components:
• Capacitive Soil Moisture Sensor v2.0
• DHT11 Temperature and Humidity Sensor
• DC Water Pump
• 4-Channel Relay Module
• Breadboard and jumper wires
• A fan for environmental humidity control
• LEDs for real-time visual status indicators
• Tubing for water delivery

The system is designed to continuously monitor environmental and soil conditions. When the
soil moisture drops below a set threshold, the system activates the water pump using the relay
module. At the same time, LEDs provide visual feedback on the current moisture status and
whether the pump is running. A future extension could use the humidity and temperature sensors
to activate additional environmental responses.

# 3. Implementation and Hardware Setup 
Our system is built using modular components common in Arduino starter kits, with added
peripherals like a pump, fan, and sensors. The water pump is powered externally via a wall
adapter and controlled through the relay module. The capacitive soil sensor provides analog
moisture readings to the Arduino, while the temperature and humidity sensor offers additional
environmental data for future improvements.
The LEDs on the breadboard are used to indicate the following states:
• Green: Soil moisture is optimal
• Yellow: Soil is drying and may need water soon
• Red: Soil is too dry, watering is necessary
• Blue: The pump is currently running
These LEDs make it easy for users to quickly understand the system's status without needing to
check logs or screens. The relay module plays a crucial role here by allowing the Arduino to
control high-powered components like the pump and fan using safe, low-powered signals.

# 4. Algorithm and Methodology 
The core logic of the system is a threshold-based control loop:
• Analog data from the soil moisture sensor is continuously read by the Arduino.
• If the value falls below a predefined threshold (indicating dryness), a digital signal is sent
to the relay module.
• The relay activates the water pump, watering the plant for a short duration.
• Once the soil returns to an adequate moisture range, the pump is turned off.
• Simultaneously, the system reads temperature and humidity from a DHT11 sensor to
compute the heat index.
• If the heat index exceeds a comfort threshold, the system automatically activates a fan to
improve air circulation.
• Additionally, users can manually override fan behavior with a button input, ensuring
flexible climate control regardless of sensor readings.

This control algorithm is simple but effective. We use ranges of analog readings to classify
moisture levels into dry, moderate, or wet zones. Each range corresponds to one of the LED
indicators, providing an easy-to-understand UI.
The system also contains the infrastructure to support expansion, such as temperature thresholds
to activate the fan and serial output for logging sensor data. Although we did not integrate
wireless communication, it could easily be added using modules like the ESP8266.

# 5. Results and Testing 
We conducted multiple tests to ensure system reliability. The pump activated correctly when the
soil dried out, and the LEDs updated consistently. We also confirmed that the relay module
isolated the high-powered pump from the low-powered Arduino, ensuring both safety and
functionality.
