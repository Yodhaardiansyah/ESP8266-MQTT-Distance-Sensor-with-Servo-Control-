Here’s your **README.md** file for the project:  

---

# **ESP8266 MQTT Distance Sensor with Servo Control 🚀**

This project connects an **ESP8266** to WiFi and an **MQTT broker** to measure **distance** using an **ultrasonic sensor** and **control a servo motor** based on received MQTT messages.

## **📌 Features**
- 📡 **WiFi & MQTT Integration**: Connects to WiFi and publishes sensor data to an MQTT broker.
- 🎯 **Distance Measurement**: Uses an **HC-SR04 ultrasonic sensor** to measure distance.
- 🔄 **Servo Motor Control**: Controls a servo motor based on received MQTT messages.
- 📊 **Real-time Data**: Publishes distance data to an MQTT topic.
- 🔄 **Auto-Reconnect**: Automatically reconnects to WiFi and MQTT if disconnected.

---

## **🛠️ Hardware Requirements**
| Component           | Quantity |
|--------------------|----------|
| ESP8266 (NodeMCU)  | 1        |
| HC-SR04 Ultrasonic Sensor | 1        |
| Servo Motor (SG90 or similar) | 1        |
| Jumper Wires      | As needed |

---

## **📜 Wiring Diagram**
| ESP8266 Pin | Component |
|------------|-----------|
| **D5** (GPIO14) | HC-SR04 **Trig** |
| **D6** (GPIO12) | HC-SR04 **Echo** |
| **D3** (GPIO0)  | Servo Motor **Signal** |
| **3.3V / 5V**   | HC-SR04 & Servo **VCC** |
| **GND**         | HC-SR04 & Servo **GND** |

---

## **📦 Installation & Setup**
### **1️⃣ Install Required Libraries**
Ensure you have installed the following libraries in **Arduino IDE**:
- **ESP8266WiFi** (Built-in)
- **PubSubClient** ([Download](https://github.com/knolleary/pubsubclient))
- **Servo** ([Download](https://github.com/arduino-libraries/Servo))

### **2️⃣ Update Configuration**
Modify the following **WiFi & MQTT credentials** in the code:

```cpp
// WiFi Credentials
const char* ssid = "YOUR_WIFI_SSID";         
const char* password = "YOUR_WIFI_PASSWORD"; 

// MQTT Configuration
const char* mqttServer = "YOUR_MQTT_BROKER"; 
const int mqttPort = 1883;
const char* mqttUser = "YOUR_MQTT_USERNAME"; 
const char* mqttPassword = "YOUR_MQTT_PASSWORD";
```

### **3️⃣ Upload the Code**
- Connect the **ESP8266** to your PC.
- Select the correct **Board** (`NodeMCU 1.0 (ESP-12E)`) and **Port**.
- Upload the code using **Arduino IDE**.

### **4️⃣ Monitor Serial Output**
Open the **Serial Monitor** (`115200 baud rate`) to check the connection status.

---

## **📡 MQTT Topics**
| Topic | Description |
|-------|-------------|
| `sensor/distance` | Publishes the measured distance (in cm). |
| `sensor/servo` | Receives servo angle commands (0 - 180°). |

### **📩 Publish a Servo Command**
To move the servo to **90°**, send this **MQTT message**:
```
Topic: sensor/servo
Message: 90
```

---

## **📷 Example Output**
```
Connecting to WiFi...
WiFi connected!
Connecting to MQTT...
Connected to MQTT!
Publishing distance: 25 cm
Servo angle set to: 90
```

---

## **👨‍💻 Author & Credits**
- **Author:** [Yodha Ardiansyah](https://github.com/Yodhaardiansyah)  
- **Website:** [arunovasi.my.id](https://arunovasi.my.id)  
- **License:** MIT  

---
