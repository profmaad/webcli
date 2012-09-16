# include <fstream>

# include "command.hpp"

# include "webcli.hpp"

WebCLI::WebCLI(const char *commands_file, bool echo) : echo(echo)
{
	loadCommands(commands_file);
}
WebCLI::~WebCLI()
{
	for(CommandsMap::iterator it = commands.begin(); it != commands.end(); it++)
	{
		delete (*it).second;
	}
}

void WebCLI::loadCommands(const char *commands_file)
{
	std::ifstream file(commands_file);

	std::string line;
	while(std::getline(file, line))
	{
		Command *command = new Command(line);
		commands.insert(CommandsMapPair(command->getCommand(), command));
	}
}

std::string WebCLI::resolveCommand(const std::string &string) const
{
	size_t whitespace_pos;
	if((whitespace_pos = string.find_first_of(" \t")) != std::string::npos)
	{
		std::string command = string.substr(0, whitespace_pos);
		std::string arg = string.substr(whitespace_pos+1);
		
		CommandsMap::const_iterator it = commands.find(command);
		if(it != commands.end())
		{
			return (*it).second->resolve(arg);
		}
		else { return std::string(); }
	}
	else if(echo)
	{
		return string;
	}
	else { return std::string(); }
}
