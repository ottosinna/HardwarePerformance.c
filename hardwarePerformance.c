#include <stdio.h>
#include <stdlib.h>

struct Instruction {
    float cpi;
    float count; // number of instructions
};

struct Performance {
    float averageCPI;
    float cpuTime;
    float MIPS;
};

struct Machine machine;
struct Machine {
    float clockRate;
    int classes; // instructio classes
    struct Instruction * instructions; // pointer
    struct Performance performance; 
};

void printMenu() {
printf("\n");
    printf(" Performance\n");
    printf("--------------------------------------------------\n");
    printf("1. Enter Parameters\n");
    printf("2. Print table of input Parameters\n");
    printf("3. Print Performance Table\n");
    printf("4. Exit Application\n");
    printf("\n");
}
void printMenu();
void enterParameters();
void printParameters();
void calculatePerformance();
void performanceTable(); // sus??
int main() {
    int choice;
    do {
        printMenu();
        printf("Enter options:\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                enterParameters();
                break;
            case 2:
                printParameters();
                break;
            case 3:
                performanceTable();
                break;
            case 4:
                printf("Exiting the app...\n");
                if (machine.instructions != NULL) {
                    free(machine.instructions);  //allocated memory
                }
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);
    return 0; //wont?
}

void calculatePerformance() {
    // collects total cycles &&instructions
    float totalCycles = 0; 
    float totalInstructions = 0;
    for (int i = 0; i < machine.classes; i++) { // loops all instruction classes
        //multiply by 1,000,000 to convert the instruction count from millions to the actual count
        totalCycles += machine.instructions[i].cpi * machine.instructions[i].count * 1000000; 
        totalInstructions += machine.instructions[i].count * 1000000; //instructions in millions to actual count
    }
    machine.performance.averageCPI = totalCycles / totalInstructions; //total cycles devided by total instructions
    //total cycles devided by clock rate and cancelling to get miliseconds by 1,000,000 dividing 1,000 
    machine.performance.cpuTime = totalCycles / (machine.clockRate * 1000.0);  
    //divide total instructions by cpu time divin=ding the same to get MIPS
    machine.performance.MIPS = totalInstructions / (machine.performance.cpuTime * 1000.0);
}

void enterParameters() {
    printf("Enter amount of instruction classes: ");
    scanf("%d", &machine.classes);
    
    //allocate memory for instructions array
    machine.instructions = (struct Instruction*)malloc(machine.classes * sizeof(struct Instruction));
    if (machine.instructions == NULL) {
        printf("Memory allocation failed. Exiting...\n"); //checks in/completion
        exit(1);
    }

    printf("Enter frequency(Clock Rate) of the machine (MHz): ");
    scanf("%f", &machine.clockRate);
    for(int i = 0; i < machine.classes; i++) {
        printf("Enter CPI of class %d: ", i + 1);
        scanf("%f", &machine.instructions[i].cpi);
        printf("Enter count of class %d (millions): ", i + 1);
        scanf("%f", &machine.instructions[i].count);
    }
}
// prints the calculated parameters
void printParameters() {
    printf("--------------------------------------------------\n");
    printf("| Class | CPI    | Count  |\n");
    printf("--------------------------------------------------\n");
    for(int i = 0; i < machine.classes; i++) { //loops IClasses -->prints
        printf("| %d     | %.2f   | %.2f   |\n", i + 1, machine.instructions[i].cpi, machine.instructions[i].count);
    } //floated 2 dec for aesthetics and to loo like performance table floats
    printf("--------------------------------------------------\n");
    printf("\n");
}

//print for calculation performance meterics
void performanceTable() {
    calculatePerformance();
    printf("--------------------------------------------------\n");
    printf("| Performance  | Value     |\n");
    printf("--------------------------------------------------\n");
    printf("| Average CPI  | %.2f      |\n", machine.performance.averageCPI);
    printf("--------------------------------------------------\n");
    printf("| CPU Time(ms) | %.2f     |\n", machine.performance.cpuTime);
    printf("--------------------------------------------------\n");
    printf("| MIPS         | %.2f      |\n", machine.performance.MIPS);
    printf("--------------------------------------------------\n");
    printf("\n");
}