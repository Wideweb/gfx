//
//  TriangleRender.hpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/12/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#ifndef TriangleRender_hpp
#define TriangleRender_hpp

#include <vector>
#include "LineRender.hpp"

class TriangleRender : public LineRender {
public:
    TriangleRender(Canvas& buffer);
    
    void drawTriangle(Pixels points, Color color);
};

#endif /* TriangleRender_hpp */
