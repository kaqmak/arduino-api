#ifdef ETHERNET
#ifndef plotly_ethernet_h
#define plotly_ethernet_h
#endif
#ifdef WIFI
#ifndef plotly_wifi_h
#define plotly_wifi_h
#endif
#ifdef CC3000
#ifndef plotly_cc3000_h
#define plotly_cc3000_h
#endif
#ifdef GSM
#ifndef plotly_GSM_h
#define plotly_GSM_h
#endif

#include "Arduino.h"

#ifdef ETHERNET
#include <SPI.h>
#include <Ethernet.h>
#include "plotly_ethernet.h"
#endif
#ifdef WIFI
#include <WiFi.h>
#include "plotly_wifi.h"
#endif
#ifdef CC3000
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include "plotly_cc3300.h"
#endif
#ifdef GSM
#include <GSM.h>
#include "plotly_gsm.h"
#endif

class plotly
{
	public:
		plotly();
		#ifdef ETHERNET
        EthernetClient client;
        #endif
        #ifdef WIFI
		WiFiClient client;
		#endif
		#ifdef CC3000
        Adafruit_CC3000 cc3000;
        Adafruit_CC3000_Client client;
        #endif
        #ifdef GSM
        GSMClient client;
        #endif
		void open_stream(int N, int M, char *filename, char* layout);
		void post(int x, int y);
		void post(int x, float y);
		void post(unsigned long x, int y);
		void post(unsigned long x, float y);		
		void post(float x, int y);
		void post(float x, float y);
		void post(char *x, int y);
		void post(char *x, float y);
		void post(String x, int y);
		void post(String x, float y);
		void close_stream();
		int maxStringLength;
		bool VERBOSE;
		bool DRY_RUN;
		bool timestamp;
		char *timezone;
		char *username;
		char *api_key;
		char *layout;
		char *filename;
	private:
		int M_;	 	// number of traces * 2
		int mi_; 	// counter of M_
		int N_; 	// number of series points
		int ni_; 	// counter of N_
		int nChar_; // counter of characters in querystring
		unsigned long upper_; // upper bound on length of querystring, set to the messages content-length
		unsigned char prec_;
		signed char width_;
		void sendString_(int d);
		void sendString_(float d);
		void sendString_(String d);
		void sendString_(unsigned long d);
		void sendString_(char *d);

		void send_prepad_();
		void send_postpad_();
		void print_(char *s, int nChar);
		void print_(char *s);
		void print_(String s, int nChar);
		void print_(String s);
		void print_(int s);

		void println_(char *s, int nChar); 
		void println_(unsigned int long, int nChar);
		int intlen_(int i);
};
#endif