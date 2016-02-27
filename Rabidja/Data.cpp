#include <iostream>
#include "Data.h"

using namespace std;

Data* Data::m_instance = nullptr;

Data::Data()
{
	cout << "Creation" << endl;
}

Data::~Data()
{
	cout << "Destruction" << endl;
}

Data* Data::Instance()
{
	if (m_instance == nullptr)
		m_instance = new Data();
	return m_instance;
}