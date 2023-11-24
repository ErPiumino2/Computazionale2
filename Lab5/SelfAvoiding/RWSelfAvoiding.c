//2D self avoiding random walk
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include <stdbool.h>

typedef int iterator;
typedef unsigned long int randn;

struct RandomParameters{
    randn seed;
    randn n; //Number Generated
};

void RW(int argc, char **argv);
bool Check(int **walk, int x, int y, int step);
int Random(struct RandomParameters *RP);

int main(int argc, char **argv){
    RW(argc, argv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void RW(int argc, char **argv){
    randn min=1, max=4, x;
    struct RandomParameters RP;
    iterator nmax, n=1;
    FILE *fp;
    if(argc !=4){
		printf("\nInput must be: x0(starting point), y0(starting point), nmax(total number of steps)\n");
		exit(1);
	}
    nmax = atoi(argv[3]);
    //////////////////Creating 2dimensional array using calloc//////////////////
    int **position=(int**)calloc(nmax, sizeof(int*)); 
    for(int i=0; i<nmax; i++) {
        position[i] = (int *) calloc(2, sizeof(int));
    }
    ////////////////////////////////////////////////////////////////////////////
    int currentX = atoi(argv[1]); 
    int currentY = atoi(argv[2]); 
    position[0][0] = currentX; //x values of first columns
    position[0][1] = currentY; //y values of second columns
    RP.seed = time(NULL);
    fp = fopen("/workspaces/Computazionale2/Lab5/File/SelfAvoiding.dat", "w+");
    fprintf(fp, "%i \t %i \t %i\n", position[0][0], position[0][1], 0);
    while (n < nmax){
        x = Random(&RP);
        x = min + (x % (max - min + 1)); //Get x within rangeX
        // Move in the chosen direction
        switch (x) {
            case 1: //Up
                currentY++;
                break;
            case 2: //Down
                currentY--;
                break;
            case 3: //Left
                currentX--;
                break;
            case 4: //Right
                currentX++;
                break;
        }
        // Check if the new position has already been visited
        if (!Check(position, currentX, currentY, n)) {
            position[n][0] = currentX;
            position[n][1] = currentY;
            n++;
        }
        fprintf(fp, "%i \t %i \t %i\n", position[n-1][0], position[n-1][1], n-1);
    }
    fclose(fp);
    //Free the allocated memory
    for (int i = 0; i < nmax; i++) {
        free(position[i]);
    }
    free(position);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Random(struct RandomParameters *RP){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    return RP->n;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
bool Check(int **walk, int x, int y, int step) {
    for (int i = 0; i < step; i++) {
        if (walk[i][0] == x && walk[i][1] == y) {
            return true;
        }
    }
    return false;
}