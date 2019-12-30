#pragma once
#include "Station.h"
class StationPP :
	public Station
{
public:
	StationPP(const int radio_max, const int channel_max, const int b, const int sn, const double x = 0, const double y = 0) :
		Station(radio_max, channel_max, b, sn, x, y), org_c_max(channel_max) {};
	void init_strategy() override;
	int utility() override;
private:
	int org_c_max;
};

