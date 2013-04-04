#ifndef ABC_DEKTEC_READER_H__
#define ABC_DEKTEC_READER_H__ 1

#include "common.h"
#include "Reader.h"
#include "Exception.h"
#include "DTAPI.h"

#define DEKTEC_BUFFER_SIZE 4096

namespace ABC
{

class Exception;

/// A concrete implementation of the Reader interface for reading files.
/// \author David Schweinsberg
class DektecReader : public Reader
{
public:
    DektecReader();
    virtual ~DektecReader();

    void open(int deviceNumber, int port) throw (Exception);

    void close() throw();

    /// \return the name of the material being read.
    virtual const std::wstring& getName() const;

    /// \return the absolute position of the reader within a stream.
    virtual UInt64 getPosition() const;

    /// Set the position of the reader within a stream.
    /// \param distance The distance in bytes to move relative to the
    /// Origin parameter.
    /// \param origin An enumeration specifying the relative position to use
    /// when calculating the absolute position to move to.
    /// \return The absolute position moved to within the stream.
    virtual UInt64 setPosition(Int64 distance, Origin origin);

    /// \return the length of the stream.
    virtual UInt64 getLength() const;

    /**
     * Reads from the stream.
     * \param buffer A pointer to a buffer to read data into.
     * \param length The amount of data to read.
     * \return The actual number of bytes read.
     */
    virtual UInt64 read(UInt8 *buffer, UInt64 length);

private:

    char _buffer[DEKTEC_BUFFER_SIZE];
    char *_bufferReadPtr;
    DtDevice _device;
    DtInpChannel _inpChannel;
};

} //namespace ABC
#endif //ABC_DEKTEC_READER_H__
