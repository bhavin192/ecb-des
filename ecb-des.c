#define _GNU_SOURCE  
#include <crypt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <omp.h>
#define OMP_THREADS 4

void print_characters(char *array, int size)
{
    for(int i = 0; i < size; i++)
        printf("%c", array[i]);
}

int main(int argc, char *argv[])
{
    char key[64];
    char input[256];
    char divided_input[32][8];
    char bin_input[32][64];
    struct crypt_data data;
    data.initialized = 0;
    int DEC_FLAG;

    // handle all command line arguments properly
    // TODO: print more detailed help
    if(argc != 3)
    {
        printf("Invalid arguments.\nUsage: ecb-des [-e | -d] [<input_text>]\n");
        exit(1);
    }
    else
    {
        if(!strcmp(argv[1], "-e"))
            DEC_FLAG = 0;
        else if(!strcmp(argv[1], "-d"))
            DEC_FLAG = 1;
        else
        {
            printf("%s is not a valid option.\n", argv[1]);
            exit(1);
        }
    }
    strcpy(input, argv[2]);

#pragma omp parallel num_threads(OMP_THREADS)
    {
#pragma omp for
        for(int i = 0; i < 32; i++)
            for(int j = 0; j < 8; j++)
                    divided_input[i][j] = input[i * 8 + j];
            
        // convert all arrays to bit form 
#pragma omp for
        for(int i = 0; i < 32; i++)
            for(int j = 0; j < 8; j++)
                for(int k = 0; k < 8; k++)
                    bin_input[i][j * 8 + k] = divided_input[i][j] >> k & 1;

        //TODO: generate readable random key
#pragma omp for
        for(int i = 0; i < 64; i++)
            key[i] = 1; //rand() & 1; dummy key
            
        
        // encrypt all blocks 
        setkey_r(key, &data);
#pragma omp for
        for(int i = 0; i < 32; i++)
            encrypt_r(bin_input[i], DEC_FLAG, &data);

        // convert the bit arrays to readable form 
#pragma omp for
        for(int i = 0; i < 32; i++)
            for(int j = 0; j < 8; j++)
            {
                divided_input[i][j] = '\0';
                for(int k = 0; k < 8; k++)
                    divided_input[i][j] |= bin_input[i][j * 8 + k] << k;
            }
    }

    // print encrypted/decrypted message
    for(int i = 0; i < 32; i++)
        print_characters(divided_input[i], 8);

    return 0;
}

//http://www.gnu.org/software/libc/manual/html_node/crypt.html#crypt
//http://man7.org/linux/man-pages/man3/encrypt.3.html
//https://stackoverflow.com/questions/4892579/how-to-convert-a-char-to-binary
