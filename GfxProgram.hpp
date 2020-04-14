//
//  GfxProgram.hpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/13/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#ifndef GfxProgram_hpp
#define GfxProgram_hpp

#include "Canvas.hpp"

struct Vertex {
    float f0; //x
    float f1; //y
    float f2; //r
    float f3; //g
    float f4; //b
};

struct Uniforms {
    float f0;
    float f1;
    float f2;
    float f3;
    float f4;
};

class GfxProgram {
public:
    virtual void setUniforms(const Uniforms& uniforms) = 0;
    virtual Vertex vertexShader(const Vertex& vertex) = 0;
    virtual Color fragmentShader(const Vertex& vertex) = 0;
};

#endif /* GfxProgram_hpp */
