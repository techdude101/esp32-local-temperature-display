/* Header files */
#include <HTTPClient.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#include <ESPmDNS.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <ArduinoJson.h>

#include <math.h> // Math.round

// #include "wifi_info.h"
#include "wifi_config.h"
#include "seven_segment_driver.h"
/* End of header files */

/* Constants */
// const char *URL = "http://api.weather.com/v3/wx/observations/current?apiKey=e1f10a1e78da46f5b10a1e78da96f525&geocode=54.615%2C-5.861&language=en-US&units=m&format=json";
// const char *URL_TO = "http://api.weather.com/v3/wx/observations/current?apiKey=e1f10a1e78da46f5b10a1e78da96f525&geocode=43.653%2C-79.384&units=m&language=en-US&format=json";

const char *SOFT_AP_SSID = "ESP32";
const char *SOFT_AP_PSK = "12345678"; // Must be 8 characters or more

/* End of constants */

/* #defines */
#define USE_STATIC_IP FALSE // Change to TRUE for static IP & DNS. Update WiFi_Info.h
#define MOTION_SENSOR_PIN 33

#include "HTMLForm.h" // HTML Form
#include "wifi_config.h"
/* End of #defines */

/* Global variables */
DynamicJsonDocument g_doc(4096);
AsyncWebServer server(80);

char ssid[32] = "";
char password[63] = "";
char g_url[255] = "";
volatile boolean g_is_wifi_configured = false;
volatile boolean g_is_wifi_client_connected = false;
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
String http_get(const char *url)
{
  WiFiClient client;
  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(client, url);

  // Send HTTP GET request
  int http_response_code = http.GET();

  String payload = "";

  if (http_response_code > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(http_response_code);
    payload = http.getString();
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(http_response_code);
  }
  // Free resources
  http.end();

  return payload;
}

void perform_power_on_self_test()
{
  seven_segment_display_digit(8);
  turn_digit_on(1);
  delay(1000);
  turn_digit_off(1);
  turn_digit_on(2);
  delay(1000);
  seven_segment_turn_display_off();
  turn_digit_off(2);
}

