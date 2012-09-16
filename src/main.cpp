# include <iostream>
# include <cstdlib>

# include <unistd.h>

# include "webcli.hpp"

void print_usage(const char *program_name)
{
	std::cerr<<"Usage: "<<program_name<<" [-he] [-p PORT] [-c FILE]"<<std::endl;

	std::cerr<<"\t -h: start http daemon" << std::endl;
	std::cerr<<"\t -e: if no command was given, just echo back the request" << std::endl;
	std::cerr<<"\t -p PORT: use PORT for http daemon" << std::endl;
	std::cerr<<"\t -c FILE: read commadns from FILE" << std::endl;
}

int main(int argc, char**argv)
{
	bool enable_http = false;
	bool echo = false;
	unsigned short http_port = 8023;
	const char *commands_file = "~/.webcli-commands";

	int opt;
	while((opt = getopt(argc, argv, "hep:c:")) != -1)
	{
		switch(opt)
		{
		case 'h':
			enable_http = true;
			break;
		case 'e':
			echo = true;
			break;
		case 'p':
			http_port = atoi(optarg);
			break;
		case 'c':
			commands_file = optarg;
			break;
		default:
			print_usage(argv[0]);
			return -1;
		}
	}

	WebCLI webcli(commands_file, echo);

	std::string line;
	while(std::getline(std::cin, line))
	{
		std::cout << webcli.resolveCommand(line) << std::endl;
	}

	return 0;
}
      
