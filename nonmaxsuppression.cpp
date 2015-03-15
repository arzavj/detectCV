#include "nonmaxsuppression.h"
#include <algorithm>
#include <numeric>

#define OVERLAP_THRESH 0.5
#define SCORE_THRESH 0.8

/*
 * Obtained from
 * http://stackoverflow.com/questions/17074324/how-can-i-sort-two-vectors-in-the-same-way-with-criteria-that-uses-only-one-of */

static vector<int> sort_permutation(vector<pair<float, int>> const& scoreLabels)
{
    vector<int> p(scoreLabels.size());
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j){ return scoreLabels[i].first > scoreLabels[j].first; });
    return p;
}

static vector<Rect> apply_permutation(vector<Rect> const& windows, vector<int> const& sortedIndices)
{
    vector<Rect> sortedWindows(sortedIndices.size());
    transform(sortedIndices.begin(), sortedIndices.end(), sortedWindows.begin(),
              [&](int i){ return windows[i]; });
    return sortedWindows;
}

static double getOverlap(Rect w1, Rect w2)
{
    int intersectionArea = (w1 & w2).area();
    int unionArea = w1.area() + w2.area() - intersectionArea;
    return ((double) intersectionArea) / unionArea; //TODO: pick smaller or bigger area?
}

NonMaxSuppression::NonMaxSuppression()
{
}

vector<tuple<Rect, float, int>> NonMaxSuppression::suppress(vector<Rect> windows,
                                                            vector<pair<float, int>> scoreLabels)
{
    vector<int> sortedIndices = sort_permutation(scoreLabels);
    vector<Rect> sortedWindows = apply_permutation(windows, sortedIndices);
    vector<bool> keepWindows(sortedWindows.size(), true);
    vector<tuple<Rect, float, int>> result;

    for (int i = 0; i < sortedWindows.size(); i++) {
        int sortedIdx = sortedIndices[i];
        if (!keepWindows[i] || scoreLabels[sortedIdx].first < SCORE_THRESH) {
            continue;
        }
        for (int j = i + 1; j < sortedWindows.size(); j++) {
            if (getOverlap(sortedWindows[i], sortedWindows[j]) > OVERLAP_THRESH) {
                keepWindows[j] = false;
            }
        }
        result.push_back(make_tuple(sortedWindows[i], scoreLabels[sortedIdx].first,
                                    scoreLabels[sortedIdx].second));
    }

    return result;
}
