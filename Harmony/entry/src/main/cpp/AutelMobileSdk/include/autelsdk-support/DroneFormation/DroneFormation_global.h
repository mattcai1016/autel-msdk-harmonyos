#ifndef AUTELALGORITHM_GLOBAL_H
#define AUTELALGORITHM_GLOBAL_H

#ifdef _WIN32
#ifdef DRONEFORMATION_EXPORTS
 #define DRONEFORMATION_API __declspec(dllexport)
#else
 #define DRONEFORMATION_API __declspec(dllimport)
#endif
#else
#define DRONEFORMATION_API
#endif

#endif // AUTELALGORITHM_GLOBAL_H
