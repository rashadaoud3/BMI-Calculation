// Rasha Daoud - 1210382
// OS Project - Part 1: Naive Approache 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PEOPLE 1000

typedef struct {// for each person
    char gender[20];
    double height;
    double weight;
} Person;

double calculate_bmi(double weight, double height) {
    height = height / 100;// convert from centimeter to meter
    return weight / (height * height);// BMI Function
}

int main() {
    clock_t start_time, end_time;//To calculate the Excution Time
    double execution_time;

    start_time = clock();
    // Open the file
    FILE *file = fopen("bmi.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    Person people[MAX_PEOPLE];
    int num_people = 0;

    // Skip header row
    fgets(line, sizeof(line), file);

    // Read data from each line until end of file (EOF)
    while (fgets(line, sizeof(line), file) != NULL && num_people < MAX_PEOPLE) {
        char gender[20];
        double height, weight;
        if (sscanf(line, "%s %lf %lf", gender, &height, &weight) != 3) {
            printf("Invalid data format in line: %s\n", line);
            continue;
        }
        strcpy(people[num_people].gender, gender);
        people[num_people].height = height;
        people[num_people].weight = weight;
        num_people++;
    }
    fclose(file);

    if (num_people == 0) {
        printf("No valid data found in the file.\n");
        return 1;
    }

    // Calculate average BMI for all people 
    double total_bmi = 0.0;
    for (int i = 0; i < num_people; i++) {
        total_bmi += calculate_bmi(people[i].weight, people[i].height);
    }
    double average_bmi = total_bmi / num_people;

    end_time = clock();
    //calculates the execution time of the program by taking the difference..
    //..between the end time and the start time, converting it to seconds
    execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Average BMI: %.2f\n", average_bmi);
    printf("Execution Time: %.6f seconds\n", execution_time);

    return 0;
}
