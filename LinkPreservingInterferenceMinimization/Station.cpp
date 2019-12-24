#include "Station.h"

#include <algorithm>
#include <iostream>
#include <limits>

void Station::add_neighbour(const shared_ptr<Station>& neighbour)
{
	for (const auto &ptr : neighbours) {
		if(ptr.lock() == neighbour)
			return;
	}
	neighbours.emplace_back(neighbour);
	interface_size = (r_max < neighbours.size()) ? r_max : neighbours.size();
}

void Station::init_channel()
{
	for (int i = 0; i < interface_size; ++i) {
		strategy.at(i) = true;
	}
}

void Station::assign_channel(const vector<bool> new_strategy)
{
	strategy = new_strategy;
}

bool Station::best_response()
{
	auto org_strategy = strategy;
	vector<bool> max_strategy = org_strategy;
	int max_utility = numeric_limits<int>().min();

	vector<bool> walk(c_max, false);
	fill(walk.begin(), walk.begin()+interface_size, true);

	do {
		strategy = walk;
		auto new_utility = utility();
		if (new_utility > max_utility) {
			max_strategy = walk;
			max_utility = new_utility;
		}
	} while (prev_permutation(walk.begin(), walk.end()));
	strategy = max_strategy;
	return !(max_strategy == org_strategy);
}

int Station::utility()
{
	int u = t();
	for (const auto &ptr : neighbours) {
		u += ptr.lock()->t();
	}
	return u;
}

int Station::t()
{
	return beta * gain() + impact();
}

int Station::impact()
{
	int i = 0;
	for (const auto &ptr : neighbours) {
		i -= common(ptr.lock());
	}
	return i;
}

int Station::gain()
{
	int g = 0;
	for (const auto &nb : neighbours) {
		g += C(nb.lock());
	}
	return g;
}


int Station::C(const shared_ptr<Station>& neighbour)
{
	return (common(neighbour) == 0) ? -static_cast<int>(neighbours.size()) : 0;
}

int Station::common(const shared_ptr<Station>& neighbour)
{
	int num = 0;
	for (int i = 0; i < c_max; ++i) {
		if (strategy.at(i) == neighbour->strategy.at(i))
			++num;
	}
	return num;
}

Station::~Station()
{
}
