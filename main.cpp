#include "vacationdrop.h"
#include <grace/filesystem.h>
#include <dbfile/db4file.h>
#include <grace/smtp.h>
#include <syslog.h>

APPOBJECT(vacationdropApp);

#define PATH_CONF "/etc/vacationdrop"
#define PATH_CONF_RCPTS "/etc/vacationdrop/recipients"
#define PATH_SENDERDB "/var/db/vacation"

//  =========================================================================
/// Main method.
//  =========================================================================
int vacationdropApp::main (void)
{
	string rcpt;
	statstring sender;
	db4file db;
	db.setencoding (dbfile::flat);
	
	if (argv["*"].count() < 2)
	{
		ferr.writeln ("Usage: vacationdrop <rcpt> <sender>");
		return 1;
	}
	
	openlog ("vacationdrop", 0, LOG_MAIL);
	
	// FIXME sanitize
	rcpt = argv["*"][0];
	sender = argv["*"][1];
	
	syslog (LOG_ERR, "Invoked rcpt=<%s> sender=<%s>", rcpt.str(), sender.str());
	
	string rfn = PATH_CONF_RCPTS "/%s" %format (rcpt);
	string sdbfn = PATH_SENDERDB "/%s" %format (rcpt);
	
	if (! fs.exists (rfn)) return startMaildrop (rcpt);
	
	value conf;
	conf.loadxml (rfn);

	if (! db.open (sdbfn)) return startMaildrop (rcpt);
	if (db.db.exists (sender))
	{
		db.close ();
		return startMaildrop (rcpt);
	}
	
	db.db[sender] = "on";
	db.commit ();
	db.close ();
	
	smtpsocket s;
	
	s.setsmtphost ("localhost");
	s.setsender ("MAILER-DAEMON", "Autoresponder");
	s.sendmessage (sender, conf["subject"], conf["body"]);
	
	return startMaildrop (rcpt);
}

int vacationdropApp::startMaildrop (const string &rcpt)
{
	::execlp ("/usr/bin/maildrop", "maildrop", "-d", rcpt.cval(), NULL);
	return 1;
}
