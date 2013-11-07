//////////////////////////////////////////////////////////////////////////////////////////////////
//#pragma once
#ifndef __INCLUDED_EXCEPTION_HH__
#define __INCLUDED_EXCEPTION_HH__
//////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
//include files
////////////////////////////////////////////////////////////////////
#include <iostream> //required for string




////////////////////////////////////////////////////////////////////
//preprocesor macros
////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//ASSERT MACRO if "#define NDEBUG" isn't defined
//#define NDEBUG
#ifndef NDEBUG
 #define ASSERT( condition, method, detail )\
 if( !(condition) ){\
 	throw Exception(__FILE__,__LINE__,method,detail);\
 }
#else
 #define ASSERT( condition, method, detail ) //nothing
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////
//ASSERT MACRO FOR STATIC FUNTION MEMBERS if "#define NDEBUG" isn't defined
#ifndef NDEBUG
 #define ASSERT_STATIC( condition, method, detail )\
 if( !(condition) ){\
 	print(method,__LINE__,__FILE__,detail,true);\
 	exit(-1);\
 }
#else
 #define ASSERT_STATIC( condition, method, detail ) //nothing
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////
//COMPILE TIME ASSERT MACRO
#define CTASSERT( condition )\
 compile_time_assert< condition >()
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
namespace prima{

//////////////////////////////////////////////////////////////////////////////////////////////////
//compile-time-assert class
//////////////////////////////////////////////////////////////////////////////////////////////////
//compile time assert class
//condition: is a constant expression, this will cause a compile-time error unless C evaluates to a nonzero integral value.
//One word of warning: when writing a compile-time assertion ctassert<E>, make sure that the expression E does not contain the > sign, or your compiler is likely to consider it a closing angle bracket.  Rewrite your expression to use < logic instead.
template <bool condition>
struct compile_time_assert{
	enum { COMPILE_TIME_ASSERT = 1 - 2*static_cast<int>(!condition) }; //N = 1 if condition is true or -1 if it is false
	static char a[COMPILE_TIME_ASSERT];
}; //compile-time-assert class

template <bool condition>
char compile_time_assert<condition>::a[COMPILE_TIME_ASSERT];
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
//Exception class
//////////////////////////////////////////////////////////////////////////////////////////////////
class Exception{
	////////////////////////////////////////////////////////////////////
	//Data Members
	////////////////////////////////////////////////////////////////////
private:
	std::string file;
	int line;
	std::string method;
	std::string detail;
public:
	////////////////////////////////////////////////////////////////////
	//Constructors and destructor
	////////////////////////////////////////////////////////////////////
	Exception(const std::string& file, const int line, const std::string& method, const std::string& detail=std::string("UNKNOW EXCEPTION")) throw();
	Exception(const Exception& right) throw();
	virtual ~Exception() throw(){};

	////////////////////////////////////////////////////////////////////
	//Administratives
	////////////////////////////////////////////////////////////////////
	void info() const throw();
	const std::string& what() const throw();
	void print() const throw();
	Exception& stack(const std::string& file, const int line, const std::string& method) throw();
}; //Exception class
//////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
//External Funtions
////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void print(const std::string& method, const int line, const std::string& file, const std::string& detail, bool isStatic=false);
//////////////////////////////////////////////////////////////////////////////////////////////////



}//namespace prima
//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__INCLUDED_EXCEPTION_HH__