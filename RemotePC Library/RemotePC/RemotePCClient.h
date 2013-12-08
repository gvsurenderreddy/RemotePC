#pragma once
//----------------------------------------------------------------------//
#define WIN32_LEAN_AND_MEAN 
#define VC_LEANMEAN         
//----------------------------------------------------------------------//
#include "Windows.h"
#include "stdio.h"
//----------------------------------------------------------------------//
#include "RemotePC.h"
#include "ClientScreenshotManager.h"
#include "OpenGL.h"
//----------------------------------------------------------------------//

class CRemotePCClient : public CRemotePC, public IRemotePCClient {
public:
	CRemotePCClient();
	~CRemotePCClient();
private:
	HWND hRendererWnd;
	COpenGL OpenGL;
	CClientScreenshotManager ScreenshotManager;
public:
	COpenGL* GetOpenGL(){return &OpenGL;}

	void Reset();
	void ProcessRemotePCMessages(MsgHeaderStruct *pMsgHeader, BYTE *pMsgData);

	void SetRendererWnd(HWND h);
	bool InitOpenGL();
	void ShutdownOpenGL();
	void RenderTexture();

	void SendLoginRequest(char *pUserName, char *pPassword);
	void OnLoginResult(LoginResultStruct* pLoginResult);
	
	void SendScreenshotRequest();
	void OnScreenshotMsg(MsgHeaderStruct *pMsgHeader, BYTE *pMsgData);

	void SendMouseMsg();
	void SendKeyboardMsg();
};