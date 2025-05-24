#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

// Function to get result from Arduino
int arduino_result() {
    DCB serial_parameters = { 0 };  // Serial port parameters
    HANDLE serial_port;              // Serial port handle

    // Start communication with COM4 port
    serial_port = CreateFile("\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (serial_port == INVALID_HANDLE_VALUE) {
        // Error handling
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            printf("ERROR: COM4 IS NOT AVAILABLE.\n");
        }
        else {
            printf("ERROR !!!\n");
        }
    }
    else {
        // Get serial port parameters
        serial_parameters.DCBlength = sizeof(serial_parameters);
        if (!GetCommState(serial_port, &serial_parameters)) {
            printf("ERROR !!!\n");
            CloseHandle(serial_port);
            return 0; 
        }

        // Set serial port parameters
        serial_parameters.BaudRate = CBR_9600;
        serial_parameters.ByteSize = 8;
        serial_parameters.StopBits = ONESTOPBIT;
        serial_parameters.Parity = NOPARITY;

        if (!SetCommState(serial_port, &serial_parameters)) {
            printf("ERROR !!!\n");
            CloseHandle(serial_port);
            return 0; 
        }

        // Array to catch data from Arduino
        char catch[256];
        DWORD bytesRead;
        // Read data from the serial port
        if (ReadFile(serial_port, catch, sizeof(catch), &bytesRead, NULL)) {
            catch[bytesRead] = '\0'; 
            CloseHandle(serial_port);
            return atoi(catch); 
        } else {
            printf("ERROR !!!\n");
            CloseHandle(serial_port);
            return 0;
        }
    }

    return 0;
}

// Function for Arduino communication
void arduino_get(int caller, int sec_parameter) {
    DCB serial_parameters = { 0 };  // Serial port parameters
    HANDLE serial_port;              // Serial port handle
   
    // Start communication with COM4 port
    serial_port = CreateFile("\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (serial_port == INVALID_HANDLE_VALUE) {
        // Error handling
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            printf("Error: CONNECTION FAILED\n");
        }
    }
    else {
        // Get serial port parameters
        serial_parameters.DCBlength = sizeof(serial_parameters);

        if (!GetCommState(serial_port, &serial_parameters)) {
            printf("Error\n");
            CloseHandle(serial_port);
            return;
        }

        // Set serial port parameters
        serial_parameters.BaudRate = CBR_9600;
        serial_parameters.ByteSize = 8;
        serial_parameters.StopBits = ONESTOPBIT;
        serial_parameters.Parity = NOPARITY;

        if (!SetCommState(serial_port, &serial_parameters)) {
            printf("Error\n");
            CloseHandle(serial_port);
            return;
        }

        // Put commands to be sent to Arduino into a char array
        char command[2];
        command[0] = (char)caller;
        command[1] = (char)sec_parameter;

        DWORD bytesWritten;
        // Send commands to the serial port
        if (!WriteFile(serial_port, command, 2, &bytesWritten, NULL)) {
            printf("Error\n");
        }

        // Close the serial port connection
        CloseHandle(serial_port);
    }
}
int main() {
    long sonuc;           // Result returned from Arduino
    int caller;           // User's choice
    int fact_num;         // Number entered to calculate factorial
    
    // Main loop for user interaction
    do {
        // Welcome message to the user
        printf("## WELCOME TO GTU ARDUINO LAB          ##\n");
        printf("## STUDENT NAME: MUHAMMED KORKMAZ      ##\n");
        printf("## PLEASE SELECT FROM THE FOLLOWING    ##\n");
        printf("## MENU :                              ##\n");
        printf("(1) TURN ON LED ON ARDUINO\n");
        printf("(2) TURN OFF LED ON ARDUINO\n");
        printf("(3) FLASH ARDUINO LED 5 TIMES\n");
        printf("(4) SEND A NUMBER TO ARDUINO TO COMPUTE FACTORIAL BY ARDUINO\n");
        printf("(5) TURN ON EXTERNAL LED\n");
        printf("(0) EXIT\n");
        printf("    PLEASE SELECT: ");
        scanf("%d", &caller);

        switch (caller) {
            case 1:
            case 2:
            case 3:
            case 5:
                // Send a simple command to Arduino
                arduino_get(caller, 0);
                break;

            case 4:
                // Get a number from the user and send it to Arduino
                printf("    ENTER AN INTEGER NUMBER: ");
                scanf("%d", &fact_num);
                arduino_get(4, fact_num);

                // Get the result from Arduino and print it to the screen
                sonuc = arduino_result();
                printf("    THE FACTORIAL OF THE SENT NUMBER IS: %ld\n\n", sonuc);
                break;

            case 0:
                printf("    YOU ARE QUITTED\n");
                break;
                
            default:
                printf("    INVALID CHOICE\n");
        }
    } while (caller != 0);

    return 0;
}


