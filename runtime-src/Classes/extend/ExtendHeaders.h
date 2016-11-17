#include "base/ccConfig.h"
#ifndef __ExtendHeaders_h__
#define __ExtendHeaders_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_custom_function(lua_State* tolua_S);

#endif