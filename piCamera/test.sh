# load bcm driver before run a programm
sudo modprobe bcm2835-v4l2
# frame rate set to 90.000 fps
v4l2-ctl -p 90
#.............
v4l2-ctl --all | grep 'Frames\|Width'
echo "......"
vcgencmd measure_temp
vcgencmd measure_clock arm
echo "......"
for src in arm core h264 isp v3d uart pwm emmc pixel vec hdmi dpi ; do \
	echo -e "$src:\t$(vcgencmd measure_clock $src)" ; \
done
echo "....."
for id in core sdram_c sdram_i sdram_p ; do \
	echo -e "$id:\t$(vcgencmd measure_volts $id)" ; \
done

