// WiFi Connect ESP-8266
//
// Store WiFi credentials inside EEPROM with the help of a hotspot
//
// Hardware:
// * ESP-01S (ESP-8266)
//
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

const char *hostname = "wificonnect";
const char *ssid = "WifiConnect-2022";
const char *psk = "Fa7LnaU9QBHqzMrxyRUM3wGN9va9JPC3UEZM7sgns3U39D8ZHXm7LCCkqGy5AzD";
// https://zxing.org/w/chart?cht=qr&chs=350x350&chld=L&choe=UTF-8&chl=WIFI%3AS%3AWifiConnect-2022%3BT%3AWPA%3BP%3AFa7LnaU9QBHqzMrxyRUM3wGN9va9JPC3UEZM7sgns3U39D8ZHXm7LCCkqGy5AzD%3B%3B
// Tool to generate WiFi QR-Codes: http://zxing.appspot.com/generator/

extern const char index_html[];
extern const char style_css[];
extern const char main_js[];
#define GPIO_OUT 0  // GPIO0 ESP-01
#define GPIO_LED 2  // GPIO2 ESP-01
#define PORT_HTTP 80
#define PORT_DNS 53
#define MASK "255.255.255.128"
IPAddress staticIpAddress(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 128); // = 126 usable IP addresses
const int ssidMaxClient = 1; // does not allow anyone else to connect besides the first one to connect
const int ssidChannel = 7;
const bool ssidHidden = false;
String networkList;
ESP8266WebServer server(PORT_HTTP);
DNSServer dnsServer;
static bool isHotspotMode = true;

const char *wifiLocked = "🔒";
const char *wifiUnlocked = "🔓";

//////////
// LOOP //
//////////

void loop() {
  //if (WiFi.status() != WL_CONNECTED) {
  if (isHotspotMode) {
    dnsServer.processNextRequest();
    server.handleClient();
  } else {
    //TODO: esp8266 is connected to a network
  }
}


/////////////////////////
// Webserver Functions //
/////////////////////////

void setupWebServer() {
  Serial.println("HTTP server setup");
  server.on("/", handleIndexHtml);
  server.on("/style.css", handleStyleCss);
  server.on("/main.js", handleMainJs);
  server.on("/networkStatus", handleNetworkStatus);
  server.on("/wifiNetworkList", handleWiFiNetworkList);
  server.on("/wifiNetworkSetup", handleWiFiNetworkSetup);
  server.on("/reboot", handleReboot);
  server.on("/generate_204", handleCaptivePortal); // Android captive portal
  server.on("/fwlink", handleCaptivePortal);       // Microsoft captive portal
  server.onNotFound(handleNotFound);
  server.begin(); // WebServer start

  Serial.println();
  Serial.println("HTTP server started.");
  Serial.println();
}

void handleIndexHtml() {
  server.send_P(200, "text/html", index_html);
  // send_P(): send content directly from Flash PROGMEM to client
}

void handleStyleCss() {
  server.send_P(200, "text/css", style_css);
  // send_P(): send content directly from Flash PROGMEM to client
}

void handleMainJs() {
  server.send_P(200, "application/javascript", main_js);
  // send_P(): send content directly from Flash PROGMEM to client
}

void handleNotFound() {
  printRequest();

  // send 404 error message
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(404, "text/plain", "404 Page Not Found");
}

/**
   Callback for network status endpoint

   Ex: http://10.0.0.1/networkStatus
   returns json
*/
void handleNetworkStatus() {
  char buf[256] = {0};
  //IPAddress ipAddress = WiFi.localIP();
  IPAddress apAddress = WiFi.softAPIP();
  sprintf(
    buf,
    "{\"macAddress\":\"%s\", \"networkSSID\":\"%s\", \"hostname\":\"%s\", \"ipAddress\":\"%s\", \"subnetMask\":\"%s\", \"gatewayAddress\":\"%s\"}",
    WiFi.macAddress().c_str(),
    ssid,
    hostname,
    toStringIp(apAddress),
    MASK,
    toStringIp(apAddress)
  );
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", buf);
}

