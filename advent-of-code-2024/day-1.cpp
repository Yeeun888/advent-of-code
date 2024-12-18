/**
 * @file day-1.cpp
 * @author Maximus Philisp Chan
 * @brief  Day 1 solution. Get two lists and see the difference between them. What
 * this functionally is ordering them then adding the differences togehter
 * 
 * Solution started with 64 bit numbers only 
 * 
 * @version 0.1
 * @date 2024-12-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>

#define MAX_SIZE 2048
#define MAX_DIGITS 100000

void merge_array(int array[], int lo, int mid, int hi) {
    int *temp_arr = (int *)malloc(sizeof(int) * (hi - lo + 1));

    int temp_index = 0;
    int i = lo;  //Left index
    int j = mid + 1; //Right index

    while(i <= mid && j <= hi) {
        if(array[i] < array[j]) { //Left has smaller element
            temp_arr[temp_index] = array[i];
            temp_index += 1;
            i += 1;
        } else { //Right has smaller element
            temp_arr[temp_index] = array[j];
            temp_index += 1;
            j += 1;
        }
    }

    //Pop the remaining elements into array
    //i.e left or right has run out of elements
    while(i <= mid) {temp_arr[temp_index] = array[i]; ++i; ++temp_index; };
    while(j <= hi) {temp_arr[temp_index] = array[j]; ++j; ++temp_index; };

    //Copy temp_arr back into array
    temp_index = 0;
    while(lo <= hi) {
        array[lo] = temp_arr[temp_index];
        temp_index++;
        lo++;
    } 
}

void merge_sort(int array[], int lo, int hi) {
    //Recursive exit statement
    if(lo >= hi) return;

    int midpoint = ((lo + hi) / 2);
    merge_sort(array, lo, midpoint);
    merge_sort(array, midpoint + 1, hi);

    merge_array(array, lo, midpoint, hi);
}

int main(int argv, char** argc) {
    //Arbitrary malloc allocation for large amounZNt of variables
    int* left_arr = (int *)malloc(sizeof(int) * MAX_SIZE);
    int* right_arr = (int *)malloc(sizeof(int) * MAX_SIZE);

    //Semi chatgpt file reading code
    std::ifstream inputFile("day-1-input.txt");
    if(!inputFile) {
        std::cout << "Error on file read \n";
        return 1;
    }

    // ------------------- PART I --------------------

    //First get all of our input
    int array_length = 0;
    while(inputFile >> left_arr[array_length] >> right_arr[array_length]) {
        ++array_length;
    }
    int final_index = array_length - 1;

    // if(array_index = 0) { // Necessary check but disable if no need for performance
    //     std::cout << "0\n";
    //     return 0;
    // }

    merge_sort(left_arr, 0, final_index);
    merge_sort(right_arr, 0, final_index);

    int ans = 0;
    for(int i = 0; i < array_length; ++i) {
        ans += abs(left_arr[i] - right_arr[i]);
    }

    // Part 1 answer
    printf("ans: %d\n", ans);

    // ------------------- PART II -------------------

    int sim_score = 0;

    //Individual similarity scores of each number
    int* score_array = (int *)calloc(MAX_DIGITS, sizeof(int));
    for(int i = 0; i < array_length; ++i) {
        score_array[right_arr[i]] += 1; //Add one for each score
    }

    for(int i = 0; i < array_length; ++i) {
        sim_score += left_arr[i] * score_array[left_arr[i]]; //Add one for each score
    }
    
    printf("sim_score: %d\n", sim_score);

    return 0;
}

