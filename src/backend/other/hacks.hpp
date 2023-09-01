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
typedef                 int int32  ;
typedef unsigned            uint32 ;
typedef          long       int64  ;
typedef unsigned long       uint64 ;
typedef          long  long int128 ;
typedef unsigned long  long uint128;

#endif
