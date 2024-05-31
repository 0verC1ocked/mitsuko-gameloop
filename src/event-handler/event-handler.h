#pragma once
#include "../../lib/payloadbuilder/src/proto/payload.pb.h"
#include "../../lib/payloadbuilder/inc/payload-builder.h"
class EventHandler {
    private:
        EventHandler();
        static EventHandler* eHInstance;
    public:
        static EventHandler* getEventHandlerInstance() noexcept;
        ~EventHandler();

        bool handleEvent(PayloadBuilder &pb, PAYLOAD::Payload* payload);
};
