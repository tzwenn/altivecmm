#pragma once

#include "Vec.h"
#include "VecBool.h"

namespace altivecmm {

template<typename elemtype>
Vec<elemtype> _if(const VecBool<elemtype> & condition, const Vec<elemtype> & thenvalue, const Vec<elemtype> & elsevalue)
{
	return vec_sel(elsevalue.d(), thenvalue.d(), condition.d());
}

template<typename elemtype>
Vec<elemtype> _if(const VecBool<elemtype> & condition, const Vec<elemtype> & thenvalue)
{
	return _if(condition, thenvalue, Vec<elemtype>());
}

}
