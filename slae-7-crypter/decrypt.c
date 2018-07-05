#include <stdio.h>
#include <string.h>
#include <mcrypt.h>

int main()
{
    char cipher_text[] = "\x1B\x7B\x6C\x3E\x55\xDB\x83\xB3\x77\x75\x22\x26\xAE\xB4\xBF\x67\xFE\x23\x53\xE4\x38\x91\xF6\x61\x8B\x2A\xDF\x99\xB5\x54\x9F\x42\xE4\x11\x22\xD0\xE\xA\xB5\x1D\x83\x38\xEB\x90\xC1\xAF\xD7\x0\x11\x9B\xF\x2D\xA8\xF\x28\xE1\xAF\x59\x4C\x4A\x46\xA5\xD2\x15\x6C\x72\x65\x61\x64\x79";
    char initialization_vector[] = "SLAE1261SLAE1261";
    char password[] = "securitytubetube";
    int password_length = 16;
    int c_text_length = 70;

    MCRYPT algorithm = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
    mcrypt_generic_init(algorithm, password, password_length, initialization_vector);
    mdecrypt_generic(algorithm, cipher_text, c_text_length);
    mcrypt_generic_deinit(algorithm);
    mcrypt_module_close(algorithm);

    printf("Decrypted: %s\n", cipher_text);
  
    return 0;
}
