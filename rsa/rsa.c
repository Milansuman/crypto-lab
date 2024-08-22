#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long n, e;
} PublicKey;

typedef struct {
    long n, d;
} PrivateKey;

long gcd(long a, long b, long *x, long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long x1, y1;
    long g = gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

long modInverse(long a, long m) {
    long x, y;
    long g = gcd(a, m, &x, &y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

long modPow(long base, long exp, long mod) {
    long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

PublicKey generatePublicKey(long p, long q) {
    long n = p * q;
    long phi = (p - 1) * (q - 1);
    long e = 65537; // Common choice for e
    return (PublicKey){n, e};
}

PrivateKey generatePrivateKey(long p, long q, PublicKey pub) {
    long phi = (p - 1) * (q - 1);
    long d = modInverse(pub.e, phi);
    return (PrivateKey){pub.n, d};
}

long* encrypt(const char* plainText, PublicKey pub) {
    size_t len = strlen(plainText);
    long* cipherText = malloc(sizeof(long) * len);
    for (size_t i = 0; i < len; i++)
        cipherText[i] = modPow(plainText[i], pub.e, pub.n);
    return cipherText;
}

char* decrypt(const long* cipherText, size_t len, PrivateKey pri) {
    char* plainText = malloc(len + 1);
    for (size_t i = 0; i < len; i++)
        plainText[i] = modPow(cipherText[i], pri.d, pri.n);
    plainText[len] = '\0';
    return plainText;
}

int main() {
    long p = 61, q = 53; // Small primes for demonstration
    PublicKey pub = generatePublicKey(p, q);
    PrivateKey pri = generatePrivateKey(p, q, pub);
    
    char* message = "Hello, RSA!";
    size_t len = strlen(message);
    
    long* encrypted = encrypt(message, pub);
    char* decrypted = decrypt(encrypted, len, pri);

    printf("Original: %s\n", message);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    free(encrypted);
    free(decrypted);
    return 0;
}