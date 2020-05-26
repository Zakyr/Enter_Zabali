#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));

    float a = 1.0;
    for (int i=0;i<20;i++)
        printf("%f\n", ((float)rand()/(float)(RAND_MAX)) * a);
        
    char symb = 175;
    
    printf("\n\n   this %c%cis the symbol", symb, symb);
    return 0;
}
