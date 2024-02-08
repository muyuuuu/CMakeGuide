#ifndef __error_h__
#define __error_h__

#ifdef __cpluscplus
extern "C"
{
#endif

typedef enum ErrorCode
{
    SUCCESS = 0,
    INVALID = -1,
    LEQZERO = 1,
    GRTZERO = 2
} ErrorCode;

#ifdef __cpluscplus
}
#endif

#endif