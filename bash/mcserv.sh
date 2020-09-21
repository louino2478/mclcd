screen -d -m -S arduino /dev/ttyUSB0 9600
screen -d -m -S mc
sleep 0.5
screen -S mc -X stuff "cd /home/pi/Desktop/mc^M"
sleep 0.3
screen -S mc -X stuff "java -Xmx512M -XX:+AlwaysPreTouch -XX:+DisableExplicitGC -XX:+UseG1GC -XX:+UnlockExperimentalVMOptions -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=4M -XX:TargetSurvivorRatio=90 -XX:G1NewSizePercent=50 -XX:G1MaxNewSizePercent=80 -XX:InitiatingHeapOccupancyPercent=10 -XX:G1MixedGCLiveThresholdPercent=50 -XX:+AggressiveOpts -jar server.jar --nogui^M"
sleep 4.5
screen -S arduino -X stuff "ready"
sleep 2
while true
do
  screen -S arduino -X stuff "ip: `ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1'`"
  sleep 0.1
  screen -S arduino -X stuff "`sed -n 1p /home/pi/Desktop/mc/plugins/lcd-link/config.yml`"
  sleep 0.1
  screen -S arduino -X stuff "`sed -n 2p /home/pi/Desktop/mc/plugins/lcd-link/config.yml`"
  sleep 0.1
  screen -S arduino -X stuff "`sed -n 3p /home/pi/Desktop/mc/plugins/lcd-link/config.yml`"
  sleep 0.1
  screen -S arduino -X stuff "`sed -n 4p /home/pi/Desktop/mc/plugins/lcd-link/config.yml`"
  sleep 0.1
done