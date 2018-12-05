#ifndef _SD_H_
#define _SD_H_
  //includes
  #include <dirent.h>
  #include <string.h>
  #include "esp_log.h"
  #include "sdmmc_cmd.h"
  #include "sdkconfig.h"
  #include "esp_err.h"
  #include "esp_log.h"
  #include "esp_vfs_fat.h"
  #include "driver/sdmmc_host.h"
  #include "driver/sdspi_host.h"
  #include "../functions/functions.h"

  //defines
  #define TAG "sd"
  #define MAX_LENGTH_FILE_NAMES CONFIG_FATFS_MAX_LFN
  #define USE_SPI_MODE

  // When testing SD and SPI modes, keep in mind that once the card has been
  // initialized in SPI mode, it can not be reinitialized in SD mode without
  // toggling power to the card.

  #ifdef USE_SPI_MODE
  // Pin mapping when using SPI mode.
  // With this mapping, SD card can be used both in SPI and 1-line SD mode.
  // Note that a pull-up on CS line is required in SD mode.
  #define PIN_NUM_MISO 2
  #define PIN_NUM_MOSI 15
  #define PIN_NUM_CLK  14
  #define PIN_NUM_CS   13
  #endif //USE_SPI_MODE

  //functions
  void initSD();
  void printDirNames(char dirNameInput[]);
  // char  **getDirNames(char  dirNameInput[]);
  char  *getDirName(char  dirNameInput[], int input);
  int  getDirSize(char dirNameInput[]);
  char *getFileLine(char fileName[], int index);
  char *getFileAsStr(char *filename);
  int getAmountOfLines(char fileName[]);
  int getFileSize(char *filename);
  int getLineSize(char *filename, int lineNO);//lineNO = line number
  fpos_t getPosOfLine(char *filename, int lineNO);
  // int getLineSizeAtPos(char *filename, fpos_t pos);
#endif
