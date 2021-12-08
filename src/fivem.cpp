#include "fivem.hpp"

auto fivem::GetFirstPair ( Process* target ) -> uint64_t
{
	static auto adhesivemodule = 
		target->GetModuleBase( "adhesive.dll" );

	if ( adhesivemodule )
		return adhesivemodule + 0x28F24F0;

	return NULL;
}

auto fivem::GetSecondPair ( Process* target ) -> uint64_t
{
	static auto adhesivemodule = 
		target->GetModuleBase( "adhesive.dll" );

	if ( adhesivemodule )
		return adhesivemodule + 0x28F2B7F;

	return NULL;
}

auto fivem::GetICoreGameInit ( Process* target ) -> uint64_t
{
	static auto gtacoremodule =
		target->GetModuleBase( "gta-core-five.dll" );

	if ( gtacoremodule )
		return gtacoremodule + 0xEFEA8;

	return NULL;
}

auto fivem::GetGameBuild ( Process* target ) -> uint64_t
{
	static auto asifivemodule =
		target->GetModuleBase( "asi-five.dll" );

	if ( asifivemodule )
		return asifivemodule + 0x2E048;

	return NULL;
}
