#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 2048
#define INT_BUFFER_SIZE 256

int try_safe(int *arr, int size);

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
    int unsafe;

    while (fgets(line, BUFFER_SIZE, file)) {
        unsafe = 0;
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
                if(try_safe(arr, i)) {
                    printf("safe\n");
                } else {
                    ++bad_reports;
                    printf("increasing violation\n");
                }
                break;
            } else if (!increasing && (arr[j] - arr[j + 1]) < 0) {
                if(try_safe(arr, i)) {
                    printf("safe\n");
                } else {
                    ++bad_reports;
                    printf("increasing violation\n");
                }
                break;
            }

            if (abs(arr[j] - arr[j + 1]) < 1 || abs(arr[j] - arr[j + 1]) > 3) {
                if(try_safe(arr, i)) {
                    printf("safe\n");
                } else {
                    ++bad_reports;
                    printf("bad\n");
                }
                break;
            }       
        }
    }

    printf("safe_reports = %d\n", nlines - bad_reports);
    // Close the file
    fclose(file);

    return 0;
}

/**
 * @brief test for safety of array
 * 
 * @param arr 
 * @param size 
 * @return int 1 if safe, 0 if not
 */
int try_safe(int *arr, int size) {
    //Not memory efficient but I've given up
    int* temp_ptr = malloc(sizeof(int) * (size - 1));
    int increasing = 1;
    int ret = 0;

    //Create copies 
    for(int i = 0; i < size; ++i) {

        int j = 0;
        int l = 0;
        while(j < size) {
            if(i == j) {
                ++j;
                continue;
            } 

            temp_ptr[l] = arr[j];
            ++j;
            ++l;
        }
        
        for(int m = 0; m < size - 1; ++m) {
            printf("%d ", temp_ptr[m]);
        }
        printf("\n");

        //Check if teration is safe or not
        if ((temp_ptr[0] - temp_ptr[1]) > 0) {
            increasing = 0;
        }

        j = 0;
        for (; j < size - 2; j++) {
            // printf("%d ", arr[j]);
            if (increasing && (temp_ptr[j] - temp_ptr[j + 1]) > 0) {
                printf("increasing violation\n");
                ret = 0;
                break;
            } else if (!increasing && (temp_ptr[j] - temp_ptr[j + 1]) < 0) {
                printf("increasing violation\n");
                ret = 0;
                break;
            }

            if (abs(temp_ptr[j] - temp_ptr[j + 1]) < 1 || abs(temp_ptr[j] - temp_ptr[j + 1]) > 3) {
                printf("bad\n");
                ret = 0;
                break;
            }       

            ret = 1;
        }    

        increasing = 1;
        if(ret) return 1;
    }

    return ret;
}