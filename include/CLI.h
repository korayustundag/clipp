#pragma once
#include <Windows.h>
#include <string>
#include "Colors.h"

#ifndef CLI__FRAMEWORK__X64
#define CLI__FRAMEWORK__X64

namespace CLI
{
	class Console
	{
	public:
		Console();
		void Write(const wchar_t* text)
		{
			WriteConsoleW(ConsoleOutputHandle, text, static_cast<DWORD>(std::wcslen(text)), 0, 0);
		}

		void Write(std::wstring& text)
		{
			WriteConsoleW(ConsoleOutputHandle, text.c_str(), static_cast<DWORD>(text.size()), 0, 0);
		}

		void WriteLine()
		{
			WriteConsoleW(ConsoleOutputHandle, NewLine.c_str(), static_cast<DWORD>(NewLine.size()), 0, 0);
		}

		void WriteLine(const wchar_t* text)
		{
			WriteConsoleW(ConsoleOutputHandle, text, static_cast<DWORD>(std::wcslen(text)), 0, 0);
			WriteLine();
		}

		void WriteLine(std::wstring& text)
		{
			WriteConsoleW(ConsoleOutputHandle, text.c_str(), static_cast<DWORD>(text.size()), 0, 0);
			WriteLine();
		}

		std::wstring ReadLine()
		{
			DWORD dwRead = 0;
			WCHAR buf[1024] = { 0 };
			std::wstring line;
			ReadConsole(ConsoleInputHandle, buf, ARRAYSIZE(buf), &dwRead, nullptr);
			line.assign(buf, static_cast<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>::size_type>(dwRead) - 2);

			return line;
		}

		std::wstring ReadPasswordLine()
		{
			DWORD dwMode = 0;
			DWORD dwRead = 0;
			WCHAR buf[1024] = { 0 };
			std::wstring line;
			GetConsoleMode(ConsoleInputHandle, &dwMode);
			SetConsoleMode(ConsoleInputHandle, dwMode & (~ENABLE_ECHO_INPUT));
			ReadConsole(ConsoleInputHandle, buf, ARRAYSIZE(buf), &dwRead, nullptr);
			line.assign(buf, static_cast<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>::size_type>(dwRead) - 2);
			SetConsoleMode(ConsoleInputHandle, dwMode);
			Write(L"\r\n");
			return line;
		}

		void SetForegroundColor(CLI::Colors::Color color)
		{
			SetConsoleTextAttribute(ConsoleOutputHandle, color);
		}

		void ResetColor()
		{
			SetConsoleTextAttribute(ConsoleOutputHandle, csbi.wAttributes);
		}

		~Console();

	private:
		HANDLE ConsoleOutputHandle;
		HANDLE ConsoleInputHandle;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		std::wstring NewLine;
	};

	Console::Console()
	{
		ConsoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		ConsoleInputHandle = GetStdHandle(STD_INPUT_HANDLE);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		NewLine = L"\r\n";
	}

	Console::~Console()
	{
		if (ConsoleInputHandle)
		{
			CloseHandle(ConsoleInputHandle);
			ConsoleInputHandle = nullptr;
		}
		if (ConsoleOutputHandle)
		{
			CloseHandle(ConsoleOutputHandle);
			ConsoleOutputHandle = nullptr;
		}
	}
}

#endif