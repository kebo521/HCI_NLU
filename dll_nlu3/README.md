------

# Zhiye Fusion: Third-Party Function Integration (C/C++ Dynamic Library Approach)

#### Main Program Name

Zhiye (支叶)

#### Introduction

The Zhiye program begins as a seed, growing roots and branches through human interaction while continuously acquiring knowledge and ideas.
 It can assist humans with intellectual tasks (capabilities require user teaching or knowledge-sharing). When integrated with server resources, it masters unlimited knowledge.
 In the future, it will become an indispensable super assistant for every individual.

#### Runtime Environments

Data centers, large-scale servers, personal computers, smartphones, automotive systems, and intelligent robots.

#### Library Compilation Guide

1. Install Visual Studio (sample project created with VS2017).
2. Double-click to open `ThirdLib.sln` (VS project file).
3. Modify `ThirdFunc.cpp` in `ThirdLib/` (implements main interface functions, function mapping table, and author information).
4. Select: **Build** → **Rebuild gThirdLib**. If compiled successfully, this generates `gThirdLib.dll` (the dynamic library file).

#### Usage Instructions

1. Copy `gThirdLib.dll` to the directory containing `zhiye.exe`.
2. Run `zhiye.exe`, then load the library using the built-in `loadlib` function (enter: `loadlib("gThirdLib.dll")`).
3. If no errors occur, functions from `gThirdLib.dll` are now available in Zhiye.
4. Execute functions by entering their names (defined in `ThirdFunc.cpp`) with required parameters.
5. Unload libraries using `unload` (e.g., `unload("gThirdLib.dll")`).

#### Special Notes

1. Zhiye provides two built-in functions:
   - `loadlib`: Loads multiple third-party libraries.
   - `unload`: Unloads libraries (supports partial matching, e.g., `unload "dll"` unloads all DLLs).
2. All C/C++ and Y-language functions can be executed by name. Parameters follow in parentheses (parentheses optional for single parameters).
3. **Type II functions support overloading**. Parameters may be placed before, after, or on both sides of the function name. Zhiye auto-matches syntax based on context.
4. During execution, parameters and variables require no type declarations (types inferred during assignment, similar to Python).
5. Zhiye has continuous learning capabilities. It starts with minimal rules and develops logic through interaction—usage improves understanding.
6. During public testing, skills/knowledge acquired by Zhiye belong to the user.
7. **Users shall bear full responsibility** for consequences arising from teaching Zhiye to perform illegal actions.

