/*
  ==============================================================================

    EnumClass.h
    Created: 1 Dec 2024 7:35:32am
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

enum class WorkingMode
{
    EDIT_MODE,
    PREVIEW_MODE,
    SIMULATION_MODE
};

enum class FilmstripOrientation
{
    VERTICAL_FILMSTRIP,
    HORIZONTAL_FILMSTRIP
};

enum class AnglesOrThumbPos
{
    ANGLES,
    THUMB_POS
};

enum class AssetType
{
    KNOB,
    KNOB_SCALE,
    THUMB,
    TRACK,
    TRACK_SCALE
};