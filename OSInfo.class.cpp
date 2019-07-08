#include "OSInfo.class.hpp"

OSInfo::OSInfo ( void )
{
	this->updateInfo();
}

OSInfo::~OSInfo ( void )
{

}

OSInfo::OSInfo ( OSInfo const & obj )
{
	*this = obj;
}

OSInfo &OSInfo::operator= ( OSInfo const &assig )
{
	if (this == &assig)
		return (*this);
	this->_userInfo = assig.getUserInfo();
	this->_hostInfo = assig.getHostInfo();
	this->_osInfo = assig.getOsInfo();
	this->_dateInfo = assig.getDateInfo();
	this->_cpuInfo = assig.getCpuInfo();
	this->_cpuUsage = assig.getCpuUsage();
	this->_ramInfo = assig.getRamInfo();
	this->_ramUsage = assig.getRamUsage();
	return *this;
}

std::string OSInfo::exec(const char* cmd){
	std::array<char, 128> buff;
	std::string rt;
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);

	if (!pipe) throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get())) {
		if (fgets(buff.data(), 128, pipe.get()) != nullptr)
			rt += buff.data();
	}
	return rt;
}

void OSInfo::updateInfo ( void )
{
	_userInfo = exec("whoami");
	_hostInfo = exec("hostname");
	_osInfo = exec("sw_vers");
	_dateInfo = exec("date");
	_cpuInfo = exec("sysctl -n machdep.cpu.brand_string");
	_cpuUsage = exec("top -l 1 | grep 'CPU usage:' |  cut -d' ' -f3");
	_ramUsage = exec("top -l 1 | grep 'PhysMem:' |  cut -d' ' -f2");
	_ramInfo = exec("top -l 1 | grep 'PhysMem:' |  cut -d' ' -f6");
	std::string tmpStr = exec("top -l 1 | grep 'PhysMem:' |  cut -d' ' -f4");
	std::stringstream tmp;
	tmp << (atoi(_ramUsage.c_str()) + atoi(_ramInfo.c_str())) << "M" << std::endl;
	_ramInfo = tmp.str();
	_netIn = exec("top -l 1 | grep 'Networks:' |  cut -d' ' -f3");
	_netIn = _netIn.substr(0, _netIn.find("/", 0));
	_netOut = exec("top -l 1 | grep 'Networks:' |  cut -d' ' -f5");
	_netOut = _netOut.substr(0, _netOut.find("/", 0));
}

std::string OSInfo::getUserInfo ( void ) const
{
	return (this->_userInfo);
}

std::string OSInfo::getHostInfo ( void ) const
{
	return (this->_hostInfo);
}

std::string OSInfo::getOsInfo ( void ) const
{
	return (this->_osInfo);
}

std::string OSInfo::getDateInfo ( void ) const
{
	return (this->_dateInfo);
}

std::string OSInfo::getCpuInfo ( void ) const
{
	return (this->_cpuInfo);
}

std::string OSInfo::getCpuUsage ( void ) const
{
	return (this->_cpuUsage);
}

std::string OSInfo::getRamInfo ( void ) const
{
	return (this->_ramInfo);
}

std::string OSInfo::getRamUsage ( void ) const
{
	return (this->_ramUsage);
}

std::string OSInfo::getNetIn ( void ) const
{
	return (this->_netIn);
}

std::string OSInfo::getNetOut ( void ) const
{
	return (this->_netOut);
}
