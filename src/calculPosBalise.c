#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculPosition (double longueur, int nbBalise)
{
  double angle, tmp, seg, radians;
  angle = (double)360/nbBalise;
  radians = angle*M_PI/(double)180;
  seg = sqrt(pow(longueur, 2) + pow(longueur, 2) - ((2*longueur*longueur)*cos(radians)));
  
  printf("[ANGLE] %f\n",angle);
  printf("SEG = sqrt(l^2 + l^2 - 2l*l * cos(angle))\n");
  printf("SEG = %f\n\n", seg);
  
  return seg;
}

int main (int argc, char **argv)
{
  if (argc < 2)
    {
      printf("USAGE: ./%s longueur nbBalise\n",argv[0]);
      return EXIT_FAILURE;
    }
  
  double longueur, seg;
  int nbBalise;
  longueur = atof(argv[1]);
  nbBalise = atoi(argv[2]);
  
  seg = calculPosition(longueur, nbBalise);
  printf("[DIST]  %f cm\n",seg);

  return EXIT_SUCCESS; 
}
