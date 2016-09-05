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
        if (i<509)
        if (buffer[i]==0xff)
            if (buffer[i+1]==0xd8)
                if (buffer[i+2]==0xff)
                    if ((buffer[i+3]>=0xe0)&&(buffer[i+3]<=0xef))
                        {
                        //close previous file
                        if (counter>0)
                            {
                            //printf(" %x %x %x %x %i %i initial\n",buffer[i],buffer[i+1],buffer[i+2],buffer[i+3], counter,i);    
                            fclose(tempfile);
                            //create new file name and open it for writing
                            sprintf(title,"%.3d.jpg",counter);
                            //printf(" %x %x %x %x %i %i second \n",buffer[i],buffer[i+1],buffer[i+2],buffer[i+3], counter,i);      
                            tempfile=fopen(title,"w");
                            }
                        counter++;
                        }
        if ((counter>0)&&(i<bytesread))
            fwrite(&buffer[i],1,1,tempfile);
        }
    }        
fclose(tempfile);
fclose(file1);
return 0;
}
