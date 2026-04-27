#include "pch_Hazel.h"

// Visual Studio requires a .cpp translation unit for PCHs.
// Visual Studio also needs to create a PCH-file in order to
// use it, while with other compilers this does not necessarily
// happen. This is why the 'pchsource' needs to be declared
// in the premake-file, though it will automatically be
// excluded when creating these projects from other platforms
// which do not require it.