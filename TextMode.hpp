#ifndef TEXTMODE_HPP
# define TEXTMODE_HPP

# include "IMonitorDisplay.hpp"
# include "IMonitorModule.hpp"

# include <iostream>
# include <string>
# include <vector>
# include <ncurses.h>
# include <sstream>
# include <iomanip>

# define WIDTH 46
# define HEIGHT 33

class TextMode : public IMonitorDisplay
{
	public:
		TextMode ( IMonitorModule* );
		virtual ~TextMode ( void );
		void		printOutput(void) const;
	private:
		TextMode ( void );
		TextMode ( TextMode const & );
		TextMode &operator=(TextMode const & );
		WINDOW*								_win;
		IMonitorModule*					_module;
};



#endif
