//
//  Window.cpp
//  hello-render
//
//  Created by Alexander Alkevich on 4/14/20.
//  Copyright © 2020 Alexander Alkevich. All rights reserved.
//

#include "Window.hpp"
#include <iostream>
#include <sstream>

namespace Engine {

static std::ostream& operator<<(std::ostream& out, const SDL_version& v)
{
    out << static_cast<int>(v.major) << '.';
    out << static_cast<int>(v.minor) << '.';
    out << static_cast<int>(v.patch);
    return out;
}

std::string Window::init(const WindowProps& props) {
    using namespace std;
    
    m_Props = props;

    stringstream serr;

    SDL_version compiled = { 0, 0, 0 };
    SDL_version linked   = { 0, 0, 0 };

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    if (SDL_COMPILEDVERSION !=
        SDL_VERSIONNUM(linked.major, linked.minor, linked.patch))
    {
        serr << "warning: SDL2 compiled and linked version mismatch: " << compiled << " " << linked << endl;
    }

    const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
    if (init_result != 0)
    {
        const char* err_message = SDL_GetError();
        serr << "error: failed call SDL_Init: " << err_message << endl;
        return serr.str();
    }

    m_Window = SDL_CreateWindow(
                                "title",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                props.width,
                                props.height,
                                SDL_WINDOW_OPENGL);

    if (m_Window == nullptr)
    {
        const char* err_message = SDL_GetError();
        serr << "error: failed call SDL_CreateWindow: " << err_message
             << endl;
        SDL_Quit();
        return serr.str();
    }
    
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == nullptr)
    {
        const char* err_message = SDL_GetError();
        serr << "error: failed call SDL_CreateRenderer: " << err_message
             << endl;
        SDL_Quit();
        return serr.str();
    }
    
    return "";
}

void Window::setEventCallback(const EventCallbackFn& callback) {
    m_eventCallback = callback;
}

void Window::readInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            //WindowEvent event(EventType::Window);
            //m_eventCallback(event);
            break;
        }
        else if (e.type == SDL_MOUSEMOTION)
        {
            MouseEvent event(e.motion.x, e.motion.y, EventType::MouseMoved);
            m_eventCallback(event);
        }
    }
}

bool Window::draw(void *pixels) {
    using namespace std;
    
    SDL_Surface* bitmapSurface = SDL_CreateRGBSurfaceFrom(
                                                          pixels,
                                                          m_Props.width,
                                                          m_Props.height,
                                                          m_Props.depth,
                                                          m_Props.pitch,
                                                          m_Props.rmask,
                                                          m_Props.gmask,
                                                          m_Props.bmask,
                                                          m_Props.amask);
    if (bitmapSurface == nullptr)
    {
        cerr << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }
    SDL_Texture* bitmapTex =
        SDL_CreateTextureFromSurface(m_Renderer, bitmapSurface);
    if (bitmapTex == nullptr)
    {
        cerr << SDL_GetError() << endl;
        return false;
    }
    SDL_FreeSurface(bitmapSurface);

    SDL_RenderClear(m_Renderer);
    SDL_RenderCopy(m_Renderer, bitmapTex, nullptr, nullptr);
    SDL_RenderPresent(m_Renderer);

    SDL_DestroyTexture(bitmapTex);
    
    return true;
}

void Window::shutDown() {
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    SDL_Quit();
}

}
