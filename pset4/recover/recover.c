#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int fileManagement(char*);
int createFiles(FILE*);
void closeFile(FILE*, bool*);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2){
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // remember filename
    char* cardfile = argv[1];

    // control of file opening and closing
    int ret = fileManagement(cardfile);
    if (ret != 0){
        return ret;
    }
    
    // success
    return 0;
}

/*
 * Control of file opening and closing
 */
int fileManagement(char* cardfile)
{
    // open card file 
    FILE* cardptr = fopen(cardfile, "rb");
    if (cardptr == NULL){
        fprintf(stderr, "Could not open %s.\n", cardfile);
        return 2;
    }

    // create JPEG-files from cardfile
    int ret = createFiles(cardptr);
    
    // close cardfile
    fclose(cardptr);

    // not ok
    if (ret != 0){
        return ret;
    }
    
    // success
    return 0;
}

/*
 * Create JPEG-files from cardfile
 */
//int createFiles(BYTE* buffer[], FILE* cardptr)
int createFiles(FILE* cardptr)
{
    /*
    NMEMB       - number elements of data
    BUFFER_SIZE - size of buffer for cardfile's block
    */
    enum constants { 
        NMEMB = 1, BUFFER_SIZE = 512
    };
    enum bytes {
        FIRST_B = 0, SECOND_B, THIRD_B, FOURTH_B
    };
    // create counter of JPEG files
    int count = 0;
    
    // create an array of chars for the name of JPEG-file
    char filename[8];
    
    // file exists or not ?
    bool file_exists = false;
    FILE* img;
    
    // create temporary buffer for cardfile's block
    typedef uint8_t  BYTE;
    BYTE buffer[BUFFER_SIZE];
    
    // iterate over cardfile's blocks
    while(fread(&buffer, BUFFER_SIZE, NMEMB, cardptr) > 0){
        //printf("%02x%02x%02x\n", buffer[FIRST_B], buffer[SECOND_B], buffer[THIRD_B]);
        
        // start of a new JPEG ?
        if (buffer[FIRST_B] == 0xff && buffer[SECOND_B] == 0xd8 &&
            buffer[THIRD_B] == 0xff && (buffer[FOURTH_B] & 0xf0) == 0xe0){
            
            // close existing JPEG-file
            closeFile(img, &file_exists);
            
            // open a new JPEG-file
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "wb");
            if (img == NULL){
                fprintf(stderr, "Could not open %s.\n", filename);
                return 2;
            }
            file_exists = true;
            
            // next be later
            count++;
        }
        if (false == file_exists){
            continue;
        }
        else if(true == file_exists){
            // write block to JPEG-file
            fwrite(&buffer, BUFFER_SIZE, NMEMB, img);
        }
    }
    
    // close existing JPEG-file
    closeFile(img, &file_exists);
    
    // success
    return 0;
}

/*
 * Close existing JPEG-file
 */
void closeFile(FILE* img, bool* file_exists)
{
    if (true == *file_exists){
        fclose(img);
    }
}