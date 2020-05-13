#include <omp.h>
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

void tableInsert(int x, int y, int length, int *table, int input)
{
    //GArray *row = g_array_index(table, GArray*, x);
    table[x+(length* y)] = input;
    //g_array_insert_val(row, y, input);
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
    struct Pixel n1, n2, test1, test2, postClust;
    struct Cluster candidate;
    GArray *pixelList = g_array_new(FALSE,FALSE,sizeof(struct Pixel));

    while (fscanf(filePtr,"%d %*c %d %*c %*c %d %*s %d %*s  %d %*s",&xPos,&yPos,&redChan,&greenChan,&blueChan))
    {
        n1 = assignPixel(xPos,yPos,redChan,greenChan,blueChan); // puts aspects into a pixel data container
        g_array_append_val(pixelList, n1); // stores each pixel into a list 
        if(feof(filePtr)) // end loop when EOF reached
        {
            break;
        }
    }

    int length = pixelList->len;
    //GArray *tableCells = g_array_sized_new(FALSE,TRUE,sizeof(int),pixelList->len);
    int * table = malloc(sizeof(int) * length * length);
    //GArray *table = g_array_sized_new(FALSE,TRUE,sizeof(tableCells),pixelList->len);

    for(int i=0;i<pixelList->len;i++) // test content in pixelList TO BE REMOVED
    {
        struct Pixel temp = g_array_index(pixelList,struct Pixel,i);
        //printf("The coords is: %d,%d ", temp.coords.x, temp.coords.y);
        //printf("\t R: %d, G: %d, B: %d\n", temp.RGB.R,temp.RGB.G,temp.RGB.B);
    }
    
    // Loop the following function until pixelList->len==1
    while(pixelList->len > 1)
    {
        minSeeker = 9999;
        for(int i=0;i<pixelList->len;i++)// fill table with weight values by comparing elements of pixelList
        {
            #pragma omp parallel shared(pixelList,candidate,n1,n2)
            {
                #pragma omp for
                for(int j=0;j<pixelList->len;j++)
                {
                    if(i != j)
                    {
                        n1 = g_array_index(pixelList,struct Pixel, i);
                        n2 = g_array_index(pixelList,struct Pixel, j);
                        cellValue = comparePixel(n1,n2);
                        tableInsert(i,j,length,table,cellValue);
                        if(minSeeker > cellValue)
                        {
                            candidate.p1 = n1;
                            candidate.p2 = n2;
                            minSeeker = cellValue;
                        }
                    }
                }
            }
        }
        //at this point candidate is filled with the min weight pixels
        for(int i = 0; i<pixelList->len;i++)
        {
            test1 = g_array_index(pixelList,struct Pixel, i);
            if(comparePixel(n1,test1) == 0 || comparePixel(n2,test1) == 0)
            {
                g_array_remove_index(pixelList,i);
                break;
            }
        }
        for(int i = 0; i<pixelList->len;i++)
        {
            test1 = g_array_index(pixelList,struct Pixel, i);
            if(comparePixel(n1,test1) == 0 || comparePixel(n2,test1) == 0)
            {
                g_array_remove_index(pixelList,i);
                break;
            }
        }
        postClust = clusterToPixel(candidate);
        g_array_append_val(pixelList,postClust);
    }
    printf("Clustering is now complete!");
    return 0;
}