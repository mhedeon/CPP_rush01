#ifndef OSInfo_HPP
# define OSInfo_HPP

# include "IMonitorModule.hpp"
# include <array>
# include <iostream>
# include <string>
# include <cstdlib>
# include <sstream>

class OSInfo : public IMonitorModule
{
	public:
		OSInfo ( void );
		virtual ~OSInfo ( void );
		OSInfo ( OSInfo const & obj );
		OSInfo &operator= ( OSInfo const & rhs );

		virtual std::string getUserInfo ( void ) const;
		virtual std::string getHostInfo ( void ) const;
		virtual std::string getOsInfo ( void ) const;
		virtual std::string getDateInfo ( void ) const;
		virtual std::string getCpuInfo ( void ) const;
		virtual std::string getCpuUsage ( void ) const;
		virtual std::string getRamInfo ( void ) const;
		virtual std::string getRamUsage ( void ) const;
		virtual std::string getNetIn ( void ) const;
		virtual std::string getNetOut ( void ) const;
		virtual std::string	exec(const char* );
		virtual void updateInfo ( void );
	private:
		std::string _userInfo; //
		std::string _hostInfo; //
		std::string _osInfo; //
		std::string _dateInfo; //
		std::string _cpuInfo; //
		std::string _cpuUsage; //
		std::string _ramInfo; //
		std::string _ramUsage; //
		std::string _netIn;
		std::string _netOut;
};

#endif
