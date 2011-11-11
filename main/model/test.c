#include "test.h"
#include <stdio.h>

int main()
{
    FILE * pFile;
    pFile = fopen ("10k-new.txt","r");
    if (pFile!=NULL)
    {
        printf("fopen example\n");
        fclose (pFile);
     }
     else{
         printf("The sun will never rise.\n");
     }
    return 0;
}
