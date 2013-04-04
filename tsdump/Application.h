//
//  Application.h
//  drift
//
//  Created by David Schweinsberg on 2/04/13.
//  Copyright (c) 2013 David Schweinsberg. All rights reserved.
//

#ifndef __drift__Application__
#define __drift__Application__

#include "EventStreamParser.h"

namespace ABC
{
    class Application : public EventStreamParserDelegate
    {
    public:
        int main(int argc, const char *argv[]);

        virtual void updated(EventStreamParser *parser, Service &service);

    private:
        bool parseCommandLine(int argc, const char *argv[], long *deviceNumber, long *port);
    };
}

#endif /* defined(__drift__Application__) */
