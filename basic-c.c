#include <stdio.h>

#include <limits.h>
#include <unistd.h>

void pr(char *ch)
{
    *ch = 'd';
}

int get_int(int c)
{
    (void) c;
    return (0);
}

int main()
{
    // [d][a][r][a][f][a][\0]
    char test[7] = "darafa";
    test[2] = 'R';




    unsigned char max = 256;
    printf("%d\n", max);


    char *test_ptr = test;
    (void) test_ptr;
    //write(1, test_ptr, 1);
    //write(1, "\n", 1);

    if (get_int(4) == 45)
        return (1);

    //printf("%d\n", get_int(4));

    // [d][a][r][a][f][a][\0]
    // [d][a][R][a][f][a][\0]


/*    char i = 'a';

    pr(&i);*/
    //char *test = &i;

   //printf("%s\n", test);
   return (0);
}