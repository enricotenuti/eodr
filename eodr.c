#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int signum) {
    int pid = getpid();
    int fid = fork();
    if (!fid){
        printf("Received SIGTSTP (^Z). Exiting...\n");
        sleep(1);
        kill(pid, SIGKILL);
        exit(1);
    }
}

int main() {
    printf("Welcome to EoDr 1.0.\nIf ^C is not working use ^Z.\n");
    signal(SIGTSTP, sigint_handler);
    char scramble[256];
    int eomax = 6;
    int drmax = 10;
    char nissEo = '\0';
    char nissDr = '\0';
    char allCases = '\0';
    char outText = '\0';

    char outputFileName[] = "outputeo.txt";
    // Prompt the user to enter initial parameters
    while(eomax < 0 || eomax >= 6){
        printf("max EO: ");
        scanf("%d", &eomax);
        fflush(stdin);    
    }
    while(drmax < 0 || drmax >= 10){
        printf("max DR: ");
        scanf("%d", &drmax);
        fflush(stdin);  
    }
    while(nissEo != 'Y' && nissEo != 'N'){
        printf("eo with niss (Y or N): ");
        scanf("%c", &nissEo);
        fflush(stdin); 
    }
    while(nissDr != 'Y' && nissDr != 'N'){
        printf("dr with niss (Y or N, heavy task): ");
        scanf("%c", &nissDr);
        fflush(stdin); 
    }
    while(allCases != 'Y' && allCases != 'N'){
        printf("do you want to see all cases for eo (Y or N)? ");
        scanf("%c", &allCases);
        fflush(stdin); 
    }
    while(outText != 'Y' && outText != 'N'){
        printf("do you want to save DRs on a specific file (Y or N)? ");
        scanf("%c", &outText);
        fflush(stdin); 
    }
    char output2FileName[50];
    if(outText == 'Y') {
        printf("File name: ");
        fgets(output2FileName, sizeof(output2FileName), stdin);    
        output2FileName[strcspn(output2FileName, "\n")] = '\0';
    } else {
        strcpy(output2FileName, "outputdr.txt");
    }
    printf("Scramble: ");
    fgets(scramble, sizeof(scramble), stdin);

    // Remove the newline from the scramble string
        scramble[strcspn(scramble, "\n")] = '\0';
    scramble[strcspn(scramble, "\n")] = '\0';


    FILE *outputFile = fopen(outputFileName, "w");
    fclose(outputFile);
    outputFile = fopen(outputFileName, "r");
    FILE *output2File = fopen(output2FileName, "w");
    fclose(output2File);
    output2File = fopen(output2FileName, "a+");

    if (outputFile == NULL || output2File == NULL) {
        perror("Error opening output files");
        return 1;
    }

    char command[512];
    char line[256];
    char line2[256];
    char useNissEo[4] = "";
    char useNissDr[4] = "";
    char useAllCases[4] = "";
    char useOutText[4] = "";
    if (nissEo == 'Y') strcpy(useNissEo, "-N");
    if (nissDr == 'Y') strcpy(useNissDr, "-N");
    if (allCases == 'Y') strcpy(useAllCases, "-a");
    // Run the initial command and save the output to output2.txt
    printf("EO found: ");
    fflush(stdout);
    snprintf(command, sizeof(command), "nissy solve eo -c %s %s -M %d \"%s\"", useAllCases, useNissEo ,eomax,  scramble);
    system(command); 
    printf("Press Enter to continue.");
    fflush(stdout); // Flush the output buffer to ensure the message is displayed immediately
    // Wait for the user to press Enter
    while (getchar() != '\n');

    snprintf(command, sizeof(command), "nissy solve eo %s -p %s -M %d \"%s\" > %s", useAllCases, useNissEo ,eomax,  scramble, outputFileName);
    system(command);
    fseek(outputFile, 0, SEEK_SET);
    unsigned int i = 1;
    // Loop until there are lines in the output file
    while (fgets(line, sizeof(line), outputFile) != NULL) {
        // Remove the newline from the read line
        line[strcspn(line, "\n")] = '\0';
        // Build the command to run nissy with the above output
        snprintf(command, sizeof(command), "echo \"\n%d) DR for %s\" | tee -a %s\n",i, line, output2FileName);
        system(command);
        snprintf(command, sizeof(command), "nissy solve dr -p %s -M %d \"%s %s\" | tee -a %s\n", useNissDr, drmax, scramble, line, output2FileName);
        system(command);
        i++;
    }

    printf("\nDR analysis completed.\n");
    sleep(1);

    fclose(outputFile);
    fclose(output2File);

    return 0;
}
