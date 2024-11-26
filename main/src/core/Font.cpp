



#include "Font.hpp"


namespace CORE
{

    void Font::INIT(){

    }
    void Font::USE(){
        ImGui::PushFont(*(this->font));
    }
    void Font::UNUSE(){
        ImGui::PopFont();

    } 
    
    
} // namespace CORE
