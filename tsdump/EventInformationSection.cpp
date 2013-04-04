//
//  EventInformationSection.cpp
//  tssniff
//
//  Created by David Schweinsberg on 4/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#include "common.h"
#include "EventInformationSection.h"
#include "conversion.h"

namespace ABC
{
    EventInformationSection::EventInformationSection(const UInt8 *data) : _data(data)
    {
    }
    
    UInt8 EventInformationSection::getTableId() const
    {
        return _data[0];
    }

    UInt16 EventInformationSection::getSectionLength() const
    {
        UInt16 len;
        unpack(&len, _data + 1, 2);
        return len & 0x0fff;
    }

    UInt16 EventInformationSection::getServiceId() const
    {
        UInt16 id;
        unpack(&id, _data + 3, 2);
        return id;
    }
    
    UInt8 EventInformationSection::getVersionNumber() const
    {
        return (_data[5] >> 1) & 0x1f;
    }
    
    UInt8 EventInformationSection::getCurrentNextIndicator() const
    {
        return _data[5] & 0x01;
    }
    
    UInt8 EventInformationSection::getSectionNumber() const
    {
        return _data[6];
    }
    
    UInt8 EventInformationSection::getLastSectionNumber() const
    {
        return _data[7];
    }
    
    UInt16 EventInformationSection::getTransportStreamId() const
    {
        UInt16 id;
        unpack(&id, _data + 8, 2);
        return id;
    }
    
    UInt16 EventInformationSection::getOriginalNetworkId() const
    {
        UInt16 id;
        unpack(&id, _data + 10, 2);
        return id;
    }
    
    UInt8 EventInformationSection::getSegmentLastSectionNumber() const
    {
        return _data[12];
    }
    
    UInt8 EventInformationSection::getLastTableId() const
    {
        return _data[13];
    }

    int EventInformationSection::getEventOffset(int index) const
    {
        // TESTING
        //UInt16 len = getSectionLength();

        int offset = 14;  // Events start 14 bytes into the section
        
        // Actual length of buffer is 3 bytes longer than section_length reports
        for (int i = 0; i < index; ++i)
        {
            const UInt8 *ptr = _data + offset;
            
            if (*ptr == 0xff)
                break;
            
            // What is the total length of the descriptors? Length of event data
            // is this length + 12 bytes
            UInt16 loopLen;
            unpack(&loopLen, ptr + 10, 2);
            loopLen &= 0x0fff;
            offset += loopLen + 12;
        }

        if (offset < getSectionLength() - 1) // section_length + 3 - 4
            return offset;
        else
            return -1;
    }

    UInt16 EventInformationSection::getEventId(int index) const
    {
        int offset = getEventOffset(index);
        if (offset > -1)
        {
            const UInt8 *data = _data + offset;
            UInt16 id;
            unpack(&id, data, 2);
            return id;
        }
        return 0;
    }
    
    UInt64 EventInformationSection::getStartTime(int index) const
    {
        int offset = getEventOffset(index);
        if (offset > -1)
        {
            const UInt8 *data = _data + offset + 2;
            return ((UInt64)data[0] << 32) | ((UInt64)data[1] << 24) | ((UInt64)data[2] << 16) | ((UInt64)data[3] << 8) | data[4];
        }
        return 0;
    }
    
    UInt32 EventInformationSection::getDuration(int index) const
    {
        int offset = getEventOffset(index);
        if (offset > -1)
        {
            const UInt8 *data = _data + offset + 7;
            return ((UInt32)data[0] << 16) | ((UInt32)data[1] << 8) | data[2];
        }
        return 0;
    }
    
    UInt8 EventInformationSection::getRunningStatus(int index) const
    {
        int offset = getEventOffset(index);
        if (offset > -1)
        {
            const UInt8 *data = _data + offset + 10;
            return (data[0] >> 5) & 0x07;
        }
        return 0;
    }
    
    UInt16 EventInformationSection::getDescriptorsLoopLength(int index) const
    {
        int offset = getEventOffset(index);
        if (offset > -1)
        {
            UInt16 loopLen;
            unpack(&loopLen, _data + offset + 10, 2);
            return loopLen & 0x0fff;
        }
        return 0;
    }

    const UInt8 *EventInformationSection::getDescriptorData(int index, int descriptorIndex, UInt8 &length) const
    {
        int offset = getEventOffset(index);
        if (offset > -1)
        {
            UInt16 loopLen;
            unpack(&loopLen, _data + offset + 10, 2);
            loopLen &= 0x0fff;

            int descriptorOffset = 0;
            for (int i = 0; i <= descriptorIndex; ++i)
            {
                const UInt8 *ptr = _data + offset + 12 + descriptorOffset;
                if (i == descriptorIndex)
                {
                    length = ptr[1];
                    return ptr;
                }
                
                descriptorOffset += ptr[1] + 2;
                if (descriptorOffset >= loopLen)
                    break;
            }
        }
        length = 0;
        return 0;
    }

    void EventInformationSection::dump() const
    {
        wprintf(L"EIS table_id: 0x%x\n", getTableId());
        wprintf(L"    section_length: %d\n", getSectionLength());
        wprintf(L"    service_id: %d\n", getServiceId());
        wprintf(L"    version_number: %d\n", getVersionNumber());
        wprintf(L"    current_next_indicator: %d\n", getCurrentNextIndicator());
        wprintf(L"    section_number: %d\n", getSectionNumber());
        wprintf(L"    last_section_number: %d\n", getLastSectionNumber());
        wprintf(L"    transport_stream_id: %d\n", getTransportStreamId());
        wprintf(L"    original_network_id: %d\n", getOriginalNetworkId());
        wprintf(L"    segment_last_section_number: %d\n", getSegmentLastSectionNumber());
        wprintf(L"    last_table_id: 0x%x\n", getLastTableId());
        
        for (int i = 0; ; ++i)
        {
            UInt16 eventId = getEventId(i);
            if (eventId == 0)
                break;
            
            wprintf(L"\n    event_id: %d\n", eventId);
            wprintf(L"    start_time: 0x%llx\n", getStartTime(i));
            wprintf(L"    duration: 0x%06x\n", getDuration(i));
            wprintf(L"    running_status: %d\n", getRunningStatus(i));
            wprintf(L"    descriptors_loop_length: %d\n", getDescriptorsLoopLength(i));
            
            for (int j = 0; ; ++j)
            {
                UInt8 descriptorLen;
                const UInt8 *descriptorData = getDescriptorData(i, j, descriptorLen);
                if (descriptorLen == 0)
                    break;
                
                wprintf(L"\n    descriptor_tag: 0x%x\n", descriptorData[0]);
                wprintf(L"    descriptor_length: 0x%x\n", descriptorData[1]);
            }
        }
    }

} //namespace ABC
