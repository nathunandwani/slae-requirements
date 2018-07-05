#include <stdio.h>
#include <string.h>
#include <mcrypt.h>

int main()
{
    char plain_text[] = "this is for the SLAE assignment which currently works properly already";
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
        printf("\\x%X", (unsigned char)plain_text[i]);
    }
    printf("\n");
    return 0;
}

