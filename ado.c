#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//BUFFON NEEDLES

// 0 <= x <= d/2
// 0 <= theta <= PI/2

void save_pi(unsigned, unsigned, float, unsigned);

int main(void) {
  unsigned line_dis = 2;
  unsigned needles = 5000000;
  float needle_size = 0.8;
  double pi_1, pi_2;

  printf("\n=== ADO ===\n");

  pid_t id = fork();

  if (id == 0) {
    save_pi(line_dis, needles, needle_size, 0);
  }
  else {
    //espera o primeiro executar.
    wait(NULL);

    //sleep 1 para mudar a seed do random.
    sleep(1);

    save_pi(line_dis, needles, needle_size, 1);

    FILE *file1;
    file1 = fopen("file1", "r");
    fscanf(file1, "%lf", &pi_1);
    fclose(file1);

    FILE *file2;
    file2 = fopen("file2", "r");
    fscanf(file2, "%lf", &pi_2);
    fclose(file2);

    printf("\nValor aproximado de PI: %lf\n", (pi_1 + pi_2)/2);
  }

  return 0;
}

void save_pi(unsigned line_dis, unsigned needles, float needle_size, unsigned file_num) {
  unsigned hits = 0;
  double theta, x, pi;
  char file_name[6];
  char pi_n[9];

  if (file_num) {
    strcpy(file_name, "file1");
  }
  else {
    strcpy(file_name, "file2");
  }

  FILE *file;
  file = fopen(file_name, "w");
  if (!file) {
    printf("\nUnable to create file!\n");
    exit(1);
  }

  srand(time(0));

  for (int i=0; i < needles; i++) {
    //centro da agulha
    x = ((double)rand()/RAND_MAX) * line_dis/2;

    //angulo da agulha
    theta = ((double)rand()/RAND_MAX) * M_PI/2;

    //se caiu na linha
    if (x <= ((needle_size/2)*sin(theta))) {
      hits++;
    }
  }

  pi = (2*needle_size/line_dis) * needles/hits;

  sprintf(pi_n, "%lf", pi); 
  fprintf(file, pi_n);
  fclose(file);
}
