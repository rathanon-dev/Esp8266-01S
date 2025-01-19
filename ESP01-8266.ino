#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Network credentials
const char* ssid = "ABCDEFG";
const char* password = "1234567890";
// Uncomment the following lines if you want to use Fixed IP address
// comment if you random IP Address
IPAddress local_IP(192, 168, 1, 100);   // Fixed IP Address
IPAddress gateway(192, 168, 1, 1);    // Gateway
IPAddress subnet(255, 255, 255, 0);   // Subnet Mask

// LED configuration
const int ledPin = 0; // PINOUT >> GPIO 0 
bool ledState = 1; // State 

// Web server and WebSocket setup
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// HTML page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP WebSocket</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; background-color: #F8F7F9; margin: 0; }
    h1 { color: #143642; }
    .button { padding: 15px; font-size: 24px; background-color: #0f8b8d; color: white; border: none; border-radius: 5px; }
    .state { font-size: 1.5rem; color: #8c8c8c; font-weight: bold; }
  </style>
</head>
<body>
  <h1>ESP WebSocket Control</h1>
  <p class="state">State: <span id="state">%STATE%</span></p>
  <button class="button" onclick="toggle()">Toggle</button>
<script>
  const gateway = `ws://${window.location.hostname}/ws`;
  let websocket;
  window.onload = () => {
    websocket = new WebSocket(gateway);
    websocket.onmessage = ({ data }) => document.getElementById('state').innerText = data === '1' ? 'ON' : 'OFF';
  };
  function toggle() { websocket.send('toggle'); }
</script>
</body>
</html>
)rawliteral";

// Send WebSocket message to clients
void notifyClients() { ws.textAll(String(ledState)); }

// Handle WebSocket messages
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  if (strncmp((char*)data, "toggle", len) == 0) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    notifyClients();
  }
}

// Handle WebSocket events
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_DATA) handleWebSocketMessage(arg, data, len);
}

// Initialize WebSocket
void initWebSocket() {
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
}

// Replace variables in HTML
String processor(const String& var) { return var == "STATE" ? (ledState ? "ON" : "OFF") : String(); }

void setup() {
  // Start Serial and Wi-Fi
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  // Configure Fixed IP
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Failed to configure static IP");
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP());

  // Initialize WebSocket and Server
  initWebSocket();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html, processor);
  });
  server.begin();
}

void loop() { ws.cleanupClients(); }
