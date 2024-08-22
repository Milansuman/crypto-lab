#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* strupper(char *text){
    char *upper = malloc(sizeof(char) * strlen(text));
    for(int i=0; i<strlen(text); i++){
        upper[i] = toupper(text[i]);
    }
    return upper;
}

char* encrypt(char *plainText, int key){
    char *upperText = strupper(plainText);

    for(int i=0; i<strlen(upperText); i++){
        if(!isalpha(upperText[i])) continue;

        int offset = (upperText[i] - 'A' + key) % 25;
        upperText[i] = 'A' + offset;
    }
    return upperText;
}

char* decrypt(char *cipherText, int key){
    char *upperText = strupper(cipherText);

    for(int i=0; i<strlen(upperText); i++){
        if(!isalpha(upperText[i])) continue;

        int offset = (upperText[i] - 'A' - key) % 25;
        if(offset < 0) offset += 25;
        upperText[i] = 'A' + offset;
    }
    return upperText;
}

int main(int argc, char **argv){
    if(argc < 3){
        printf("./substitution -e|-d [TEXT] [KEY]\n");
        return 0;
    }

    if(strcmp(argv[1], "-e") == 0){
        printf("%s\n", encrypt(argv[2], (int) argv[3][0] - '0'));
    }else if(strcmp(argv[1], "-d") == 0){
        printf("%s\n", decrypt(argv[2], (int) argv[3][0] - '0'));
    }else{
        printf("./substitution -e|-d [TEXT] [KEY]\n");
    }
    return 0;
}