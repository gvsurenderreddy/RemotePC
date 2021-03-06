#pragma once
//----------------------------------------------------------------------//
#include "Windows.h"
#include "stdio.h"
//----------------------------------------------------------------------//
#include "VortezSDK.h"
//----------------------------------------------------------------------//
#include "..\\Preproc.h"
//----------------------------------------------------------------------//

#define NETSTATS_TEXT_BUF_SIZE  1024

struct EXP_FUNC CNetStatsStruct {
	__int64 d,ld,u,lu;
	float ad, au;

	char szTotalDownloaded[NETSTATS_TEXT_BUF_SIZE];
	char szTotalUploaded[NETSTATS_TEXT_BUF_SIZE];
	char szAverageDownloadKBPS[NETSTATS_TEXT_BUF_SIZE];
	char szAverageUploadKBPS[NETSTATS_TEXT_BUF_SIZE];
};

class EXP_FUNC CNetStats {
public:
	CNetStats();
private:
	bool    IsPerfCounterAvailable;
	float   TimeScale;
	__int64 PerfCounterFrequency;

	__int64 LastTime;
	__int64 CurrentTime;
	float   fElapsedTime;

	//CLock StatsLock;
	CNetStatsStruct Stats;
	float Tick();
public:
	void Reset();
	
	void IncNumBytesDownloaded(__int64 NumBytesDownloaded);
	void IncNumBytesUploaded(__int64 NumBytesUploaded);

	void UpdateStats();
	
	char* GetTotalDownloaded(){return &Stats.szTotalDownloaded[0];}
	char* GetTotalUploaded(){return &Stats.szTotalUploaded[0];}
	char* GetAverageDownloadKBPS(){return &Stats.szAverageDownloadKBPS[0];}
	char* GetAverageUploadKBPS(){return &Stats.szAverageUploadKBPS[0];}
};
