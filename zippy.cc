/*
	Zippy, a Z80 Emulator
	==========================================
	Copyright (c) 2019, Bradan J. Wolbeck (CompaqDisc)
	https://www.compaqdisc.com/projects/zippy/

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <iostream>
#include <string>
#include "machine/machine.h"

int main(int argc, char** argv) {
	/*
	Some basic flag testing, user must pass atleast these params:
			-m, --machine   In-built machine type, or machine description file.
				[default, rc2014]
			-b, --blast	 Run at the full speed achievable by the host.
	*/

	std::cout << "Zippy, a Z80 Emulator" << std::endl
		<< "Copyright (c) 2019, "
		<< "Bradan J. Wolbeck (CompaqDisc) <bwolbeck@compaqdisc.com>"
		<< std::endl << std::endl;

	Machine machine_ = Machine();
	machine_.Start();

	return 0;
}