#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

int n;

typedef int iterator;
typedef unsigned long int randn;

struct RandomParameters{
    randn seed;
    randn n; //Number Generated
};
struct Position{
    int x;
    int y;
};

void RW(int argc, char **argv);
int Random(struct RandomParameters *RP);

int main(int argc, char **argv){
    RW(argc, argv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void RW(int argc, char **argv){
    randn min=1, max=4, x;
    struct RandomParameters RP;
    struct Position r;
    iterator i, k, ktot, j;
    FILE *fp;
    if(argc !=5){
		printf("\nInput must be: x0(starting point), y0(starting point), n(number of steps), k(number of total random walks)\n");
		exit(1);
	}
    n = atoi(argv[3]);
    ktot = atoi(argv[4]);
    RP.seed = time(NULL);
    for(j=0; j<6; j++){
        r.x = atoi(argv[1]); //Initial position
        r.y = atoi(argv[2]); //Initial position
        char NomeFile[60];
        sprintf(NomeFile, "/workspaces/Computazionale2/RandomWalk/File/RW2DHiston=%i.dat", n);
        fp = fopen(NomeFile, "w+");
        for(k=0; k<ktot; k++){ //Doing ktot different random walks 
            r.x = atoi(argv[1]); //Initial position
            r.y = atoi(argv[2]); //Initial position
            for(i=0; i<n; i++){ //Main cycle 
                x = Random(&RP);
                x = min + (x % (max - min + 1)); //Get x within range
                if(x==1){ //Going up, following clockwise 1,2,3,4
                    r.y += 1;}
                if(x==2){ //Going right, following clockwise 1,2,3,4
                    r.x += 1;}
                if(x==3){ //Going down, following clockwise 1,2,3,4
                    r.y -= 1;}
                if(x==4){ //Going left, following clockwise 1,2,3,4
                    r.x -= 1;}
            }
            fprintf(fp, "%i \t %i\n", r.x, r.y); //Fprinting the final position of each RW
        }
        fclose(fp);
        n+=5*n; //Increasing the steps, studying the histogram for various number of steps
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Random(struct RandomParameters *RP){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    return RP->n;
}