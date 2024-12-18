#include <Loders/data.hpp>
#include <core/LOG.hpp>

class Cube : public DATA {

public:
  float *Vetexs;
  unsigned int *Element;
  float *Color;
  Cube(); 
  ~Cube() = default; 

  float *GetVertices() override;
  uint16_t GetNbVertices() override;
  uint16_t GetSizeVertices() override;
  uint16_t GetDimVertices() override;
  unsigned int *GetIndices() override;
  uint16_t GetNbIndices() override;
  uint16_t GetSizeIndices() override;
  uint16_t GetDimIndices() override;
  float *GetColor() override;
  uint16_t GetNbColor() override;
  uint16_t GetSizeColor() override;
  uint16_t GetDimColor() override;

};
