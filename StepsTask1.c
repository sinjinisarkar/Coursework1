#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here
#define MAX_SIZE 1000 //defining the array


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
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
int main() {
    FILE *file = fopen("FitnessData_2023.csv", "r");
    if (file == NULL) {
        perror("Error");
        return 1;
    }
    
    FITNESS_DATA fitnessData[MAX_SIZE]; // Creates an array named fitnessData and stores the data
    int numRecords; // Variable to store the number of records read and processed

    int buffer_size = 200; // Giving the buffer size a larger value so that it has the ability to read in any data file
    char line_buffer[buffer_size];

    while (fgets(line_buffer, buffer_size, file) != NULL) {
        char date[11];
        char time[6];
        char steps[20]; // Have put a large number as assuming steps can be long number


        // The function will split line_buffer whenever it encounters a comma.
        tokeniseRecord(line_buffer, ",", date, time, steps);
        
        int stepsInt = atoi(steps); // Have used atoi here to convert from string to integer

        // Store data in the struct array 
        strcpy(fitnessData[numRecords].date, date);
        strcpy(fitnessData[numRecords].time, time);
        fitnessData[numRecords].steps = stepsInt;

        numRecords++; 
    }

    fclose(file);
    
    //Output the number of records
    printf("Number of records in file: %d\n", numRecords);

   // Print the first three rows - took some help of chatgpt as not many resoursces were available online
    int printRows; 
    for (int i = 0; i < numRecords && printRows < 3; i++) {
        int found = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(fitnessData[i].time, fitnessData[j].time) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("%s/%s/%d\n", fitnessData[i].date, fitnessData[i].time, fitnessData[i].steps);
            printRows++;
        }
    }

    return 0;
}