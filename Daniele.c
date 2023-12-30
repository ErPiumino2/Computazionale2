include <math.h>
#include <stdio.h>
#include<time.h>
#include <stdlib.h>


#define NMAX 1000
#define V 9
#define Nsim 500

typedef struct {
    int x;
    int y;
} Particle;

void Stampa_Reticolo(int L, int Reticolo[L][L]) 
{
    for (int i = 0; i < L; i++) 
    {
        for (int j = 0; j < L; j++)
        {
            printf("%d ", Reticolo[i][j]);
        }
        printf("\n");
    }
}

void Stampa_pos(int N, Particle *particles) 
{
    FILE *fp;
    fp =fopen("Reticolo.dat", "w");
    printf("Posizioni delle particelle:\n");
    for (int i = 0; i < N; i++) 
    {
        printf("Particella %d: x = %d, y = %d\n", i+1, particles[i].x, particles[i].y);
        fprintf(fp,"%d %d %d\n", i+1, particles[i].x, particles[i].y);
    }
    fclose(fp);
}

double Spostamento_quad(int N,Particle *NonP,Particle *t0)
{
    double somma=0;
    for(int i=0;i<N;i++)
    {
        somma+=(NonP[i].x-t0[i].x)*(NonP[i].x-t0[i].x)+(NonP[i].y-t0[i].y)*(NonP[i].y-t0[i].y);
    }
    return somma/(double) N;
}


int main()
{
    int N,L; //N rappresenta il numero di part e L la dim del reticolo
    double n,m;
    double avg[NMAX];
    FILE *fp;
    Particle particles[N];
    int Reticolo[L][L];
    Particle t0[N];
    Particle NonP[N];
    fp =fopen("Reticolo.dat", "w");
    srand(time(NULL));
    printf("Inserisci la dimensione del reticolo: ");
    scanf("%d", &L);
    printf("Inserisci il numero di particelle: ");
    scanf("%d", &N);
    if (N > L * L)
     {
        printf("Il numero di particelle Ã¨ troppo grande per il reticolo.\n");
        return 1;
    }
    for(int i=0;i<NMAX;i++)
{
    avg[i]= 0;
}
    for(int k=0;k<Nsim;k++)
{
    for (int i = 0; i < L; i++) 
    {
        for (int j = 0; j < L; j++) 
        {
            Reticolo[i][j] = 0;
        }
    }
    for (int i = 0; i < N; i++)
     {
        int x, y;
        do {
            x = rand() % L;
            y = rand() % L;
        } while (Reticolo[x][y] != 0);
        Reticolo[x][y] = 1;
        particles[i].x = x;
        particles[i].y = y;
        t0[i].x = particles[i].x ;
        t0[i].y = particles[i].y ;
        NonP[i].x = particles[i].x;
        NonP[i].y = particles[i].y;
        //fprintf(fp,"%d %d %d\n", i+1, particles[i].x, particles[i].y);
    }
    for(int j=0;j<NMAX;j++)
    {
        for (int i = 0; i < N; i++)
    {
         n = (double)rand() / (RAND_MAX);
         m = (double)rand() / (RAND_MAX);
         //printf("%lf \n",n);
         if(n>=0.5)
         {
            particles[i].x = (particles[i].x +1);
            NonP[i].x = (particles[i].x +1);
            if((particles[i].x + 1) >= L)
            {
                particles[i].x = 0;
            }
         }
         else if (n<0.5)
         {
            particles[i].x = (particles[i].x - 1);
            NonP[i].x = (particles[i].x - 1);
            if((particles[i].x + 1) <= 0)
            {
                particles[i].x = L;
            }
         }
        if(m>=0.5)
         {
            particles[i].y = (particles[i].y +1);
            NonP[i].y = (particles[i].y + 1);
            if((particles[i].y + 1) >= L)
            {
                particles[i].y = 0;
            }
         }
         else if (m<0.5)
         {
            particles[i].y = (particles[i].y - 1);
            NonP[i].y = (particles[i].y - 1);
            if((particles[i].y + 1) <= 0)
            {
                particles[i].y = L;
            }
         }
         for(int k=i;k>=(i-N) && (i-N)>0 ;k--)
         {
            if(particles[i].x==particles[k].x && particles[i].y==particles[k].y)
            {
                particles[i].x = particles[i-N].x;
                particles[i].y = particles[i-N].y;
            }
         }
         //printf("Particella %d: x = %d, y = %d\n", i+1, particles[i].x,particles[i].y);
         //fprintf(fp,"%d %d %d\n", i+1, particles[i].x,particles[i].y);
    }
    avg[j]+=Spostamento_quad(N,NonP,t0);
 }
}
FILE *fd;
fd=fopen("Avg1.dat", "w");
for(int i=0;i<NMAX;i++)
{
    avg[i]= avg[i]/(4*(i)*Nsim);
    fprintf(fd,"%d %f \n",i,avg[i]);
}

//Stampa_Reticolo(L, Reticolo);   //0 indica posizione vuota e 1 indica posizione occupata
//Stampa_pos(N, particles); //Serve per graficare con python
fclose(fp);
fclose(fd);
}