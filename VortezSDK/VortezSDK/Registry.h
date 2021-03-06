#ifndef _CREGISTRY_H_
#define _CREGISTRY_H_
#ifdef __cplusplus

#include "Windows.h"
#include "Stdio.h"

#include "Preproc.h"

#ifdef COMPILE_FOR_BORLAND
// Create an abstract class of the object to export
class ARegistry {
public:
	virtual void _INTERNAL_LINKAGE CreateKey(HKEY MainKey, LPCSTR SubKey);
	virtual void _INTERNAL_LINKAGE DeleteKey(HKEY MainKey, LPCSTR SubKey);
	virtual bool _INTERNAL_LINKAGE DoesKeyExist(HKEY MainKey, LPCSTR SubKey);
	
	virtual bool _INTERNAL_LINKAGE GetValue(HKEY MainKey, LPCSTR SubKey, LPCSTR Value, DWORD Type, BYTE *pBuffer, DWORD *pBufferSize);
	virtual UINT _INTERNAL_LINKAGE GetValueType(HKEY MainKey, LPCSTR SubKey, LPCSTR Value);
	virtual void _INTERNAL_LINKAGE SetValue(HKEY MainKey, LPCSTR SubKey, LPCSTR Value, DWORD Type, BYTE *pBuffer, DWORD BufferSize);
	virtual void _INTERNAL_LINKAGE DeleteValue(HKEY MainKey, LPCSTR SubKey, LPCSTR Value);
	virtual bool _INTERNAL_LINKAGE DoesValueExist(HKEY MainKey, LPCSTR SubKey, LPCSTR Value);

	virtual void _INTERNAL_LINKAGE Free() = 0;
};
#endif


#ifdef COMPILE_FOR_BORLAND
class CRegistry  : public ARegistry {
#else
class _EXP_FUNC CRegistry {
#endif
private:
#ifndef RAD_STUDIO_XE
	bool OpenKey(HKEY MainKey, LPCSTR SubKey, PHKEY pKey);
#else
	bool OpenKey(HKEY MainKey, LPCSTR SubKey, HKEY *pKey);
#endif
	void CloseKey(HKEY hKey);
public:
	void _INTERNAL_LINKAGE CreateKey(HKEY MainKey, LPCSTR SubKey);
	void _INTERNAL_LINKAGE DeleteKey(HKEY MainKey, LPCSTR SubKey);
	bool _INTERNAL_LINKAGE DoesKeyExist(HKEY MainKey, LPCSTR SubKey);
	
	bool _INTERNAL_LINKAGE GetValue(HKEY MainKey, LPCSTR SubKey, LPCSTR Value, DWORD Type, void *pBuffer, DWORD *pBufferSize);
	UINT _INTERNAL_LINKAGE GetValueType(HKEY MainKey, LPCSTR SubKey, LPCSTR Value);
	void _INTERNAL_LINKAGE SetValue(HKEY MainKey, LPCSTR SubKey, LPCSTR Value, DWORD Type, void *pBuffer, DWORD BufferSize);
	void _INTERNAL_LINKAGE DeleteValue(HKEY MainKey, LPCSTR SubKey, LPCSTR Value);
	bool _INTERNAL_LINKAGE DoesValueExist(HKEY MainKey, LPCSTR SubKey, LPCSTR Value);
	
	//GetKeysNames(HKEY MainKey, LPCSTR SubKey); <-- besoin de qqch comme tstringlist
	//GetValueNames(HKEY MainKey, LPCSTR SubKey);<-- besoin de qqch comme tstringlist

	bool LoadInteger(HKEY MainKey, LPCSTR SubKey, LPCSTR Value, void *pBuffer, DWORD DefaultValue = 0);
	void SaveInteger(HKEY MainKey, LPCSTR SubKey, LPCSTR Value, void *pBuffer);
	bool LoadString(HKEY MainKey, LPCSTR SubKey, LPCSTR Value, void *pBuffer, int BufSize, char *pDefaultValue = NULL);
	void SaveString(HKEY MainKey, LPCSTR SubKey, LPCSTR Value, void *pBuffer, int BufSize);

#ifdef COMPILE_FOR_BORLAND
	void _INTERNAL_LINKAGE Free(){if(this) delete this;}
#endif
};

#endif
#endif //--_CREGISTRY_H_
