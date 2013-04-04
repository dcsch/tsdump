//
//  TimeDateSection.cpp
//  tsdump
//
//  Created by David Schweinsberg on 3/04/13.
//  Copyright (c) 2013 ABC. All rights reserved.
//

#include "common.h"
#include "TimeDateSection.h"
#include "conversion.h"

namespace ABC
{
    TimeDateSection::TimeDateSection(const UInt8 *data) : _data(data)
    {
    }

    UInt8 TimeDateSection::getTableId() const
    {
        return _data[0];
    }

    UInt16 TimeDateSection::getSectionLength() const
    {
        UInt16 len;
        unpack(&len, _data + 1, 2);
        return len & 0x0fff;
    }

    UInt64 TimeDateSection::getUTCTime() const
    {
        const UInt8 *data = _data + 3;
        return ((UInt64)data[0] << 32) | ((UInt64)data[1] << 24) | ((UInt64)data[2] << 16) | ((UInt64)data[3] << 8) | data[4];
    }

    void TimeDateSection::dump() const
    {
//        wprintf(L"EIS table_id: 0x%x\n", getTableId());
//        wprintf(L"    section_length: %d\n", getSectionLength());
//        wprintf(L"    service_id: %d\n", getServiceId());
//        wprintf(L"    version_number: %d\n", getVersionNumber());
//        wprintf(L"    current_next_indicator: %d\n", getCurrentNextIndicator());
//        wprintf(L"    section_number: %d\n", getSectionNumber());
//        wprintf(L"    last_section_number: %d\n", getLastSectionNumber());
//        wprintf(L"    transport_stream_id: %d\n", getTransportStreamId());
//        wprintf(L"    original_network_id: %d\n", getOriginalNetworkId());
//        wprintf(L"    segment_last_section_number: %d\n", getSegmentLastSectionNumber());
//        wprintf(L"    last_table_id: 0x%x\n", getLastTableId());
//
//        for (int i = 0; ; ++i)
//        {
//            UInt16 eventId = getEventId(i);
//            if (eventId == 0)
//                break;
//
//            wprintf(L"\n    event_id: %d\n", eventId);
//            wprintf(L"    start_time: 0x%llx\n", getStartTime(i));
//            wprintf(L"    duration: 0x%06x\n", getDuration(i));
//            wprintf(L"    running_status: %d\n", getRunningStatus(i));
//            wprintf(L"    descriptors_loop_length: %d\n", getDescriptorsLoopLength(i));
//
//            for (int j = 0; ; ++j)
//            {
//                UInt8 descriptorLen;
//                const UInt8 *descriptorData = getDescriptorData(i, j, descriptorLen);
//                if (descriptorLen == 0)
//                    break;
//
//                wprintf(L"\n    descriptor_tag: 0x%x\n", descriptorData[0]);
//                wprintf(L"    descriptor_length: 0x%x\n", descriptorData[1]);
//            }
//        }
    }
    
} //namespace ABC
