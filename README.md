# IEQ_monitor_Arie
Indoor environmental monitoring system — Arduino + SHT40 + SCD30

Add files via upload
# Envirotech — Indoor Environmental Monitoring System

Mid-semester project | DIY Sensors for Environmental Research | 2026

## Overview
A low-cost open-source system for continuous indoor monitoring of 
temperature, relative humidity, and CO₂ built with Arduino Uno.

## Hardware
- Arduino Uno R3
- Adafruit SHT40 (T/RH sensor)
- Sensirion SCD30 (CO₂/T/RH sensor)
- SparkFun Level Shifting MicroSD Breakout
- DFRobot Gravity I2C Hub V1.0

## Repository Contents
| File | Description |
|------|-------------|
| `mid_project_arie.ino` | Arduino logging code |
| `IEQ_plot.ipynb` | Python data cleaning & plotting script |
| `DATA (1).CSV` | Raw logged data (4.5 days, ~12,900 rows) |
| `IEQ_Monitoring_Figures.png` | Results figures |
| `circuit_image.png` | Wiring diagram |
| `Mid-semester Project_Arie_207223447.docx` | Full project report |

## How to Run the Plot Script
1. Install dependencies: `pip install matplotlib numpy`
2. Place `DATA (1).CSV` and `IEQ_plot.ipynb
` in the same folder
3. Run: `IEQ_plot.ipynb
`
4. Output: `IEQ_Monitoring_Figures.png`

## Results Summary
- Duration: ~4.5 days continuous logging
- Temperature (SHT40): 21.1–28.2°C, mean 25.2°C
- Relative Humidity (SHT40): 25.9–66.8%, mean 48.5%
- CO₂ (SCD30): 150–729 ppm, mean 248 ppm
