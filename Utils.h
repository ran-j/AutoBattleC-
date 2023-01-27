#include <cstdlib>

class Utils
{
public:
    static inline int GetRandomInt(int min, int max)
    {
        int range = max - min + 1;
        return rand() % range + min;
    }

    static inline float GetRandomFloat(float min, float max)
    {
        return max + (rand() / (RAND_MAX / (min - max)));
    }

    static inline double DistanceTo(double x1, double y1, double x2, double y2)
    {
        //https://www.wikihow.com/Find-the-Distance-Between-Two-Points
        return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

    static inline float RollD4()
    {
        return GetRandomFloat(1, 4);
    }
};