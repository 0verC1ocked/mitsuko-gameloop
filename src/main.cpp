#include "gameloop/gameloop.h"
#include "server.h"

int main() {
    zmq::context_t sub_context(1);
    GameLoop::getGameLoopInstance()->subscriber = zmq::socket_t(sub_context, ZMQ_SUB);
    GameLoop::getGameLoopInstance()->subscriber.connect("tcp://localhost:5555");

    Logger::Log(DEBUG, "Subscribed to server");

    zmq::context_t pub_context(1);
    GameLoop::getGameLoopInstance()->publisher = zmq::socket_t(pub_context, ZMQ_PUB);
    GameLoop::getGameLoopInstance()->publisher.bind("tcp://*:6666");
    Logger::Log(DEBUG, "Publisher to server");
    Logger::printStartMessage();
    GameLoop::getGameLoopInstance()->Start();
    return 0;
}
