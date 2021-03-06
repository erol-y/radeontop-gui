#! /bin/bash

#path_sbin="/usr/sbin/"
#path_devel=""
SUDO=
INSTALLED=
exec=
XHOST=

while [ ! -z "$1" ]; do

    PARAM=$1
    case ${PARAM} in
		-r|--root)
		SUDO="sudo"
		;;

		-i|--installed)
		if [ -f /usr/sbin/radeontop-gui.v1 ]; then
			#exec="/usr/sbin/radeontop-gui.v1"
			INSTALLED="1"
		else
			echo "radeontop-gui not found! Try to (re)install."
			exit 1
		fi
		;;

		-x|--xhost)
		XHOST="1"
		;;

		-*)
		echo "\
Options:
-r, --root			Run with root priv.
-i, --installed		Run installed copy , instead of local.
-x, --xhost			Deactivate xhost."
		exit 1
		;;

	esac
	shift
done

if [ ! -z $INSTALLED ]; then
	exec="/usr/sbin/radeontop-gui.v1"
else

### First, try to run debug version.
	if [ -f ./out/bin/Debug/radeontop-gui ]; then
		exec="./out/bin/Debug/radeontop-gui"

	elif [ -f ./out/bin/Release/radeontop-gui ]; then
		exec="./out/bin/Release/radeontop-gui"

### Check where the script runs from.
	elif [[ $0 == /usr/sbin* ]]; then
		exec="/usr/sbin/radeontop-gui.v1"

	else
		echo "Exec file can not found."
		echo "$0"
		exit 1
	fi
fi

### Run Time!
if [ ! -z $XHOST ]; then
	xhost +
fi

$SUDO $exec

if [ ! -z $XHOST ]; then
	xhost -
fi

exit 0

