#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "You need to supply one argument only.  This argument must be a file name\n");
        return 1;
    }
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    BYTE buf[512];
    char filename[8];
    FILE *outptr;
    int count = 0;

    while(fread(buf,512,1,inptr)){

        if(buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && (buf[3] & 0xf0) == 0xe0)
        {
            if(count > 0){
                fclose(outptr);
            }

            sprintf(filename, "%03i.jpg", count);

            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }
            count++;
        }
        if (!count)
        {
            continue;
        }
         fwrite(buf,512,1,outptr);
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}
