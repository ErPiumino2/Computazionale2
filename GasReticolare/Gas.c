#include "Funzioni.h"

typedef struct Position{
    int x;
    int y;
}Pos;

int main(int argc, char **argv){
    int N;
    if(argc!=3){
        printf("\nInput must be: ro(density of particle, where ro in [0,1]), L(side of grid)\n");
        exit(1);
    }
    double ro = fabs(atof(argv[1]));
    int L = atoi(argv[2]);
    if(ro<0 || ro>1){immission_error();}
    else{N = L*L*ro;}
    int **reticolo = matrix(L);
    particles(reticolo, ro, L, N);
    //printmatrix(reticolo, L);
}