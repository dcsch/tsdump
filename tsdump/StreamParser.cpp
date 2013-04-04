//
//  StreamParser.cpp
//  tssniff
//
//  Created by David Schweinsberg on 3/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#include "common.h"
#include "StreamParser.h"
#include "Reader.h"
#include "TransportPacket.h"
#include "EventInformationSection.h"
#include "TimeDateSection.h"

#define BUFFER_LENGTH 188
#define SYNC_BYTE 0x47

namespace ABC
{
    StreamParser::StreamParser() : _reader(0)
    {
    }
    
    StreamParser::~StreamParser()
    {
    }
    
    void StreamParser::initialise(Reader *reader) throw(Exception)
    {
        _reader = reader;
    }
    
    void StreamParser::finalise() throw()
    {
    }

    Position StreamParser::findNextStartCode(UInt8 &startCode)
    {
        UInt8 byte;
        bool nextByteIsStartCode = false;
        int zeroCount = 0;
        
        while (true)
        {
            _reader->read(&byte, 1);

            if (nextByteIsStartCode)
            {
                startCode = byte;
                return _reader->getPosition() - 3;
            }
            
            if (zeroCount == 2 && byte == 1)
                nextByteIsStartCode = true;
            
            if (byte == 0)
                ++zeroCount;
            else
                zeroCount = 0;
        }
        return -1;
    }

    bool StreamParser::sync()
    {
        int offsets[2 * BUFFER_LENGTH];
        int offsetCount = 0;
        for (int i = 0; i < 2 * BUFFER_LENGTH; ++i)
        {
            UInt8 byte;
            _reader->read(&byte, 1);
            if (byte == SYNC_BYTE)
            {
                offsets[offsetCount++] = i;
                
                // Look through the offsets to see if we have an alignment with the sync byte
                for (int n = offsetCount - 1; n >= 0; --n)
                {
                    if (offsets[n] == i - BUFFER_LENGTH)
                    {
                        // We have sync - throw away the rest of this packet
                        UInt8 buffer[BUFFER_LENGTH];
                        _reader->read(buffer, BUFFER_LENGTH - 1);
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    bool StreamParser::readNextPacket(UInt8 *buffer)
    {
        _reader->read(buffer, BUFFER_LENGTH);
        return buffer[0] == SYNC_BYTE;
    }

    void StreamParser::handlePacket(const UInt8 *buffer)
    {
        TransportPacket packet(buffer);
//        wprintf(L"PID: 0x%04x   pusi: %d, afc: %d, cc: %d\n",
//                packet.getPID(),
//                packet.getPayloadUnitStartIndicator(),
//                packet.getAdaptationFieldControl(),
//                packet.getContinuityCounter());

//        if (packet.getPID() == 0)
//            wprintf(L"Found PAT\n");
//        else if (packet.getPID() == 1)
//            wprintf(L"Found CAT\n");
//        else if (packet.getPID() == 0x10)
//            wprintf(L"Found NIT\n");
//        else if (packet.getPID() == 0x12)

        if (packet.getPID() == 0x12)
        {
            // EIT, ST, CIT (TS 102 323 [13])

            UInt32 len;
            const UInt8 *data = packet.getPayloadData(len);

            if (packet.getPayloadUnitStartIndicator() == 1)
            {
                UInt8 offset = data[0];
                
                if (len < 4096)
                {
                    _eisBufferLen = len - 1;
                    memcpy(_eisBuffer, data + offset + 1, _eisBufferLen);
                }
            }
            else
            {
                UInt32 copyLen = std::min(len, 4096 - _eisBufferLen);
                memcpy(_eisBuffer + _eisBufferLen, data, copyLen);
                _eisBufferLen += copyLen;
            }
            
            EventInformationSection eis(_eisBuffer);
            if (_eisBufferLen >= eis.getSectionLength())
                handleEventInformationSection(_eisBuffer);
        }
        else if (packet.getPID() == 0x13)
        {
            // RST, ST

            wprintf(L"Found RST\n");
        }
        else if (packet.getPID() == 0x14)
        {
            // TDT, TOT, ST

            UInt32 len;
            const UInt8 *data = packet.getPayloadData(len);

            if (packet.getPayloadUnitStartIndicator() == 1)
            {
                UInt8 offset = data[0];

                if (len < 4096)
                {
                    memcpy(_tdtBuffer, data + offset + 1, 8);
                }
            }

            TimeDateSection timeDateSection(_tdtBuffer);
            wprintf(L"TDT - UTC: %llX\n", timeDateSection.getUTCTime());
        }
    }

} //namespace ABC
