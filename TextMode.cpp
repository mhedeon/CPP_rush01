#include "TextMode.hpp"
#include <unistd.h>

TextMode::TextMode ( IMonitorModule* module) : IMonitorDisplay(), _module(module)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	_win = newwin(HEIGHT, WIDTH,  0, 0);
	mvwprintw(_win, 1, 1, "%s", "");
	wrefresh(_win);
	start_color();
}

TextMode::~TextMode()
{
	delwin(_win);
	keypad(stdscr, FALSE);
	nodelay(stdscr, FALSE);
	endwin();
}

void	TextMode::printOutput(void) const
{
	while (true)
	{
		wclear(_win);
		this->_module->updateInfo();
		
		mvwprintw(_win, 2, WIDTH / 2 - strlen("ft_gkrellm") / 2, "%s", "ft_gkrellm");

		mvwprintw(_win, 4, 2, "%s", "Date: ");
		mvwprintw(_win, 4, 8, "%s", &_module->getDateInfo()[0]);

		mvwprintw(_win, 6, 2, "%s", "Host: ");
		mvwprintw(_win, 6, 8, "%s", &_module->getHostInfo()[0]);
		mvwprintw(_win, 6, 23, "%s", " |  Username: ");
		mvwprintw(_win, 6, 37, "%s", &_module->getUserInfo()[0]);

		mvwprintw(_win, 8, 2, "%s", &_module->getOsInfo().substr(0, 22).replace(12, 1, "    ")[0]);
		mvwprintw(_win, 9, 2, "%s", &_module->getOsInfo().substr(22, 23).replace(15, 1, " ")[0]);
		mvwprintw(_win, 10, 2, "%s", &_module->getOsInfo().substr(46, 19).replace(13, 1, "   ")[0]);

		mvwprintw(_win, 12, 2, "%s", "CPU Information:");
		mvwprintw(_win, 13, 3, "%s", &_module->getCpuInfo()[0]);

		mvwprintw(_win, 15, 2, "%s", "CPU Usage:");
		mvwprintw(_win, 15, 13, "%s", &_module->getCpuUsage()[0]);

		std::stringstream tmp;
		tmp << "[";
		for (int i = 0, end = (WIDTH - 2) * atoi(_module->getCpuUsage().c_str()) / 100; i < end; i++)
			tmp << "-";
		tmp << std::setw(WIDTH - 2 - strlen(tmp.str().c_str())) << std::setfill(' ') << "]";
		mvwprintw(_win, 16, 1, "%s", &tmp.str()[0]);

		mvwprintw(_win, 18, 2, "%s", "RAM Info: ");
		mvwprintw(_win, 18, 13, "%s", &_module->getRamInfo()[0]);

		mvwprintw(_win, 20, 2, "%s", "RAM Usage: ");
		mvwprintw(_win, 20, 13, "%s", &_module->getRamUsage()[0]);

		mvwprintw(_win, 22, WIDTH / 2 - strlen("Network information:") / 2, "%s", "Network information:");
		mvwprintw(_win, 23, 2, "%s", "Packages in: ");
		mvwprintw(_win, 23, 16, "%s", &_module->getNetIn()[0]);
		mvwprintw(_win, 24, 2, "%s", "Packages out: ");
		mvwprintw(_win, 24, 16, "%s", &_module->getNetOut()[0]);

		mvwprintw(_win, 28, 21, "%s", " _._     _,-'""`-._");
		mvwprintw(_win, 29, 21, "%s", "(,-.`._,'(       |\\`-/|");
		if (rand() % 2)
			mvwprintw(_win, 30, 21, "%s", "    `-.-' \\ )-`( , o o)");
		else
			mvwprintw(_win, 30, 21, "%s", "    `-.-' \\ )-`( , - -)");
		mvwprintw(_win, 31, 21, "%s", "          `-    \\`_`\"'-");

		box(_win, 0, 0);
		wrefresh(_win);
	}
}

/*
 _._     _,-'""`-._
(,-.`._,'(       |\`-/|
    `-.-' \ )-`( , o o)
          `-    \`_`"'-
 */