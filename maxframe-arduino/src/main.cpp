#include <Arduino.h>
#include "maxframe.h"

#define WIDTH 32
#define HEIGHT 8

const uint16_t BUFFER_SIZE = (WIDTH * HEIGHT) / 8; // 32
uint8_t framebuffer[BUFFER_SIZE];
Maxframe max;

void setup()
{
  max.init(10, WIDTH, HEIGHT, framebuffer);
  max.brightness(1);
  // memset(framebuffer, 0x01, BUFFER_SIZE);

  for (int i = 0; i < 32; i++)
  {
    framebuffer[i] = i;
  }

  max.display();
}

void loop()
{
}