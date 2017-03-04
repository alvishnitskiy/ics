#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int fileManagement(char*, char*);
int checkHeader(BITMAPFILEHEADER*, BITMAPINFOHEADER*, FILE*, FILE*);
int changeColors(BITMAPINFOHEADER*, FILE*, FILE*);

/*
NMEMB - nmemb elements of data (fread, fwrite)
MULTIPLIER - multiple for Microsoft’s BMP format 4.0
*/
enum constants { 
    NMEMB = 1, MULTIPLIER = 4
};

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3){
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // control of file reading and writing to file
    int ret = fileManagement(infile, outfile);
    if (ret != 0){
        return ret;
    }

    // success
    return 0;
}

/*
 * Control of file reading and writing to file
 */
int fileManagement(char* infile, char* outfile)
{
    // open input file 
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL){
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL){
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, BITMAPFILEHEADER_SIZE, NMEMB, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, BITMAPINFOHEADER_SIZE, NMEMB, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (checkHeader(&bf, &bi, inptr, outptr) != 0){
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, BITMAPFILEHEADER_SIZE, NMEMB, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, BITMAPINFOHEADER_SIZE, NMEMB, outptr);

    // change colors of RGB triples
    int ret = changeColors(&bi, inptr, outptr);
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
    
    // not ok
    if (ret != 0){
        return ret;
    }
    
    // success
    return 0;
}

/*
 * Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
 */
int checkHeader(BITMAPFILEHEADER* bf, BITMAPINFOHEADER* bi, FILE* inptr, FILE* outptr)
{
    if (bf->bfType != 0x4d42 || bf->bfOffBits != (BITMAPFILEHEADER_SIZE + BITMAPINFOHEADER_SIZE) || 
        bi->biSize != BITMAPINFOHEADER_SIZE || bi->biBitCount != BITCOUNT || bi->biCompression != 0){

        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // success
    return 0;
}

/*
 * Change colors of RGB triples
 */
int changeColors(BITMAPINFOHEADER* bi, FILE* inptr, FILE* outptr)
{
    // determine padding for scanlines
    int padding = (MULTIPLIER - (bi->biWidth * RGBTRIPLE_SIZE) % MULTIPLIER) % MULTIPLIER;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi->biHeight); i < biHeight; i++){
        // iterate over pixels in scanline
        for (int j = 0; j < bi->biWidth; j++){
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, RGBTRIPLE_SIZE, NMEMB, inptr);

            // change intensity of colors to get whodunit
            //printf("B: %x G: %x R: %x\n", triple.rgbtBlue, triple.rgbtGreen, triple.rgbtRed);
            if(triple.rgbtRed == 0xff){
                triple.rgbtBlue = triple.rgbtGreen = 0xff;
            }
            else {
                triple.rgbtBlue = triple.rgbtGreen = 0x00;
            }

            // write RGB triple to outfile
            fwrite(&triple, RGBTRIPLE_SIZE, NMEMB, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++){
            fputc(0x00, outptr);
        }
    }
    
    // success
    return 0;
}