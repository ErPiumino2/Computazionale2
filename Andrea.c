#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct phasespace{
  double x;  /*posizione lunglo l'asse x*/
  double v;
  double a;
  double k1;
  double k2;
  double k3;
  double k4;
  double dt1;
  /*double F;*/
};
struct input{
  double T;
  double dt; /*passo di integrazione*/
  double w;  /*omega quadro*/
  double x0; /*posizione iniziale in radianti*/
  double v0; /*velocità iniziale*/
  double w1; /*frequenza forzante*/
  double g;  /*coefficiente di attrito dipendente dalla velocità*/
  double f1;
  double f2;
  double f3;
  double f4;
  double f5;
  double f;
};

/*double rk4(struct phasespace ph, struct input inp);
{
  struct ph.k1;
  struct ph.k2;
  struct ph.k3;
  struct ph.k4;
  struct ph.x;
  struct ph.v;
  double k=1./6;
  k1=f(x,dt1,g);
  x=x(1,x,g,k1);
 
  k2=f(x,dt1,g);
  x=x(1,x,0.5,k2);

  k3=f(x,dt1,g);
  x=x(1,x,1,k3);

  k4=f(x,dt1,g);

  x=x(1.,x,(1./6.),x(1.,x(1,k1,2.,k2),1.,x()2.,k3,1.,k4));
  v=x(1.,x(1.,k1,2.,k2),1.,x(2.,k3,1.,k4));
  x=(1.,x,k,k1,k2,k3,k4);
  return x, v;
}*/
double rk4(struct phasespace ph, struct input inp){
  struct phasespace ph;
  struct input inp;
  double k=1./6.;
  double F;
  F=-inp.g*ph.v-inp.w*sin(ph.x)+inp.f*cos(inp.w1*ph.dt1);
  ph.k1=F(ph.a,ph.dt1,inp.g);
  ph.a=ph.x(1,ph.x,0.5, ph.k1);

  ph.k2=F(ph.a,ph.dt1,inp.g);
  ph.a=ph.x(1,ph.x,0.5,ph.k2);

  ph.k3=F(ph.a,ph.dt1,inp.g);
  ph.a=ph.x(1,ph.x,1,ph.k3);
  ph.k4=F(ph.a,ph.dt1,inp.g);
 
  ph.a=ph.x(1.,ph.x,1./6,ph.x(ph.x(1.,ph.k1,2.,ph.k2),1.,ph.x(2.,ph.k3,1.,ph.k4)));
 
  return ph.x, ph.v;
}


int main(){
  struct phasespace ph;
  struct input inp;
  inp.f1=0.90;
  inp.f2=1.07;
  inp.f3=1.15;
  inp.f4=1.47;
  inp.f5=1.50;
  FILE*fp1;
  FILE*fp2;
  FILE*fp3;
  FILE*fp4;
  FILE*fp5;
  inp.w1=2./3.;
  inp.x0=M_PI/2.;
  inp.g=0.5;
  printf("l'input deve essere:T,dt, w, v0\n");
  scanf("%lf %lf %lf %lf", &inp.T,&inp.dt,&inp.w,&inp.v0);
  double n=(double)inp.T/inp.dt;

  inp.f=inp.f1;
  ph.x=inp.x0;
  ph.v=inp.v0;
  fp1=fopen("f0=0.90.dat","w");
  for(int i=0; i<n; i++){
    ph.dt1=i*inp.dt;
    rk4;
    fprintf(fp1,"%lf %lf %lf",ph.x, ph.v, ph.dt1);
  }
  fclose(fp1);
 
  inp.f=inp.f2;
  ph.x=inp.x0;
  ph.v=inp.v0;
  fp2=fopen("f1=1.07.dat","w");
  for(int i=0; i<n; i++){
    ph.dt1=i*inp.dt;
    rk4;
    fprintf(fp2,"%lf %lf", ph.x, ph.v);
  }
  fclose(fp2);
 
  inp.f=inp.f3;
  ph.x=inp.x0;
  ph.v=inp.v0;
  fp3=fopen("f2=1.15.dat","w");
  for(int i=0; i<n; i++){
    ph.dt1=i*inp.dt;
    rk4;
    fprintf(fp3,"%lf %lf",ph.x,ph.v);
  }
  fclose(fp3);
 
  inp.f=inp.f4;
  ph.x=inp.x0;
  ph.v=inp.v0;
  fp4=fopen("f3=1.47.dat","w");
  for(int i =0; i<n; i++){
    ph.dt1=i*inp.dt;
    rk4;
    fprintf(fp4,"%lf %lf",ph.x, ph.v);
  }
  fclose(fp4);
 
  inp.f=inp.f5;
  ph.x=inp.x0;
  ph.v=inp.v0;
  fp5=fopen("f5=1.50.dat","w");
  for(int i=0; i<n; i++){
    ph.dt1=i*inp.dt;
    rk4;
    fprintf(fp5,"%lf %lf",ph.x,ph.v);
  }
  fclose(fp5);
}
