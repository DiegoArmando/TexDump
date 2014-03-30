#ifndef HOT_KEY_LISTENER_H
#define HOT_KEY_LISTENER_H

class hot_key_listener
{
public:
	~hot_key_listener() {};

	void start();
	void stop();
	void run();
	bool get_start() { return start_; }
	static hot_key_listener* getInstance() {
		static hot_key_listener hot_key;
		return &hot_key;
	}

private:
	hot_key_listener() {};
	hot_key_listener(hot_key_listener const&);
	void operator=(hot_key_listener const&);

	bool start_;

};
#endif
