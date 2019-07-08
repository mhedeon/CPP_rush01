#ifndef IMONITORDISPLAY_HPP
# define IMONITORDISPLAY_HPP

class IMonitorDisplay
{
	public:
		virtual ~IMonitorDisplay() {};

		virtual void 	printOutput(void) const = 0;
};

#endif
