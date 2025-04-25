#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Complete the 'nearlySimilarRectangles' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts 2D_LONG_INTEGER_ARRAY sides as parameter.
 */

/*
 * Algorithm:
 * 1. Two rectangles are "nearly similar" if their width-to-height ratios are the same
 * 2. For each rectangle, normalize its ratio by:
 *    a. Finding the GCD (greatest common divisor) of width and height
 *    b. Dividing both width and height by their GCD
 * 3. Use a hash table to group rectangles with the same normalized ratio
 * 4. For each group, calculate the number of pairs using the formula n*(n-1)/2
 *    where n is the number of rectangles in the group
 * 5. Sum up the pairs from all groups
 *
 * Optimization:
 * - Instead of calculating pairs afterward, we count them during insertion
 *   by adding the current count of matching ratios to our result
 *
 * Time Complexity: O(n * log(max(w,h))) where:
 * - n is the number of rectangles
 * - w, h are the maximum width and height values
 * - log term is from GCD calculation
 * Space Complexity: O(n) for the hash table
 */

// Calculate GCD (Greatest Common Divisor)
long gcd(long a, long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Structure for storing normalized ratios
struct Ratio
{
    long width;
    long height;
};

// Hash table entry
struct Entry
{
    struct Ratio ratio;
    int count;
    struct Entry *next;
};

// Simple hash function
unsigned long hash(long w, long h)
{
    return (w * 31 + h) % 10007; // Prime number
}

long nearlySimilarRectangles(int sides_rows, long **sides)
{
    const int TABLE_SIZE = 10007; // Prime number for hash table
    struct Entry **table = (struct Entry **)calloc(TABLE_SIZE, sizeof(struct Entry *));

    long result = 0;

    for (int i = 0; i < sides_rows; i++)
    {
        long w = sides[i][0];
        long h = sides[i][1];

        // Calculate GCD to normalize ratio
        long g = gcd(w, h);
        w /= g;
        h /= g;

        // Hash the normalized ratio
        unsigned long h_val = hash(w, h);

        // Check if this ratio already exists
        struct Entry *entry = table[h_val];
        int found = 0;

        while (entry != NULL)
        {
            if (entry->ratio.width == w && entry->ratio.height == h)
            {
                // Found matching ratio, add to count and calculate new pairs
                result += entry->count;
                entry->count++;
                found = 1;
                break;
            }
            entry = entry->next;
        }

        // If not found, add new entry
        if (!found)
        {
            struct Entry *new_entry = (struct Entry *)malloc(sizeof(struct Entry));
            new_entry->ratio.width = w;
            new_entry->ratio.height = h;
            new_entry->count = 1;
            new_entry->next = table[h_val];
            table[h_val] = new_entry;
        }
    }

    // Clean up the hash table
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct Entry *entry = table[i];
        while (entry != NULL)
        {
            struct Entry *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    free(table);

    return result;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int sides_rows, sides_columns;
    scanf("%d %d", &sides_rows, &sides_columns);

    long **sides = (long **)malloc(sides_rows * sizeof(long *));
    for (int i = 0; i < sides_rows; i++)
    {
        sides[i] = (long *)malloc(sides_columns * sizeof(long));
        for (int j = 0; j < sides_columns; j++)
        {
            scanf("%ld", &sides[i][j]);
        }
    }

    long result = nearlySimilarRectangles(sides_rows, sides);

    fprintf(fptr, "%ld\n", result);

    for (int i = 0; i < sides_rows; i++)
    {
        free(sides[i]);
    }
    free(sides);

    fclose(fptr);

    return 0;
}