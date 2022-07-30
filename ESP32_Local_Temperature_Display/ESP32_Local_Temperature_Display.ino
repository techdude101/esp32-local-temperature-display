/* Header files */
#include <WiFi.h>
#include <HTTPClient.h>

#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#include <math.h> // Math.round

#include "wifi_info.h"
#include "seven_segment_driver.h"
/* End of header files */

/* Constants */
const char* URL = "http://api.weather.com/v3/wx/observations/current?apiKey=e1f10a1e78da46f5b10a1e78da96f525&geocode=54.615%2C-5.861&language=en-US&units=m&format=json";
const char* URL_TO = "http://api.weather.com/v3/wx/observations/current?apiKey=e1f10a1e78da46f5b10a1e78da96f525&geocode=43.653%2C-79.384&units=m&language=en-US&format=json";

/* End of constants */

/* #defines */
#define USE_STATIC_IP FALSE // Change to TRUE for static IP & DNS. Update WiFi_Info.h
/* End of #defines */

/* Global variables */
DynamicJsonDocument g_doc(4096);
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




void perform_power_on_self_test() {
  seven_segment_display_digit(8);
  turn_digit_on(1);
  delay(1000);
  turn_digit_off(1);
  turn_digit_on(2);
  delay(1000);
  seven_segment_turn_display_off();
  turn_digit_off(2);
}

void configure_pins() {
  pinMode(SEVEN_SEG_A, OUTPUT);
  pinMode(SEVEN_SEG_B, OUTPUT);
  pinMode(SEVEN_SEG_C, OUTPUT);
  pinMode(SEVEN_SEG_D, OUTPUT);
  pinMode(SEVEN_SEG_E, OUTPUT);
  pinMode(SEVEN_SEG_F, OUTPUT);
  pinMode(SEVEN_SEG_G, OUTPUT);

  pinMode(SEVEN_SEG_DIGIT_1, OUTPUT);
  pinMode(SEVEN_SEG_DIGIT_2, OUTPUT);
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
boolean reset_reason_is_wakeup_related() {
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
* Function Name: handle_temperature_error
********************************************************************************
*
* Summary:
*  This routine handles a temperature error by displaying the degree symbol on a seven segment display
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void handle_temperature_error() {
    while(true) {
      turn_digit_on(1);
      seven_segment_display_degree_symbol();
      delay(1);
    }
}

/*******************************************************************************
* Function Name: handle_wifi_error
********************************************************************************
*
* Summary:
*  This routine handles a wifi connection error by displaying the degree symbol on a seven segment display
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void handle_wifi_error() {
    while(true) {
      seven_segment_display_two_letters('F', 'i', 1);
      delay(1);
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
  // Variables
  float temperature = -123.4f;
  boolean network_connected = false;
  // Start the serial port
  Serial.begin(115200);
  
  configure_pins();

  if (reset_reason_is_wakeup_related() == false) {
    Serial.println("Reset reason not wakeup related");
    Serial.println("#### POST - Power On Self Test ####");
    perform_power_on_self_test();
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

  int connection_attempt = 0;
  while ((WiFi.status() != WL_CONNECTED) && (connection_attempt < 5)) {
    connection_attempt++;
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  network_connected = (WiFi.status() == WL_CONNECTED);

  if (network_connected == false) {
    handle_wifi_error();
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
  try {
    deserializeJson(g_doc, response_data);
    
    temperature = g_doc["temperature"];
    Serial.print("Temperature: ");
    Serial.println(temperature);
    if (temperature == 0.00f) {
      throw 400;
    }
  } catch (...) {
    handle_temperature_error();
  }
  
  // 3. Display the 2-digit temperature on the 7-segment display
  int i_temperature = (int)round(temperature);
  int tens = (i_temperature / 10);
  int units = (i_temperature % 10);
  
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
