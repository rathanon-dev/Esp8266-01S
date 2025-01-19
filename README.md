# ESP8266 WebSocket Server with Static IP (Optional)

โครงการนี้เป็นตัวอย่างการควบคุม LED ที่เชื่อมต่อกับ **ESP8266** โดยใช้เว็บอินเทอร์เฟซและการสื่อสารผ่าน WebSocket โดย ESP8266 จะให้บริการหน้าเว็บที่สามารถใช้สำหรับเปิด/ปิด **LED** ผ่านการส่งข้อความใน WebSocket

## ฟีเจอร์

- การสื่อสารผ่าน **WebSocket** เพื่อการโต้ตอบแบบเรียลไทม์
- การตั้งค่า **Static IP** (IP คงที่) หรือสามารถใช้ **Dynamic IP (DHCP)** ได้ตามต้องการ
- **อินเทอร์เฟซ HTML** ที่เรียบง่ายสำหรับการเปิด/ปิด LED
- **เว็บเซิร์ฟเวอร์แบบอะซิงโครนัส (Asynchronous)** เพื่อรองรับการเชื่อมต่อ WebSocket หลายๆ คลายเอ็นต์ได้อย่างมีประสิทธิภาพ

![esp8266-01s](https://github.com/user-attachments/assets/9266c4cc-141c-4c46-857f-90c996affb3c)

## ส่วนประกอบ

- **ESP8266 NodeMCU (esp8266-01s)**: ไมโครคอนโทรลเลอร์หลัก
- **Terminal 5v relay module**: ช่องต่อแบบ Terminal ใช้ไฟเลี้ยง 5V เชื่อมต่อกับ GPIO pin 0
- **Adapter 220v to 5v**: แปลงไฟฟ้า 220v เป็น 5v กระแสตรงเลี้ยงวงจร
- **เครือข่าย Wi-Fi**: ESP8266 เชื่อมต่อกับเครือข่าย Wi-Fi ภายในบ้าน 

## ไลบรารีที่ใช้

- **ESP8266WiFi**: สำหรับการเชื่อมต่อ ESP8266 เข้ากับเครือข่าย Wi-Fi
- **[ESPAsyncWebServer](https://github.com/lacamera/ESPAsyncWebServer)**: สำหรับสร้างเว็บเซิร์ฟเวอร์แบบอะซิงโครนัส (ไม่บล็อค) ที่สามารถจัดการคำขอ HTTP ได้
- **[ESPAsyncTCP](https://github.com/dvarrel/ESPAsyncTCP)**: ไลบรารีที่ใช้สำหรับการสื่อสารผ่าน WebSocket

## การตั้งค่า

### 1. ใส่ข้อมูล Wi-Fi

คุณต้องตั้งค่าข้อมูล Wi-Fi (SSID และรหัสผ่าน) เพื่อให้ ESP8266 เชื่อมต่อกับเครือข่าย Wi-Fi ของคุณ:

```cpp
const char* ssid = "your_wifi_ssid";  // ชื่อ Wi-Fi
const char* password = "your_wifi_password";  // รหัสผ่าน Wi-Fi
```

### 2. การตั้งค่า Static IP (IP คงที่) (Optional)

หากคุณต้องการใช้ IP คงที่ (Static IP) ให้เปิดใช้การตั้งค่าดังนี้:
```cpp
// comment if you random IP Address
IPAddress local_IP(192, 168, 1, 100);   // Static IP Address
IPAddress gateway(192, 168, 1, 1);     // Gateway
IPAddress subnet(255, 255, 255, 0);    // Subnet Mask
```

### 3. การตั้งค่า WebSocket

โค้ดนี้ใช้ WebSocket สำหรับการสื่อสารแบบเรียลไทม์ระหว่าง ESP8266 และเว็บบราวเซอร์ โดยเมื่อมีการคลิกปุ่มบนหน้าเว็บ จะส่งคำสั่ง toggle ไปยัง WebSocket เพื่อสลับสถานะของ LED
ในส่วนของ HTML คุณสามารถควบคุม LED ได้จากปุ่มที่แสดงในหน้าเว็บที่ถูกเสิร์ฟจาก ESP8266
```html
<button class="button" onclick="toggle()">Toggle</button>
```
เมื่อคลิกปุ่มนี้จะส่งคำสั่ง toggle ไปยัง ESP8266 และเปลี่ยนสถานะของ LED

![Animation](https://github.com/user-attachments/assets/4d6413fb-7ce7-4576-8b63-f2616c3486c4)

# วิธีการใช้งาน
### 1. เชื่อมต่อ ESP8266 กับ Wi-Fi:
- เมื่อ ESP8266 เชื่อมต่อกับ Wi-Fi สำเร็จ จะพิมพ์ IP Address ของมันบน Serial Monitor
### 2. เปิดเว็บเบราว์เซอร์:
- ไปที่ IP ที่แสดงใน Serial Monitor เพื่อเปิดหน้าเว็บที่ใช้ควบคุม LED
### 3. ควบคุม LED:
- กดปุ่ม Toggle เพื่อเปิดหรือปิด LED
## คำแนะนำเพิ่มเติม
- หากต้องการใช้ Static IP ให้คอมเมนต์บรรทัด // comment if you random IP Address และเปิดใช้บรรทัดที่เกี่ยวข้องกับการตั้งค่า IP คงที่
- หากต้องการใช้ Dynamic IP (DHCP) ให้คอมเมนต์การตั้งค่า Static IP
# การติดตั้ง
1. ติดตั้ง Arduino IDE และติดตั้งไลบรารีที่ใช้:
- ESP8266 Board: จาก Arduino IDE ไปที่ Boards Manager แล้วติดตั้ง ESP8266.
- ไลบรารีที่ใช้: ไปที่ Sketch > Include Library > Manage Libraries... แล้วติดตั้งไลบรารี ESPAsyncWebServer และ ESPAsyncTCP
2. คัดลอกโค้ดไปที่ Arduino IDE แล้วอัปโหลดไปยัง ESP8266
# การต่อวงจร 
### 1. ไฟ 220V:
- สาย LINE เข้ากับสวิตช์ไฟ ก่อนโดยขนานกับ อะแดปเตอร์ 220V to 5V และเชื่อมต่อกับขา COM ของ Relay Module 5V.
### 2. การต่อ Relay:
- เชื่อมต่อจากขา NC ของ Relay Module 5V ไปยังหลอดไฟ
> [!NOTE]  
> **(การต่อจาก COM ไป NC จะทำให้ไฟติดทุกครั้งที่เปิดสวิตช์ไฟ, แล้วใช้ ESP ในการควบคุมการเปิด/ปิดไฟ)**
### 3. การเชื่อมต่อ Adapter:
- เชื่อมต่อ อะแดปเตอร์ 220V to 5V เข้ากับ Relay Module:
- VCC ไปที่ VCC ของ Relay Module.
- GND ไปที่ GND ของ Relay Module.
> [!NOTE]  
> โดยการเชื่อมต่อแบบนี้จะทำให้ทุกครั้งที่เปิดสวิตช์ไฟ, ไฟจะติด, และ ESP8266 จะใช้เพื่อควบคุมการเปิด/ปิดไฟตามสถานะที่ได้รับ
<img width="2136" alt="Untitled" src="https://github.com/user-attachments/assets/f1e93134-9b74-4731-a9e0-3dc5b923a1c7" />

> [!WARNING] 
> !! Always isolate 220V power before adjusting DIY circuits.!!

### การสนับสนุน:
> [!NOTE]  
> ref **[Random Nerd Tutorials]( https://randomnerdtutorials.com/)** หรือโพสต์คำถามใน GitHub Issues ของโปรเจ็กต์นี้
 
