#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "std_type.h"

extern void putInMemory(int segment, int address, char character);
extern int interrupt(int number, int AX, int BX, int CX, int DX);
extern unsigned int getBiosTick();
extern int getCursorPos();

void printString(char* str, byte color);
void readString(char* buf, byte color);
void clearScreen();

#endif // __KERNEL_H__
