//2D self avoiding random walk
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
int Check(int **walk, int x, int y, int step);
int Random(struct RandomParameters *RP);
int Trapped(int **walk, int step);
void Python(int trapped[6]);

int main(int argc, char **argv){
    RW(argc, argv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void RW(int argc, char **argv){
    randn p;
    struct RandomParameters RP;
    iterator nmax;
    int trapped[6];
    FILE *fp;
    if(argc !=4){
		printf("\nInput must be: x0(starting point), y0(starting point), nmax(total number of steps)\n");
		exit(1);
	}
    RP.seed = time(NULL);
    nmax = atoi(argv[3]);
    for(int k=0; k<6; k++){
        //////////////////Creating 2dimensional array using calloc//////////////////
        int **position=(int**)calloc(nmax, sizeof(int*)); 
        for(int i=0; i<nmax; i++) {
            position[i] = (int *) calloc(2, sizeof(int));
        }
        ////////////////////////////////////////////////////////////////////////////
        int n=1;
        position[0][0] = atoi(argv[1]);
        position[0][1] = atoi(argv[2]);
        char NomeFile[70];
        sprintf(NomeFile, "/workspaces/Computazionale2/RandomWalk/File/SelfAvoidingn=%i.dat", nmax-2);
        fp = fopen(NomeFile, "w+");
        while(n<nmax){
            //Check if the starting position of every cycle is trapped
            if(Trapped(position, n-1)==1){
                    printf("Trapped at %i \t\t %i \t\t %i\n", position[n-1][0], position[n-1][1], n-1);
                    fprintf(fp, "%i \t\t %i \t\t %i\n", position[n-1][0], position[n-1][1], n-1);
                    trapped[k]=1;
                    break;
            }
            p = (Random(&RP) % 4 + 4) % 4 + 1; //x will be in the range [1, 4]
            int dx=0, dy=0;
            // Move in the chosen direction
            switch (p) {
                case 1: // Up
                    dy = -1;
                    break;
                case 2: // Down
                    dy = 1;
                    break;
                case 3: // Left
                    dx = -1;
                    break;
                case 4: // Right
                    dx = 1;
                    break;
            }
            // Check if the new position has already been visited
            if(Check(position, position[n-1][0]+dx, position[n-1][1]+dy, n) == 0){
                position[n][0] = position[n-1][0] + dx;
                position[n][1] = position[n-1][1] + dy;
                fprintf(fp, "%i \t\t %i \t\t %i\n", position[n-1][0], position[n-1][1], n-1);
                n++;
            }
        }
        fclose(fp);
        //Free the allocated memory
        for (int i=0; i<nmax; i++) {
            free(position[i]);
        }
        free(position);
        nmax = (nmax-2)*5 +2;
    }
    Python(trapped);
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
int Check(int **walk, int x, int y, int step) {
    int controllo = 0;
    for (int i=0; i<step; i++){
        if (walk[i][0] == x && walk[i][1] == y) {
            controllo = 1;
        }
    }
    return controllo;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Trapped(int **walk, int step){
    // Check all possible moves
    if(
    Check(walk, walk[step][0]+1, walk[step][1]+0, step) == 1  &&  
    Check(walk, walk[step][0]-1, walk[step][1]+0, step) == 1  &&  
    Check(walk, walk[step][0]+0, walk[step][1]+1, step) == 1  && 
    Check(walk, walk[step][0]+0, walk[step][1]-1, step) == 1) {
        return 1;
    }
    else{
        return 0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void Python(int trapped[6]){
    FILE *py;
    py = fopen("RWSelfAvoiding.py", "w+");
fprintf(py, "import matplotlib.pyplot as plt\n");
fprintf(py, "import numpy as np\n");
fprintf(py, "from matplotlib.ticker import MultipleLocator\n");
fprintf(py, "fig, ax = plt.subplots(3,2)\n");
fprintf(py, "fig.set_figwidth(20)\n");
fprintf(py, "fig.set_figheight(20)\n");
fprintf(py, "fig.suptitle('Self Avoiding Random Walk for various number of steps', fontsize=20)\n");
fprintf(py, "x1, y1 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/SelfAvoidingn=10.dat', usecols=(0, 1), unpack=True)\n");
fprintf(py, "x2, y2 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/SelfAvoidingn=50.dat', usecols=(0, 1), unpack=True)\n");
fprintf(py, "x3, y3 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/SelfAvoidingn=250.dat', usecols=(0, 1), unpack=True)\n");
fprintf(py, "x4, y4 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/SelfAvoidingn=1250.dat', usecols=(0, 1), unpack=True)\n");
fprintf(py, "x5, y5 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/SelfAvoidingn=6250.dat', usecols=(0, 1), unpack=True)\n");
fprintf(py, "x6, y6 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/SelfAvoidingn=31250.dat', usecols=(0, 1), unpack=True)\n");
fprintf(py, "N1 = len(x1)\n");
fprintf(py, "N2 = len(x2)\n");
fprintf(py, "N3 = len(x3)\n");
fprintf(py, "N4 = len(x4)\n");
fprintf(py, "N5 = len(x5)\n");
fprintf(py, "N6 = len(x6)\n");
fprintf(py, "#Vari plot\n");
fprintf(py, "ax[0,0].plot(x1, y1, color='skyblue', label=f'Random Walk 10 steps',  zorder=-1)\n");
fprintf(py, "ax[0,1].plot(x2, y2, color='skyblue', label=f'Random Walk 50 steps',  zorder=-1)\n");
fprintf(py, "ax[1,0].plot(x3, y3, color='skyblue', label=f'Random Walk 250 steps',  zorder=-1)\n");
fprintf(py, "ax[1,1].plot(x4, y4, color='skyblue', label=f'Random Walk 1250 steps',  zorder=-1)\n");
fprintf(py, "ax[2,0].plot(x5, y5, color='skyblue', label=f'Random Walk 6250 steps',  zorder=-1)\n");
fprintf(py, "ax[2,1].plot(x6, y6, color='skyblue', label=f'Random Walk 31250 steps',  zorder=-1)\n");
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
for(int k=0; k<6; k++){
    if(trapped[k]==1){
        fprintf(py, "ax[0,0].plot([], [], '', label=f'Trapped at: ({x%i[-1]:.0f}, {y%i[-1]:.0f})', zorder=1, alpha=0)\n", k+1, k+1);
    }
}
fprintf(py, "for ax in ax.flat:\n");
fprintf(py, "    ax.legend(fontsize=10)\n");
fprintf(py, "    ax.set(xlabel='x', ylabel='y')\n");
fprintf(py, "    ax.xaxis.set_major_locator(MultipleLocator(1))\n");
fprintf(py, "    ax.yaxis.set_major_locator(MultipleLocator(1))\n");
fprintf(py, "    ax.xaxis.set_minor_locator(MultipleLocator(0.5))\n");
fprintf(py, "    ax.yaxis.set_minor_locator(MultipleLocator(0.5))\n");
fprintf(py, "    # Vari plot\n");
fprintf(py, "    ax.grid(which='major', color='#DDDDDD', linewidth=0.8, zorder=-2)\n");
fprintf(py, "    ax.grid(which='minor', color='#EEEEEE', linestyle=':', linewidth=0.5, zorder=-2)\n");
fprintf(py, "    ax.minorticks_on()\n");
fprintf(py, "plt.savefig('SelfAvoiding.png')\n");
}