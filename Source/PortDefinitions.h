#ifndef PortDefinitionsGuard
#define PortDefinitionsGuard

	#define WINDOWS_RESOURCE_FILE( X ) File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getChildFile( X )
	#define MAC_RESOURCE_FILE( X ) File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getParentDirectory().getChildFile( X )

	#ifdef __APPLE__
		#define RESOURCE_FILE( X ) MAC_RESOURCE_FILE( X )
	#else
		#define RESOURCE_FILE( X ) WINDOWS_RESOURCE_FILE( X )
	#endif

#endif