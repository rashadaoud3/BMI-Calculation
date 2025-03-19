# Operating Systems Project 1: BMI Calculation with Parallelism

## Project Overview
In this project, you will write a program to calculate the average BMI (Body Mass Index) for a provided dataset. The goal is to compare three different approaches for parallelism and measure the execution time for each:

1. **Naive Approach**: A single-threaded program that does not use any child processes or threads.
2. **Multiprocessing Approach**: A program that uses multiple child processes running in parallel.
3. **Multithreading Approach**: A program that uses multiple joinable threads running in parallel.

## Requirements:
- You must work on a computer with at least 4 CPU cores. If using a virtual machine, ensure it has at least 4 cores allocated.
- The dataset for BMI calculation is provided in the project description.
- The program should calculate the average BMI from the dataset using all three approaches and measure the execution time for each.

## Deliverables:
- **Program Code**: The implementation of all three approaches.
- **Project Report**: A detailed report that includes:
  - The APIs and functions used for multiprocessing and multithreading.
  - An analysis according to Amdahl’s law:
    - Percentage of the serial part of the code.
    - Maximum speedup based on the available number of cores.
    - Optimal number of child processes or threads.
  - A comparison table of performance for the three approaches.
  - A discussion on the differences in performance and conclusion.

## Phases:

### Phase 1: Naive Approach 
- Implement the BMI calculation program without using parallelism.
- Measure and record the execution time of this approach.

### Phase 2: Multiprocessing Approach 
- Modify the program to use multiprocessing.
- Run the program with different numbers of processes (e.g., 2, 4, 8) and measure the execution times.
- Record the results and compare the performance.

### Phase 3: Multithreading Approach
- Modify the program to use multithreading.
- Run the program with different numbers of threads (e.g., 2, 4, 8) and measure the execution times.
- Record the results and compare the performance.

### Phase 4: Analysis and Report 
- Analyze the results using Amdahl’s law and calculate the maximum speedup based on the number of cores.
- Create a table comparing the performance of all three approaches (Naive, Multiprocessing, Multithreading).
- Write the final report, summarizing your findings, performance comparisons, and conclusions.

## Evaluation Criteria:
- Correct implementation of the three approaches.
- Clear and accurate analysis using Amdahl’s law.
- Well-documented code and report.
- Performance comparison table and well-reasoned conclusions.

## Technologies Used:
- Programming Language: [e.g., C]
- Libraries/Frameworks: [e.g., multiprocessing, threading, etc.]
