#pragma once

#include <altivec.h>
#include <ostream>

#include "typetable.h"
#include "detail/build_vec.h"

namespace altivecmm {

	template<typename elemtype>
	class Vec
	{
	public:
		using typeinfo = typetable<elemtype>;
		using vectype = typename typeinfo::vectype;

		template<typename... Args>
		static Vec construct(Args &&... args)
		{
			using typeinfo = typetable<elemtype>;
			static_assert(!(sizeof...(Args) > typeinfo::elem_count), "Too many arguments for this vector type");
			static_assert(!(sizeof...(Args) < typeinfo::elem_count),  "Too few arguments for this vector type");
			return detail::vec_from_arg<typeinfo::elem_count, elemtype>()(args...);
		}

		////////////////////////////////////

		Vec(std::initializer_list<elemtype> list) :
			m_d(detail::vec_from_stdvec<typeinfo::elem_count, elemtype>()(list))
		{
			;;
		}

		Vec(const elemtype * data) :
			m_d(vec_ld(typeinfo::elem_count, data))
		{
			;;
		}

		template<typename S>
		Vec(const Vec<S> & other) :
			m_d(other.m_d)
		{
			;;
		}

		Vec(const vectype & d) :
			m_d(d)
		{
			;;
		}

		////////////////////////////////////

		Vec & operator +=(const Vec & other)
		{
			m_d = vec_add(m_d, other.m_d);
			return *this;
		}

		Vec & operator -=(const Vec & other)
		{
			m_d = vec_sub(m_d, other.m_d);
			return *this;
		}

		Vec & operator *=(const Vec & other)
		{
			m_d = vec_mul(m_d, other.m_d);
			return *this;
		}

		Vec & operator /=(const Vec & other)
		{
			m_d = vec_mul(m_d, other.m_d);
			return *this;
		}


		////////////////////////////////////

		Vec operator +(const Vec & other) const
		{
			return vec_add(m_d, other.m_d);
		}

		Vec operator -(const Vec & other) const
		{
			return vec_sub(m_d, other.m_d);
		}

		Vec operator *(const Vec & other) const
		{
			return vec_mul(m_d, other.m_d);
		}

		Vec operator /(const Vec & other) const
		{
			return vec_div(m_d, other.m_d);
		}

		////////////////////////////////////

		Vec operator &(const Vec & other) const
		{
			return vec_and(m_d, other.m_d);
		}

		Vec operator ^(const Vec & other) const
		{
			return vec_xor(m_d, other.m_d);
		}

		////////////////////////////////////

		Vec operator ~() const
		{
			return vec_nand(m_d, m_d);
		}

		Vec abs() const
		{
			return vec_abs(m_d);
		}

		//! Returns the saturated absolute values of this vector
		Vec abss() const
		{
			return vec_abss(m_d);
		}

		//! Returns a vector containing the carry produced by adding this vector
		Vec add_carry(const Vec & other) const
		{
			return vec_addc(m_d, other.m_d);
		}

		////////////////////////////////////

		vectype d() const
		{
			return m_d;
		}

		operator vectype() const
		{
			return m_d;
		}

		////////////////////////////////////

		std::ostream& print(std::ostream & stream) const
		{
			stream << "Vec<" << typeinfo::typestr << ">{" << +m_d[0];
			for (int i = 1; i < typeinfo::elem_count; i++) {
				stream << ", " << +m_d[i];
			}
			stream << "}";
			return stream;
		}

	protected:
		vectype m_d;

	};

}

template<typename elemtype>
std::ostream &operator<<(std::ostream & stream, const altivecmm::Vec<elemtype> & vec)
{
	return vec.print(stream);
}
