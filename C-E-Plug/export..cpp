// C-E-Plug.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "lua_export.h"


extern ExportedFunctions Exported;

extern "C" {
	_declspec(dllexport) BOOL __stdcall CEPlugin_GetVersion(PPluginVersion pv, int sizeofpluginversion)
	{
		pv->version = CESDK_VERSION;
		pv->pluginname = (char *)"my pluging version-1.0"; //exact strings like this are pointers to the string in the dll, so workable
		return TRUE;
	}

	_declspec(dllexport) BOOL __stdcall CEPlugin_InitializePlugin(PExportedFunctions ef, int pluginid)
	{
		//copy the EF list to Exported
		Exported = *ef; //Exported is defined in the .h
		if (Exported.sizeofExportedFunctions != sizeof(Exported)) {
			MessageBoxA(0, "Exported is defined", "mmp", MB_OK);
			return FALSE;
		}
		lua_export();
		return true;
	}
	_declspec(dllexport) BOOL __stdcall CEPlugin_DisablePlugin(void)
	{
		//clean up memory you might have allocated
		//MessageBoxA(0, "disabled plugin", "mmp", MB_OK);

		return TRUE;
	}
}