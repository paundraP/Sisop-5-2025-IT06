#include "shell.h"
#include "kernel.h"

int main() {
    clearScreen(0x07);  
    shell();
}

void printString(char *textPtr) {
    while (*textPtr != '\0') {
        interrupt(0x10, 0x0E00 + *textPtr, 0, 0, 0);        
        textPtr++;
    }
}

void readString(char *buffer) {
    char inputChar;
    int bufferIndex = 0;
    
    while (1) {
        inputChar = interrupt(0x16, 0x0000, 0, 0, 0) & 0xFF;
        
        if (inputChar == 0x0D) break;
        
        if (inputChar == 0x08) {
            if (bufferIndex > 0) {
                bufferIndex--;
                displayPrompt("\b \b");
            }
        } else {
            buffer[bufferIndex++] = inputChar;
            interrupt(0x10, 0x0E00 + inputChar, 0, 0, 0);
        }
    }
    
    buffer[bufferIndex++] = 0x0D;
    buffer[bufferIndex++] = 0x0A;
    buffer[bufferIndex] = '\0';  
    displayPrompt("\r\n");
}

void clearScreen(int backgroundColor) {
    int memoryOffset;
    
    for (memoryOffset = 0; memoryOffset < 80 * 25 * 2; memoryOffset += 2) {
        putInMemory(0xB800, memoryOffset, ' ');
        putInMemory(0xB800, memoryOffset + 1, backgroundColor); 
    }
    
    interrupt(0x10, 0x0200, 0, 0, 0);
}