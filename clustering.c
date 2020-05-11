#include <stdio.h>
#include <gmodule.h>
#include "pixel.h"

struct Pixel indexInTable(int rowNum, int colNum, GArray *table)
{
    struct Pixel temp;
    GArray *row = g_array_index(table, GArray*, rowNum);
    temp = g_array_index(row, struct Pixel, colNum);
    return temp;
}

int main(int argc, char *argv[])
{
FILE* filePtr = fopen("pixelOutput.txt","r");
if(filePtr==NULL)
{
    printf("Input file not found.");
    return 0;
}

int xPos, yPos, redChan, greenChan, blueChan;
struct Pixel temp;
GArray *tableCells = g_array_new(FALSE,FALSE,sizeof(struct Pixel));
GArray *tableRows = g_array_new(FALSE,FALSE,sizeof(tableCells));
g_array_append_val(tableCells,temp);
g_array_append_val(tableRows, tableCells);

while (fscanf(filePtr,"%d %*c %d %*c %*c %d %*s %d %*s  %d %*s",&xPos,&yPos,&redChan,&greenChan,&blueChan))
{
    printf("X position: %d\n",xPos);
    printf("Y position: %d\n",yPos);
    printf("\tRed channel: %d\n",redChan);
    printf("\tGreen channel: %d\n",greenChan);
    printf("\tBlue channel: %d\n", blueChan);

    temp = assignPixel(xPos,yPos,redChan,greenChan,blueChan);

    if(feof(filePtr))
    {
        break;
    }
}
/*
struct Pixel temp;
temp = assignPixel(1,2,4,5,6);
GArray *tableCells = g_array_new(FALSE,FALSE,sizeof(struct Pixel));
GArray *tableRows = g_array_new(FALSE,FALSE,sizeof(tableCells));
g_array_append_val(tableCells,temp);
g_array_append_val(tableRows, tableCells);
*/
//printf("The xCoord is: %d\n", g_array_index(tableCells,struct Pixel,0).coords[0]);
printf("The pixel R: %d\n", indexInTable(0,0,tableRows).RGB.R);
return 0;
}