#pragma once
#include "Station.h"

#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class Mesh
{
public:
	Mesh(const int max_ch) : max_channel(max_ch) {};
	int add_station(shared_ptr<Station> station);
	int create_station(const int r_max, const int c_max, const int beta);
	void add_neighbour(const int idx_a, const int idx_b);
	void init_channel();

	int potential() const; 
	double distance(const int idx_a, const int idx_b) const;
	void find_nash();
	void print_status() const;
	void auto_connect(const int range);
	vector<shared_ptr<Station>> stations;
	~Mesh();
private:
	const int max_channel;

};

