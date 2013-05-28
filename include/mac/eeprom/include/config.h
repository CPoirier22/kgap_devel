#ifndef CONFIG_H_
#define CONFIG_H_

#define BOOT_SW_VER_LENGTH 7
#define FLASH_SW_VER_LENGTH 7
#define FLASH_SW_PART_NO_LENGTH 8
#define SYSTEM_ARI_LENGTH 12

typedef char BootSwVersionType [ BOOT_SW_VER_LENGTH ];  /* Not used characters are set to space (ASCII 20H)*/
typedef char FlashSwPartNoType [ FLASH_SW_PART_NO_LENGTH ];  /* Not used char. are set to space (ASCII 20H)*/
typedef char FlashSwVersionType [ FLASH_SW_VER_LENGTH ];  /* Not used characters are set to space (ASCII 20H)*/
typedef char SystemAriType [ SYSTEM_ARI_LENGTH ];
void ReadFlashSwVersion ( FlashSwVersionType FlashSwVersion );
void ReadFlashSwPartNo ( FlashSwPartNoType FlashSwPartNo );
void ReadBootSwVersion ( BootSwVersionType BootSwVersion );
#endif /*CONFIG_H_*/
