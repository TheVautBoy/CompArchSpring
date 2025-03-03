#include <stdio.h>
#include <omp.h>
#define N 4096
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
int main()
{
  float a[N];
  int i, i_min, i_max, rang, nb_taches;

  /* La répartition STATIC consiste à diviser les itérations en paquets
d'une taille donnée (sauf peut-être pour le dernier).
Il est ensuite attribué, d'une façon cyclique à chacune des tâches,
un ensemble de paquets suivant l'ordre des tâches jusqu'à concurrence 
du nombre total de paquets*/

#pragma omp parallel private(rang,nb_taches,i_min,i_max)
  {
    rang=omp_get_thread_num();
    nb_taches=omp_get_num_threads();
    i_min=N, i_max=0;

#pragma omp for schedule(static) nowait
    for (i=0; i<N; i++) {
      a[i] = 92291. + (float) i;
      i_min=min(i_min,i);
      i_max=max(i_max,i);
    }
    printf("Rang : %d; i_min : %d; i_max : %d\n",rang,i_min,i_max);
  }
  return 0;
}
