#include <stdio.h>
#include <string.h>

int main(){
    char hello[] = "hello world";
    size_t n = strlen(hello);

    char andString[n], orString[n], xorString[n];
    for(int i=0; i<n; i++){
        andString[i] = hello[i] & 127;
        orString[i] = hello[i] | 127;
        xorString[i] = hello[i] ^ 127;
    }

    printf("Original Text: hello world\n");
    printf("And String: %s\n", andString);
    printf("Or String: %s\n", orString);
    printf("XOR String: %s\n", xorString);
    return 0;
}