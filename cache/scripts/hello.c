#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int l_square(lua_State *L) {
	int num = lua_tonumber(L, -1);
	lua_pushnumber(L, num*num);
	return 1;
}

int main() {
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	lua_pushcfunction(L, l_square);
	lua_setglobal(L, "square");
}
