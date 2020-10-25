#include <stdio.h>
#include <stdlib.h>

int main()
{
    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    char* buffer;
    buffer = (char*) malloc(26);   
    for (int i = 0; i < 26; i++){
        buffer[i] = alphabet[i];
    }  
    printf("%s\n", buffer);
    free(buffer);
    printf("%s\n", buffer);
    free(buffer);
    return 0;
}
