
#ifndef _WIN_H_
#define _WIN_H_

#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "Layout.hpp"
#include <vector>
namespace CORE
{

    class Win
    {
    public:
        void INIT()  ;
        void INIT_LOOP() ;
        void RUN() ;
        void ADD(Layout* layout){
             Layouts.push_back(layout) ;
             
        }
        void CLEAR_LOOP();
        void CLOSE();

    private:
        std::vector<Layout*> Layouts {};
        GLFWwindow * window;
    
    };

} // namespace CORE

#endif // _WIN_H_