// Rasha Daoud - 1210382
// OS Project - Part 2: MultiProcesses Approache 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PEOPLE 1000

typedef struct {// for each person
    char gender[20];
    double height;
    double weight;
} Person;

double calculate_bmi(double weight, double height) {
    height = height / 100;// convert the hieght from centimeter to meter
    return weight / (height * height);
}

int main() {
    clock_t start_time, end_time;// to calculate the Excution Time
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

    //Skip header row
    fgets(line, sizeof(line), file);

    //Read data from each line until end of file (EOF)
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

    //Number of child processes
    int num_processes = 4;

    //Calculate data chunk size for each child process
    int chunk_size = num_people / num_processes;
    int remainder = num_people % num_processes;

    //Create a pipe for communication between parent and child processes
    int pipefd[2];
    if (pipe(pipefd) == -1) {// creates the pipe using the pipe() system call
        perror("pipe");
        return 1;
    }

    // Fork child processes
    pid_t pid;
    for (int i = 0; i < num_processes; i++) {
        pid = fork();

        if (pid == -1) {
            printf("Error in forking process.\n");
            return 1;
        } else if (pid == 0) {//Child process
            // Calculate BMI for chunk of data
            double total_bmi = 0.0;
            int start_idx = i * chunk_size;
            int end_idx = start_idx + chunk_size;
            if (i == num_processes - 1) {
                // Add remainder to the last chunk
                end_idx += remainder;
            }
            for (int j = start_idx; j < end_idx; j++) {
                total_bmi += calculate_bmi(people[j].weight, people[j].height);
            }

            //Write the average BMI to the pipe
            double average_bmi = total_bmi / (end_idx - start_idx);
            close(pipefd[0]); //Close the read end of the pipe
            write(pipefd[1], &average_bmi, sizeof(double));
            close(pipefd[1]); //Close the write end of the pipe
            exit(0); //Exit child process
        }
    }

    //Parent process reads average BMI values from the pipe and calculates the total
    double totalB = 0.0;
    printf("Average BMI for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        double average_bmi;
        close(pipefd[1]); //Close the write end of the pipe in the parent process
        read(pipefd[0], &average_bmi, sizeof(double));
        printf("Process %d: Average BMI: %.2f\n", i, average_bmi);
        totalB += average_bmi;
    }

    // Record the ending time
    end_time = clock();
    execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("MultiProcesses: 4\n");
    printf("Total BMI= %.2f\n", totalB / num_processes);
    printf("Parent Process: Execution Time: %.6f seconds\n", execution_time);

    return 0;
}
