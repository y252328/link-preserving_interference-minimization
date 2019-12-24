#pragma once
#include <vector>
#include <memory>
#include <unordered_set>

using namespace std;

class Station
{
public:
	Station(const int radio_max, const int channel_max)
		:r_max(radio_max), c_max(channel_max) {};
	void add_neighbour(const shared_ptr<Station> &neighbour);
	void init_channel();
	void assign_channel(const int radio_idx, const int channel);
	void assign_channel(const vector<int> channels);

	bool best_response();
	int utility(const int beta);
	int t(const int beta);
	int impact();
	int gain();
	int C(const shared_ptr<Station>& neighbour);
	int common(const shared_ptr<Station>& neighbour);
	~Station();
private:
	const int r_max, c_max;
	vector<weak_ptr<Station>> neighbours;
	vector<bool> strategy;
};
