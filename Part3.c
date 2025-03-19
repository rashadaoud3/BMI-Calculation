// Rasha Daoud - 1210382
// OS Project - Part 3: MultiThread Approache 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PEOPLE 1000
#define NUM_THREADS 4

typedef struct {
    char gender[20];
    double height;
    double weight;
} Person;

typedef struct {
    Person* people;
    int start_idx;
    int end_idx;
    double total_bmi;
} ThreadData;

double calculate_bmi(double weight, double height) {
    height = height / 100;
    return weight / (height * height);
}

void* thread_function(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->start_idx; i < data->end_idx; i++) {
        data->total_bmi += calculate_bmi(data->people[i].weight, data->people[i].height);
    }
    double average_bmi = data->total_bmi / (data->end_idx - data->start_idx);
    printf("Thread %ld: Average BMI: %.2f\n", pthread_self(), average_bmi);

    pthread_exit(NULL);
}

int main() {
    clock_t start_time, end_time;
    double execution_time;

    start_time = clock();

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

    // Read data from each line until end of file
    while (fgets(line, sizeof(line), file) != NULL && num_people < MAX_PEOPLE) {
        char gender[20];
        double height, weight;
        if (sscanf(line, "%s %lf%lf", gender, &height, &weight) != 3) {
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

    // Create an array of threads
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Calculate data chunk size for each thread
    int chunk_size = num_people / NUM_THREADS;
    int remainder = num_people % NUM_THREADS;

    // Create and start threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].people = people;
        thread_data[i].start_idx = i * chunk_size;
        thread_data[i].end_idx = thread_data[i].start_idx + chunk_size;
        if (i == NUM_THREADS - 1) {
            // Add remainder to the last chunk
            thread_data[i].end_idx += remainder;
        }
        thread_data[i].total_bmi = 0;

        pthread_create(&threads[i], NULL, thread_function, (void*)&thread_data[i]);
    }

    // Join threads and calculate total BMI
    double total_bmi = 0.0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_bmi += thread_data[i].total_bmi;
    }

    // Calculate average BMI
    double average_bmi = total_bmi / num_people;

    // Record the ending time
    end_time = clock();
    execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print results
    printf("Average BMI: %.2f\n", average_bmi);
    printf("Execution Time: %.6f seconds\n", execution_time);

    return 0;
}
