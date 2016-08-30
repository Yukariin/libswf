#ifndef _DATASTREAM_H
#define _DATASTREAM_H

#include <iostream>

using namespace std;

class _DataStream
{
public:
    enum ByteOrder
    {
        BigEndian,
        LittleEndian
    };
    
    enum Status
    {
        Ok,
        ReadPastEnd,
        ReadCorruptData,
        WriteFailed
    };
    
    _DataStream();
    explicit _DataStream(iostream *d);
    ~_DataStream();
    
    int8_t readInt8();
    short readInt16();
    int readInt32();
    long long readInt64();
    
    float readFloat();
    double readDouble();
    string readString();
    string readString(int len);
    
private:
    iostream *dev;
    bool owndev;
    ByteOrder byteorder;
    Status status;
    
    int readBlock(char *data, int len);
};

#endif // _DATASTREAM_H
