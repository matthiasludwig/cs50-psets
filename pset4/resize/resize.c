/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // Cast input argv[1] to an integer and check against bounds 0 and 100
    int n = atoi(argv[1]);
    if (n < 0 || n > 100) {
        fprintf(stderr, "Usage: n has to be between 1 and 100!\n");
        return 2;
    }

    // remember filenames and factor
    char *infile = argv[2];
    char *outfile = argv[3];


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Padding & size of the scanline of the INFILE
    int inpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int sizescanline = (sizeof(RGBTRIPLE) * bi.biWidth);
    int oldbiWidth = bi.biWidth;
    int oldbiHeight = abs(bi.biHeight);

    // Update BITMAPINFOHEADER
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for scanlines BEFORE finishing updating the BITMAPINFOHEADER
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight));

    // Update BITMAPFILEHEADER
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < oldbiHeight; i++)
    {
        // How many times to I have to write the scanline to the output
        for (int m = 0; m < n; m++) {
        // iterate over pixels in scanline
            for (int j = 0; j < oldbiWidth; j++) // Go horizontally through the lines biWidth (old) times
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int k = 0; k < n; k++) {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            //add padding to outfile
            for (int l = 0; l < padding; l++)
            {
                fputc(0x00, outptr);
            }
            if (m < (n - 1)) {
                fseek(inptr, -sizescanline, SEEK_CUR);
            }
        }

        // skip over padding, if any
        fseek(inptr, inpadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
