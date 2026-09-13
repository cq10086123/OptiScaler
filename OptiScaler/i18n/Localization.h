#pragma once
// Simple bilingual (English / Simplified Chinese) localization for OptiScaler UI.
//
// How it works:
//   - UI strings in the code stay in English and are wrapped with L() at display time,
//     e.g.  ImGui::Text(L("Close"));
//   - L() returns the Simplified Chinese translation when the user has selected Chinese
//     (menu: bottom bar "Language" combo, persisted as [Menu] Language in OptiScaler.ini),
//     and the original English string otherwise.
//   - Strings without a translation fall back to English automatically.
//
// The language can be switched at runtime from the menu; L() reads the current value
// from Config on every call, so changes take effect on the next frame.

#include <Config.h>

namespace Localization
{
    // Keep in sync with [Menu] Language in OptiScaler.ini
    enum class Language
    {
        English = 0,
        Chinese = 1,
    };

    // Current UI language, read from Config (so runtime switching works)
    Language Current();

    bool IsChinese();

    // Translate an English UI string to the current language.
    // Returns the input unchanged for English or when no translation exists.
    const char* L(const char* english);

    // Localized display names, e.g. for the language combo box
    const char* Name(Language lang);
    const char* CurrentName();
}

// Convenience free function so call sites read as L("English text")
inline const char* L(const char* english)
{
    return Localization::L(english);
}
