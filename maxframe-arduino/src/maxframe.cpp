/*
Maxframe
https://github.com/slpuk/maxframe

Licensed under Apache-2.0
Copyright 2026 slpuk
*/

#include "maxframe.h"

void Maxframe::write(uint8_t reg, uint8_t data)
{
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(_ss, LOW);
    SPI.transfer(reg);
    SPI.transfer(data);
    digitalWrite(_ss, HIGH);
    SPI.endTransaction();
}

void Maxframe::init(uint8_t cs, uint16_t width, uint16_t height, uint8_t *ex_buffer)
{
    _ss = cs;
    _width = width;
    _height = height;
    _buffer = ex_buffer;
    _cascade_size = (_width / 8) * (_height / 8);

    pinMode(_ss, OUTPUT);
    digitalWrite(_ss, HIGH);
    SPI.begin();

    write(REG_DISPLAY_TEST, 0x00);
    write(REG_DECODE_MODE, 0x00);
    write(REG_SCAN_LIMIT, 0x07);
    write(REG_INTENSITY, 0x07);
    write(REG_SHUTDOWN, 0x01);

    clear();
    display();
}

void Maxframe::shutdown(bool state)
{
    write(REG_SHUTDOWN, !state);
}

void Maxframe::brightness(uint8_t level)
{
    if (level > 15)
        level = 15;
    write(REG_INTENSITY, level);
}

void Maxframe::clear()
{
    uint16_t total_bytes = (_width * _height) / 8;
    memset(_buffer, 0, total_bytes);
}

void Maxframe::display()
{
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));

    for (uint8_t row = 0; row < 8; row++)
    {
        digitalWrite(_ss, LOW);

        for (int16_t ce = (_cascade_size * 8) - 1; ce >= 7; ce -= 8)
        {
            uint8_t data = _buffer[ce - 7 + row];

            SPI.transfer(REG_DIGIT0 + row);
            SPI.transfer(data);
        }

        digitalWrite(_ss, HIGH);
    }

    SPI.endTransaction();
}
