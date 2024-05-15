#include "include/CLI.h"

int main()
{
	CLI::Console* c = new CLI::Console();

	c->WriteLine(L"Welcome to CLI");
	c->WriteLine();
	c->WriteLine(L"--User Login----");

	c->Write(L"Username: ");
	std::wstring username = c->ReadLine();

	c->Write(L"Password: ");
	std::wstring password = c->ReadPasswordLine();

	c->SetForegroundColor(CLI::Colors::Color::RED);
	c->WriteLine(username);

	c->SetForegroundColor(CLI::Colors::Color::GREEN);
	c->WriteLine(password);

	c->ResetColor();

	c->Write(L"Press [enter] to exit...");
	c->ReadLine();

	delete c;
	return 0;
}