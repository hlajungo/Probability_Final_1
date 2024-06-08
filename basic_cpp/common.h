#ifndef COMMON_H
#define COMMON_H
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <sstream>
#include <chrono>
#include <stdexcept>

//#include <thread>
//#include <ctime>
#define LOG(var) Log(#var, var, __LINE__, __func__ )

#define TYPE(type, var) Type(#var, var, __LINE__, __func__ , #type)

template<typename T>
std::string COMMON_is_const() {
	return std::is_const<std::remove_reference_t<T>>::value ? "const " : "";
}

//error 問題一堆，所有東西都是reference// Helper function to check reference
//template<typename T>
//std::string COMMON_is_reference() {
//	if (std::is_lvalue_reference<T>::value) {
//		return "&";
//	}
//	else if (std::is_rvalue_reference<T>::value) {
//		return "&&";
//	}
//	return "";
//}

//More information when outputting in Debug mode
//<iomanip> setw setfill dec 
//<typeinfo> typeid 
//<sstream> stringstream
//<thread> this_thread 
//<chrono> chrono 
//<ctime> 
#ifdef _DEBUG
template <typename T>
void Type(const char* varName, T  var, int line, const char* functionName, const char* type) {
	std::stringstream ss;
	ss << type << " <==> [" << typeid(var).name() << "] ";
	std::ios_base::fmtflags originalFlags = std::cout.flags();/*FORMAT FLAG*/\
		/*auto now = std::chrono::system_clock::now();*//*TIME*/\
		/*std::time_t timestamp = std::chrono::system_clock::to_time_t(now);*//*TIME*/\
		/* std::cout << "\nTime taken at Total : " << duration.count() / 1000.0 << " millisecond" << std::endl;*//*TIME*/
		std::cout.width(0);
	std::cout << std::setfill(' ') << std::left << "TYPE "\
		<< std::setw(50) << ss.str()/*TYPE*/\
		<< " At " << std::setw(15) << functionName /*FUNCTION*/\
		<< std::dec << ",line " << std::setw(5) << std::setfill('0') << std::right << line /*LINE*/\
		/*<< "File: " << __FILE__ */   /*FILE*/\
		/*<< ", Thread ID: " << std::this_thread::get_id() << ", "*//*THREAD*/\
		<< std::endl; \
		std::cout.flags(originalFlags);
}

template <typename T>
void Log(const char* varName, T&& var, int line, const char* functionName) {
	std::stringstream ss;

	ss << "[ " << COMMON_is_const<T>() << typeid(var).name() << " ] " << varName << " = [" << var << "]";

	std::ios_base::fmtflags originalFlags = std::cout.flags();/*FORMAT FLAG*/
	/*auto now = std::chrono::system_clock::now();*//*TIME*/
	/*std::time_t timestamp = std::chrono::system_clock::to_time_t(now);*//*TIME*/\
		/* std::cout << "\nTime taken at Total : " << duration.count() / 1000.0 << " millisecond" << std::endl;*//*TIME*/
		std::cout.width(0);
	std::cout << std::setfill(' ') << std::left << "LOG  "
		<< std::setw(50) << ss.str() /*TYPE*//*VARIABLE*//*VALUE*/
		<< " At " << std::setw(15) << functionName /*FUNCTION*/
		<< std::dec << ",line " << std::setw(5) << std::setfill('0') << std::right << line /*LINE*/\
		/*<< "File: " << __FILE__ */   /*FILE*/
		/*<< ", Thread ID: " << std::this_thread::get_id() << ", "*//*THREAD*/
		<< std::endl;
	std::cout.flags(originalFlags);
}


