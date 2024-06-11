#include "../../server.h"

void WaitingForUsers::preUpdate(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &matchModel, PayloadBuilder* payloadBuilder) {
    Logger::Log(DEBUG, "WaitingForUsers::preUpdate ");
}

void WaitingForUsers::onUpdate(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &matchModel, PayloadBuilder* payloadBuilder) {
  
    Logger::Log(DEBUG, "WaitingForUsers::onUpdate ");
}

void WaitingForUsers::postUpdate(TransitionalCondition& condition, const std::shared_ptr<MatchModel> &matchModel, PayloadBuilder* payloadBuilder) {
    Logger::Log(DEBUG, "WaitingForUsers::postUpdate ");
}

void WaitingForUsers::autoPlay() {

}

void WaitingForUsers::botPlay() {

}
