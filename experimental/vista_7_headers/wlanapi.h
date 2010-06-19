#ifndef _INC_WLANAPI
#define _INC_WLANAPI

typedef struct _DOT11_NETWORK {
  DOT11_SSID     dot11Ssid;
  DOT11_BSS_TYPE dot11BssType;
} DOT11_NETWORK, *PDOT11_NETWORK;

typedef enum _DOT11_RADIO_STATE {
  dot11_radio_state_unknown,
  dot11_radio_state_on,
  dot11_radio_state_off 
} DOT11_RADIO_STATE, *PDOT11_RADIO_STATE;

#if (_WIN32_WINNT >= 0x0600)
typedef struct _DOT11_NETWORK_LIST {
  DWORD         dwNumberOfItems;
  DWORD         dwIndex;
  DOT11_NETWORK Network[1];
} DOT11_NETWORK_LIST, *PDOT11_NETWORK_LIST;
#endif /*(_WIN32_WINNT >= 0x0600)*/

#endif /*_INC_WLANAPI*/