//未完成
#define RUTHIS(var, var2) WhoAreYou_2(#var, var, __LINE__, __func__, __FILE__, var2)
template <typename T, typename U>
__forceinline void WhoAreYou_2(const char* varName, T var, int line, const char* functionName, const char* fileName, U var2) {
	// 实现双参数版本的逻辑
	std::ios_base::fmtflags originalFlags = std::cout.flags();/*FORMAT FLAG*/
	std::cout.width(0);
	std::cout << std::setfill(' ') << std::left << "WHORU [" << typeid(T).name() << "] " << varName << "\nBASIC\n";


	/*fundmental, void, compound, function, reference不是object*/
	/*array, class, union, null_pointer, arithmetic, integral, floating_point, enum, pointer, member_pointer是object*/
	/*null_pointer, arithmetic, integral, floating_point, enum, pointer, member_pointer是scalar/
	/* an object type (that is any possibly cv-qualified type other than function, reference, or void types)*/
	if (std::is_object<T>::value && !std::is_scalar<T>::value) std::cout << " [ object ] \n";
	/*a scalar type*/
	if (std::is_scalar<T>::value) std::cout << "[ object -> scalar ] \n";

	/* a fundamental type (that is, arithmetic type, void, or nullptr_t)*/
	if (std::is_fundamental<T>::value && !std::is_void<T>::value && !std::is_arithmetic<T>::value) std::cout << "[ fundamental ] \n";

	/* void, const void, volatile void, or const volatile void*/
	if (std::is_void<T>::value) std::cout << "[ fundamental -> void ] \n";

	/* std::nullptr_t, const std::nullptr_t, volatile std::nullptr_t, or const volatile std::nullptr_t.*/
	if (std::is_null_pointer<T>::value) std::cout << "[ null pointer ] \n";
	/* an arithmetic type (that is, an integral type or a floating-point type) or a cv-qualified version thereof*/
	if (std::is_arithmetic<T>::value && !std::is_integral<T>::value && !std::is_floating_point<T>::value) std::cout << "[ fundamental -> arithmetic ] \n";
	/* the type bool, char, char8_t(since C++20), char16_t, char32_t, wchar_t, short, int, long, long long, or any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants*/
	if (std::is_integral<T>::value) std::cout << "[ fundamental -> arithmetic -> integral ] \n";
	/* the type float, double, long double, or any extended floating-point types (std::float16_t, std::float32_t, std::float64_t, std::float128_t, or std::bfloat16_t)(since C++23), including any cv-qualified variants*/
	if (std::is_floating_point<T>::value) std::cout << "[ fundamental -> arithmetic -> floating point ] \n";

	/* a compound type (that is, array, function, object pointer, function pointer, member object pointer, member function pointer, reference, class, union, or enumeration, including any cv-qualified variants)*/
	if (std::is_compound<T>::value && !std::is_function<T>::value && !std::is_reference<T>::value && !std::is_array<T>::value && !std::is_union<T>::value && !std::is_class<T>::value && !std::is_pointer<T>::value && !std::is_enum<T>::value && !std::is_member_pointer<T>::value) std::cout << "[ compound ] \n";

	/* a function type.
	Types like std::function, lambdas, classes with overloaded operator() and pointers to functions don't count as function types*/
	if (std::is_function<T>::value) std::cout << "[ compound -> function ] \n";
	/* a reference type (lvalue reference or rvalue reference)*/
	if (std::is_reference<T>::value && !std::is_lvalue_reference<T>::value && !std::is_rvalue_reference<T>::value) std::cout << "[ reference ] \n";
	/* an lvalue reference type*/
	if (std::is_lvalue_reference<T>::value) std::cout << "[ compound -> reference -> lvalue reference ] \n";
	/* an rvalue reference type*/
	if (std::is_rvalue_reference<T>::value) std::cout << "[ compound -> reference -> rvalue reference ] \n";

	/* array type*/
	if (std::is_array<T>::value) std::cout << "[ compound -> array ] \n";
	/* a union type*/
	if (std::is_union<T>::value) std::cout << "[ compound -> union ] \n";
	/* a non-union class type*/
	if (std::is_class<T>::value) std::cout << "[ compound -> class ] \n";

	/* a pointer to object or function (including pointer to void, but excluding pointer to member) or a cv-qualified version thereof*/
	if (std::is_pointer<T>::value) std::cout << "[ compound -> pointer ] \n";
	/* an enumeration type*/
	if (std::is_enum<T>::value) std::cout << "[ compound -> enum ] \n";
	/* pointer to non-static member object or a pointer to non-static member function*/
	if (std::is_member_pointer<T>::value && !std::is_member_object_pointer<T>::value && !std::is_member_function_pointer<T>::value) std::cout << "[ compound -> member pointer ] \n";
	/* a non-static member object pointer*/
	if (std::is_member_object_pointer<T>::value) std::cout << "[ compound -> member pointer -> member object pointer ] \n";
	/* a non-static member function pointer*/
	if (std::is_member_function_pointer<T>::value) std::cout << "[ compound -> member pointer -> member function pointer ] \n";


	std::cout << "OTHER\n";

	/*(This type trait has been deprecated[1] and removed[2] as offering negligible value to generic code.)*/
	//if (std::is_literal_type<T>::value) std::cout <<"[ literal type ] \n"; // Deprecated in C++20
	/*(deprecated in C++20)*/
	//if (std::is_pod<T>::value) std::cout <<"[ POD ] \n"; // Deprecated in C++20

	/* a scoped enumeration type*/
	//if constexpr (std::is_scoped_enum<T>::value) std::cout <<"[ scoped enum ] \n"; // C++23 feature, use with caution
	/* an implicit-lifetime type(C++23)*/
	//if constexpr (std::is_implicit_lifetime<T>::value) std::cout <<"[ implicit lifetime ] \n"; // C++23 feature, use with caution

	/* a const-qualified type (that is, const, or const volatile)*/
	if (std::is_const<T>::value) std::cout << "[ const ] \n";
	/* a volatile-qualified type (that is, volatile, or const volatile)*/
	if (std::is_volatile<T>::value) std::cout << "[ volatile ] \n";
	/* an empty type (that is, a non-union class type with no non-static data members other than bit-fields of size 0, no virtual functions, no virtual base classes, and no non-empty base classes)*/
	if (std::is_empty<T>::value) std::cout << "[ empty class ] ";
	/* a polymorphic class (that is, a non-union class that declares or inherits at least one virtual function)*/
	if (std::is_polymorphic<T>::value) std::cout << "[ polymorphic class ] \n";
	/* a final class*/
	if (std::is_final<T>::value) std::cout << "[ final class ] \n";
	/* an abstract class (that is, a non-union class that declares or inherits at least one pure virtual function)*/
	if (std::is_abstract<T>::value) std::cout << "[ abstract class ] \n";
	/* an aggregate type*/
	if (std::is_aggregate<T>::value) std::cout << "[ aggregate ] \n";
	/* a trivial type*/
	if (std::is_trivial<T>::value) std::cout << "[ trivial ] \n";
	/* a trivially copyable type*/
	if (std::is_trivially_copyable<T>::value) std::cout << "[ trivially copyable ] \n";
	/* a standard-layout type*/
	if (std::is_standard_layout<T>::value) std::cout << "[ standard layout ] \n";
	/* an arithmetic type, provides the member constant value equal to true if T(-1) < T(0): this results in true for the floating-point types and the signed integer types, and in false for the unsigned integer types and the type bool.*/
	if (std::is_signed<T>::value) std::cout << "[ signed ] \n";
	/* an arithmetic type, provides the member constant value equal to true if T(0) < T(-1): this results in true for the unsigned integer types and the type bool and in false for the signed integer types and the floating-point types.*/
	if (std::is_unsigned<T>::value) std::cout << "[ unsigned ] \n";
	/* an array type of known bound*/
	if (std::is_bounded_array<T>::value) std::cout << "[ bounded array ] \n"; // C++20 feature
	/* an arrays of unknown bound*/
	if (std::is_unbounded_array<T>::value) std::cout << "[ unbounded array ] \n"; // C++20 feature
	/* TriviallyCopyable and if any two objects of type T with the same value have the same object representation*/
	if (std::has_unique_object_representations<T>::value) std::cout << "[ unique object representations ] \n"; // C++17 feature
	/*文章節錄：
	For the purpose of this trait, two arrays have the same value if their elements have the same values, two non-union classes have the same value if their direct subobjects have the same value, and two unions have the same value if they have the same active member and the value of that member is the same.
	It is implementation-defined which scalar types satisfy this trait, but unsigned(until C++20) integer types that do not use padding bits are guaranteed to have unique object representations.
	The behavior is undefined if T is an incomplete type other than (possibly cv-qualified) void or array of unknown bound.
	If the program adds specializations for std::has_unique_object_representations or std::has_unique_object_representations_v, the behavior is undefined.*/


	/*解讀：template< class T, class... Args >struct is_constructible;這模板是多參數的，default是單參數*/
	// Construction
	/* an object or reference type and the variable definition T obj(std::declval<Args>()...); is well-formed*/
	if (std::is_constructible<T>::value) std::cout << "[ constructible ] \n";
	/* Same as is_constructible, but the variable definition does not call any operation that is not trivial*/
	if (std::is_trivially_constructible<T>::value) std::cout << "[ trivially constructible ] \n";
	/* Same as is_constructible, but the variable definition is noexcept*/
	if (std::is_nothrow_constructible<T>::value) std::cout << "[ nothrow constructible ] \n";
	/*文章節錄：關於以上的undefined behavior
	If T is not a complete type, (possibly cv-qualified) void, or an array of unknown bound, the behavior is undefined.
	If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.*/
	///* equal to std::is_constructible<T>::value*/
	//if (std::is_default_constructible<T>::value) std::cout <<"[ default constructible ] \n";
	///* equal to std::is_trivially_constructible<T>::value*/
	//if (std::is_trivially_default_constructible<T>::value) std::cout <<"[ trivially default constructible ] \n";
	///* equal to std::is_nothrow_constructible<T>::value*/
	//if (std::is_nothrow_default_constructible<T>::value) std::cout <<"[ nothrow default constructible ] \n";

	/*解讀：以下是多模板參數的is_constructible*/
	/*T is a referenceable type*/
	/* std::is_constructible<T, const T&>::value*/
	if (std::is_copy_constructible<T>::value) std::cout << "[ copy constructible ] \n";
	/* std::is_trivially_constructible<T, const T&>::value*/
	if (std::is_trivially_copy_constructible<T>::value) std::cout << "[ trivially copy constructible ] \n";
	/* std::is_nothrow_constructible<T, const T&>::value*/
	if (std::is_nothrow_copy_constructible<T>::value) std::cout << "[ nothrow copy constructible ] \n";

	/*解讀：以下是多模板參數的is_constructible*/
	/*T is a referenceable type*/
	/* std::is_constructible<T, T&&>::value*/
	if (std::is_move_constructible<T>::value) std::cout << "[ move constructible ] \n";
	/* std::is_trivially_constructible<T, T&&>::value*/
	if (std::is_trivially_move_constructible<T>::value) std::cout << "[ trivially move constructible ] \n";
	/* std::is_nothrow_constructible<T, T&&>::value*/
	if (std::is_nothrow_move_constructible<T>::value) std::cout << "[ nothrow move constructible ] \n";

	// Assignability
	/*  If the expression std::declval<T>() = std::declval<U>() is well-formed in unevaluated context*/
	if (std::is_assignable<T, T>::value) std::cout << "[ assignable ] \n";
	/* Same as is_assignable, but the evaluation of the assignment expression will not call any operation that is not trivial. For the purposes of this check, a call to std::declval is considered trivial and not considered an odr-use of std::declval.*/
	if (std::is_trivially_assignable<T, T>::value) std::cout << "[ trivially assignable ] \n";
	/* Same as is_assignable, but the evaluation of the assignment expression will not call any operation that is not noexcept.*/
	if (std::is_nothrow_assignable<T, T>::value) std::cout << "[ nothrow assignable ] \n";
	/*文章節錄：未定義的行為
	If T is not a complete type, (possibly cv-qualified) void, or an array of unknown bound, the behavior is undefined.
	If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.*/


	/* 解讀：以下是多模板參數的is_assignable*/
	/* T is a referenceable type*/
	/* std::is_assignable<T, const T&>::value*/
	if (std::is_copy_assignable<T>::value) std::cout << "[ copy assignable ] \n";
	/*	std::is_trivially_assignable<T, const T&>::value*/
	if (std::is_trivially_copy_assignable<T>::value) std::cout << "[ trivially copy assignable ] \n";
	/* std::is_nothrow_assignable<T, const T&>::value*/
	if (std::is_nothrow_copy_assignable<T>::value) std::cout << "[ nothrow copy assignable ] \n";

	/* T is a referenceable type*/
	/* std::is_assignable<T, T&&>::value*/
	if (std::is_move_assignable<T>::value) std::cout << "[ move assignable ] \n";
	/* std::is_trivially_assignable<T, T&&>::value*/
	if (std::is_trivially_move_assignable<T>::value) std::cout << "[ trivially move assignable ] \n";
	/* std::is_nothrow_assignable<T, T&&>::value*/
	if (std::is_nothrow_move_assignable<T>::value) std::cout << "[ nothrow move assignable ] \n";

	/*解讀3.：如果是object，通過std::remove_all_extents<T>::type去除數組，如int[10][20](T)變為int(U)，接著使用std::declval<U&>().~U()，測試析構函數是否well-formed，也是主要的工作目標。*/
	// Destruction
	/*1.a reference type ,value equals true,
	2.(possibly cv-qualified) void, a function type, or an array of unknown bound, value equals false
	3.If T is an object type, then, for the type U that is std::remove_all_extents<T>::type, if the expression std::declval<U&>().~U() is well-formed in unevaluated context, value equals true*/
	if (std::is_destructible<T>::value) std::cout << "[ destructible ] \n";
	/*Same as is_destructible and additionally std::remove_all_extents<T>::type is either a non-class type or a class type with a trivial destructor.*/
	if (std::is_trivially_destructible<T>::value) std::cout << "[ trivially destructible ] \n";
	/*Same as is_destructible, but the destructor is noexcept.*/
	if (std::is_nothrow_destructible<T>::value) std::cout << "[ nothrow destructible ] \n";
	/*文章節錄：未定義的行為
	If T is not a complete type, (possibly cv-qualified) void, or an array of unknown bound, the behavior is undefined.
	If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.*/

	/*If T is a type with a virtual destructor, the base characteristic is std::true_type. For any other type, the base characteristic is std::false_type.*/
	if (std::has_virtual_destructor<T>::value) std::cout << "[ virtual destructor ] \n";

	// C++17 Swappable traits
	/* If the expressions swap(std::declval<T>(), std::declval<U>()) and swap(std::declval<U>(), std::declval<T>()) are both well-formed in unevaluated context after using std::swap; (see Swappable), provides the member constant value equal true. Otherwise, value is false.*/
	if (std::is_swappable_with<T, T>::value) std::cout << "[ swappable with ] \n"; // C++17 feature
	/*	std::is_swappable_with<T&, T&>::value*/
	if (std::is_swappable<T>::value) std::cout << "[ swappable ] \n"; // C++17 feature
	/* Same as is_swappable_with, but evaluations of both expressions from (1) are known not to throw exceptions.*/
	if (std::is_nothrow_swappable_with<T, T>::value) std::cout << "[ nothrow swappable with ] \n"; // C++17 feature
	/* std::is_nothrow_swappable_with<T&, T&>::value*/
	if (std::is_nothrow_swappable<T>::value) std::cout << "[ nothrow swappable ] \n"; // C++17 feature

	// Type relationships
	if (std::is_same<T, U>::value) std::cout << "[ same as U ] \n";
	if (std::is_base_of<U, T>::value) std::cout << "[ base of U ] \n";
	if (std::is_convertible<T, U>::value) std::cout << "[ convertible to U ] \n";
	if (std::is_nothrow_convertible<T, U>::value) std::cout << "[ nothrow convertible to U ] \n"; // C++20 feature

	// C++20 Compatibility and Interconvertibility
	if (std::is_layout_compatible<T, U>::value) std::cout << "[ layout compatible with U ] \n"; // C++20 feature
	if (std::is_pointer_interconvertible_base_of<U, T>::value) std::cout << "[ pointer interconvertible base of U ] \n"; // C++20 feature
	//undealed error if (std::is_pointer_interconvertible_with_class<T, U>::value) std::cout <<"[ pointer interconvertible with class U ] "; // C++20 feature
	//undealed error if (std::is_corresponding_member<T, U>::value) std::cout <<"[ corresponding member with U ] "; // C++20 feature

	/*解讀：std::rank<T>::value是數組的維度，一般變量是0。*/
	/*解讀：std::extent<T,0>::value是數組指定維度的變量數，如std::extent<int[3],0>::value==3。*/
	// Type properties
	/*Provides the member constant value equal to the alignment requirement of the type T, as if obtained by an alignof expression. If T is an array type, returns the alignment requirements of the element type. If T is a reference type, returns the alignment requirements of the type referred to.*/
	std::cout << "[ alignment of: " << std::alignment_of<T>::value << " ] \n";
	/*If T is an array type, provides the member constant value equal to the number of dimensions of the array. For any other type, value is ​0​.*/
	std::cout << "[ rank: " << std::rank<T>::value << " ] \n";
	/*If T is an array type, provides the member constant value equal to the number of elements along the Nth dimension of the array, if N is in [​0​, std::rank<T>::value). For any other type, or if T is an array of unknown bound along its first dimension and N is ​0​, value is ​0​.*/
	if constexpr (std::rank<T>::value > 0/*T是個數組*/) std::cout << "[ extent: " << std::extent<T, 1>::value << " ] \n";

	// Callable properties
	/*template< class Fn, class... ArgTypes >
	   struct is_invocable;*/
	   /*Determines whether INVOKE(std::declval<Fn>(), std::declval<ArgTypes>()...) is well formed when treated as an unevaluated operand.*/
	if (std::is_invocable<T>::value) std::cout << "[ invocable ] \n";
	/*template< class R, class Fn, class... ArgTypes >
	   struct is_invocable_r;*/
	   /*Determines whether INVOKE<R>(std::declval<Fn>(), std::declval<ArgTypes>()...) is well formed when treated as an unevaluated operand.*/
	if (std::is_invocable_r<U, T>::value) std::cout << "[ invocable_r ] \n";
	/*template< class Fn, class... ArgTypes >
	   struct is_nothrow_invocable;*/
	   /*Determines whether INVOKE(std::declval<Fn>(), std::declval<ArgTypes>()...) is well formed when treated as an unevaluated operand, and is known not to throw any exceptions.*/
	if (std::is_nothrow_invocable<T>::value) std::cout << "[ nothrow invocable ] \n";
	/*template< class R, class Fn, class... ArgTypes >
	   struct is_nothrow_invocable_r;*/
	   /*Determines whether INVOKE<R>(std::declval<Fn>(), std::declval<ArgTypes>()...) is well formed when treated as an unevaluated operand, and is known not to throw any exceptions.*/
	if (std::is_nothrow_invocable_r<U, T>::value) std::cout << "[ nothrow invocable_r ] \n";

	// C++23 Reference properties
	// if (std::reference_constructs_from_temporary<T>::value) std::cout <<"[ reference constructs from temporary ] "; // C++23 feature
	// if (std::reference_converts_from_temporary<T>::value) std::cout <<"[ reference converts from temporary ] "; // C++23 feature

	/*Provides member typedef type, which is defined as T if B is true at compile time, or as F if B is false.*/
	std::cout << "[ type after conditional: " << typeid(typename std::conditional<true, T, T>::type).name() << " ] \n";

	// Type modifications
   /* Removes the topmost const, or the topmost volatile, or both, if present. */
	std::cout << "[ type after remove_cv: " << typeid(typename std::remove_cv<T>::type).name() << " ] \n";
	/* Removes the topmost const.*/
	std::cout << "[ type after remove_const: " << typeid(typename std::remove_const<T>::type).name() << " ] \n";
	/* Removes the topmost volatile.*/
	std::cout << "[ type after remove_volatile: " << typeid(typename std::remove_volatile<T>::type).name() << " ] \n";
	/* adds both const and volatile*/
	std::cout << "[ type after add_cv: " << typeid(typename std::add_cv<T>::type).name() << " ] \n";
	/* adds const*/
	std::cout << "[ type after add_const: " << typeid(typename std::add_const<T>::type).name() << " ] \n";
	/* adds volatile */
	std::cout << "[ type after add_volatile: " << typeid(typename std::add_volatile<T>::type).name() << " ] \n";
	/* an integral (except bool) or enumeration type, provides the member typedef type which is the signed integer type corresponding to T*/
	/* If T is signed or unsigned char, short, int, long, long long, the signed type from this list corresponding to T is provided.*/
	/* an enumeration type or char, wchar_t, char8_t(since C++20), char16_t, char32_t, the signed integer type with the smallest rank having the same sizeof as T is provided.*/
	std::cout << "[ type after make_signed: " << typeid(typename std::make_signed<T>::type).name() << " ] \n";
	/* an integral (except bool) or enumeration type, provides the member typedef type which is the unsigned integer type corresponding to T, with the same cv-qualifiers.*/
	/* signed or unsigned char, short, int, long, long long; the unsigned type from this list corresponding to T is provided.*/
	/* an enumeration type or char, wchar_t, char8_t(since C++20), char16_t, char32_t; the unsigned integer type with the smallest rank having the same sizeof as T is provided.*/
	std::cout << "[ type after make_unsigned: " << typeid(typename std::make_unsigned<T>::type).name() << " ] \n";
	/* a reference type, provides the member typedef type which is the type referred to by T.
	Otherwise type is T.*/
	std::cout << "[ type after remove_reference: " << typeid(typename std::remove_reference<T>::type).name() << " ] \n";
	/* T is a referenceable type => T& */
	/* T is not a referenceable type => T*/
	std::cout << "[ type after add_lvalue_reference: " << typeid(typename std::add_lvalue_reference<T>::type).name() << " ] \n";
	/* T is a referenceable type => T&& */
	/* T is not a referenceable type => T*/
	std::cout << "[ type after add_rvalue_reference: " << typeid(typename std::add_rvalue_reference<T>::type).name() << " ] \n";
	/*Provides the member typedef type which is the type pointed to by T, or, if T is not a pointer, then type is the same as T.*/
	std::cout << "[ type after remove_pointer: " << typeid(typename std::remove_pointer<T>::type).name() << " ] \n";
	/* add * to T*/
	/* If T is a referenceable type or (possibly cv-qualified) void, the member typedef type provided is typename std::remove_reference::type<T>*.
	Otherwise, the member typedef type provided is T.*/
	std::cout << "[ type after add_pointer: " << typeid(typename std::add_pointer<T>::type).name() << " ] \n";
	/*If T is an array of some type X, provides the member typedef type equal to X, otherwise type is T. Note that if T is a multidimensional array, only the first dimension is removed.*/
	std::cout << "[ type after remove_extent: " << typeid(typename std::remove_extent<T>::type).name() << " ] \n";
	/*If T is a multidimensional array of some type X, provides the member typedef type equal to X, otherwise type is T.*/
	std::cout << "[ type after remove_all_extents: " << typeid(typename std::remove_all_extents<T>::type).name() << " ] ";

	// Type transformations
	/* If T is "array of U" or reference to it, the member typedef type is U*.
	Otherwise, if T is a function type F or reference to one, the member typedef type is std::add_pointer<F>::type.
	Otherwise, the member typedef type is std::remove_cv<std::remove_reference<T>::type>::type.*/
	std::cout << "type after decay : " << typeid(typename std::decay<T>::type).name() << " ] ";
	/* 解讀:B是Bool，T是templete，兩者結合可以開發出一些功能。*/
	/* If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.*/
	std::cout << "[ type after enable_if: " << typeid(typename std::enable_if<true, T>::type).name() << " ] \n";
	/* Utility metafunction that maps a sequence of any types to the type void.*/
	std::cout << "[ type after void_t: " << typeid(typename std::void_t<T>).name() << " ] \n";
	/* 推導兩個或更多型別之間的共同型別（common type）。所謂的共同型別，是指能夠安全容納所有提供的型別的值的型別。*/
	std::cout << "[ type after common_type: " << typeid(typename std::common_type<T, T>::type).name() << " ] \n";
	/* 推導兩個或多個型別的共同參考型別（common reference type）*/
	std::cout << "[ type after common_reference: " << typeid(typename std::common_reference<T, T>::type).name() << " ] \n";
	/* 推導enum或enum class的uderlying_type*/
	/*Otherwise, the behavior is undefined.(until C++20)
	Otherwise, if T is not an enumeration type, there is no member type.
	Otherwise (T is an incomplete enumeration type), the program is ill-formed.*/
	//std::cout <<"[ type after underlying_type: " << std::underlying_type<T>::type << " ] \n";
	/*推導函數的返回值，普通函數，類或結構的非靜態成員函數，重載了operator()（Functors函數對象），Lambda表式，綁定表式 Bind expressions，閉包 Closures*/
	/* a callable type, reference to function, or reference to callable type. */
	/*F and all types in ArgTypes can be any complete type, array of unknown bound, or (possibly cv-qualified) void.*/
	std::cout << "[ type after invoke_result: " << typeid(typename std::invoke_result<void(*)(T), T>::type).name() << " ] \n";
	/*推導出T的類型，例如(4.2,1)正常會報錯，但用這能避免。*/
	std::cout << "[ type after type_identity: " << typeid(typename std::type_identity<T>::type).name() << " ] \n";

	std::cout
		<< "At " << std::setw(15) << functionName /*FUNCTION*/
		<< std::dec << ",line " << std::setw(5) << std::setfill('0') << std::right << line /*LINE*/\
		<< std::setfill(' ') << std::setw(10) << ",File: " << fileName    /*FILE*/
		/*<< ", Thread ID: " << std::this_thread::get_id() << ", "*//*THREAD*/
		<< '\n' << std::endl;
	std::cout.flags(originalFlags);	std::ios_base::fmtflags originalFlags = std::cout.flags();/*FORMAT FLAG*/
	std::cout.width(0);
	std::cout << std::setfill(' ') << std::left << "WHORU [" << typeid(T).name() << "]" << varName << "\nBASIC\n";


	/*fundmental, void, compound, function, reference不是object*/
	/*array, class, union, null_pointer, arithmetic, integral, floating_point, enum, pointer, member_pointer是object*/
	/*null_pointer, arithmetic, integral, floating_point, enum, pointer, member_pointer是scalar/
	/* an object type (that is any possibly cv-qualified type other than function, reference, or void types)*/
	if (std::is_object<T>::value && !std::is_scalar<T>::value) std::cout << " [ object ] \n";
	/*a scalar type*/
	if (std::is_scalar<T>::value) std::cout << "[ object -> scalar ] \n";

	/* a fundamental type (that is, arithmetic type, void, or nullptr_t)*/
	if (std::is_fundamental<T>::value && !std::is_void<T>::value && !std::is_arithmetic<T>::value) std::cout << "[ fundamental ] \n";

	/* void, const void, volatile void, or const volatile void*/
	if (std::is_void<T>::value) std::cout << "[ fundamental -> void ] \n";

	/* std::nullptr_t, const std::nullptr_t, volatile std::nullptr_t, or const volatile std::nullptr_t.*/
	if (std::is_null_pointer<T>::value) std::cout << "[ null pointer ] \n";
	/* an arithmetic type (that is, an integral type or a floating-point type) or a cv-qualified version thereof*/
	if (std::is_arithmetic<T>::value && !std::is_integral<T>::value && !std::is_floating_point<T>::value) std::cout << "[ fundamental -> arithmetic ] \n";
	/* the type bool, char, char8_t(since C++20), char16_t, char32_t, wchar_t, short, int, long, long long, or any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants*/
	if (std::is_integral<T>::value) std::cout << "[ fundamental -> arithmetic -> integral ] \n";
	/* the type float, double, long double, or any extended floating-point types (std::float16_t, std::float32_t, std::float64_t, std::float128_t, or std::bfloat16_t)(since C++23), including any cv-qualified variants*/
	if (std::is_floating_point<T>::value) std::cout << "[ fundamental -> arithmetic -> floating point ] \n";

	/* a compound type (that is, array, function, object pointer, function pointer, member object pointer, member function pointer, reference, class, union, or enumeration, including any cv-qualified variants)*/
	if (std::is_compound<T>::value && !std::is_function<T>::value && !std::is_reference<T>::value && !std::is_array<T>::value && !std::is_union<T>::value && !std::is_class<T>::value && !std::is_pointer<T>::value && !std::is_enum<T>::value && !std::is_member_pointer<T>::value) std::cout << "[ compound ] \n";

	/* a function type.
	Types like std::function, lambdas, classes with overloaded operator() and pointers to functions don't count as function types*/
	if (std::is_function<T>::value) std::cout << "[ compound -> function ] \n";
	/* a reference type (lvalue reference or rvalue reference)*/
	if (std::is_reference<T>::value && !std::is_lvalue_reference<T>::value && !std::is_rvalue_reference<T>::value) std::cout << "[ reference ] \n";
	/* an lvalue reference type*/
	if (std::is_lvalue_reference<T>::value) std::cout << "[ compound -> reference -> lvalue reference ] \n";
	/* an rvalue reference type*/
	if (std::is_rvalue_reference<T>::value) std::cout << "[ compound -> reference -> rvalue reference ] \n";

	/* array type*/
	if (std::is_array<T>::value) std::cout << "[ compound -> array ] \n";
	/* a union type*/
	if (std::is_union<T>::value) std::cout << "[ compound -> union ] \n";
	/* a non-union class type*/
	if (std::is_class<T>::value) std::cout << "[ compound -> class ] \n";

	/* a pointer to object or function (including pointer to void, but excluding pointer to member) or a cv-qualified version thereof*/
	if (std::is_pointer<T>::value) std::cout << "[ compound -> pointer ] \n";
	/* an enumeration type*/
	if (std::is_enum<T>::value) std::cout << "[ compound -> enum ] \n";
	/* pointer to non-static member object or a pointer to non-static member function*/
	if (std::is_member_pointer<T>::value && !std::is_member_object_pointer<T>::value && !std::is_member_function_pointer<T>::value) std::cout << "[ compound -> member pointer ] \n";
	/* a non-static member object pointer*/
	if (std::is_member_object_pointer<T>::value) std::cout << "[ compound -> member pointer -> member object pointer ] \n";
	/* a non-static member function pointer*/
	if (std::is_member_function_pointer<T>::value) std::cout << "[ compound -> member pointer -> member function pointer ] \n";


	std::cout << "OTHER\n";

	/*(This type trait has been deprecated[1] and removed[2] as offering negligible value to generic code.)*/
	//if (std::is_literal_type<T>::value) std::cout <<"[ literal type ] \n"; // Deprecated in C++20
	/*(deprecated in C++20)*/
	//if (std::is_pod<T>::value) std::cout <<"[ POD ] \n"; // Deprecated in C++20

	/* a scoped enumeration type*/
	//if constexpr (std::is_scoped_enum<T>::value) std::cout <<"[ scoped enum ] \n"; // C++23 feature, use with caution
	/* an implicit-lifetime type(C++23)*/
	//if constexpr (std::is_implicit_lifetime<T>::value) std::cout <<"[ implicit lifetime ] \n"; // C++23 feature, use with caution

	/* a const-qualified type (that is, const, or const volatile)*/
	if (std::is_const<T>::value) std::cout << "[ const ] \n";
	/* a volatile-qualified type (that is, volatile, or const volatile)*/
	if (std::is_volatile<T>::value) std::cout << "[ volatile ] \n";
	/* an empty type (that is, a non-union class type with no non-static data members other than bit-fields of size 0, no virtual functions, no virtual base classes, and no non-empty base classes)*/
	if (std::is_empty<T>::value) std::cout << "[ empty class ] ";
	/* a polymorphic class (that is, a non-union class that declares or inherits at least one virtual function)*/
	if (std::is_polymorphic<T>::value) std::cout << "[ polymorphic class ] \n";
	/* a final class*/
	if (std::is_final<T>::value) std::cout << "[ final class ] \n";
	/* an abstract class (that is, a non-union class that declares or inherits at least one pure virtual function)*/
	if (std::is_abstract<T>::value) std::cout << "[ abstract class ] \n";
	/* an aggregate type*/
	if (std::is_aggregate<T>::value) std::cout << "[ aggregate ] \n";
	/* a trivial type*/
	if (std::is_trivial<T>::value) std::cout << "[ trivial ] \n";
	/* a trivially copyable type*/
	if (std::is_trivially_copyable<T>::value) std::cout << "[ trivially copyable ] \n";
	/* a standard-layout type*/
	if (std::is_standard_layout<T>::value) std::cout << "[ standard layout ] \n";

	/* an arithmetic type, provides the member constant value equal to true if T(-1) < T(0): this results in true for the floating-point types and the signed integer types, and in false for the unsigned integer types and the type bool.*/
	if (std::is_signed<T>::value) std::cout << "[ signed ] \n";
	/* an arithmetic type, provides the member constant value equal to true if T(0) < T(-1): this results in true for the unsigned integer types and the type bool and in false for the signed integer types and the floating-point types.*/
	if (std::is_unsigned<T>::value) std::cout << "[ unsigned ] \n";
	/* an array type of known bound*/
	if (std::is_bounded_array<T>::value) std::cout << "[ bounded array ] \n"; // C++20 feature
	/* an arrays of unknown bound*/
	if (std::is_unbounded_array<T>::value) std::cout << "[ unbounded array ] \n"; // C++20 feature
	/* TriviallyCopyable and if any two objects of type T with the same value have the same object representation*/
	if (std::has_unique_object_representations<T>::value) std::cout << "[ unique object representations ] \n"; // C++17 feature
	/*文章節錄：
	For the purpose of this trait, two arrays have the same value if their elements have the same values, two non-union classes have the same value if their direct subobjects have the same value, and two unions have the same value if they have the same active member and the value of that member is the same.
	It is implementation-defined which scalar types satisfy this trait, but unsigned(until C++20) integer types that do not use padding bits are guaranteed to have unique object representations.
	The behavior is undefined if T is an incomplete type other than (possibly cv-qualified) void or array of unknown bound.
	If the program adds specializations for std::has_unique_object_representations or std::has_unique_object_representations_v, the behavior is undefined.*/


	/*解讀：template< class T, class... Args >struct is_constructible;這模板是多參數的，default是單參數*/
	// Construction
	/* an object or reference type and the variable definition T obj(std::declval<Args>()...); is well-formed*/
	if (std::is_constructible<T>::value) std::cout << "[ constructible ] \n";
	/* Same as is_constructible, but the variable definition does not call any operation that is not trivial*/
	if (std::is_trivially_constructible<T>::value) std::cout << "[ trivially constructible ] \n";
	/* Same as is_constructible, but the variable definition is noexcept*/
	if (std::is_nothrow_constructible<T>::value) std::cout << "[ nothrow constructible ] \n";
	/*文章節錄：關於以上的undefined behavior
	If T is not a complete type, (possibly cv-qualified) void, or an array of unknown bound, the behavior is undefined.
	If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.*/
	///* equal to std::is_constructible<T>::value*/
	//if (std::is_default_constructible<T>::value) std::cout <<"[ default constructible ] \n";
	///* equal to std::is_trivially_constructible<T>::value*/
	//if (std::is_trivially_default_constructible<T>::value) std::cout <<"[ trivially default constructible ] \n";
	///* equal to std::is_nothrow_constructible<T>::value*/
	//if (std::is_nothrow_default_constructible<T>::value) std::cout <<"[ nothrow default constructible ] \n";

	/*解讀：以下是多模板參數的is_constructible*/
	/*T is a referenceable type*/
	/* std::is_constructible<T, const T&>::value*/
	if (std::is_copy_constructible<T>::value) std::cout << "[ copy constructible ] \n";
	/* std::is_trivially_constructible<T, const T&>::value*/
	if (std::is_trivially_copy_constructible<T>::value) std::cout << "[ trivially copy constructible ] \n";
	/* std::is_nothrow_constructible<T, const T&>::value*/
	if (std::is_nothrow_copy_constructible<T>::value) std::cout << "[ nothrow copy constructible ] \n";

	/*解讀：以下是多模板參數的is_constructible*/
	/*T is a referenceable type*/
	/* std::is_constructible<T, T&&>::value*/
	if (std::is_move_constructible<T>::value) std::cout << "[ move constructible ] \n";
	/* std::is_trivially_constructible<T, T&&>::value*/
	if (std::is_trivially_move_constructible<T>::value) std::cout << "[ trivially move constructible ] \n";
	/* std::is_nothrow_constructible<T, T&&>::value*/
	if (std::is_nothrow_move_constructible<T>::value) std::cout << "[ nothrow move constructible ] \n";

	// Assignability
	/*  If the expression std::declval<T>() = std::declval<U>() is well-formed in unevaluated context*/
	if (std::is_assignable<T, T>::value) std::cout << "[ assignable ] \n";
	/* Same as is_assignable, but the evaluation of the assignment expression will not call any operation that is not trivial. For the purposes of this check, a call to std::declval is considered trivial and not considered an odr-use of std::declval.*/
	if (std::is_trivially_assignable<T, T>::value) std::cout << "[ trivially assignable ] \n";
	/* Same as is_assignable, but the evaluation of the assignment expression will not call any operation that is not noexcept.*/
	if (std::is_nothrow_assignable<T, T>::value) std::cout << "[ nothrow assignable ] \n";
	/*文章節錄：未定義的行為
	If T is not a complete type, (possibly cv-qualified) void, or an array of unknown bound, the behavior is undefined.
	If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.*/


	/* 解讀：以下是多模板參數的is_assignable*/
	/* T is a referenceable type*/
	/* std::is_assignable<T, const T&>::value*/
	if (std::is_copy_assignable<T>::value) std::cout << "[ copy assignable ] \n";
	/*	std::is_trivially_assignable<T, const T&>::value*/
	if (std::is_trivially_copy_assignable<T>::value) std::cout << "[ trivially copy assignable ] \n";
	/* std::is_nothrow_assignable<T, const T&>::value*/
	if (std::is_nothrow_copy_assignable<T>::value) std::cout << "[ nothrow copy assignable ] \n";

	/* T is a referenceable type*/
	/* std::is_assignable<T, T&&>::value*/
	if (std::is_move_assignable<T>::value) std::cout << "[ move assignable ] \n";
	/* std::is_trivially_assignable<T, T&&>::value*/
	if (std::is_trivially_move_assignable<T>::value) std::cout << "[ trivially move assignable ] \n";
	/* std::is_nothrow_assignable<T, T&&>::value*/
	if (std::is_nothrow_move_assignable<T>::value) std::cout << "[ nothrow move assignable ] \n";

	/*解讀3.：如果是object，通過std::remove_all_extents<T>::type去除數組，如int[10][20](T)變為int(U)，接著使用std::declval<U&>().~U()，測試析構函數是否well-formed，也是主要的工作目標。*/
	// Destruction
	/*1.a reference type ,value equals true,
	2.(possibly cv-qualified) void, a function type, or an array of unknown bound, value equals false
	3.If T is an object type, then, for the type U that is std::remove_all_extents<T>::type, if the expression std::declval<U&>().~U() is well-formed in unevaluated context, value equals true*/
	if (std::is_destructible<T>::value) std::cout << "[ destructible ] \n";
	/*Same as is_destructible and additionally std::remove_all_extents<T>::type is either a non-class type or a class type with a trivial destructor.*/
	if (std::is_trivially_destructible<T>::value) std::cout << "[ trivially destructible ] \n";
	/*Same as is_destructible, but the destructor is noexcept.*/
	if (std::is_nothrow_destructible<T>::value) std::cout << "[ nothrow destructible ] \n";
	/*文章節錄：未定義的行為
	If T is not a complete type, (possibly cv-qualified) void, or an array of unknown bound, the behavior is undefined.
	If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.*/

	/*If T is a type with a virtual destructor, the base characteristic is std::true_type. For any other type, the base characteristic is std::false_type.*/
	if (std::has_virtual_destructor<T>::value) std::cout << "[ virtual destructor ] \n";

	// C++17 Swappable traits
	/* If the expressions swap(std::declval<T>(), std::declval<U>()) and swap(std::declval<U>(), std::declval<T>()) are both well-formed in unevaluated context after using std::swap; (see Swappable), provides the member constant value equal true. Otherwise, value is false.*/
	if (std::is_swappable_with<T, T>::value) std::cout << "[ swappable with ] \n"; // C++17 feature
	/*	std::is_swappable_with<T&, T&>::value*/
	if (std::is_swappable<T>::value) std::cout << "[ swappable ] \n"; // C++17 feature
	/* Same as is_swappable_with, but evaluations of both expressions from (1) are known not to throw exceptions.*/
	if (std::is_nothrow_swappable_with<T, T>::value) std::cout << "[ nothrow swappable with ] \n"; // C++17 feature
	/* std::is_nothrow_swappable_with<T&, T&>::value*/
	if (std::is_nothrow_swappable<T>::value) std::cout << "[ nothrow swappable ] \n"; // C++17 feature

	// Type relationships
	if (std::is_same<T, U>::value) std::cout << "[ same as U ] \n";
	if (std::is_base_of<U, T>::value) std::cout << "[ base of U ] \n";
	if (std::is_convertible<T, U>::value) std::cout << "[ convertible to U ] \n";
	if (std::is_nothrow_convertible<T, U>::value) std::cout << "[ nothrow convertible to U ] \n"; // C++20 feature

	// C++20 Compatibility and Interconvertibility
	if (std::is_layout_compatible<T, U>::value) std::cout << "[ layout compatible with U ] \n"; // C++20 feature
	if (std::is_pointer_interconvertible_base_of<U, T>::value) std::cout << "[ pointer interconvertible base of U ] \n"; // C++20 feature
	//undealed error if (std::is_pointer_interconvertible_with_class<T, U>::value) std::cout <<"[ pointer interconvertible with class U ] "; // C++20 feature
	//undealed error if (std::is_corresponding_member<T, U>::value) std::cout <<"[ corresponding member with U ] "; // C++20 feature

	/*解讀：std::rank<T>::value是數組的維度，一般變量是0。*/
	/*解讀：std::extent<T,0>::value是數組指定維度的變量數，如std::extent<int[3],0>::value==3。*/
	// Type properties
	/*Provides the member constant value equal to the alignment requirement of the type T, as if obtained by an alignof expression. If T is an array type, returns the alignment requirements of the element type. If T is a reference type, returns the alignment requirements of the type referred to.*/
	std::cout << "[ alignment of: " << std::alignment_of<T>::value << " ] \n";
	/*If T is an array type, provides the member constant value equal to the number of dimensions of the array. For any other type, value is ​0​.*/
	std::cout << "[ rank: " << std::rank<T>::value << " ] \n";
	/*If T is an array type, provides the member constant value equal to the number of elements along the Nth dimension of the array, if N is in [​0​, std::rank<T>::value). For any other type, or if T is an array of unknown bound along its first dimension and N is ​0​, value is ​0​.*/
	if constexpr (std::rank<T>::value > 0/*T是個數組*/) std::cout << "[ extent: " << std::extent<T, 1>::value << " ] \n";

	// Callable properties
	/*template< class Fn, class... ArgTypes >
	   struct is_invocable;*/
	   /*Determines whether INVOKE(std::declval<Fn>(), std::declval<ArgTypes>()...) is well formed when treated as an unevaluated operand.*/
	if (std::is_invocable<T>::value) std::cout << "[ invocable ] \n";
	/*template< class R, class Fn, class... ArgTypes >
	   struct is_invocable_r;*/
	   /*Determines whether INVOKE<R>(std::declval<Fn>(), std::declval<ArgTypes>()...) is well formed when treated as an unevaluated operand.*/
	if (std::is_invocable_r<U, T>::value) std::cout << "[ invocable_r ] \n";
	/*template< class Fn, class... ArgTypes >
	   struct is_nothrow_invocable;*/
	   /*Determines whether INVOKE(std::declval<Fn>(), std::declval<ArgTypes>()...) is well formed when treated as an unevaluated operand, and is known not to throw any exceptions.*/
	if (std::is_nothrow_invocable<T>::value) std::cout << "[ nothrow invocable ] \n";
	/*template< class R, class Fn, class... ArgTypes >
	   struct is_nothrow_invocable_r;*/
	   /*Determines whether INVOKE<R>(std::declval<Fn>(), std::declval<ArgTypes>()...) is well formed when treated as an unevaluated operand, and is known not to throw any exceptions.*/
	if (std::is_nothrow_invocable_r<U, T>::value) std::cout << "[ nothrow invocable_r ] \n";

	// C++23 Reference properties
	// if (std::reference_constructs_from_temporary<T>::value) std::cout <<"[ reference constructs from temporary ] "; // C++23 feature
	// if (std::reference_converts_from_temporary<T>::value) std::cout <<"[ reference converts from temporary ] "; // C++23 feature

	/*Provides member typedef type, which is defined as T if B is true at compile time, or as F if B is false.*/
	std::cout << "[ type after conditional: " << typeid(typename std::conditional<true, T, T>::type).name() << " ] \n";

	// Type modifications
   /* Removes the topmost const, or the topmost volatile, or both, if present. */
	std::cout << "[ type after remove_cv: " << typeid(typename std::remove_cv<T>::type).name() << " ] \n";
	/* Removes the topmost const.*/
	std::cout << "[ type after remove_const: " << typeid(typename std::remove_const<T>::type).name() << " ] \n";
	/* Removes the topmost volatile.*/
	std::cout << "[ type after remove_volatile: " << typeid(typename std::remove_volatile<T>::type).name() << " ] \n";
	/* adds both const and volatile*/
	std::cout << "[ type after add_cv: " << typeid(typename std::add_cv<T>::type).name() << " ] \n";
	/* adds const*/
	std::cout << "[ type after add_const: " << typeid(typename std::add_const<T>::type).name() << " ] \n";
	/* adds volatile */
	std::cout << "[ type after add_volatile: " << typeid(typename std::add_volatile<T>::type).name() << " ] \n";
	/* an integral (except bool) or enumeration type, provides the member typedef type which is the signed integer type corresponding to T*/
	/* If T is signed or unsigned char, short, int, long, long long, the signed type from this list corresponding to T is provided.*/
	/* an enumeration type or char, wchar_t, char8_t(since C++20), char16_t, char32_t, the signed integer type with the smallest rank having the same sizeof as T is provided.*/
	std::cout << "[ type after make_signed: " << typeid(typename std::make_signed<T>::type).name() << " ] \n";
	/* an integral (except bool) or enumeration type, provides the member typedef type which is the unsigned integer type corresponding to T, with the same cv-qualifiers.*/
	/* signed or unsigned char, short, int, long, long long; the unsigned type from this list corresponding to T is provided.*/
	/* an enumeration type or char, wchar_t, char8_t(since C++20), char16_t, char32_t; the unsigned integer type with the smallest rank having the same sizeof as T is provided.*/
	std::cout << "[ type after make_unsigned: " << typeid(typename std::make_unsigned<T>::type).name() << " ] \n";
	/* a reference type, provides the member typedef type which is the type referred to by T.
	Otherwise type is T.*/
	std::cout << "[ type after remove_reference: " << typeid(typename std::remove_reference<T>::type).name() << " ] \n";
	/* T is a referenceable type => T& */
	/* T is not a referenceable type => T*/
	std::cout << "[ type after add_lvalue_reference: " << typeid(typename std::add_lvalue_reference<T>::type).name() << " ] \n";
	/* T is a referenceable type => T&& */
	/* T is not a referenceable type => T*/
	std::cout << "[ type after add_rvalue_reference: " << typeid(typename std::add_rvalue_reference<T>::type).name() << " ] \n";
	/*Provides the member typedef type which is the type pointed to by T, or, if T is not a pointer, then type is the same as T.*/
	std::cout << "[ type after remove_pointer: " << typeid(typename std::remove_pointer<T>::type).name() << " ] \n";
	/* add * to T*/
	/* If T is a referenceable type or (possibly cv-qualified) void, the member typedef type provided is typename std::remove_reference::type<T>*.
	Otherwise, the member typedef type provided is T.*/
	std::cout << "[ type after add_pointer: " << typeid(typename std::add_pointer<T>::type).name() << " ] \n";
	/*If T is an array of some type X, provides the member typedef type equal to X, otherwise type is T. Note that if T is a multidimensional array, only the first dimension is removed.*/
	std::cout << "[ type after remove_extent: " << typeid(typename std::remove_extent<T>::type).name() << " ] \n";
	/*If T is a multidimensional array of some type X, provides the member typedef type equal to X, otherwise type is T.*/
	std::cout << "[ type after remove_all_extents: " << typeid(typename std::remove_all_extents<T>::type).name() << " ] ";

	// Type transformations
	/* If T is "array of U" or reference to it, the member typedef type is U*.
	Otherwise, if T is a function type F or reference to one, the member typedef type is std::add_pointer<F>::type.
	Otherwise, the member typedef type is std::remove_cv<std::remove_reference<T>::type>::type.*/
	std::cout << "type after decay : " << typeid(typename std::decay<T>::type).name() << " ] ";
	/* 解讀:B是Bool，T是templete，兩者結合可以開發出一些功能。*/
	/* If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.*/
	std::cout << "[ type after enable_if: " << typeid(typename std::enable_if<true, T>::type).name() << " ] \n";
	/* Utility metafunction that maps a sequence of any types to the type void.*/
	std::cout << "[ type after void_t: " << typeid(typename std::void_t<T>).name() << " ] \n";
	/* 推導兩個或更多型別之間的共同型別（common type）。所謂的共同型別，是指能夠安全容納所有提供的型別的值的型別。*/
	std::cout << "[ type after common_type: " << typeid(typename std::common_type<T, T>::type).name() << " ] \n";
	/* 推導兩個或多個型別的共同參考型別（common reference type）*/
	std::cout << "[ type after common_reference: " << typeid(typename std::common_reference<T, T>::type).name() << " ] \n";
	/* 推導enum或enum class的uderlying_type*/
	/*Otherwise, the behavior is undefined.(until C++20)
	Otherwise, if T is not an enumeration type, there is no member type.
	Otherwise (T is an incomplete enumeration type), the program is ill-formed.*/
	//std::cout <<"[ type after underlying_type: " << std::underlying_type<T>::type << " ] \n";
	/*推導函數的返回值，普通函數，類或結構的非靜態成員函數，重載了operator()（Functors函數對象），Lambda表式，綁定表式 Bind expressions，閉包 Closures*/
	/* a callable type, reference to function, or reference to callable type. */
	/*F and all types in ArgTypes can be any complete type, array of unknown bound, or (possibly cv-qualified) void.*/
	std::cout << "[ type after invoke_result: " << typeid(typename std::invoke_result<void(*)(T), T>::type).name() << " ] \n";
	/*推導出T的類型，例如(4.2,1)正常會報錯，但用這能避免。*/
	std::cout << "[ type after type_identity: " << typeid(typename std::type_identity<T>::type).name() << " ] \n";

	std::cout
		<< "At " << std::setw(15) << functionName /*FUNCTION*/
		<< std::dec << ",line " << std::setw(5) << std::setfill('0') << std::right << line /*LINE*/\
		<< std::setfill(' ') << std::setw(10) << ",File: " << fileName    /*FILE*/
		/*<< ", Thread ID: " << std::this_thread::get_id() << ", "*//*THREAD*/
		<< '\n' << std::endl;
	std::cout.flags(originalFlags);


}

