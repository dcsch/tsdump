//
//  Application.cpp
//  drift
//
//  Created by David Schweinsberg on 2/04/13.
//  Copyright (c) 2013 David Schweinsberg. All rights reserved.
//

#include "common.h"
#include "Application.h"
#include "EventStreamParser.h"
#include "conversion.h"
#include <stdlib.h>
#include <string.h>

#ifdef FILE_TEST
#include "FileReader.h"
#else
#include "DektecReader.h"
#endif //FILE_TEST

namespace ABC
{
    bool Application::parseCommandLine(int argc, const char *argv[], long *deviceNumber, long *port)
    {
        if (argc != 3)
            return false;

        if (isdigit(*argv[1]))
            *deviceNumber = strtol(argv[1], NULL, 10);
        else
            return false;

        if (isdigit(*argv[2]))
            *port = strtol(argv[2], NULL, 10);
        else
            return false;

        return true;
    }

    int Application::main(int argc, const char *argv[])
    {
#ifdef FILE_TEST
        FileReader *reader = new FileReader;
        //reader->open(L"/Users/david/Documents/ABC/IRD Main 1710 18 Sep.ts");
        reader->open(L"/Users/david/Documents/RecordedTs.ts");
#else
        long deviceNumber;
        long port;

        if (!parseCommandLine(argc, argv, &deviceNumber, &port))
            return -1;

        DektecReader *reader = 0;
        try
        {
            reader = new DektecReader;
            reader->open(deviceNumber, port);
        }
        catch (Exception &e)
        {
            std::wstring str = e.getExtra();
            wprintf(L"ERROR: 0x%x %ls\n", e.getCode(), str.c_str());
            return e.getCode();
        }
#endif //FILE_TEST

        EventStreamParser *parser = new EventStreamParser(this);
        parser->initialise(reader);
        parser->sync();

        UInt8 buffer[188];

        while (true)
        {
            if (parser->readNextPacket(buffer) == false)
                break;

            parser->handlePacket(buffer);
        }
        
        parser->finalise();
        reader->close();
        
        delete parser;
        delete reader;
        
        return 0;
    }

    void Application::updated(EventStreamParser *parser, Service &service, long long timeDateUTC)
    {
        const int TZ_PLUS_11 = 39600;
        time_t presentStartTime = timeFromMJDUTC(service.getPresentEvent().getStartTime()) + TZ_PLUS_11;
        time_t followingStartTime = timeFromMJDUTC(service.getFollowingEvent().getStartTime()) + TZ_PLUS_11;
        time_t updatedTime = timeFromMJDUTC(timeDateUTC);

        char present[256];
        strncpy(present, asctime(gmtime(&presentStartTime)), 256);
        char *pos = strchr(present, '\n');
        if (pos)
            *pos = 0;

        char following[256];
        strncpy(following, asctime(gmtime(&followingStartTime)), 256);
        pos = strchr(following, '\n');
        if (pos)
            *pos = 0;

        char updated[256];
        strncpy(updated, asctime(gmtime(&updatedTime)), 256);
        pos = strchr(updated, '\n');
        if (pos)
            *pos = 0;

        wprintf(L"%d: present event_id: %d - %s, following event_id: %d - %s, updated: %s\n",
                service.getId(),
                service.getPresentEvent().getId(),
                present,
                service.getFollowingEvent().getId(),
                following,
                updated);
    }
}
