#include "process.hpp"

auto FindModuleBySnapshot ( const HANDLE& Snapshot, const std::string& ModuleName ) -> HMODULE
{
	auto mEntry = MODULEENTRY32 { sizeof( MODULEENTRY32 ) };

	while ( Module32Next( Snapshot, &mEntry) )
		if ( strstr( reinterpret_cast<char*>( mEntry.szModule ), ModuleName.c_str( ) ) )
			return mEntry.hModule;

	return nullptr;
}

auto FindProcesssIdBySnapshot ( const HANDLE& Snapshot, const std::string& ProcessName ) -> DWORD
{
	auto pEntry = PROCESSENTRY32{ sizeof( PROCESSENTRY32 ) };

	while ( Process32Next( Snapshot, &pEntry ) )
		if ( strstr( reinterpret_cast<char*>( pEntry.szExeFile ), ProcessName.c_str( ) ) )
			return pEntry.th32ProcessID;

	return NULL;
}

auto FindThreadIdBySnapshot ( const HANDLE& Snapshot, const DWORD& ProcessId ) -> const DWORD
{
	auto tEntry = THREADENTRY32{ sizeof( THREADENTRY32 ) };

	while ( Thread32Next( Snapshot, &tEntry ) )
		if ( tEntry.th32OwnerProcessID == ProcessId )
			return tEntry.th32ThreadID;

	return NULL;
}

auto GetProcessThreadId ( const DWORD& ProcessId ) -> const DWORD
{
	auto Snapshot =	CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, NULL );

	auto ThreadId =	FindThreadIdBySnapshot( Snapshot, ProcessId );

	CloseHandle( Snapshot );
	return ThreadId;
}

auto GetProcessModule ( const std::string& ModuleName, const DWORD ProcessId ) -> uint64_t
{
	auto Snapshot =	CreateToolhelp32Snapshot( 
		TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessId );

	auto hModule =	reinterpret_cast<uint64_t>( 
		FindModuleBySnapshot( Snapshot, ModuleName ) );

	CloseHandle( Snapshot );
	return hModule;
}

auto GetProcessByName ( const std::string& ProcessName ) -> const DWORD
{
	auto Snapshot =	CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );

	auto ProcID = FindProcesssIdBySnapshot( Snapshot, ProcessName );

	CloseHandle( Snapshot );
	return ProcID;
}

auto Process::GetModuleBase ( const std::string& name ) -> uint64_t
{
	auto pid = GetProcessId( handle );
	return GetProcessModule( name, pid );
}

Process::Process ( const std::string& name, const DWORD& access )
{		
	this->handle = OpenProcess( 
		access, false, GetProcessByName( name ) );
}

auto Process::IsAttached ( ) -> bool
{
	return GetProcessId( handle );
}

Process::~Process ( )
{
	CloseHandle( handle );
}
