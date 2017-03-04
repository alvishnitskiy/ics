#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int fileManagement(char*, char*, float*);
int getFloatInput(char*, float*);
int checkHeader(BITMAPFILEHEADER*, BITMAPINFOHEADER*, FILE*);
int createBuffer(RGBTRIPLE* [], BITMAPINFOHEADER*, const int*);
int bufferWrite(RGBTRIPLE* [], BITMAPINFOHEADER*, int*, FILE*);
int changeSettings(BITMAPFILEHEADER*, BITMAPINFOHEADER*, int*, float*);
int bufferRead(RGBTRIPLE* [], BITMAPINFOHEADER*, BITMAPINFOHEADER*, int*, FILE*);
void freeMemory(RGBTRIPLE* [], const int*);

/*
NOT_OK - if something is wrong
NMEMB - nmemb elements of data (fread, fwrite)
MULTIPLIER - multiple for Microsoft’s BMP format 4.0
*/
enum constants { 
    NOT_OK = 1, NMEMB = 1, MULTIPLIER = 4
};

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4){
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return NOT_OK;
    }

    // getting and parsing the float input
    float f;
    if (getFloatInput(argv[1], &f) != 0){
        return NOT_OK;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // control of file reading and writing to file
    if (fileManagement(infile, outfile, &f) != 0){
        return NOT_OK;
    }

    // success
    return 0;
}

/*
 * Control of file reading and writing to file
 */
int fileManagement(char* infile, char* outfile, float* f)
{
    int padding;
    
    // open input file
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL){
        fprintf(stderr, "Could not open %s.\n", infile);
        return NOT_OK;
    }

     // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, BITMAPFILEHEADER_SIZE, NMEMB, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, BITMAPINFOHEADER_SIZE, NMEMB, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (checkHeader(&bf, &bi, inptr) != 0){
        return NOT_OK;
    }

    // create temporary buffer for RGBTRIPLE structure
    const int BUFFER_SIZE = abs(bi.biHeight);
    RGBTRIPLE* triple[BUFFER_SIZE];
    if (createBuffer(triple, &bi, &BUFFER_SIZE) != 0){
        // close infile
        fclose(inptr);
        
        return NOT_OK;
    }

    // read input file and write to the buffer
    int ret = bufferWrite(triple, &bi, &padding, inptr);

    // close infile
    fclose(inptr);
    
    // not ok
    if (ret != 0){
        freeMemory(triple, &BUFFER_SIZE);
        return ret;
    }
    
    // open output file
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL){
        freeMemory(triple, &BUFFER_SIZE);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return NOT_OK;
    }
    
    // remember the height and width settings
    BITMAPINFOHEADER old_bi = bi;
    
    // update header settings
    if (changeSettings(&bf, &bi, &padding, f) != 0){
        // close outfile
        fclose(outptr);
        freeMemory(triple, &BUFFER_SIZE);
        return NOT_OK;
    }
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, BITMAPFILEHEADER_SIZE, NMEMB, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, BITMAPINFOHEADER_SIZE, NMEMB, outptr);

    // read buffer and write to the output file
    ret = bufferRead(triple, &old_bi, &bi, &padding, outptr);
    
    // free memory from RGBTRIPLE buffer
    freeMemory(triple, &BUFFER_SIZE);
    
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
 * Getting and parsing the float input
 */
int getFloatInput(char* argv_1, float* f)
{
    const float RESIZE_MIN = 0.0;
    const float RESIZE_MAX = 100.0;
    
    if (sscanf(argv_1, "%f", f) <= 0 || *f <= RESIZE_MIN || *f > RESIZE_MAX){
        fprintf(stderr, "Incorrect floating-point value "
            "(must be more than %f and no more than %f).\n", RESIZE_MIN, RESIZE_MAX);
        return NOT_OK;
    }
    
    // success
    return 0;
}

/*
 * Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
 */
