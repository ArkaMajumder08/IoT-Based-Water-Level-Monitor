📌 Overview
This project is an IoT-based Smart Water Level Monitoring System developed using ESP32, Ultrasonic Sensor, and Blynk Cloud Platform.
The system monitors tank water levels in real time, automatically controls a pump using a relay module, and sends live data to a mobile dashboard.

It is designed to prevent:
-> Tank overflow
-> Dry-run of pump
-> Water wastage

🚀 Features
-> Real-time water level monitoring
-> Automatic pump ON/OFF control
-> LED alert indication
-> Cloud-based dashboard monitoring (Blynk)
-> Percentage-based tank level calculation
-> Serial Monitor debugging support

🛠️ Hardware Components Used
1) ESP32 Microcontroller
2) Ultrasonic Sensor (HC-SR04 / RCWL-1655)
3) Relay Module
4) LED Indicator
5) Water Pump
6) Power Supply

🌐 Software & Platform
-> Arduino IDE
-> Blynk IoT Platform
-> ESP32 WiFi Library

⚙️ Working Principle

The ultrasonic sensor measures the distance between the sensor and water surface. Distance is converted into water level percentage. 
Based on predefined thresholds:

---> Tank Full (≥90%) → Pump OFF + LED blinking

---> Half Full (≥50%) → Pump ON

---> Low Water (>20%) → Pump ON

---> Very Low (≤20%) → Pump OFF

Data is sent to Blynk cloud dashboard in real time.

📊 Threshold Logic
Water Level	Status	Pump	LED
≥ 90%	Tank Full	OFF	Blinking
≥ 50%	Half Full	ON	OFF
> 20%	Low Water	ON	OFF
≤ 20%	Very Low	OFF	OFF

📱 Blynk Dashboard Setup:-
V1 → Water Level Percentage
V2 → Tank Status String
