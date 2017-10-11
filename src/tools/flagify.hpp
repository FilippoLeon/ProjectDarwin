//
// https://stackoverflow.com/questions/9874960/how-can-i-use-an-enum-class-in-a-boolean-context
//
#pragma once

/*
Use this line before header, if you don't want flags(T x) function to be implemented for your enum.
#define USE_ENUM_FLAGS_FUNCTION 0
*/

#ifndef USE_ENUM_FLAGS_FUNCTION
  #define USE_ENUM_FLAGS_FUNCTION 1
#endif

#define ENUM_FLAGS_EX_NO_FLAGS_FUNC(T, INT_T) \
enum class T;	\
inline T	operator	&	(T x, T y)		{	return static_cast<T>	(static_cast<INT_T>(x) & static_cast<INT_T>(y));	}; \
inline T	operator	|	(T x, T y)		{	return static_cast<T>	(static_cast<INT_T>(x) | static_cast<INT_T>(y));	}; \
inline T	operator	^	(T x, T y)		{	return static_cast<T>	(static_cast<INT_T>(x) ^ static_cast<INT_T>(y));	}; \
inline T	operator	~	(T x)			{	return static_cast<T>	(~static_cast<INT_T>(x));							}; \
inline T&	operator	&=	(T& x, T y)		{	x = x & y;	return x;	}; \
inline T&	operator	|=	(T& x, T y)		{	x = x | y;	return x;	}; \
inline T&	operator	^=	(T& x, T y)		{	x = x ^ y;	return x;	}; \
inline bool	operator	*	(T&& x)		    {	return static_cast<INT_T>(x);	};

#if(USE_ENUM_FLAGS_FUNCTION)

#define ENUM_FLAGS_EX(T,INT_T) ENUM_FLAGS_EX_NO_FLAGS_FUNC(T,INT_T) \
	inline bool			flags(T x)			{	return static_cast<INT_T>(x) != 0;};

#else

#define ENUM_FLAGS_EX(T,INT_T) ENUM_FLAGS_EX_NO_FLAGS_FUNC(T,INT_T)

#endif

#define FLAGIFY(T) ENUM_FLAGS_EX(T,intptr_t)