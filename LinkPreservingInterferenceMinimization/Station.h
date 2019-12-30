#pragma once
#include <vector>
#include <utility>
#include <memory>
#include <unordered_map>
#include <chrono>

using namespace std;

class Station
{
public:
	Station(const int radio_max, const int channel_max, const int b, const int sn, const double x=0, const double y=0)
		:sn(sn), interface_size(0),
		loc_x(x), loc_y(y), r_max(radio_max), c_max(channel_max), beta(b), strategy(channel_max, false) {};
	virtual void add_neighbour(const shared_ptr<Station> &neighbour);
	virtual void init_strategy();
	void assign_strategy(const vector<bool> &new_strategy);
	void assign_channel(const vector<int> &new_channel);

	vector<int> get_channel();

	bool best_response();
	virtual int utility();
	int t();
	int impact();
	int gain();
	int C(const shared_ptr<Station>& neighbour);
	int common(const shared_ptr<Station>& neighbour) ;
	double loc_x, loc_y;
	~Station();
	int interface_size;
protected:
	const int r_max, beta;
	int c_max;
	int sn;
	chrono::steady_clock::time_point t_strategy;
	unordered_map<int, pair<chrono::steady_clock::time_point, int>> common_cache;
	vector<weak_ptr<Station>> neighbours;
	vector<bool> strategy;
	friend class Mesh;
};
