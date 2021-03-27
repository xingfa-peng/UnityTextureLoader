#pragma once

#include <string>
using namespace std;

#ifdef _WIN64   
typedef wchar_t Char;
typedef wstring String;
#else
typedef char Char;
typedef string String;
#endif