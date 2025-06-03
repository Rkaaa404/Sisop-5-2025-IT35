#include "std_lib.h"

int div(int a, int b) {
  int result;   
  bool negative; 

  if (b == 0) {
    // Division by zero, return 0
    return 0;
  }

  result = 0;
  negative = (a < 0) ^ (b < 0); // XOR check a b negatif atau tidak

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
  return a - div(a, b) * b;
}

bool strcmp(char *str1, char *str2) {
  while (*str1 && (*str1 == *str2)) {
    str1++;
    str2++;
  }
  return (*str1 - *str2); 
}

void strcpy(char *dst, char *src) {
  while (*src) {
    *dst++ = *src++;
  }
  *dst = '\0';
}


void clear(byte *buf, unsigned int size) {
  unsigned int i; 
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num) {
  int result = 0; 
  int sign = 1;   

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
  int i = 0;   
  int sign = num; 
  int j;       
  char temp;    
  int len;      

  if (sign == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  if (sign < 0) {
    num = -num; 
  }

  while (num > 0) {
    str[i++] = mod(num, 10) + '0'; 
    num = div(num, 10);            
  }

  if (sign < 0) {
    str[i++] = '-';
  }
  str[i] = '\0'; // Null-terminate string

  len = i; 
  j = 0;   
  while (j < div(len, 2)) {
    temp = str[j];
    str[j] = str[len - j - 1];
    str[len - j - 1] = temp;
    j++;
  }
}

void strcat(char *dest, char *src) {
    
  while (*dest) { 
    dest++;
  }

  while (*src) { 
    *dest++ = *src++;
  }
  *dest = '\0'; // Null-terminate the string
}
