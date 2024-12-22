
#include <LOG.hpp>

#include "Font.hpp"

namespace CORE {
Font::Font(const char *fontPath, float fontSize)
    : font(nullptr), path(fontPath), size(fontSize) {}

void Font::INIT() {
  LOG_INFO("WOW");
  auto &io = ImGui::GetIO();
  LOG_INFO("WOW {:x}", (uint64_t)font);
  font = io.Fonts->AddFontFromFileTTF(path, size);
  LOG_INFO("WOW {:x}", (uint64_t)font);
  // if (!font)
    // LOG_CRITICAL("Failed to load font: {}", path);
}

void Font::USE() const {
  if (font) {
    ImGui::PushFont(font);
  } else {
    LOG_ERROR("Font is not initialized. Did you call INIT()?");
  }
}

void Font::UNUSE() const { ImGui::PopFont(); }

Font::~Font() {
  // Font memory is managed by ImGui, no explicit cleanup needed
}
} // namespace CORE
