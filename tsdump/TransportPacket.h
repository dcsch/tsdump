//
//  TransportPacket.h
//  tssniff
//
//  Created by David Schweinsberg on 4/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#ifndef __tssniff__TransportPacket__
#define __tssniff__TransportPacket__

namespace ABC
{
    class TransportPacket
    {
    public:
        TransportPacket(const UInt8 *data);
        
        UInt8 getSyncByte() const;
        
        UInt8 getTransportErrorIndicator() const;
        
        UInt8 getPayloadUnitStartIndicator() const;
        
        UInt8 getTransportPriority() const;
        
        UInt16 getPID() const;
        
        UInt8 getTransportScramblingControl() const;
        
        UInt8 getAdaptationFieldControl() const;

        UInt8 getContinuityCounter() const;
        
        const UInt8 *getPayloadData(UInt32 &length) const;
        
    private:
        const UInt8 *_data;
    };
    
} //namespace ABC
#endif /* defined(__tssniff__TransportPacket__) */
