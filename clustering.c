#include <stdio.h>
#include <gmodule.h>
#include "pixel.h"

int indexInTable(int rowNum, int colNum, GArray *table)
{
    int temp;
    GArray *row = g_array_index(table, GArray*, rowNum);
    temp = g_array_index(row, int, colNum);
    return temp;
}

void tableInsert(int x, int y, GArray *table, int input)
{
    GArray *row = g_array_index(table, GArray*, x);
    g_array_insert_val(row, y, input);
    return;
}

int main(int argc, char *argv[])
{
    FILE* filePtr = fopen("pixelOutput.txt","r");
    if(filePtr==NULL)
    {
        printf("Input file not found.");
        return 0;
    }

    int xPos, yPos, redChan, greenChan, blueChan, cellValue, minSeeker = 9999;
    struct Pixel n1, n2;
    struct Cluster candidate;
    GArray *pixelList = g_array_new(FALSE,FALSE,sizeof(struct Pixel));
    GArray *tableCells = g_array_new(FALSE,FALSE,sizeof(int));
    GArray *table = g_array_new(FALSE,FALSE,sizeof(tableCells));

    while (fscanf(filePtr,"%d %*c %d %*c %*c %d %*s %d %*s  %d %*s",&xPos,&yPos,&redChan,&greenChan,&blueChan))
    {
        n1 = assignPixel(xPos,yPos,redChan,greenChan,blueChan); // puts aspects into a pixel data container
        g_array_append_val(pixelList, n1); // stores each pixel into a list 
        if(feof(filePtr)) // end loop when EOF reached
        {
            break;
        }
    }

    for(int i=0;i<pixelList->len;i++) // test content in pixelList
    {
        struct Pixel temp = g_array_index(pixelList,struct Pixel,i);
        printf("The coords is: %d,%d ", temp.coords.x, temp.coords.y);
        printf("\t R: %d, G: %d, B: %d\n", temp.RGB.R,temp.RGB.G,temp.RGB.B);
    }
    
    // Loop the following function until pixelList->len==1
    while(pixelList->len > 1)
    {
        minSeeker = 9999;
        for(int i=0;i<pixelList->len;i++)// fill table with weight values by comparing elements of pixelList
        {
            for(int j=0;j<pixelList->len;j++)
            {
                n1 = g_array_index(pixelList,struct Pixel, i);
                n2 = g_array_index(pixelList,struct Pixel, j);
                cellValue = comparePixel(n1,n2);
                tableInsert(i,j,table,cellValue);
                if(minSeeker > cellValue)
                {
                    candidate.p1 = n1;
                    candidate.p2 = n2;
                    minSeeker = cellValue;
                }
            }
        }
        //at this point candidate is filled with the min weight pixels
        // remove n1 and n2 from pixelList
        //  do clusterToPixel and insert into pixelList
    }
    return 0;
}