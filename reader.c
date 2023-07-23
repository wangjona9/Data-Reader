#include "homestats.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("This program will read in the rows line for line of a file with a table of a variable\n"
            "and print their mean, median and mode to an output file.\n"
            "Each row must have a 2 letter-code for the state (Either CA, NY, NJ, or PA),\n"
            "and the home's price (in thousands), size, beds, and baths respectively."
            "The program will then ask the user for their state of interest and print the homes of the"
            "requested state onto the screen\n\n");

    if (argc < 3) { // Check if the correct arguments were inputted during compilation
        printf("Not enough arguments were provided"); // Print error message given too few arguments
        return 1;
    }

    Home_t *homes; 
    homes = malloc((sizeof(Home_t)) * MAX_HOMES); // Memory allocation for homes definition
    
    /* reads the number of homes from a file specified by the first 
       command line argument (argv[1]) and stores the result in the 
       integer variable num_homes */
    int num_homes = read_homes_from_file(argv[1], homes); 
    if (num_homes < 0) {
        return 1;
    }

    // Calculates the overall statistics of all the homes
    float mean;
    float median;
    int mode;
    calculate_statistics(homes, num_homes, &mean, &median, &mode);

    // Opens the output file
    FILE* out_fp = fopen(argv[2], "w");
    if (out_fp == NULL) {
        printf("Error: could not open file %s\n", argv[2]);
        return 1;
    }
    setvbuf(out_fp, NULL, _IONBF, 0); //Ensures the code will print to the output file

    // Prints the number of homes and overall statistics to output file
    fprintf(out_fp, "Number of homes: %d\n", num_homes);
    fprintf(out_fp, "Average home price (in thousands): $%.2f\n", mean);
    fprintf(out_fp, "Median home price (in thousands): $%.2f\n", median);
    fprintf(out_fp, "Mode home price (in thousands): $%d\n", mode);
    //fflush(out_fp);

    // Calculates the statistics for each state and print to output file
    char states[4][3] = {"CA", "NY", "NJ", "PA"};
    Home_t *state_homes;
    
    for (int i = 0; i < 4; i++) { //loop through the 4 state options
        int state_count = 0;
        float state_mean;
        float state_median;
        int state_mode;
        for (int j = 0; j < num_homes; j++) {
            if (strcmp(homes[j].state, states[i]) == 0) {
                state_count++;
            }
        }

        //checks if there are any homes in the current state being analyzed
        if (state_count > 0) { 
            state_homes = malloc((sizeof(Home_t)) * state_count);
            int k = 0;

            //loops through each home in the original homes array. 
            for (int j = 0; j < num_homes; j++) { 
                if (strcmp(homes[j].state, states[i]) == 0) {
                    state_homes[k++] = homes[j]; 
                }
            }

            //call calculate_stats function and print the stats for each state
            calculate_statistics(state_homes, state_count, &state_mean, &state_median, &state_mode);
            fprintf(out_fp, "\nStatistics for %s:\n", states[i]);
            fprintf(out_fp, "Number of homes: %d\n", state_count);
            fprintf(out_fp, "Average home price (in thousands): $%.2f\n", state_mean);
            fprintf(out_fp, "Median home price (in thousands): $%.2f\n", state_median);
            fprintf(out_fp, "Mode home price (in thousands): $%d\n", state_mode);
            free(state_homes);
        }
    }
      // Prints the homes by user-requested state to stdout
    print_homes_by_state(homes, num_homes);

    // Close output file and deallocate the memory of homes
    fclose(out_fp);
    free(homes);

    return 0;
}