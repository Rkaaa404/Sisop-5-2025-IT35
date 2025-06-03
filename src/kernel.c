#include "shell.h"
#include "kernel.h"
#define WHITE 0x07

int main() {
  clearScreen();
  shell();
}

void printString(char *str, byte color)
{
  int i = 0;
  while (str[i] != '\0') {
    putInMemory(0xB000, 0x8000 + i * 2, str[i]);   
    putInMemory(0xB000, 0x8001 + i * 2, color); 
    i++;
  }
}

void readString(char *buf, byte color)
{
  int i = 0;
  char ch;

  while (1) {
    asm volatile (
      "mov $0x00, %%ah\n"        // Set up BIOS interrupt 0x16 (keyboard input)
      "int $0x16\n"              // Call BIOS interrupt 0x16 to read a character from the keyboard
      "mov %%al, %[ch]"          // Store the result in 'ch'
      : [ch] "=r" (ch)           // Output: 'ch' is the result of the assembly code
      :                          // No input operands
      : "%ah", "%al"             // Clobbered registers
    );

    if (ch == 0x0D) {  // Enter key
      buf[i] = '\0';  
      break;
    }

    if (ch == 0x08) { // Backspace
      if (i > 0) {  
        i--;  
        putInMemory(0xB000, 0x8000 + (i * 2), ' ');  
        putInMemory(0xB000, 0x8001 + (i * 2), WHITE); 
      }
    } else if (i < 127) {  
      buf[i] = ch;
      i++;
      putInMemory(0xB000, 0x8000 + (i * 2), ch);  
      putInMemory(0xB000, 0x8001 + (i * 2), color);
    }
  }
}


void clearScreen()
{
  int i;
  for (i = 0; i < 2000; i++) { // ukuran layar 80 * 25 karakter = 2000
    putInMemory(0xB000, 0x8000 + i * 2, ' ');   
    putInMemory(0xB000, 0x8001 + i * 2, WHITE); 
  }
}