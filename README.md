

# 📏🚗 Measurement Vehicle Project

A remote-controlled vehicle system that measures distances and calculates areas with real-time LCD feedback.

<img width="1819" height="708" alt="Screenshot 2025-08-01 at 10 21 29 PM" src="https://github.com/user-attachments/assets/e7d99651-a898-4716-96a9-4629abed4047" />

### Remote Controller
- **Interactive LCD Display** showing:
  - Real-time distance measurements
  - Length/width calculations
  - Area computation
- **Dual-mode operation**:
  - Distance Mode: Tracks movement
  - Area Mode: Guides through length/width measurements
- **Wireless Control** via nRF24L01 module
- **Joystick Navigation** for precise vehicle movement

### Vehicle Unit
- **Precision Movement** with H-bridge motor control
- **Accurate Distance Tracking** using wheel encoders
- **Wireless Feedback** of measurement data
- **Debounced Interrupts** for reliable sensor readings

## Hardware Components

### Remote Controller
- Arduino Uno/Nano
- nRF24L01 RF Transceiver
- 16x2 LCD Display
- Analog Joystick
- Mode Selection Buttons

### Vehicle
- Arduino Uno/Nano
- nRF24L01 RF Transceiver
- L298N Motor Driver
- 2x DC Motors with Encoders
- Power Supply

## Installation & Setup

### Prerequisites
- Arduino IDE
- Required Libraries:
  - `RF24` (for wireless communication)
  - `LiquidCrystal` (for LCD display)
  - `SPI` (for nRF24L01 module)


## Usage Instructions

1. Power both controller and vehicle units
2. Select mode using buttons:
   - **Distance Mode**: Shows real-time movement
   - **Area Mode**: Guides through area measurement
3. Use joystick to navigate vehicle
4. View measurements on LCD display

## Wiring Diagrams

<img width="921" height="632" alt="Screenshot 2025-08-01 at 10 31 26 PM" src="https://github.com/user-attachments/assets/a9e3fa68-226b-4c2c-b8da-f9ca5ddc99ea" />


### Remote Controller

<img width="921" height="523" alt="Screenshot 2025-08-01 at 10 13 30 PM" src="https://github.com/user-attachments/assets/86e76d42-35f3-417a-beda-ab81d48e92a8" />




