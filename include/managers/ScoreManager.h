#pragma once

#include <algorithm>

#include "..\..\include\basics\HistoryScore.h"

typedef std::unique_ptr<Score> Score_uptr;
typedef std::unique_ptr<HistoryScore> HiScore_uptr;
typedef std::vector<Score_uptr> VecScore;
typedef std::vector<HiScore_uptr> VecHiScore;

class ScoreManager
{
private:
	VecHiScore allScores = VecHiScore();
	Score actualScore;

	HistoryScore selectBestScore(int place);

	struct ScoreIndex {
		int index;
		int score;
		ScoreIndex(int index, int score) : index(index), score(score) {}
		bool operator<(const ScoreIndex second) { return score < second.score; }
		bool operator>(const ScoreIndex second) { return score > second.score; }
	};

public:
	ScoreManager();
	virtual ~ScoreManager();

	Score& getActualScore();
	HistoryScore getBestScore();
	int getSize();

	bool addHistoryScore(HistoryScore& score);
	HistoryScore saveActualScore(int level, int foundSnacks);
	void exterminate();
};

