#include "shell.h"
#include "kernel.h"
#include "std_lib.h" 

// Define color codes
#define WHITE 0x07
#define RED 0x0C
#define BLUE 0x09
#define YELLOW 0x0E

void shell() {
  
  char buf[128];
  char cmd[16];
  char arg[2][64]; 
  char user[64];
  int neutral;   
  byte color;      

  strcpy(user, "user"); 
  color = WHITE;
  neutral = 1;        

  printString("Welcome to EorzeOS!\n", color);
  while (true) {
    printString(user, color);
    printString("> ", color);
    readString(buf, color); 
    parseCommand(buf, cmd, arg); 

    if (strcmp(cmd, "clear") == 0) {
      char tempUserBase[64];
      char *atSymbolPosition = 0;
      int k = 0;
      int baseNameLength;

      clearScreen();
      color = WHITE;

      while(user[k] != '\0'){
        if(user[k] == '@'){
          atSymbolPosition = &user[k];
          break;
        }
        k++;
      }

      if (!neutral) {
        baseNameLength = atSymbolPosition - user;
        if (baseNameLength < 64) {
            strncpy(tempUserBase, user, baseNameLength);
            tempUserBase[baseNameLength] = '\0';
            strcpy(user, tempUserBase);
        }
      }
      neutral = 1; 
    } else if (strcmp(cmd, "yo") == 0) {
      printString("gurt", color);
      printString("\n", color);
    } else if (strcmp(cmd, "gurt") == 0) {
      printString("yo", color);
      printString("\n", color);
    } else if (strcmp(cmd, "user") == 0) {
      if (arg[0][0] == '\0') { 
        strcpy(user, "user");
        printString("Username changed to user\n", color);
      } else {
        if (neutral){
          strcpy(user, arg[0]);
        } else {
          char companyName[64];
          char *iterator = user;
          while (*iterator != '\0' && *iterator != '@'){
            iterator++;
          }

          strcpy(companyName, iterator);
          strcpy(user, arg[0]);
          strcat(user, companyName);
        }
        printString("Username changed to ", color);
        printString(user, color);
        printString("\n", color);
      }
    } else if (strcmp(cmd, "grandcompany") == 0) {
      pickCompany(arg, &color, user); 
      neutral = 0;
    } else if (strcmp(cmd, "add") == 0) {
      int a, b, result;
      char str_result[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result = a + b;
      itoa(result, str_result);
      printString(str_result, color);
      printString("\n", color);
    } else if (strcmp(cmd, "sub") == 0) {
      int a, b, result;
      char str_result[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result = a - b;
      itoa(result, str_result);
      printString(str_result, color);
      printString("\n", color);
    } else if (strcmp(cmd, "mul") == 0) {
      int a, b, result;
      char str_result[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result = a * b;
      itoa(result, str_result);
      printString(str_result, color);
      printString("\n", color);
    } else if (strcmp(cmd, "div") == 0) { 
      int a, b, result_val; 
      char str_result[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result_val = div(a, b); 
      itoa(result_val, str_result);
      printString(str_result, color);
      printString("\n", color);
    } else if (strcmp(cmd, "yogurt") == 0) { 
      unsigned int tick;
      int choice;
      tick = getBiosTick(); // Get BIOS tick count
      choice = mod(tick, 3);  // Get a choice based on tick

      if (choice == 0) {
        printString("gurt> ts unami gng </3\n", color);
      } else if (choice == 1) {
        printString("gurt> yo\n", color);
      } else {
        printString("gurt> sygau\n", color);
      }
    } else if (buf[0] != '\0') {
      printString(buf, color);
      printString("\n", color);
    } 

    // Clear buffers 
    clear((byte*)buf, 128); 
    clear((byte*)cmd, 16);
    clear((byte*)arg, sizeof(arg)); 
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, argIndex = 0;
  bool isArg = false; 

  clear((byte*)cmd, 16);
  clear((byte*)arg, sizeof(arg[0]) * 2); 

  while (buf[i] != '\0' && buf[i] != '\n') { 
    if (buf[i] == ' ') { 
      if (!isArg) {     
        cmd[j] = '\0';
        isArg = true;
        j = 0; 
      } else if (j > 0) { 
        arg[argIndex][j] = '\0';
        argIndex++;
        j = 0;
        if (argIndex >= 2) break; 
      }
      while(buf[i+1] == ' ') i++;

    } else { 
      if (!isArg) {
        if (j < 16 - 1) cmd[j++] = buf[i]; 
      } else {
        if (argIndex < 2 && j < 64 - 1) arg[argIndex][j++] = buf[i]; 
      }
    }
    i++;
  }

  if (!isArg) {
    cmd[j] = '\0';
  } else if (argIndex < 2 && j > 0) {
    arg[argIndex][j] = '\0';
  }
}

void strncpy(char *dst, char *src, unsigned int n) {
  unsigned int i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dst[i] = src[i];
  }
  if (n > 0) {
    if (i < n) {
      dst[i] = '\0';
    } else {
      dst[n] = '\0';
    }
  }
}

void pickCompany(char arg[2][64], byte *color, char *user) {
  char baseUser[32]; 
  char *atSymbol;
  int k = 0; 
  int len_base_user; 

  atSymbol = 0; 
  while(user[k] != '\0'){
    if(user[k] == '@'){
      atSymbol = &user[k];
      break;
    }
    k++;
  }

  if (atSymbol != 0) {
    len_base_user = atSymbol - user;
    if (len_base_user > 31) len_base_user = 31; 
    strncpy(baseUser, user, len_base_user);
    baseUser[len_base_user] = '\0';
  } else { 
    strcpy(baseUser, user);
  }


  if (strcmp(arg[0], "maelstrom") == 0) {
    *color = RED;
    strcpy(user, baseUser);
    strcat(user, "@Storm");   
    clearScreen();
  } else if (strcmp(arg[0], "twinadder") == 0) {
    *color = YELLOW; 
    strcpy(user, baseUser);
    strcat(user, "@Serpent");
    clearScreen();
  } else if (strcmp(arg[0], "immortalflames") == 0) {
    *color = BLUE; 
    strcpy(user, baseUser);
    strcat(user, "@Flame");
    clearScreen();
  } else {
    printString("Company itu belum ada...\n", *color);
  }
}
