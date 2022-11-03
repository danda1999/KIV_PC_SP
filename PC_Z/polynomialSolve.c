#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define EPSILON 0.01

int main(int argc, char const *argv[])
{
    float coeficient[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        coeficient[i - 1] = atof(argv[i]);
    }

    float a = 0.1;
    float result = 0.0;
    int counter = 1;
    int counter_rotare = 0;
    float help = 0.0;
    while (1)
    {   
        //printf("%f\n", a);

        for (int i = 0; i < argc - 1; i++)
        {
            if(i == 0){
                result += coeficient[argc - 2];
            }
            if(i == 1) {
                result += coeficient[argc - (2 + i)]*a;
            } else {
                for (int x = 0; x < i; x++)
                {
                    help += a;
                }

                result += a * coeficient[argc - (2 + i)];
            }
            
        }

        result = fabs(result);
        

        if(result < EPSILON) {
            printf("Koren %d: %f\n", counter, a);
            counter++;
        }

        counter_rotare ++;
        if(counter == argc - 1) {
            break;
        }
        
        if(counter_rotare == 1) {
            a = a *(-1);
        } else { 
            a += 0.1;
        }
    }
    
    return 0;
}
