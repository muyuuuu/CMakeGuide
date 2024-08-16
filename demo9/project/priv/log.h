#ifndef __log_h__
#define __log_h__

#ifdef __cpluscplus
extern "C"
{
#endif

#include <stdio.h>

#define LOG(tag, format, ...) \
    printf("[%s] [%s %s %d] " format, tag, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#ifdef __cpluscplus
}
#endif

#endif