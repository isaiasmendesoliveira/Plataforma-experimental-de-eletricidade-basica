/*  Criado por Isaias Mendes
    Mestrado em IoT
    Experimento Remoto
    2022
*/
// INCLUSÃO DAS BIBLIOTECAS
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <FS.h>
#include <WebSocketsServer.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// MODO DE INICIAR OS DISPLAYS
#define OLED_RESET -1
// DEFINIÇÃO DO ENDEREÇO DO MULTIPLEXADOR I2C
#define MULTIPLEXADOR 0x70
// DEFINIÇÃO DO TAMANHO DAS TELAS DOS DISPLAYS
#define LARGURA_TELA 128  // Largura dos display em pixels
#define ALTURA_TELA 64    // Altura dos display em pixels
// CRIAÇÃO DOS OBJETOS PARA CADA DISPLAY
Adafruit_SSD1306 DisplayUm(LARGURA_TELA, ALTURA_TELA, &Wire, OLED_RESET);
Adafruit_SSD1306 DisplayDois(LARGURA_TELA, ALTURA_TELA, &Wire, OLED_RESET);
Adafruit_SSD1306 DisplayTres(LARGURA_TELA, ALTURA_TELA, &Wire, OLED_RESET);
Adafruit_SSD1306 DisplayQuatro(LARGURA_TELA, ALTURA_TELA, &Wire, OLED_RESET);
// CRIAÇÃO DOS OBJETOS PARA CADA SENSOR
Adafruit_INA219 SensorUm(0x40);
Adafruit_INA219 SensorDois(0x40);
Adafruit_INA219 SensorTres(0x40);
Adafruit_INA219 SensorQuatro(0x40);
// CRIAÇÃO DOS OBJETOS PARA O SERVIDOR WEB E PARA O SERVIDOR WEBSOCKT
WebServer ServidorWeb(80);        // Criação do servidor web na porta 80
WebSocketsServer WebSocket(81);   // Criação do servidor websockt na porta 81

File UploadArquivo;  

const char *NomeRede = "xxx"; 
const char *SenhaRede = "xxx";  

int UsuarioAtivo = -1;
// Estados das chaves ao iniciar o programa
int ChaveUmStatus = 0;
int ChaveDoisStatus = 0;
int ChaveTresStatus = 0;
int ChaveQuatroStatus = 0;
int ChaveCincoStatus = 0;
int ChaveSeisStatus = 0;
int ChaveSeteStatus = 0;
int ChaveOitoStatus = 0;

char *StatusExperimento = "N";
// novo
void SelecionaCanal(uint8_t Canal) {
  if (Canal > 7) return;
 
  Wire.beginTransmission(MULTIPLEXADOR);
  Wire.write(1 << Canal);
  Wire.endTransmission();  
}

