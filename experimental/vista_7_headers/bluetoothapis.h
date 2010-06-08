#ifndef _INC_BLUETOOTHAPIS
#define _INC_BLUETOOTHAPIS

#if (_WIN32_WINNT >= 0x0600)

typedef enum AUTHENTICATION_REQUIREMENTS {
  MITMProtectionNotRequired                 = 0x00,
  MITMProtectionRequired                    = 0x01,
  MITMProtectionNotRequiredBonding          = 0x02,
  MITMProtectionRequiredBonding             = 0x03,
  MITMProtectionNotRequiredGeneralBonding   = 0x04,
  MITMProtectionRequiredGeneralBonding      = 0x05,
  MITMProtectionNotDefined                  = 0xff 
} AUTHENTICATION_REQUIREMENTS;

#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_BLUETOOTHAPIS*/
