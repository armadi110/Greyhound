#include "stdafx.h"

// The class we are implementing
#include "WraithUpdate.h"

// We need the following classes
#include "Strings.h"
#include "FileSystems.h"

void WraithUpdate::CheckForUpdates(const std::string& GithubName, const std::string& GithubRepoName, const std::string& ApplicationName, const std::string& AssemblyName, bool WaitForResult)
{
	// Attempt to check for updates to the tool
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFOA StartupInfo;

	// Initialize
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(StartupInfo);

	// Get path
	auto UpdaterPath = FileSystems::CombinePath(FileSystems::GetApplicationPath(), "GreyhoundUpdater.exe");

	// Build arguments
	auto Arguments = Strings::Format("\"%s\" %s %s %s %s true", UpdaterPath.c_str(), GithubName.c_str(), GithubRepoName.c_str(), ApplicationName.c_str(), AssemblyName.c_str());

	// Create the process
	if (CreateProcessA(NULL, (char*)Arguments.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
	{
		// Check to wait
		if (WaitForResult)
		{
			// Wait
			WaitForSingleObject(ProcessInfo.hProcess, INFINITE);

			// Clean up
			CloseHandle(ProcessInfo.hThread);
			CloseHandle(ProcessInfo.hProcess);
		}
	}
}