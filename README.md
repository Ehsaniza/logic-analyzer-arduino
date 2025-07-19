# 📡 RF Signal Logic Analyzer with CC1101 + Arduino + Python

This project uses an **Arduino + CC1101 RF receiver module** to capture and visualize digital RF signals with microsecond timing – turning your Arduino into a basic logic analyzer.

---

## 🔧 Features

- Works with **CC1101 RF modules** at 433.92 MHz.
- Captures **digital edges** (HIGH/LOW transitions) via GDO0 pin.
- Records each transition with precise **microsecond timestamps**.
- Stops capturing when:
  - 500 transitions are recorded, or
  - No activity for 2 seconds.
- Sends captured data over Serial.
- A Python script reads and **plots a logic waveform**.

---

## 🧰 Requirements

### Hardware

- Arduino (UNO, Nano, etc.)
- CC1101 RF Module
- Jumper wires

### Software

- Arduino IDE
- Python 3.x
- Python packages:
  - `pyserial`
  - `matplotlib`

Install Python dependencies with:

```bash
pip install pyserial matplotlib
🔌 Wiring
CC1101 Pin	Arduino Pin
VCC	3.3V
GND	GND
MOSI	25
MISO	26
SCK	33
CSN (SS)	32
GDO0	14

⚠️ Important: The CC1101 works on 3.3V only – do not connect to 5V or 5V logic without level shifters.

🚀 Getting Started
1️⃣ Upload Arduino Code
Open rf_capture.ino and upload it to your Arduino using the Arduino IDE.

The code uses external interrupt on pin 14 to detect signal changes from GDO0.

2️⃣ Run the Python Plotter
Connect Arduino via USB.

Find the port name (e.g., COM4 on Windows or /dev/ttyUSB0 on Linux).

Edit logic_plotter.py and update:

python
Copy
Edit
port = 'COM4'  # ← change this to match your Arduino's port
In your terminal or CMD:

bash
Copy
Edit
cd path/to/your/script
python logic_plotter.py
🖼 Output
You’ll get a step waveform showing 0/1 level over time (microseconds).

Example:

markdown
Copy
Edit
Time(us)   | Level
-------------------
0          | 1
540        | 0
980        | 1
...

📂 Project Files
rf_capture.ino → Arduino sketch for CC1101 signal capture

logic_plotter.py → Python script for plotting waveform

README.md → This file

🧠 Notes
Make sure Serial Monitor is closed before running the Python script.

If no data appears: check wiring, CC1101 power (3.3V only), and confirm RF activity exists.

Use http://test.sui.li/oszi/ to paste raw timings and visualize alternative waveform styles.

🙌 Credits
ELECHOUSE CC1101 Library

RC-Switch Project

Logic analyzer concept by Little Satan

Built by [YourName] – feel free to use, fork, and improve!
