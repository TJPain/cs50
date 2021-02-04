#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool check_length(string key);
bool check_duplicates(string key);
bool check_characters(string key);
bool check_key(string key);
void substitute(string text, string key);
char get_caps(char character, string key);
char get_lower(char character, string key);

int main(int argc, string argv[])
{
    // check that there are the correct number of command line arguments
    if (argc != 2)
    {
        // error if not
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // if the correct number of command line arguments test the validity of the key with check_key function
        bool key_test = check_key(argv[1]);
        // if key is valid ask for plain text to decrypt
        if (key_test == true)
        {
            string text = get_string("plaintext: ");
            // call substitute function on the text input
            substitute(text, argv[1]);
        }
        // if key is not valid return error code
        else
        {
            return 1;
        }
    }
}

bool check_key(string key)
{
    // call test functions
    bool length_test = check_length(key);
    bool duplicates_test = check_duplicates(key);
    bool characters_test = check_characters(key);
    // if all test functions are fine return true
    if (length_test == true && duplicates_test == true && characters_test == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool check_length(string key)
{
    // if key is 26 characters return true
    bool outcome = true;
    if (strlen(key) != 26)
    {
        outcome = false;
        printf("Key must contain 26 characters.\n");
    }
    return outcome;
}

bool check_duplicates(string key)
{
    // check for duplicates
    bool outcome = true;
    int n = strlen(key);
    int count;
    int i;
    int j;
    char i_lower;
    char j_lower;
    // use a loop in a loop to go through each element and test for duplication
    for (i = 0; i < n; i++)
    {
        // set counter to zero for each loop of i
        count = 0;
        // normalise to lowercase to catch duplicate characters that are in different cases
        if (key[i] >= 65 && key[i] <= 90)
        {
            i_lower = key[i] + 32;
        }
        else
        {
            i_lower = key[i];
        }
        // inner loop to compare against i
        for (j = 0; j < n; j++)
        {
            // normalise to lowercase to catch duplicate characters that are in different cases
            if (key[j] >= 65 && key[j] <= 90)
            {
                j_lower = key[j] + 32;
            }
            else
            {
                j_lower = key[j];
            }
            // test if the now lower case elements are identical
            if (i_lower == j_lower)
            {
                count++;
            }
            if (count > 1)
            {
                outcome = false;
            }
        }
    }
    if (outcome == false)
    {
        // throw error if there is a duplicate
        printf("The key must not contain duplicate characters.\n");
        return outcome;
    }
    else
    {
        return outcome;
    }
}

bool check_characters(string key)
{
    // check for not alphabetic characters
    bool outcome = true;
    int i = 0;
    do
    {
        // test if lower or uppercase alphabetic character
        if ((key[i] >= 65 && key[i] <= 90) || (key[i] >= 97 && key[i] <= 122))
        {
        }
        else
        {
            outcome = false;
        }
        i++;
    }
    while (i <= 25 && outcome == true);
    // throw error if test fails
    if (outcome == false)
    {
        printf("Key must only contain alphabetic characters.\n");
    }
    return outcome;
}

void substitute(string text, string key)
{
    // substitute text for cipher
    char cipher[strlen(text)];
    // loop through text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // call get_caps function if character from text is upper case
        if (text[i] >= 65 && text[i] <= 90)
        {
            cipher[i] = get_caps(text[i], key);
        }
        else
        {
            // call get_loweer function if character from text is lower case
            if (text[i] >= 97 && text[i] <= 122)
            {
                cipher[i] = get_lower(text[i], key);
            }
            else
            {
                cipher[i] = text[i];
            }
        }

    }
    printf("ciphertext: %s\n", cipher);
}

char get_caps(char character, string key)
// if the text character is upper case ensure that the cypher function is upper case
{
    int index = character - 65;
    if (key[index] < 91)
    {
        return key[index];
    }
    else
    {
        return key[index] - 32;
    }
}

char get_lower(char character, string key)
// if the text character is lower case ensure that the cypher function is lower case
{
    int index = character - 97;
    if (key[index] > 96)
    {
        return key[index];
    }
    else
    {
        return key[index] + 32;
    }
}