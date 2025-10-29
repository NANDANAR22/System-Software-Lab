#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() 
{
    FILE *fp, *fp1;
    int i, j, stdaddr1;
    char line[100], name[50], staddr[20];

    fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Error: input.txt not found!\n");
        return;
    }

    fp1 = fopen("output.txt", "w");

    fscanf(fp, "%s", line);
    for (i = 2, j = 0; line[i] != '^'; i++, j++)
        name[j] = line[i];
    name[j] = '\0';

    printf("name from obj.%s\n", name);

    while (fscanf(fp, "%s", line) != EOF) 
    {
        if (line[0] == 'T') 
        {
            for (i = 2, j = 0; line[i] != '^'; i++, j++)
                staddr[j] = line[i];
            staddr[j] = '\0';

            // Convert starting address from HEX
            sscanf(staddr, "%x", &stdaddr1);

            // Move to start of object code (after 3 '^' fields)
            int caretCount = 0;
            i = 0;
            while (line[i] != '\0' && caretCount < 3) {
                if (line[i] == '^') caretCount++;
                i++;
            }

            // Read all object codes until end of string
            while (line[i] != '\0') 
            {
                if (line[i] != '^' && line[i + 1] != '\0') 
                {
                    printf("%04X\t%c%c\n", stdaddr1, line[i], line[i + 1]);
                    fprintf(fp1, "%04X\t%c%c\n", stdaddr1, line[i], line[i + 1]);
                    stdaddr1++;
                    i += 2;
                }
                else i++;
            }
        }
    }

    fclose(fp);
    fclose(fp1);

    printf("\n✅ Output written to output.txt\n");
}
