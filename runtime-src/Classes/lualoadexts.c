#include "lualoadexts.h"
#include "luamd5.h"
#include "lpack.h"
#include "luarpacketcrypto.h"
#include "lua_zlib.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "bit.h"
#endif

void luax_initpreload(lua_State *L)
{	
	luaopen_pack(L);	
	luaopen_md5(L);
	luaopen_packetcrypto(L);
	luaopen_zlib(L);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    // 苹果下无法 require "bit"
    luaopen_bit(L);
#endif
}

