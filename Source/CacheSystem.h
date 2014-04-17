#include "../JuceLibraryCode/JuceHeader.h"

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


class CacheSystem
{
public:
	~CacheSystem();

	bool setUserName();
	bool setPassword();
	bool setServer(String &address_, uint32 port_);
	bool connectToServer();
	void getResultsFor(String &str, CacheSystemClient *client);

	static CacheSystem *getInstance();

private:
	int fetchResultsFor(String &str);

	CacheSystem();
	CacheSystem(CacheSystem const&){};             // copy constructor is private
	CacheSystem& operator=(CacheSystem const&){};  // assignment operator is private
	static CacheSystem* instancePointer;

	String username;
	String password;
	String address;
	uint32 port;

};