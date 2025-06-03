#include "shell.h"
#include "kernel.h"
#include "std_lib.h"
#define WHITE 0x07
#define RED 0x0C
#define BLUE 0x09
#define YELLOW 0x0E

void shell() {
  char buf[128];
  char cmd[10];
  char arg[2][64];
  char user[64] = "user"; 
  byte color = WHITE;
  printString("Welcome to EorzeOS!\n", color);
  
  while (true) {
    printString(user, color);
    printString("> ", color);
    readString(buf, color);
    parseCommand(buf, cmd, arg);
    
    if (strcmp(cmd, "clear") == 0) {  
      clearScreen();
      color = WHITE;
      strcpy(user, "user");  
    } else if (strcmp(cmd, "yo") == 0) {  
      printString("gurt", color);
      printString("\n", color);
    } else if (strcmp(cmd, "gurt") == 0) {  
      printString("yo", color);
      printString("\n", color);
    } else if (strcmp(cmd, "user") == 0) {
      if (arg[0][0] == '\0') {
        strcpy(user, "user");
        printString("Username changed to user \n", color);
      } else {
        strcpy(user, arg[0]);
        printString("Username changed to ", color);
        printString(user, color);
        printString("\n", color);
      }
    } else if (strcmp(cmd, "grandcompany") == 0){
      pickCompany(arg, &color, user);
    } else if (strcmp(cmd, "add") == 0) {
      int a, b, result;
      char str[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result = a + b;
      itoa(result, str);
      printString(str, color);
      printString("\n", color);
    } else if (strcmp(cmd, "sub") == 0) {
      int a, b, result;
      char str[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result = a - b;
      itoa(result, str);
      printString(str, color);
      printString("\n", color);
    } else if (strcmp(cmd, "mul") == 0) {
      int a, b, result;
      char str[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result = a * b;
      itoa(result, str);
      printString(str, color);
      printString("\n", color);
    } else if (strcmp(cmd, "div") == 0) {
      int a, b, result;
      char str[32];
      atoi(arg[0], &a);
      atoi(arg[1], &b);
      result = div(a, b);
      itoa(result, str);
      printString(str, color);
      printString("\n", color);
    } else if (strcmp(cmd, "yogurt")){
      unsigned int tick = getBiosTick();
      int choice = mod(tick,3);

      if (choice == 0) {
        printString("gurt> ts unami gng </3\n", color);
      } else if (choice == 1) {
        printString("gurt> yo\n", color);
      } else {
        printString("gurt> sygau\n", color);
      }
    }else {
      printString(buf, color);  
      printString("\n", color);
    }

    // bersih bersih wok
    clear(buf, sizeof(buf));
    clear(cmd, sizeof(cmd));
    clear((byte*)arg, sizeof(arg));
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, argIndex = 0;
  bool isArg = false;

  while (buf[i] != '\0') {
    if (buf[i] == ' ' || buf[i] == '\n') {
      if (!isArg) {
        cmd[j] = '\0';  
        isArg = true;   
        j = 0;
      }
    } else {
      if (!isArg) {
        cmd[j++] = buf[i];  
      } else {
        arg[argIndex][j] = buf[i];  
        j++;
      }
    }
    i++;

    if (buf[i] == ' ' || buf[i] == '\n') {
      if (isArg && j > 0) {
        arg[argIndex][j] = '\0';  
        argIndex++;  
        j = 0;  
        if (argIndex == 2) break;  
      }
    }
  }

  if (isArg && j > 0 && argIndex < 2) {
    arg[argIndex][j] = '\0';  
  }
}

void pickCompany(char arg[2][64], byte *color, char *user) {
  char tmp[64];

  if (strcmp(arg[0], "maelstrom") == 0) {
    *color = RED;
    strcpy(tmp, user);
    strcpy(user, tmp);
    strcat(user, "@Storm");
    clearScreen();
  } else if (strcmp(arg[0], "twinadder") == 0) {
    *color = YELLOW;
    strcpy(tmp, user);
    strcpy(user, tmp);
    strcat(user, "@Serpent");
    clearScreen();
  } else if (strcmp(arg[0], "immortalflames") == 0) {
    *color = BLUE;
    strcpy(tmp, user);
    strcpy(user, tmp);
    strcat(user, "@Flame");
    clearScreen();
  } else {
    printString("Maaf, grandcompany tidak ditemukan... \n", *color);
  }
}
