# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <cstring>

# include <unistd.h>
# include <wordexp.h>

# include <sys/types.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <signal.h>

# include <microhttpd.h>

# include "webcli.hpp"

void print_usage(const char *program_name)
{
	std::cerr<<"Usage: "<<program_name<<" [-he] [-p PORT] [-c FILE]"<<std::endl;

	std::cerr<<"\t -h: start http daemon" << std::endl;
	std::cerr<<"\t -e: if no command was given, just echo back the request" << std::endl;
	std::cerr<<"\t -d: daemonize (implies -h)" << std::endl;
	std::cerr<<"\t -p PORT: use PORT for http daemon" << std::endl;
	std::cerr<<"\t -c FILE: read commadns from FILE" << std::endl;
}

int http_callback(void *cls,
		  MHD_Connection *connection,
		  const char *url,
		  const char *method, const char *version,
		  const char *upload_data, size_t *upload_data_size,
		  void **con_cls)
{
	WebCLI *webcli = (WebCLI*)cls;
	MHD_Response *response;
	int return_value;

	const char *query = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "q");
	std::string result;
	if(!query)
	{
		result = webcli->resolveCommand(std::string());
	}
	else
	{
		result = webcli->resolveCommand(std::string(query));
	}

	response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
	if(!response) { return MHD_NO; }

	if(MHD_add_response_header(response, "Location", result.c_str()) == MHD_NO)
	{
		MHD_destroy_response(response);
		return MHD_NO;
	}

	return_value = MHD_queue_response(connection, MHD_HTTP_FOUND, response);
	MHD_destroy_response(response);

	return return_value;
}
void daemonize()
{
        int i;

        if(getppid()==1) { return; }

        i = fork();
        if(i < 0) { exit(1); }
        if(i > 0) { exit(0); }
 
        setsid();
        for(i = getdtablesize(); i >= 0; --i)
	{
		close(i);
	}
	i = open("/dev/null",O_RDWR);
	dup(i);
	dup(i);
 
        signal(SIGCHLD,SIG_IGN);
        signal(SIGTSTP,SIG_IGN);
        signal(SIGTTOU,SIG_IGN);
        signal(SIGTTIN,SIG_IGN);
}

int main(int argc, char**argv)
{
	bool enable_http = false;
	bool echo = false;
	bool enable_daemonize = false;
	unsigned short http_port = 8023;
	const char *commands_file = "~/.webcli-commands";

	int opt;
	while((opt = getopt(argc, argv, "hedp:c:")) != -1)
	{
		switch(opt)
		{
		case 'h':
			enable_http = true;
			break;
		case 'e':
			echo = true;
			break;
		case 'd':
			enable_http = true;
			enable_daemonize = true;
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

	if(enable_daemonize) { daemonize(); }

	wordexp_t exp_result;
	wordexp(commands_file, &exp_result, 0);	

	WebCLI webcli(exp_result.we_wordv[0], echo);

	if(enable_http)
	{
		MHD_Daemon *daemon;
		sockaddr_in localhost;
		memset(&localhost, 0, sizeof(localhost));
		localhost.sin_family = AF_INET;
		localhost.sin_addr.s_addr = inet_addr("127.0.0.1");
		localhost.sin_port = htons(http_port);

		daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, http_port, NULL, NULL, &http_callback, &webcli, MHD_OPTION_SOCK_ADDR, &localhost, MHD_OPTION_END);
		if(!daemon)
		{
			std::cerr<<"Failed to start http daemon, exiting"<<std::endl;
			return -1;
		}

		sigset_t set;
		sigemptyset(&set);
		sigaddset(&set, SIGHUP);
		sigaddset(&set, SIGINT);
		sigaddset(&set, SIGTERM);
		sigsuspend(&set);

		MHD_stop_daemon(daemon);
	}
	else
	{
		std::string line;
		while(std::getline(std::cin, line))
		{
			std::cout << webcli.resolveCommand(line) << std::endl;
		}
	}

	return 0;
}
      
