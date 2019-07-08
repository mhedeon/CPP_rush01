#ifndef IMONITORMODULE_HPP
# define IMONITORMODULE_HPP

# include <iostream>
# include <vector>

typedef std::vector<std::string> t_vector;

class IMonitorModule
{
	public:
		virtual ~IMonitorModule() {}
		virtual std::string	exec(const char* ) = 0;
		virtual std::string getUserInfo ( void ) const = 0;
		virtual std::string getHostInfo ( void ) const = 0;
		virtual std::string getOsInfo ( void ) const = 0;
		virtual std::string getDateInfo ( void ) const = 0;
		virtual std::string getCpuInfo ( void ) const = 0;
		virtual std::string getCpuUsage ( void ) const = 0;
		virtual std::string getRamInfo ( void ) const = 0;
		virtual std::string getRamUsage ( void ) const = 0;
		virtual std::string getNetIn ( void ) const = 0;
		virtual std::string getNetOut ( void ) const = 0;
		virtual void updateInfo ( void ) = 0;
};

#endif
