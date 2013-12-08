#include "ClientScreenshotManager.h"

CClientScreenshotManager::CClientScreenshotManager()
{
	Reset();
}

CClientScreenshotManager::~CClientScreenshotManager()
{
	Reset();
}

void CClientScreenshotManager::Reset()
{
	UncompressedBuffer.Free();
	OpenGLBuffer.Free();
}

void CClientScreenshotManager::Decompress(BYTE *pCompressedBuffer, DWORD CompressedBufferSize, DecompressedScreenshotInfoStruct* pInfo)
{
	int CompressedHeaderSize = sizeof(CompressedScreenshotInfoStruct);

	CompressedScreenshotInfoStruct CompressionHeader;
	memcpy(&CompressionHeader, pCompressedBuffer, CompressedHeaderSize);

	int w, h, BPP, UncSize;
	w = CompressionHeader.Width;
	h = CompressionHeader.Height;
	BPP = CompressionHeader.BitsPerPixel / 8;
	UncSize = CompressionHeader.UncompressedSize;

	UncompressedBuffer.Allocate(UncSize);
	DWORD CompressedDataSize = CompressedBufferSize - CompressedHeaderSize;
	
	{
		BYTE *pIn  = &pCompressedBuffer[CompressedHeaderSize];
		BYTE *pOut = UncompressedBuffer.GetBuffer();

		// Decompress the data
		int Res = FreeImage_ZLibUncompress(pOut, UncSize, pIn, CompressedDataSize);
		
		// Check for error
		if(Res == 0){
			pInfo->Width   = 0;
			pInfo->Height  = 0;
			pInfo->BPP     = 0;
			pInfo->pBuffer = NULL;
			return;
		}
	}
	
	int NumPixels = w * h;
	int BufSize = NumPixels * BPP;

	if(OpenGLBuffer.GetBufferSize() != (UINT)BufSize)
		OpenGLBuffer.Allocate(BufSize);
	
	// Used to read our unc. buffer data
	int BufIndx = 0;

	// Start decompressing the images blocks
	while(BufIndx < UncSize){

		// Gather information about the current texture part
		CQuadTexInfo TexInfo;
		memcpy(&TexInfo, UncompressedBuffer.GetBuffer(BufIndx), sizeof(TexInfo));
		
		// Update the unc. buffer index
		BufIndx += sizeof(TexInfo);

		// Copy and decode the data, line per line
		for(int CptLines = 0; CptLines < TexInfo.Height; CptLines++){

			DWORD GLIndx = TexInfo.Offset + ((w * BPP) * CptLines);

			// Copy a line of data
			memcpy(OpenGLBuffer.GetBuffer(GLIndx), UncompressedBuffer.GetBuffer(BufIndx), TexInfo.Width * BPP);		

			// Update the unc. buffer index
			BufIndx += TexInfo.Width * BPP;
		}
	}

	pInfo->Width   = w;
	pInfo->Height  = h;
	pInfo->BPP     = BPP;
	pInfo->pBuffer = &OpenGLBuffer;
}