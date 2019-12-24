#include "Station.h"


void Station::add_neighbour(const shared_ptr<Station>& neighbour)
{
	for (const auto &ptr : neighbours) {
		if(ptr.lock() == neighbour)
			return;
	}
	neighbours.emplace_back(neighbour);
	interfaces.resize((r_max < neighbours.size()) ? r_max : neighbours.size());
}

void Station::assign_channel(const int radio_idx, const int channel)
{
	interfaces.at(radio_idx) = channel;
}

void Station::init_channel()
{
	for (int i = 0; i < interfaces.size(); ++i) {
		interfaces[i] = i + 1;
	}
}

void Station::assign_channel(const vector<int> channels)
{
	for (int i = 0; i < interfaces.size(); ++i) {
		if (i < channels.size())
			interfaces[i] = channels[i];
		else
			interfaces[i] = 0;
	}
}

bool Station::best_response()
{
	vector<bool> max_strategy;
	int max_utility;
	return false;
}

int Station::utility(const int beta)
{
	int u = t(beta);
	for (const auto &ptr : neighbours) {
		u += ptr.lock()->t(beta);
	}
	return u;
}

int Station::t(const int beta)
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
		if (strategy[i] == neighbour->strategy[i])
			++num;
	}
	return num;
}

Station::~Station()
{
}
