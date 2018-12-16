# How to setup Linux with Real Time Kernel Patch
This tutorial tried with Ubuntu 14.04  

1. Creat a directory for kernel file and patch file
```
mkdir Kernel
cd Kernel
```

2. Select kernel version  
http://cdn.kernel.org/pub/linux/kernel/

3. Download the selected kernel
```
wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.14.1.tar.xz
```

4. Select the patch as long as its kernel version and major revision same  
http://cdn.kernel.org/pub/linux/kernel/projects/rt/

5. Download the selected patch
```
wget http://cdn.kernel.org/pub/linux/kernel/projects/rt/4.14/older/patch-4.14.1-rt3.patch.gz
```

6. Extract the kernel content
```
tar xvf linux-4.14.1.tar.xz
cd linux-4.14.1/
```

7. Unzip the kernel patch and patch it with -pnum options  
-p0 gives the entire file name unmodified and -p1 gives without leading slash
```
gzip -cd ../patch-4.14.1-rt3.patch.gz 
zcat ../patch-4.14.1-rt3.patch.gz | patch -p1
```

8. requires ncurses and openssl
```
sudo apt-get install libncurses5-dev libncursesw5-dev
sudo apt-get install libssl-dev
```

9. Load the existing configuration of your system
```
make menuconfig
```

* When graphical menu comes
```
Processor type and features ---> [Enter] 
Preemption Model (Valuntary Kernel Preemption (Desktop)) [Enter]
Fully Preemptible Kernel (RT) [Enter] # Select

Upper menu with <exit>

Kernel hacking --> [Enter]
Memory debugging [Enter]
Check for stack overflows #Deselect

<save> and save as .config
```

10. Compile the kernel modules, make modules and install
```
make 
sudo make modules_install
sudo make install
```

11. After all, you can check the new kernel
```
ls /boot
```

12. Then update grub to see new kernel in beginning and reboot
```
sudo update-grub
sudo reboot
```

13. After rebooting verify is your sistem real time or not
```
uname -a
```

My outputs:
```
Linux sevval-rtos 4.14.1-rt3 #1 SMP PREEMPT RT Sat Dec 15 23:15:11 EET 2018 x86_64 x86_64 x86_64 GNU/Linux
```

14. Testing  
When 2 threads run at real-time priority level 10 in process 7836
![When 2 threads run at real-time priority level 10 in process 7836 ](test.jpg)

