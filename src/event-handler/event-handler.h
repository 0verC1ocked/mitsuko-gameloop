#pragma once
#include "../../lib/arenaallocator/src/proto/payload.pb.h"
#include "../../lib/arenaallocator/inc/arena-allocator.h"
class EventHandler {
    private:
        EventHandler();
        static EventHandler* eHInstance;
    public:
        static EventHandler* getEventHandlerInstance() noexcept;
        ~EventHandler();

        bool handleEvent(ArenaAllocator &allocator, PAYLOAD::Payload* payload);
};
