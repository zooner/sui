#ifndef SUICORE_GLOBAL_H
#define SUICORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SUICORE_LIBRARY)
#  define SUICORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SUICORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SUICORE_GLOBAL_H
