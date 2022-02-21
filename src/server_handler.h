#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include"Arduino.h"
#include <WebServer.h>
#include <WebConfig.h>
#include <WebServer.h>

extern WebServer server;
extern WebConfig conf;

extern String params;

void handleConf() ;
bool initConf();

bool initWiFi();
bool initServer();

void serverHandler( void * pvParameters );
void serverHandler();


#endif