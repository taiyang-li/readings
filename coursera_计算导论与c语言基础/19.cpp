#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;

float calcDistance(const pair<float, float>& p1, const pair<float, float>& p2)
{
	float delta_x = p1.first - p2.first;
	float delta_y = p1.second - p2.second;
	float result = sqrt(delta_x * delta_x + delta_y * delta_y);
	// cout << delta_x << ", " << delta_y << ", " << result << endl;
	return result;
}

int main()
{
	int n = 0;
	cin >> n;

	vector<pair<float, float> > points;
	for (int i=0; i<n; i++)
	{
		float x, y;
		cin >> x >> y;
		points.push_back(pair<float, float>(x, y));
	}
	
	float max_distance = 0;
	for (int i=0; i<n; i++)
	{
		for (int j=i+1; j<n; j++)
		{
			float d = calcDistance(points[i], points[j]);
			max_distance = max(max_distance, d);
		}
	}
	cout << max_distance << endl;
	return 0;
}

