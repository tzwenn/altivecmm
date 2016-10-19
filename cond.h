#pragma once

#include "Vec.h"
#include "VecBool.h"

namespace altivecmm {

template<typename elemtype>
Vec<elemtype> ifthenelse(const VecBool<elemtype> & condition, const Vec<elemtype> & thenValue, const Vec<elemtype> & elseValue)
{
	return vec_sel(elseValue.d(), thenValue.d(), condition.d());
}

template<typename elemtype>
Vec<elemtype> ifthen(const VecBool<elemtype> & condition, const Vec<elemtype> & thenValue)
{
	return ifthenelse(condition, thenValue, Vec<elemtype>());
}

namespace detail {

	template<typename elemtype>
	struct _thenobj
	{
		explicit _thenobj(const VecBool<elemtype> & condition, const Vec<elemtype> & thenValue) :
			m_condition(condition),
			m_thenvalue(thenValue)
		{
			;;
		}

		operator Vec<elemtype>() const
		{
			return ifthen(m_condition, m_thenvalue);
		}

		Vec<elemtype> operator()(const Vec<elemtype> & elsevalue) const
		{
			return ifthenelse(m_condition, m_thenvalue, elsevalue);
		}

	private:
		VecBool<elemtype> m_condition;
		Vec<elemtype> m_thenvalue;
	};

	template<typename elemtype>
	struct _ifobj
	{
		explicit _ifobj(const VecBool<elemtype> & condition) :
			m_condition(condition)
		{
			;;
		}

		detail::_thenobj<elemtype> operator ()(const Vec<elemtype> & thenvalue) const
		{
			return detail::_thenobj<elemtype>(m_condition, thenvalue);
		}

	private:
		VecBool<elemtype> m_condition;
	};
}

//! An element-wise ternary assignment
template<typename elemtype>
detail::_ifobj<elemtype> _if(const VecBool<elemtype> & condition)
{
	return detail::_ifobj<elemtype>(condition);
}

////////////////////////////////////////////////////////////////////////////

template<typename elemtype>
struct _switchobj
{
	// switch (switchValue) {
	explicit _switchobj(const Vec<elemtype> & switchValue) :
		m_switchValue(switchValue)
	{
		;;
	}

	// caseValue: return thenValue;
	_switchobj & operator()(const Vec<elemtype> & caseValue, const Vec<elemtype> & thenValue)
	{
		typename VecBool<elemtype>::vectype eq = vec_cmpeq(*m_switchValue, *caseValue);
		m_resValue = vec_sel(*m_resValue, *thenValue, eq);
		m_filled = vec_or(*m_filled, eq);
		return *this;
	}

	// default: return defaultValue;
	Vec<elemtype> operator()(const Vec<elemtype> & defaultValue) const
	{
		return vec_sel(*defaultValue, *m_resValue, *m_filled);
	}

	operator Vec<elemtype>() const
	{
		return m_filled;
	}

private:
	Vec<elemtype> m_switchValue;
	Vec<elemtype> m_resValue;
	VecBool<elemtype> m_filled;
};

template<typename elemtype>
_switchobj<elemtype> _switch(const Vec<elemtype> & switchValue)
{
	return _switchobj<elemtype>(switchValue);
}

}
