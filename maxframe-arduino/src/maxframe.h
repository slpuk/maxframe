/*
Maxframe
https://github.com/slpuk/maxframe

Licensed under Apache-2.0
Copyright 2026 slpuk
*/

#ifndef MAXFRAME_H
#define MAXFRAME_H

#include <stdint.h>
#include <string.h>
#include <Arduino.h>
#include <SPI.h>

#define REG_NOOP 0x00
#define REG_DIGIT0 0x01
#define REG_DECODE_MODE 0x09
#define REG_INTENSITY 0x0A
#define REG_SCAN_LIMIT 0x0B
#define REG_SHUTDOWN 0x0C
#define REG_DISPLAY_TEST 0x0F

class Maxframe
{
private:
    uint8_t _ss;
    uint16_t _width;
    uint16_t _height;
    uint16_t _cascade_size;
    uint8_t *_buffer;

    void write(uint8_t reg, uint8_t data);

public:
    void init(uint8_t cs, uint16_t width, uint16_t height, uint8_t *ex_buffer);
    void shutdown(bool state);
    void brightness(uint8_t level);
    void clear();
    void display();
};

#endif
