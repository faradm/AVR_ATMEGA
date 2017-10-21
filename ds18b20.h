#define DS_SKIP_ROM 0xCC
#define DS_CONVERT 0x44
#define DS_WRITE_SCRATCHPAD 0x4E
#define DS_READ_SCRATCHPAD 0xBE
#define DS_COPY_SCRATCHPAD 0x48
#define DS_RECALL_EE 0xB8
#define DS_READ_POWER 0xB4
#include <stdbool.h>
bool ds_init();
//void ds_search_rom();
void ds_skip_rom();
void ds_convert();//NON_PARASITE, NOTE: Only returns after conversion is complete.
void ds_write_scratchpad(uint8_t th_register, uint8_t tl_register, uint8_t configuration_register);
uint8_t* ds_read_scratchpad();
void ds_copy_scratchpad();//NON_PARASITE;
void ds_recall_ee();
bool ds_is_parasite();