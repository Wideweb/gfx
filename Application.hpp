//
//  Application.hpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/14/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <memory>
#include "Window.hpp"
#include "InterpolatedTriangleRender.hpp"

namespace Engine {

class Application {
protected:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<InterpolatedTriangleRender> m_Render;
    Canvas m_Canvas;
    
    bool m_Running = true;
public:
    Application();
    virtual ~Application();
    
    virtual void render() = 0;
    virtual void onMouseEvent(MouseEvent& e);
    virtual void onWindowEvent(WindowEvent& e);
    
    void run();
};
    
}
#endif /* Application_hpp */
