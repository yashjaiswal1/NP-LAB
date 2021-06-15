#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char *substring(char string[], int low, int high)
{
    int current = low;
    char result[100];
    while (current < high)
    {
        result[current] = string[current];
        current += 1;
    }
    result[current] = '\0';
    return result;
}

char *xor_operation(char *a, char *b)
{
    char result[100];
    int n = strlen(b);
    int counter = 0;
    int i;
    for (i = 1; i < n; i++)
    {
        if (a[i] == b[i])
        {
            result[counter] = '0';
            counter += 1;
        }
        else
        {
            result[counter] = '1';
            counter += 1;
        }
    }
    result[counter] = '\0';
    return result;
}

char *binary_division(char divisor[], char divident[])
{
    int window_size = strlen(divisor);
    char *temp = substring(divident, 0, window_size);
    char str_zero_div[100];
    int i;

    int n = strlen(divident);
    while (window_size < n)
    {
        if (temp[0] == '1')
        {
            temp = strcat(xor_operation(divisor, temp), &divident[window_size]);
        }
        else
        {
            for (i = 0; i < window_size; i++)
            {
                str_zero_div[i] = '0';
            }
            str_zero_div[i] = '\0';
            temp = strcat(xor_operation(str_zero_div, temp), &divident[window_size]);
        }
        window_size += 1;
    }

    if (temp[0] == '1')
    {
        temp = xor_operation(divisor, temp);
    }
    else
    {
        for (i = 0; i < window_size; i++)
        {
            str_zero_div[i] = '0';
        }
        str_zero_div[i] = '\0';
        temp = xor_operation(str_zero_div, temp);
    }
    printf("rem = %s\n", temp);
    return temp;
}

void main()
{

    char original_data[100], generator_poly[50];
    printf("Enter the original data to be transmitted");
    gets(original_data);
    printf("Enter the bit-pattern for the generator polynomial");
    gets(generator_poly);

    // append zeros to the end of the original data
    int n = strlen(generator_poly);
    int int_modified_data = atoi(original_data) * pow(10, n - 1);
    char modified_data[100];
    sprintf(modified_data, "%d", int_modified_data);

    // char *ans = substring(modified_data, 0, 4);
    // // printf("%s", ans);
    // for (int i = 0; i < 6; i++)
    // {
    //     printf("%c", ans[i]);
    // }
    // binary division
    char *remainder = binary_division(generator_poly, modified_data);

    // append data to original polynomial
    char *codeword = strcat(original_data, remainder);
    printf("\nRemainder = %s\n", remainder);
    printf("Encoded Data = %s\n", codeword);
}