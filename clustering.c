//#include <omp.h>
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
    printf("DBUG4a\n");
    GArray *row = g_array_index(table, GArray*, x);
    printf("DBUG4b\n");
    g_array_insert_val(row, y, input);
    printf("DBUG4c\n");
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
            //parallelize  inner loop? HARD
            for(int j=0;j<pixelList->len;j++)
            {
                printf("Iteration of i: %d, j: %d\n",i,j);
                if(i != j)
                {
                    printf("DBUG1\n");
                    n1 = g_array_index(pixelList,struct Pixel, i);
                    printf("DBUG2\n");
                    n2 = g_array_index(pixelList,struct Pixel, j);
                    printf("DBUG3\n");
                    cellValue = comparePixel(n1,n2);
                    printf("DBUG4\n");
                    tableInsert(i,j,table,cellValue);
                    printf("DBUG5\n");
                    if(minSeeker > cellValue)
                    {
                        candidate.p1 = n1;
                        candidate.p2 = n2;
                        minSeeker = cellValue;
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
        // so remove n1 and n2 from pixelList DONE
        postClust = clusterToPixel(candidate);
        g_array_append_val(pixelList,postClust);
        //  do clusterToPixel and insert into pixelList DONE
    }
    return 0;
}