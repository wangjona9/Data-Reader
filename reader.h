#ifndef READER_H
#define READER_H

//Max amount of homes for dataset definition
#define MAX_HOMES 1000
#define MAX_STATE_LEN 2

typedef struct {
    char state[MAX_STATE_LEN + 1];
    float price;
    float size;
    float beds;
    float baths;
} Home_t;


/* read_homes_from_file(const char* filename, Home_t homes[])
 *Preconditions: The homes argument is a valid array of struct 'Home' objects
 *Postconditions: Opens and reads the file or prints an error message if not
 * Reads the input file line by line, storing the values until 
 * the EOF is reached.
 */
int read_homes_from_file(const char* filename, Home_t homes[]);

/* int compare_floats(const void* a, const void* b)
 *Preconditions: Takes two arguments (a, b) which must be floats
 *Postconditions: returns true if the floats are equal and returns false if not
 * Returns a boolean value indicating if the floats are equal or not
 */
int compare_floats(const void* a, const void* b);

/* calculate_statistics(Home_t homes[], int num_homes, float* mean, float* median, int* mode)
 *Preconditions: the input 'numbers' list must be non-empty and have no non-numeric values
 *Postconditions: returns a tuple of 5 numeric values in order
 * Prints the mean, median, and mode of the input numbers in order
 */
void calculate_statistics(Home_t homes[], int num_homes, float* mean, float* median, int* mode);

/* void print_homes_by_state(Home_t homes[], int num_homes)
 *Preconditions: Must be a list of dictionaries containing the 2-letter state code for each home
 *Postconditions: prints the details of each home in a specific format
 * Prints the homes by user-requested state to stdout
 */
void print_homes_by_state(Home_t homes[], int num_homes);

#endif