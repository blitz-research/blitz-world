#pragma once

#include <cassert>
#include <cmath>
#include <cstring>

#include <algorithm>
#include <any>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using uchar = unsigned char;
#ifdef __EMSCRIPTEN__
using ulong = unsigned long;
using ushort = unsigned short;
using uint = unsigned int;
#endif

namespace wb {

#define WB_ALIGN4 __attribute__((aligned(4)))
#define WB_ALIGN8 __attribute__((aligned(8)))
#define WB_ALIGN16 __attribute__((aligned(16)))

constexpr float pi = 3.14159265359f;
constexpr float twopi = pi * 2;
constexpr float halfpi = pi * .5f;

using Any = std::any;
using CAny = const Any&;

using String = std::string;
using CString = const String&;

template <class T> using Vector = std::vector<T>;
template <class T> using CVector = const Vector<T>&;

template <class K, class V, class C = std::less<K>> using Map = std::map<K, V, C>;
template <class K, class V, class C = std::less<K>> using CMap = const Map<K, V, C>&;

template <class V> using StringMap = Map<String, V>;
template <class V> using CStringMap = const StringMap<V>&;

template <class E, class = std::enable_if<std::is_enum<E>::value>> E operator&(E x, E y) {
	return E(int(x) & int(y));
}
template <class E, class = std::enable_if<std::is_enum<E>::value>> E operator|(E x, E y) {
	return E(int(x) | int(y));
}
template <class E, class = std::enable_if<std::is_enum<E>::value>> E operator^(E x, E y) {
	return E(int(x) ^ int(y));
}
template <class E, class = std::enable_if<std::is_enum<E>::value>> E& operator&=(E& x, E y) {
	return (x = E(x & y));
}
template <class E, class = std::enable_if<std::is_enum<E>::value>> E& operator|=(E& x, E y) {
	return (x = E(x | y));
}
template <class E, class = std::enable_if<std::is_enum<E>::value>> E& operator^=(E& x, E y) {
	return (x = E(x ^ y));
}
template <class E, class = std::enable_if<std::is_enum<E>::value>> E operator~(E x) {
	return E(~int(x));
}

//! Safely erase first matching element from a vector
// template <class T> void erase(Vector<T>& vec, const T& value) {
//	vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
//}

//! Erase first matching element from a vector
template <class T, class U> void eraseFirst(Vector<T>& vec, const U& value) {
	auto it = std::find(vec.begin(), vec.end(), value);
	if (it != vec.end()) vec.erase(it);
}

template <class T, class U> bool addUnique(Vector<T>& vec, const U& value) {
	if (std::find(vec.begin(), vec.end(), value) != vec.end()) return false;
	vec.push_back(value);
	return true;
}

template <class T, class U> bool contains(CVector<T> vec, const U& value) {
	return std::find(vec.begin(), vec.end(), value) != vec.end();
}

//! Convert a value to a string, using the value type's operator<<(std::ostream&).
template <class T> inline String toString(const T& value) {
	std::stringstream buf;
	buf << value;
	return buf.str();
}

template <class T> T sgn(T x) {
	return (x < 0) ? -1 : (x > 0);
}

[[noreturn]] void fail(CString cond, const char* file, int line);

//! Release mode assert
#define verify(C)                                                                                                      \
	if (!(C)) fail(#C, __FILE__, __LINE__);

//! PANIC!
#define panic(C) fail(C, __FILE__, __LINE__);

// Seed rnd generator
void seedRnd(uint seed);

// Seed rnd generator with current time().
void seedRnd();

//! Generate a pseudo random number from [0, 1).
float rnd();

//! Generate a pseudo random number from [0, max).
float rnd(float max);

//! Generate a pseudo random number from [min, max).
float rnd(float min, float max);

//! Load a string from a file.
String loadString(CString path);

//! Split a string into an array of substrings.
Vector<String> splitString(CString string, CString separator);

//! Load bytes from a file.
Vector<uchar> loadData(CString path);

//! convert string to uppercase.
String toUpper(String str);

} // namespace wb

// Release mode asserts, remove for final release...
#undef assert
#define assert verify