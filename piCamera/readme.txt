// load bcm driver before run a programm
sudo modprobe bcm2835-v4l2
// frame rate set to 90.000 fps
v4l2-ctl -p 80
