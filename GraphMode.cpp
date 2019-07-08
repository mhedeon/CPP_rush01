#include "GraphMode.hpp"

GraphMode::GraphMode ( IMonitorModule* module ): IMonitorDisplay(), _module(module)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	_win = SDL_CreateWindow("ft_gkrellm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	_ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	_font = this->ttf_open_font(20);
}

GraphMode::~GraphMode ( void )
{
	ttf_close_font(_font);
}

TTF_Font*		GraphMode::ttf_open_font(int size)
{
	TTF_Font	*newFont;

	if (!TTF_WasInit() && TTF_Init() == -1)
	{
		return (NULL);
	}
	if ((newFont = (TTF_OpenFont("OpenSans-Regular.ttf", size))) == NULL)
	{
		return (NULL);
	}
	return (newFont);
}

void			GraphMode::ttf_close_font(TTF_Font *font)
{
	if (font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}
	if (TTF_WasInit())
		TTF_Quit();
}

void			GraphMode::ttf_render_text(SDL_Renderer *ren, TTF_Font *font, int x, int y, const char *text) const
{
	SDL_Surface	*sur;
	SDL_Texture	*msg;
	SDL_Rect r;

	sur = TTF_RenderText_Blended(font, text, (SDL_Color) { 255, 255, 255, 0 });
	if (sur == NULL)
	{
		return ;
	}
	msg = SDL_CreateTextureFromSurface(ren, sur);
	if (msg == NULL)
	{
		SDL_FreeSurface(sur);
		return ;
	}
	SDL_QueryTexture(msg, NULL, NULL, &r.w, &r.h);
	r.x = x;
	r.y = y;
	SDL_RenderCopy(ren, msg, NULL, &r);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(msg);
}

void GraphMode::printOutput ( void ) const
{
	int end = 0;
	std::string tmpString;
	SDL_SetRenderDrawColor(_ren, 189, 42, 199, 0);
	while (!end)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT)
				end = 1;
		_module->updateInfo();

		SDL_RenderClear(_ren);
		
		this->ttf_render_text(_ren, _font, 150, 20, "ft_gkrellm");

		this->ttf_render_text(_ren, _font, 30, 60, "Date: ");
		tmpString = _module->getDateInfo(); tmpString.erase(tmpString.end() - 1);
		this->ttf_render_text(_ren, _font, 100, 60, tmpString.c_str());

		this->ttf_render_text(_ren, _font, 30, 100, "Host: ");
		tmpString = _module->getHostInfo(); tmpString.erase(tmpString.end() - 1);
		this->ttf_render_text(_ren, _font, 100, 100, tmpString.c_str());

		this->ttf_render_text(_ren, _font, 30, 140, "User: ");
		tmpString = _module->getUserInfo(); tmpString.erase(tmpString.end() - 1);
		this->ttf_render_text(_ren, _font, 100, 140, tmpString.c_str());

		this->ttf_render_text(_ren, _font, 30, 180, _module->getOsInfo().substr(0, 21).replace(12, 1, "    ").c_str());
		this->ttf_render_text(_ren, _font, 30, 220, _module->getOsInfo().substr(22, 23).replace(15, 1, " ").c_str());
		this->ttf_render_text(_ren, _font, 30, 260, _module->getOsInfo().substr(46, 19).replace(13, 1, "   ").c_str());

		this->ttf_render_text(_ren, _font, 30, 300, "CPU Info: ");
		tmpString = _module->getCpuInfo(); tmpString.erase(tmpString.end() - 1);
		this->ttf_render_text(_ren, _font, 10, 340,tmpString.c_str());

		this->ttf_render_text(_ren, _font, 30, 380, "CPU Usage: ");
		tmpString = _module->getCpuUsage(); tmpString.erase(tmpString.end() - 1);
		this->ttf_render_text(_ren, _font, 160, 380, tmpString.c_str());
		
		this->ttf_render_text(_ren, _font, 30, 420, "RAM Info: ");
		tmpString = _module->getRamInfo(); tmpString.replace(tmpString.length() - 1, 1, "b");
		this->ttf_render_text(_ren, _font, 160, 420, tmpString.c_str());

		this->ttf_render_text(_ren, _font, 30, 460, "RAM Usage: ");
		tmpString = _module->getRamUsage(); tmpString.replace(tmpString.length() - 1, 1, "b");
		this->ttf_render_text(_ren, _font, 160, 460, tmpString.c_str());

		this->ttf_render_text(_ren, _font, 150, 500, "Network information:");
		this->ttf_render_text(_ren, _font, 30, 540, "Packages in: ");
		this->ttf_render_text(_ren, _font, 170, 540, _module->getNetIn().c_str());
		this->ttf_render_text(_ren, _font, 30, 580, "Packages out: ");
		this->ttf_render_text(_ren, _font, 170, 580, _module->getNetOut().c_str());

		this->ttf_render_text(_ren, _font, 30, 640, " _._     _,-'""`-._");
		this->ttf_render_text(_ren, _font, 30, 660, "(,-.`._,'(       |\\`-/|");
		if (rand() % 2)
			this->ttf_render_text(_ren, _font, 30, 680, "    `-.-' \\ )-`( , o o)");
		else
			this->ttf_render_text(_ren, _font, 30, 680, "    `-.-' \\ )-`( , -   - )");
		this->ttf_render_text(_ren, _font, 30, 700, "          `-    \\`_`\"'-");

		SDL_RenderPresent(_ren);
	}
}


