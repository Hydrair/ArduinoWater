# 1 "/Users/mikey/Nextcloud/6.Semester/Projekt/server_esp/server_esp.ino"
# 1 "/Users/mikey/Nextcloud/6.Semester/Projekt/server_esp/server_esp.ino"
# 2 "/Users/mikey/Nextcloud/6.Semester/Projekt/server_esp/server_esp.ino" 2
# 3 "/Users/mikey/Nextcloud/6.Semester/Projekt/server_esp/server_esp.ino" 2
# 4 "/Users/mikey/Nextcloud/6.Semester/Projekt/server_esp/server_esp.ino" 2
# 5 "/Users/mikey/Nextcloud/6.Semester/Projekt/server_esp/server_esp.ino" 2
# 6 "/Users/mikey/Nextcloud/6.Semester/Projekt/server_esp/server_esp.ino" 2
# 7 "/Users/mikey/Nextcloud/6.Semester/Projekt/server_esp/server_esp.ino" 2
# 8 "/Users/mikey/Nextcloud/6.Semester/Projekt/server_esp/server_esp.ino" 2
# 9 "/Users/mikey/Nextcloud/6.Semester/Projekt/server_esp/server_esp.ino" 2

const char *ssid = "esp";
const char *password = "12345678";
// const char *ssid = "Dunkelrot";
// const char *password = "Mnawe3mk";


void setup(void)
{

 Serial.begin(9600);
   WiFi.persistent(false);
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);

 Serial.println("");

 // Wait for connection
 while (WiFi.status() != WL_CONNECTED)
 {
  // Serial.print(".");
  delay(500);
 }

 pinMode(2,0x01);
 digitalWrite(2,0x0);

 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());

 NTP.begin("pool.ntp.org",1,true,0);
    NTP.setInterval(63);

 server.on("/", handleRoot);
 server.onNotFound(handleNotFound);

 server.begin();

 pinMode(0,0x01);

 waterempty = 0;
}

void loop(void)
{
 server.handleClient();
 recvWithStartEndMarkers();

    if (newSerialData == true) {
        strcpy(tempChars, receivedChars);
        parseData();
  serialHandler();
        newSerialData = false;
    }
 checkTime();
}
