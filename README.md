# WatchDoge

IoT based [Rickrollable](https://en.wikipedia.org/wiki/Rickrolling) intrusion detection system using PIR sensor.

## Features

- ✅ **Rickrollable** – Rickroll the intruder with a piezo buzzer.
- ✅ **Remote Control** – Control the device remotely with [Blynk](https://blynk.io/).
- ✅ **Notification** – Get notified via [Line](https://notify-bot.line.me/).

## Development Tools

- **IDE:**
  - [Arduino IDE](https://www.arduino.cc/en/software)
- **µC:**
  - Arduino Uno
  - ESP32
- **Peripherals:**
  - Piezo Buzzer
  - PIR Sensor
  - LED
- **PaaS:**
  - [Blynk](https://blynk.io/)
  - [Line Notify](https://notify-bot.line.me/)
- **Libraries:**
  - [Blynk](https://www.arduino.cc/reference/en/libraries/blynk/)
  - [TridentTD_Linenotify](https://www.arduino.cc/reference/en/libraries/tridenttd_linenotify/)

## Sketches

Arduino sketches of **WatchDoge** are separated into two modules:

- [`UNO`](UNO) – Dedicated Rickrolling Module
- [`ESP32`](ESP32) – WiFi Gateway Module

## License

Licensed under the [MIT License](LICENSE).

---

[![cover](https://user-images.githubusercontent.com/55230837/224076690-475ae0b3-3424-4229-a0d7-5e5be3477d0d.png)](https://youtu.be/dQw4w9WgXcQ)

> The final project of `ITE-433: Internet of Things` course.
