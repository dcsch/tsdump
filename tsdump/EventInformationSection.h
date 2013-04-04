//
//  EventInformationSection.h
//  tssniff
//
//  Created by David Schweinsberg on 4/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#ifndef __tssniff__EventInformationSection__
#define __tssniff__EventInformationSection__

namespace ABC
{
    class EventInformationSection
    {
    public:
        EventInformationSection(const UInt8 *data);
        
        UInt8 getTableId() const;
        
        UInt16 getSectionLength() const;
        
        UInt16 getServiceId() const;

        UInt8 getVersionNumber() const;

        UInt8 getCurrentNextIndicator() const;

        UInt8 getSectionNumber() const;

        UInt8 getLastSectionNumber() const;

        UInt16 getTransportStreamId() const;
        
        UInt16 getOriginalNetworkId() const;

        UInt8 getSegmentLastSectionNumber() const;

        UInt8 getLastTableId() const;

        int getEventCount() const;
        
        UInt16 getEventId(int index) const;

        UInt64 getStartTime(int index) const;

        UInt32 getDuration(int index) const;

        UInt8 getRunningStatus(int index) const;

        UInt16 getDescriptorsLoopLength(int index) const;
        
        const UInt8 *getDescriptorData(int index, int descriptorIndex, UInt8 &length) const;
        
        void dump() const;
        
    private:
        const UInt8 *_data;
        
        int getEventOffset(int index) const;
    };
    
} //namespace ABC
#endif /* defined(__tssniff__EventInformationSection__) */
