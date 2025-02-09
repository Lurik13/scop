#include "../includes/Window.h"

int main()
{
    try
    {
        Window();
    }
    catch(const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
}
