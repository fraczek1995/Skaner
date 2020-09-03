// Load Wi-Fi library
#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"
#include "StepperMotor.h"
#include "sdCardFunction.h"

#define steepsPerRotate 200
#define stops 4

int motorCounter = 0;
bool startReadingSd = false;
int counterToStartReadingSd = 1;

bool alarm_w_temp = false;
bool alarm_temp = false;


String kolor[241]= {
"	#0000ff"	,
"	#0004ff"	,
"	#0008ff"	,
"	#000dff"	,
"	#0011ff"	,
"	#0015ff"	,
"	#0019ff"	,
"	#001eff"	,
"	#0022ff"	,
"	#0026ff"	,
"	#002bff"	,
"	#002fff"	,
"	#0033ff"	,
"	#0037ff"	,
"	#003bff"	,
"	#0040ff"	,
"	#0044ff"	,
"	#0048ff"	,
"	#004cff"	,
"	#0051ff"	,
"	#0055ff"	,
"	#0059ff"	,
"	#005eff"	,
"	#0062ff"	,
"	#0066ff"	,
"	#006aff"	,
"	#006eff"	,
"	#0073ff"	,
"	#0077ff"	,
"	#007bff"	,
"	#007fff"	,
"	#0084ff"	,
"	#0088ff"	,
"	#008cff"	,
"	#0091ff"	,
"	#0095ff"	,
"	#0099ff"	,
"	#009dff"	,
"	#00a1ff"	,
"	#00a6ff"	,
"	#00aaff"	,
"	#00aeff"	,
"	#00b2ff"	,
"	#00b7ff"	,
"	#00bbff"	,
"	#00bfff"	,
"	#00c3ff"	,
"	#00c8ff"	,
"	#00ccff"	,
"	#00d0ff"	,
"	#00d4ff"	,
"	#00d9ff"	,
"	#00ddff"	,
"	#00e1ff"	,
"	#00e5ff"	,
"	#00eaff"	,
"	#00eeff"	,
"	#00f2ff"	,
"	#00f6ff"	,
"	#00fbff"	,
"	#00ffff"	,
"	#00fffb"	,
"	#00fff7"	,
"	#00fff2"	,
"	#00ffee"	,
"	#00ffea"	,
"	#00ffe6"	,
"	#00ffe1"	,
"	#00ffdd"	,
"	#00ffd9"	,
"	#00ffd5"	,
"	#00ffd0"	,
"	#00ffcc"	,
"	#00ffc8"	,
"	#00ffc4"	,
"	#00ffbf"	,
"	#00ffbb"	,
"	#00ffb7"	,
"	#00ffb3"	,
"	#00ffae"	,
"	#00ffaa"	,
"	#00ffa6"	,
"	#00ffa2"	,
"	#00ff9d"	,
"	#00ff99"	,
"	#00ff95"	,
"	#00ff91"	,
"	#00ff8c"	,
"	#00ff88"	,
"	#00ff84"	,
"	#00ff80"	,
"	#00ff7b"	,
"	#00ff77"	,
"	#00ff73"	,
"	#00ff6f"	,
"	#00ff6a"	,
"	#00ff66"	,
"	#00ff62"	,
"	#00ff5e"	,
"	#00ff59"	,
"	#00ff55"	,
"	#00ff51"	,
"	#00ff4d"	,
"	#00ff48"	,
"	#00ff44"	,
"	#00ff40"	,
"	#00ff3c"	,
"	#00ff37"	,
"	#00ff33"	,
"	#00ff2f"	,
"	#00ff2b"	,
"	#00ff26"	,
"	#00ff22"	,
"	#00ff1e"	,
"	#00ff19"	,
"	#00ff15"	,
"	#00ff11"	,
"	#00ff0d"	,
"	#00ff09"	,
"	#00ff04"	,
"	#00ff00"	,
"	#04ff00"	,
"	#08ff00"	,
"	#0dff00"	,
"	#11ff00"	,
"	#15ff00"	,
"	#1aff00"	,
"	#1eff00"	,
"	#22ff00"	,
"	#26ff00"	,
"	#2bff00"	,
"	#2fff00"	,
"	#33ff00"	,
"	#37ff00"	,
"	#3bff00"	,
"	#40ff00"	,
"	#44ff00"	,
"	#48ff00"	,
"	#4cff00"	,
"	#51ff00"	,
"	#55ff00"	,
"	#59ff00"	,
"	#5eff00"	,
"	#62ff00"	,
"	#66ff00"	,
"	#6aff00"	,
"	#6eff00"	,
"	#73ff00"	,
"	#77ff00"	,
"	#7bff00"	,
"	#80ff00"	,
"	#84ff00"	,
"	#88ff00"	,
"	#8cff00"	,
"	#91ff00"	,
"	#95ff00"	,
"	#99ff00"	,
"	#9dff00"	,
"	#a1ff00"	,
"	#a6ff00"	,
"	#aaff00"	,
"	#aeff00"	,
"	#b2ff00"	,
"	#b7ff00"	,
"	#bbff00"	,
"	#bfff00"	,
"	#c3ff00"	,
"	#c8ff00"	,
"	#ccff00"	,
"	#d0ff00"	,
"	#d4ff00"	,
"	#d9ff00"	,
"	#ddff00"	,
"	#e1ff00"	,
"	#e6ff00"	,
"	#eaff00"	,
"	#eeff00"	,
"	#f2ff00"	,
"	#f6ff00"	,
"	#fbff00"	,
"	#ffff00"	,
"	#fffb00"	,
"	#fff700"	,
"	#fff200"	,
"	#ffee00"	,
"	#ffea00"	,
"	#ffe500"	,
"	#ffe100"	,
"	#ffdd00"	,
"	#ffd900"	,
"	#ffd500"	,
"	#ffd000"	,
"	#ffcc00"	,
"	#ffc800"	,
"	#ffc300"	,
"	#ffbf00"	,
"	#ffbb00"	,
"	#ffb700"	,
"	#ffb300"	,
"	#ffae00"	,
"	#ffaa00"	,
"	#ffa600"	,
"	#ffa200"	,
"	#ff9d00"	,
"	#ff9900"	,
"	#ff9500"	,
"	#ff9100"	,
"	#ff8c00"	,
"	#ff8800"	,
"	#ff8400"	,
"	#ff8000"	,
"	#ff7b00"	,
"	#ff7700"	,
"	#ff7300"	,
"	#ff6e00"	,
"	#ff6a00"	,
"	#ff6600"	,
"	#ff6200"	,
"	#ff5e00"	,
"	#ff5900"	,
"	#ff5500"	,
"	#ff5100"	,
"	#ff4d00"	,
"	#ff4800"	,
"	#ff4400"	,
"	#ff4000"	,
"	#ff3c00"	,
"	#ff3700"	,
"	#ff3300"	,
"	#ff2f00"	,
"	#ff2b00"	,
"	#ff2600"	,
"	#ff2200"	,
"	#ff1e00"	,
"	#ff1a00"	,
"	#ff1500"	,
"	#ff1100"	,
"	#ff0d00"	,
"	#ff0900"	,
"	#ff0400"	,
"	#ff0000"};




