#include "StationPP.h"

#include <iostream>
#include <limits>

void StationPP::init_strategy()
{
	int min_rri = std::numeric_limits<int>::max();
	for (const auto & ptr : neighbours) {
		if ((interface_size + ptr.lock()->interface_size - 1) < min_rri) {
			min_rri = (interface_size + ptr.lock()->interface_size - 1);
		}
	}
	if (min_rri < c_max) c_max = min_rri;
	for (int i = 0; i < interface_size; ++i) {
		strategy.at(i) = true;
	}
	t_strategy = chrono::steady_clock::now();
}

int StationPP::utility()
{
	return impact();
}
