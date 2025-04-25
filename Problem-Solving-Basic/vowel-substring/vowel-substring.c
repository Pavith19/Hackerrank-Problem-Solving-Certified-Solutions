#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Complete the 'findSubstring' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER k
 */

/*
 * Algorithm:
 * 1. Define a sliding window of size k and count vowels in this window
 * 2. Initialize first window by counting vowels in first k characters
 * 3. Slide the window through the string:
 *    a. Add new character (rightmost in window)
 *    b. Remove old character (leftmost in previous window)
 *    c. Check if current window has more vowels than the best found so far
 * 4. Return the substring with maximum vowels, or "Not found!" if no vowels exist
 *
 * Time Complexity: O(n) where n is the length of string s
 * Space Complexity: O(k) for storing the result substring
 */

char *findSubstring(char *s, int k)
{
    char vowels[] = "aeiou";
    int len = strlen(s);
    int best = 0, ans = 0;
    int i, j;

    // Initialize the first window
    int cur = 0;
    for (i = 0; i < k && i < len; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (s[i] == vowels[j])
            {
                cur++;
                break;
            }
        }
    }

    best = cur;

    // Slide the window
    for (i = k; i < len; i++)
    {
        // Add new character
        for (j = 0; j < 5; j++)
        {
            if (s[i] == vowels[j])
            {
                cur++;
                break;
            }
        }

        // Remove old character
        for (j = 0; j < 5; j++)
        {
            if (s[i - k] == vowels[j])
            {
                cur--;
                break;
            }
        }

        if (cur > best)
        {
            best = cur;
            ans = i - k + 1;
        }
    }

    // Allocate memory for result string
    char *result = (char *)malloc((k + 1) * sizeof(char));
    if (best > 0)
    {
        strncpy(result, &s[ans], k);
        result[k] = '\0';
    }
    else
    {
        strcpy(result, "Not found!");
    }

    return result;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char *s = malloc(200001 * sizeof(char));
    scanf("%s", s);

    int k;
    scanf("%d", &k);

    char *result = findSubstring(s, k);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);
    free(s);
    free(result);

    return 0;
}