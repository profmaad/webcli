# include <string>

# include "command.hpp"

Command::Command(const std::string &line)
{
	size_t whitespace_pos = line.find_first_of(" \t");
	if(whitespace_pos != std::string::npos)
	{
		command = line.substr(0, whitespace_pos);
		
		size_t placeholder_pos = line.find("%s", whitespace_pos+1);
		if(placeholder_pos != std::string::npos)
		{
			has_placeholder = true;
			start = line.substr(whitespace_pos+1, placeholder_pos-whitespace_pos-1);
			end = line.substr(placeholder_pos+2);
		}
		else
		{
			has_placeholder = false;
			start = line.substr(whitespace_pos+1);
		}
	}
	else
	{
		// throw exception
	}
}

std::string Command::resolve(const std::string &arg) const
{
	if(has_placeholder)
	{
		std::string result = start;
		result.append(arg);
		result.append(end);

		return result;
	}
	else
	{
		return start;
	}
}
