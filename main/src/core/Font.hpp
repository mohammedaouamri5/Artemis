#ifndef _FONT_H_
#define _FONT_H_
#include "imgui.h"

namespace CORE
{

    class Font
    {
    private:
    ImFont font;
        
    public:
    void INIT();
    void USE();
    void UNUSE(); 

        Font(/* args */);
        ~Font();
    };

} // namespace CORE

#endif // _FONT_H_