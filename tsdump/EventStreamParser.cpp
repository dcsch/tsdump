//
//  EventStreamParser.cpp
//  tssniff
//
//  Created by David Schweinsberg on 10/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#include "common.h"
#include "EventStreamParser.h"
#include "EventInformationSection.h"

namespace ABC
{
    EventStreamParser::EventStreamParser(EventStreamParserDelegate *delegate) : StreamParser(), _delegate(delegate)
    {
    }
    
    EventStreamParser::~EventStreamParser()
    {
    }

    void EventStreamParser::handleEventInformationSection(const UInt8 *buffer)
    {
        EventInformationSection eis(buffer);
        
        if (eis.getTableId() == 0x4e)
        {
            //eis.dump();
            
            UInt16 serviceId = eis.getServiceId();
            
            if (_partialServices.count(serviceId) == 0)
            {
                // We don't have this presently, so check if this is
                // section 0 - if not, then skip it
                if (eis.getSectionNumber() != 0)
                    return;

                _partialServices[serviceId] = Service(serviceId);
                //wprintf(L"Service: %d\n", serviceId);
            }
            
            Service &service = _partialServices[eis.getServiceId()];
            
            if (eis.getSectionNumber() == 0)
            {
                // Present Event
//                int eventId = eis.getEventId(0);
//                if (eventId != service.getPresentEvent().getId())
                {
                    service.getPresentEvent() = Event(eis.getEventId(0),
                                                      eis.getStartTime(0),
                                                      eis.getDuration(0));
                }
            }
            else if (eis.getSectionNumber() == 1)
            {
                // Following Event
//                int eventId = eis.getEventId(0);
//                if (eventId != service.getPresentEvent().getId())
                {
                    service.getFollowingEvent() = Event(eis.getEventId(0),
                                                        eis.getStartTime(0),
                                                        eis.getDuration(0));
                }

                // If we have both present and following, put it into the map
                if (service.isComplete())
                {
                    // Check that it differs from what we already have
                    Service &currentService = _services[serviceId];
                    if (currentService == service)
                    {
                        // NOP
                    }
                    else
                    {
                        _services[serviceId] = service;
                        if (_delegate)
                            _delegate->updated(this, service);
                    }

                    // Remove it from the partials
                    std::map<int, Service>::iterator pos = _partialServices.find(serviceId);
                    _partialServices.erase(pos);
                }
            }
        }
    }

    const std::map<int, Service> &EventStreamParser::getServices() const
    {
        return _services;
    }
    
} //namespace ABC
