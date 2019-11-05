#include <stdio.h>
#include "bstree.h"
#include <string.h>

int main()
{
    //test string_dup

    char *testString = "helloworld";
    char *dupString = string_dup(testString);

    //check if the string is the same

    if ((strcmp(testString, dupString) == 0) && (&testString != &dupString))
    {
        printf("Test 1 passed\n\n");
    }
    else
    {
        printf("Test 1 failed\n");
        printf("input string: %s, output string: %s, Memory address of input, output: %p, %p\n\n", testString, dupString, &testString, &dupString);
    }

    //test key gen

    Key testKey = key_gen("test1", "test2");

    if (strcmp(testKey->skey1, "test1") == 0 && strcmp(testKey->skey2, "test2") == 0)
    {
        printf("Test 2 passed\n\n");
    }
    else
    {
        printf("Test failed\n\n");
    }

    //test key compare

    Key testKey1 = key_gen("test1", "test2");
    Key testKey2 = key_gen("test3", "test4");
    Key testKey3 = key_gen("test3", "test5");

    //both the same
    if (key_comp(testKey, testKey1) == 0)
    {
        printf("Test 3 passed\n\n");
    }
    else
    {
        printf("Test 3 failed\n\n");
    }

    //both different
    if (key_comp(testKey1, testKey2) == -1)
    {
        printf("Test 4 passed\n\n");
    }
    else
    {
        printf("Test 4 failed\n\n");
    }

    //first same
    if (key_comp(testKey2, testKey3) == -1)
    {
        printf("Test 5 passed\n\n");
    }
    else
    {
        printf("Test 5 failed\n\n");
    }

    //manually check if the key was printed
    printf("Check manuualy this was printed: test1 test2  \n");
    key_print(testKey);

    Data testData = data_gen(10);

    //    printf("%d", *testData);
    //    data_print(testData);

    if (*testData == 10)
    {
        printf("Test 7 passed\n\n");
    }
    else
    {
        printf("Test 7 failed\n\n");
    }

    data_set(testData, 15);

    //    data_print(testData);

    if (*testData == 15)
    {
        printf("Test 8 passed\n\n");
    }
    else
    {
        printf("Test 8 failed\n\n");
    }

    key_free(testKey);
    key_free(testKey1);
    key_free(testKey2);
    key_free(testKey3);

    data_free(testData);
}