#include <stdio.h>
#include <math.h>
#include <unistd.h>

/* 単位の変換 */
#define DEG_TO_RAD(DEG) (((DEG)*(2*M_PI)/360))
#define RAD_TO_DEG(RAD) (((RAD)*360)/(2*M_PI))

/* 倒立振子のパラメタ */
#define ARM_LENGTH 1
#define PENDULUM_LENGTH 1

int simulate_pendulum(float theta_detg);
float arm_pos[2][3];
float pendulum_pos[2][3];

int main(){
  FILE *gp;
  gp = popen("gnuplot -persist", "w");
  fprintf(gp, "set xrange [-2:2]\n");
  fprintf(gp, "set yrange [-2:2]\n");
  fprintf(gp, "set zrange [-2:2]\n");
  fprintf(gp, "set ticslevel 0\n");

  for(int i=0; i<=360; i++){
    usleep(5000);
    fprintf(gp, "set multiplot\n");

    simulate_pendulum(i);
    
    fprintf(gp, "splot '-' with lines linetype 1\n");
    fprintf(gp, "%f %f %f\n", arm_pos[0][0], arm_pos[0][1], arm_pos[0][2]);
    fprintf(gp, "%f %f %f\n", arm_pos[1][0], arm_pos[1][1], arm_pos[1][2]);
    fprintf(gp, "e\n");

    fprintf(gp, "splot '-' with lines linetype 1\n");
    fprintf(gp, "%f %f %f\n", pendulum_pos[0][0], pendulum_pos[0][1], pendulum_pos[0][2]);
    fprintf(gp, "%f %f %f\n", pendulum_pos[1][0], pendulum_pos[1][1], pendulum_pos[1][2]);
    fprintf(gp, "e\n");

    fprintf(gp, "set nomultiplot\n");
  }
  fprintf(gp, "exit\n");
  fflush(gp);
  pclose(gp);

  return 0;
}

int simulate_pendulum(float theta_deg)
{
  float theta_rad = DEG_TO_RAD(theta_deg);

  /* リソース節約で先に計算しておく */
  float unit_x_pos = cos(theta_rad);
  float unit_y_pos = sin(theta_rad);

  /* armの回転中心 */
  arm_pos[0][0] = 0;
  arm_pos[0][1] = 0;
  arm_pos[0][2] = 0;

  /* armの先端 */
  arm_pos[1][0] = ARM_LENGTH * unit_x_pos;
  arm_pos[1][1] = ARM_LENGTH * unit_y_pos;
  arm_pos[1][2] = 0;

  /* pendulumの回転中心 */
  /* armの先端と同じ */
  pendulum_pos[0][0] = arm_pos[1][0];
  pendulum_pos[0][1] = arm_pos[1][1];
  pendulum_pos[0][2] = arm_pos[1][2];

  /* pendulumの先端 */
  pendulum_pos[1][0] = ARM_LENGTH * unit_x_pos;
  pendulum_pos[1][1] = ARM_LENGTH * unit_y_pos;
  pendulum_pos[1][2] = PENDULUM_LENGTH;

  return 0;
}
