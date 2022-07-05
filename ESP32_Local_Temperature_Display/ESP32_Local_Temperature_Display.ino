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


/*******************************************************************************
* Function Name: http_get
********************************************************************************
*
* Summary:
*  This routine performs an http GET request and returns a String
*
* Parameters:
*  const char* url: HTTP url
*
* Return:
*  String: Empty string on error else payload / response body
*
*******************************************************************************/
String http_get(const char* url) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, url);
  
  // Send HTTP GET request
  int http_response_code = http.GET();
  
  String payload = ""; 
  
  if (http_response_code > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(http_response_code);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(http_response_code);
  }
  // Free resources
  http.end();

  return payload;
}


/*******************************************************************************
* Function Name: turn_digit_on
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
void turn_digit_on(int digit) {
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
* Function Name: turn_digit_off
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
void turn_digit_off(int digit) {
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
* Function Name: seven_segment_display_digit
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
void seven_segment_display_digit(int digit) {
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
* Function Name: seven_segment_display_dash
********************************************************************************
*
* Summary:
*  This routine displays a dash '-' on a 7-segment display
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void seven_segment_display_dash() {
    digitalWrite(SEVEN_SEG_A, LED_OFF);
    digitalWrite(SEVEN_SEG_B, LED_OFF);
    digitalWrite(SEVEN_SEG_C, LED_OFF);
    digitalWrite(SEVEN_SEG_D, LED_OFF);
    digitalWrite(SEVEN_SEG_E, LED_OFF);
    digitalWrite(SEVEN_SEG_F, LED_OFF);
    digitalWrite(SEVEN_SEG_G, LED_ON);
}

/*******************************************************************************
* Function Name: seven_segment_turn_display_off
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
void seven_segment_turn_display_off() {
  digitalWrite(SEVEN_SEG_A, LED_OFF);
  digitalWrite(SEVEN_SEG_B, LED_OFF);
  digitalWrite(SEVEN_SEG_C, LED_OFF);
  digitalWrite(SEVEN_SEG_D, LED_OFF);
  digitalWrite(SEVEN_SEG_E, LED_OFF);
  digitalWrite(SEVEN_SEG_F, LED_OFF);
  digitalWrite(SEVEN_SEG_G, LED_OFF);
}

/*******************************************************************************
* Function Name: seven_segment_set_all_pins_as_output
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
void seven_segment_set_all_pins_as_output() {
  pinMode(SEVEN_SEG_A, OUTPUT);
  pinMode(SEVEN_SEG_B, OUTPUT);
  pinMode(SEVEN_SEG_C, OUTPUT);
  pinMode(SEVEN_SEG_D, OUTPUT);
  pinMode(SEVEN_SEG_E, OUTPUT);
  pinMode(SEVEN_SEG_F, OUTPUT);
  pinMode(SEVEN_SEG_G, OUTPUT);
}

/*******************************************************************************
* Function Name: seven_segment_set_all_pins_as_input
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
void seven_segment_set_all_pins_as_input() {
  pinMode(SEVEN_SEG_A, INPUT);
  pinMode(SEVEN_SEG_B, INPUT);
  pinMode(SEVEN_SEG_C, INPUT);
  pinMode(SEVEN_SEG_D, INPUT);
  pinMode(SEVEN_SEG_E, INPUT);
  pinMode(SEVEN_SEG_F, INPUT);
  pinMode(SEVEN_SEG_G, INPUT);
}

/*******************************************************************************
* Function Name: seven_segment_display_two_numbers
********************************************************************************
*
* Summary:
*  This routine displays two numbers on a 7-segment display with a delay of <delayInMs> between updates
*  example: 
*    seven_segment_display_two_numbers(1, 9, 10)
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
void seven_segment_display_two_numbers(int tens, int units, int delayInMs) {
  // Display tens
  seven_segment_display_digit(tens);
  turn_digit_on(2);
  delay(delayInMs);
  turn_digit_off(2);
  
  // Display units
  seven_segment_display_digit(units);
  turn_digit_on(1);
  delay(delayInMs);
  turn_digit_off(1);
}


void perform_POST() {
  seven_segment_display_digit(8);
  turn_digit_on(1);
  delay(1000);
  turn_digit_off(1);
  turn_digit_on(2);
  delay(1000);
  seven_segment_turn_display_off();
  turn_digit_off(2);
}

/*******************************************************************************
* Function Name: reset_reason_is_wakeup_related
********************************************************************************
*
* Summary:
*  This routine checks the wakeup reason. Returns true if wakeup related, false otherwise
*
* Parameters:
*  None
*
* Return:
*  boolean: true if the reset reason is wakeup related, false otherwise
*
*******************************************************************************/
boolean reset_reason_is_wakeup_related(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0:
      // Fall through
    case ESP_SLEEP_WAKEUP_EXT1:
      // Fall through
    case ESP_SLEEP_WAKEUP_TIMER:
      // Fall through
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      // Fall through
    case ESP_SLEEP_WAKEUP_ULP:
      return true;
    default:
      return false;
  }
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
  
  seven_segment_set_all_pins_as_output();

  pinMode(SEVEN_SEG_DIGIT_1, OUTPUT);
  pinMode(SEVEN_SEG_DIGIT_2, OUTPUT);

  if (reset_reason_is_wakeup_related() == false) {
    Serial.println("Reset reason not wakeup related");
    Serial.println("#### POST - Power On Self Test ####");
    perform_POST();
  }

  turn_digit_on(1);
  seven_segment_display_dash(); // Display a dash while connecting to WiFi
  
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
  
  // 1. Retrieve the current weather
  String response_data = http_get(URL);
  Serial.println(response_data);
  
  // 2. Extract the temperature
  deserializeJson(doc, response_data);
  
  const float temperature = doc["temperature"];
  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  // 3. Display the 2-digit temperature on the 7-segment display
  int iTemperature = (int)round(temperature);
  int tens = (iTemperature / 10);
  int units = (iTemperature % 10);
  
  unsigned long millis_now = millis();
  unsigned long millis_now_plus_30_seconds = millis_now + (30 * 1000);
  
  while(millis() < millis_now_plus_30_seconds) {
    seven_segment_display_two_numbers(tens, units, 1);
  }
  
  while (digitalRead(33)) {
    Serial.println("Motion detected ... ");
    Serial.println("Will enter sleep mode once motion is no longer detected");
    delay(500);
  }

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1); // 1 = High, 0 = Low
  
  Serial.println("Going to sleep now");
  esp_deep_sleep_start();
}

void loop() {
  // Never enters the main loop
}
