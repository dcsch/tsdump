#ifndef ABC_READER_H__
#define ABC_READER_H__ 1

#include "IOBase.h"

namespace ABC
{

/**
 * \author David Schweinsberg
 */
class Reader : public IOBase
{
public:

	Reader()
	{
	}

	virtual ~Reader()
	{
	}

	/**
	 * Reads from the stream.
	 * \param buffer A pointer to a buffer to read data into.
	 * \param length The amount of data to read.
	 * \return The actual number of bytes read.
	 */
	virtual UInt64 read(UInt8* buffer, UInt64 length) = 0;
};

} //namespace ABC
#endif //ABC_READER_H__
