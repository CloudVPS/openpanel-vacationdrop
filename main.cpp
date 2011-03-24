// This file is part of OpenPanel - The Open Source Control Panel
// OpenPanel is free software: you can redistribute it and/or modify it 
// under the terms of the GNU General Public License as published by the Free 
// Software Foundation, using version 3 of the License.
//
// Please note that use of the OpenPanel trademark may be subject to additional 
// restrictions. For more information, please visit the Legal Information 
// section of the OpenPanel website on http://www.openpanel.com/

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
	
	if (! fs.exists (rfn)) return startMaildrop (sender, rcpt);
	
	value conf;
	conf.loadxml (rfn);

	if (! db.open (sdbfn)) return startMaildrop (sender, rcpt);
	if (db.db.exists (sender))
	{
		db.close ();
		return startMaildrop (sender, rcpt);
	}
	
	db.db[sender] = "on";
	db.commit ();
	db.close ();
	
	smtpsocket s;
	
	s.setsmtphost ("localhost");
	s.setsender ("MAILER-DAEMON", "Autoresponder");
	s.sendmessage (sender, conf["subject"], conf["body"]);
	
	return startMaildrop (sender, rcpt);
}

int vacationdropApp::startMaildrop (const string &sender, const string &rcpt)
{
	if (argv.exists ("--nomaildrop")) return 0;
	::execlp ("/usr/bin/maildrop", "maildrop", "-f", sender.cval(), "-d", rcpt.cval(), NULL);
	return 1;
}