/*
   Callback for Captive Portal web page

   Android: http://10.0.0.1/generate_204
   Microsoft: http://10.0.0.1/fwlink
*/
void handleCaptivePortal() {
  printRequest();
  Serial.println("Request redirected to captive portal");

  server.sendHeader("Location", String("http://") + toStringIp(staticIpAddress), true);
  server.send(302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
}

void handleWiFiNetworkList() {
  printRequest();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", networkList);
}

void handleWiFiNetworkSetup() {
  printRequest();
  int statusCode;
  String content;

  if (!server.hasArg("ssid") || !server.hasArg("pass")) {
    content = "{\"Error\":\"404 not found\"}";
    statusCode = 404;
    Serial.println("Sending 404");

  } else {
    String ssid = server.arg("ssid");
    String psk = server.arg("pass");

    if (writeAndCommitWiFiSettings(ssid, psk)) {
      content = "{\"Success\":\"Saved to eeprom. Reseting to boot into new wifi\"}";
      statusCode = 200;
      ESP.reset();

    } else {
      content = "{\"Error\":\"404 not found\"}";
      statusCode = 404;
      Serial.println("Sending 404");
    }
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(statusCode, "application/json", content);
}

void handleReboot() {
  printRequest();

  ESP.reset();
  
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Rebooting...");
}

void scanNetworksAndSetupAP() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  int n = WiFi.scanNetworks();
  Serial.println("Scan completed");

  if (n == 0) {
    Serial.println("No WiFi Networks found");
    networkList = "<b>No WiFi Networks found</b>";

  } else {
    Serial.print(n);
    Serial.println(" Networks found");

    for (int i = 0; i < n; ++i) {
      // SSID and RSSI of each network
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
    buildWifiNetworksHtml(n);
  }
  Serial.println("");

  delay(100);

  wifiSetupAccessPointMode();
}

void buildWifiNetworksHtml(int n) {
  networkList = "<ol>";
  for (int i = 0; i < n; ++i) {
    networkList += "<li>";
    networkList += "<button class='btn btn-success' onclick='ssid(\"";
    networkList += WiFi.SSID(i);
    networkList += "\");'>";
    networkList += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? wifiUnlocked : wifiLocked;
    networkList += " ";
    networkList += WiFi.SSID(i);
    networkList += "</a> (";
    networkList += WiFi.RSSI(i);
    networkList += " dBm)</button>";
    networkList += "</li>";
  }
  networkList += "</ol>";
}

bool testWifi() {
  int c = 0;
  Serial.println("Waiting for WiFi to connect");
  while (c < 20) {
    if (WiFi.status() == WL_CONNECTED) {
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connection timed out, opening AP or Hotspot");
  return false;
}


////////////
// EEPROM //
////////////

const uint8_t EEPROM_MAGIC_BYTE = 0x27; // eeprom

bool readWiFiSettingsAndConnect() {
  // check if we are the author of the EEPROM bytes read
  if (EEPROM.read(137) != EEPROM_MAGIC_BYTE) {
    Serial.println("Skipping EEPROM read. Nothing to read.");
    return false;
  }
  // Read eeprom for ssid and password
  Serial.println("Reading EEPROM ssid");

  String ssid;
  for (int i = 0; i < 32; ++i) {
    ssid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.println("Reading EEPROM pass");

  String psk = "";
  for (int i = 32; i < 96; ++i) {
    psk += char(EEPROM.read(i));
  }
  Serial.print("PSK: ");
  Serial.println(psk);

  WiFi.begin(ssid.c_str(), psk.c_str());

  return true;
}

bool writeAndCommitWiFiSettings(String ssid, String psk) {
  if (ssid.length() > 0 && psk.length() > 0) {

    Serial.println("clearing eeprom");
    for (int i = 0; i < 96; ++i) {
      EEPROM.write(i, 0);
    }

    Serial.println(ssid);
    Serial.println("");
    Serial.println(psk);
    Serial.println("");

    Serial.println("writing eeprom ssid:");
    for (int i = 0; i < ssid.length(); ++i) {
      EEPROM.write(i, ssid[i]);
      Serial.print("Wrote: ");
      Serial.println(ssid[i]);
    }

    Serial.println("writing eeprom pass:");
    for (int i = 0; i < psk.length(); ++i) {
      EEPROM.write(32 + i, psk[i]);
      Serial.print("Wrote: ");
      Serial.println(psk[i]);
    }

    EEPROM.write(137, EEPROM_MAGIC_BYTE);
    EEPROM.commit();
    return true;

  } else {
    Serial.println("Empty SSID/PSK");
    return false;
  }
}

/*
   Print the URI and query string of the current request
*/
void printRequest() {
  Serial.print("Received HTTP request for: ");
  Serial.print(server.uri());

  for (int i = 0; i < server.args(); i++) {
    if (i == 0) {
      Serial.print("?");
    }
    else {
      Serial.print("&");
    }
    Serial.print(server.argName(i));
    Serial.print("=");
    Serial.print(server.arg(i));
  }
  Serial.println();
}

/**
   IP to String
*/
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}


/*
   Setup WiFi AP + DNS (for redirect)
*/
void wifiSetupAccessPointMode() {
  Serial.print("Setting soft-AP configuration... ");
  WiFi.mode(WIFI_AP);
  WiFi.setSleepMode(WIFI_NONE_SLEEP); // default=MODEM_SLEEP
  Serial.println(WiFi.softAPConfig(staticIpAddress, staticIpAddress, subnet) ? "Ready" : "Failed!");

  Serial.print("Starting soft-AP... ");
  Serial.println(WiFi.softAP(ssid, psk, ssidChannel, ssidHidden, ssidMaxClient) ? "Ready" : "Failed!");

  delay(500); // Without delay I've seen the IP address blank
  IPAddress ipAddress = WiFi.softAPIP();

  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");
  Serial.print("AP IP address:\t");
  Serial.println(toStringIp(ipAddress));
  //  Serial.println(ipAddress.toString());
  Serial.println();

  // Setup the DNS server redirecting all http requests
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(PORT_DNS, "*", ipAddress);
}


///////////
// SETUP //
///////////

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("------------------------------------");
  Serial.println("----------  WiFi Connect  ----------");
  Serial.println("------------------------------------");
  Serial.println("----> MCU: Esp8266");
  Serial.println("----> Version: 1.0");
  Serial.println("------------------------------------");
  Serial.println("------------------------------------");
  Serial.println("Starting...");
  delay(100); // power-up safety delay

  // set up GPIO pins
  pinMode(GPIO_LED, OUTPUT);

  Serial.println("Disconnecting previously connected WiFi");
  WiFi.disconnect();

  Serial.println("Checking WiFi mode...");
  EEPROM.begin(512);

  if (readWiFiSettingsAndConnect() && testWifi()) {
    isHotspotMode = false;
    Serial.println("Succesfully Connected to the Internet!");

  } else {
    isHotspotMode = true;
    Serial.println("Turning the Hotspot on");

    scanNetworksAndSetupAP();

    if (MDNS.begin(hostname)) {
      Serial.println("mDNS started");
    }
    setupWebServer();

    MDNS.addService("http", "tcp", PORT_HTTP);
  }
}
