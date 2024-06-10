#include "../../server.h"
#include "states.h"

void WaitingForMatchReady::preUpdate(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &matchModel, PayloadBuilder* payloadBuilder) {
}

void WaitingForMatchReady::onUpdate(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &matchModel, PayloadBuilder* payloadBuilder) {
  
}

void WaitingForMatchReady::postUpdate(TransitionalCondition& condition, const std::shared_ptr<MatchModel> &matchModel, PayloadBuilder* payloadBuilder) {
}

void WaitingForMatchReady::autoPlay() {

}

void WaitingForMatchReady::botPlay() {

}
