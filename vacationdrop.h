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
			 	
			 }
			~vacationdropApp (void)
			 {
			 }

	int		 main (void);
	int		 startMaildrop (const string &);
};

#endif
