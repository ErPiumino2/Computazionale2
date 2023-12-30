#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void LeapFrog (double x0, double v0, double omega2, double tmax, double dt);

int main(int argc, char **argv){
	double x0, v0, omega2, tmax, dt;
	//argc : contiene il numero di stringhe inserite dall'utente nella linea di comando +1
	//argv: l'array contiene le stringhe inserite dall'utente (puntatore) 
	if(argc !=6){
		printf("\nInput must be: x0 v0 omega2 tmax dt\n");
		exit(1);
	}

	x0 = atof(argv[1]);//atof legge un float, atoi per gli int
	v0 = atof(argv[2]);
	omega2 = atof(argv[3]);
	tmax = atof(argv[4]);
	dt = atof(argv[5]);

	//printf("%lf %lf %lf %lf %lf", x, v, omega2, tmax, dt);
	LeapFrog(x0, v0, omega2, tmax, dt);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LeapFrog (double x0, double v0, double omega2, double tmax, double dt){
	double x, v, E0, E, n;
	int i;
	n=tmax/dt;
	E0=pow(v0,2) + (omega2*pow(x0,2));
	printf("\t %.2lf \t %.2lf \t 0.00 \t %.2lf\n", x0, v0, E0);
	for(i=1; i<=n; i++){
        x=x0;
        x=x0+(v*dt-0.5*omega2*x0*dt*dt);
        v0=v0-(0.5*omega2*(x+x0)*dt);
        v=v0;
        x0=v*dt;
		E=pow(v0,2) + (omega2*(pow(x0,2)));
		printf("\t %.2lf \t %.2lf \t %.2lf \t %lf\n", x, v, i*dt, E);
	}
}