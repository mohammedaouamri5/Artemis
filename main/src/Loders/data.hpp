#ifndef __DATA_HPP__
#define __DATA_HPP__

#include <cstdint>
class DATA {
public:
    virtual float *GetVertices() = 0;
    virtual uint16_t GetNbVertices() = 0;
    virtual uint16_t GetSizeVertices() = 0;
    virtual uint16_t GetDimVertices() = 0;

    virtual unsigned int *GetIndices() = 0;
    virtual uint16_t GetNbIndices() = 0;
    virtual uint16_t GetSizeIndices() = 0;
    virtual uint16_t GetDimIndices() = 0;

    virtual float *GetColor() = 0;
    virtual uint16_t GetNbColor() = 0;
    virtual uint16_t GetSizeColor() = 0;
    virtual uint16_t GetDimColor() = 0;

};
#endif // __DATA_HPP__
