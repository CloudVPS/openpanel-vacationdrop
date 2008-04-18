#include <grace/application.h>
#include <grace/filesystem.h>

#define PATH_CONF_RCPTS "/etc/vacationdrop/recipients"
#define PATH_SENDERDB "/var/db/vacation"

class setvacationApp : public application
{
public:
	setvacationApp (void) : application ("setvacation")
	{
		opt["-s"]["long"] = "--subject";
		opt["-r"]["long"] = "--rcpt";
		opt["--subject"]["argc"] = 1;
		opt["--rcpt"]["argc"] = 1;
		opt["--unset"]["argc"] = 0;
	}
	
	~setvacationApp (void)
	{
	}
	
	int usage (void)
	{
		ferr.writeln ("Usage: setvacation [options] < vacationmessage");
		ferr.writeln ("options:");
		ferr.writeln ("  --rcpt recipient-address");
		ferr.writeln ("  --subject subject-line");
		ferr.writeln (" [--unset]");
		return 1;
	}
	
	int main (void)
	{
		string rcpt;

		if (! argv.exists ("--rcpt")) return usage ();
		rcpt = argv["--rcpt"];
				
		string rfn = PATH_CONF_RCPTS "/%s" %format (rcpt);
		string sdbfn = PATH_SENDERDB "/%s" %format (rcpt);
		
		if (argv.exists ("--unset"))
		{
			fs.rm (rfn);
			fs.rm (sdbfn);
			return 0;
		}
		
		string body;
		
		while (! fin.eof())
		{
			body.strcat (fin.read(1024));
		}
		
		value v;
		v["subject"] = argv["--subject"];
		v["body"] = body;
		
		fout.writeln ("Saving to %s" %format (rfn));
		
		v.savexml (rfn);
		return 0;
	}
};

APPOBJECT(setvacationApp);
