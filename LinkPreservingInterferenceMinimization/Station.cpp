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

void Station::init_strategy()
{
	for (int i = 0; i < interface_size; ++i) {
		strategy.at(i) = true;
	}
	t_strategy = chrono::steady_clock::now();
}

void Station::assign_strategy(const vector<bool> &new_strategy)
{
	strategy = new_strategy;
	t_strategy = chrono::steady_clock::now();
}

void Station::assign_channel(const vector<int>& new_channel)
{
	fill(strategy.begin(), strategy.end(), false);
	for (const int ch : new_channel) {
		if (ch - 1 < c_max) {
			strategy[ch - 1] = true;
		}
	}
	t_strategy = chrono::steady_clock::now();
}

vector<int> Station::get_channel()
{
	vector<int> channel;
	for (int i = 0; i < c_max; ++i) {
		if (strategy[i]) channel.push_back(i + 1);
	}
	return channel;
}

bool Station::best_response()
{
	auto org_strategy = strategy;
	vector<bool> max_strategy = org_strategy;
	int max_utility = utility();

	vector<bool> walk(c_max, false);
	fill(walk.begin(), walk.begin()+interface_size, true);

	do {
		strategy = walk;
		t_strategy = chrono::steady_clock::now();
		auto new_utility = utility();
		if (new_utility > max_utility) {
			max_strategy = walk;
			max_utility = new_utility;
		}
	} while (prev_permutation(walk.begin(), walk.end()));
	strategy = max_strategy;
	t_strategy = chrono::steady_clock::now();
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
	auto ptr = neighbour.get();
	const auto & pair = common_cache[neighbour->sn];
	if (pair.first > t_strategy && pair.first > neighbour->t_strategy) {
		return pair.second;
	}

	int num = 0;
	for (int i = 0; i < c_max; ++i) {
		if (strategy[i] && neighbour->strategy[i])
			++num;
	}
	common_cache[neighbour->sn] = make_pair(chrono::steady_clock::now(), num);
	return num;
	//int num = 0;
	//for (int i = 0; i < c_max; ++i) {
	//	if (strategy[i] && neighbour->strategy[i])
	//		++num;
	//}
	//return num;

}

Station::~Station()
{
}
