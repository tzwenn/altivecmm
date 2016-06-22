#pragma once

#include <iterator>
#include "typetable.h"

namespace altivecmm {

namespace detail {

template<std::size_t elem_count, typename elemtype>
struct splat;

template<typename elemtype>
struct splat<2, elemtype> {
	typename typetable<elemtype>::vectype operator() (const elemtype & value)
	{ return (typename typetable<elemtype>::vectype) {value, value}; }
};

template<typename elemtype>
struct splat<4, elemtype> {
	typename typetable<elemtype>::vectype operator() (const elemtype & value)
	{ return (typename typetable<elemtype>::vectype) {value, value, value, value}; }
};

template<typename elemtype>
struct splat<8, elemtype> {
	typename typetable<elemtype>::vectype operator() (const elemtype & value)
	{ return (typename typetable<elemtype>::vectype) {value, value, value, value, value, value, value, value}; }
};

template<typename elemtype>
struct splat<16, elemtype> {
	typename typetable<elemtype>::vectype operator() (const elemtype & value)
	{ return (typename typetable<elemtype>::vectype) {value, value, value, value, value, value, value, value, value, value, value, value, value, value, value, value}; }
};


}}
