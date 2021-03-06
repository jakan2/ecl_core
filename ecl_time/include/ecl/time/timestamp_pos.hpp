/**
 * @file /include/ecl/time/timestamp_pos.hpp
 *
 * @brief Interfaces for the posix/rt timers.
 *
 * @date June, 2009
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_TIME_STAMP_POS_HPP_
#define ECL_TIME_STAMP_POS_HPP_

/*****************************************************************************
** Platform Check
*****************************************************************************/

#include <ecl/config.hpp>
#if defined(ECL_IS_POSIX)
#define ECL_HAS_TIMESTAMP

/*****************************************************************************
** Includes
*****************************************************************************/

#include <time.h>
#include <ecl/config/macros.hpp>
#include <ecl/config/portable_types.hpp>
#include <ecl/exceptions/macros.hpp>
#include <ecl/exceptions/standard_exception.hpp>
#include "timestamp_base.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Interface [Time]
*****************************************************************************/

/**
 * @brief Posix timestamping class.
 *
 * This class works with the posix timespec struct that allows
 * timestamping and operations on the time objects (differences etc).
 *
 * <b>Usage:</b>
 *
 * There are several ways of initialising the timestamp:
 * @code
 * TimeStamp time_system;           // Automatically captures system time since Epoch.
 * TimeStamp time_double(3.21)      // Initialise with a decimalised time (slow).
 * TimeStamp time_pair(3,210000000) // Initialise with a (s,ns) pair (fastest).
 * @endcode
 *
 * These operations can also be performed to set the timestamp after construction:
 *
 * @code
 * time_system.stamp();         // Automatically captures system time since Epoch.
 * time_double.stamp(3.21)      // Initialise with a decimalised time (slow).
 * time_pair.stamp(3,210000000) // Initialise with a (s,ns) pair (fast for posix rt systems).
 * @endcode
 *
 * All the usual comparison (==,!=,<=,>=,<,>) and mathematical (+,-,+=,-=) operations can also be used.
 *
 * @code
 * if ( time_system > time_double ) {
 *     time_system -= time_double;
 * }
 * @endcode
 *
 * <b>Caution</b>: The only thing to be wary of with timestamps is to remember that they
 * must always be positive. This was a design decision that keeps the timestamp class as light as
 * possible. If negativity was introduced, an extra sign bit would be required, and in almost all
 * timestamp operations, this is not necessary.
 *
 * <b>Error Handling</b>
 *
 * Will throw exceptions in debug mode if the timer doesn't initialise
 * properly (unlikely) or you exceed the resolution of a time unit/attempt to
 * create a negative timestamp (more likely).
 *
 * In release mode they do not come with any error handling. These functions
 * need to remain fast, like containers, and since they're not usually
 * destructive, such bells and whistles are omitted.
 **/
class ECL_PUBLIC TimeStamp : public TimeStampBase {
public:
	/*********************
	** Constructors
	**********************/
	/**
	 * @brief Initialises the timestamp with the current time.
	 *
	 * Constructor that initialises the timestamp with the current
	 * system time using the windows query performance calls (these call
	 * the intel handles under the hood).
	 *
	 * @exception StandardException : throws if clock lookup fails [debug mode only].
	 **/
	TimeStamp() ecl_debug_throw_decl(StandardException);
	/**
	 * @brief Initialise the timestamp with a default value.
	 *
	 * Initialises the timestamp with the specified double value. Note that this is
	 * slower than the manual initialisation with a sec/nsec pair.
	 *
	 * @param decimal_time_value : time units in seconds (integral part) and nanoseconds (decimal part).
	 *
	 * @exception StandardException : thrown from TimeStampBase if the input arguments is not positive [debug mode only].
	 */
	TimeStamp (const double& decimal_time_value) ecl_assert_throw_decl(StandardException);
	/**
	 * @brief Initialises the timestamp with the specified sec/nsec pair.
	 *
	 * This is the fastest means of initialisation to a set time value.
	 *
	 * @param seconds : discrete time value measured in whole seconds.
	 * @param nanoseconds : fraction of a second measured in nanoseconds.
	 *
	 * @exception StandardException : thrown from TimeStampBase if input arguments are not positive [debug mode only].
	 **/
	TimeStamp (const time_t &seconds, const long &nanoseconds) ecl_assert_throw_decl(StandardException);
	/**
	 * @brief Allow direct conversions from the base class.
	 *
	 * Not for direct use - it is only there so that the operators that return a TimeStampBase
	 * class will correctly convert into their child class counterparts. As the children
	 * only contain methods, this loses nothing.
	 *
	 * @param base : the base class (data) representation.
	 */
	TimeStamp (const TimeStampBase& base);

	virtual ~TimeStamp() {}

	/******************************************
	** Stamps
	*******************************************/
	using TimeStampBase::stamp;
	/**
	 * @brief Stamp with the system timestamp.
	 *
	 * Records the internal time variables with the current system time.
	 * @exception StandardException : throws if clock lookup fails [debug mode only].
	 */
	const TimeStamp& stamp() ecl_debug_throw_decl(StandardException);
};
}; // namespace ecl

#ifdef ECL_HAS_EXCEPTIONS
namespace ecl {
namespace time {

/**
 * This function generates a custom StandardException response
 * for posix error numbers generated by time.h function calls within
 * the TimeStamp class.
 * @param loc : use with the LOC macro, identifies the line and file of the code.
 */
ecl::StandardException throwTimeStampException(const char*loc);

} // namespace time
}; // namespace ecl

#endif /* ECL_HAS_EXCEPTIONS */


#endif /* ECL_IS_POSIX */
#endif /* ECL_TIME_STAMP_POS_HPP_ */
