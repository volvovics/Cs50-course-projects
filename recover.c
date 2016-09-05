/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

int main(void)
{
//uint8_t c;
bool lastbytes=true;
int bytesread=512;
int counter=0;
FILE* file1=fopen("card.raw","r");
if (file1==NULL)
    {
    printf ("Failed to open file");
    fclose(file1);
    return 1;
    }

uint8_t buffer[512];
char title[8]="000.jpg";
sprintf(title,"%.3d.jpg",counter);
FILE* tempfile=fopen(title,"w");
while (lastbytes)
    {
    bytesread=fread(&buffer,1,512,file1);
    if (bytesread<512) lastbytes=false;
    for (int i=0;i<512;i++)    
        {
        if (buffer[i]==0xff) 
            if (buffer[i+1]==0xd8)
                if (buffer[i+2]==0xff)
                    if ((buffer[i+3]>=0xe0)&&(buffer[i+3]<=0xef))
                        {
                        //close previous file create new name and open new file only if this is not the first file
                        //if it's the first file it will start writing because counter changes to 1
                        if (counter>0)
                            {
                            fclose(tempfile);
                            sprintf(title,"%.3d.jpg",counter);
                            tempfile=fopen(title,"w");
                            }
                        counter++;
                        }
        // only write if we have found the 4 bytes and until the last bytes read (for the EOF)
        if ((counter>0)&&(i<bytesread))
            fwrite(&buffer[i],1,1,tempfile);
        }
    }        
fclose(tempfile);
fclose(file1);
return 0;
}
