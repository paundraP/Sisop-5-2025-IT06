#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

void printString(char *str)
{
  //TODO: Implementasi fungsi untuk mencetak string
  while (*str) {
    interrupt(0x10, 0x0E00 + *str, 0, 0, 0);
    str++;
  }
}

void readString(char *buf)
{
  //TODO: Implementasi fungsi untuk membaca string
  int i = 0;
  char c;
  while (1) {
    c = interrupt(0x16, 0, 0, 0, 0);
    if (c == 0x0D) break;
    if (c == 0x08 && i > 0) {
      i--;
      printString("\b \b");
    } else if (c >= 32 && c <= 126 && i < 127) {
      buf[i++] = c;
      interrupt(0x10, 0x0E00 + c, 0, 0, 0);
    }
  }
  buf[i] = '\0';
  printString("\n");
}

void clearScreen()
{
  //TODO: Implementasi fungsi untuk membersihkan layar
  int i;
  for (i = 0; i < 80 * 25 * 2; i += 2) {
    putInMemory(0xB800, i, ' ');
    putInMemory(0xB800, i + 1, 0x07);
  }
  interrupt(0x10, 0x0200, 0, 0, 0);
}