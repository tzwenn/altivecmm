#pragma once

namespace altivecmm { namespace detail {

template<typename T>
struct typetable_bool;

template <>
struct typetable_bool<char> {
	using vectype = __vector bool char;
	static constexpr const char *typestr = "bool char";
	enum { elem_count = 16,
		   elem_bits = 8};
};

template <>
struct typetable_bool<short> {
	using vectype = __vector bool short;
	static constexpr const char *typestr = "bool short";
	enum { elem_count = 8,
		   elem_bits = 16};
};

template <>
struct typetable_bool<int> {
	using vectype = __vector bool int;
	static constexpr const char *typestr = "bool int";
	enum { elem_count = 4,
		   elem_bits = 32};
};

#if _ARCH_PWR8
template <>
struct typetable_bool<long> {
	using vectype = __vector long bool;
	static constexpr const char *typestr = "long bool";
	enum { elem_count = 2,
		   elem_bits = 64};
};
#endif

}}
