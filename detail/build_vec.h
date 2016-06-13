#pragma once

#include <vector>
#include "../typetable.h"

namespace altivecmm {

	namespace detail {

		// C++ doesn't want me to partially specialize functions. So wrap a struct around it
		template<std::size_t elem_count, typename elemtype>
		struct vec_from_arg;

		template<typename elemtype>
		struct vec_from_arg<2, elemtype> {
			typename typetable<elemtype>::vectype operator() (const elemtype & r0, const elemtype & r1)
			{ return (typename typetable<elemtype>::vectype) {r0, r1}; }
		};

		template<typename elemtype>
		struct vec_from_arg<4, elemtype> {
			typename typetable<elemtype>::vectype operator() (const elemtype & r0, const elemtype & r1, const elemtype & r2, const elemtype & r3)
			{ return (typename typetable<elemtype>::vectype) {r0, r1, r2, r3}; }
		};

		template<typename elemtype>
		struct vec_from_arg<8, elemtype> {
			typename typetable<elemtype>::vectype operator() (const elemtype & r0, const elemtype & r1, const elemtype & r2, const elemtype & r3, const elemtype & r4, const elemtype & r5, const elemtype & r6,  const elemtype & r7)
			{ return (typename typetable<elemtype>::vectype) {r0, r1, r2, r3, r4, r5, r6, r7}; }
		};

		template<typename elemtype>
		struct vec_from_arg<16, elemtype> {
			typename typetable<elemtype>::vectype operator() (const elemtype & r0, const elemtype & r1, const elemtype & r2, const elemtype & r3, const elemtype & r4, const elemtype & r5, const elemtype & r6,  const elemtype & r7,  const elemtype & r8,  const elemtype & r9,  const elemtype & r10,  const elemtype & r11,  const elemtype & r12,  const elemtype & r13,  const elemtype & r14,  const elemtype & r15)
			{ return (typename typetable<elemtype>::vectype) {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15}; }
		};

		////////////////////////////////////

		template<std::size_t elem_count, typename elemtype>
		struct vec_from_stdvec;

		template<typename elemtype>
		struct vec_from_stdvec<2, elemtype> {
			typename typetable<elemtype>::vectype operator() (const std::vector<elemtype> & r)
			{ return (typename typetable<elemtype>::vectype) {r[0], r[1]}; }
		};

		template<typename elemtype>
		struct vec_from_stdvec<4, elemtype> {
			typename typetable<elemtype>::vectype operator() (const std::vector<elemtype> & r)
			{ return (typename typetable<elemtype>::vectype) {r[0], r[1], r[2], r[3]}; }
		};

		template<typename elemtype>
		struct vec_from_stdvec<8, elemtype> {
			typename typetable<elemtype>::vectype operator() (const std::vector<elemtype> & r)
			{ return (typename typetable<elemtype>::vectype) {r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7]}; }
		};

		template<typename elemtype>
		struct vec_from_stdvec<16, elemtype> {
			typename typetable<elemtype>::vectype operator() (const std::vector<elemtype> & r)
			{ return (typename typetable<elemtype>::vectype) {r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9], r[10], r[11], r[12], r[13], r[14], r[15]}; }
		};
	 }

}
