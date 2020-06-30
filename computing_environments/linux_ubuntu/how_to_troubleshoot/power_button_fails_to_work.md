* Draft: 2020-06-15 (Mon)
# The Power Button Fails to Work with Dell Alienware Aurora R-Series
* [Alienware Aurora R6](https://www.dell.com/support/home/en-us/product-support/product/alienware-aurora-r6-desktop/docs)

## Problem
I was going to install a new OS (Ubuntu 18.04) using a bootable USB memory onto a computer with two GPU cards (GeForce 1080Ti). This computer was used by someone else and he claimed it was working fine. However it failed to boot properly. 

When I pressed the power button, the color of the button started from blue and switched to yellow. Blinked 3 times and then 6 times. I restarted the system several times and failed all the time. After a while, it somehow worked and I saw the login console. However I didn't see the alien logo which is expected at the very beginning of the boot sequence for Dell Alienware. 

I know this because I'm using the same machine for three years. Something is wrong. So I called the previous user of this computer. I asked several diagnostic questions. "Did you see an alien logo at the time of booting the computer? No". "How long have you used it? 2~3 months." He said he installed CentOS and Node.js. I assumed he left it on for a long time. "In that case, you left it on most of time, right? Yes." He might have seen the alien logo, but may not have realized it because he didn't boot the system many times.

[Accessing the BIOS on your Alienware System](https://www.dell.com/support/article/ko-kr/sln304847/accessing-the-bios-on-your-alienware-system?lang=en)
```
How to access the BIOS on your Alienware System?
1. Turn On your System
2. Tap the F2 key repeatedly as the system turns on
3. BIOS should load after the Alienware logo screen
```
## Hint
* [Aurora R5 power button blinking yellow and pc won’t start](https://www.dell.com/community/Alienware-Desktops/Aurora-R5-power-button-blinking-yellow-and-pc-won-t-start/td-p/6072008)
```
@Yason The 3,6 error code is indicating that the BIOS recovery image was not not found.  I've seen a couple of posts over the past couple of weeks from people with R5's that got a BIOS Upgrade Required prompt only to have their system bricked.  Did you notice perhaps if one of the updates it did was a BIOS update?
```
### System diagnostic lights
| Number of Power LED flashes | Problem description                   | Suggested solution                                                                                    |
|-----------------------------|---------------------------------------|-------------------------------------------------------------------------------------------------------|
| 1                           | System board: BIOS and ROM failure    | Flash latest BIOS version. If problem persists, replace the system board.                             |
| 2                           | No memory or RAM detected             | Confirm that the memory module is installed properly. If problem persists, replace the memory module. |
| 3                           | System board or chipset error         | Replace the system board.                                                                             |
| 4                           | Memory or RAM failure                 | Replace the memory module.                                                                            |
| 5                           | CMOS battery failure                  | Replace the CMOS battery.                                                                             |
| 6                           | Video card or chip failure            | Replace the video card.                                                                               |
| 7                           | CPU failure                           | Replace the system board.                                                                             |
| 3,6                         | BIOS recovery image not found         | Reimage the system BIOS.                                                                              |
| 3,7                         | BIOS recovery image found but invalid | Reimage the system BIOS.                                                                              |

Source: [Aurora R5 Service Manual](https://www.dell.com/support/manuals/us/en/04/alienware-aurora-r5-desktop/alienware-aurora-r5-sm/system-diagnostic-lights?guid=guid-a862de3c-1031-4adc-b3a5-c84676da1852&lang=en-us)

### See how the devices inside the box looks like
[How to upgrade the Alienware Aurora R5 and R6](https://www.windowscentral.com/how-upgrade-alienware-aurora-r5-and-r6)
How to open the Alienware Aurora
```
1. Remove the single screw from the black handle on the rear.
2. Slide both latches up.
3. Pull the black handle outwards.
4. Pop off the side panel with the ventilation grilles in.
5. Swing out the power supply to reveal the internals of the PC.
```
<img src="https://www.windowscentral.com/sites/wpcentral.com/files/styles/w830_wm_brw/public/field/image/2017/02/aurora-rear-howto.jpg?itok=m5BtSYb5">

### I talked with the guy who used to use this machine.
He got this computer a couple of months ago. No OS was installed and he installed CentOS and Node.js. He powered on this machine and left it on for a long time because he ended up not using it.

I asked him the first thing he saw when he powered on this computer. He said he didn't see an alien symbol when the computer is booted up. The first thing was a console terminal (or log-in for CentOS).

I've seen this just once after several failures to boot up the system. Only once. Afterward the computer's power button turns blue for seconds and then starts to blink in yellow 3-6 times.

### Google search: alienware bios recovery
* [BIOS Recovery Steps for a No Post issue on Alienware Aurora R5/R6/R7/R8 and XPS 8910/8920/8930 PCs](https://www.dell.com/support/article/en-us/sln309785/bios-recovery-steps-for-a-no-post-issue-on-alienware-aurora-r5-r6-r7-r8-and-xps-8910-8920-8930-pcs?lang=en)
```
Are you seeing a 3-6 or 3-7 LED No POST diagnostic error on your Alienware or XPS PC?
The following section of this article will take you through the steps needed to use the built-in BIOS recovery facility to recover from a No POST issue on your system.

Affected Systems: Alienware R5/R6/R7/R8, XPS 8910/8920/8930
```
* [How to run a Bios update on an Alienware Computer](https://www.dell.com/support/article/en-us/sln148359/how-to-run-a-bios-update-on-an-alienware-computer?lang=en)
```
System does not startup after a BIOS update

No image on the screen after the BIOS update:

    Turn off the system
    Unplug the AC Adapter or the power cord
    Unplug the battery (Mobiles Only). Click HERE for help on how to remove the battery
    Press and Hold the power button for 30 seconds
    Connect everything back
    Press and Hold the Fn key while turning on the system, let go when you see the Alienware logo
```
Caution:
* [Alienware: Safety precautions (New Video on Description)](https://www.youtube.com/watch?v=w75LEsUStpM)

I was going to follow the above insturctions and remove the battery in order to reset the BIOS. Before proceeding, I confirmed with the admin in charge of the devices in my department. He suggested not to do it by myself. So I had to stop here.

I took a video before returning the computer to record the phenomena. 
