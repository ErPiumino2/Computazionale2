#include "Funzioni.h"

int main(int argc, char **argv){
    if(argc!=4){
        printf("\nInput must be: ro(density of particle, where ro in [0,1]), L(side of grid), m(moves)\n");
        exit(1);
    }
    int N;
    srand(time(NULL));
    double ro = fabs(atof(argv[1]));
    int L = atoi(argv[2]);
    int m = atoi(argv[3]);
    if(ro<0 || ro>1){immission_error();}
    else{N = L*L*ro;}
    int **reticolo = matrix(L);
    Pos *particelle = array(N, sizeof(Pos));
    spawn(reticolo, particelle, L, N);
    printmatrix(reticolo, L);
    for(int i=0; i<m; i++){
        move(reticolo, particelle, N, L);
        printf("\n");
        printmatrix(reticolo, L);
    }
}