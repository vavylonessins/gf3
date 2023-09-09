#ifndef __HACKS_H__
#define __HACKS_H__


#define pointable           \
    void* ptr(){            \
        return (void*)this; \
    }                       \

typedef signed         char int8   ;
typedef unsigned       char uint8  ;
typedef   signed      short int16  ;
typedef unsigned      short uint16 ;
typedef          long       int32  ;
typedef unsigned long       uint32 ;
typedef          long  long int64  ;
typedef unsigned long  long uint64 ;

#endif
