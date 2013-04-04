
#include "DektecReader.h"
#include "errorcodes.h"

namespace ABC
{

static std::wstring name = L"Dektec";

DektecReader::DektecReader() : _buffer(), _bufferReadPtr(0), _device(), _inpChannel()
{
}

DektecReader::~DektecReader()
{
}

void DektecReader::open(int deviceNumber, int port) throw (Exception)
{
    if (_device.AttachToType(2144, deviceNumber) != DTAPI_OK)
        throw Exception(ERROR_InvalidParameter, L"Failed to attach to device");

    if (_device.SetIoConfig(port, DTAPI_IOCONFIG_IODIR, DTAPI_IOCONFIG_INPUT, DTAPI_IOCONFIG_INPUT) != DTAPI_OK)
        throw Exception(ERROR_InvalidParameter, L"Failed to set I/O configuration");

    if (_inpChannel.AttachToPort(&_device, port) != DTAPI_OK)
        throw Exception(ERROR_InvalidParameter, L"Failed to attach to port");

    _inpChannel.SetRxControl(DTAPI_RXCTRL_RCV);
}

void DektecReader::close() throw()
{
    _inpChannel.Detach(0);
    _device.Detach();
}

const std::wstring& DektecReader::getName() const
{
    return name;
}

UInt64 DektecReader::getPosition() const
{
    return 0;
}

UInt64 DektecReader::setPosition(Int64 distance, Origin origin)
{
    return 0;
}

UInt64 DektecReader::getLength() const
{
    return 0;
}

UInt64 DektecReader::read(UInt8 *buffer, UInt64 length)
{
    UInt8 *ptr = buffer;
    while (length)
    {
        int bytesInBuffer = _bufferReadPtr ? DEKTEC_BUFFER_SIZE - (_bufferReadPtr - _buffer) : 0;
        if (bytesInBuffer == 0)
        {
            DTAPI_RESULT result = _inpChannel.Read(_buffer, DEKTEC_BUFFER_SIZE, 1000);
            if (result == DTAPI_OK)
            {
                _bufferReadPtr = _buffer;
                bytesInBuffer = DEKTEC_BUFFER_SIZE;
            }
        }

        int bytesToCopy = std::min(bytesInBuffer, (int)length);
        memcpy(ptr, _bufferReadPtr, bytesToCopy);
        ptr += bytesToCopy;
        _bufferReadPtr += bytesToCopy;
        length -= bytesToCopy;
    }

    return 0;
}

} //namespace ABC
