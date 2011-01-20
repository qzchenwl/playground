echo $1
sudo ifconfig $1 up
sudo route add -host 8.8.8.8 dev $1
