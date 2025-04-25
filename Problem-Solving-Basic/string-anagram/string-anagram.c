#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Complete the 'stringAnagram' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY dictionary
 *  2. STRING_ARRAY query
 */

/*
 * Algorithm:
 * 1. Create a hash table to store sorted words from the dictionary:
 *    a. For each word in the dictionary, sort its characters
 *    b. Use the sorted word as a key, and count how many words map to the same sorted form
 * 2. For each query word:
 *    a. Sort the query word
 *    b. Look up the sorted word in the hash table
 *    c. Return the count of matching words (or 0 if none found)
 *
 * Note: A hash table is used for efficient lookups. Two words are anagrams if they have the same sorted order.
 *
 * Time Complexity: O(n*m log m + q*k log k) where:
 * - n is the number of dictionary words
 * - m is the maximum length of a dictionary word
 * - q is the number of query words
 * - k is the maximum length of a query word
 * Space Complexity: O(n) for storing the hash table
 */

// Function to sort a string
void sortString(char *str)
{
    int n = strlen(str);
    char temp;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (str[i] > str[j])
            {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

// Structure for dictionary entries
struct DictEntry
{
    char *sorted_word;
    int count;
};

// Simple hash function for strings
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int *stringAnagram(int dictionary_count, char **dictionary, int query_count, char **query)
{
    // Create a structure to store dictionary entries
    const int TABLE_SIZE = 10007; // Prime number for hash table
    struct DictEntry **table = (struct DictEntry **)calloc(TABLE_SIZE, sizeof(struct DictEntry *));

    // Process dictionary words
    for (int i = 0; i < dictionary_count; i++)
    {
        // Create a copy to sort
        int len = strlen(dictionary[i]);
        char *sorted = (char *)malloc((len + 1) * sizeof(char));
        strcpy(sorted, dictionary[i]);
        sortString(sorted);

        // Hash the sorted word
        unsigned long h = hash(sorted) % TABLE_SIZE;

        // Find if this sorted word already exists in our table
        int found = 0;
        struct DictEntry *entry = table[h];
        while (entry != NULL)
        {
            if (strcmp(entry->sorted_word, sorted) == 0)
            {
                entry->count++;
                found = 1;
                break;
            }
            entry = entry->count > 0 ? (struct DictEntry *)entry->sorted_word : NULL; // Use count field as next pointer
        }

        // If not found, add new entry
        if (!found)
        {
            struct DictEntry *new_entry = (struct DictEntry *)malloc(sizeof(struct DictEntry));
            new_entry->sorted_word = sorted;
            new_entry->count = 1;
            // Insert at the head of the chain
            if (table[h] != NULL)
            {
                entry = (struct DictEntry *)table[h]->sorted_word;
                table[h]->sorted_word = (char *)new_entry;
            }
            else
            {
                table[h] = new_entry;
            }
        }
        else
        {
            free(sorted); // We don't need this copy
        }
    }

    // Process queries
    int *result = (int *)calloc(query_count, sizeof(int));

    for (int i = 0; i < query_count; i++)
    {
        // Sort the query word
        int len = strlen(query[i]);
        char *sorted = (char *)malloc((len + 1) * sizeof(char));
        strcpy(sorted, query[i]);
        sortString(sorted);

        // Look up in the hash table
        unsigned long h = hash(sorted) % TABLE_SIZE;
        struct DictEntry *entry = table[h];

        while (entry != NULL)
        {
            if (strcmp(entry->sorted_word, sorted) == 0)
            {
                result[i] = entry->count;
                break;
            }
            entry = entry->count > 0 ? (struct DictEntry *)entry->sorted_word : NULL;
        }

        free(sorted);
    }

    // Clean up the hash table
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct DictEntry *entry = table[i];
        while (entry != NULL)
        {
            struct DictEntry *next = entry->count > 0 ? (struct DictEntry *)entry->sorted_word : NULL;
            free(entry->sorted_word);
            free(entry);
            entry = next;
        }
    }
    free(table);

    return result;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int dictionary_count;
    scanf("%d", &dictionary_count);

    char **dictionary = (char **)malloc(dictionary_count * sizeof(char *));
    for (int i = 0; i < dictionary_count; i++)
    {
        dictionary[i] = (char *)malloc(1001 * sizeof(char));
        scanf("%s", dictionary[i]);
    }

    int query_count;
    scanf("%d", &query_count);

    char **query = (char **)malloc(query_count * sizeof(char *));
    for (int i = 0; i < query_count; i++)
    {
        query[i] = (char *)malloc(1001 * sizeof(char));
        scanf("%s", query[i]);
    }

    int *result = stringAnagram(dictionary_count, dictionary, query_count, query);

    for (int i = 0; i < query_count; i++)
    {
        fprintf(fptr, "%d\n", result[i]);
        free(query[i]);
        free(dictionary[i]);
    }
    fprintf(fptr, "\n");

    free(dictionary);
    free(query);
    free(result);

    fclose(fptr);

    return 0;
}