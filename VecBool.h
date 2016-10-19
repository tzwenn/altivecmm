#pragma once

#include "detail/typetable_bool.h"

namespace altivecmm {

template<typename elemtype>
class VecBool
{
public:
	using typeinfo = detail::typetable_bool<elemtype>;
	using vectype = typename typeinfo::vectype;

	VecBool()
	{
		m_d = vec_xor(m_d, m_d);
	}

	VecBool(vectype d) :
		m_d(d)
	{
		;;
	}

	template<typename S>
	VecBool(const VecBool<S> & other) :
		m_d(other.d)
	{
		;;
	}

	vectype d() const
	{
		return m_d;
	}

	vectype operator *() const
	{
		return m_d;
	}

	operator vectype() const
	{
		return m_d;
	}

protected:
	vectype m_d;
};

}
