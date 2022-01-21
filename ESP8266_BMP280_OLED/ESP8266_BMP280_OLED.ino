
 /***************************************************************************
This is a library for the BMP280 humidity, temperature & pressure sensor
 
Designed specifically to work with the Adafruit BMEP280 Breakout 
----> http://www.adafruit.com/products/2651
 
These sensors use I2C or SPI to communicate, 2 or 4 pins are required 
to interface.
 
Adafruit invests time and resources providing this open source code,
please support Adafruit andopen-source hardware by purchasing products
from Adafruit!
 
Written by Limor Fried & Kevin Townsend for Adafruit Industries. 
BSD license, all text above must be included in any redistribution
***************************************************************************/
 #define __DEBUG__ //directiva del preprocesador para controlar modo DEBUG
 
 #include <Wire.h>
 #include <Adafruit_Sensor.h>
 #include <Adafruit_BMP280.h>
 #include <Adafruit_GFX.h>
 #include <Adafruit_SSD1306.h>

// Definir constantes OLED
#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 64 // alto pantalla OLED

// Objeto de la clase Adafruit_SSD1306
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

//Objeto de la clase Adafruti_BMP280
Adafruit_BMP280 bme; // I2C

void setup() {

#ifdef __DEBUG__
  Serial.begin(9600);
  delay(100);
  Serial.println("Iniciando pantalla OLED");
#endif

  // Iniciar pantalla OLED en la dirección 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
#ifdef __DEBUG__
    Serial.println("No se encuentra la pantalla OLED");
#endif
    while (true);
  }

  // Limpiar buffer
  display.clearDisplay();

  // Tamaño del texto
  display.setTextSize(2);
  // Color del texto
  display.setTextColor(SSD1306_WHITE);
  // Posición del texto
  display.setCursor(0, 0);
  // Escribir texto
  display.println("METEO");
  display.println("BMP280");

  // Enviar a pantalla
  display.display();


  
//Serial.begin(9600);
 Serial.println(F("BMP280 test"));
 
if (!bme.begin(0x76)) { 
Serial.println("Could not find a valid BMP280 sensor, check wiring!");
while (1);
}


delay(5000);

}
 
void loop() {
  // variables meteo
  float temp = bme.readTemperature();
  float pres = bme.readPressure()/100;
  float alt  = bme.readAltitude(1013.25);// this should be adjusted to your local forcase
  
  //Puerto Serie
  Serial.print("Temperatura = ");
  Serial.print(temp);
  Serial.println(" ºC");
  Serial.print("Pressure = ");
  Serial.print(pres);
  Serial.println(" hPa");
  Serial.print("Approx altitude = ");
  Serial.print(alt);
  Serial.println(" m");
  Serial.println();

 //OLED 
  // Limpiar buffer OLED
  display.clearDisplay();
  //colocar el cursor al inicio de la pantalla
  //x (0-128 cols), y (0-64, cada pg 8 bits)
  display.setCursor(0, 0); 
  // Escribir texto
  display.println("Meteo JaS");
  display.println(String (String(temp) + " C"));
  display.println(String (String (pres) + " hPa"));
  display.println(String (String(alt) + " m"));
  // Enviar a pantalla
  display.display();

delay(2000); // 2 s entre medidas consecutivas
}
