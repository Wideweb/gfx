//
//  LineRender.hpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/11/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#ifndef LineRender_hpp
#define LineRender_hpp

#include "Canvas.hpp"

class LineRender : IRender {
private:
    Canvas& buffer;
public:
    LineRender(Canvas& buffer);
    
    void clear(Color color) override;
    void setPixel(Position point, Color color) override;
    void drawLine(Position from, Position to, Color color);
};

#endif /* LineRender_hpp */
