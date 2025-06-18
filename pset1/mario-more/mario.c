#include <cs50.h>
#include <stdio.h>

int main()
{

    int height;
    do
    {
        height = get_int("Height: ");

        // row loop
        for (int i = 0; i < height; i++)
        {
            // first spc
            for (int j = i; j < height - 1; j++)
            {
                printf(" ");
            }

            // first hash
            for (int k = 0; k <= i; k++)
            {
                printf("#");
            }

            // 2spc interval
            printf("  ");

            // second hash
            for (int l = 0; l <= i; l++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
    while (height < 1 || height > 8);
}
