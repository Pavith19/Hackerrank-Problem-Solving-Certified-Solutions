#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Complete the 'mostActive' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY customers as parameter.
 */

/*
 * Algorithm:
 * 1. Count the number of transactions for each unique customer:
 *    a. Iterate through all customer transactions
 *    b. For each customer, check if we've seen them before
 *    c. If not, add them to our unique customers list
 *    d. If yes, increment their transaction count
 * 2. Filter customers with at least 5% of the total transactions:
 *    a. Calculate the threshold: 5% of total transactions
 *    b. Include only customers whose transaction count exceeds this threshold
 * 3. Sort the filtered list of active traders alphabetically
 * 4. Return the sorted list of active traders
 *
 * Time Complexity:
 * - O(n²) for counting unique customers in the worst case
 * - O(m log m) for sorting the active traders list
 * Where n is the total number of transactions, m is the number of unique customers
 *
 * Space Complexity: O(m) where m is the number of unique customers
 */

// Structure to store customer information
typedef struct
{
    char *name;
    int count;
} CustomerInfo;

// Comparison function for qsort (for alphabetical sorting)
int compareCustomers(const void *a, const void *b)
{
    return strcmp(((CustomerInfo *)a)->name, ((CustomerInfo *)b)->name);
}

char **mostActive(int customers_count, char **customers, int *result_count)
{
    const int MAX_CUSTOMERS = 10000; // Maximum number of unique customers
    CustomerInfo *unique_customers = (CustomerInfo *)malloc(MAX_CUSTOMERS * sizeof(CustomerInfo));
    int unique_count = 0;

    // Count occurrences of each customer
    for (int i = 0; i < customers_count; i++)
    {
        // Check if customer already exists in our array
        int found = 0;
        for (int j = 0; j < unique_count; j++)
        {
            if (strcmp(unique_customers[j].name, customers[i]) == 0)
            {
                unique_customers[j].count++;
                found = 1;
                break;
            }
        }

        // If not found, add as a new customer
        if (!found)
        {
            unique_customers[unique_count].name = strdup(customers[i]);
            unique_customers[unique_count].count = 1;
            unique_count++;
        }
    }

    // Create result array
    char **result = (char **)malloc(unique_count * sizeof(char *));
    *result_count = 0;

    // Filter customers with >= 5% of transactions
    float threshold = 0.05 * customers_count;
    for (int i = 0; i < unique_count; i++)
    {
        if (unique_customers[i].count >= threshold)
        {
            result[*result_count] = strdup(unique_customers[i].name);
            (*result_count)++;
        }
    }

    // Create a new array with just the active traders for sorting
    CustomerInfo *active_traders = (CustomerInfo *)malloc(*result_count * sizeof(CustomerInfo));
    for (int i = 0; i < *result_count; i++)
    {
        active_traders[i].name = result[i];
    }

    // Sort active traders alphabetically
    qsort(active_traders, *result_count, sizeof(CustomerInfo), compareCustomers);

    // Update result array with sorted names
    for (int i = 0; i < *result_count; i++)
    {
        result[i] = active_traders[i].name;
    }

    // Free memory
    for (int i = 0; i < unique_count; i++)
    {
        free(unique_customers[i].name);
    }
    free(unique_customers);
    free(active_traders);

    return result;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int customers_count;
    scanf("%d", &customers_count);

    char **customers = malloc(customers_count * sizeof(char *));
    for (int i = 0; i < customers_count; i++)
    {
        customers[i] = malloc(101 * sizeof(char)); // Assuming max length of 100
        scanf("%s", customers[i]);
    }

    int result_count;
    char **result = mostActive(customers_count, customers, &result_count);

    for (int i = 0; i < result_count; i++)
    {
        fprintf(fptr, "%s\n", result[i]);
        free(result[i]);
    }
    fprintf(fptr, "\n");

    for (int i = 0; i < customers_count; i++)
    {
        free(customers[i]);
    }
    free(customers);
    free(result);

    fclose(fptr);

    return 0;
}