void setup(){
  // Chave um
  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);
  // Chave dois
  pinMode(33, OUTPUT);
  digitalWrite(33, HIGH);
  // Chave três
  pinMode(19, OUTPUT);
  digitalWrite(19, HIGH);
  // Chave quatro
  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
  // Chave cinco
  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);
  // Chave seis
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
  // Chave sete
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  // Chave oito
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);


  Wire.begin();
  // Sensor Um
  SelecionaCanal(0);
  if (!SensorUm.begin()) {
    Serial.println("Falha no sensor um");
    while (1) { delay(10); }
  }
  // Sensor Dois
  SelecionaCanal(1);
   if (!SensorDois.begin()) {
    Serial.println("Falha no sensor dois");
    while (1) { delay(10); }
  }
  // Sensor Três
  SelecionaCanal(2);
   if (!SensorTres.begin()) {
    Serial.println("Falha no sensor três");
    while (1) { delay(10); }
  }
  // Sensor Quatro
  SelecionaCanal(3);
   if (!SensorQuatro.begin()) {
    Serial.println("Falha no sensor quatro");
    while (1) { delay(10); }
  }
  // Display Um
  SelecionaCanal(4);
  if(!DisplayUm.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Falha no display um"));
  }
  DisplayUm.clearDisplay();
  DisplayUm.setTextColor(WHITE);
  DisplayUm.setTextSize(1);
  DisplayUm.print("Display um");
  DisplayUm.display();
  // Display Dois
  SelecionaCanal(5);
  if(!DisplayDois.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Falha no display dois"));
  }
  DisplayDois.clearDisplay();
  DisplayDois.setTextColor(WHITE);
  DisplayDois.setTextSize(1);
  DisplayDois.print("Display dois");
  DisplayDois.display();
  // Display Três
  SelecionaCanal(6);
  if(!DisplayTres.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Falha no display três"));
  }
  DisplayTres.clearDisplay();
  DisplayTres.setTextColor(WHITE);
  DisplayTres.setTextSize(1);
  DisplayTres.print("Display três");
  DisplayTres.display();
  // Display Quatro
  SelecionaCanal(7);
  if(!DisplayQuatro.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Falha no display quatro"));
  }
  DisplayQuatro.clearDisplay();
  DisplayQuatro.setTextColor(WHITE);
  DisplayQuatro.setTextSize(1);
  DisplayQuatro.print("Display quatro");
  DisplayQuatro.display();

 
  Serial.begin(115200);        
  IniciarRedeWifi();               
  IniciarServidorArquivos();              
  IniciarWebSocket();          
  IniciarServidorWeb();             
}

