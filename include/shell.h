#ifndef __SHELL_H__
#define __SHELL_H__

#include "std_type.h"

void shell();
void parseCommand(char *buf, char *cmd, char args[2][64]);
void updateDisplayColor(int newColor);
void displayPrompt(char *username);
void extractCommand(char *inputBuffer, char *command, char arguments[2][64]);
void generateRandomResponse();
void processCommand(char *command, char *rawInput, char arguments[2][64]);

#endif // __SHELL_H__