#define WHORU(var) \
do { \
    std::stringstream ss; \
    ss << "\nWHORU [" << typeid(decltype(var)).name() << "] " << #var << "\nBASIC\n"; \
    if (std::is_object<decltype(var)>::value) { \
        ss << "[ object ] "; \
        if (std::is_scalar<decltype(var)>::value) ss << "-> [ scalar ] "; \
        ss << '\n'; \
    } \
    if (std::is_fundamental<decltype(var)>::value) { \
        ss << "[ fundamental ] "; \
        if (std::is_void<decltype(var)>::value) ss << "->  [ void ] "; \
        if (std::is_null_pointer<decltype(var)>::value) ss << "-> [ null pointer ] "; \
        if (std::is_arithmetic<decltype(var)>::value) { \
            ss << "-> [ arithmetic ] "; \
            if (std::is_integral<decltype(var)>::value) ss << "-> [ integral ] "; \
            if (std::is_floating_point<decltype(var)>::value) ss << "-> [ floating point ] "; \
            if constexpr (std::is_signed<decltype(var)>::value) ss << "-> [ signed ] "; \
            if constexpr (std::is_unsigned<decltype(var)>::value) ss << "-> [ unsigned ] "; \
        } \
        ss << '\n'; \
    } \
    if (std::is_compound<decltype(var)>::value) { \
        ss << "[ compound ] "; \
        if (std::is_function<decltype(var)>::value) std::cout << "-> [ function ] "; \
        if (std::is_reference<decltype(var)>::value) { \
            ss << "-> [ reference ] "; \
            if (std::is_lvalue_reference<decltype(var)>::value) ss << "-> [ lvalue reference ] "; \
            if (std::is_rvalue_reference<decltype(var)>::value) ss << "-> [ rvalue reference ] "; \
        } \
        if (std::is_array<decltype(var)>::value) { \
            ss << "-> [ array ] "; \
            if (std::is_bounded_array<decltype(var)>::value) ss << "-> [ bounded array ] "; \
            if (std::is_unbounded_array<decltype(var)>::value) ss << "-> [ unbounded array ] "; \
        } \
        if (std::is_union<decltype(var)>::value) ss << "-> [ union ] "; \
        if (std::is_class<decltype(var)>::value) { \
            ss << "-> [ class ] "; \
            if (std::is_empty<decltype(var)>::value) ss << "-> [ empty class ] "; \
            if (std::is_polymorphic<decltype(var)>::value) { \
                ss << "-> [ polymorphic class ] "; \
                if (std::is_abstract<decltype(var)>::value) ss << "-> [ abstract class ] "; \
            } \
            if (std::is_final<decltype(var)>::value) ss << "-> [ final class ] "; \
            if (std::is_aggregate<decltype(var)>::value) ss << "-> [ aggregate ] "; \
        } \
        if (std::is_pointer<decltype(var)>::value) ss << "-> [ pointer ] "; \
        if (std::is_enum<decltype(var)>::value) ss << "-> [ enum ] "; \
        if (std::is_member_pointer<decltype(var)>::value) { \
            ss << "-> [ member pointer ] "; \
            if (std::is_member_object_pointer<decltype(var)>::value) ss << "-> [ member object pointer ] "; \
            if (std::is_member_function_pointer<decltype(var)>::value) ss << "-> [ member function pointer ] "; \
        } \
        ss << '\n'; \
    } \
    if (std::is_const<decltype(var)>::value) ss << "[ const ] \n"; \
    if (std::is_volatile<decltype(var)>::value) ss << "[ volatile ] \n"; \
     ss << "CLASS_PROPERTIES\n";\
if (std::is_constructible<decltype(var)>::value) {\
	ss << "[ constructible ] ";\
	if (std::is_default_constructible<decltype(var)>::value) ss << "-> [ default constructible ] ";\
	if (std::is_copy_constructible<decltype(var)>::value) ss << "-> [ copy constructible ] ";\
	if (std::is_move_constructible<decltype(var)>::value) ss << "-> [ move constructible ] ";\
	ss << '\n';\
}\
if (std::is_assignable<decltype(var), decltype(var)>::value) {\
	ss << "[ assignable ] ";\
	if (std::is_copy_assignable<decltype(var)>::value) ss << "-> [ copy assignable ] ";\
	if (std::is_move_assignable<decltype(var)>::value) ss << "-> [ move assignable ] ";\
	ss << '\n';\
}\
if (std::is_destructible<decltype(var)>::value) {\
	ss << "[ destructible ] ";\
	if (std::has_virtual_destructor<decltype(var)>::value) ss << "-> [ virtual destructor ] ";\
	ss << '\n';\
}\
if (std::is_swappable<decltype(var)>::value) {\
	ss << "[ swappable ] ";\
	if (std::is_nothrow_swappable<decltype(var)>::value) ss << "-> [ nothrow swappable ] "; \
	ss << '\n';\
}\
ss << "CLASS_PROPERTIES_TRIVIAL\n";\
if (std::is_trivial<decltype(var)>::value) ss << "[ trivial ] \n";\
if (std::is_trivially_copyable<decltype(var)>::value) ss << "[ trivially copyable ] \n";\
if (std::is_trivially_constructible<decltype(var)>::value) {\
	ss << "[ trivially constructible ] ";\
	if (std::is_trivially_default_constructible<decltype(var)>::value) ss << "-> [ trivially default constructible ] ";\
	if (std::is_nothrow_constructible<decltype(var)>::value) {\
		ss << "-> [ nothrow constructible ] ";\
		if (std::is_nothrow_default_constructible<decltype(var)>::value) ss << "-> [ nothrow default constructible ] ";\
		ss << '\n';\
	}\
}\
if (std::is_trivially_copy_constructible<decltype(var)>::value) {\
	ss << "[ trivially copy constructible ] ";\
	if (std::is_nothrow_copy_constructible<decltype(var)>::value) ss << "-> [ nothrow copy constructible ] ";\
	ss << '\n';\
}\
if (std::is_trivially_move_constructible<decltype(var)>::value) {\
	ss << "[ trivially move constructible ] ";\
	if (std::is_nothrow_move_constructible<decltype(var)>::value) ss << "-> [ nothrow move constructible ] ";\
	ss << '\n';\
}\
if (std::is_trivially_copy_assignable<decltype(var)>::value) {\
	ss << "[ trivially copy assignable ] ";\
	if (std::is_nothrow_copy_assignable<decltype(var)>::value) ss << "-> [ nothrow copy assignable ] ";\
	ss << '\n';\
}\
if (std::is_trivially_move_assignable<decltype(var)>::value) {\
	ss << "[ trivially move assignable ] ";\
	if (std::is_nothrow_move_assignable<decltype(var)>::value) ss << "-> [ nothrow move assignable ] ";\
	ss << '\n';\
}\
if (std::is_trivially_destructible<decltype(var)>::value) {\
	ss << "[ trivially destructible ] ";\
	if (std::is_nothrow_destructible<decltype(var)>::value) ss << "-> [ nothrow destructible ] ";\
	ss << '\n';\
}\
ss << "[ alignment of: " << std::alignment_of<decltype(var)>::value << " ] \n";\
ss << "[ rank: " << std::rank<decltype(var)>::value << " ] \n";\
if constexpr (std::rank<decltype(var)>::value > 0) ss << "[ extent: " << std::extent<decltype(var), 0>::value << " ] \n";\
if (std::is_invocable<decltype(var)>::value) ss << "[ invocable ] \n";\
if (std::is_nothrow_invocable<decltype(var)>::value) ss << "[ nothrow invocable ] \n";\
std::cout << ss.str();\
} while (0)

