#ifndef _LEVEL_H_
#define _LEVEL_H_

/*For test use only one level*/
class Level {
    int number;
    int plusScore;
    int minusScore;
public:
    Level() : number(0), plusScore(10), minusScore(-10) {}
    inline bool isNextLevel(Score & score) const {
        return false;
    }
    inline void addScore(Score & score) const  {
        score.value += plusScore;
    }
    inline void delScore(Score & score)  const {
        score.value += minusScore;
    }
    inline float getSpeed() const {
        return 0.036f;
    }
    inline unsigned long getMinDelayBetweenNotes() const {
    	return 10000;
    }
};

#endif
