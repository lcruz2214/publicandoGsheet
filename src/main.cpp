#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Declarando Variaveis

String GOOGLE_SCRIPT_ID = "AKfycbxr2z__0kjNbziMTFsTEeX_qn1OHuzZcnriaXQu1RGMl7uHndTc";

long timeInterval = 5000;
long timeIntervalAnterior = 0;

#define led 2
bool estadoLed = LOW;



//******************
// *** Senha da rede 
const char* ssid = "Vedderdog_2.4"; // Login
const char* password = "NaoLembro"; //Senha
//*******************

//*******************
// PROTOTIPOS DE FUNÇÃO
void sendData(String params);


const char * root_ca=\
"-----BEGIN CERTIFICATE-----\n" \
"MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n" \
"A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n" \
"Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n" \
"MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n" \
"A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n" \
"hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n" \
"v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n" \
"eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n" \
"tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n" \
"C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n" \
"zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n" \
"mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n" \
"V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n" \
"bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n" \
"3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n" \
"J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n" \
"291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n" \
"ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n" \
"AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n" \
"TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n" \
"-----END CERTIFICATE-----\n";

WiFiClientSecure client;


//**************** SETUP ***************
void setup(){
	
    Serial.begin(9600);
    pinMode(led, OUTPUT);
	
	// Set device as a Wi-Fi Station
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	
	Serial.println("Iniciando...");
	Serial.print("Connecting...");
    
    // verifica se conectado
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
		Serial.print(".");
	  }
    
    Serial.println("");
	Serial.println("WiFi conectado");
	Serial.println("IP >>: ");
	Serial.println(WiFi.localIP());
}

void loop(){

    unsigned long tempocorrentMillis = millis();

    //SE O TEMPO ATUAL MENOS O TEMPO ANTERIOR FOR MENOR QUE O INTERVALO, EXECULTA FUNÇAO
    if (tempocorrentMillis - timeIntervalAnterior > timeInterval) {
    //TEMPO ANTERIOR GUARDA O TEMPO ATUAL
        tempocorrentMillis = timeIntervalAnterior;

        if (estadoLed == LOW) { //VERIFICA O ESTADO ATUAL DO LED E SE ESTIVER EM DESLIGADO MUDA PARA LIGADO
            estadoLed = HIGH; //VARIÁVEL RECEBE ESTADO HIGH(LIGA O LED)
        } 
        else { //SENÃO, FAZ
            estadoLed = LOW; //VARIÁVEL RECEBE ESTADO LOW(DESLIGA O LED)
        }
        digitalWrite(led, estadoLed); //ESCREVE NO PINO DIGITAL O ESTADO ATUAL (LIGADO OU DESLIGADO)
    }


}
 

//bool tempo(int tempoDeEspera, )

void sendData(String params) { //function sending data to google excel sheet
	Serial.println("");
    Serial.println("Enviando dados...");
    
    HTTPClient http;
    
    String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
    Serial.print(url);
    Serial.println("Making a request");
    http.begin(url, root_ca); //Specify the URL and certificate
    int httpCode = http.GET();  
    http.end();
    Serial.println("Dados enviados...");
}

