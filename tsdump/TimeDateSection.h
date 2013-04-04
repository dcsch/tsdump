//
//  TimeDateSection.h
//  tsdump
//
//  Created by David Schweinsberg on 3/04/13.
//  Copyright (c) 2013 ABC. All rights reserved.
//

#ifndef __tsdump__TimeDateSection__
#define __tsdump__TimeDateSection__

namespace ABC
{
    class TimeDateSection
    {
    public:
        TimeDateSection(const UInt8 *data);

        UInt8 getTableId() const;

        UInt16 getSectionLength() const;

        UInt64 getUTCTime() const;

        void dump() const;

    private:
        const UInt8 *_data;
    };
    
} //namespace ABC
#endif /* defined(__tsdump__TimeDateSection__) */
