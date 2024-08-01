#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* scanLine(){
    char *buf = (char*) malloc(sizeof(char));
    size_t size = sizeof(char);
    int i = 0;
    
    char c;
    while((c = getchar()) != '\n' && c != EOF){
        size += sizeof(char);
        buf = (char*) realloc(buf, size);
        *(buf+i) = c;
        i++;
    }
    return buf;
}

char* generateSubstitutionCipher(char *plainText, int key){
    size_t sizeOfPlainText = strlen(plainText);
    char *buf = (char*) malloc(sizeof(char)*sizeOfPlainText);

    for(int i=0; i<sizeOfPlainText; i++){
        //skip spaces for experiment
        if(*(plainText+i) == ' '){
            *(buf+i) = ' ';
            continue;
        }
        int index = (*(plainText+i) - 'a' + key)%25;

        *(buf+i) = 'a' + index;
    }

    return buf;
}

char* decryptSubstitutionCipherText(char *cipherText, int key){
    size_t sizeOfCipherText = strlen(cipherText);
    char *buf = (char*) malloc(sizeof(char)*sizeOfCipherText);

    for(int i=0; i<sizeOfCipherText; i++){
        //skip spaces for experiment
        if(*(cipherText+i) == ' '){
            *(buf+i) = ' ';
            continue;
        }
        int index = ((*(cipherText+i) - 'a' - key)%25 + 25)%25; // a (mod b) = (a%n + n)%n
        *(buf+i) = 'a' + index;
    }

    return buf;
}

char* bruteforceSubstitutionCipherText(char *cipherText){
    size_t sizeOfCipherText = strlen(cipherText);
    char *buf = (char*) malloc(sizeof(char)*sizeOfCipherText*26); //26 keys

    for(int i=0; i<26; i++){
        buf = strcat(buf, decryptSubstitutionCipherText(cipherText, i));
        buf = strcat(buf, "\n");
    }

    return buf;
}

int main(){
    printf("Enter some text: ");
    char *input = scanLine();
    char *encrypted = generateSubstitutionCipher(input, 5);
    char *decrypted = decryptSubstitutionCipherText(encrypted, 5);
    char *bruteForce = bruteforceSubstitutionCipherText(encrypted);

    printf("Enter a filename to save results to: ");
    char *filename = scanLine();
    FILE *file = fopen(filename, "w+");

    fprintf(file, "Original: %s\nEncrypted: %s\nDecrypted: %s\nBruteFore Attempts:\n%s", input, encrypted, decrypted, bruteForce);
    fclose(file);
    free(input);
    free(encrypted);
    free(decrypted);
    free(bruteForce);
    return 0;
}