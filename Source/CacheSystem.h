#ifndef CacheSystemGuard
#define CacheSystemGuard

#include "../JuceLibraryCode/JuceHeader.h"

#define QUERYBLOCKSIZE (1024 * 1024 * 2)

class QueryEntry;

class CacheSystemClient
{
public:
	virtual ~CacheSystemClient() {
		masterReference.clear();
	}

	virtual void receivedResults(QueryEntry *qe_) = 0;

private:
	WeakReference<CacheSystemClient>::Master masterReference;
	friend class WeakReference<CacheSystemClient>;
};

class CacheReadyMessage : public CallbackMessage
{
public:
	CacheReadyMessage(WeakReference<CacheSystemClient> client_, QueryEntry *qe_)
		: client(client_), qe(qe_) { }

	virtual void messageCallback() {
		if (client) {
			client->receivedResults(qe);
		}
	};

private:
	WeakReference<CacheSystemClient> client;
	QueryEntry *qe;
};

class QueryEntry{
public:
    enum QueryTable { Events=0, Accounts, Companies, Customers, Suppliers, QueryTableSize};
    
	QueryEntry() : result(nullptr), num_fields(0), size(0) {
	}

	~QueryEntry() {
		if (result != nullptr) {
			free(result);
		}
	}

	String getFieldFromRow(int row, int field) {
		const int sz = fieldSizes[row*num_fields + field];
		char *str = (char *) malloc(sz+1);
		str[sz] = '\0';

		int pos = 0;
		for (int i = 0; i < row*num_fields + field; i++) {
			pos += fieldSizes[i];
		}

		memcpy(str, (char*)result + pos, sz);
		String res = String(CharPointer_UTF8(str));
		free(str);

		return res;
	}

	String request;
	Array<WeakReference<CacheSystemClient>> clientList;
	void *result;
	int num_rows;
	int num_fields;
	Array<int> fieldSizes;
	unsigned long size;
	unsigned long usedSpace;
    QueryTable tableType;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QueryEntry)
};

class CacheSystem	:	public Thread
{
public:
	~CacheSystem();

	bool setUserName(String &user);
	bool setPassword(String &pass);
	bool setServer(String &address_, uint32 port_);
	bool testServer();

	void getResultsFor(String &str, QueryEntry::QueryTable tableType, CacheSystemClient *client);

	static CacheSystem *getInstance();

private:
	CacheSystem();
	CacheSystem(CacheSystem const&) : CacheSystem() {};	// copy constructor is private
	CacheSystem& operator=(CacheSystem const&){ return *instancePointer; };		// assignment operator is private

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

#endif