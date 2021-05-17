#pragma once

#include "home-work-5-core.h"

#include <windows.h>
#include <string>
#include <sstream>
#include <cstdint>

using std::wstring;
using std::wstringstream;
using std::ostream;

static HWND curOutputWnd = nullptr;

// Helpers
void error(wstring errMsg, int errCode = -1) {
	//std::wcerr << errMsg << std::endl;
	MessageBox(nullptr, errMsg.data(), L"Error", MB_OK | MB_ICONERROR);
	exit(errCode);
}
void Output(const wstring& text) {
	SetWindowText(curOutputWnd, text.data());
}

void SetOutputWnd(HWND hwnd) {
	curOutputWnd = hwnd;
}

template<typename T>
void OutputNumsArray(T arNUms[], size_t arSize) {
	wstringstream sout;
	output_array(sout, arNUms, arSize);
	Output(sout.str());
}
// end Helpers

// Home work
void OutputDoubleArray(double arDouble[], size_t arSize) {
	OutputNumsArray(arDouble, arSize);
}

void OutputXorArray(uint8_t arBits[], size_t arSize) {
	xor_array(arBits, arSize);
	OutputNumsArray(arBits, arSize);
}

void OutputFillArrayByStep3(int arInts[], size_t arSize) {
	fill_array_step3(arInts, arSize);
	OutputNumsArray(arInts, arSize);
}

template<typename T, size_t ArSize>
void OutputRotateArray(T (&arInts)[ArSize], int64_t n) {
	rotate_array(arInts, ArSize, n);
	OutputNumsArray(arInts, ArSize);
}

template<typename T, size_t ArSize>
void OutputIsBalanceArray(T(&arInts)[ArSize]) {
	bool bBalance = is_balance_array(arInts, ArSize);
	wstring res = bBalance ? L"array is balanced" : L"array is not balanced";
	Output(res);
}
