#include "sd.h"

void initSD()
{
  ESP_LOGI(TAG, "Using SPI peripheral");

  sdmmc_host_t host = SDSPI_HOST_DEFAULT();
  sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
  slot_config.gpio_miso = PIN_NUM_MISO;
  slot_config.gpio_mosi = PIN_NUM_MOSI;
  slot_config.gpio_sck  = PIN_NUM_CLK;
  slot_config.gpio_cs   = PIN_NUM_CS;
  // This initializes the slot without card detect (CD) and write protect (WP) signals.
  // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.

  esp_vfs_fat_sdmmc_mount_config_t mount_config =
  {
      .format_if_mount_failed = true,
      .max_files = 25
  };

  // Use settings defined above to initialize SD card and mount FAT filesystem.
  // Note: esp_vfs_fat_sdmmc_mount is an all-in-one convenience function.
  // Please check its source code and implement error recovery when developing
  // production applications.
  sdmmc_card_t* card;
  esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

  if (ret != ESP_OK) {
      if (ret == ESP_FAIL) {
          ESP_LOGE(TAG, "Failed to mount filesystem. "
              "If you want the card to be formatted, set format_if_mount_failed = true.");
      } else {
          ESP_LOGE(TAG, "Failed to initialize the card (%d). "
              "Make sure SD card lines have pull-up resistors in place.", ret);
      }
      return;
  }

  // Card has been initialized, print its properties
  sdmmc_card_print_info(stdout, card);
  printDirNames("sdcard");
}


void printDirNames(char  dirNameInput[])
{
  struct dirent *pDirent;
  DIR *pDir;
  size_t size = strlen(dirNameInput);
  char dirName[(size + 1)*sizeof(char)];
  strcpy(dirName,"/");
  strcat(dirName,dirNameInput);
  pDir = opendir (dirName);

  if (pDir == NULL)
  {
      ESP_LOGI("sd","Cannot open directory");
  }
  else
  {
    while ((pDirent = readdir(pDir)) != NULL)
    {
        ESP_LOGI("sd","[%s]", pDirent->d_name);
    }
  }
  closedir (pDir);
}

char *getDirName(char  dirNameInput[], int index)
{
  struct dirent *pDirent;
  DIR *pDir;
  size_t size = strlen(dirNameInput);
  char dirName[(size + 1)*sizeof(char)];
  strcpy(dirName,"/");
  strcat(dirName,dirNameInput);
  pDir = opendir (dirName);
  char *name = malloc(MAX_LENGTH_FILE_NAMES * sizeof(char));
  if (pDir == NULL)
  {
      ESP_LOGI("sd","Cannot open directory");
  }
  else
  {
    int counter = 0;
    while ((pDirent = readdir(pDir)) != NULL)
    {
        if (counter == index)
        {
           strcpy(name, pDirent->d_name);
           break;
        }
        ++counter;
    }
  }
  closedir (pDir);
  return name;
}

int getDirSize(char  dirNameInput[])
{
  size_t size = strlen(dirNameInput);
  struct dirent *pDirent;
  DIR *pDir;
  char dirName[(size + 1)*sizeof(char)];
  strcpy(dirName,"/");
  strcat(dirName,dirNameInput);
  pDir = opendir (dirName);
  int counter = 0;
  if (pDir == NULL)
  {
      ESP_LOGI("sd","Cannot open directory");

      return 0;
  }
  else
  {
    //get size

    while ((pDirent = readdir(pDir)) != NULL)
    {
      ++counter;
    }
  }
  closedir (pDir);
  return --counter;
}

char *getFileLine(char fileName[], int index)
{
  fpos_t pos = getPosOfLine(fileName, index);
  int size = getLineSize(fileName, index);
  char *line = malloc(sizeof(char) * size);
  FILE *f = fopen(fileName, "r");
  if (f == NULL)
  {
      ESP_LOGE(TAG, "Failed to open file for reading");
      return "403";
  }
  else
  {
    fsetpos(f, &pos);
    fgets(line, size, f);
  }
  fclose(f);
  return line;
}

fpos_t getPosOfLine(char *filename, int lineNO)
{
  int c,lineSize,lineCounter;
  fpos_t pos = 0;
  c = 0;
  lineCounter = 0;
  lineSize = 0;
  FILE *f = fopen(filename, "r");
  bool EOL = false;
  if (f == NULL)
  {
      ESP_LOGE(TAG, "Failed to open file for reading");
      return 0;
  }
  else
  {
    while(c >= 0 && EOL == false)
    {
      if(lineCounter<lineNO) //loop trough file till system is @ the right line
      {
        while(1)
        {
          c = fgetc(f);
          if(c == 0x0D || c == -1)
          {
            lineCounter++;
            fgetc(f);
            break;
          }
        }
      }
      else // if it's the right line then count the length
      {
        fgetpos(f, &pos);
        fclose(f);
        return pos;
      }
    }
  }
  fclose(f);
  return pos;
}

char *getFileAsStr(char *filename)
{
  char *fileStr = malloc(sizeof(char) * getFileSize(filename));
  int amountOfLines = getAmountOfLines(filename);
  strcpy(fileStr, "");
  for (size_t i = 0; i <= amountOfLines; i++)
  {
    strcat(fileStr,getFileLine(filename,i));
  }
  return fileStr;
}

int getAmountOfLines(char fileName[])
{
  char c = 0;
  #define TAG "file"
  FILE *f = fopen(fileName, "r");

  if (f == NULL)
  {
      ESP_LOGE(TAG, "Failed to open file for reading");
      return "403";
  }
  else
  {
    int counter = 0;

    while (!feof(f))
    {
      c = fgetc(f);
      if(c =='\n')
      {
        ++counter;
      }
    }
    fclose(f);
    return counter;
  }

}

int getFileSize(char *filename)
{
  int totalSize = 0;
  int amountOfLines = getAmountOfLines(filename);
  int line = 0;
  while (line < amountOfLines - 1)
  {
      totalSize += getLineSize(filename, line);
      line++;
  }
  return totalSize;
}

int getLineSize(char *filename, int lineNO)
{
  int c,lineSize,lineCounter;
  c = 0;
  lineCounter = 0;
  lineSize = 0;
  FILE *f = fopen(filename, "r");
  bool EOL = false;
  if (f == NULL)
  {
      ESP_LOGE(TAG, "Failed to open file for reading");
      return 0;
  }
  else
  {
    while(c >= 0 && EOL == false)
    {
      if(lineCounter<lineNO) //loop trough file till system is @ the right line
      {
        while(1)
        {
          c = fgetc(f);
          if(c == 0x0D || c == -1)
          {
            lineCounter++;
            fgetc(f);
            break;
          }
        }
      }
      else // if it's the right line then count the length
      {
        while(c >= 0 && EOL == false)
        {
          c = fgetc(f);
          if(c == 0x0D || c == -1)
          {
            EOL = true;
            break;
          }
          else
          {
            lineSize++;
          }

        }
      }
    }
  }
  fclose(f);
  return lineSize + 1;
}
