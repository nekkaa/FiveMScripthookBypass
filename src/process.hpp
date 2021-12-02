#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <string>

class Process
{
	public:
		auto GetModuleBase ( const std::string& name ) -> uint64_t;
		auto IsAttached ( ) -> bool;

		template<typename T>
		auto WriteVirtualMemory ( const uint64_t& target, const T& value ) -> bool
		{
			return WriteProcessMemory( handle, reinterpret_cast<PVOID>( target ),
				&value, sizeof( T ), nullptr );
		}

		template<typename T>
		auto ReadVirtualMemory ( const uint64_t& target ) -> T
		{
			T buffer = T( );
			ReadProcessMemory( handle, reinterpret_cast<PVOID>( target ), 
				&buffer, sizeof( T ), nullptr );
			return buffer;
		}

		Process ( const std::string& name, const DWORD& access );
		~Process( );

	private:
		HANDLE handle;
};


