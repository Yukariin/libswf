#ifndef LIBSWF_SWF_H
#define LIBSWF_SWF_H


#include <stdint.h>
#include <vector>

#include "Tag.h"
#include "SwfCompression.h"
#include "SwfBaseTypes.h"
#include "RECT.h"
#include "TagStub.h"

using namespace std;

class Swf {
public:
	/*
	 * SWF file compression
	 */
	SwfCompression compression = SwfCompression::NONE;

	/*
	 * Flash version
	 */
	UI8 version;

	/*
	 * File length (including header)
	 * For uncompressed SWF == file size
	 * For compressed SWF == total length after decompression
	 */
	UI32 fileLength;

	/*
	 * Size of SWF frame
	 */
	RECT frameSize;

	/*
	 * Frame delay in fixed number of frames per second
	 */
	UI16 frameRate;

	/*
	 * Total number of frames in file
	 */
	UI16 frameCount;

	/*
	 * Series of tagged data blocks
	 */
	vector<Tag> tags;


	/*
	 * Empty SWF
	 */
	Swf();

	/*
	 * SWF from file
	 */
	Swf(vector<uint8_t > in);

	//void saveTo();

private:
	static void decompress(vector<uint8_t > in, vector<uint8_t>& out);
	Tag* readTag(DataStream* ds);
	static Tag* resolveTag(TagStub* t);
	void readTagList(DataStream* ds);
};


#endif //LIBSWF_SWF_H
