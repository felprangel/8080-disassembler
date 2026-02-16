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
            opbytes = 3;
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
            opbytes = 2;
            break;

        case 0x07:
            printf("RLC");
            break;

        case 0x08:
            printf("NOP (Invalid Opcode)");
            break;

        case 0x09:
            printf("DAD    B");
            break;

        case 0x0A:
            printf("LDAX   B");
            break;

        case 0x0B:
            printf("DCX    B");
            break;

        case 0x0C:
            printf("INR    C");
            break;

        case 0x0D:
            printf("DCR    C");
            break;

        case 0x0E:
            printf("MVI    C,#$%02x", code[1]);
            opbytes = 2;
            break;

        case 0x0F:
            printf("RRC");
            break;

        case 0x10:
            printf("NOP (Invalid Opcode)");
            break;

        case 0x11:
            printf("LXI    D,#$%02x%02x", code[2], code[1]);
            opbytes = 3;
            break;

        case 0x12:
            printf("STAX   D");
            break;

        case 0x13:
            printf("INX    D");
            break;

        case 0x14:
            printf("INR    D");
            break;

        case 0x15:
            printf("DCR    D");
            break;

        case 0x16:
            printf("MVI    D,#$%02x", code[1]);
            opbytes = 2;
            break;

        case 0x17:
            printf("RAL");
            break;

        case 0x18:
            printf("NOP (Invalid Opcode)");
            break;

        case 0x19:
            printf("DAD    D");
            break;

        case 0x1A:
            printf("LDAX   D");
            break;

        case 0x1B:
            printf("DCX    D");
            break;

        case 0x1C:
            printf("INR    E");
            break;

        case 0x1D:
            printf("DCR    E");
            break;

        case 0x1E:
            printf("MVI    E,#$%02x", code[1]);
            opbytes = 2;
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
