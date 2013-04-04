//
//  TransportPacket.cpp
//  tssniff
//
//  Created by David Schweinsberg on 4/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#include "common.h"
#include "TransportPacket.h"
#include "conversion.h"

namespace ABC
{
    TransportPacket::TransportPacket(const UInt8 *data) : _data(data)
    {
    }

    UInt8 TransportPacket::getSyncByte() const
    {
        return _data[0];
    }
    
    UInt8 TransportPacket::getTransportErrorIndicator() const
    {
        return (_data[1] >> 7) & 0x01;
    }
    
    UInt8 TransportPacket::getPayloadUnitStartIndicator() const
    {
        return (_data[1] >> 6) & 0x01;
    }
    
    UInt8 TransportPacket::getTransportPriority() const
    {
        return (_data[1] >> 5) & 0x01;
    }

    UInt16 TransportPacket::getPID() const
    {
        UInt16 pid;
        unpack(&pid, _data + 1, 2);
        return pid & 0x1fff;
    }

    UInt8 TransportPacket::getTransportScramblingControl() const
    {
        return (_data[3] >> 6) & 0x03;
    }
    
    UInt8 TransportPacket::getAdaptationFieldControl() const
    {
        return (_data[3] >> 4) & 0x03;
    }
    
    UInt8 TransportPacket::getContinuityCounter() const
    {
        return _data[3] & 0x0f;
    }

    const UInt8 *TransportPacket::getPayloadData(UInt32 &length) const
    {
        if (getAdaptationFieldControl() == 1)
        {
            length = 188 - 4;
            return _data + 4;
        }
        else
        {
            // TODO Handle adaption field
            length = 0;
            return 0;
        }
    }
    
} //namespace ABC
