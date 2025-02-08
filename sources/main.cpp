#include "../includes/Scop.h"

int main()
{
    try
    {
        Scop();
    }
    catch(const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
}
