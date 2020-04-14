//
//  main.cpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/11/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "Application.hpp"

class myGfxProgram : public GfxProgram {
private:
    float mouseX;
    float mouseY;
    float radius;
    
public:
    void setUniforms(const Uniforms &uniforms) override {
        mouseX = uniforms.f0;
        mouseY = uniforms.f1;
        radius = uniforms.f2;
    }
    
    Vertex vertexShader(const Vertex& vertex) override {
        Vertex out;
        
        float dx = mouseX - vertex.f0;
        float dy = mouseY - vertex.f1;
        float angle = std::atan2(dy, dx);
        float t = 1 - (dx * dx + dy * dy) / (radius * radius);
        
        if (dx * dx + dy * dy < radius * radius) {
            out.f0 = vertex.f0 - radius / 4 * t * cos(angle);
            out.f1 = vertex.f1 - radius / 4 * t * sin(angle);
        } else {
            out.f0 = vertex.f0;
            out.f1 = vertex.f1;
        }
        
        out.f2 = vertex.f2;
        out.f3 = vertex.f3;
        out.f4 = vertex.f4;
        
        return out;
    }

    Color fragmentShader(const Vertex& vertex) override {
        
        float dx = mouseX - vertex.f0;
        float dy = mouseY - vertex.f1;
        float t = (dx * dx + dy * dy) / (radius * radius);
        
        uint8_t r = static_cast<uint8_t>(vertex.f2);
        uint8_t g = static_cast<uint8_t>(vertex.f3);
        uint8_t b = static_cast<uint8_t>(vertex.f4);
        
        if (dx * dx + dy * dy < radius * radius) {
            r = r * t + 255 * (1 - t);
            g = g * t;
            b = b * t;
        }
        
        return {r, g, b};
    }
};

class myApp : public Engine::Application {
private:
    std::vector<Vertex> m_Vertexes;
    std::vector<int> m_Indexes;
    myGfxProgram m_Program;
    
    const float m_TileSize = 10.0f;
    
public:
    myApp() {
        const float tilesNumberX = width / m_TileSize + 1;
        const float tilesNumberY = height / m_TileSize + 1;
        
        for (int i = 0; i < tilesNumberY; i++) {
            for (int j = 0; j < tilesNumberX; j++) {
                m_Vertexes.push_back({j * m_TileSize, i * m_TileSize, 0.0, 255.0, 0.0});
            }
        }
        
        for (int i = 0; i < tilesNumberY - 1; i++) {
            for (int j = 0; j < tilesNumberX - 1; j++) {
                m_Indexes.push_back(i * tilesNumberX + j);
                m_Indexes.push_back(i * tilesNumberX + j);
                m_Indexes.push_back(i * tilesNumberX + j + 1);
                
                m_Indexes.push_back(i * tilesNumberX + j);
                m_Indexes.push_back(i * tilesNumberX + j);
                m_Indexes.push_back((i + 1) * tilesNumberX + j);
            }
        }
        
        m_Render->setProgram(m_Program);
    }
    
    void render() override {
        m_Render->clear({0, 0, 0});
        m_Render->drawTriangles(m_Vertexes, m_Indexes);
    }
    
    void onMouseEvent(Engine::MouseEvent &e) override {
        if (e.type == Engine::EventType::MouseMoved) {
            float x = e.x;
            float y = e.y;
            float radius = 100;
            m_Program.setUniforms({x, y, radius});
        }
    }
    
    ~myApp() {}
};

int main(int argc, const char * argv[]) {
    auto app = new myApp();
    app->run();
    delete app;
    
    return 0;
}