String TrocaPonto(float Valor){
  char buffer[] = "9999.99";
  dtostrf(Valor, 4, 2, buffer);
  char* p  = strchr(buffer, '.');
  *p = ',';
  return buffer;  

}
void loop() {
  DisplayUm.clearDisplay();
  DisplayDois.clearDisplay();
  DisplayTres.clearDisplay();
  DisplayQuatro.clearDisplay();

  WebSocket.loop();                          
  ServidorWeb.handleClient();                    
  WebSocket.broadcastTXT(StatusExperimento);
  // NOVAS VARIÁVEIS
  String TensaoDisplayUm = "TU";
  String CorrenteDisplayUm = "CU";
  String TensaoDisplayDois = "TD";
  String CorrenteDisplayDois = "CD";
  String TensaoDisplayTres = "TT";
  String CorrenteDisplayTres = "CT";
  String TensaoDisplayQuatro = "TQ";
  String CorrenteDisplayQuatro = "CQ";

  float TensaoSensorUm = 0;
  float CorrenteSensorUm = 0;
  
  float TensaoSensorDois = 0;
  float CorrenteSensorDois = 0;

  float TensaoSensorTres = 0;
  float CorrenteSensorTres = 0;

  float TensaoSensorQuatro = 0;
  float CorrenteSensorQuatro = 0;

  // Sensor Um
  SelecionaCanal(0);
  TensaoSensorUm = SensorUm.getBusVoltage_V();
  CorrenteSensorUm = SensorUm.getCurrent_mA();
  CorrenteSensorUm = CorrenteSensorUm / 1000; 
    // Sensor Dois
  SelecionaCanal(1);
  TensaoSensorDois = SensorDois.getBusVoltage_V();
  CorrenteSensorDois = SensorDois.getCurrent_mA();
  CorrenteSensorDois = CorrenteSensorDois / 1000; 
  // Sensor Três
  SelecionaCanal(2);
  TensaoSensorTres = SensorTres.getBusVoltage_V();
  CorrenteSensorTres = SensorTres.getCurrent_mA();
  CorrenteSensorTres = CorrenteSensorTres / 1000; 
  // Sensor Quatro
  SelecionaCanal(3);
  TensaoSensorQuatro = SensorQuatro.getBusVoltage_V();
  CorrenteSensorQuatro = SensorQuatro.getCurrent_mA();
  CorrenteSensorQuatro = CorrenteSensorQuatro / 1000; 
 
 
  TensaoDisplayUm.concat(TensaoSensorUm);
  WebSocket.broadcastTXT(TensaoDisplayUm);
  CorrenteDisplayUm.concat(CorrenteSensorUm);
  WebSocket.broadcastTXT(CorrenteDisplayUm);

  TensaoDisplayDois.concat(TensaoSensorDois);
  WebSocket.broadcastTXT(TensaoDisplayDois);
  CorrenteDisplayDois.concat(CorrenteSensorDois);
  WebSocket.broadcastTXT(CorrenteDisplayDois);

  TensaoDisplayTres.concat(TensaoSensorTres);
  WebSocket.broadcastTXT(TensaoDisplayTres);
  CorrenteDisplayTres.concat(CorrenteSensorTres);
  WebSocket.broadcastTXT(CorrenteDisplayTres);

  TensaoDisplayQuatro.concat(TensaoSensorQuatro);
  WebSocket.broadcastTXT(TensaoDisplayQuatro);
  CorrenteDisplayQuatro.concat(CorrenteSensorQuatro);
  WebSocket.broadcastTXT(CorrenteDisplayQuatro);
  // Display Um
  SelecionaCanal(4);
  DisplayUm.setCursor(0,0);
  DisplayUm.println("MEDIDOR 1");
  DisplayUm.setTextSize(3);
  //DisplayUm.print("U ");
  DisplayUm.print(TrocaPonto(TensaoSensorUm));
  DisplayUm.println("V");
  //DisplayUm.print("I ");
  DisplayUm.print(TrocaPonto(CorrenteSensorUm));
  DisplayUm.print("A");
  DisplayUm.display();
  DisplayUm.setTextSize(2);
  // Display Dois
  SelecionaCanal(5);
  DisplayDois.setCursor(0,0);
  DisplayDois.println("MEDIDOR 2");
  DisplayDois.setTextSize(3);
  //DisplayDois.print("U ");
  DisplayDois.print(TrocaPonto(TensaoSensorDois));
  DisplayDois.println("V");
  //DisplayDois.print("I ");
  DisplayDois.print(TrocaPonto(CorrenteSensorDois));
  DisplayDois.print("A");
  DisplayDois.display();
  DisplayDois.setTextSize(2);
  // Display Três
  SelecionaCanal(6);
  DisplayTres.setCursor(0,0);
  DisplayTres.println("MEDIDOR 3");
  DisplayTres.setTextSize(3);
  //DisplayTres.print("U ");
  DisplayTres.print(TrocaPonto(TensaoSensorTres));
  DisplayTres.println("V");
  //DisplayTres.print("I ");
  DisplayTres.print(TrocaPonto(CorrenteSensorTres));
  DisplayTres.print("A");
  DisplayTres.display();
  DisplayTres.setTextSize(2);
  // Display Quatro
  SelecionaCanal(7);
  DisplayQuatro.setCursor(0,0);
  DisplayQuatro.println("MEDIDOR 4");
  DisplayQuatro.setTextSize(3);
  //DisplayQuatro.print("U ");
  DisplayQuatro.print(TrocaPonto(TensaoSensorQuatro));
  DisplayQuatro.println("V");
  //DisplayQuatro.print("I ");
  DisplayQuatro.print(TrocaPonto(CorrenteSensorQuatro));
  DisplayQuatro.print("A");
  DisplayQuatro.display();
  DisplayQuatro.setTextSize(2);

}

void IniciarRedeWifi() { 
  Serial.println("Conectando à rede Wi-Fi");
  WiFi.begin(NomeRede, SenhaRede);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado a rede " + String(NomeRede));
  Serial.print(" com o endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Para acessar digite http://");
  Serial.print(WiFi.localIP());
  Serial.println("/ no seu navegador web");
 }


