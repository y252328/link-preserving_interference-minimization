#pragma once
#include <vector>
#include <memory>
#include <unordered_set>

using namespace std;

class Station
{
public:
	Station(const int radio_max, const int channel_max, const int b, const double x=0, const double y=0)
		:sn(0), interface_size(0),
		loc_x(x), loc_y(y), r_max(radio_max), c_max(channel_max), beta(b), strategy(channel_max, false) {};
	void add_neighbour(const shared_ptr<Station> &neighbour);
	void init_strategy();
	void assign_strategy(const vector<bool> &new_strategy);
	void assign_channel(const vector<int> &new_channel);

	vector<int> get_channel();

	bool best_response();
	int utility() const;
	int t() const;
	int impact() const;
	int gain() const;
	int C(const shared_ptr<Station>& neighbour) const;
	int common(const shared_ptr<Station>& neighbour) const;
	int sn;
	double loc_x, loc_y;
	~Station();
private:
	const int r_max, c_max, beta;
	int interface_size;
	vector<weak_ptr<Station>> neighbours;
	vector<bool> strategy;
};
