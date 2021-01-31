#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <stdio.h>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>

class Console
{
private:
	std::mutex _mtx;
	std::string _input;
	std::string _prompt;

public:
	Console() {}

	Console(const Console &) = delete;
	Console &operator=(const Console &) = delete;

	std::string read();

	void write(const char *text, size_t size);
	void write(const char *text) { write(text, strlen(text)); }
	void write(const std::string &text) { write(text.c_str(), text.size()); }
};

struct Flags
{
	bool exit;
	bool start;
	Console console;

	Flags() : exit(false), start(true) {}
};

void dataProc(Flags &shared);

void processInput(const std::string &input, Flags &shared);

#endif
