#include "process.hpp"
#include "fivem.hpp"
#include <iostream>

auto main ( ) -> int
{
	SetConsoleTitleA( "Scripthook Bypass - unknowncheats.me" );

	auto fivemprocess = Process( "GTAProcess.exe", PROCESS_ALL_ACCESS );

	if ( !fivemprocess.IsAttached( ) )
	{
		std::cout << "[-] FiveM is not running." << std::endl;
		std::cin.get( );
		return 0;
	}

	std::cout << "[+] Attached to FiveM." << std::endl;

	if ( fivemprocess.ReadVirtualMemory<uint32_t>( 
		fivem::GetGameBuild( &fivemprocess ) ) >= 2189 )
	{
		std::cout << "[!] You'll need to inject your menus." << std::endl;
	}

	auto picoregameinit = fivem::GetICoreGameInit( &fivemprocess );

	if ( !picoregameinit )
	{
		std::cout << "[-] ICoreGameInit not found." << std::endl;
		std::cin.get( );
		return 0;
	}

	std::cout << "[+] ICoreGameInit found." << std::endl;

	auto pfirst_pair = fivem::GetFirstPair( &fivemprocess );

	if ( !pfirst_pair )
	{
		std::cout << "[-] First pair not found." << std::endl;
		std::cin.get( );
		return 0;
	}

	std::cout << "[+] First pair found." << std::endl;

	auto psecond_pair = fivem::GetSecondPair( &fivemprocess );

	if ( !psecond_pair )
	{
		std::cout << "[-] Second pair not found." << std::endl;
		std::cin.get( );
		return 0;
	}

	std::cout << "[+] Second pair found." << std::endl;

	auto first_pair = fivemprocess.ReadVirtualMemory<FirstPair>(
		pfirst_pair );

	auto second_pair = fivemprocess.ReadVirtualMemory<SecondPair>(
		psecond_pair );

	std::cout << "[+] Adjusting pairs..." << std::endl;

	first_pair.first = first_pair.second ^ 0xDE;
	second_pair.first = second_pair.second ^ 0xDE;

	std::cout << "[+] Writing pairs..." << std::endl;

	fivemprocess.WriteVirtualMemory<FirstPair>(
		pfirst_pair, first_pair );

	fivemprocess.WriteVirtualMemory<SecondPair>(
		psecond_pair, second_pair );

	std::cout << "[~] Enabled have fun..." << std::endl;

	while ( true )
	{
		fivemprocess.WriteVirtualMemory<bool>(
			picoregameinit + 0x8, true );

		Sleep( 1 );
	}

	return 0;
}
