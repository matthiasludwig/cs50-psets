#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef int DATA[126];
typedef uint8_t  HEADER[4];



typedef struct {
    HEADER header;
    DATA data;
} BUFFER;

int main(int argc, char* argv[]) {
    // Test if image is passed in the command line
    if (argc != 2) {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    // Save filename in *image
    char *image = argv[1];
    // File counter
    int filecounter = -1;
    int number = 1;

    //Open card file
    FILE *infile = fopen(image, "r");
    char filename[50];

    if (infile == NULL) {
        fprintf(stderr, "Could not open %s.\n", image);
        return 2;
    }

    // Iterate over image until the EOF is reached (which is smaller than the 512 Byte)
    while (number == 1) {
        // Declare and read in buffersize
        BUFFER bf;
        // Check if the beginning is JPG header
        number = fread(&bf, 512, 1, infile);
        if (bf.header[0] == 0xff &&
            bf.header[1] == 0xd8 &&
            bf.header[2] == 0xff &&
            (bf.header[3] & 0xf0) == 0xe0) {
                filecounter++;
                // Get current file name
                sprintf(filename, "%03i.jpg", filecounter);
                FILE *outfile = fopen(filename, "w");
                fwrite(&bf, 512, 1, outfile);
                fclose(outfile);
        }
        else if (filecounter >= 0 && number == 1) {
            FILE *outfile = fopen(filename, "a");
            fwrite(&bf, 512, 1, outfile);
            fclose(outfile);
        }
    }
    // Closing the infile
    fclose(infile);

    return 0;
}