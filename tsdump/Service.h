//
//  Service.h
//  tssniff
//
//  Created by David Schweinsberg on 10/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#ifndef __tssniff__Service__
#define __tssniff__Service__

#include "Event.h"

namespace ABC
{
//    class Event
//    {
//    public:
//        Event(int eventId = 0);
//        
//        int getId() const;
//
//    private:
//        int _id;
//    };

//    class Event;

	class Service
    {
    public:
        Service(int serviceId = 0);

        Service(const Service &other);

        bool operator==(const Service &other) const;
        
        int getId() const;
        
        const Event &getPresentEvent() const;

        Event &getPresentEvent();

        const Event &getFollowingEvent() const;

        Event &getFollowingEvent();

        bool isComplete() const;
        
    private:
        int _id;
        Event _presentEvent;
        Event _followingEvent;
    };
    
} //namespace ABC
#endif /* defined(__tssniff__Service__) */
