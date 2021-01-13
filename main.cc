#include "bm.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

const double SPRING_CONSTANT = 1000.0;
const double GRAVITY = 0.1;
const double GAMMA = 0.1;
const double dt = 0.01;

struct d2 {
  double x, y;
};
std::vector<d2> p, q;
std::vector<double> stress;
std::vector<int> bond1;
std::vector<int> bond2;
std::vector<double> b_length;
double s_time = 0.0;

void add_particle(double x, double y) {
  d2 q2, p2;
  q2.x = x;
  q2.y = y;
  p2.x = 0.0;
  p2.y = 0.0;
  q.push_back(q2);
  p.push_back(p2);
}

void add_bond(int i1, int i2) {
  bond1.push_back(i1);
  bond2.push_back(i2);
  double dx = q[i1].x - q[i2].x;
  double dy = q[i1].y - q[i2].y;
  double l = dx * dx + dy * dy;
  b_length.push_back(l);
}

void calculate(void) {
  const int pn = q.size();
  for (int i = 0; i < pn; i++) {
    stress[i] = 0.0;
  }
  for (int i = 0; i < pn; i++) {
    q[i].x += p[i].x * dt;
    q[i].y += p[i].y * dt;
  }
  for (int k = 0; k < bond1.size(); k++) {
    const int i1 = bond1[k];
    const int i2 = bond2[k];
    const double dx = q[i2].x - q[i1].x;
    const double dy = q[i2].y - q[i1].y;
    const double r2 = dx * dx + dy * dy;
    const double f = SPRING_CONSTANT * (r2 - b_length[k]);
    stress[i1] += f * f;
    stress[i2] += f * f;
    p[i1].x += f * dx * dt;
    p[i1].y += f * dy * dt;
    p[i2].x -= f * dx * dt;
    p[i2].y -= f * dy * dt;
  }
  for (int i = 0; i < pn; i++) {
    p[i].x -= p[i].x * GAMMA * dt;
    p[i].y += -p[i].y * GAMMA * dt - GRAVITY * dt;
    if (q[i].y < 0) {
      p[i].y -= 10.0 * q[i].y * dt;
    }
  }
  s_time += dt;
}

void loadfile(void) {
  double x;
  double y;
  while (!std::cin.fail()) {
    std::cin >> x >> y;
    add_particle(x, y);
  }
  const int pn = q.size();
  stress.resize(pn, 0.0);
}

void show_particle(void) {
  const int pn = q.size();
  for (int i = 0; i < pn; i++) {
    printf("%f %f\n", q[i].x, q[i].y);
  }
}

void connect_bond(void) {
  const int pn = q.size();
  for (int i = 0; i < pn - 1; i++) {
    for (int j = i + 1; j < pn; j++) {
      const double dx = q[i].x - q[j].x;
      const double dy = q[i].y - q[j].y;
      const double r2 = dx * dx + dy * dy;
      if (r2 > 3.1) continue;
      add_bond(i, j);
    }
  }
}

void savetopov(int index) {
  char filename[256];
  sprintf(filename, "data%03d.pov", index);
  index++;
  std::ofstream ofs(filename);
  const int pn = q.size();
  ofs << "#include \"hito.inc\"" << std::endl;
  ofs << "merge{" << std::endl;
  for (int i = 0; i < pn; i++) {
    double ic = 1.0 - stress[i] * 0.0005;
    if (ic < 0.0) ic = 0.0;
    ofs << "object{ sphere {<";
    ofs << q[i].x << ",";
    ofs << q[i].y << ",0>,1.5}" << std::endl;
    ofs << "interior{ ior 1.0} " << std::endl;
    ofs << "pigment{ color <1.0,";
    ofs << ic << "," << ic;
    ofs << "> filter 0.7 }}" << std::endl;
    ofs << std::endl;
  }
  ofs << "}" << std::endl;
  printf("%s\n", filename);
}

void savetobmp(int index) {
  const int pn = q.size();
  const double mag = 4.0;
  const double R = 1.0;
  int LX = 60 * mag;
  int LY = 60 * mag;
  WindowsBitmap canvas(LX, LY);
  canvas.SetColor(255, 255, 255);
  canvas.FillRect(0, 0, LX, LY);
  for (int i = 0; i < pn; i++) {
    int ic = stress[i] * 0.2;
    if (ic > 255) ic = 255;
    canvas.SetColor(ic, 0, 0);
    int ix = (int)(q[i].x * mag);
    int iy = (int)(q[i].y * mag);
    int ir = (int)(R * mag);
    canvas.FillCircle(ix, iy, ir);
  }
  char filename[256];
  sprintf(filename, "data%03d.bmp", index);
  index++;
  canvas.SaveToFile(filename);
  printf("%s\n", filename);
}

int main(void) {
  loadfile();
  connect_bond();
  int index = 0;
  for (int i = 0; i < 20000; i++) {
    if (i % 200 == 0) {
      savetobmp(index);
      savetopov(index);
      index++;
    }
    calculate();
  }
}