void IniciarServidorArquivos() { 
  SPIFFS.begin();                            
  Serial.println("Servidor de arquivos iniciado com o seguinte conteúdo:");
  File Diretorio = SPIFFS.open("/");
  File Arquivos = Diretorio.openNextFile();
  while (Arquivos) {                     
      Serial.printf(" %s - %u bytes\n", Arquivos.name(), Arquivos.size());
      Arquivos = Diretorio.openNextFile();
  }
  Serial.printf("\n");
}

void IniciarWebSocket() {
  WebSocket.begin();                         
  WebSocket.onEvent(EventoWebSocket);        
  Serial.println("Serviço WebSocket iniciado!");
}

void IniciarServidorWeb() { 
 ServidorWeb.on("/index.html",  HTTP_POST, []() {  
    ServidorWeb.send(200, "text/plain", ""); 
 }, GerenciaUploadArquivo);                     

  ServidorWeb.onNotFound(GerenciaArquivoNaoEncontrado);        
                                           
  ServidorWeb.begin();                           
  Serial.println("Servidor Web iniciado!");
}



void GerenciaArquivoNaoEncontrado(){ 
  if(!GerenciaLeituraArquivo(ServidorWeb.uri())){         
    ServidorWeb.send(404, "text/plain", "404: Arquivo não encontrado");
  }
}

bool GerenciaLeituraArquivo(String path) { 
  Serial.println("Leitura: " + path);
  if (path.endsWith("/")) path += "index.html";         
  String contentTipo = getContentTipo(path);            
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) { 
    if (SPIFFS.exists(pathWithGz))                        
      path += ".gz";                                       
    File Arquivos = SPIFFS.open(path, "r");                   
    size_t sent = ServidorWeb.streamFile(Arquivos, contentTipo);   
    Arquivos.close();                                        
    Serial.println(String("\tEnviando arquivo: ") + path);
    return true;
  }
  Serial.println(String("\tArquivo não encontrado: ") + path);   
  return false;
}

void GerenciaUploadArquivo(){ // upload a new file to the SPIFFS
  HTTPUpload& Upload = ServidorWeb.upload();
  String path;
  if(Upload.status == UPLOAD_FILE_START){
    path = Upload.filename;
    if(!path.startsWith("/")) path = "/"+path;
    if(!path.endsWith(".gz")) {                         
      String pathWithGz = path+".gz";                   
      if(SPIFFS.exists(pathWithGz))                    
         SPIFFS.remove(pathWithGz);
    }
    Serial.print("Nome: "); Serial.println(path);
    UploadArquivo = SPIFFS.open(path, "w");           
    path = String();
  } else if(Upload.status == UPLOAD_FILE_WRITE){
    if(UploadArquivo)
      UploadArquivo.write(Upload.buf, Upload.currentSize); 
  } else if(Upload.status == UPLOAD_FILE_END){
    if(UploadArquivo) {                                   
      UploadArquivo.close();                              
      Serial.print("Tamanho: ");
      Serial.println(Upload.totalSize);
      ServidorWeb.sendHeader("Location","/success.html");     
      ServidorWeb.send(303);
    } else {
      ServidorWeb.send(500, "text/plain", "500: couldn't create file");
    }
  }
}

