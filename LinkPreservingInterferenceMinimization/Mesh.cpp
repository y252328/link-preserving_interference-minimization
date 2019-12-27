#include "Mesh.h"

#include "Station.h"
#include <memory>
#include <cmath>

using namespace std;
int Mesh::add_station(shared_ptr<Station> station)
{
	stations.emplace_back(station);
	station->sn = stations.size() - 1;
	return stations.size() - 1;
}

int Mesh::create_station(const int r_max, const int c_max, const int beta, const double x, const double y)
{
	int sn = stations.size();
	stations.push_back(make_shared<Station>(r_max, c_max, beta, sn, x, y));
	return stations.size() - 1;
}

void Mesh::add_neighbour(const int idx_a, const int idx_b)
{
	stations[idx_a-1]->add_neighbour(stations[idx_b-1]);
}

void Mesh::init_channel()
{
	for (auto &ptr : stations) {
		ptr->init_strategy();
	}
}

int Mesh::potential() const
{
	int phi = 0;
	for (const auto & ptr : stations) {
		phi += ptr->t();
	}
	return phi;
}

double Mesh::distance(const int idx_a, const int idx_b) const
{
	auto a = (stations[idx_a]->loc_x - stations[idx_b]->loc_x);
	auto b = (stations[idx_a]->loc_y - stations[idx_b]->loc_y);
	auto distance = sqrt(a*a + b*b);
	return distance;
}

void Mesh::find_nash()
{
	auto move = false;
	//print_status();
	do {
		move = false;
		for (auto &ptr : stations) {
			if (ptr->best_response()) {
				move = true;
				break;
			}
		}
		//print_status();
	} while (move);
}

void Mesh::print_status() const
{
	for (int i = 0; i < stations.size(); ++i) {
		cout << "{";
		for (const auto ch : stations[i]->get_channel()) {
			cout << " " << ch;
		}
		cout << "}  ";
	}
	cout << endl;
}

void Mesh::auto_connect(const double range)
{
	for (int i = 0; i < stations.size(); ++i) {
		for (int j = 0; j < stations.size(); ++j) {
			if (distance(i, j) >= range) {
				stations[i]->add_neighbour(stations[j]);
				stations[j]->add_neighbour(stations[i]);
			}
		}
	}
}


Mesh::~Mesh()
{
}
