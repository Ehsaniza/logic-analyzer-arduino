import serial
import matplotlib.pyplot as plt

port = 'COM3'  # پورت سریال Arduino (در لینوکس مثلاً '/dev/ttyUSB0')
baudrate = 115200

# داده‌های دریافتی
timestamps = []
levels = []

with serial.Serial(port, baudrate, timeout=2) as ser:
    print("Reading data...")

    while True:
        line = ser.readline().decode('utf-8').strip()
        if line.startswith("Time"):  # رد شدن از خط عنوان
            continue
        if line == "":
            break

        try:
            time_str, level_str = line.split('\t')
            t = int(time_str)
            l = int(level_str)
            timestamps.append(t)
            levels.append(l)
        except ValueError:
            continue

# تبدیل به شکل step plot برای نمایش لاجیک دیجیتال
plt.step(timestamps, levels, where='post')
plt.xlabel("Time (us)")
plt.ylabel("Signal")
plt.title("RF Signal Logic View")
plt.ylim(-0.2, 1.2)
plt.grid(True)
plt.show()