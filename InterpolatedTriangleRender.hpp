//
//  InterpolatedTriangleRender.hpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/12/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#ifndef InterpolatedTriangleRender_hpp
#define InterpolatedTriangleRender_hpp

#include "IndexedTriangleRender.hpp"
#include "GfxProgram.hpp"

class InterpolatedTriangleRender : public IndexedTriangleRender {
private:
    GfxProgram* m_Program;
    Vertex interpolate(Vertex v0, Vertex v1, float t);
    float interpolate(float from, float to, float t);
    bool isCollinear(Vertex v0, Vertex v1, Vertex v2);
    
public:
    InterpolatedTriangleRender(Canvas& buffer) : IndexedTriangleRender(buffer) {}
    
    void setProgram(GfxProgram& program);
    
    void drawTriangles(std::vector<Vertex> vertexes, std::vector<int> indexes);
    
    std::vector<Vertex> rasterizeTriange(Vertex v0, Vertex v1, Vertex v2);
};

#endif /* InterpolatedTriangleRender_hpp */
