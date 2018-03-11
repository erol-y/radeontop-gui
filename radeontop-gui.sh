#! /bin/bash

xhost +

if [ -f ./radeontop-gui.v1 ]; then
	sudo ./radeontop-gui.v1
elseif [ ./bin/Debug/radeontop-gui ]
	sudo ./bin/Debug/radeontop-gui
else
	sudo ./bin/Release/radeontop-gui
fi

xhost -

