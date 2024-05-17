#include "server.h"

int main() {
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5555");

    GameLoop::getGameLoopInstance()->Start(subscriber);
    return 0;
}  pv
