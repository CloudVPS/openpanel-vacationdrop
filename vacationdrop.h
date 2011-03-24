// This file is part of OpenPanel - The Open Source Control Panel
// OpenPanel is free software: you can redistribute it and/or modify it 
// under the terms of the GNU General Public License as published by the Free 
// Software Foundation, using version 3 of the License.
//
// Please note that use of the OpenPanel trademark may be subject to additional 
// restrictions. For more information, please visit the Legal Information 
// section of the OpenPanel website on http://www.openpanel.com/

#ifndef _vacationdrop_H
#define _vacationdrop_H 1
#include <grace/application.h>

//  -------------------------------------------------------------------------
/// Main application class.
//  -------------------------------------------------------------------------
class vacationdropApp : public application
{
public:
		 	 vacationdropApp (void) :
				application ("com.openpanel.tools.vacationdrop")
			 {
			 	opt["-n"]["long"] = "--nomaildrop";
			 	opt["--nomaildrop"]["argc"] = 0;
			 }
			~vacationdropApp (void)
			 {
			 }

	int		 main (void);
	int		 startMaildrop (const string &);
};

#endif
