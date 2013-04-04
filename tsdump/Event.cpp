//
//  Event.cpp
//  tssniff
//
//  Created by David Schweinsberg on 10/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#include "Event.h"
#include <memory.h>

namespace ABC
{
    Event::Event(int eventId, long long startTime, int duration) :
    _id(eventId),
    _startTime(startTime),
    _duration(duration)
    {
    }

    bool Event::operator==(const Event &other) const
    {
        return _id == other._id;
    }

    int Event::getId() const
    {
        return _id;
    }

    long long Event::getStartTime() const
    {
        return _startTime;
    }

    int Event::getDuration() const
    {
        return _duration;
    }

    time_t Event::getStartTimeTime()
    {
        struct tm tm;
        memset(&tm, 0, sizeof(struct tm));

        // Convert MJD into YMD
        double mjd = (double)(_startTime >> 24);
        int y = (int)((mjd - 15078.2) / 365.25);
        int m = (int)((mjd - 14956.1 - int(y * 365.25)) / 30.6001);
        tm.tm_mday = (int)(mjd - 14956 - int(y * 365.25) - int(m * 30.6001));
        int k;
        if (m == 14 || m == 15)
            k = 1;
        else
            k = 0;
        tm.tm_year = y + k;
        tm.tm_mon = (m - 1 - k * 12) - 1;

        // Convert BCD encoded time
        tm.tm_hour = 10 * ((_startTime >> 20) & 15) + ((_startTime >> 16) & 15);
        tm.tm_min = 10 * ((_startTime >> 12) & 15) + ((_startTime >> 8) & 15);
        tm.tm_sec = 10 * ((_startTime >> 4) & 15) + (_startTime & 15);

        return timegm(&tm);
    }

} //namespace ABC