void EventoWebSocket(uint8_t IdUsuario, WStype_t Tipo, uint8_t * MensagemRecebida, size_t TamMensagem) { 
  switch (Tipo) {
    case WStype_DISCONNECTED:            
      Serial.printf("[%u] Desconectado!\n", IdUsuario);
      if (UsuarioAtivo==IdUsuario){
        StatusExperimento = "N";
        ChaveUmStatus = 0;
        ChaveDoisStatus = 0;
        ChaveTresStatus = 0;
        ChaveQuatroStatus = 0;
        ChaveCincoStatus = 0;
        ChaveSeisStatus = 0;
        ChaveSeteStatus = 0;
        ChaveOitoStatus = 0;
        digitalWrite(32, HIGH);
        digitalWrite(33, HIGH);
        digitalWrite(19, HIGH);
        digitalWrite(25, HIGH);
        digitalWrite(14, HIGH);
        digitalWrite(15, HIGH);
        digitalWrite(16, HIGH);
        digitalWrite(17, HIGH);
        }
    break;
    case WStype_CONNECTED: {             
        IPAddress ip = WebSocket.remoteIP(IdUsuario);
        Serial.printf("[%u] Conectado em %d.%d.%d.%d url: %s\n", IdUsuario, ip[0], ip[1], ip[2], ip[3], MensagemRecebida);
     }
      break;
    case WStype_TEXT:                   
      
      Serial.printf("[%u] Texto recebido: %s\n", IdUsuario, MensagemRecebida);
      // Chave 1
      if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '1' && MensagemRecebida[2] =='L') {           
        ChaveUmStatus = 1;
        digitalWrite(32, LOW);
        digitalWrite(23, HIGH);
      }
       if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '1' && MensagemRecebida[2] =='D') {          
         ChaveUmStatus = 0;
         digitalWrite(32, HIGH);
         digitalWrite(23, LOW);
      }
      // Chave 2
      if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '2' && MensagemRecebida[2] =='L') {         
        ChaveDoisStatus = 1;
        digitalWrite(33, LOW);
      }
       if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '2' && MensagemRecebida[2] =='D') {         
         ChaveDoisStatus = 0;
         digitalWrite(33, HIGH);
      }
      // Chave 3
      if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '3' && MensagemRecebida[2] =='L') {            
        ChaveTresStatus = 1;
        digitalWrite(19, LOW);
      }
       if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '3' && MensagemRecebida[2] =='D') {           
         ChaveTresStatus = 0;
         digitalWrite(19, HIGH);
      }
      // Chave 4
      if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '4' && MensagemRecebida[2] =='L') {          
        ChaveQuatroStatus = 1;
        digitalWrite(25, LOW);
      }
       if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '4' && MensagemRecebida[2] =='D') {           
         ChaveQuatroStatus = 0;
         digitalWrite(25, HIGH);
      }
      // Chave 5
      if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '5' && MensagemRecebida[2] =='L') {          
        ChaveCincoStatus = 1;
        digitalWrite(14, LOW);
      }
       if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '5' && MensagemRecebida[2] =='D') {           
         ChaveCincoStatus = 0;
         digitalWrite(14, HIGH);
      }
      // Chave 6
      if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '6' && MensagemRecebida[2] =='L') {          
        ChaveSeisStatus = 1;
        digitalWrite(15, LOW);
      }
       if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '6' && MensagemRecebida[2] =='D') {           
         ChaveSeisStatus = 0;
         digitalWrite(15, HIGH);
      }
      // Chave 7
      if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '7' && MensagemRecebida[2] =='L') {           
        ChaveSeteStatus = 1;
        digitalWrite(16, LOW);
      }
       if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '7' && MensagemRecebida[2] =='D') {           
         ChaveSeteStatus = 0;
         digitalWrite(16, HIGH);
      }
      //Chave 8
      if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '8' && MensagemRecebida[2] =='L') {          
        ChaveOitoStatus = 1;
        digitalWrite(17, LOW);
      }
       if (MensagemRecebida[0] == 'C' && MensagemRecebida[1] == '8' && MensagemRecebida[2] =='D') {            
         ChaveOitoStatus = 0;
         digitalWrite(17, HIGH);
      }
            
      if (MensagemRecebida[0] == 'S') {         
         StatusExperimento = "S";
         UsuarioAtivo = IdUsuario;
      }
       if (MensagemRecebida[0] == 'N') {         
         StatusExperimento = "N";
      }
      break;
  }
}



String formatBytes(size_t bytes) { 
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }
}

String getContentTipo(String filename) { 
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
