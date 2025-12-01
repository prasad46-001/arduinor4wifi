#include "WiFiS3.h"
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;
WiFiServer server(80);

const char* ssid = "UNO_Matrix";
const char* password = "12345678";

String lastMessage = "";
bool loopEnabled = false;
bool isPlaying = false;
bool scrollingActive = false;
unsigned long lastLoopTime = 0;
unsigned long scrollDuration = 0;
const unsigned long loopDelayMs = 100; // Gap between scrolls

// Estimate scroll duration: (chars * pixels per char + width) * speedMs
unsigned long estimateScrollDuration(String msg, uint16_t speedMs) {
  unsigned long lengthPx = msg.length() * 12 + 12;
  return lengthPx * speedMs;
}

void setup() {
  Serial.begin(115200);
  matrix.begin();

  Serial.println("Starting Access Point...");
  if (!WiFi.beginAP(ssid, password)) {
    Serial.println("Failed to start AP!");
    while (1);
  }
  Serial.print("AP IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  lastMessage = "";
  showScrollingMessage("READY", 60);
  scrollingActive = true;
  scrollDuration = estimateScrollDuration("READY", 60);
  lastLoopTime = millis();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // AJAX button for scrolling toggle
    if (request.indexOf("GET /toggle") >= 0) {
      loopEnabled = !loopEnabled;
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/plain");
      client.println("Connection: close");
      client.println();
      client.println(loopEnabled ? "Looping" : "Stopped");
      client.stop();
      return;
    }

    // Parse incoming message
    String message = "";
    int msgIndex = request.indexOf("message=");
    if (msgIndex != -1) {
      int ampIndex = request.indexOf('&', msgIndex);
      if (ampIndex == -1) ampIndex = request.indexOf(' ', msgIndex);
      message = request.substring(msgIndex + 8, ampIndex);
      message.replace("+", " ");
      message.trim();
    }
    if (message.length() > 0) {
      lastMessage = message;
      isPlaying = true;
      showScrollingMessage(lastMessage.c_str(), 50);
      scrollingActive = true;
      scrollDuration = estimateScrollDuration(lastMessage, 50);
      lastLoopTime = millis();
    }

    // Serve HTML (message box + loop button)
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta charset='utf-8'><title>UNO Matrix Message</title>");
    client.println("<script>");
    client.println("function toggleLoop(){");
    client.println("  fetch('/toggle').then(r => r.text()).then(state => {");
    client.println("    const btn = document.getElementById('loopBtn');");
    client.println("    const st = document.getElementById('status');");
    client.println("    if(state.trim() === 'Looping'){");
    client.println("      btn.innerText = 'Stop Loop';");
    client.println("      btn.style.backgroundColor = '#ff5050';");
    client.println("      st.innerText = 'Scrolling ON';");
    client.println("    } else {");
    client.println("      btn.innerText = 'Start Loop';");
    client.println("      btn.style.backgroundColor = '#4CAF50';");
    client.println("      st.innerText = 'Scrolling OFF';");
    client.println("    }");
    client.println("  });");
    client.println("}");
    client.println("</script>");
    client.println("</head>");
    client.println("<body style='text-align:center; font-family:sans-serif;'>");
    client.println("<h2>UNO R4 WiFi Matrix Message</h2>");
    client.println("<form action='/' method='GET'>");
    client.println("<input type='text' name='message' placeholder='Type message' style='width:220px; height:30px;' value='" + lastMessage + "'>");
    client.println("<input type='submit' value='Send' style='height:35px; margin-left:10px;'>");
    client.println("</form>");
    client.println("<br>");
    client.println("<button id='loopBtn' onclick='toggleLoop()' style='height:35px; width:150px; border:none; border-radius:6px; color:white; background-color:" + String(loopEnabled ? "#ff5050" : "#4CAF50") + ";'>");
    client.println(loopEnabled ? "Stop Loop" : "Start Loop");
    client.println("</button>");
    client.println("<br><p id='status'>" + String(loopEnabled ? "Scrolling ON" : "Scrolling OFF") + "</p>");
    client.println("<p>Last Message: " + lastMessage + "</p>");
    client.println("</body></html>");
    client.stop();
  }

  // Handle looping playback
  if (lastMessage.length() > 0) {
    if (loopEnabled) {
      if (!scrollingActive && (millis() - lastLoopTime > loopDelayMs)) {
        showScrollingMessage(lastMessage.c_str(), 50);
        scrollingActive = true;
        scrollDuration = estimateScrollDuration(lastMessage, 50);
        lastLoopTime = millis();
      }
      if (scrollingActive && (millis() - lastLoopTime > scrollDuration)) {
        scrollingActive = false;
        lastLoopTime = millis();
      }
    } else { // Single shot
      if (scrollingActive && (millis() - lastLoopTime > scrollDuration)) {
        scrollingActive = false;
      }
    }
  }
}

// Scroll text helper
void showScrollingMessage(const char* txt, uint16_t speedMs) {
  matrix.clear();
  matrix.textScrollSpeed(speedMs);
  matrix.textFont(Font_5x7);
  matrix.beginText(12, 0, 0xFFFFFF);
  matrix.println(txt);
  matrix.endText(SCROLL_LEFT);
}
