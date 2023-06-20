#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <filesystem>

#include "json.hpp"
#include "KompozytUAR.h"
#include "KompozytSzeregowy.h"
#include "KompozytRownolegly.h"
#include "ModelARX.h"
#include "RegulatorPID.h"
#include "ParametrySyg.h"

using json = nlohmann::json;
using namespace nlohmann::literals;

void ZapisDoPliku(std::ofstream& out_file, std::filesystem::path& path, json& j_out);

bool sprawdzCzyIstniejeFolder(std::filesystem::path& path, std::string& response);

void odczytJSON(std::ifstream& f, KompozytUAR& UAR, ParametrySyg& params);

void stworzKompozyt(KompozytUAR& UAR, json& data);

//void ZapisJSON(KompozytUAR& UAR, ParametrySyg& params);


