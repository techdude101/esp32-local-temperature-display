/* Header files */
#include <WiFi.h>
#include <HTTPClient.h>

#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#include <math.h> // Math.round

#include "WiFi_Info.h"
/* End of header files */

/* SEVEN-segment Pins
YZ50282IJ1S LED SEVEN-segment display from DVD player (green)

Common Anode (digit pins)

13   12  11  10  9   8  7   6   5     4     3     2   1
g   f   e   d   c   b   a   digit5  digit4  digit3  digit2  digit1  decimal separator


left most separator = 9 & 1
right most separator = 8 & 1
*/

/* Constants */
const int SEVEN_SEG_DIGIT_1 = 21;
const int SEVEN_SEG_DIGIT_2 = 22;

const int SEVEN_SEG_A = 19;
const int SEVEN_SEG_B = 18;
const int SEVEN_SEG_C = 17;
const int SEVEN_SEG_D = 16;
const int SEVEN_SEG_E = 15;
const int SEVEN_SEG_F = 14;
const int SEVEN_SEG_G = 13;

const char* URL = "http://api.weather.com/v3/wx/observations/current?apiKey=e1f10a1e78da46f5b10a1e78da96f525&geocode=54.615%2C-5.861&language=en-US&units=m&format=json";
const char* URL_TO = "http://api.weather.com/v3/wx/observations/current?apiKey=e1f10a1e78da46f5b10a1e78da96f525&geocode=43.653%2C-79.384&units=m&language=en-US&format=json";

/* End of constants */

/* #defines */
/* Change depending on whether common anode or common cathode */
#define LED_ON LOW
#define LED_OFF HIGH

#define USE_STATIC_IP FALSE // Change to TRUE for static IP & DNS. Update WiFi_Info.h
/* End of #defines */

/* Global variables */
DynamicJsonDocument doc(4096);
/* End of global variables */


String httpGETRequest(const char* url) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, url);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}


/*******************************************************************************
* Function Name: TurnDigitOn
********************************************************************************
*
* Summary:
*  This routine provides power to a single digit in a 7-segment display
*
* Parameters:
*  int digit number: (1 - 5)
*
* Return:
*  None
*
*******************************************************************************/
void TurnDigitOn(int digit) {
  if (digit <= 0) return;
  if (digit > 2) return;
  switch (digit) {
    case 1:
      digitalWrite(SEVEN_SEG_DIGIT_1, LED_OFF);
      break;
    case 2:
      digitalWrite(SEVEN_SEG_DIGIT_2, LED_OFF);
      break;
  }
}

/*******************************************************************************
* Function Name: TurnDigitOff
********************************************************************************
*
* Summary:
*  This routine removes power from a single digit in a 7-segment display
*
* Parameters:
*  int digit number: (1 - 5)
*
* Return:
*  None
*
*******************************************************************************/
void TurnDigitOff(int digit) {
  if (digit <= 0) return;
  if (digit > 2) return;
  switch (digit) {
    case 1:
      digitalWrite(SEVEN_SEG_DIGIT_1, LED_ON);
      break;
    case 2:
      digitalWrite(SEVEN_SEG_DIGIT_2, LED_ON);
      break;
  }
}

/*******************************************************************************
* Function Name: SEVENSegmentDisplayDigit
********************************************************************************
*
* Summary:
*  This routine displays a number (digit) on a 7-segment display
*
* Parameters:
*  int digit: number (0 - 9)
*
* Return:
*  None
*
*******************************************************************************/
void SEVENSegmentDisplayDigit(int digit) {
  switch (digit) {
    case 0:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
    case 1:
      digitalWrite(SEVEN_SEG_A, LED_OFF);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_OFF);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
    case 2:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_OFF);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_OFF);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 3:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_OFF);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 4:
      digitalWrite(SEVEN_SEG_A, LED_OFF);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 5:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_OFF);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 6:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_OFF);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 7:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_OFF);
      digitalWrite(SEVEN_SEG_G, LED_OFF);
      break;
    case 8:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_ON);
      digitalWrite(SEVEN_SEG_E, LED_ON);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
    case 9:
      digitalWrite(SEVEN_SEG_A, LED_ON);
      digitalWrite(SEVEN_SEG_B, LED_ON);
      digitalWrite(SEVEN_SEG_C, LED_ON);
      digitalWrite(SEVEN_SEG_D, LED_OFF);
      digitalWrite(SEVEN_SEG_E, LED_OFF);
      digitalWrite(SEVEN_SEG_F, LED_ON);
      digitalWrite(SEVEN_SEG_G, LED_ON);
      break;
  }
}


