#ifndef CHORUSKIT_BATPROCGLOBAL_H
#define CHORUSKIT_BATPROCGLOBAL_H

#include <QtGlobal>

#if defined(BATPROC_LIBRARY)
#    define BATPROC_EXPORT Q_DECL_EXPORT
#else
#    define BATPROC_EXPORT Q_DECL_IMPORT
#endif

#endif GLOBAL_H
