#include <stdio.h>

int main(int argc, char *argv[])
{
FILE* filePtr = fopen("pixelOutput.txt","r");
if(filePtr==NULL)
{
    printf("Input file not found.");
    return 0;
}

int xPos, yPos, redChan, greenChan, blueChan;
while (fscanf(filePtr,"%d %*c %d %*c %*c %d %*s %d %*s  %d %*s",&xPos,&yPos,&redChan,&greenChan,&blueChan))
{
    printf("X position: %d\n",xPos);
    printf("Y position: %d\n",yPos);
    printf("\tRed channel: %d\n",redChan);
    printf("\tGreen channel: %d\n",greenChan);
    printf("\tBlue channel: %d\n", blueChan);
    if(feof(filePtr))
    {
        break;
    }
}
return 0;
}