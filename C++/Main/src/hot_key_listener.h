#ifndef HOT_KEY_LISTENER_H
#define HOT_KEY_LISTENER_H

#include <Windows.h>

class hot_key_listener
{
public:
	~hot_key_listener() { UnregisterHotKey(NULL, 1); };

	void run();
	static hot_key_listener* getInstance() {
		static hot_key_listener hot_key;
		return &hot_key;
	}

	void stop();
	bool get_start() { return start_; }

private:
	hot_key_listener() {};
	hot_key_listener(hot_key_listener const&);
	void operator=(hot_key_listener const&);

	bool start_;

};
#endif
