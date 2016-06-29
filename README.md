# AltiVecMM

A C++ wrapper around the [AltiVec (VMX) intrinsics in GCC](https://gcc.gnu.org/onlinedocs/gcc/PowerPC-AltiVec_002fVSX-Built-in-Functions.html). It is highly incomplete, incoherent, and unoptimized. But it allows you to use vector instructions on IBM's POWER architecture with a nicer interface, that is e.g. templately interchangeable with native scalar types.

## Usage

This library uses header-only templates. Clone it into your project or a convenient folder in your include path.

Your compiler must support the GCC AltiVec (preferably VSX) extensions and C++11.

```bash
CXXFLAGS+="-mvsx -std=c++11"
```

AltiVecMM's vectors are defined using their element types as template arguments. Each vector type provides information about the number and size of its elements.

```C++
#include <altivecmm/altivecmm.h>

altivecmm::Vec<double> doubleVec{-1, 2};
altivecmm::Vec<unsigned int> uintVec{2, 1, 0, -1};

using floatInfo = altivecmm::Vec<float>::typeinfo;
std::cout << "altivecmm::Vec<" << floatInfo::typestr << "> has " 
          << floatInfo::elem_count << " elements of " 
          << floatInfo::elem_bits << " bits each."
          << std::endl;
// prints: altivecmm::Vec<float> has 4 elements of 32 bits each.
```

AltiVecMM defines operators on vectors. When scalar types are combined with vectors they are treated like a vector with all elements set to this value.

```C++
altivecmm::Vec<double> v0{-1, 2};
altivecmm::Vec<double> v1{ 3, 4};
altivecmm::Vec<double> allTwo(2);

std::cout << "v0 - v1 = " << v0 - v1 << std::endl;
std::cout << "allTwo = " << allTwo << std::endl;
std::cout << "v0 * 2 = " << v0 * 2 << std::endl;
std::cout << "(v0 / v1).abs() = " << (v0 / v1).abs() << std::endl;

/* prints:
v0 - v1 = Vec<double>{-4, -2}
allTwo = Vec<double>{2, 2}
v0 * 2 = Vec<double>{-2, 4}
(v0 / v1).abs() = Vec<double>{0.333333, 0.5}
*/

```

## Notes

Unfortunately the template approach requires proper C++ element types and thus forecloses the AltiVec types `vector bool (char|short|int|long)` and `vector pixel`. They can nonetheless be emulated using `unsigned (char|short|int|long)`, respectively `unsigned short`.

Double precision floating point vectors are only available if compiled for POWER7 or later, and 64 bit integer types only for POWER8 or later.