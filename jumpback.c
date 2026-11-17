/*
JumpBack (reverse claster order) algorithm
https://github.com/slpuk/maxframe

Licensed under Apache-2.0
Copyright 2026 slpuk
*/

#include <stdint.h>

#define WIDTH 16
#define HEIGHT 8

#define BUFFER_SIZE ((WIDTH * HEIGHT) / 8)        // 16 bytes
#define CASCADE_SIZE ((WIDTH / 8) * (HEIGHT / 8)) // 2 matrices

/*
{
{0,0,0,0,0,0,0,0},    // first cluster = first matrix
{0,0,0,0,0,0,0,0}     // second cluster
}

(In the code it becomes: {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
framebuffer layout: [matrix0: 8 bytes][matrix1: 8 bytes]... - matrix-major
*/
uint8_t framebuffer[BUFFER_SIZE] = {0};

int main()
{
    for (uint8_t row = 0; row < 8; row++)
    {
        for (int16_t ce = (CASCADE_SIZE * 8) - 1; ce >= 7; ce -= 8)
        {
            uint8_t data = framebuffer[ce - 7 + row];

            // Transferring data to matrices:
            // MAX72XX: 16-bit packet = address + data
            // transfer(REG_DIGIT0 + row);
            // transfer(data);
        }
    }

    return 0;
}