int checkHeader(BITMAPFILEHEADER* bf, BITMAPINFOHEADER* bi, FILE* inptr)
{
    if (bf->bfType != 0x4d42 || bf->bfOffBits != (BITMAPFILEHEADER_SIZE + BITMAPINFOHEADER_SIZE) || 
        bi->biSize != BITMAPINFOHEADER_SIZE || bi->biBitCount != BITCOUNT || bi->biCompression != 0){
        
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return NOT_OK;
    }
    
    // success
    return 0;
}

/*
 * Create temporary buffer for RGBTRIPLE structure
 */
int createBuffer(RGBTRIPLE* triple[], BITMAPINFOHEADER* bi, const int* BUFFER_SIZE)
{
    if (triple == NULL){
        return NOT_OK;
    }
    for (int i = 0; i < *BUFFER_SIZE; i++){
        triple[i] = (RGBTRIPLE*) malloc (bi->biWidth * RGBTRIPLE_SIZE);
        if (triple[i] == NULL){
            freeMemory(triple, BUFFER_SIZE);
            return NOT_OK;
        }
    }
    
    // success
    return 0;
}

/*
 * Read input file and write to the buffer
 */
int bufferWrite(RGBTRIPLE* triple[], BITMAPINFOHEADER* bi, int* padding, FILE* inptr)
{
    // determine padding for scanlines (infile)
    *padding = (MULTIPLIER - (bi->biWidth * RGBTRIPLE_SIZE) % MULTIPLIER) % MULTIPLIER;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi->biHeight); i < biHeight; i++){
        // iterate over pixels in scanline
        for (int j = 0; j < bi->biWidth; j++){
            // read RGB triple from infile
            fread(&triple[i][j], RGBTRIPLE_SIZE, NMEMB, inptr);
        }

        // skip over padding, if any
        fseek(inptr, *padding, SEEK_CUR);
    }
    
    // success
    return 0;
}

/*
 * Update header settings
 */
int changeSettings(BITMAPFILEHEADER* bf, BITMAPINFOHEADER* bi, int* padding, float* f)
{
    // update the height and width settings
    bi->biWidth = lroundf(bi->biWidth * (*f));
    bi->biHeight = lroundf(bi->biHeight * (*f));
    
    // determine padding for scanlines (outfile)
    *padding = (MULTIPLIER - (bi->biWidth * RGBTRIPLE_SIZE) % MULTIPLIER) % MULTIPLIER;
    
    // update outfile's header
    bi->biSizeImage = ((RGBTRIPLE_SIZE * bi->biWidth) + *padding) * abs(bi->biHeight);
    bf->bfSize = bi->biSizeImage + BITMAPFILEHEADER_SIZE + BITMAPINFOHEADER_SIZE;
    
    // success
    return 0;
}

/*
 * Read buffer and write to the output file
 */
int bufferRead(RGBTRIPLE* triple[], BITMAPINFOHEADER* old_bi, 
                BITMAPINFOHEADER* bi, int* padding, FILE* outptr)
{
    // defined old settings for height and width 
    const long OLD_WIDTH = old_bi->biWidth;
    const long OLD_HEIGHT = abs(old_bi->biHeight);
    
    // dimensions for RGBTRIPLE buffer
    long x = 0;
    long y = 0;

    // iterate over outfile's scanlines
    for (int i = 0, biHeight = abs(bi->biHeight); i < biHeight; i++){
        // corresponding row
        x = lroundf(i * OLD_HEIGHT / biHeight);
        
        // iterate over pixels in scanline
        for (int j = 0; j < bi->biWidth; j++){
            // corresponding pixel from old row
            y = lroundf(j * OLD_WIDTH / bi->biWidth);
            
            // write RGB triple to outfile
            fwrite(&triple[x][y], RGBTRIPLE_SIZE, NMEMB, outptr);
        }

        // then add it back (to demonstrate how)
        for (int k = 0; k < *padding; k++){
            fputc(0x00, outptr);
        }
    }
    
    // success
    return 0;
}

/*
 * Free memory from RGBTRIPLE buffer
 */
void freeMemory(RGBTRIPLE* triple[], const int* BUFFER_SIZE)
{
    for (int i = 0; i < *BUFFER_SIZE; i++){
        if (triple[i] != NULL){
            free(triple[i]);
        }
    }
}
