#include "MatchInfo.h"

MatchInfo::MatchInfo(int matchId, int levelId, int maximumNumberOfPlayers, int actualNumberOfPlayers):
        matchId(matchId), levelId(levelId),maximumNumberOfPlayers(maximumNumberOfPlayers),
        actualNumberOfPlayers(actualNumberOfPlayers) {}

int MatchInfo::getMatchId() const {
    return matchId;
}
int MatchInfo::getLevelId() const {
    return levelId;
}
int MatchInfo::getMaximumNumberOfUsers() const {
    return maximumNumberOfPlayers;
}
int MatchInfo::getActualNumberOfUsers() const {
    return actualNumberOfPlayers;
}
