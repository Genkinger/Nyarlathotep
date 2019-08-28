//
// Created by genkinger on 8/27/19.
//

#ifndef NYARLATHOTEP_WINDOW_HPP
#define NYARLATHOTEP_WINDOW_HPP

#include "../core/common.hpp"
#include <GLFW/glfw3.h>
#include "../core/string/NString.hpp"

namespace Nyarlathotep::Graphics {
    class Window {
    private:
        i32 mWidth = 0, mHeight = 0;
        GLFWwindow *mWindow = nullptr;
    public:
        Window(i32 width, i32 height, NString title){
            glfwInit();
        }
        void Update(){}
        void Swap(){}
    };
}

#endif //NYARLATHOTEP_WINDOW_HPP
