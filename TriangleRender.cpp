//
//  TriangleRender.cpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/12/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#include "TriangleRender.hpp"

TriangleRender::TriangleRender(Canvas& buffer) : LineRender(buffer) {}

void TriangleRender::drawTriangle(Pixels points, Color color) {
    drawLine(points[0], points[1], color);
    drawLine(points[1], points[2], color);
    drawLine(points[2], points[0], color);
}
