/*
  ==============================================================================

    EnumClass.h
    Created: 1 Dec 2024 7:35:32am
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

enum class PageState
{
    PAGE1_GREETINGS,
    PAGE2_WORKSPACE,
    PAGE3_INFO
};

enum class WorkingMode
{
    EDIT_MODE,
    PREVIEW_MODE,
    SIMULATION_MODE
};

enum class FilmstripOrientationEnum
{
    VERTICAL_FILMSTRIP,
    HORIZONTAL_FILMSTRIP
};

enum class AnglesOrThumbPos
{
    ANGLES,
    THUMB_POS
};

enum class FilmstripType
{
    KNOB,
    SLIDER
};

enum class AssetType
{
    KNOB,
    KNOB_SCALE,
    KNOB_SCALE_GENERATED,
    THUMB,
    TRACK,
    TRACK_SCALE,
    TRACK_SCALE_GENERATED,
};

enum class SliderSide
{
    MIN_LEFT_AND_MAX_RIGHT,     // MIN LEFT AND MAX RIGHT
    MIN_RIGHT_AND_MAX_LEFT,     // MIN RIGHT AND MAX LEFT
    MIN_BOTTOM_AND_MAX_TOP,     // MIN BOTTOM AND MAX TOP
    MIN_TOP_AND_MAX_BOTTOM,     // MIN TOP AND MAX BOTTOM
};