////完成，新增:這個有問題，使用define版本
//#define WHORU(var) WhoAreYou(#var, var)
//template <typename T>
//__forceinline void WhoAreYou(const char* varName, T&& var) {
//	std::stringstream ss;
//
//	ss << "\nWHORU [" << typeid(T).name() << "] " << varName << "\nBASIC\n";
//
//	/* fundmental, void, compound, function, reference不是object*/
//	/* array, class, union, null_pointer, arithmetic, integral, floating_point, enum, pointer, member_pointer是object*/
//	/* an object type (that is any possibly cv-qualified type other than function, reference, or void types)*/
//	if (std::is_object<\
//		T\
//	>::value) {
//		ss << "[ object ] ";
//		/*a scalar type*/
//		/*null_pointer, arithmetic, integral, floating_point, enum, pointer, member_pointer是scalar*/
//		if (std::is_scalar<T>::value) ss << "-> [ scalar ] ";
//		ss << '\n';
//	}
//
//	/* a fundamental type (that is, arithmetic type, void, or nullptr_t)*/
//	if (std::is_fundamental<T>::value) {
//		ss << "[ fundamental ] ";
//		/* void, const void, volatile void, or const volatile void*/
//		if (std::is_void<T>::value) ss << "->  [ void ] ";
//		/* std::nullptr_t, const std::nullptr_t, volatile std::nullptr_t, or const volatile std::nullptr_t.*/
//		if (std::is_null_pointer<T>::value) ss << "-> [ null pointer ] ";
//		/* an arithmetic type (that is, an integral type or a floating-point type) or a cv-qualified version thereof*/
//		if (std::is_arithmetic<T>::value) {
//			ss << "-> [ arithmetic ] ";
//			/* the type bool, char, char8_t(since C++20), char16_t, char32_t, wchar_t, short, int, long, long long, or any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants*/
//			if (std::is_integral<T>::value) ss << "-> [ integral ] ";
//			/* the type float, double, long double, or any extended floating-point types (std::float16_t, std::float32_t, std::float64_t, std::float128_t, or std::bfloat16_t)(since C++23), including any cv-qualified variants*/
//			if (std::is_floating_point<T>::value) ss << "-> [ floating point ] ";
//			if constexpr (std::is_signed<T>::value) ss << "-> [ signed ] ";
//			if constexpr (std::is_unsigned<T>::value) ss << "-> [ unsigned ] ";
//		}
//		ss << '\n';
//	}
//
//	/* a compound type (that is, array, function, object pointer, function pointer, member object pointer, member function pointer, reference, class, union, or enumeration, including any cv-qualified variants)*/
//	if (std::is_compound<T>::value) {
//		ss << "[ compound ] ";
//		/* a function type.
//		Types like std::function, lambdas, classes with overloaded operator() and pointers to functions don't count as function types*/
//		if (std::is_function<T>::value) std::cout << "-> [ function ] ";
//		/* a reference type (lvalue reference or rvalue reference)*/
//		if (std::is_reference<T>::value) {
//			ss << "-> [ reference ] ";
//			/* an lvalue reference type*/
//			if (std::is_lvalue_reference<T>::value) ss << "-> [ lvalue reference ] ";
//			/* an rvalue reference type*/
//			if (std::is_rvalue_reference<T>::value) ss << "-> [ rvalue reference ] ";
//		}
//
//		/*解讀:除了array外，std::array，std::vector等也是*/
//		/* array type*/
//		if (std::is_array<T>::value) {
//			ss << "-> [ array ] ";
//			/* an array type of known bound*/
//			if (std::is_bounded_array<T>::value) ss << "-> [ bounded array ] "; // C++20 feature
//			/* an arrays of unknown bound*/
//			if (std::is_unbounded_array<T>::value) ss << "-> [ unbounded array ] "; // C++20 feature
//		}
//		/* a union type*/
//		if (std::is_union<T>::value) ss << "-> [ union ] ";
//		/* a non-union class type*/
//		if (std::is_class<T>::value) {
//			ss << "-> [ class ] ";
//			/*解讀:一個空的類*/
//			/* an empty type (that is, a non-union class type with no non-static data members other than bit-fields of size 0, no virtual functions, no virtual base classes, and no non-empty base classes)*/
//			if (std::is_empty<T>::value) ss << "-> [ empty class ] ";
//			/*解讀:有或繼承虛函數的類*/
//			/* a polymorphic class (that is, a non-union class that declares or inherits at least one virtual function)*/
//			if (std::is_polymorphic<T>::value) {
//				ss << "-> [ polymorphic class ] ";
//				/*解讀:一個有或繼承純虛函數的基類*/
//				/* an abstract class (that is, a non-union class that declares or inherits at least one pure virtual function)*/
//				if (std::is_abstract<T>::value) ss << "-> [ abstract class ] ";
//			}
//			/*解讀:一個不被繼承的類*/
//			/* a final class*/
//			if (std::is_final<T>::value) ss << "-> [ final class ] ";
//
//			/*解讀:一個無構造函數，無private或protected的non-static 數據成員，無基類或虛函數，
//			無virtual private 或protected的繼承(从 C++17 开始，允许继承，但继承必须是公有的且非虚拟的)，
//			无任何类型的赋值运算符重载和非静态数据成员的初始值(从 C++14 开始，非静态成员可以有初始值。)*/
//			/*例如:宣告struct Point {int x;int y;} 初始化Point p = {10, 20};*/
//			/* an aggregate type，struct class或array(array本來就是)*/
//			if (std::is_aggregate<T>::value) ss << "-> [ aggregate ] ";
//		}
//
//		/* a pointer to object or function (including pointer to void, but excluding pointer to member) or a cv-qualified version thereof*/
//		if (std::is_pointer<T>::value) ss << "-> [ pointer ] ";
//		/* an enumeration type*/
//		if (std::is_enum<T>::value) ss << "-> [ enum ] ";
//		/* pointer to non-static member object or a pointer to non-static member function*/
//		if (std::is_member_pointer<T>::value) {
//			ss << "-> [ member pointer ] ";
//			/* a non-static member object pointer*/
//			if (std::is_member_object_pointer<T>::value) ss << "-> [ member object pointer ] ";
//			/* a non-static member function pointer*/
//			if (std::is_member_function_pointer<T>::value) ss << "-> [ member function pointer ] ";
//		}
//		ss << '\n';
//
//	}
//
//	/* a const-qualified type (that is, const, or const volatile)*/
//	if (std::is_const<std::remove_reference_t<decltype(var)>>::value) ss << "[ const ] \n";
//	/* a volatile-qualified type (that is, volatile, or const volatile)*/
//	if (std::is_volatile<T>::value) ss << "[ volatile ] \n";
//
//	/*(This type trait has been deprecated[1] and removed[2] as offering negligible value to generic code.)*/
//	//if (std::is_literal_type<T>::value) std::cout <<"[ literal type ] \n"; // Deprecated in C++20
//	/*(deprecated in C++20)*/
//	//if (std::is_pod<T>::value) std::cout <<"[ POD ] \n"; // Deprecated in C++20
//
//	/* a scoped enumeration type*/
//	//if constexpr (std::is_scoped_enum<T>::value) std::cout <<"[ scoped enum ] \n"; // C++23 feature, use with caution
//	/* an implicit-lifetime type(C++23)*/
//	//if constexpr (std::is_implicit_lifetime<T>::value) std::cout <<"[ implicit lifetime ] \n"; // C++23 feature, use with caution
//
//	// C++23 Reference properties
//	// if (std::reference_constructs_from_temporary<T>::value) std::cout <<"[ reference constructs from temporary ] "; // C++23 feature
//	// if (std::reference_converts_from_temporary<T>::value) std::cout <<"[ reference converts from temporary ] "; // C++23 feature
//
//	//常見度不高隱藏	/*解讀:非靜態數據成員都是相同的訪問控制，沒有虛函數和虛基類，所有基類和成員都要遵守規定，和其他規定*/
//	///* a standard-layout type*/
//	//if (std::is_standard_layout<T>::value) std::cout << "[ standard layout ] \n";
//
//	//常見度不高隱藏/* TriviallyCopyable and if any two objects of type T with the same value have the same object representation*/
//	//if (std::has_unique_object_representations<T>::value) std::cout << "[ unique object representations ] \n"; // C++17 feature
//	///*文章節錄：
//	//For the purpose of this trait, two arrays have the same value if their elements have the same values, two non-union classes have the same value if their direct subobjects have the same value, and two unions have the same value if they have the same active member and the value of that member is the same.
//	//It is implementation-defined which scalar types satisfy this trait, but unsigned(until C++20) integer types that do not use padding bits are guaranteed to have unique object representations.
//	//The behavior is undefined if T is an incomplete type other than (possibly cv-qualified) void or array of unknown bound.
//	//If the program adds specializations for std::has_unique_object_representations or std::has_unique_object_representations_v, the behavior is undefined.*/
//
//	ss << "CLASS_PROPERTIES\n";
//
//	/*解讀：template< class T, class... Args >struct is_constructible;是多參數的，default是單參數
//	第一個參數後是參數是構造的參數*/
//	// Construction
//	/* an object or reference type and the variable definition T obj(std::declval<Args>()...); is well-formed*/
//	if (std::is_constructible<T>::value) {
//		ss << "[ constructible ] ";
//		if (std::is_default_constructible<T>::value) ss << "-> [ default constructible ] ";
//		/*文章節錄：關於以上的undefined behavior
//		If T is not a complete type, (possibly cv-qualified) void, or an array of unknown bound, the behavior is undefined.
//		If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.*/
//		/* equal to std::is_constructible<T>::value*/
//
//		/*T is a referenceable type*/
//		/* 相等於std::is_constructible<T, const T&>::value*/
//		if (std::is_copy_constructible<T>::value) {
//			ss << "-> [ copy constructible ] ";
//		}
//		/*T is a referenceable type*/
//		/* 相等於std::is_constructible<T, T&&>::value*/
//		if (std::is_move_constructible<T>::value) {
//			ss << "-> [ move constructible ] ";
//		}
//		ss << '\n';
//	}
//
//	/* T is a referenceable type*/
//	/*  If the expression std::declval<T>() = std::declval<U>() is well-formed in unevaluated context*/
//	if (std::is_assignable<T, T>::value) {
//		ss << "[ assignable ] ";
//		/* 相等於std::is_assignable<T, const T&>::value*/
//		if (std::is_copy_assignable<T>::value) {
//			ss << "-> [ copy assignable ] ";
//		}
//		/* T is a referenceable type*/
//		/* 相等於std::is_assignable<T, T&&>::value*/
//		if (std::is_move_assignable<T>::value) {
//			ss << "-> [ move assignable ] ";
//		}
//		ss << '\n';
//	}
//
//	/*解讀3.：如果是object，通過std::remove_all_extents<T>::type去除數組，如int[10][20](T)變為int(U)，接著使用std::declval<U&>().~U()，測試析構函數是否well-formed，也是主要的工作目標。*/
//	// Destruction
//	/*1.a reference type ,value equals true,
//	2.(possibly cv-qualified) void, a function type, or an array of unknown bound, value equals false
//	3.If T is an object type, then, for the type U that is std::remove_all_extents<T>::type, if the expression std::declval<U&>().~U() is well-formed in unevaluated context, value equals true*/
//	if (std::is_destructible<T>::value) {
//		ss << "[ destructible ] ";
//		/*Same as is_destructible and additionally std::remove_all_extents<T>::type is either a non-class type or a class type with a trivial destructor.*/
//
//		/*If T is a type with a virtual destructor, the base characteristic is std::true_type. For any other type, the base characteristic is std::false_type.*/
//		if (std::has_virtual_destructor<T>::value) ss << "-> [ virtual destructor ] ";
//		ss << '\n';
//	}
//	// C++17 Swappable traits
//	/* 相等於std::is_swappable_with<T&, T&>::value*/
//	if (std::is_swappable<T>::value) {
//		ss << "[ swappable ] "; // C++17 feature
//		/* 相等於std::is_nothrow_swappable_with<T&, T&>::value*/
//		if (std::is_nothrow_swappable<T>::value) ss << "-> [ nothrow swappable ] "; // C++17 feature
//		ss << '\n';
//	}
//
//	ss << "CLASS_PROPERTIES_TRIVIAL\n";
//	/* a trivial type*/
//	if (std::is_trivial<T>::value) ss << "[ trivial ] \n";
//	/* a trivially copyable type*/
//	if (std::is_trivially_copyable<T>::value) ss << "[ trivially copyable ] \n";
//
//	/* Same as is_constructible, but the variable definition does not call any operation that is not trivial*/
//	if (std::is_trivially_constructible<T>::value) {
//		ss << "[ trivially constructible ] ";
//		/* equal to std::is_trivially_constructible<T>::value*/
//		if (std::is_trivially_default_constructible<T>::value) {
//			ss << "-> [ trivially default constructible ] ";
//		}
//		/* Same as is_constructible, but the variable definition is noexcept*/
//		if (std::is_nothrow_constructible<T>::value) {
//			ss << "-> [ nothrow constructible ] ";
//			/* equal to std::is_nothrow_constructible<T>::value*/
//			if (std::is_nothrow_default_constructible<T>::value) ss << "-> [ nothrow default constructible ] ";
//			ss << '\n';
//		}
//	}
//
//	/* 相等於std::is_trivially_constructible<T, const T&>::value*/
//	if (std::is_trivially_copy_constructible<T>::value) {
//		ss << "[ trivially copy constructible ] ";
//		/* 相等於std::is_nothrow_constructible<T, const T&>::value*/
//		if (std::is_nothrow_copy_constructible<T>::value) ss << "-> [ nothrow copy constructible ] ";
//		ss << '\n';
//	}
//	/* 相等於std::is_trivially_constructible<T, T&&>::value*/
//	if (std::is_trivially_move_constructible<T>::value) {
//		ss << "[ trivially move constructible ] ";
//		/* 相等於std::is_nothrow_constructible<T, T&&>::value*/
//		if (std::is_nothrow_move_constructible<T>::value) ss << "-> [ nothrow move constructible ] ";
//		ss << '\n';
//	}
//	/* 相等於std::is_trivially_assignable<T, const T&>::value*/
//	if (std::is_trivially_copy_assignable<T>::value) {
//		ss << "[ trivially copy assignable ] ";
//		/* 相等於std::is_nothrow_assignable<T, const T&>::value*/
//		if (std::is_nothrow_copy_assignable<T>::value) ss << "-> [ nothrow copy assignable ] ";
//		ss << '\n';
//	}
//	/* 相等於std::is_trivially_assignable<T, T&&>::value*/
//	if (std::is_trivially_move_assignable<T>::value) {
//		ss << "[ trivially move assignable ] ";
//		/* 相等於std::is_nothrow_assignable<T, T&&>::value*/
//		if (std::is_nothrow_move_assignable<T>::value) ss << "-> [ nothrow move assignable ] ";
//		ss << '\n';
//	}
//	if (std::is_trivially_destructible<T>::value) {
//		ss << "[ trivially destructible ] ";
//		/*Same as is_destructible, but the destructor is noexcept.*/
//		if (std::is_nothrow_destructible<T>::value) ss << "-> [ nothrow destructible ] ";
//		/*文章節錄：未定義的行為
//		If T is not a complete type, (possibly cv-qualified) void, or an array of unknown bound, the behavior is undefined.
//		If an instantiation of a template above depends, directly or indirectly, on an incomplete type, and that instantiation could yield a different result if that type were hypothetically completed, the behavior is undefined.*/
//		ss << '\n';
//	}
//
//	/*解讀：std::rank<T>::value是數組的維度，一般變量是0。*/
//	/*解讀：std::extent<T,0>::value是數組指定維度的變量數，如std::extent<int[3],0>::value==3。*/
//	// Type properties
//	/*Provides the member constant value equal to the alignment requirement of the type T, as if obtained by an alignof expression. If T is an array type, returns the alignment requirements of the element type. If T is a reference type, returns the alignment requirements of the type referred to.*/
//	ss << "[ alignment of: " << std::alignment_of<T>::value << " ] \n";
//	/*If T is an array type, provides the member constant value equal to the number of dimensions of the array. For any other type, value is ​0​.*/
//	ss << "[ rank: " << std::rank<T>::value << " ] \n";
//	/*If T is an array type, provides the member constant value equal to the number of elements along the Nth dimension of the array, if N is in [​0​, std::rank<T>::value). For any other type, or if T is an array of unknown bound along its first dimension and N is ​0​, value is ​0​.*/
//	if constexpr (std::rank<T>::value > 0/*T是個數組*/) ss << "[ extent: " << std::extent<T, 1>::value << " ] \n";
//
//	// Callable properties
//	/*template< class Fn, class... ArgTypes >
//	   struct is_invocable;*/
//	   /*Determines whether INVOKE(std::declval<Fn>(), std::declval<ArgTypes>()...) is well formed when treated as an unevaluated operand.*/
//	if (std::is_invocable<T>::value) ss << "[ invocable ] \n";
//	/*template< class R, class Fn, class... ArgTypes >
//	   struct is_invocable_r;*/
//	   /*template< class Fn, class... ArgTypes >
//		  struct is_nothrow_invocable;*/
//		  /*Determines whether INVOKE(std::declval<Fn>(), std::declval<ArgTypes>()...) is well formed when treated as an unevaluated operand, and is known not to throw any exceptions.*/
//	if (std::is_nothrow_invocable<T>::value) ss << "[ nothrow invocable ] \n";
//	/*template< class R, class Fn, class... ArgTypes >
//	   struct is_nothrow_invocable_r;*/
//
//	std::cout << ss.str();
//}

