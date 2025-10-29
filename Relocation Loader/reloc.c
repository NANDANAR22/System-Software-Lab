#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char bitmask[20], bit[80];

void convert(char h[12]) {
    strcpy(bit, "");
    for (int i = 0; i < strlen(h); i++) {
        switch (toupper(h[i])) {
            case '0': strcat(bit, "0000"); break;
            case '1': strcat(bit, "0001"); break;
            case '2': strcat(bit, "0010"); break;
            case '3': strcat(bit, "0011"); break;
            case '4': strcat(bit, "0100"); break;
            case '5': strcat(bit, "0101"); break;
            case '6': strcat(bit, "0110"); break;
            case '7': strcat(bit, "0111"); break;
            case '8': strcat(bit, "1000"); break;
            case '9': strcat(bit, "1001"); break;
            case 'A': strcat(bit, "1010"); break;
            case 'B': strcat(bit, "1011"); break;
            case 'C': strcat(bit, "1100"); break;
            case 'D': strcat(bit, "1101"); break;
            case 'E': strcat(bit, "1110"); break;
            case 'F': strcat(bit, "1111"); break;
        }
    }
}

int main() {
    FILE *fp1, *fp2;
    char input[20], pn[10], ch;
    int start, length, address, tlen, i, opcode, addr;
    char relocbit;

    printf("\nEnter the actual starting address : ");
    scanf("%x", &start);

    fp1 = fopen("input.txt", "r");
    if (!fp1) { printf("Error: input.txt not found\n"); return 1; }

    fp2 = fopen("output.txt", "w");
    fprintf(fp2, " ----------------------------\n");
    fprintf(fp2, " ADDRESS\tCONTENT\n");
    fprintf(fp2, " ----------------------------\n");

    while (fscanf(fp1, "%s", input) != EOF) {
        if (strcmp(input, "H") == 0) {
            fscanf(fp1, "%s", pn);
            fscanf(fp1, "%x", &address);
            fscanf(fp1, "%x", &length);
        } 
        else if (strcmp(input, "T") == 0) {
            fscanf(fp1, "%x", &address);
            fscanf(fp1, "%x", &tlen);
            fscanf(fp1, "%s", bitmask);

            convert(bitmask);
            address += start;

            for (i = 0; i < strlen(bit); i++) {
                int objcode;
                if (fscanf(fp1, "%x", &objcode) != 1) break;

                opcode = objcode / 0x10000;
                addr = objcode % 0x10000;

                relocbit = bit[i];
                if (relocbit == '1') addr += start;

                fprintf(fp2, "\n  %x\t\t%06x", address, opcode * 0x10000 + addr);
                address += 3;
            }
        }
        else if (strcmp(input, "E") == 0) {
            break;
        }
    }

    fprintf(fp2, "\n ----------------------------\n");
    fclose(fp1);
    fclose(fp2);

    printf("\n\nThe contents of output file (output.txt):\n\n");
    fp2 = fopen("output.txt", "r");
    while ((ch = fgetc(fp2)) != EOF) putchar(ch);
    fclose(fp2);

    return 0;
}
