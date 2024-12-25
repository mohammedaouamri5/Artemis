#ifndef __DATA_HPP__
#define __DATA_HPP__

#include <cstdint>
#include <exception>

namespace Loader {
class DATA {
public:
  virtual float *GetVertices() { return NULL; };
  virtual uint64_t GetNbVertices() { return -1; };
  virtual uint64_t GetSizeVertices() { return -1; };
  virtual uint64_t GetDimVertices() { return -1; };
  virtual unsigned int *GetIndices() { return NULL; };
  virtual uint64_t GetNbIndices() { return -1; };
  virtual uint64_t GetSizeIndices() { return -1; };
  virtual uint64_t GetDimIndices() { return -1; };
  virtual float *GetColor() { return NULL; };
  virtual uint64_t GetNbColor() { return -1; };
  virtual uint64_t GetSizeColor() { return -1; };
  virtual uint64_t GetDimColor() { return -1; };
};
}      // namespace Loader
#endif // __DATA_HPP__
