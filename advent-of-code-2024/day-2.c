#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 1024
#define INT_BUFFER_SIZE 128

int main(int argc, char** argv) {
    FILE *file;
    char line[BUFFER_SIZE]; // Buffer to store each line

    // Open the file in read mode
    file = fopen("day-2-input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the file line by line
    int i;
    int arr[INT_BUFFER_SIZE];
    int bad_reports = 0;
    int point; 
    int nlines = 0;
    int increasing; // Default true

    while (fgets(line, BUFFER_SIZE, file)) {
        i = 0;
        increasing = 1;
        nlines++;
        point = 0;

        char *token = strtok(line, " ");
        while (token != NULL) {
            arr[i++] = atoi(token); // Convert string to integer and store in array
            token = strtok(NULL, " "); // Get the next token
        }

        if (i < 1) {
            printf("Array smaller than 2\n");
            ++bad_reports;
            break;
        }

        if ((arr[0] - arr[1]) > 0) {
            increasing = 0;
        }

        printf("line %d, is increasing %d\n", nlines, increasing);

        for (int j = 0; j < i - 1; j++) {
            // printf("%d ", arr[j]);
            if (increasing && (arr[j] - arr[j + 1]) > 0) {
                ++point;
                printf("increasing violation\n");
                continue;
            } else if (!increasing && (arr[j] - arr[j + 1]) < 0) {
                ++point;
                printf("increasing violation\n");
                continue;
            }

            if (abs(arr[j] - arr[j + 1]) < 1 || abs(arr[j] - arr[j + 1]) > 3) {
                printf("bad\n");
                ++point;
                continue;
            }       

            if (point == 1) {
                arr[j + 1] = arr[j];
            } else if (point >= 2) {
                ++bad_reports;
                break;
            }
        }
    }

    printf("safe_reports = %d\n", nlines - bad_reports);
    // Close the file
    fclose(file);

    return 0;
}
