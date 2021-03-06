#include <iostream>
#include <filesystem>

using namespace std::experimental::filesystem;
using namespace std;

void IspisiSadrzajKazala(const path& kazalo)
{
	using dirIt = directory_iterator;
	// prolazimo sve stavke u kazalu:
	for (dirIt iter(kazalo); iter != dirIt(); ++iter)
	{
		// ako je podkazalo...
		if (is_directory(iter->path()))
		{
			// ... ispiši ime ...
			cout << "kazalo:   " << iter->path() << endl;
			// te rekurzivno pozovi funkciju da se ispiše
			// sadržaj tog podkazala
			IspisiSadrzajKazala(*iter);
		}
		if (is_regular_file(iter->path()))
			cout << "datoteka: " << iter->path() << endl;
	}
}


int main()
{
	IspisiSadrzajKazala(R"(d:\Tools)");
    
	return 0; 
}

