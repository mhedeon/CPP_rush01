#include <unistd.h>
#include <signal.h>
#include <iostream>
#include "OSInfo.class.hpp"
#include "TextMode.hpp"
#include "GraphMode.hpp"
#include <ctime>

void usage ( void )
{
	std::cout << "Usage: ./ft_gkrellm < \"-g\" to graphical interface or \"-c\" to open in console >" << std::endl;
	exit (1);
}

int main (int ac, char ** av)
{
	srand(time(NULL));
	IMonitorModule *m = new OSInfo();
	IMonitorDisplay *d ;
	if (ac != 2)
		usage();
	if (!std::string(av[1]).compare("-c"))
		d = new TextMode(m);
	else if (!std::string(av[1]).compare("-g"))
		d = new GraphMode(m);
	else
	{
		delete m;
		return (0);
	}
	d->printOutput();

	delete m;
	delete d;
	return (0);
}
