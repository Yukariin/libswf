#include "_DataStream.h"

#include <sstream>

_DataStream::_DataStream()
{
    dev = nullptr;
    owndev = false;
    byteorder = BigEndian;
    status = Ok;
}

_DataStream::_DataStream(iostream* d)
{
    dev = d;
    owndev = false;
    byteorder = BigEndian;
    status = Ok;
}

_DataStream::~_DataStream()
{
    if (owndev)
        delete dev;
}

int8_t _DataStream::readInt8()
{
    int8_t i = 0;
    char c;
    if (readBlock(&c, 1) == 1)
        i = c;
    return i;
}

short _DataStream::readInt16()
{
    short i = 0;
    if (readBlock(reinterpret_cast<char *>(&i), 2) != 2)
        i = 0;
    return i;
}

int _DataStream::readInt32()
{
    int i = 0;
    if (readBlock(reinterpret_cast<char *>(&i), 4) != 4)
        i = 0;
    return i;
}

long long _DataStream::readInt64()
{
    long long i = 0;
    if (readBlock(reinterpret_cast<char *>(&i), 8) != 8)
        i = 0;
    return i;
}

float _DataStream::readFloat()
{
    float i = 0.0f;
    if (readBlock(reinterpret_cast<char *>(&i), 4) != 4)
        i = 0.0f;
    return i;
}

double _DataStream::readDouble()
{
    double i = 0.0;
    if (readBlock(reinterpret_cast<char *>(&i), 8) != 8)
        i = 0.0;
    return i;
}

string _DataStream::readString()
{
    ostringstream s;
    char c;
    while (readBlock(&c, 1))
    {
        if (c == 0)
            break;
        s << c;
    }
    return s.str();
}

string _DataStream::readString(int len)
{
    ostringstream s;
    char c;
    for (int i = 0; i < len; i++)
    {
        readBlock(&c, 1);
        s << c;
    }
    return s.str();
}

int _DataStream::readBlock(char* data, int len)
{
    if (status != Ok)
        return -1;
    
    if (!dev->read(data, len))
        status = ReadPastEnd;
    return len;
}
