#include <stdio.h>
#include <string.h>

int main(){
    char hello[] = "hello world";
    for(int i=0; i<strlen(hello); i++){
        printf("%c", hello[i] ^ 0);
    }
    printf("\n");
    return 0;
}