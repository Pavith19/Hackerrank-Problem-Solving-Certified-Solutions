#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Complete the 'decryptPassword' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

/*
 * Algorithm:
 * 1. The password is encrypted with three operations:
 *    a. Digits are placed at the beginning and replaced with '0' in the original position
 *    b. Characters around '*' are swapped
 *    c. '*' is added to mark the swapped positions
 *
 * To decrypt:
 * 1. Identify the digits at the beginning of the encrypted password
 * 2. Replace '0's in the string with those digits in reverse order
 * 3. For each '*', swap the two preceding characters
 * 4. Remove placeholder characters (digits at beginning and '*')
 *
 * Time Complexity: O(n) where n is the length of the encrypted password
 * Space Complexity: O(n) for storing the decrypted password
 */

char *decryptPassword(char *s)
{
    int len = strlen(s);
    char *result = (char *)malloc((len + 1) * sizeof(char));
    char *temp = (char *)malloc((len + 1) * sizeof(char));

    strcpy(temp, s);

    int i = 0;
    // Find where numeric prefix ends
    while (i < len && temp[i] >= '1' && temp[i] <= '9')
    {
        i++;
    }

    // Replace 0's with corresponding digits
    int j;
    int digit_index = i - 1;
    for (j = i; j < len; j++)
    {
        if (temp[j] == '0' && digit_index >= 0)
        {
            temp[j] = temp[digit_index];
            temp[digit_index] = ' '; // Mark as used
            digit_index--;
        }
    }

    // Swap characters around '*'
    for (j = i; j < len; j++)
    {
        if (temp[j] == '*')
        {
            char t = temp[j - 1];
            temp[j - 1] = temp[j - 2];
            temp[j - 2] = t;
        }
    }

    // Build result string by copying non-space and non-* characters
    int result_index = 0;
    for (j = i; j < len; j++)
    {
        if (temp[j] != ' ' && temp[j] != '*')
        {
            result[result_index++] = temp[j];
        }
    }

    result[result_index] = '\0';
    free(temp);
    return result;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char *s = (char *)malloc(10001 * sizeof(char));
    scanf("%s", s);

    char *result = decryptPassword(s);

    fprintf(fptr, "%s\n", result);

    free(s);
    free(result);
    fclose(fptr);

    return 0;
}