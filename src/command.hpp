# ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>

class Command
{
public:
	Command(const std::string &line);

	std::string getCommand() const { return command; }

	std::string resolve(const std::string &arg) const;

private:
	std::string command;

	std::string start;
	std::string end;
	bool has_placeholder;
};

# endif /*COMMAND_HPP*/
