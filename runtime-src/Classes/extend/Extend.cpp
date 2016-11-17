#include "cocos2d.h"
#include "extend/ExtendHeaders.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "lua_dragonbones_auto.hpp"
#include "MD5/luamd5.h"
#include "lpack.h"
//#include "lua_zlib.h"

USING_NS_CC;
using namespace std;

// ����Ϣ��
int MsgBox(lua_State* L)
{
	MessageBox((char*)luaL_checkstring(L, 1), "MsgBox");
	return 0;
}

// ע���Զ����lua����
int register_custom_function(lua_State * L)
{
	luaopen_md5(L);
	register_all_dragonbones(L);
	lua_register(L, "CCMessageBox", MsgBox);
	//luaopen_zlib(L);
	luaopen_pack(L);
	return 1;
}