#include "../../server.h"
#include "states.h"

void WaitingForMatchReady::preUpdate(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &matchModel, ArenaAllocator &allocator) {
}

void WaitingForMatchReady::onUpdate(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &matchModel, ArenaAllocator &allocator) {
  
}

void WaitingForMatchReady::postUpdate(TransitionalCondition& condition, const std::shared_ptr<MatchModel> &matchModel, ArenaAllocator &allocator) {
}

void WaitingForMatchReady::autoPlay(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &match_model, ArenaAllocator &allocator) {

}

void WaitingForMatchReady::botPlay(TransitionalCondition &condition, const std::shared_ptr<MatchModel> &match_model, ArenaAllocator &allocator) {

}
