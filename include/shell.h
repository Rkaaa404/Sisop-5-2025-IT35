#ifndef __SHELL_H__
#define __SHELL_H__

#include "std_type.h"

void shell();
void parseCommand(char *buf, char *cmd, char arg[2][64]);
void pickCompany(char arg[2][64], byte *color, char *user);
void strncpy(char *dst, char *src, unsigned int n);
#endif // __SHELL_H__
