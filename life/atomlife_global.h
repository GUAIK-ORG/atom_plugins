#ifndef ATOMLIFE_GLOBAL_H
#define ATOMLIFE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ATOMLIFE_LIBRARY)
#  define ATOMLIFE_EXPORT Q_DECL_EXPORT
#else
#  define ATOMLIFE_EXPORT Q_DECL_IMPORT
#endif

#endif // ATOMLIFE_GLOBAL_H
