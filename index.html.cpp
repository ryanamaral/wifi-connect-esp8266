#include <pgmspace.h>
char index_html[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html lang='en' dir='ltr'>
<head>
    <meta http-equiv='Content-Type' content='text/html; charset=utf-8' />
    <meta name='viewport' content='width=device-width, initial-scale=1.0' />
    
    <title>ESP8266 WiFi Setup</title>

    <link type='text/css' href='style.css' rel='stylesheet'>
    
    <script type='text/javascript' src='main.js'></script>
</head>
<body>
    <div class='navbar navbar-expand-lg navbar-dark bg-primary mb-3'>
        <div class='container'>
            <span class='navbar-brand'>ESP8266 WiFi Connect</span>
            <div class='navbar-right'>
                <span id='statusBadge' class='btn btn-danger' style='pointer-events: none;'>Disconnected</span>
            </div>
        </div>
    </div>
    <div class='container'>
        <div class='card mb-3'>
            <div class='card-body'>
                <h4 class='card-title'>AP Network Status</h4>
                <div id='statusCard' class='card-text'>Loading...</div>
            </div>
        </div>
        <div class='card mb-3'>
            <div class='card-body'>
               <h4 class='card-title'>Connect WiFi Network</h4>
               <form method='get' action='wifiNetwork'>
                  <input id='ssid' name='ssid' length=32 maxlength=32 class='form-control' placeholder='SSID' style='margin-top: 22px;'>
                  <input id='pass' name='pass' length=63 maxlength=63 class='form-control' placeholder='Password' style='margin-top: 10px;'>
               </form><br>
               <button class='btn btn-primary mr-3' onclick='wifiNetworkSetup();'>Save & Reboot</button>
               <button class='btn btn-danger mr-3' onclick='reboot();'>Just Reboot</button>
            </div>
        </div>
        <div class='card mb-3'>
            <div class='card-body'>
               <h4 class='card-title'>Select WiFi Network</h4>
               <div id='wifiNetworkListContainer'></div>
            </div>
        </div>
    </div>
</body>
</html>
)=====";
