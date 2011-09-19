/**
 * 
 */
module dfilt;

import core.demangle;
import std.stdio;
import std.ctype;

int main(string[] args)
{
	// read from stdin?
	if (args.length < 2)
	{
		// TODO: what's the maximum length of a mangled D symbol?
		// use a static array to avoid senseless reallocations
		char[1024] buffer; short idx;
		bool inword = false;

		foreach(c; LockingTextReader(stdin))
		{
			if (!inword)
			{
				if (c == '_') // || isalpha(c)) // TODO: can names start without _?
				{
					inword = true;
					idx = 0;
					buffer[idx++] = cast(char) c;
				}
				else
					write(cast(char) c);
			}
			else
			{
				// inside the name numbers are allowed
				if (c == '_' || isalnum(c))
					buffer[idx++] = cast(char) c;
				else
				{
					inword = false;
					write(demangle(cast(string)buffer[0..idx]), cast(char) c);
				}
			}
		}
		if (inword)
			write(demangle(cast(string)buffer[0..idx]));
	}
	else
	{
		// there's at least one command-line argument

		if (args[1] == "--help" || args[1] == "-h")
			displayUsage();
		else
			// mangled names are given via the command line
			foreach (arg; args[1..$])
			{
				writeln(demangle(arg));
			}
	}

	return 0;
}

void displayUsage()
{
	write(`Demangles D symbol names.

            Usage: dfilt [options] [mangled names]
            Options are:
              [-h|--help] Display this information

            Demangled names are written to stdout.
            If a name can't be demangled it is just echoed.
            If the command line is empty, stdin is read.
`);
}
