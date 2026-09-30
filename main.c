#include <math.h>
#include <stdio.h>
#include <unistd.h> // usleep için

void renderPoint(float x, float y, float z, char ch);

#define LINES 24
#define COLS 80

char buffer[LINES][COLS] = {0};
float zbuffer[LINES][COLS] = {0};

float origin_x = COLS / 2.0f;
float origin_y = LINES / 2.0f;
float z = -5;

float edges[4][2] = {{-5, -5}, {5, -5}, {5, 5}, {-5, 5}};

float B = 0.0f;
float A = 0.0f;

// kamera
float K1 = 15.0f;
// çizim kameraya kıyasla ne kadar çizdiriliceği
float K2 = 18.0f;

float sinA, cosA, sinB, cosB;

int main() {

  printf("\x1b[2J");

  while (1) {
    for (int i = 0; i < LINES; i++) {
      for (int j = 0; j < COLS; j++) {
        buffer[i][j] = ' ';
        zbuffer[i][j] = 0.0f;
      }
    }

    sinA = sin(A), cosA = cos(A);
    sinB = sin(B), cosB = cos(B);

    for (float i = -5; i < 5; i += 0.2f) {
      for (float j = -5; j < 5; j += 0.2f) {

        renderPoint(j, i, -5.0f, '#'); // Ön yüz
        renderPoint(j, i, 5.0f, '$');  // Arka yüz
        renderPoint(-5.0f, i, j, '~'); // Sol yüz
        renderPoint(5.0f, i, j, ';');  // Sağ yüz
        renderPoint(j, -5.0f, i, '+'); // Alt yüz
        renderPoint(j, 5.0f, i, '@');  // Üst yüz
      }
    }

    for (int i = 0; i < LINES; i++) {
      for (int j = 0; j < COLS; j++) {
        putchar(buffer[i][j]);
      }
      putchar('\n');
    }

    B += 0.06;
    A += 0.04;
    usleep(30000);
  }

  return 0;
}

void renderPoint(float x, float y, float z, char ch) {
  // 1. Y ekseninde rotasyon (B açısı)
  float rot_x = x * cosB + z * sinB;
  float rot_y = y;
  float rot_z = -x * sinB + z * cosB;

  // 2. X ekseninde rotasyon (A açısı - küpü bize doğru eğer)
  float final_y = rot_y * cosA - rot_z * sinA;
  float final_z = rot_y * sinA + rot_z * cosA;

  float screen_z = K2 + final_z;
  float ooz = 1.0f / screen_z;

  int screen_x = (int)(0.5f + origin_x + (2.5f * K1 * ooz * rot_x));
  int screen_y = (int)(0.5f + origin_y + (K1 * ooz * final_y));

  if (screen_x >= 0 && screen_x < COLS && screen_y >= 0 && screen_y < LINES) {
    if (ooz > zbuffer[screen_y][screen_x]) {
      zbuffer[screen_y][screen_x] = ooz;
      buffer[screen_y][screen_x] = ch;
    }
  }
}