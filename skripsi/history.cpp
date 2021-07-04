sudo apt install tree
  117  tree include/v2.0
  118  l
  119  tree include/v2.0
  120  cd v2.0
  121  cd ..
  122  l
  123  cd mav
  124  cd mavlink
  125  l
  126  sudo apt install tree
  127  tree include/v2.0
  128  ssh ubuntu@10.42.0.1
  129  exit
  130  cd catkin_ws/
  131  l
  132  cd src/
  133  l
  134  cd qr_scanning_drones/
  135  l
  136  cd quirc/
  137  l
  138  cd ../../..
  139  l
  140  cd devel/
  141  l
  142  cd ..
  143  cd build/
  144  l
  145  sudo rm -rf qr_scanning_drones/
  146  cd ..
  147  cd src/
  148  l
  149  sudo rm -rf qr_scanning_drones/
  150  l
  151  cd
  152  sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" > /etc/apt/sources.list.d/ros-latest.list'
  153  wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
  154  sudo apt update
  155  sudo apt-get install ros-kinetic-desktop-full ros-kinetic-joy ros-kinetic-octomap-ros ros-kinetic-mavlink python-wstool python-catkin-tools protobuf-compiler libgoogle-glog-dev ros-kinetic-control-toolbox ros-kinetic-mavros
  156  sudo aptt install ros-kinetic-simulators
  157  sudo apt install ros-kinetic-simulators
  158  sudo apt install ros-kinetic-gazebo-ros-pkgs ros-kinetic-simulators
  159  sudo apt install ros-kinetic-gazebo-dev ros-kinetic-gazebo-msgs ros-kinetic-gazebo-plugins ros-kinetic-gazebo-ros ros-kinetic-gazebo-ros-pkgs ros-kinetic-simulators
  160  sudo apt install gazebo7 libgazebo7-dev libgazebo7 libignition-math2 libsdformat4 libgazebo7 libsdformat4 ros-kinetic-gazebo-dev ros-kinetic-gazebo-msgs ros-kinetic-gazebo-plugins ros-kinetic-gazebo-ros ros-kinetic-gazebo-ros-pkgs ros-kinetic-simulators
  161  sudo apt-get install ros-kinetic-desktop-full ros-kinetic-joy ros-kinetic-octomap-ros ros-kinetic-mavlink python-wstool python-catkin-tools protobuf-compiler libgoogle-glog-dev ros-kinetic-control-toolbox ros-kinetic-mavros
  162  sudo rosdep init
  163  rosdep update
  164  source /opt/ros/kinetic/setup.bash
  165  cd catkin_ws/
  166  cd src/
  167  catkin_init_workspace
  168  wstool init
  169  wget https://raw.githubusercontent.com/ethz-asl/rotors_simulator/master/rotors_hil.rosinstall
  170  l
  171  wstool merge rotors_hil.rosinstall
  172  l
  173  wstool merge rotors_hil.rosinstall
  174  sudo wstool merge rotors_hil.rosinstall
  175  wstool merge rotors_hil.rosinstall
  176  wstool update
  177  l
  178  cd ..
  179  catkin_make
  180  catkin_make_isolated
  181  catkin_make_isolated -j4
  182  catkin_make
  183  git clone https://github.com/mavlink/mavlink-gbp-release -b release/kinetic/mavlink
  184  cd src
  185  git clone https://github.com/mavlink/mavlink-gbp-release -b release/kinetic/mavlink
  186  mkdir mavlink-gbp-release/build
  187  l
  188  cd mavlink-gbp-release/build
  189  cmake ..
  190  make
  191  cd ../..
  192  cd ..
  193  catkin_make
  194  catkin_make_isolated
  195  l
  196  catkin_make_isolated
  197  catkin build
  198  catkin_make
  199  roslaunch rotors_gazebo mav_qr_code_scan2.launch
  200  roslaunch rotors_gazebo mav_hovering_example.launch mav_name:=firefly world_name:=basic
  201  cd src
  202  cd
  203  ssh ubuntu@10.42.0.1
  204  ssh yazid@10.42.0.1
  205  sudo ssh ubuntu@10.42.0.1
  206  ssh ubuntu@10.42.0.1
  207  service networking restart
  208  ssh ubuntu@10.42.0.1
  209  cd /etc/ssh/
  210  l
  211  cd
  212  cd /ssh
  213  cd .ssh/
  214  l
  215  nano known_hosts 
  216  cd
  217  ssh ubuntu@10.42.0.1
  218  ssh ubuntu@10.42.0.2
  219  cd .ssh/
  220  nano authorizedkeys
  221  l
  222  cd
  223  ssh ubuntu@10.42.0.1
  224  ifconfig
  225  ssh ubuntu@10.42.0.181
  226  ssh ubuntu@10.42.0.1
  227  ip a
  228  ifconfig enp2s0 down
  229  sudo ifconfig enp2s0 down
  230  ssh ubuntu@10.42.0.1
  231  sudo ifconfig eth0 192.168.10.10 netmask 255.255.255.0
  232  ifconfig
  233  service networking start
  234  ifconfig
  235  ip a
  236  ifconfig 
  237  ssh ubuntu@10.42.0.1
  238  rm -rf .ssh
  239  ssh ubuntu@10.42.0.1
  240  pip install roslib
  241  python
  242  rostopic list
  243  sudo nano .bashrc
  244  fg
  245  sudo nano .bashrc
  246  rostopic list
  247  sudo nano .bashrc
  248  rostopic list
  249  sudo nano .bashrc
  250  rostopic list
  251  sudo nano .bashrc
  252  source .bashrc
  253  rostopic list
  254  roscd 
  255  cd
  256  cd catkin_ws/
  257  l
  258  catkin_make
  259  cd
  260  mkdir -p ~/catkin_ws_krti2020/devel
  261  cd catkin_ws_krti2020/
  262  catkin_make
  263  mkdir src
  264  catkin_make
  265  cd devel/
  266  l
  267  source setup.bash
  268  cd
  269  sudo nano .bashrc
  270  source .bashrc
  271  roscd
  272  cd
  273  cd cat
  274  cd catkin_ws
  275  cd
  276  cd catkin_ws
  277  cd
  278  cd catkin_ws_krti2020/
  279  catkin_make
  280  rosrun krti2020 qrpose_detection 
  281  catkin_make
  282  rosrun krti2020 qrpose_detection 
  283  catkin_make
  284  rosrun krti2020 qrpose_detection 
  285  rostopic list
  286  rosrun krti2020 qrpose_detection 
  287  rostopic list
  288  rosrun image_view image_view image:=/usb_cam1/image_raw
  289  rosrun image_view image_view image:=/usb_cam2/image_raw
  290  rosrun krti2020 qrpose_detection 
  291  ifconfig
  292  ip a
  293  ssh ubuntu@10.42.0.1
  294  cd Documents/
  295  python tfTest.py 
  296  python tfTest.py 
  297  gedit tfTest.py 
  298  python blockDetection.py 
  299  ls /dev/tty*
  300  ls /dev/video*
  301  ssh ubuntu@10.42.0.1
  302  rm -rf .ssh
  303  ssh ubuntu@10.42.0.1
  304  6 bc 7 n cv89s nm xc 67
  305  rosrun image_view image_view image:=/usb_cam2/image_raw compressed
  306  rosrun image_view image_view image:=/usb_cam2/image_raw 
  307  rostopic list
  308  ls
  309  locate object_detect
  310  cd catkin_ws_krti2020/
  311  ls
  312  catkin_make
  313  ls
  314  ls src/
  315  rosrun KRTI2020 qrpose_detection
  316  cd src/
  317  ls
  318  cd KRTI2020/
  319  ls
  320  ls scripts/
  321  ls src/
  322  rosrun  krti2020 qrpose_detection 
  323  l
  324  cd src
  325  l
  326  nano calib_results_catadioptric.txt 
  327  rosrun krti2020 qrpose_detection 
  328  roslaunch usb_cam usb_cam-test.launch 
  329  npm init
  330  npm init -y
  331  npm install cypress
  332  sudo npm install cypress
  333  node index.js --exec install
  334  sudo npm install cypress
  335  node index.js --exec install
  336  npm cypress open
  337  sudo code --user-data-dir
  338  sudo apt install nodejs-legacy
  339  sudo apt install npm
  340  sudo apt install nodejs
  341  ifconfig
  342  cd .ssr/
  343  l
  344  cd
  345  ssh ubuntu@ubiquityrobot.local
  346  sudo rm -rf .ssh
  347  ssh ubuntu@10.42.0.1
  348  ls
  349  cd .ssh
  350  l
  351  cd
  352  rm -rf .ssh
  353  ssh ubuntu@10.42.0.1
  354  rm -rf .ssh
  355  ssh ubuntu@10.42.0.1
  356  sudo ssh ubuntu@10.42.0.1
  357  sudo nano .bashrc
  358  ssh ubuntu@10.42.0.1
  359  ping 10.42.0.1
  360  ssh ubuntu@10.42.0.1
  361  ubuntu123
  362  ssh ubuntu@10.42.0.1
  363  nmap 10.42.0.1
  364  ssh ubuntu@10.42.0.1
  365  ssh ubiquity@10.42.0.1
  366  ssh ubuntu@10.42.0.1
  367  ssh pi@10.42.0.1
  368  sudo rm -rf .ssh
  369  sudo apt remove ssh\
  370  sudo apt remove ssh
  371  ssh pi@10.42.0.1
  372  ssh ubuntu@10.42.0.1
  373  sudo apt remove ssh-import-id 
  374  sudo reboot
  375  ssh ubuntu@10.42.0.1
  376  rm -rf .ssh
  377  ssh ubuntu@10.42.0.1
  378  ssh ubuntu@10.42.0.1
  379  sudo apt install ssh
  380  cd .ssh
  381  l
  382  sudo nano known_hosts 
  383  ssh ubuntu@10.42.0.1
  384  sudo apt update
  385  ssh ubuntu@10.42.0.1
  386  10.42.0.1
  387  ssh ubuntu@10.42.0.1
  388  cd
  389  PermitRootLogin yes
  390  AllowUsers otheruser
  391  service sshd restart
  392  ssh ubuntu@10.42.0.1
  393  exit
  394  ssh 10.42.0.1
  395  ssh ubuntu@10.42.0.1
  396  sudo reboot 
  397  sudo nano .bashrc
  398  source .bashrc
  399  ssh ubuntu@10.42.0.1
  400  ssh ubuntu@10.42.0.181
  401  ssh ubuntu@10.42.0.1
  402  rostopic list
  403  ssh ubuntu@10.42.0.1
  404  rostopic list
  405  sudo nano .bashrc
  406  rostopic list
  407  rosrun image_view image_view image:=/usb_cam2/image_raw compressed
  408  rosrun image_view image_view image:=/usb_cam2/image_raw compressed 
  409  ifconfig
  410  rostopic list
  411  roslaunch visp_auto_tracker tracklive_usb.launch 
  412  rosrun image_view image_view image:=/usb_cam2/image_raw compressed
  413  rosrun image_view image_view image:=/usb_cam2/image_raw
  414  ssh ubuntu@10.42.0.1
  415  sudo add-apt-repository universe
  416  sudo apt update
  417  sudo apt install putty
  418  sudo apt-get install putty
  419  ssh ubuntu@10.42.0.1
  420  sudo rm -rf .ssh/
  421  l
  422  cd .ssh
  423  ssh ubuntu@10.42.0.1
  424  rostopic list
  425  ssh ubuntu@10.42.0.1
  426  clear
  427  ssh ubuntu@10.42.0.1
  428  rostopic list
  429  ssh ubuntu@10.42.0.1
  430  rostopic list 
  431  rosrun krti2020 qrpose_detection 
  432  ssh ubuntu@10.42.0.1
  433  rostopic list 
  434  rosrun image_view image_view image:=/usb_cam2/image_raw
  435  rosrun image_view image_view image:=/usb_cam2/image_raw compressed
  436  rostopic list
  437  rosrun image_view image_view image:=/usb_cam2/image_raw compressed
  438  cd catkin_ws_krti2020/
  439  l
  440  cd sr
  441  cd src/
  442  l
  443  cd KRTI2020/
  444  l
  445  cd src/
  446  l
  447  cd
  448  roscd
  449  cd ..
  450  catkin_make
  451  l
  452  cd src/
  453  l
  454  cd ..
  455  cd
  456  cd catkin_ws_krti2020/
  457  l
  458  catkn_make
  459  catkin_make
  460  cd
  461  nano .inputrc
  462  source .inputrc 
  463  nano .inputrc
  464  source .inputrc 
  465  cd catkin_ws_krti2020/
  466  l
  467  cd src/KRTI2020/
  468  l
  469  cd src
  470  l
  471  sudo nano qrpose_detection.cpp 
  472  sudo code qrpose_detection.cpp --user-data-dir
  473  cd
  474  cd catkin_ws_krti2020/
  475  catkin_make
  476  rosrun krti2020 qrpose_detection 
  477  catkin_make
  478  rosrun krti2020 qrpose_detection 
  479  rosrun camera_calibration cameracalibrator.py
  480  rostopic list 
  481  rosrun camera_calibration cameracalibrator.py --size 6x5 --square 0.09 image:=/usb_cam2/image_raw camera:=/usb_cam2
  482  cd /tmp/
  483  l
  484  rosrun krti2020 qrpose_detection 
  485  ssh ubuntu@10.42.0.1
  486  sudo ssh ubuntu@10.42.0.1
  487  ubuntu
  488  sudo ssh ubuntu@10.42.0.1
  489  ssh ubuntu@10.42.0.1
  490  pip install roslib
  491  sudo pip install roslib
  492  ls /dev/tty*
  493  ssh ubuntu@10.42.0.1
  494  rostopic list
  495  echo /tf
  496  rostopic echo /tf
  497  ifconfig
  498  service networking restart 
  499  ifconfig 
  500  dronekit-sitl -copter
  501  dronekit-sitl -copter 1
  502  dronekit-sitl copter
  503  sudo apt remove python-pip
  504  sudo apt remove python2.7-pip
  505  sudo apt remove python2-pip
  506  sudo install python-roslib
  507  sudo apt install python-roslib
  508  sudo apt remove python-pip
  509  sudo apt install python-pip
  510  sudo apt update
  511  sudo apt install python-pip
  512  pip --version
  513  pip install python-roslib
  514  sudo pip install python-roslib
  515  pip install python-roslib
  516  pip install ros-kinetic-python-roslib
  517  udo apt-get install -y python-roslib
  518  sudo apt-get install -y python-roslib
  519  sudo apt-get update -y
  520  sudo apt-get install -y catkin
  521  sudo apt install -y python-catkin-pkg catkin python-roslib
  522  sudo apt install python-catkin-pkg catkin python-roslib
  523  sudo apt install catkin python-roslib
  524  sudo apt install python-roslib
  525  sudo apt install python-dev
  526  sudo pip install python-roslib
  527  python
  528  cd Documents/
  529  python Test01_Takeoffhoverland.py 
  530  ifconig
  531  ifconfig
  532  ls
  533  python Test01_Takeoffhoverland.py 
  534  pip --version
  535  sudo pip update
  536  cd
  537  /usr/bin/python2.7
  538  cd /usr/bin
  539  l
  540  mavproxy --master tcp:127.0.0.1:5760 --out udp:192.168.193.134:14551 --out udp:192.168.193.134:14550
  541  mavproxy.py --master tcp:127.0.0.1:5760 --out udp:192.168.193.134:14551 --out udp:192.168.193.134:14550
  542  pip --version
  543  cd /usr/local/lib/python2.7/dist-packages/
  544  l
  545  cd pip
  546  l
  547  cd ..
  548  sudo rm -rf pip
  549  pip --version
  550  l
  551  pip --version
  552  cd
  553  roscd roslib
  554  l
  555  pip install rospy
  556  pip install roslib
  557  /usr/bin/python /home/xyz/Documents/Test02_UpDownQR.py
  558  /usr/bin/python /home/xyz/Documents/Test01_Takeoffhoverland.py
  559  sudo nano .bashrc
  560  ls /dev/tty*
  561  ip a
  562  whereis python
  563  python --version
  564  which python
  565  python
  566  sudo code --user-data-dir
  567  sudo apt install roslib
  568  sudo apt install ros-kinetic-python-roslib
  569  sudo apt install python-roslib
  570  roscore
  571  source .bahsrc
  572  source .bashrc
  573  roscore
  574  pip install rospy
  575  pip install roslib
  576  mavproxy.py --master /dev/ttyUSB0 --out udp:127.0.0.1:14551 --out udp:127.0.0.1:14550
  577  ssh ubuntu@10.42.0.1
  578  sudo rm -rf .ssh
  579  ssh ubuntu@10.42.0.1
  580  sudo dpkg --
  581  ./bashrc
  582  l
  583  sudo apt update
  584  sudo apt install anydesk
  585  sudo killall
  586  sudo killall 
  587  sudo kill
  588  sudo apt install anydesk
  589  sudo cd /var/lib/dpkg/
  590  cd /var/lib/dpkg/
  591  l
  592  sudo nano lock
  593  sudo apt install anydesk
  594  sudo nano lock-frontend 
  595  sudo apt install anydesk
  596  history 
