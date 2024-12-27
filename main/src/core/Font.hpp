#ifndef _FONT_H_
#define _FONT_H_
#include "imgui.h"

namespace CORE {

class Font {
private:
  ImFont *font;     // Use a pointer since ImGui manages the font memory
  const char *path; // Path to the font file
  float size;       // Font size

public:
  Font(const char *fontPath, float fontSize);
  
  void INIT();
  void USE() const;
  void UNUSE() const;
  ~Font();
};

} // namespace CORE

#endif // _FONT_H_
