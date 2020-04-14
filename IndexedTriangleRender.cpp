//
//  IndexedTriangleRender.cpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/12/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#include "IndexedTriangleRender.hpp"

void IndexedTriangleRender::drawTriangles(Pixels vertexes, std::vector<int> indexes, Color color) {
    for (size_t i = 0; i < indexes.size(); i += 3){

        drawTriangle({
            vertexes.at(indexes.at(i)),
            vertexes.at(indexes.at(i + 1)),
            vertexes.at(indexes.at(i + 2))
        }, color);

    }
}
