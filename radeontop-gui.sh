#! /bin/bash

xhost +

if [ ./bin/Debug/radeontop-gui ]; then
	sudo ./bin/Debug/radeontop-gui
else
	sudo ./bin/Release/radeontop-gui
fi

xhost -

