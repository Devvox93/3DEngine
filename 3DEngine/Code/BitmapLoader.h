#include <Windows.h>
#include <string>



typedef unsigned long DWORD;
typedef unsigned short WORD;


typedef struct {
	int Signature;
	DWORD Size;
	DWORD Reserved;
	DWORD BitsOffset;
} BITMAP_FILEHEADER;


typedef struct {
	DWORD HeaderSize;
	DWORD Width;
	DWORD Height;
	WORD Planes;
	WORD BitCount;
	DWORD Compression;
	DWORD SizeImage;
	DWORD PelsPerMeterX;
	DWORD PelsPerMeterY;
	DWORD ClrUsed;
	DWORD ClrImportant;
	unsigned int numColors;

} BITMAP_HEADER;









class BitmapLoader
{
public:
	BitmapLoader();
	~BitmapLoader();
	bool LoadBMP(char* argFileName);




};
