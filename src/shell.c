#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char currentUser[64] = "user"; 
char systemHost[64] = ""; 
int displayColor = 0x07;

void updateDisplayColor(int newColor) {
    displayColor = newColor;
}

void displayPrompt(char *username) {
    printString(username);
    if (systemHost[0] != '\0') {
        printString(systemHost);  
    }
    printString("> ");
}

void parseCommand(char *buf, char *cmd, char args[2][64]) {
    int pos = 0, cmdIdx = 0, argIdx = 0;
    int currentArgument = 0;
    
    // Skip leading whitespace and newlines
    while (buf[pos] != '\0' && (buf[pos] == '\r' || buf[pos] == '\n')) 
        pos++;
    
    // Extract cmd
    while (buf[pos] != '\0' && buf[pos] != ' ' && 
           buf[pos] != '\r' && buf[pos] != '\n') {
        cmd[cmdIdx++] = buf[pos++];
    }
    cmd[cmdIdx] = '\0';   
    
    // Skip spaces
    while (buf[pos] == ' ') pos++;   
    
    // Extract up to 2 args
    for (currentArgument = 0; currentArgument < 2; currentArgument++) {
        argIdx = 0;
        while (buf[pos] != '\0' && buf[pos] != ' ' && 
               buf[pos] != '\r' && buf[pos] != '\n') {
            args[currentArgument][argIdx++] = buf[pos++];
        }
        args[currentArgument][argIdx] = '\0';
        
        while (buf[pos] == ' ') pos++;
    }
}

void generateRandomResponse() {
    int randomValue = mod(getBiosTick(), 3);
    
    switch(randomValue) {
        case 0:
            printString("ts unami gng </3\r\n");
            break;
        case 1:
            printString("yo\r\n");
            break;
        default:
            printString("sygau\r\n");
            break;
    }    
}

void processCommand(char *command, char *rawInput, char arguments[2][64]) {
    int firstNum, secondNum, calculationResult;
    char resultString[32];
    
    if (strcmp(command, "yo")) {
        printString("gurt\r\n");
        
    } else if (strcmp(command, "gurt")) {
        printString("yo\r\n");
        
    } else if (strcmp(command, "user")) {
        if (arguments[0][0] == '\0') {
            strcpy(currentUser, "user");
        } else {
            strcpy(currentUser, arguments[0]);
        }
        printString("Username changed to ");
        printString(currentUser);
        printString("\r\n");
        
    } else if (strcmp(command, "grandcompany")) {        
        if (strcmp(arguments[0], "maelstrom")) {  
            updateDisplayColor(0x0c);   
            clearScreen(displayColor);                       
            strcpy(systemHost, "@Storm");            
        } else if (strcmp(arguments[0], "twinadder")) {   
            updateDisplayColor(0x0e);   
            clearScreen(displayColor);             
            strcpy(systemHost, "@Serpent");            
        } else if (strcmp(arguments[0], "immortalflames")) {       
            updateDisplayColor(0x09);   
            clearScreen(displayColor);             
            strcpy(systemHost, "@Flame");                   
        } else {
            printString("Unknown company\r\n");
        }
        
    } else if (strcmp(command, "clear")) {
        strcpy(systemHost, "");
        updateDisplayColor(0x07);
        clearScreen(displayColor);      
        
    } else if (strcmp(command, "add")) {
        if (arguments[0][0] == '\0' || arguments[1][0] == '\0') {
            printString("Usage: add <num1> <num2>\r\n");
            return;
        }
        atoi(arguments[0], &firstNum);
        atoi(arguments[1], &secondNum);
        calculationResult = firstNum + secondNum;
        itoa(calculationResult, resultString);        
        printString(resultString);
        printString("\r\n");
        
    } else if (strcmp(command, "sub")) {
        if (arguments[0][0] == '\0' || arguments[1][0] == '\0') {
            printString("Usage: sub <num1> <num2>\r\n");
            return;
        }
        atoi(arguments[0], &firstNum);
        atoi(arguments[1], &secondNum);
        calculationResult = firstNum - secondNum;
        itoa(calculationResult, resultString);        
        printString(resultString);
        printString("\r\n");
        
    } else if (strcmp(command, "mul")) {  
        if (arguments[0][0] == '\0' || arguments[1][0] == '\0') {
            printString("Usage: mul <num1> <num2>\r\n");
            return;
        }
        atoi(arguments[0], &firstNum);
        atoi(arguments[1], &secondNum);
        calculationResult = firstNum * secondNum;
        itoa(calculationResult, resultString);      
        printString(resultString);
        printString("\r\n");
        
    } else if (strcmp(command, "div")) {    
        if (arguments[0][0] == '\0' || arguments[1][0] == '\0') {
            printString("Usage: div <num1> <num2>\r\n");
            return;
        }
        atoi(arguments[0], &firstNum);
        atoi(arguments[1], &secondNum);
        if (secondNum == 0) {
            printString("Error: Division by zero\r\n");
            return;
        }
        calculationResult = div(firstNum, secondNum);
        itoa(calculationResult, resultString);      
        printString(resultString);
        printString("\r\n");
        
    } else if (strcmp(command, "yogurt")) {
        displayPrompt("gurt");
        generateRandomResponse();    
    } else {        
        printString(rawInput);
    }
}

void shell() {
    char inputBuffer[128];
    char parsedCommand[64];
    char commandArgs[2][64];
    
    printString("Hi! Welcome to EorzeOS\r\n");
    
    while (true) {
        displayPrompt(currentUser);
        readString(inputBuffer);
        parseCommand(inputBuffer, parsedCommand, commandArgs);
        processCommand(parsedCommand, inputBuffer, commandArgs); 
    }
}
