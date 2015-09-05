#include "Checker.h"

Checker::Checker(int _x, int _y)
{
    x = _x;
    y = _y;
}

std::string Checker::getBits()
{
    std::string bits = "";
    bits += r >= 128 ? '1' : '0';
    bits += g >= 128 ? '1' : '0';
    bits += b >= 128 ? '1' : '0';
    std::cout << bits << "\n";
    return bits;
}
