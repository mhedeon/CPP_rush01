#ifndef GRAPHMODE_HPP
# define GRAPHMODE_HPP

# include "IMonitorDisplay.hpp"
# include "IMonitorModule.hpp"

# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include <iomanip>
# include "SDL.h"
# include "SDL_ttf.h"

# define WIN_WIDTH 400
# define WIN_HEIGHT 800

class GraphMode: public IMonitorDisplay
{
public:
	GraphMode ( IMonitorModule* );
	virtual ~GraphMode ( void );
	void printOutput ( void ) const;
private:
	GraphMode ( void );
	GraphMode ( GraphMode const & );
	GraphMode& operator= ( GraphMode const & );

	TTF_Font*		ttf_open_font(int size);
	void			ttf_close_font(TTF_Font *font);
	void			ttf_render_text(SDL_Renderer *ren, TTF_Font *font, int x, int y, const char *text) const;

	IMonitorModule* _module;
	SDL_Window *_win;
	SDL_Renderer *_ren;
	TTF_Font* _font;
};


#endif
