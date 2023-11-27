//1D Random Walk with different probability for each pass
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

int n;

typedef unsigned long int randn;

struct RandomParameters{
    randn seed;
    randn n;//Number Generated
};
struct Probability{
    double p;
    double q;//q=1-p
};

void RW(int argc, char **argv);
int Random(struct RandomParameters *RP, struct Probability *P);
void Python(double p, int n0);

int main(int argc, char **argv){
    RW(argc, argv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void RW(int argc, char **argv){
    randn x;
    struct RandomParameters RP;
    struct Probability P;
    int r; //r equal position
    FILE *fp, *fp1;
    if(argc !=4 || atof(argv[3])<0 || atof(argv[3])>1){
		printf("\nInput must be: x0(starting point), n(number of initial steps), p(probability of going right on first step, where p in [0;1])\n");
		exit(1);
	}
    n = atoi(argv[2]);
    P.p = atof(argv[3]);
    P.q = 1-P.p;
    RP.seed = time(NULL);
    for(int k=0; k<6; k++){ //based on n, increasing each time
        r = atoi(argv[1]); //Initial position, has to be initialized
        char NomeFile[60];
        sprintf(NomeFile, "/workspaces/Computazionale2/Lab5/File/RWTrapn=%ip=%.2lf.dat", n, P.p);
        fp = fopen(NomeFile, "w+");
        fprintf(fp, "%i \t %i\n", r, 0);
        for(int i=0; i<n; i++){
            x = Random(&RP, &P);
            switch (x){
            case 1:
                r ++; //Going right
                break;
            case 2:
                r --; //Going left
                break;
            }
            fprintf(fp, "%i \t %i\n", r, i+1);
        }
        fclose(fp);
        n += 5*n;
    }
    Python(P.p, atof(argv[2]));
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Random(struct RandomParameters *RP, struct Probability *P){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169, x; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    double randomValue = (double)RP->n / m; //Convert RP->n to a value between 0 and 1
    if (randomValue < P->p) {//Check if the random number falls within the desired probability
        x = 1; //Probability of going right
    } else {
        x = 2; //Probability of going left, 1-p
    }
    double temp = P->p;
    P->p = P->q;
    P->q = temp;
    //printf("%.2lf \t %.2lf\n", P->p, P->q);
    return x;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void Python(double p, int n0){
    FILE *py;
    int n[6];
    for(int i=0; i<6; i++){
        n[i] = n0;
        n0 += 5*n0;
    }
    py = fopen("RWTrap.py", "w+");
fprintf(py, "import matplotlib.pyplot as plt\n");
fprintf(py, "import numpy as np\n");
fprintf(py, "from matplotlib.ticker import MultipleLocator\n");
fprintf(py, "fig, ax = plt.subplots(3,2)\n");
fprintf(py, "fig.set_figwidth(20)\n");
fprintf(py, "fig.set_figheight(20)\n");
fprintf(py, "fig.suptitle('1D Random walk with probability p=%.2lf for various number of steps', fontsize=20)\n", p);
for(int i=0; i<6; i++){
fprintf(py, "y%i, x%i = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RWTrapn=%ip=%.2lf.dat', usecols=(0, 1), unpack=True)\n", i+1, i+1, n[i], p);
fprintf(py, "N%i = len(x%i)\n", i+1, i+1);
}
fprintf(py, "#Vari plot\n");
fprintf(py, "ax[0,0].plot(x1, y1, color='skyblue', label=f'Random Walk %i steps',  zorder=-1)\n", n[0]);
fprintf(py, "ax[0,1].plot(x2, y2, color='skyblue', label=f'Random Walk %i steps',  zorder=-1)\n", n[1]);
fprintf(py, "ax[1,0].plot(x3, y3, color='skyblue', label=f'Random Walk %i steps',  zorder=-1)\n", n[2]);
fprintf(py, "ax[1,1].plot(x4, y4, color='skyblue', label=f'Random Walk %i steps',  zorder=-1)\n", n[3]);
fprintf(py, "ax[2,0].plot(x5, y5, color='skyblue', label=f'Random Walk %i steps',  zorder=-1)\n", n[4]);
fprintf(py, "ax[2,1].plot(x6, y6, color='skyblue', label=f'Random Walk %i steps',  zorder=-1)\n", n[5]);
fprintf(py, "#Initial Points plots\n");
fprintf(py, "ax[0,0].scatter(x1[0], y1[0], color='red', label=f'Starting Point: ({x1[0]:.0f}, {y1[0]:.0f})',  zorder=1)\n");
fprintf(py, "ax[0,1].scatter(x2[0], y2[0], color='red', label=f'Starting Point: ({x2[0]:.0f}, {y2[0]:.0f})',  zorder=1)\n");
fprintf(py, "ax[1,0].scatter(x3[0], y3[0], color='red', label=f'Starting Point: ({x3[0]:.0f}, {y3[0]:.0f})',  zorder=1)\n");
fprintf(py, "ax[1,1].scatter(x4[0], y4[0], color='red', label=f'Starting Point: ({x4[0]:.0f}, {y4[0]:.0f})',  zorder=1)\n");
fprintf(py, "ax[2,0].scatter(x5[0], y5[0], color='red', label=f'Starting Point: ({x5[0]:.0f}, {y5[0]:.0f})',  zorder=1)\n");
fprintf(py, "ax[2,1].scatter(x6[0], y6[0], color='red', label=f'Starting Point: ({x6[0]:.0f}, {y6[0]:.0f})',  zorder=1)\n");
fprintf(py, "#Final Points plots\n");
fprintf(py, "ax[0,0].scatter(x1[-1], y1[-1], color='darkslategrey', label=f'Final Point:  ({x1[-1]:.0f}, {y1[-1]:.0f})', zorder=1)\n");
fprintf(py, "ax[0,1].scatter(x2[-1], y2[-1], color='darkslategrey', label=f'Final Point:  ({x2[-1]:.0f}, {y2[-1]:.0f})', zorder=1)\n");
fprintf(py, "ax[1,0].scatter(x3[-1], y3[-1], color='darkslategrey', label=f'Final Point:  ({x3[-1]:.0f}, {y3[-1]:.0f})', zorder=1)\n");
fprintf(py, "ax[1,1].scatter(x4[-1], y4[-1], color='darkslategrey', label=f'Final Point:  ({x4[-1]:.0f}, {y4[-1]:.0f})', zorder=1)\n");
fprintf(py, "ax[2,0].scatter(x5[-1], y5[-1], color='darkslategrey', label=f'Final Point:  ({x5[-1]:.0f}, {y5[-1]:.0f})', zorder=1)\n");
fprintf(py, "ax[2,1].scatter(x6[-1], y6[-1], color='darkslategrey', label=f'Final Point:  ({x6[-1]:.0f}, {y6[-1]:.0f})', zorder=1)\n");
fprintf(py, "#Empty plots\n");
fprintf(py, "for ax in ax.flat:\n");
fprintf(py, "    ax.legend(fontsize=10)\n");
fprintf(py, "    ax.set(xlabel='t', ylabel='y')\n");
fprintf(py, "plt.savefig('RWTrapP=%.2lf.png')\n", p);
}