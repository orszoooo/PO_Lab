#include "Utils.h"

//void ZapisJSON(KompozytUAR& UAR, ParametrySyg& params)
//{
//	std::string response = "";
//	std::cout << "Czy zapisac parametry regulatora i modelu do pliku? (y/N): ";
//	std::cin >> response;
//	std::cout << std::endl;
//
//	if (response.find("y") != std::string::npos) {
//		std::cout << "Podaj sciezke do folderu docelowego: ";
//		std::cin >> response;
//		std::cout << std::endl;
//		auto path = std::filesystem::path(response);
//
//		if (!path.empty()) {
//
//			json j_out;
//			j_out["PID"] = { { "P",reg1.get_k() },{ "I", reg1.get_Ti() },{ "D",reg1.get_Td() } };
//			j_out["ARX"] = { { "A", arx1.getWspolWielA() },{ "B", arx1.getWspolWielB() },{ "k", arx1.getOpoznienieT() },
//				{ "OdchStd", arx1.getOdchStd() } };
//			j_out["Skok Jednostkowy"] = { { "Amplituda", params.amplitudaSkokJed },{ "Czas skoku", params.czasSkoku },
//				{ "Start", params.startSkokJed },{ "Koniec", params.koniecSkokJed } };
//			j_out["Sinusoida"] = { { "Amplituda", params.amplitudaSin },{ "Okres", params.okres },{ "Start", params.startSin },
//				{ "Koniec", params.koniecSin } };
//			j_out["Szum"] = { { "Start", params.startSzum },{ "Koniec", params.koniecSzum } };
//
//			//Sprawdzenie czy folder istnieje
//			bool folder_exists = sprawdzCzyIstniejeFolder(path, response);;
//
//			//Zapis do pliku
//			std::cout << "Podaj nazwe pliku(musi konczyc sie na .json!): ";
//			std::cin >> response;
//			std::cout << std::endl;
//
//			std::ofstream out_file;
//			path += "\\" + response;
//			if (std::filesystem::exists(path))
//			{
//				std::cout << "Uwaga! Chcesz nadpisac istniejacy plik! Czy chcesz kontynuowac? (y/N): ";
//				std::cin >> response;
//				std::cout << std::endl;
//
//				if (response.find("y") != std::string::npos)
//				{
//					ZapisDoPliku(out_file, path, j_out);
//				}
//				else
//				{
//					std::cout << "Anulowano zapis do pliku!" << std::endl;
//				}
//				out_file.close();
//			}
//			else
//			{
//				ZapisDoPliku(out_file, path, j_out);
//			}
//
//		}
//
//	}
//}

void odczytJSON(std::ifstream& f, KompozytUAR& UAR, ParametrySyg& params)
{
	if (f.is_open()) {
		json data = json::parse(f);

		stworzKompozyt(UAR, data);

		//Generator Wzorzec Dekorator
		//Skok Jednostkowy
		params.amplitudaSkokJed = data.at("Skok Jednostkowy").at("Amplituda");
		params.czasSkoku = data.at("Skok Jednostkowy").at("Czas skoku");
		params.startSkokJed = data.at("Skok Jednostkowy").at("Start");
		params.koniecSkokJed = data.at("Skok Jednostkowy").at("Koniec");

		//Sinusoida
		params.amplitudaSin = data.at("Sinusoida").at("Amplituda");
		params.okres = data.at("Sinusoida").at("Okres");
		params.startSin = data.at("Sinusoida").at("Start");
		params.koniecSin = data.at("Sinusoida").at("Koniec");

		//Szum
		params.startSzum = data.at("Szum").at("Start");;
		params.koniecSzum = data.at("Szum").at("Koniec");;
	}
}

void stworzKompozyt(KompozytUAR& UAR, json& data) {
	//Typ pêtli
	UAR.setTyp(data.at("UAR").at("Typ"));

	//Tworzenie kompozytu
	Komponent* kompSzereg = new KompozytSzeregowy();
	Komponent* arx1 = new ModelARX(
		data.at("/UAR/Pojemnik/KompozytSzereg/ARX1/A"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytSzereg/ARX1/B"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytSzereg/ARX1/OdchStd"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytSzereg/ARX1/k"_json_pointer)
	);

	kompSzereg->dodaj(arx1);

	Komponent* arx2 = new ModelARX(
		data.at("/UAR/Pojemnik/KompozytSzereg/ARX2/A"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytSzereg/ARX2/B"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytSzereg/ARX2/OdchStd"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytSzereg/ARX2/k"_json_pointer)
	);

	kompSzereg->dodaj(arx2);

	UAR.dodaj(kompSzereg);

	Komponent* kompRown = new KompozytRownolegly();
	Komponent* arx3 = new ModelARX(
		data.at("/UAR/Pojemnik/KompozytRown/ARX3/A"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytRown/ARX3/B"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytRown/ARX3/OdchStd"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytRown/ARX3/k"_json_pointer)
	);

	kompRown->dodaj(arx3);

	Komponent* arx4 = new ModelARX(
		data.at("/UAR/Pojemnik/KompozytRown/ARX4/A"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytRown/ARX4/B"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytRown/ARX4/OdchStd"_json_pointer),
		data.at("/UAR/Pojemnik/KompozytRown/ARX4/k"_json_pointer)
	);

	kompRown->dodaj(arx4);

	UAR.dodaj(kompRown);

	Komponent* PID = new RegulatorPID(
		data.at("/UAR/PID/P"_json_pointer),
		data.at("/UAR/PID/I"_json_pointer),
		data.at("/UAR/PID/D"_json_pointer)
	);

	UAR.dodaj(PID);
}

bool sprawdzCzyIstniejeFolder(std::filesystem::path& path, std::string& response)
{
	if (!std::filesystem::exists(path))
	{
		std::cout << "Uwaga! Podany katalog nie istnieje! Czy chcesz kontynuowac i utworzyc katalog? (y/N): ";
		std::cin >> response;
		std::cout << std::endl;

		if (response.find("y") != std::string::npos)
		{
			std::filesystem::create_directories(path);
			std::cout << "Utworzono katalog!" << std::endl;
			return true;
		}
		else
		{
			std::cout << "Anulowano zapis do pliku!" << std::endl;
			return false;
		}
	}
	else
	{
		return true;
	}
}
void ZapisDoPliku(std::ofstream& out_file, std::filesystem::path& path, json& j_out)
{
	out_file.open(path);

	if (out_file)
	{
		std::cout << "Zapisano! :)" << std::endl;
		out_file << std::setw(4) << j_out << std::endl;
	}
	else
	{
		std::cout << "Zapis zakonczony niepowodzeniem! :(" << std::endl;
	}
}