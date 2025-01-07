/*
  ==============================================================================

    Easing.h
    Created: 6 Jan 2025 6:56:00pm
    Author:  UFThaq

  ==============================================================================
*/

#pragma once

#include <cmath>

template <typename Type>
inline Type easeOutQuint(Type x)
{
    return Type(1) - std::pow(Type(1) - x, Type(5));
}