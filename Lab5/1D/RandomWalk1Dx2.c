#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

typedef int iterator;
typedef unsigned long int randn;

struct RandomParameters{
    randn seed;
    randn n; //Number Generated
};

void RW(int argc, char **argv);
int Random(struct RandomParameters *RP);

int main(int argc, char **argv){
    RW(argc, argv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void RW(int argc, char **argv){
    double x2mean=0, x2error=0;
    randn min=1, max=2, x, r;
    struct RandomParameters RP;
    iterator nmax, n, i, dn, iterations;
    FILE *fp;
    if(argc !=4){
		printf("\nInput must be: x0(starting point), tmax(total time of integration), k(number of total RW for x(t)^2, must be tmax%k==0)\n");
		exit(1);
	}
    nmax = atoi(argv[2]);
    iterations = atoi(argv[3]);
    if((nmax%iterations)!=0 || nmax<iterations){
        printf("\nError, number of iterations must be an int, not a float...\n");
        exit(1);
    }
    RP.seed = time(NULL);
    dn = nmax/iterations;
    fp = fopen("/workspaces/Computazionale2/Lab5/File/<x2>.dat", "w+");
    for(n=0; n<=nmax; n+=dn){
        r = atoi(argv[1]);
        x2mean = 0;
        x2error = 0;
        for(i=0; i<n; i++){
            x = Random(&RP);
            x = min + (x % (max - min + 1)); //Get x within range
            if(x==1){ //Going right
                r += 1;}
            if(x==2){ //Going left
                r -= 1;}
            x2mean += x*x;
            x2error += x*x*x*x;
        }
        fprintf(fp, "%.2lf \t %.2lf \t %i\n", x2mean/iterations, x2error/iterations, n);
    }
    fclose(fp);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Random(struct RandomParameters *RP){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    return RP->n;
}