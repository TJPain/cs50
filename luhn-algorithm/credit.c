#include <cs50.h>
#include <stdio.h>

void card_type(long number, long multiplier, int length);

int main(void)
{
    long number;
    int length = 0;
    // ask for credit card number and ensure that it is at least 13 digits
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1000000000 || number >= 10000000000000000);

    // set temp variable to calculate card number length
    long tmp = number;
    // calculate the number of digits in the card number
    while (tmp != 0)
    {
        tmp /= 10;     // n = n/10
        length++;
    }

    bool isOdd = false;
    long multiplier = 1;
    int digit;
    int sum = 0;
    int test;
    // loop backwards through number and handle the odd and even digits
    for (int i = length - 1; i >= 0; i--)
    {
        // get the current digit
        digit = (number / multiplier) % 10;
        // if it is an odd digit double it and add to sum
        if (isOdd == true)
        {
            // handle the use case where the double is 10 or more
            digit = digit * 2;
            sum += digit / 10;
            sum += digit % 10;
        }
        else
        {
            // add the even digits to the sum
            sum += digit;
        }
        // increase the multipler to get the next digit on the next loop
        multiplier = multiplier * 10;
        // toggle the isOdd boolean for the next loop
        isOdd = !isOdd;
    }
    test = sum % 10;

    if (test == 0)
    {
        // if the test is 0 find the card type
        card_type(number, multiplier, length);
    }
    // if the test is not zero, it is invalid
    else
    {
        printf("INVALID\n");
    }
}

void card_type(long number, long multiplier, int length)
{
    // get the last used multiplier and divide by 10 to get digit one
    long newMultiplier = multiplier / 10;
    // use modulo and the multiplier to get digit 1
    int digit1 = (number / newMultiplier) % 10;
    // reduce the multiplier to get digit 2
    newMultiplier = newMultiplier / 10;
    // use modulo and the multiplier to get digit 2
    int digit2 = (number / newMultiplier) % 10;
    // check the 2 digits and print the card type
    if (digit1 == 3 && (digit2 == 4 || digit2 == 7) && length == 15)
    {
        printf("AMEX\n");
    }
    else
    {
        if (digit1 == 4 && (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        else
        {
            if (digit1 == 5 && (digit2 == 1 || digit2 == 2 || digit2 == 3 || digit2 == 4 || digit2 == 5) && length == 16)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                // if the digits don't match any of the above, the card is invalid
                printf("INVALID\n");
            }
        }
    }
}