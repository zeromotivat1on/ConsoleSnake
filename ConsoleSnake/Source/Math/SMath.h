/**
 * File contains math helper functions and structs.
 */

#pragma once

// Custom types
#include "Math/IntVector2.h"

// Built-in types
#include "stdint.h"

namespace SMath
{

// Is the given value is within limits?
template <typename T> //
static inline bool WithinRange(T value, T lower, T upper, bool exclusive = true)
{
	return exclusive ? (value > lower && value < upper) : (value >= lower && value <= upper);
}

} // namespace SMath