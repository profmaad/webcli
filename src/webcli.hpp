# ifndef WEBCLI_H
# define WEBCLI_H

# include <string>
# include <map>

class Command;

typedef std::map<std::string, Command*> CommandsMap;
typedef std::pair<std::string, Command*> CommandsMapPair;

class WebCLI
{
public:
	WebCLI(const char *commands_file, bool echo);
	~WebCLI();

	std::string resolveCommand(const std::string &string) const;

private:
	void loadCommands(const char *commands_file);

	CommandsMap commands;

	bool echo;
};

# endif /*WEBCLI_H*/
