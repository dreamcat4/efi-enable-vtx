## Apple EFI Firmware - Enable VT-X

Guide by monoclast, posted at 

[http://forum.parallels.com/showthread.php?t=3273](http://forum.parallels.com/showthread.php?t=3273)

Fix by Josh LeVasseur

[http://forum.parallels.com/showthread.php?t=577](http://forum.parallels.com/showthread.php?t=577)


### Why

Pretty much all the chips Apple uses in the Intel Macintosh computers have VT-X. It allows the chip to run more effeiciently, resulting in performance increases for the end user. For detailed information about VT, see http://www.intel.com/technology/computing/vptech/.

Although present, VT is not turned on in all Intel Macintosh computers. This was 'fixed' by Apple some time ago around the time of Mac Mini EFI Firmware update 1.1. However it seems that some users will continue to experience VT-X related issues, even after upgrading to the latest EFI Firmware update. As a result, you may have experienced intermittent success with the ability to enable VT. These instructions show you how to use the EFI firmware in Intel Macs to enable VT in the processor permanently, so that it lasts through restarts of the computer.

If you don't wish to alter the EFI Firmware in this way, there is 1 alternative.

### Sleep Trick

Put the computer to sleep. Wait 5 seconds. Wake it up. VT-X should be working. The setting is forgotten on reboot. You will need to sleep again after each restart to switch VT-X on again.

### Compatibility

The real compatibility is not fully known. Tested, and known to work well for the following system:


Mac mini (Late 2006)

Model Identifier: Macmini1,1

EFI Boot ROM Version: MM11.0055.B08 (EFI 1.1)

SMC Version: 1.3f4 (SMC 1.0)


This trick changes only 1 bit in the MSR CPU Register. Other Mac models with different EFI and different versions should (we expect) have this bit located in the same relative address scheme. However its not been verified / tested (and therefore may brick your computer). If you have tried this, and works / fails, then please send your system specs and we can update the list.

The full list of possible Apple EFI Firmwares is available here:

[http://support.apple.com/kb/ht1237](http://support.apple.com/kb/ht1237)

### Set EFI VT-X Register bit

1. Download rEFIt disk image from: [http://prdownloads.sourceforge.net/refit/rEFIt-0.5.dmg?download](http://prdownloads.sourceforge.net/refit/rEFIt-0.5.dmg?download)

2. Copy vmx folder (with vmx-var-set.efi) from the `vmx` folder in this git repository. Or download the original zip file from [http://i30www.ira.uka.de/~joshua/vmx.zip](http://i30www.ira.uka.de/~joshua/vmx.zip)

3. Mount rEFIt disk image.

4. Decompress vmx folder (if zip archive).

5. Copy rEFIt "efi" folder to root of startup volume.

6. Copy "vmx" folder into "efi" folder at root of startup volume.

7. Open Terminal.

8. In Terminal, enter command: cd /efi/refit

9. Enter command: ./enable.sh

10. At prompt, enter your user account password.

11. Restart computer, holding down Option/Alt key on keyboard until you see boot device selection menu.

12. Select rEFIt boot device to enter rEFIt menu.

13. In rEFIt menu, select Console.

14. At console prompt, enter volume command: fs0:

15. Enter command: ls

16. If root of startup volume is not listed:

  1. Increment volume number (for example, "fs1")

  2. Re-enter volume command (for example, fs1: )

  3. Go back to step 16.

17. If root of startup volume is listed (NOTE: you should see items such as: Users, Volumes, etc, mach, . 

18. private, var, usr), enter command: cd efi

19. Enter command: cd vmx

20. Enter command: vmx-var-set.efi

21. If an error message was displayed, here or at any point prior to this, it's possible some files are not in the right place, or you missed a step. Try the steps again from the start, and if they still don't work, seek help online!

22. If no error message was displayed, enter command: exit

23. From rEFIt menu, boot into Mac OS X (usually the first menu item).

24. Remove "efi" folder from root of startup volume.

25. Open Apple menu > System Preferences > Startup Disk.

26. Select your normal Mac OS X startup disk.

27. Close System Preferences.

28. Shut down.

29. Leave computer completely off for 10 seconds.

30. Turn computer back on and boot up normally (no keys held down).
