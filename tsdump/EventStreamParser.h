//
//  EventStreamParser.h
//  tssniff
//
//  Created by David Schweinsberg on 10/10/12.
//  Copyright (c) 2012 ABC. All rights reserved.
//

#ifndef __tssniff__EventStreamParser__
#define __tssniff__EventStreamParser__

#include "StreamParser.h"
#include "Service.h"

namespace ABC
{
    class EventStreamParserDelegate;

    class EventStreamParser : public StreamParser
    {
    public:
        EventStreamParser(EventStreamParserDelegate *delegate);
        
        virtual ~EventStreamParser();
        
//        /// Initialiser
//        /// \param reader The Reader from which the raw data will be read.
//        virtual void initialise(Reader *reader) throw(Exception);
//        
//        /// Finaliser
//        virtual void finalise() throw();
        
        virtual void handleEventInformationSection(const UInt8 *buffer);
        virtual void handleTimeDateSection(const UInt8 *buffer);

        const std::map<int, Service> &getServices() const;
        
    private:
        EventStreamParserDelegate *_delegate;
        std::map<int, Service> _services;
        std::map<int, Service> _partialServices;
        long long _streamTimeDateUTC;
    };

    class EventStreamParserDelegate
    {
    public:
        virtual void updated(EventStreamParser *parser, Service &service, long long timeDateUTC) = 0;
    };
    
} //namespace ABC
#endif /* defined(__tssniff__EventStreamParser__) */
