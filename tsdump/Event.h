//
//  Event.h
//  tssniff
//
//  Created by David Schweinsberg on 10/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#ifndef __tssniff__Event__
#define __tssniff__Event__

namespace ABC
{
    class Event
    {
    public:
        Event(int eventId = 0, long long startTime = 0, int duration = 0);

        bool operator==(const Event &other) const;

        int getId() const;
        long long getStartTime() const;
        int getDuration() const;

    private:
        int _id;
        long long _startTime;
        int _duration;
    };
    
} //namespace ABC
#endif /* defined(__tssniff__Event__) */
