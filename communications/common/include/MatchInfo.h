#ifndef MATCHINFO_H
#define MATCHINFO_H

class MatchInfo {
    int actualNumberOfPlayers;
    int maximumNumberOfPlayers;
    int matchId;
    int levelId;
public:
    MatchInfo(int matchId, int levelId, int maximumNumberOfPlayers, int actualNumberOfPlayers);
    int getMatchId() const;
    int getLevelId() const;
    int getMaximumNumberOfUsers() const;
    int getActualNumberOfUsers() const;
};

#endif
