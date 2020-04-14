//
//  IndexedTriangleRender.hpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/12/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#ifndef IndexedTriangleRender_hpp
#define IndexedTriangleRender_hpp

#include <vector>
#include "TriangleRender.hpp"

class IndexedTriangleRender : public TriangleRender {
public:
    IndexedTriangleRender(Canvas& buffer) : TriangleRender(buffer) {}
    
    void drawTriangles(Pixels vertexes, std::vector<int> indexes, Color color);
};

#endif /* IndexedTriangleRender_hpp */
