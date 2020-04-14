//
//  Canvas.hpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/11/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <array>

constexpr int width = 640;
constexpr int height = 420;

#pragma pack(push,1)
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    friend bool operator==(const Color& c1, const Color& c2);
};
#pragma pack(pop)

class Canvas : public std::array<Color, width * height> {
public:
    void save(const std::string& fileName);
    void load(const std::string& fileName);
};

struct Position {
    uint16_t x;
    uint16_t y;
    Position(uint16_t x, uint16_t y) : x(x), y(y) {}
    friend bool operator==(const Position& p1, const Position& p2);
};

using Pixels = std::vector<Position>;

class IRender {
public:
    virtual void clear(Color) = 0;
    virtual void setPixel(Position, Color color) = 0;
};

#endif /* Canvas_hpp */
