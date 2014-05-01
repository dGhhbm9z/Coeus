#include "../JuceLibraryCode/JuceHeader.h"

#define QUERYBLOCKSIZE (1024 * 1024 * 2)

class CacheSystemClient
{
public:
	~CacheSystemClient() {
		masterReference.clear();
	}

	virtual void receivedResults() = 0;

private:
	WeakReference<CacheSystemClient>::Master masterReference;
	friend class WeakReference<CacheSystemClient>;
};

class CacheReadyMessage : public CallbackMessage
{
public:
	CacheReadyMessage(WeakReference<CacheSystemClient> client_) : client(client_) { }

	virtual void messageCallback() {
		if (client) {
			client->receivedResults();
		}
	};

private:
	WeakReference<CacheSystemClient> client;
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

class CacheSystem	:	public Thread
{
public:
	~CacheSystem();

	bool setUserName();
	bool setPassword();
	bool setServer(String &address_, uint32 port_);

	void getResultsFor(String &str, CacheSystemClient *client);

	static CacheSystem *getInstance();

private:
	CacheSystem();
	CacheSystem(CacheSystem const&) : CacheSystem() {};	// copy constructor is private
	CacheSystem& operator=(CacheSystem const&){};		// assignment operator is private

	void serveNextQuery();
	void *initialiseConnection();
	bool hasUnservedQueries() const;
	void run() override;

	static CacheSystem* instancePointer;

	String username;
	String password;
	String address;
	uint32 port;

	OwnedArray<QueryEntry> queries;
	CriticalSection querySection;
	int nextQueryToServeIndex;
};