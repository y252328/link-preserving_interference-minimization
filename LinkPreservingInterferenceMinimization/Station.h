#pragma once
#include <vector>
#include <memory>
#include <unordered_set>

using namespace std;

class Station
{
public:
	Station(const int radio_max, const int channel_max, const int b)
		:r_max(radio_max), c_max(channel_max), beta(b), strategy(channel_max, false) {};
	void add_neighbour(const shared_ptr<Station> &neighbour);
	void init_channel();
	void assign_channel(const vector<bool> new_strategy);

	bool best_response();
	int utility();
	int t();
	int impact();
	int gain();
	int C(const shared_ptr<Station>& neighbour);
	int common(const shared_ptr<Station>& neighbour);
	~Station();
private:
	const int r_max, c_max, beta;
	int interface_size;
	vector<weak_ptr<Station>> neighbours;
	vector<bool> strategy;
};
