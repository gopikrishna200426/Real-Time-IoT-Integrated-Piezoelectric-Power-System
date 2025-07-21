# Real-Time-IoT-Integrated-Piezoelectric-Power-System
 A Smart Energy Harvesting &amp; Monitoring System using Piezoelectric Transducers and IoT


## Project overview

This project presents a **real-time IoT-based energy harvesting system** that converts ambient mechanical vibrations into electrical energy using **piezoelectric transducers**. It integrates sensors and IoT technologies to **monitor voltage, current, power output**, and detect **transducer failures**, enabling intelligent data logging and real-time visual analytics through **mobile or web dashboards**.


##  Problem Statement

Traditional piezoelectric systems **lack real-time monitoring** and **fault detection**, making them inefficient for practical, large-scale deployment. This project solves those limitations by building an integrated system that:

- Measures electrical output from each transducer
- Detects faulty transducers using **force sensors**
- Sends live performance data to the **cloud**
- Displays real-time insights through **visual dashboards**


##  Objectives

- Convert mechanical vibrations/pressure into electrical energy
- Use **INA3221** for measuring voltage, current, and power
- Integrate **force sensors** for fault detection
- Collect and transmit data using **ESP32**
- Store and visualize data using **IoT Cloud & Dashboards**
- Build a scalable and modular system for future expansion


##  System Architecture

Mechanical Vibrations
        ↓
Piezoelectric Transducers
        ↓
     Rectifier
        ↓
    INA3221 Sensor
        ↓
       ESP32
        ↓
   IoT Cloud (Firebase)

## Methodology
1.	Energy Harvesting
	Transducers convert pressure/vibrations into electricity.
2.	Signal Conditioning
	AC signal is rectified to DC.
 INA3221 reads voltage and current for each line.
3.	Fault Detection
 Force sensors detect applied pressure.
	If pressure is applied but voltage is not present → Transducer is faulty.
4.	IoT Integration
 ESP32 sends sensor data via WiFi to the cloud.
 Real-time updates are visualized on connected dashboards.
5.	Scalability & Optimization
	Data analytics help optimize output.
	System supports up to 20 transducers with future expansion options.

## Test Results / Output
Real-time data collected for voltage, current, and power output.
Transducer failure successfully detected using logic comparisons.
Web dashboard displays live status, output, and active/faulty unit animation.

## Result Images:-
 <img width="524" height="324" alt="Screenshot 2025-07-21 at 10 53 49 PM" src="https://github.com/user-attachments/assets/b3724c7d-753d-4aff-984d-21b58de4a364" />
 
## Tech Stack
Hardware: ESP32, Piezoelectric Transducers, INA3221, Force Sensors
Firmware: Arduino IDE (C/C++ for ESP32)
Cloud/IoT Platform: Firebase (Realtime DB).
Data Processing: Real-time logic on ESP32 and cloud API

## Applications
Smart Roads: Harvest energy from vehicles and monitor traffic patterns.
Industrial Monitoring: Detect machine wear via vibration data.
Wearable Tech: Self-powered systems for health tracking.
Smart Infrastructure: Structural health monitoring in buildings.
Wireless IoT Networks: Self-sustaining sensor systems.

## Future Improvements
Integrate battery storage and charge controller.
Add AI-based fault prediction using historical data.
AI controlled traffic monitering system integrated in Piezoelectric Power System

## project Images:- 
![image](https://github.com/user-attachments/assets/e47e71ef-f96c-48fb-b08b-9344377d3588)
![image](https://github.com/user-attachments/assets/5593d6cf-6e95-493a-b5ac-afbccbf631e9)




        
