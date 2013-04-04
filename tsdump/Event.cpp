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

} //namespace ABC
