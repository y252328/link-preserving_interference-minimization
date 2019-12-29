#pragma once
#include "Station.h"

#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class Mesh
{
public:
	Mesh() {};
	int add_station(shared_ptr<Station> station);
	int create_station(const int r_max, const int c_max, const int beta, const double x=0, const double y=0);
	void add_neighbour(const int idx_a, const int idx_b);
	void init_channel();

	int potential() const; 
	int interference() const;
	double distance(const int idx_a, const int idx_b) const;
	void find_nash(bool print = false);
	void print_status() const;
	void auto_connect(const double range);
	vector<shared_ptr<Station>> stations;
	~Mesh();
private:
};

