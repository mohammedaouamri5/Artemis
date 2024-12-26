#ifndef __LOADER_LAYOUR_HPP__
#define __LOADER_LAYOUR_HPP__

#include "Layout.hpp"
class LoaderLayour : public CORE::Layout {

public:
  void INIT() override;
  void RUN() override;
  void DIST() override;
};

#endif
