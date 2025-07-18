#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32
#define AUTELSDK_API __declspec(dllexport)
#else
#define AUTELSDK_API
#endif

#endif
