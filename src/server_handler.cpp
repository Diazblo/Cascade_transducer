#include"Arduino.h"
#include "server_handler.h"
#include"serial_debug.h"

WebServer server;
WebConfig conf;

String params =   "["
  "{"
  "'name':'ssid',"
  "'label':'WLAN ID',"
  "'type':"+String(INPUTTEXT)+","
  "'default':''"
  "},"
  "{"
  "'name':'pwd',"
  "'label':'WLAN Password',"
  "'type':"+String(INPUTPASSWORD)+","
  "'default':''"
  "},"
  "{"
  "'name':'cutoff_freq',"
  "'label':'Cutoff frequency for peaks',"
  "'type':"+String(INPUTNUMBER)+","
  "'min':1,'max':20,"
  "'default':'10'"
  "},"
  "{"
  "'name':'dev_mode',"
  "'label':'Debug Mode',"
  "'type':"+String(INPUTCHECKBOX)+","
  "'default':'0'"
  "}"
  "]";


bool initConf(){
  conf.setDescription(params);
  conf.readConfig();
  server.on("/",handleConf);
  return 1;
}

void handleConf() {
  conf.handleFormRequest(&server);
  if (server.hasArg("SAVE")) {
    uint8_t cnt = conf.getCount();
    V_PRINTln("*********** Konfiguration ************");
    for (uint8_t i = 0; i<cnt; i++) {
      V_PRINT(conf.getName(i));
      V_PRINT(" = ");
      V_PRINTln(conf.values[i]);
    }
    if (conf.getBool("switch")) V_PRINTf("%s %s %i %5.2f \n",
                                conf.getValue("ssid"),
                                conf.getString("continent").c_str(), 
                                conf.getInt("amount"), 
                                conf.getFloat("float"));
  }
}


bool initWiFi() {
  boolean connected = false;
  WiFi.mode(WIFI_STA);
  V_PRINT(conf.values[0]);
  V_PRINTln("");
  if (conf.values[0] != "") {
    WiFi.begin(conf.values[0].c_str(),conf.values[1].c_str());
    uint8_t cnt = 0;
    while ((WiFi.status() != WL_CONNECTED) && (cnt<20)){
      delay(500);
      V_PRINT(".");
      cnt++;
    }
    V_PRINTln();
    if (WiFi.status() == WL_CONNECTED) {
      V_PRINT("IP-Address = ");
      V_PRINTln(WiFi.localIP());
      connected = true;
    }
  }
  if (!connected) {
        WiFi.mode(WIFI_AP);
        WiFi.softAP(conf.getApName(),"",1);  
  }
  return connected;
}

bool initServer(){
  server.begin(80);
  return 1;
}

void serverHandler( void * pvParameters ){
  while(1)
    server.handleClient();
//  MDNS.update();
}
void serverHandler(){
    server.handleClient();
//  MDNS.update();
}