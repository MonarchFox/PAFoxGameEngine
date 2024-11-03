#pragma once

#ifndef CHECK_TRUE_THROW_H
#define CHECK_TRUE_THROW_H

#include <stdexcept>
#include <string>

#define CHECK_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            throw std::runtime_error(message); \
        } \
    } while (0)

#endif


#define SAFE_RELEASE(p, status) \
    if (p != nullptr) {         \
        if (!p->Release())      \
        {                       \
            status = false;     \
        }                       \
    }                           \

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x) \
{ \
HRESULT hr = (x); \
if(FAILED(hr)) \
{ \
DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
} \
}
#endif
#else
#ifndef HR
#define HR(x) (x)
#endif
#endif
