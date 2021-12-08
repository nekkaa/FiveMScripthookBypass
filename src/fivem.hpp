#pragma once

#include "process.hpp"
#include <cstdint>

namespace fivem
{
	auto GetICoreGameInit ( Process* target ) -> uint64_t;
	auto GetFirstPair ( Process* target ) -> uint64_t;
	auto GetSecondPair ( Process* target ) -> uint64_t;
	auto GetGameBuild ( Process* target ) -> uint64_t;
}

struct FirstPair
{
	uint8_t second;
	uint8_t pad[0x90B];
	uint8_t first;
};

struct SecondPair
{
	uint8_t first;
	uint8_t pad[0x24C];
	uint8_t second;
};