/*******************************************************************************
* Function Name: SEVENSegmentDisplayOff
********************************************************************************
*
* Summary:
*  This routine turns all segments off in a 7-segment display 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SEVENSegmentDisplayOff() {
//  SEVENSegmentSetAllPinsAsInput();
  digitalWrite(SEVEN_SEG_A, LED_OFF);
  digitalWrite(SEVEN_SEG_B, LED_OFF);
  digitalWrite(SEVEN_SEG_C, LED_OFF);
  digitalWrite(SEVEN_SEG_D, LED_OFF);
  digitalWrite(SEVEN_SEG_E, LED_OFF);
  digitalWrite(SEVEN_SEG_F, LED_OFF);
  digitalWrite(SEVEN_SEG_G, LED_OFF);
}

/*******************************************************************************
* Function Name: SEVENSegmentSetAllPinsAsOutput
********************************************************************************
*
* Summary:
*  This routine sets all pins used for the 7-segment display as outputs
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SEVENSegmentSetAllPinsAsOutput() {
  pinMode(SEVEN_SEG_A, OUTPUT);
  pinMode(SEVEN_SEG_B, OUTPUT);
  pinMode(SEVEN_SEG_C, OUTPUT);
  pinMode(SEVEN_SEG_D, OUTPUT);
  pinMode(SEVEN_SEG_E, OUTPUT);
  pinMode(SEVEN_SEG_F, OUTPUT);
  pinMode(SEVEN_SEG_G, OUTPUT);
}

/*******************************************************************************
* Function Name: SEVENSegmentSetAllPinsAsInput
********************************************************************************
*
* Summary:
*  This routine sets all pins used for the 7-segment display as inputs
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SEVENSegmentSetAllPinsAsInput() {
  pinMode(SEVEN_SEG_A, INPUT);
  pinMode(SEVEN_SEG_B, INPUT);
  pinMode(SEVEN_SEG_C, INPUT);
  pinMode(SEVEN_SEG_D, INPUT);
  pinMode(SEVEN_SEG_E, INPUT);
  pinMode(SEVEN_SEG_F, INPUT);
  pinMode(SEVEN_SEG_G, INPUT);
}

/*******************************************************************************
* Function Name: displayTwoNumbers
********************************************************************************
*
* Summary:
*  This routine displays two numbers on a 7-segment display with a delay of <delayInMs> between updates
*  example: 
*    displayTwoNumbers(1, 9, 10)
*    Displays 19 on the 7-segment display
*     - display 1 for 10 milliseconds on digit 2
*     - display 9 for 10 milliseconds on digit 1
* Parameters:
*  int tens: Tens
*  int units: Units
*  int delayInMs: Delay in milliseconds
*
* Return:
*  None
*
*******************************************************************************/
void displayTwoNumbers(int tens, int units, int delayInMs) {
  // Display tens
  SEVENSegmentDisplayDigit(tens);
  TurnDigitOn(2);
  delay(delayInMs);
  TurnDigitOff(2);
  
  // Display units
  SEVENSegmentDisplayDigit(units);
  TurnDigitOn(1);
  delay(delayInMs);
  TurnDigitOff(1);
}

/*******************************************************************************
* Function Name: setup
********************************************************************************
*
* Summary:
*  This routine is the builtin Arduino setup routine. Initialize hardware in this routine
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void setup() {
  // Start the serial port
  Serial.begin(115200);
  
  SEVENSegmentSetAllPinsAsOutput();

  pinMode(SEVEN_SEG_DIGIT_1, OUTPUT);
  pinMode(SEVEN_SEG_DIGIT_2, OUTPUT);

  // Turn on all segments on by displaying the number 8
  TurnDigitOn(1);
  SEVENSegmentDisplayDigit(8);

  // Configure WiFi and connect to the network
  #if USE_STATIC_IP == TRUE
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure with static IP");
  }
  #endif

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("ESP Mac Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());
  delay(1000);
  
  TurnDigitOff(1);
  TurnDigitOn(2);
  delay(1000);
  SEVENSegmentDisplayOff();
  TurnDigitOff(2);
  delay(1000);

//  String responseData = httpGETRequest(URL);
//  Serial.println(responseData);

//  DynamicJsonDocument doc(4096);
//  deserializeJson(doc, responseData);
//  
//  const float temperature = doc["temperature"];
//  Serial.print("Temperature: ");
//  Serial.println(temperature);
}

void loop() {
  // 1. Retrieve the current weather
  String responseData = httpGETRequest(URL_TO);
  Serial.println(responseData);
  
  // 2. Extract the temperature
  deserializeJson(doc, responseData);
  
  const float temperature = doc["temperature"];
  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  // 3. Display the 2-digit temperature on the 7-segment display
  int iTemperature = (int)round(temperature);
  int tens = (iTemperature / 10);
  int units = (iTemperature % 10);
  
  while(1) {
    displayTwoNumbers(tens, units, 1);
  }
}
