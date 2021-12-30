#include <pgmspace.h>
char main_js[] PROGMEM = R"=====(
document.addEventListener('DOMContentLoaded', function() {
    networkStatus();
    getWifiNetworkList();
}, false);
function updateConnectionStatus(status) {
    var statusBadge = document.getElementById('statusBadge');
    if (status == undefined) {
        statusBadge.className = 'btn btn-danger';
        statusBadge.innerText = 'AP Disconnected';
    } else {
        statusBadge.className = 'btn btn-success';
        statusBadge.innerText = 'AP Connected';
    }
}
function updateNetworkStatus(status) {
    var statusCard = document.getElementById('statusCard');
    var statusHtml = 'SSID: <b>' + status.networkSSID + '</b><br>\n';
    statusHtml += 'Hostname: <b>' + status.hostname + '.local</b><br>\n';
    statusHtml += 'MAC Address: <b>' + status.macAddress + '</b><br>\n';
    statusHtml += 'Subnet Mask: <b>' + status.subnetMask + '</b><br>\n';
    statusHtml += 'IP Address: <b>' + status.ipAddress + '</b><br>\n';
    statusCard.innerHTML = statusHtml;
}
function displayStatus(status) {
    updateConnectionStatus(status);
    if (status == undefined) return;
    updateNetworkStatus(status);
}
function updateWifiNetworkList(networkList) {
    var wifiCard = document.getElementById('wifiNetworkListContainer');
    wifiCard.innerHTML = networkList;
}
// called from the UI
function ssid(ssid) {
    if (ssid === "") return;
    var ssidView = document.getElementById('ssid');
    ssidView.value = ssid;
    var passView = document.getElementById('pass');
    window.setTimeout(() => passView.focus(), 0);
    var startButtonView = document.getElementById('startButton');
    startButtonView.style.visibility = 'hidden';
}
// called from the UI
function reboot() {
    var uri = '/reboot'
    var xhr = new XMLHttpRequest();
    xhr.open('GET', uri);
    xhr.send();
}
// called from the UI
function wifiNetworkSetup() {
    var uri = '/wifiNetworkSetup'
    var ssid = document.getElementById('ssid');
    if (ssid.value === "") return;
    uri += '&ssid=' + ssid.value;
    var pass = document.getElementById('pass');
    if (pass.value === "") return;
    uri += '&pass=' + pass.value;
    var xhr = new XMLHttpRequest();
    xhr.open('GET', uri);
    xhr.send();
}
// called when page is loaded
function getWifiNetworkList() {
    var wifiRequest = new XMLHttpRequest();
    wifiRequest.open('GET', '/wifiNetworkList');
    wifiRequest.onreadystatechange = function() {
        if (wifiRequest.readyState == 4) {
            if (wifiRequest.status == 200) {
                updateWifiNetworkList(wifiRequest.response);
            }
        }
    }
    wifiRequest.send();
}
// called when page is loaded
function networkStatus() {
    var statusRequest = new XMLHttpRequest();
    statusRequest.open('GET', '/networkStatus');
    statusRequest.onreadystatechange = function() {
        if (statusRequest.readyState == 4) {
            if (statusRequest.status == 200) {
                displayStatus(JSON.parse(statusRequest.response));
            } else {
                displayStatus();
            }
        }
    }
    statusRequest.send();
}
)=====";
