#include "reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_homes_from_file(const char *filename, Home_t homes[])
{
    FILE *fp;
    int line = 1;   // Count lines
    int counth = 0; // Count homes
    int match;      // Count of columns
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s\n", filename);
        return -1;
    }

    // Check to see if the maximum number of homes is reached
    while (counth < MAX_HOMES)
    {
        match = fscanf(fp, "%s\t%g\t%g\t%g\t%g", homes[counth].state, &homes[counth].price, &homes[counth].size, &homes[counth].beds, &homes[counth].baths);
        if (match == 5) // checks if each row has 5 values separated by a tab
        {
            // Check if a house's information value is not zero or negative
            if (homes[counth].price <= 0 || homes[counth].size <= 0 || homes[counth].beds <= 0 || homes[counth].baths <= 0)
            {
                printf("Error: invalid value in line %d\n", line); // Print if there is an invalid value and specifies the line number
            }
            else
            {
                counth++;
            }
            fscanf(fp, "%*[^\n]\n"); // Move the file pointer to the new line
            line++; 
        }
        else if (match == EOF) // Check if the EOF is reached
        {
            break;
        }
        else
        {
            fscanf(fp, "%*[^\n]\n"); // Move the file pointer to the next line
            if (line != 1)
            {
                // print issues with a specified line
                printf("Homes were skipped due to format issues at line %d\n" 
                      "(non-numerical values except for the state id will interfere with the read-in of the previous line)\n\n", line); 
            }
            line++;
        }
    }
    printf("Number of homes: %d \n", counth); // Print the number of homes that were read in
    fclose(fp); // Close the file
    return counth;
}

// This function is used as the comparator function for qsort() later.
int compare_floats(const void *a, const void *b)
{
    // Converting the void pointers to float pointers, dereference them to get the float values.
    float fa = *(const float *)a;
    float fb = *(const float *)b;

    /* Comparing the float values, returning an integer based on the comparison result.
       If fa is greater than fb return 1.
       If fa is less than fb return -1.
       If fa is equal to fb return 0. */
    return (fa > fb) - (fa < fb);
}

void calculate_statistics(Home_t homes[], int num_homes, float *mean, float *median, int *mode)
{
    // Calculate the mean, median, and mode of the home prices
    float total_price = 0.0;
    for (int i = 0; i < num_homes; i++) // Loop through homes
    {
        total_price += homes[i].price; // Repeatedly add to the total of prices by looping
    }
    *mean = total_price / num_homes; // Calulation for the mean

    float prices[num_homes];
    for (int i = 0; i < num_homes; i++) // Loop through homes
    {
        prices[i] = homes[i].price; // Repeatedly add to the total of a state's prices by looping
    }
    qsort(prices, num_homes, sizeof(float), compare_floats); // Call qsort with compare_floats

    if (num_homes % 2 == 0)
    {
        *median = (prices[num_homes / 2 - 1] + prices[num_homes / 2]) / 2.0; // Calculate median
    }
    else
    {
        *median = prices[(int)(num_homes / 2)]; // Accomodate for truncated int values during division
    }

    int max_count = 0; // Initialize the maximum count to 0
    for (int i = 0; i < num_homes; i++) // Loop through homes
    {
        int count = 0; // Initialize the count for this home to 0
        for (int j = 0; j < num_homes; j++) // Loop through homes again
        {
            if (homes[j].price == homes[i].price) // Check if this home has the same price as the current home
            {
                count++; // Increment the count if there is a match
            }
        }
        if (count > max_count) // Check if the count for this home is greater than the maximum count
        {
            max_count = count; // Update the maximum count
            *mode = homes[i].price; // Set the mode to the price of this home
        }
    }
}

void print_homes_by_state(Home_t homes[], int num_homes)
{
    char state[3];
    printf("Enter a state (CA, NY, NJ, or PA): "); // Prompt user to input a state id
    scanf("%s", state); // Store input
    printf("Homes in %s:\n", state);
    for (int i = 0; i < num_homes; i++) // Loop through homes
    {
        if (strcmp(homes[i].state, state) == 0) // Check if the information of a state id corresponds to a house
        {
            // Print the information for each home
            printf("Home %d:\n", i + 1);
            printf("State: %s\n", homes[i].state);
            printf("Price (in thousands): %g\n", homes[i].price);
            printf("Size: %g\n", homes[i].size);
            printf("Beds: %g\n", homes[i].beds);
            printf("Baths: %g\n", homes[i].baths);
            printf("\n");
        }
    }
} 