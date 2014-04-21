#include "../JuceLibraryCode/JuceHeader.h"

#define QUERYBLOCKSIZE (1024 * 1024 * 2)

class CacheSystemClient
{
public:
	virtual void receivedNumberOfResults() = 0;
	virtual void receivedResults() = 0;

private:

};

class CacheReadyMessage : public CallbackMessage
{
public:
	CacheReadyMessage(CacheSystemClient *client_) : client(client_) { }

	virtual void messageCallback() = 0;

private:
	CacheSystemClient *client;
};

class QueryEntry{
public:
	QueryEntry() : result(nullptr), size(0) {
	}

	~QueryEntry() {
		if (result != nullptr) {
			free(result);
		}
	}

	String request;
	Array<WeakReference<CacheSystemClient>> clientList;
	void *result;
	Array<int> fieldSizes;
	unsigned long size;
	unsigned long usedSpace;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QueryEntry)
};

class CacheSystem
{
public:
	CacheSystem();
	~CacheSystem();

	bool setUserName();
	bool setPassword();
	bool setServer(String &address_, uint32 port_);

	void getResultsFor(String &str, CacheSystemClient *client);

private:

	void serveNextQuery();
	MYSQL *initialiseConnection();

	String username;
	String password;
	String address;
	uint32 port;

	OwnedArray<QueryEntry> queries;
	CriticalSection querySection;
};