// Replace with your network credentials
const char* ssid     = "HH40V_E516";
const char* password = "80618234";

//const char* ssid     = "telefon";
//const char* password = "12345678";

//const char* ssid     = "HUAWEI-E5373-6753";
//const char* password = "t09njaq3";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;
char linebuf[80];
int charcount=0;



/////////////// CZUJNIK MLX /////////////////////

const byte MLX90640_address = 0x33; //Default 7-bit unshifted address of the MLX90640

#define TA_SHIFT 8 //Default shift for MLX90640 in open air

float mlx90640To[768];
paramsMLX90640 mlx90640;

String obraz [768];
int temp [768];

void setup() {
  motorSetup();
  Serial.begin(115200);
   // Connect to Wi-Fi network with SSID and password
  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
  
  sdSetup(); // karta sd
  
  
  /////////////// czujnik mlx /////////////
  
  Wire.begin();
  Wire.setClock(100000);
  
  if (isConnected() == false)
  {
    Serial.println("MLX90640 not detected at default I2C address. Please check wiring. Freezing.");
    while (1);
  }
  
  //Get device parameters - We only have to do this once
  int status;
  uint16_t eeMLX90640[832];
  status = MLX90640_DumpEE(MLX90640_address, eeMLX90640);
  if (status != 0)
    Serial.println("Failed to load system parameters");

  status = MLX90640_ExtractParameters(eeMLX90640, &mlx90640);
  if (status != 0)
    Serial.println("Parameter extraction failed");

  //Once params are extracted, we can release eeMLX90640 array

  //MLX90640_SetRefreshRate(MLX90640_address, 0x02); //Set rate to 2Hz
  MLX90640_SetRefreshRate(MLX90640_address, 0x03); //Set rate to 4Hz
  //MLX90640_SetRefreshRate(MLX90640_address, 0x07); //Set rate to 64Hz
  
}

