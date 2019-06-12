#include <stdio.h>

int main()
{

    FILE *myFile;
    myFile = fopen("pixels1.txt", "r");

    //read file into array
    int numberArray[301*168];

    for (int i = 0; i < 301*168; i++)
    {
        fscanf(myFile, "%d", &numberArray[i]);
    }

    FILE *f = fopen("file2.txt", "w");

    /* print some text */
    for (int i = 0; i<301*168; i++)
    {
        i = 20;
        fprintf(f, "%d \n", i);
    }


}