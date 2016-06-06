#include <windows.h>
#include <cstdio>		//needed by OutputDebugString()
#include <math.h>
#include <limits.h>
#include <DirectXPackedVector.h>
#include "avisynth.h"
#include "d3dx9.h"
#include <mutex>

// Converts float-precision RGB data (12-byte per pixel) into YV12 format.
class ConvertFromShader : public GenericVideoFilter {
public:
	ConvertFromShader(PClip _child, int _precision, const char* _format, bool _stack16, IScriptEnvironment* env);
	~ConvertFromShader();
	PVideoFrame __stdcall GetFrame(int n, IScriptEnvironment* env);
	const VideoInfo& __stdcall GetVideoInfo() { return viDst; }
private:
	const int precision;
	const bool stack16;
	int precisionShift;
	int floatBufferPitch;
	int halfFloatBufferPitch;
	const char* format;
	void convShaderToYV24(const byte *src, unsigned char *py, unsigned char *pu, unsigned char *pv,
		int pitch1, int pitch2Y, int pitch2UV, int width, int height, IScriptEnvironment* env);
	void convShaderToRGB(const byte *src, unsigned char *dst, int pitchSrc, int pitchDst, int width, int height, IScriptEnvironment* env);
	void convInt(const byte* rgb, unsigned char* outY, unsigned char* outU, unsigned char* outV);
	void convStack16(const byte* src, unsigned char* outY, unsigned char* outU, unsigned char* outV, unsigned char* outY2, unsigned char* outU2, unsigned char* outV2);
	uint16_t ConvertFromShader::sadd16(uint16_t a, uint16_t b);
	VideoInfo viDst;
};