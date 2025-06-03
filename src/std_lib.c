#include "std_lib.h"

int div(int a, int b)
{
  //TODO: Implementasi pembagian
  //NOTE: HARUS BISA ANGKA NEGATIF
  int quotient = 0;
  int negative = 0;
  if (a < 0) {
    a = -a;
    negative = !negative;
  }
  if (b < 0) {
    b = -b;
    negative = !negative;
  }
  while (a >= b) {
    a -= b;
    quotient++;
  }
  return negative ? -quotient : quotient;
}

int mod(int a, int b)
{
  //TODO: Implementasi modulus
  int negative = 0;
  if (a < 0) {
    a = -a;
    negative = 1;
  }
  if (b < 0) {
    b = -b;
  }
  while (a >= b) {
    a -= b;
  }
  return negative ? -a : a;
}

bool strcmp(char *str1, char *str2)
{
  //TODO: Implementasi perbandingan string
  while (*str1 && *str2) {
    if (*str1 != *str2) return false;
    str1++;
    str2++;
  }
  return *str1 == '\0' && *str2 == '\0';
}

void strcpy(char *dst, char *src)
{
  //TODO: Implementasi penyalinan string
  while (*src) {
    *dst++ = *src++;
  }
  *dst = '\0';
}

void clear(byte *buf, unsigned int size)
{
  //TODO: Implementasi pembersihan buffer
  for (unsigned int i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num)
{
  //TODO: Implementasi konversi string ke integer
  //NOTE: HARUS BISA ANGKA NEGATIF
  int sign = 1;
  int result = 0;

  if (*str == '-') {
    sign = -1;
    str++;
  }

  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');
    str++;
  }

  *num = result * sign;
}

void itoa(int num, char *str)
{
  //TODO: Implementasi konversi integer ke string
  //NOTE: HARUS BISA ANGKA NEGATIF
  int i = 0;
  int isNegative = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  if (num < 0) {
    isNegative = 1;
    num = -num;
  }

  while (num > 0) {
    str[i++] = (num % 10) + '0';
    num /= 10;
  }

  if (isNegative) {
    str[i++] = '-';
  }

  str[i] = '\0';

  for (int j = 0, k = i - 1; j < k; j++, k--) {
    char temp = str[j];
    str[j] = str[k];
    str[k] = temp;
  }
}