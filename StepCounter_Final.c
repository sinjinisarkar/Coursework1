#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
#define buffer_size 200
char filename[buffer_size];
FITNESS_DATA fitnessData[1000];
int numRecords = 0;

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Outputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        strcpy(date, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }

    // Free the duplicated string
    free(inputCopy);
}

// Complete the main function
int main() 
{
    char choice;
    FILE *file = NULL;  // File pointer
    do {
        printf("\nMenu Options:\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the data and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Quit\n");

        printf("Enter choice: ");
        scanf(" %c", &choice);

        switch (choice) 
        {
            case 'A':
            case 'a':
                printf("Input filename: ");
                scanf("%s", filename);
                file = fopen(filename, "r");
                if (file == NULL) {
                    perror("Error: Could not find or open the file.\n");
                    return 1;
                    }

                
    
                char line_buffer[buffer_size];
                while (fgets(line_buffer, buffer_size, file) != NULL) {
                    char date[11];
                    char time[6];
                    char steps[20]; // Assuming steps can be a long number
                    // The function will split line_buffer whenever it encounters a comma.
                    tokeniseRecord(line_buffer, ",", date, time, steps);
                    int stepsInt = atoi(steps); // Convert from string to integer
                    // Store data in the struct array 
                    strcpy(fitnessData[numRecords].date, date);
                    strcpy(fitnessData[numRecords].time, time);
                    fitnessData[numRecords].steps = stepsInt;
                    numRecords++; 
                }
                fclose(file);
                printf("File successfully loaded.");
                break;

            case 'B':
            case 'b':
            if (numRecords == 0) {
                printf("Error: No records found. Please load the file first.\n");
                break;
                }
            // Display the total number of records in the file
            printf("Total records: %d", numRecords);
            break;


            // Find the date and time of the timeslot with the fewest steps
            case 'C':
            case 'c':
                if (numRecords == 0) {
                    printf("Error: No records found. Please load the file first.\n");
                    break;
                }
                int fewSteps = fitnessData[0].steps;
                int fewIndex = 0;
                for (int i = 1; i < numRecords; i++) {
                    if (fitnessData[i].steps < fewSteps) {
                        fewSteps = fitnessData[i].steps;
                        fewIndex = i;
                    }
                }
                
                // Format the output date and time
                printf("Fewest steps: %s %s", fitnessData[fewIndex].date, fitnessData[fewIndex].time);
                break;
            
            //// Find the date and time of the timeslot with the largest number of step
            case 'D':
            case 'd':
                if (numRecords == 0) {
                    printf("Error: No records found. Please load the file first.\n");
                    break;
                }
                
                int maxSteps = fitnessData[0].steps;
                int maxIndex = 0;
                for (int i = 1; i < numRecords; i++) {
                    if (fitnessData[i].steps > maxSteps) {
                    maxSteps = fitnessData[i].steps;
                    maxIndex = i;
                    }
                }
                printf("Largest steps: %s %s", fitnessData[maxIndex].date, fitnessData[maxIndex].time);
                break;
            
            // Find the mean step count of all the records in the file
            case 'E':
            case 'e':
                if (numRecords == 0) {
                    printf("Error: No records found. Please load the file first.\n");
                    break;
                }
                int total = 0;
                for (int i = 0; i < numRecords; i++) {
                    total += fitnessData[i].steps;
                }
                // Calculate the mean steps
                float mean = (float)total / numRecords;
                printf("Mean step count: %.0f", mean);
                break;
            
            case 'F':
            case 'f':
               if 
               
                


            case 'Q':
            case 'q':
                return 0;
                break;

            // if they type anything else
            default:
                printf("Invalid choice. Try again.");
                break;
        }
    } while (choice != 'Q' && choice != 'q');

    return 0;

}
