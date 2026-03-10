# 🚗 Car Black Box

An automotive event logging system built on a **PIC18F4580 microcontroller**, inspired by aviation black box standards. Records critical vehicle events like over-speeding for post-incident analysis.

---

## 📌 Features

- Real-time vehicle speed monitoring using a potentiometer
- Logs critical events (over-speeding) to **EEPROM** for non-volatile storage
- Data retained even after power loss
- Interrupt-driven architecture using ISRs for accurate event capture
- Modular design — extendable to multiple vehicle types

---

## 🛠️ Tech Stack

| Component | Details |
|---|---|
| Microcontroller | PIC18F4580 |
| Language | Embedded C |
| IDE | MPLAB X |
| Compiler | XC8 |
| Storage | EEPROM |
| Peripherals | Potentiometer, GPIO, Timers, Interrupts |

---

## 🏗️ System Architecture

```
Potentiometer (Speed Simulation)
        |
        v
   ADC on PIC18F4580
        |
        v
  Speed Threshold Check
        |
   _____|_____
  |           |
Normal     Over-speed
  |           |
  |      Log to EEPROM
  |           |
  |___________|
        |
        v
  Data available for
  post-incident analysis
```

---

## 📂 Project Structure

```
Car_black_box/
├── main.c          # Main application logic
├── eeprom.c        # EEPROM read/write functions
├── eeprom.h
├── adc.c           # ADC configuration for speed input
├── adc.h
└── Makefile
```

---

## 🚀 How to Run

1. Open project in **MPLAB X IDE**
2. Connect PIC18F4580 board
3. Build using **XC8 compiler**
4. Flash to microcontroller
5. Rotate potentiometer to simulate speed changes
6. Read EEPROM data to view logged events

---

## 💡 Key Learnings

- Hardware-software integration with PIC microcontrollers
- ISR conflict debugging and resolution
- Non-volatile data storage using EEPROM
- Real-time event monitoring with interrupts

---

## 👤 Author

**Anagh CS** — Embedded Systems Engineer  
[GitHub](https://github.com/anaghchandran) | [LinkedIn](https://www.linkedin.com/in/anagh-chandran)