//暫時放置其他一些函數
template<typename T>
void other_tpye_traits_Tools()
{
	// Type modifications
/* Removes the topmost const, or the topmost volatile, or both, if present. */
	std::cout << "[ type after remove_cv: " << typeid(typename std::remove_cv<T>::type).name() << " ] \n";
	/* Removes the topmost const.*/
	std::cout << "[ type after remove_const: " << typeid(typename std::remove_const<T>::type).name() << " ] \n";
	/* Removes the topmost volatile.*/
	std::cout << "[ type after remove_volatile: " << typeid(typename std::remove_volatile<T>::type).name() << " ] \n";
	/* adds both const and volatile*/
	std::cout << "[ type after add_cv: " << typeid(typename std::add_cv<T>::type).name() << " ] \n";
	/* adds const*/
	std::cout << "[ type after add_const: " << typeid(typename std::add_const<T>::type).name() << " ] \n";
	/* adds volatile */
	std::cout << "[ type after add_volatile: " << typeid(typename std::add_volatile<T>::type).name() << " ] \n";

	if constexpr (std::is_arithmetic<T>::value) {
		/* an integral (except bool) or enumeration type, provides the member typedef type which is the signed integer type corresponding to T*/
		/* If T is signed or unsigned char, short, int, long, long long, the signed type from this list corresponding to T is provided.*/
		/* an enumeration type or char, wchar_t, char8_t(since C++20), char16_t, char32_t, the signed integer type with the smallest rank having the same sizeof as T is provided.*/
		std::cout << "[ type after make_signed: " << typeid(typename std::make_signed<T>::type).name() << " ] \n";
		/* an integral (except bool) or enumeration type, provides the member typedef type which is the unsigned integer type corresponding to T, with the same cv-qualifiers.*/
		/* signed or unsigned char, short, int, long, long long; the unsigned type from this list corresponding to T is provided.*/
		/* an enumeration type or char, wchar_t, char8_t(since C++20), char16_t, char32_t; the unsigned integer type with the smallest rank having the same sizeof as T is provided.*/
		std::cout << "[ type after make_unsigned: " << typeid(typename std::make_unsigned<T>::type).name() << " ] \n";
	}
	/* a reference type, provides the member typedef type which is the type referred to by T.
	Otherwise type is T.*/
	std::cout << "[ type after remove_reference: " << typeid(typename std::remove_reference<T>::type).name() << " ] \n";
	/* T is a referenceable type => T& */
	/* T is not a referenceable type => T*/
	std::cout << "[ type after add_lvalue_reference: " << typeid(typename std::add_lvalue_reference<T>::type).name() << " ] \n";
	/* T is a referenceable type => T&& */
	/* T is not a referenceable type => T*/
	std::cout << "[ type after add_rvalue_reference: " << typeid(typename std::add_rvalue_reference<T>::type).name() << " ] \n";
	/*Provides the member typedef type which is the type pointed to by T, or, if T is not a pointer, then type is the same as T.*/
	std::cout << "[ type after remove_pointer: " << typeid(typename std::remove_pointer<T>::type).name() << " ] \n";
	/* add * to T*/
	/* If T is a referenceable type or (possibly cv-qualified) void, the member typedef type provided is typename std::remove_reference::type<T>*.
	Otherwise, the member typedef type provided is T.*/
	std::cout << "[ type after add_pointer: " << typeid(typename std::add_pointer<T>::type).name() << " ] \n";
	/*If T is an array of some type X, provides the member typedef type equal to X, otherwise type is T. Note that if T is a multidimensional array, only the first dimension is removed.*/
	std::cout << "[ type after remove_extent: " << typeid(typename std::remove_extent<T>::type).name() << " ] \n";
	/*If T is a multidimensional array of some type X, provides the member typedef type equal to X, otherwise type is T.*/
	std::cout << "[ type after remove_all_extents: " << typeid(typename std::remove_all_extents<T>::type).name() << " ] ";
	// Type transformations
	/* If T is "array of U" or reference to it, the member typedef type is U*.
	Otherwise, if T is a function type F or reference to one, the member typedef type is std::add_pointer<F>::type.
	Otherwise, the member typedef type is std::remove_cv<std::remove_reference<T>::type>::type.*/
	std::cout << "[ type after decay : " << typeid(typename std::decay<T>::type).name() << " ] ";
	/* 解讀:B是Bool，T是templete，兩者結合可以開發出一些功能。*/
	/* If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.*/
	std::cout << "[ type after enable_if: " << typeid(typename std::enable_if<true, T>::type).name() << " ] \n";
	/* Utility metafunction that maps a sequence of any types to the type void.*/
	std::cout << "[ type after void_t: " << typeid(typename std::void_t<T>).name() << " ] \n";
	/* 推導兩個或更多型別之間的共同型別（common type）。所謂的共同型別，是指能夠安全容納所有提供的型別的值的型別。*/
	std::cout << "[ type after common_type: " << typeid(typename std::common_type<T, T>::type).name() << " ] \n";
	/* 推導兩個或多個型別的共同參考型別（common reference type）*/
	std::cout << "[ type after common_reference: " << typeid(typename std::common_reference<T, T>::type).name() << " ] \n";
	/* 推導enum或enum class的uderlying_type*/
	/*Otherwise, the behavior is undefined.(until C++20)
	Otherwise, if T is not an enumeration type, there is no member type.
	Otherwise (T is an incomplete enumeration type), the program is ill-formed.*/
	//std::cout <<"[ type after underlying_type: " << std::underlying_type<T>::type << " ] \n";
	/*推導函數的返回值，普通函數，類或結構的非靜態成員函數，重載了operator()（Functors函數對象），Lambda表式，綁定表式 Bind expressions，閉包 Closures*/
	/* a callable type, reference to function, or reference to callable type. */
	/*F and all types in ArgTypes can be any complete type, array of unknown bound, or (possibly cv-qualified) void.*/
	std::cout << "[ type after invoke_result: " << typeid(typename std::invoke_result<void(*)(T), T>::type).name() << " ] \n";
	/*推導出T的類型，例如(4.2,1)正常會報錯，但用這能避免。*/
	std::cout << "[ type after type_identity: " << typeid(typename std::type_identity<T>::type).name() << " ] \n";
}

#else
template <typename T>
void Type(const char* varName, T  var, int line, const char* functionName) {}
template <typename T>
void Log(const char* varName, T  var, int line, const char* functionName) {}
#endif

#endif