void loop() {
  WiFiClient client = server.available();
  
  // listen for incoming clients
  
  if (client) {
    Serial.println("New client");
    memset(linebuf,0,sizeof(linebuf));
    charcount=0;
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        //read char by char HTTP request
        linebuf[charcount]=c;
        if (charcount<sizeof(linebuf)-1) charcount++;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        {
          motorMove(steepsPerRotate/stops);           
          delay(200);
          long startTime = millis();
          
          for (byte x = 0 ; x < 2 ; x++)
          {
            uint16_t mlx90640Frame[834];
            int status = MLX90640_GetFrameData(MLX90640_address, mlx90640Frame);

            float vdd = MLX90640_GetVdd(mlx90640Frame, &mlx90640);
            float Ta = MLX90640_GetTa(mlx90640Frame, &mlx90640);

            float tr = Ta - TA_SHIFT; //Reflected temperature based on the sensor ambient temperature
            float emissivity = 0.95;

            MLX90640_CalculateTo(mlx90640Frame, &mlx90640, emissivity, tr, mlx90640To);
          }
        
          ////////////////////////////////////////////////////////////////         
          // ZBUDOWANIE TABLICY KOLORÓW 
          for (int x = 0 ; x < 768 ; x++)
          {
            temp[x] = (int)mlx90640To[x];
            if (temp[x] < 0) obraz[x] = kolor[0];
            
            else if (temp[x] > 240) obraz[x] = kolor[240];
            
            else obraz[x] = (kolor[(int)mlx90640To[x]]);
            
          }
          
          
          ///////////////////////////////////////////////////////////////
          if (startReadingSd == false && counterToStartReadingSd == (stops+1))
          {
           startReadingSd = true;
          }
          
          File dataFile;
          
          
          ////////////////////////////////////////////////////////////////
          // CZYTANIE PLIKU Z KARTY SD ZAWIERAJACEGO POPRZEDNI POMIAR
          String fileName = "/dane" + String(motorCounter) + ".txt";
          String next;
          int wyniki[768];
          int bufor;
          
          if (startReadingSd == true)
          {
                  
            dataFile = SD.open(fileName, FILE_READ);
            if(dataFile) 
            {
              for (int h=0; h<768; h++)
              {
                next = dataFile.readStringUntil('\n');
                bufor=next.toInt();
                wyniki[h]=bufor;
              }
             dataFile.close();
            }
            else 
            {
              // if the file didn't open, print an error:
              Serial.println("error opening test.txt");
            }
  
          Serial.println("przeczytalem");
          
          ////////////////////////////////////
          // PORÓWNANIE WARTOŚCI POMIARU Z POPRZEDNIM POMIAREM I USTAWIENIE ALARMÓW
          for (int x = 0 ; x < 768 ; x++)
          {
            if (temp[x] >= wyniki[x] +20) alarm_w_temp = true;
            if (temp[x] >= 100) alarm_temp = true;
          }
          
          ///////////////////////////////////          
          }
          
          delay(3);
          // WYSYŁANIE STANDARDOWEGO NAGŁÓWKA HTTP (send a standard http response header)
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<meta charset=\"UTF-8\"/>");
          client.println("</head>");
          client.println("<body>");
          
          if (alarm_w_temp == false && alarm_temp == false)
          {
            client.println("<h1 style=\"color:green;\">Brak zagrożenia pożarowego</h1>");
          }
          
          if (alarm_w_temp == true)
          {
            client.println("<h1 style=\"color:red;\">Alarm: wykryto wzrost temp. >20 st. C od ostatniego pomiaru</h1>");
          }
          
          if (alarm_temp == true)
          {
            client.println("<h1 style=\"color:red;\">Alarm: wykryto obiekt o temp >100 st. C</h1>");
          }
                   
          client.println("<table cellpadding = 0 cellspacing = 0 font size = 1>");
                    
          int nr_px = 0;  //TABLICA KOLORÓW I TEMPERATURY JEST JEDNOWMIAROWA DLATEGO POTRZEBA ZMIENNEJ NR_PX
        
          for (int y=0; y<24; y++)
          {
            client.println("<tr height = 30px>");
            for (int x=1; x<=32; x++)
            {
              client.println("<td width=30px bgcolor="+obraz[nr_px]+">"+temp[nr_px]+"<td/>");
              nr_px++;
            }
            client.println("<tr/>");
           }
     
          client.println("<table/>");
            
                   
          
          //client.println("<input type=\"button\" value=\"Refresh\" onclick=\"history.go(0)\"/>");
          //////////////////////////////////////////
          /// odświeżanie strony - webpage refresh 
          client.println("<script>");
          client.println("window.location.reload(true);");
          client.println("</script>");
          
          client.println("</body></html>");
          
          /////////////////////////////////////////
          // ZAPIS POMIARU NA KARTĘ SD
          dataFile = SD.open(fileName, FILE_WRITE);
          if(!dataFile)
          {
            Serial.println("Failed to open file for writing");
            return;
          }
          for(int x=0; x<768; x++)
          {
            dataFile.println(temp[x]);
          }
          
          dataFile.close();
          Serial.println("File written");

          /////////////////////////////////////////
          alarm_w_temp = false;
          alarm_temp = false;





          delay(3000);
          motorCounter++; 
          if (motorCounter == (stops))
          {
            motorDirChange();
            motorCounter = 0;
            motorMove(steepsPerRotate);
            delay(3000);
            motorDirChange();
          }
          counterToStartReadingSd++;   
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          memset(linebuf,0,sizeof(linebuf));
          charcount=0;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
  
 
  
}




//Returns true if the MLX90640 is detected on the I2C bus
boolean isConnected()
{
  Wire.beginTransmission((uint8_t)MLX90640_address);
  if (Wire.endTransmission() != 0)
    return (false); //Sensor did not ACK
  return (true);
}
