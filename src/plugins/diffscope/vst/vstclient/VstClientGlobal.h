#ifndef CHORUSKIT_VSTCLIENTGLOBAL_H
#define CHORUSKIT_VSTCLIENTGLOBAL_H

#include <QtGlobal>

#ifdef VST_LIBRARY
#    define VST_EXPORT Q_DECL_EXPORT
#else
#    define VST_EXPORT Q_DECL_IMPORT
#endif

#endif // CHORUSKIT_VSTCLIENTGLOBAL_H