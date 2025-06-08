#include "std_lib.h"

int div(int a, int b) {
    int quotient;
    int dividend;
    int divisor;
    
    if (b == 0) return 0;
    
    quotient = 0;
    if (a < 0)
        dividend = -a;
    else
        dividend = a;

    if (b < 0)
        divisor = -b;
    else
        divisor = b;
    
    while (dividend >= divisor) {
        dividend = dividend - divisor;
        quotient++;
    }
    
    if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
        quotient = -quotient;
    }
    
    return quotient;
}

int mod(int a, int b) {
    int abs_a;
    int abs_b;
    
    if (b == 0) return 0;

    if (a < 0)
        abs_a = -a;
    else
        abs_a = a;

    if (b < 0)
        abs_b = -b;
    else
        abs_b = b;

    while (abs_a >= abs_b) {
        abs_a = abs_a - abs_b;
    }

    if (a < 0)
        return -abs_a;
    else
        return abs_a;
}

bool strcmp(char *str1, char *str2) {
    int i;

    i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    
    if (str1[i] == '\0' && str2[i] == '\0') {
        return true;
    }
    return false;
}

void strcpy(char *dst, char *src) {
    int i;

    i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }

    dst[i] = '\0';
}

void clear(byte *buf, unsigned int size) {
    unsigned int i;

    for (i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

void atoi(char *str, int *num) {
    int result;
    int sign;
    int i;

    result = 0;
    sign = 1;
    i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r') {
        i++;
    }

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    *num = result * sign;
}

void itoa(int num, char *str) {
    int i;
    int isNegative;
    int start;
    int end;
    char temp;

    i = 0;
    isNegative = 0;

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    while (num > 0) {
        str[i] = mod(num, 10) + '0';
        num = div(num, 10);
        i++;
    }

    if (isNegative) {
        str[i] = '-';
        i++;
    }

    str[i] = '\0';

    start = 0;
    end = i - 1;

    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
