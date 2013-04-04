//
//  StreamParser.h
//  tssniff
//
//  Created by David Schweinsberg on 3/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#ifndef __tssniff__StreamParser__
#define __tssniff__StreamParser__

#include "Exception.h"

namespace ABC
{

class Reader;
    
class StreamParser
{
public:
    StreamParser();
    
    virtual ~StreamParser();

    /// Initialiser
    /// \param reader The Reader from which the raw data will be read.
    virtual void initialise(Reader *reader) throw(Exception);
    
    /// Finaliser
    virtual void finalise() throw();
    
    Position findNextStartCode(UInt8 &startCode);

    bool sync();
    
    bool readNextPacket(UInt8 *buffer);
    
    void handlePacket(const UInt8 *buffer);
    
    virtual void handleEventInformationSection(const UInt8 *buffer) = 0;
    virtual void handleTimeDateSection(const UInt8 *buffer) = 0;

private:
    Reader *_reader;
    UInt8 _eisBuffer[4096];
    UInt32 _eisBufferLen;
    UInt8 _tdtBuffer[8];
};

} //namespace ABC
#endif /* defined(__tssniff__StreamParser__) */
