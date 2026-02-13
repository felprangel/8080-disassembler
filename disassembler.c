#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>

int disassemble8080Opcode(unsigned char *codebuffer, int pc);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Erro: Nome da ROM é obrigatório.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "Erro: Não foi possível abrir a ROM.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(fsize);
    fread(buffer, 1, fsize, file);
    fclose(file);

    int pc = 0;
    while (pc < fsize) {
        pc += disassemble8080Opcode(buffer, pc);
    }

    free(buffer);
    return 0;
}

/*
*codebuffer is a valid pointer to 8080 assembly code
pc is the current offset into the code

returns the number of bytes of the op
*/

int disassemble8080Opcode(unsigned char *codebuffer, int pc)
{
    unsigned char *code = &codebuffer[pc];
    int opbytes = 1;
    printf ("%04x ", pc);
    switch (*code) {
        case 0x00:
            printf("NOP");
            break;

        case 0x01:
            printf("LXI    B,#$%02x%02x", code[2], code[1]);
            opbytes=3;
            break;

        case 0x02:
            printf("STAX   B");
            break;

        case 0x03:
            printf("INX    B");
            break;

        case 0x04:
            printf("INR    B");
            break;

        case 0x05:
            printf("DCR    B");
            break;

        case 0x06:
            printf("MVI    B,#$%02x", code[1]);
            opbytes=2;
            break;

        case 0x07:
            printf("RLC");
            break;

        case 0x08:
            printf("NOP");
            break;

        /* ........ */
        case 0x3e:
            printf("MVI    A,#0x%02x", code[1]);
            opbytes = 2;
            break;

        /* ........ */
        case 0xc3:
            printf("JMP    $%02x%02x",code[2],code[1]);
            opbytes = 3;
            break;

        /* ........ */
    }

    printf("\n");

    return opbytes;
}
