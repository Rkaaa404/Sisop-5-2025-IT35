#include "shell.h"
#include "kernel.h"

#define WHITE_ON_BLACK 0x07
#define VIDEO_PAGE 0

int main() {
  clearScreen();
  shell();
  while (1);
  return 0;
}

void printString(char *str, byte color_attribute) {
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == '\n') {
      interrupt(0x10, (0x0E << 8) | '\r', VIDEO_PAGE << 8, 0, 0);
      interrupt(0x10, (0x0E << 8) | '\n', VIDEO_PAGE << 8, 0, 0);
    } else {
      interrupt(0x10, (0x0E << 8) | str[i], VIDEO_PAGE << 8, 0, 0);
    }
    i++;
  }
}

void readString(char *buf, byte color_attribute) {
  int i = 0;
  int ch_code_ax;
  char ch;

  while (1) {
    ch_code_ax = interrupt(0x16, 0x00 << 8, 0, 0, 0);
    ch = (char)ch_code_ax;

    if (ch == 0x0D) {
      buf[i] = '\0';
      interrupt(0x10, (0x0E << 8) | '\r', VIDEO_PAGE << 8, 0, 0);
      interrupt(0x10, (0x0E << 8) | '\n', VIDEO_PAGE << 8, 0, 0);
      break;
    } else if (ch == 0x08) {
      if (i > 0) {
        i--;
        interrupt(0x10, (0x0E << 8) | '\b', VIDEO_PAGE << 8, 0, 0);
        interrupt(0x10, (0x0E << 8) | ' ',  VIDEO_PAGE << 8, 0, 0);
        interrupt(0x10, (0x0E << 8) | '\b', VIDEO_PAGE << 8, 0, 0);
      }
    } else if (ch >= ' ' && ch <= '~') {
      if (i < 127) {
        buf[i] = ch;
        interrupt(0x10, (0x0E << 8) | ch, VIDEO_PAGE << 8, 0, 0);
        i++;
      }
    }
  }
}

void clearScreen() {
  interrupt(0x10, (0x06 << 8) | 0x00, (WHITE_ON_BLACK << 8) | 0x00, (0x00 << 8) | 0x00, (24 << 8) | 79);
  interrupt(0x10, (0x02 << 8) | 0x00, VIDEO_PAGE << 8, 0x00 << 8 | 0x00, 0);
}
