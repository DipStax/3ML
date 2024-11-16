#pragma once

#if !defined(MMML_STATIC)
    #if defined(_WIN32)
        // Windows compilers need specific (and different) keywords for export and import
        #define M3L_API_EXPORT __declspec(dllexport)
        #define M3L_API_IMPORT __declspec(dllimport)
        // For Visual C++ compilers, we also need to turn off this annoying C4251 warning
        #ifdef _MSC_VER
            #pragma warning(disable : 4251)
        #endif
    #else // Linux, FreeBSD, macOS
        #define M3L_API_EXPORT __attribute__((__visibility__("default")))
        #define M3L_API_IMPORT __attribute__((__visibility__("default")))
    #endif
#endif

#if defined(MMML_EXPORTS)
    #define M3L_API M3L_API_EXPORT
#else
    #define M3L_API M3L_API_IMPORT
#endif