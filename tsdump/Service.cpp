//
//  Service.cpp
//  tssniff
//
//  Created by David Schweinsberg on 10/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#include "Service.h"
#include "Event.h"

namespace ABC
{
    Service::Service(int serviceId) : _id(serviceId)
    {
    }

    Service::Service(const Service &other) : _id(other._id)
    {
    }

    bool Service::operator==(const Service &other) const
    {
        return (_presentEvent == other.getPresentEvent()) && (_followingEvent == other.getFollowingEvent());
    }

    int Service::getId() const
    {
        return _id;
    }

    const Event &Service::getPresentEvent() const
    {
        return _presentEvent;
    }

    Event &Service::getPresentEvent()
    {
        return _presentEvent;
    }
    
    const Event &Service::getFollowingEvent() const
    {
        return _followingEvent;
    }

    Event &Service::getFollowingEvent()
    {
        return _followingEvent;
    }

    bool Service::isComplete() const
    {
        return (_presentEvent.getId() != 0) && (_followingEvent.getId() != 0);
    }

} //namespace ABC
