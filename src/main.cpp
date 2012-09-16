# include <iostream>
# include <cstdlib>

# include <unistd.h>

# include "webcli.hpp"

int main(int argc, char**argv)
{
	bool enable_http = false;
	unsigned short http_port = 8023;
	const char *commands_file = "~/.webcli-commands";

	int opt;
	while((opt = getopt(argc, argv, "hp:c:")) != -1)
	{
		switch(opt)
		{
		case 'h':
			enable_http = true;
			break;
		case 'p':
			http_port = atoi(optarg);
			break;
		case 'c':
			commands_file = optarg;
			break;
		default:
			std::cerr<<"Usage: "<<argv[0]<<" [-h] [-p PORT] [-c FILE]"<<std::endl;
			return -1;
		}
	}

	WebCLI webcli(commands_file);

	std::string line;
	while(std::getline(std::cin, line))
	{
		std::cout << webcli.resolveCommand(line) << std::endl;
	}

	return 0;
}
      
