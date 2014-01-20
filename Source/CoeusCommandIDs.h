//
//  DrvmatomComandIDs.h
//  drumatom
//
//  Created by accusonus on 9/21/13.
//
//

#ifndef __coeus__DrvmatomComandIDs__
#define __coeus__DrvmatomComandIDs__

#include <iostream>

/** Command Ids that are used by the application command manager.
*/
class CoeusCommandIDs
{
public:
	//==============================================================================
	enum CommandIDs
	{
		ConnectToServerDialog = 0x0010,
		SelectCompanyDialog = 0x0011,
		SyncWithServer = 0x0012,
		NewTab = 0x0021,
		CloseTab = 0x0022,
		QuitProgram = 0x0023
	};
};

#endif /* defined(__drumatom__DrvmatomComandIDs__) */