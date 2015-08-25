#include <ClanLib/application.h>

#include "IMApplication.h"

class Program
{
public:
	static int main(const std::vector<CL_String> &args)
	{
		setlocale(LC_ALL, "");

		return IMApplication::run(args);
	}
};

CL_ClanApplication app(&Program::main);