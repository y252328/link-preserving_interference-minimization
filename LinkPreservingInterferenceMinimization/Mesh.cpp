#include "Mesh.h"




void Mesh::add_station(shared_ptr<Station> station)
{
	stations.emplace_back(station);
}

void Mesh::add_neighbour(const int idx_a, const int idx_b)
{
	stations[idx_a-1]->add_neighbour(stations[idx_b-1]);
}

void Mesh::init_channel()
{
	for (auto &ptr : stations) {
		ptr->init_channel();
	}
}


Mesh::~Mesh()
{
}
