#include "std_lib.h"

int div(int a, int b) {
  if (b == 0) {
    return 0;  // Return 0 saat pembagian dengan 0
  }
  int result = 0;
  bool negative = (a < 0) ^ (b < 0);

  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (a >= b) {
    a -= b;
    result++;
  }
  return negative ? -result : result;  
}

int mod(int a, int b) {
  if (b == 0) {
    return 0;  
  }
  return a - div(a, b) * b;  // Return sisa
}

bool strcmp(char *str1, char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return (*str1 - *str2);  // Return 0 kalau sama
}

void strcpy(char *dst, char *src) {
  while (*src) {
    *dst++ = *src++;  
  }
  *dst = '\0';  
}

void clear(byte *buf, unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    buf[i] = 0;  
  }
}

void atoi(char *str, int *num) {
  int result = 0, sign = 1;

  if (*str == '-') {
    sign = -1;
    str++;
  }
  
  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');
    str++;
  }
  *num = sign * result;  
}

void itoa(int num, char *str) {
  int i = 0, sign = num;

  if (num < 0) {
    num = -num;
  } 

  do {
    str[i++] = mod(num,10) + '0';  
  } while ((div(num,10)) > 0);

  if (sign < 0) {
    str[i++] = '-';  
  }

  str[i] = '\0'; 

  int j = 0;
  while (j < div(i,2)) {
    char temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
    j++;
  }
}

void strcat(char *dest, const char *src) {
    while (*dest) dest++; 
    while (*src) *dest++ = *src++;  
    *dest = '\0';  
}
