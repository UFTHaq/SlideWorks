/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   icon_Chain_png;
    const int            icon_Chain_pngSize = 2751;

    extern const char*   icon_Copy_png;
    const int            icon_Copy_pngSize = 1439;

    extern const char*   icon_Delete_png;
    const int            icon_Delete_pngSize = 1395;

    extern const char*   icon_HoriVerti_png;
    const int            icon_HoriVerti_pngSize = 865;

    extern const char*   icon_Lock_png;
    const int            icon_Lock_pngSize = 2719;

    extern const char*   icon_On_Visible_png;
    const int            icon_On_Visible_pngSize = 4787;

    extern const char*   icon_Rotate_png;
    const int            icon_Rotate_pngSize = 5192;

    extern const char*   RobotoCondensedMedium_ttf;
    const int            RobotoCondensedMedium_ttfSize = 144888;

    extern const char*   RobotoCondensedRegular_ttf;
    const int            RobotoCondensedRegular_ttfSize = 144852;

    extern const char*   RobotoCondensedSemiBold_ttf;
    const int            RobotoCondensedSemiBold_ttfSize = 145484;

    extern const char*   RobotoMonoMedium_ttf;
    const int            RobotoMonoMedium_ttfSize = 87172;

    extern const char*   small_scale_black_png;
    const int            small_scale_black_pngSize = 7374;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 12;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
