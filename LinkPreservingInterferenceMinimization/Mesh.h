#pragma once
#include <vector>
#include <memory>

#include "Station.h"
using namespace std;

class Mesh
{
public:
	Mesh(const int max_ch) : max_channel(max_ch) {};
	void add_station(shared_ptr<Station> station);
	void add_neighbour(const int idx_a, const int idx_b);
	void init_channel();

	vector<shared_ptr<Station>> stations;
	~Mesh();
private:
	const int max_channel;

};

