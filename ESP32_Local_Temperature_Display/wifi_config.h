#ifndef _WIFI_CONFIG
#define _WIFI_CONFIG

#include <stdbool.h>

#define SSID_LENGTH 32
#define PSK_OFFSET 32
#define PSK_LENGTH 63
#define URL_MAX_LENGTH 255
#define CONFIG_FLAG_LENGTH 1

#define PSK_OFFSET (SSID_LENGTH)
#define CONFIG_FLAG_OFFSET (SSID_LENGTH + PSK_LENGTH + 1)
#define WIFI_CONFIG_OFFSET (CONFIG_FLAG_OFFSET + 1)

#define EEPROM_SIZE (SSID_LENGTH + PSK_LENGTH + CONFIG_FLAG_LENGTH + URL_MAX_LENGTH + 1) // 1 extra byte for safety

void get_wifi_ssid_from_eeprom(char* ssid);

void get_wifi_psk_from_eeprom(char* password);

bool get_wifi_credentials_from_eeprom(char* ssid, char* password);

int save_wifi_credentials_to_eeprom(char* ssid, char* password, int start_address, int end_address);

int save_url_to_eeprom(char* url);
void get_url_from_eeprom(char* url);

#endif