#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comparePairs(pair<int,int> a, pair<int,int> b)
{
    return a.first < b.second;
}

vector<pair<int,int>> mergeIntervals(vector<pair<int,int>>& pairs)
{
    vector<pair<int,int>> resultingIntervals;

    for (int i = 0; i < pairs.size(); i++)
    {
        // all integers in the array are unique, so an overlapping integer represents a sequence in the array without ambiguity
        if (i == pairs.size()-1 || pairs[i].second < pairs[i+1].first)
            resultingIntervals.push_back(pairs[i]);

        else
            pairs[i+1] = pair<int,int>(pairs[i].first, pairs[i+1].second);
    }

    return resultingIntervals;
}

int findLongestIntervalLength(vector<pair<int,int>>& intervals)
{
    int maxFound = 0;
    for (int i = 0; i < intervals.size(); i++)
    {
        int intervalLength = intervals[i].second-intervals[i].first+1;
        if ( intervalLength > maxFound)
            maxFound = intervalLength;
    }

    return maxFound;
}

int findLongestSnake(vector<vector<int>>& matrix)
{
	int width = matrix.size();
	int height = matrix[0].size();

	vector<pair<int,int>> pairs;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if ((i-1) >= 0 && abs(matrix[i][j]-matrix[i-1][j]) == 1)
			{
                // want all pairs to have lowest integer value as the 'first' data member
                if (matrix[i][j] < matrix[i-1][j])
				    pairs.push_back(pair<int,int>(matrix[i][j], matrix[i-1][j]));
                else
                    pairs.push_back(pair<int,int>(matrix[i-1][j], matrix[i][j]));
			}

			if ((j-1) >= 0 && abs(matrix[i][j]-matrix[i][j-1]) == 1)
			{
				if (matrix[i][j] < matrix[i][j-1])
				    pairs.push_back(pair<int,int>(matrix[i][j], matrix[i][j-1]));
                else
                    pairs.push_back(pair<int,int>(matrix[i][j-1], matrix[i][j]));
			}
		}
	}

	sort(pairs.begin(), pairs.end(), comparePairs);

    auto sortedIntervals = mergeIntervals(pairs);

    return findLongestIntervalLength(sortedIntervals);
}

int main()
{
	vector < vector < int > > matrix(5);
	for (int i = 0; i < 5; i++)
		matrix[i].resize(4);
	int a[4] = {9,10,12,13};
	matrix[0].assign(a, a+4);
	int b[4] = {8,7,6,5};
	matrix[1].assign(b,b+4);
	int c[4] = {16,2,3,4};
	matrix[2].assign(c,c+4);
	int d[4] = {18,1,15,14};
	matrix[3].assign(d,d+4);
	int e[4] = {17,20,19,11};
	matrix[4].assign(e,e+4);

	cout << findLongestSnake(matrix) << endl;

	char temp;
	cin >> temp;
	return 0;
}