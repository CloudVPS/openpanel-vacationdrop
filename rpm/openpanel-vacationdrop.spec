# This file is part of OpenPanel - The Open Source Control Panel
# OpenPanel is free software: you can redistribute it and/or modify it 
# under the terms of the GNU General Public License as published by the Free 
# Software Foundation, using version 3 of the License.
#
# Please note that use of the OpenPanel trademark may be subject to additional 
# restrictions. For more information, please visit the Legal Information 
# section of the OpenPanel website on http://www.openpanel.com/

%define version 0.8.0

%define libpath /usr/lib
%ifarch x86_64
  %define libpath /usr/lib64
%endif

Summary: vacationdrop
Name: vacationdrop
Version: %version
Release: 1
License: GPLv2
Group: Development
Source: http://packages.openpanel.com/archive/vacationdrop-%{version}.tar.gz
BuildRoot: /var/tmp/%{name}-buildroot
Requires: openpanel-mod-postfixcourier

%description
vacationdrop
Tool that keeps track of autoresponding in the maildrop delivery chain.

%prep
%setup -q -n vacationdrop-%version

%build
BUILD_ROOT=$RPM_BUILD_ROOT
./configure
make

%install
BUILD_ROOT=$RPM_BUILD_ROOT
rm -rf ${BUILD_ROOT}
mkdir -p ${BUILD_ROOT}/usr/bin
mkdir -p ${BUILD_ROOT}/etc/vacationdrop/recipients
mkdir -p ${BUILD_ROOT}/var/db/vacation
install -m 755 vacationdrop ${BUILD_ROOT}/usr/bin/vacationdrop
install -m 755 setvacation ${BUILD_ROOT}/usr/bin/setvacation

%post
chown vmail /var/db/vacation

%files
%defattr(-,root,root)
/
