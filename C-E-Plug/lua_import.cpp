#include "stdafx.h"
#include "lua_import.h"

extern ExportedFunctions Exported;

SHORT readSmallInteger(INT baseAddress)
{
	lua_State *L = Exported.GetLuaState();
	lua_getglobal(L, "readSmallInteger");// 
	lua_pushinteger(L, baseAddress);// 
	lua_pcall(L, 1, 1, 0);
	return (short)lua_tonumber(L, -1);
}

INT readInteger(INT baseAddress)
{
	lua_State *L = Exported.GetLuaState();
	lua_getglobal(L, "readInteger");
	lua_pushinteger(L, baseAddress);
	lua_pcall(L, 1, 1, 0);
	return (int)lua_tonumber(L, -1);
}

FLOAT readFloat(INT baseAddress)
{
	lua_State *L = Exported.GetLuaState();
	lua_getglobal(L, "readFloat");
	lua_pushinteger(L, baseAddress);
	lua_pcall(L, 1, 1, 0);
	return (float)lua_tonumber(L, -1);
}

double readDouble(INT baseAddress)
{
	lua_State *L = Exported.GetLuaState();
	lua_getglobal(L, "readDouble");
	lua_pushinteger(L, baseAddress);
	lua_pcall(L, 1, 1, 0);
	return (double)lua_tonumber(L, -1);
}