void configure_pins()
{
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
boolean reset_reason_is_wakeup_related()
{
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
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
void handle_temperature_error()
{
  while (true)
  {
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
void handle_wifi_error()
{
  while (true)
  {
    seven_segment_display_two_letters('F', 'i', 1);
    delay(1);
  }
}

void WiFiEvent(WiFiEvent_t event)
{
  Serial.printf("[WiFi-event] event: %d\n", event);

  switch (event)
  {
  case SYSTEM_EVENT_WIFI_READY:
    // Serial.println("WiFi interface ready");
    break;
  case SYSTEM_EVENT_SCAN_DONE:
    // Serial.println("Completed scan for access points");
    break;
  case SYSTEM_EVENT_STA_START:
    // Serial.println("WiFi client started");
    break;
  case SYSTEM_EVENT_STA_STOP:
    // Serial.println("WiFi clients stopped");
    break;
  case SYSTEM_EVENT_STA_CONNECTED:
    // Serial.println("Connected to access point");
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:
    // Serial.println("Disconnected from WiFi access point");
    // WiFi.begin(ssid, password);
    break;
  case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
    // Serial.println("Authentication mode of access point has changed");
    break;
  case SYSTEM_EVENT_STA_GOT_IP:
    // Serial.print("Obtained IP address: ");
    // Serial.println(WiFi.localIP());
    break;
  case SYSTEM_EVENT_STA_LOST_IP:
    // Serial.println("Lost IP address and IP address is reset to 0");
    break;
  case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
    // Serial.println("WiFi Protected Setup (WPS): succeeded in enrollee mode");
    break;
  case SYSTEM_EVENT_STA_WPS_ER_FAILED:
    // Serial.println("WiFi Protected Setup (WPS): failed in enrollee mode");
    break;
  case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
    // Serial.println("WiFi Protected Setup (WPS): timeout in enrollee mode");
    break;
  case SYSTEM_EVENT_STA_WPS_ER_PIN:
    // Serial.println("WiFi Protected Setup (WPS): pin code in enrollee mode");
    break;
  case SYSTEM_EVENT_AP_START:
    // Serial.println("WiFi access point started");
    break;
  case SYSTEM_EVENT_AP_STOP:
    // Serial.println("WiFi access point  stopped");
    break;
  case SYSTEM_EVENT_AP_STACONNECTED:
    // Serial.println("Client connected");
    // Set the flag when a client connects
    g_is_wifi_client_connected = true;
    break;
  case SYSTEM_EVENT_AP_STADISCONNECTED:
    // Serial.println("Client disconnected");
    // Remove the flag when a client disconnects
    g_is_wifi_client_connected = false;
    break;
  case SYSTEM_EVENT_AP_STAIPASSIGNED:
    // Serial.println("Assigned IP address to client");
    break;
  case SYSTEM_EVENT_AP_PROBEREQRECVED:
    // Serial.println("Received probe request");
    break;
  case SYSTEM_EVENT_GOT_IP6:
    // Serial.println("IPv6 is preferred");
    break;
  case SYSTEM_EVENT_ETH_START:
    // Serial.println("Ethernet started");
    break;
  case SYSTEM_EVENT_ETH_STOP:
    // Serial.println("Ethernet stopped");
    break;
  case SYSTEM_EVENT_ETH_CONNECTED:
    // Serial.println("Ethernet connected");
    break;
  case SYSTEM_EVENT_ETH_DISCONNECTED:
    // Serial.println("Ethernet disconnected");
    break;
  case SYSTEM_EVENT_ETH_GOT_IP:
    // Serial.println("Obtained IP address");
    break;
  default:
    break;
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
void setup()
{
  // Scenario 1 - firt power on (no WiFi config stored in EEPROM)
  // Start the softAP & restart when configuration is set

  // Scenario 2 - batteries changed (WiFi config stored in EEPROM)
  // Start the softAP for 1 minute to allow a device to connect and change config
  // If a device connects stop the timer
  // If the 1 minute timer elapses connect to the WiFi network

  // Scenario 3 - Device restarts to apply WiFi config
  // Connect to the WiFi network

  // Variables
  float temperature = -123.4f;
  boolean network_connected = false;
  boolean init_soft_ap = false;

  // Start the serial port
  Serial.begin(115200);
  delay(10);

  WiFi.onEvent(WiFiEvent);

  configure_pins();

  if (reset_reason_is_wakeup_related() == false)
  {
    Serial.println("Reset reason not wakeup related");
    Serial.println("#### POST - Power On Self Test ####");
    perform_power_on_self_test();
  }

  // Get the reset reason
  esp_reset_reason_t reset_reason = esp_reset_reason();
  if (reset_reason == ESP_RST_POWERON)
  {
    Serial.println("Power on");
    init_soft_ap = true;
  }

  turn_digit_on(1);
  seven_segment_display_dash(); // Display a dash while connecting to WiFi

  g_is_wifi_configured = get_wifi_credentials_from_eeprom(ssid, password);
  get_url_from_eeprom(g_url);
  Serial.print("URL from EEPROM: ");
  Serial.println(g_url);

  if ((g_is_wifi_configured) && (init_soft_ap == false))
  {
    // Connect to WiFi
    WiFi.begin(ssid, password);

    int connection_attempt = 0;
    while ((WiFi.status() != WL_CONNECTED) && (connection_attempt < 5))
    {
      connection_attempt++;
      delay(1000);
      Serial.println("Connecting to WiFi..");
      Serial.printf("SSID: %s, PSK: %s\n", ssid, password);
    }
    network_connected = (WiFi.status() == WL_CONNECTED);

    if (network_connected == false)
    {
      handle_wifi_error();
    }

    // 1. Retrieve the current weather
    // String response_data = http_get(URL);
    String response_data = http_get(g_url);
    Serial.println(response_data);

    // 2. Extract the temperature
    try
    {
      deserializeJson(g_doc, response_data);

      temperature = g_doc["temperature"];
      Serial.print("Temperature: ");
      Serial.println(temperature);
      if (temperature == 0.00f)
      {
        throw 400;
      }
    }
    catch (...)
    {
      handle_temperature_error();
    }

    // 3. Display the 2-digit temperature on the 7-segment display e.g. 20°C (no decimals)
    int i_temperature = (int)round(temperature); // Round to the nearest whole number (20.5 -> 21, 20.4 -> 20)
    int tens = (i_temperature / 10);
    int units = (i_temperature % 10);

    unsigned long millis_now = millis();
    unsigned long millis_now_plus_30_seconds = millis_now + (30 * 1000);

    while (millis() < millis_now_plus_30_seconds)
    {
      seven_segment_display_two_numbers(tens, units, 1);
    }

    while (digitalRead(MOTION_SENSOR_PIN))
    {
      Serial.println("Motion detected ... ");
      Serial.println("Will enter sleep mode once motion is no longer detected");
      delay(500);
    }

    // Enable wakeup on the pin the motion sensor is connected to
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1); // 1 = High, 0 = Low

    Serial.println("Going to sleep now");
    esp_deep_sleep_start();
  }

  if (network_connected == false)
  {
    Serial.println("Configuring access point...");

    bool softap_config_result = WiFi.softAP(SOFT_AP_SSID, SOFT_AP_PSK);
    Serial.print("Soft AP Config Result: ");
    Serial.println(softap_config_result);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    Serial.println("Server started");

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/html", htmlForm); });

    server.on("/config", HTTP_POST, [](AsyncWebServerRequest *request)
              {
      int params = request->params();
      for (int i = 0; i < params; i++)
      {
        AsyncWebParameter* p = request->getParam(i);
        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        if ((p->name() == "input-name") && p->value().length() > 3) {
          Serial.println("Setting ESSID");
          strcpy(ssid, p->value().c_str());
          Serial.println(ssid);
        }
        if ((p->name() == "input-password") && (p->value().length() > 3)) {
          Serial.println("Setting PSK");
          strcpy(password, p->value().c_str());
          Serial.println(password);
        }
        if ((p->name() == "input-url") && (p->value().length() > 3)) {
          Serial.println("Setting URL");
          strcpy(g_url, p->value().c_str());
          Serial.println(g_url);
        }
      }
      
      save_wifi_credentials_to_eeprom(ssid, password, 0, 96);
      save_url_to_eeprom(g_url);
      request->send(200, "text/html", "<h1>Restarting to apply settings</h1>");
      ESP.restart(); });

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(404, "text/html", "<h1>404 Page Not Found</h1>"); });

    // Configure mDNS
    boolean dns_configuration_result = MDNS.begin("esp32");

    if (!dns_configuration_result)
    {
      Serial.println("Error setting up MDNS responder!");
    }
    else
    {
      Serial.println("mDNS responder started");
    }

    server.begin(); // Actually start the server
    Serial.println("HTTP server started");
  }
  else
  {
    Serial.println("Connected");
    Serial.println(WiFi.localIP());
  }

  delay(1000); // TODO: Delay needed here?
}

void loop()
{
  unsigned long millis_now = millis();
  unsigned long millis_now_plus_60_seconds = millis_now + (60 * 1000);

  while (millis() < millis_now_plus_60_seconds)
  {
    if (g_is_wifi_client_connected)
    {
      break;
    }
    delay(1);
  }

  if ((g_is_wifi_client_connected == false) && g_is_wifi_configured)
  {
    Serial.println("Restart");
    ESP.restart();
  }
}
