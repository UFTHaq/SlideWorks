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