#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

#define RED_TEXT "\033[1;31m"
#define YELLOW_TEXT "\033[1;33m"
#define BLUE_TEXT "\033[1;34m"
#define RESET_TEXT "\033[0m"
#define CLEAR_SCREEN "\033[2J\033[H"

void shell(){
  char buf[128];
  char cmd[64];
  char arg[2][64];
  char username[32] = "user";
  char grandCompany[16] = "";
  char colorCode[16] = RESET_TEXT;

  printString("Welcome to EorzeOS!\n");

  while (true) {
    printString(colorCode);
    printString(username);
    if (grandCompany[0] != '\0') {
      printString("@");
      printString(grandCompany);
    }
    printString("> ");
    readString(buf);
    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "user") == 0) {
      if (arg[0][0] != '\0') {
        strcpy(username, arg[0]);
      } else {
        strcpy(username, "user");
      }
      printString("Username changed to ");
      printString(username);
      printString("\n");
    } else if (strcmp(cmd, "grandcompany") == 0) {
      if (strcmp(arg[0], "maelstrom") == 0) {
        strcpy(colorCode, RED_TEXT);
        strcpy(grandCompany, "Storm");
        printString(CLEAR_SCREEN);
      } else if (strcmp(arg[0], "twinadder") == 0) {
        strcpy(colorCode, YELLOW_TEXT);
        strcpy(grandCompany, "Serpent");
        printString(CLEAR_SCREEN);
      } else if (strcmp(arg[0], "immortalflames") == 0) {
        strcpy(colorCode, BLUE_TEXT);
        strcpy(grandCompany, "Flame");
        printString(CLEAR_SCREEN);
      } else {
        printString("Invalid grand company name.\n");
      }
    } else if (strcmp(cmd, "clear") == 0) {
      printString(CLEAR_SCREEN);
      strcpy(colorCode, RESET_TEXT);
      grandCompany[0] = '\0';
    } else if (strcmp(cmd, "add") == 0 || strcmp(cmd, "sub") == 0 || strcmp(cmd, "mul") == 0 || strcmp(cmd, "div") == 0) {
    int x = 0, y = 0;
    if (arg[0][0] == '\0' || arg[1][0] == '\0') {
      printString("Please provide two arguments\n");
    } else {
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      if (strcmp(cmd, "add") == 0) {
        int res = x + y;
        printInt(res);
        printString("\n");
      } else if (strcmp(cmd, "sub") == 0) {
        int res = x - y;
        printInt(res);
        printString("\n");
      } else if (strcmp(cmd, "mul") == 0) {
        int res = x * y;
        printInt(res);
        printString("\n");
      } else if (strcmp(cmd, "div") == 0) {
        if (y == 0) {
          printString("Division by zero error\n");
        } else {
          int res = x / y;
          printInt(res);
          printString("\n");
        }
      }
    }
} else if ((strcmp(cmd, "yo") == 0 && strcmp(username, "gurt") != 0) ||
               (strcmp(cmd, "gurt") == 0 && strcmp(username, "yo") != 0)) {
      if (strcmp(cmd, "yo") == 0) printString("gurt\n");
      else printString("yo\n");
    } else if (strcmp(cmd, "yogurt") == 0) {
      const char *responses[] = {"yo", "ts unami gng </3", "sygau"};
      int r = random() % 3;
      printString("gurt> ");
      printString(responses[r]);
      printString("\n");
    } else {
      printString(buf);
      printString("\n");
    }
  }
}


void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  //TODO: Implementasi fungsi untuk mem-parsing perintah
  int i = 0, j = 0, k = 0;
  while (buf[i] == ' ') i++;
  while (buf[i] != ' ' && buf[i] != '\0') {
    cmd[j++] = buf[i++];
  }
  cmd[j] = '\0';
  if (buf[i] == ' ') {
    i++;
    j = 0;
    while (buf[i] != ' ' && buf[i] != '\0') {
      arg[0][j++] = buf[i++];
    }
    arg[0][j] = '\0';
  } else {
    arg[0][0] = '\0';
  }
  if (buf[i] == ' ') {
    i++;
    j = 0;
    while (buf[i] != ' ' && buf[i] != '\0') {
      arg[1][j++] = buf[i++];
    }
    arg[1][j] = '\0';
  } else {
    arg[1][0] = '\0';
  }
}

// Tambahkan fungsi bila perlu
int random() {
  static unsigned int seed = 0xACE1;
  seed = (seed * 1103515245 + 12345) & 0x7fffffff;
  return seed;
}
