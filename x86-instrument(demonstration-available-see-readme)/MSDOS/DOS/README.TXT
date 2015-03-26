README.TXT 

NOTES ON MS-DOS 6.22
====================
This file provides important information not included in the
MICROSOFT MS-DOS USER'S GUIDE or in MS-DOS Help.

This file is divided into the following major sections:

1. Setup
2. MemMaker, EMM386, and Memory Management
3. Windows
4. Hardware Compatibility with MS-DOS 6.22
5. Microsoft Backup, Defrag and Anti-Virus
6. Third-Party Programs
7. DriveSpace

If the subject you need information about doesn't appear in
this file, you might find it in one of the following text
files included with MS-DOS:

* OS2.TXT, which describes how to remove and save data on your
  computer when you replace OS/2 with MS-DOS 6.22.

* NETWORKS.TXT, which describes how to update your network software
  for use with MS-DOS 6.22.

* COUNTRY.TXT, which provides details about enhancements to the 
  international keyboard and codepage (character set) support
  included with MS-DOS 6.22.

For information about new features, type HELP WHATSNEW at the command prompt.

This file contains the following topics:

1. Setup
   1.1  SpeedStor
   1.2  Incompatible Hard Disk or Device Driver
   1.3  AT&T 6300 Computer
   1.4  Toshiba with a Hard RAM Disk
   1.5  Tandy with ROM DOS
   1.6  Setup displays the "Your computer uses a disk-compression
	  program that is incompatible with Setup" message.
   1.7  You deleted files from the directory that Setup needs
	  to install the optional Windows programs.
   1.8  Running Setup if Your Computer Uses Windows NT
   1.9  Setup detects that your computer has a non-MS-DOS
	  partition or non-MS-DOS files, and your computer uses Windows NT.
   1.10 Setup displays the "Your computer uses password protection"
	  screen.
   1.11 Setup displays the "Your computer is using an incompatible
	  delete-protection program" screen.
   1.12 Setup detects that your computer uses DR DOS.
   1.13 Installing MS-DOS on a Drive Other Than C
   1.14 Bypassing the Uninstall Disk and Using Default Setup Options
   1.15 Installing MS-DOS on a System with a CorelSCSI UNI_ASP.SYS Driver
   1.16 Installing MS-DOS if you have DrivePro or EZ-Drive
   1.17 Setup displays the "There is not enough disk space" screen
	  and you are running PC-DOS version 6.1
   1.18 Setup cannot update a file
   1.19 Upgrading from PC-DOS 6.1
   1.20 Changes to International Keyboard and Character Set Support
2. MemMaker, EMM386, and Memory Management
   2.1  Intel Expanded-Memory Driver (EMM.SYS)
   2.2  Running MemMaker on a Computer with PC-NFS
   2.3  You have a Super VGA display and want to conserve memory.
   2.4  Using MemMaker with IBM LAN
   2.5  MemMaker and Adaptec SCSI devices
   2.6  Running MemMaker on a computer with PC Tools RAMBoost
   2.7  EMM386 detects an error in an application
   2.8  MemMaker no longer aggressively scans upper memory by default
3. Windows
   3.1  Your computer uses a Windows 3.0 permanent swap file.
   3.2  Using compressed floppy disks with Windows File Manager
4. Hardware Compatibility with MS-DOS 6.22
   4.1  Compaq EXTDISK.SYS Driver
   4.2  Hardcard
   4.3  Toshiba
5. Microsoft Backup, Defrag and Anti-Virus
   5.1  Microsoft Anti-Virus
   5.2  Running Microsoft Backup for MS-DOS under Windows
   5.3  Backup for Windows stops running at the end of the 
	compatibility test
   5.4  Running Microsoft Backup with TI4000 and Gateway NOMAD computers
   5.5  MS-DOS 6.22 Backup Cannot Restore 6 or 6.2 Backups
   5.6  Microsoft Defragmenter
6. Third-party Programs
   6.1  4DOS and NDOS
   6.2  Above Board 286 and Above Board Plus Installation
	  Programs
   6.3  CodeView
   6.4  Colorado Tape Backup
   6.5  Fastback Plus
   6.6  Norton Desktop for Windows 2.0
   6.7  Norton Utilities
   6.8  PC Tools
   6.9  QEMM's Stealth DoubleSpace Feature
   6.10 Johnson Computer Systems PC-Vault and PC-Vault Plus
   6.11 AddStor DoubleTools
7. DriveSpace
   7.1  Converting DoubleSpace Drives to DriveSpace
   7.2  Converting Your XtraDrive Disk-Compression Software
	to DriveSpace
   7.3  Converting Stacker 3.1 Software to DriveSpace
   7.4  Converting Other Disk-Compression Software to DriveSpace
   7.5  DriveSpace Setup indicates that your computer is running an
	incompatible disk-caching program.
   7.6  Your compressed drive runs out of disk space.
   7.7  Your uncompressed (host) drive runs out of disk space.
   7.8  DriveSpace did not compress all of your files because
	  the drive ran out of disk space.
   7.9  Windows displays the message "The permanent swap file is corrupt."
   7.10 EXTDISK.SYS displays a warning about drive letters.
   7.11 You need a special device driver to use your startup drive.
   7.12 Defragmenting uncompressed drives after changing file attributes
   7.13 Files DriveSpace cannot compress
   7.14 Microsoft Defragmenter runs out of memory while you are
	  compressing a drive.
   7.15 DriveSpace and PC-Vault
   7.16 Maximum size of a compressed drive
   7.17 DriveSpace could not mount a drive due to problems with the drive
   7.18 DriveSpace finishes installation, but you cannot access your
	  Hardcard.
   7.19 You receive a DoubleGuard Alarm message
   7.20 A compressed drive is currently too fragmented to mount
   7.21 DriveSpace displays the message "Your computer is running with an
	incompatible version of DRVSPACE.BIN" 
   7.22 Using the DRVSPACE command after bypassing DRVSPACE.BIN
   7.23 Removing the write-protection from a compressed floppy disk
   7.24 Automounting and Norton Disk Cache
   7.25 Undelete utilities and DriveSpace
   7.26 Creating an Emergency Startup Disk for DriveSpace Systems
   7.27 If ScanDisk Cannot Check or Repair a DoubleSpace Volume File
   7.28 DoubleSpace and the DRVSPACE.MR1 File
   7.29 Using unconverted DoubleSpace drives with DriveSpace

1. SETUP
========

1.1 SpeedStor
-------------
If Setup referred you to this section and your computer has an OS/2 
partition created by using the FDISKPM utility in OS/2 2.1, run
MS-DOS Setup by typing SETUP /U at the command prompt.

If Setup referred you to this section and you have neither OS/2 
nor a SpeedStor partition on your computer, see the section "Setup 
displays the Incompatible Hard Disk or Device Driver screen" in 
the "Diagnosing and Solving Problems" chapter of the MS-DOS
User's Guide.

If you do have a SpeedStor partition on your computer, Setup
probably referred you to this section for one of the following
reasons:

* Setup could not find in your CONFIG.SYS file a command
  for the device driver that supports your SpeedStor partition.
  If this is the case, add the command line to your CONFIG.SYS
  file, restart your computer, and run Setup. For more information
  about adding the command line to your CONFIG.SYS file, see your
  SpeedStor documentation.

* Your CONFIG.SYS file has a DEVICE=HARDRIVE.SYS line in it.
  If this is the case, carry out the following procedure:
   
   1. Use the EXPAND command to expand and copy the SSTOR.SYS
      file to your hard disk. Make sure you copy the SSTOR.SYS
      file to the same path as the HARDRIVE.SYS file.

      See the PACKING.LST file on Setup Disk 1 for the location
      of the SSTOR.SYS file on the Setup disks and for instructions
      on how to expand and copy it to your hard disk.

   2. Replace the DEVICE=HARDRIVE.SYS command with a DEVICE=SSTOR.SYS
      command. For example, if the command that loaded the
      HARDRIVE.SYS file was DEVICE=C:\SSTOR\HARDRIVE.SYS, you
      would replace it with DEVICE=C:\SSTOR\SSTOR.SYS.

   3. Restart your computer.

   4. Make sure you can access your hard disk.

   5. Run Setup.

1.2 Incompatible Hard Disk or Device Driver
-------------------------------------------
If Setup referred you to this section, and no other section in this
file is relevant to your system, you have a partition that is
incompatible with MS-DOS 6.22. You must delete the partition from your
hard disk. See "Using Fdisk to Configure Your Hard Disk" in the
chapter "Diagnosing and Solving Problems" in the MICROSOFT MS-DOS
USER'S GUIDE.

1.3 AT&T 6300 Computer
----------------------
If you use an AT&T 6300 computer and your ROM BIOS is version 1.21,
contact your vendor for a ROM BIOS upgrade. The ROM BIOS version
number is displayed when you start your computer.

1.4 Toshiba with a Hard RAM Disk
--------------------------------
These instructions apply to Toshiba models T1200, T1600,
T1200XE and T1000LE.

To use the hard RAM disk, carry out the following procedure
before you install MS-DOS 6.22:

1. Back up your hard RAM disk.

2. Using the Toshiba Setup program, delete the hard RAM
   disk by allocating zero kilobytes (KB) to it. All data on
   the hard RAM disk will be lost.

3. Restart your computer

4. Run MS-DOS Setup.

5. After Setup is complete, run the Toshiba Setup program to reinstall
   the hard RAM disk.

6. Run FDISK, change to drive 2, and create a primary DOS
   partition. Quit FDISK.

7. Use the FORMAT command to format drive D.

1.5 Tandy with ROM DOS
----------------------
Contact your hardware manufacturer for information about
upgrading a Tandy computer with ROM DOS to MS-DOS 6.22. This
applies to the following models: 1000EX, 1000HX, 1000SL, 1000SL2,
1000TL, 1000TL2, 1000TL3, 1000RL, 1000RLX, 1000RL-HD, 1000RLX-HD,
1100FD, 2500XL, 2500XL2.

1.6 Setup displays the "Your computer uses a disk-compression
     program that is incompatible with Setup" message.
--------------------------------------------------------------
If Setup indicated that your computer has an incompatible
disk-compression program, you must remove it manually before you can
install MS-DOS 6.22. Contact your disk-compression vendor for an
updated version of your software. In most cases, current versions of
disk-compression software are compatible with MS-DOS 6.22.

Alternatively, you can use the procedure below to remove your
current disk-compression software.  

1. Back up all the files on your compressed drive. In step 3,
   you will format your uncompressed drive, which destroys all the files
   on your compressed and uncompressed drives.

2. If your Setup disks are compatible with drive A, insert
   Setup Disk 1 in drive A, and restart your computer. After Setup
   displays the first screen, quit Setup by pressing F3 twice.

   If your Setup disks are not compatible with drive A,
   create a startup floppy disk for drive A. To do this, insert
   Setup Disk 1 in drive B, and a blank floppy disk in drive A. Then
   type B:SETUP /F at the command prompt.

   When prompted, choose to install MS-DOS on the floppy disk
   in drive A. After Setup is finished, leave the disk in drive A,
   and restart your computer.

3. At the command prompt, type FORMAT C: /S to reformat your startup
   drive and transfer MS-DOS 6.22 system files to it.

4. Remove the disk from drive A, and restart your computer.

5. Insert Setup Disk 1 in drive A or B, and type A:SETUP or
   B:SETUP at the command prompt.

6. After Setup is complete, restore the files you backed up. Do 
   not restore older versions of MS-DOS files.
  
1.7 You deleted files from the directory that Setup needs
    to install the optional Windows programs.
---------------------------------------------------------
If you typed BUSETUP /E at the command prompt, the "Setup did
not find the files it needs in the directory specified" message
appeared, and you think you deleted the files from
your hard disk, insert Setup Disk 1 in drive A or B, and start
Setup by typing A:SETUP /E or B:SETUP /E at the command prompt.

1.8 Running Setup if Your Computer Uses Windows NT
--------------------------------------------------
If your computer has Windows NT installed, but does not have 
MS-DOS installed on it, carry out Procedure 1. If your computer 
has Windows NT and MS-DOS installed on it, carry out Procedure 2.

Procedure 1

1. Run Setup by inserting Setup Disk 1 in drive A and restarting
   your computer. Complete Setup by following the instructions
   on the screen. When Setup is complete, Windows NT will be 
   disabled. 
   
   If Windows NT was installed on a FAT partition, complete steps 
   2 and 3 of this procedure to reenable Windows NT so that you can
   use both the Windows NT and MS-DOS operating systems.
   
   If Windows NT was installed on a non-FAT partition, see section 1.9.
   
2. Insert your Windows NT Setup disk in drive A or drive B, and then
   restart your computer.
   
3. When the Windows NT Setup screen appears, choose Repair, and then 
   insert your Windows NT Emergency Repair Disk (which you created when 
   you installed Windows NT) to repair the Windows NT system files.


Procedure 2

1. When you start your computer, choose MS-DOS as your operating
   system.

2. Run Setup by inserting Setup Disk 1 in drive A or B, and typing
   A:SETUP or B:SETUP at the command prompt.


1.9  Setup detects that your computer has a non-MS-DOS
     partition or non-MS-DOS files, and your computer uses
     Windows NT
----------------------------------------------------------
The procedure you use depends on whether you want to preserve
the partition and its files. Find the section below that describes
the configuration you want.

You Don't Want to Preserve the Partition or its Files
------------------------------------------------------
If you don't want to preserve the partition or its files, choose to
remove the partition or files if Setup prompts you to do so. If
Setup doesn't offer you that choice, remove the partition manually
after Setup is complete. For instructions on removing a non-MS-DOS
partition manually, see "Using Fdisk to Configure Your Hard Disk" in
the chapter "Diagnosing and Solving Problems" in the MICROSOFT MS-DOS
USER'S GUIDE.

You Don't Want to Preserve the Partition but Want to Save its Files
-------------------------------------------------------------------
If you want to save the data files, but don't want to preserve the
partition, back up the files, run Setup again, and then choose to
remove the partition or files if Setup prompts you to do so. If Setup
doesn't offer you this choice, remove the partition manually after
Setup is complete. For instructions on removing the partition
manually, see "Using Fdisk to Configure Your Hard Disk" in the
chapter "Diagnosing and Solving Problems" in the MICROSOFT MS-DOS
USER'S GUIDE.

You Want to Preserve the Partition and Its Files
------------------------------------------------
Carry out the following procedure.

NOTE  If the non-MS-DOS partition takes up all the space on your hard
disk, you must reconfigure your hard disk. You can either let Setup do
it for you, as described in the preceding section, or reconfigure it
yourself manually. For instructions on reconfiguring your hard disk
manually, see your Windows NT documentation.

To install MS-DOS 6.22 and preserve your partition or files:

1. Run MS-DOS Setup.

2. When prompted, choose to continue Setup without removing the
   partition or files.

3. After Setup is complete, insert your Windows NT Setup disk 
   in drive A or drive B, and then restart your computer.
   
4. When the Windows NT Setup screen appears, choose Repair, and then 
   insert your Windows NT Emergency Repair Disk (which you created when 
   you installed Windows NT) to repair the Windows NT system files.


1.10 Setup displays the "Your computer uses password protection"
     screen.
----------------------------------------------------------------
See section 1.12.

1.11 Setup displays the "Your computer is using an incompatible
     delete-protection program" screen.
---------------------------------------------------------------
See section 1.12.

1.12 Setup detects that your computer uses DR DOS.
--------------------------------------------------
If you have DR DOS installed on your computer, take the following
precautions before restarting Setup:

o If your system has any security features, including password protection,
  disable them. For more information, see "Setup displays the 'Your
  computer uses password protection' screen" in the chapter "Diagnosing
  and Solving Problems" in the MICROSOFT MS-DOS USER'S GUIDE.

  If you have protected any files or directories with a password,
  remove the password protection, particularly if you have protected
  your CONFIG.SYS or AUTOEXEC.BAT files, or your DR DOS directory.

o If you have DELWATCH installed on your computer, carry out
  the procedure "Setup displays the 'Your computer is using an
  incompatible delete-protection program' screen" in the chapter
  "Diagnosing and Solving Problems" in the MICROSOFT MS-DOS
  USER'S GUIDE.

o If your CONFIG.SYS or AUTOEXEC.BAT files use any conditional commands--
  such as the "?" or GOTO commands--remove them and adjust the order of
  commands in your startup files accordingly.

o If your CONFIG.SYS file uses the CHAIN command, remove it and
  adjust the order of commands in the file accordingly.

o If your computer uses disk compression, but drive C is not compressed,
  run Setup as described in the chapter "Getting Started" in the
  MICROSOFT MS-DOS USER'S GUIDE. When Setup displays the "Your
  CONFIG.SYS file contains commands that are not valid MS-DOS commands"
  message, choose the "Modify original files" option.

  If drive C is compressed, carry out the following procedure:

  1. Determine which drive is your original uncompressed drive. For more
     information, see your DR DOS documentation.

  2. Make backup copies of the CONFIG.SYS and AUTOEXEC.BAT files on your
     compressed drive, and the DCONFIG.SYS file on your uncompressed drive.

  3. Combine the two configuration files. For example, if drive D is your
     uncompressed drive, type the following at the command prompt:

     COPY D:\DCONFIG.SYS+C:\CONFIG.SYS D:\CONFIG.SYS

  4. Copy the combined CONFIG.SYS file to drive C. For example, if drive
     D is your uncompressed drive, type the following at the command
     prompt:

     COPY D:\CONFIG.SYS C:\CONFIG.SYS

  5. Copy your AUTOEXEC.BAT to your uncompressed drive. For example, if
     drive D is your uncompressed drive, type the following at the
     command prompt:

     COPY C:\AUTOEXEC.BAT D:\AUTOEXEC.BAT
    
  6. Run MS-DOS 6.22 Setup.

  7. When Setup displays the "Your CONFIG.SYS file contains commands
     that are not valid MS-DOS commands" message, choose the "Modify
     original files" option.

     When Setup displays the "Because you are currently using the
     DR DOS operating system" message, choose Continue.

  8. After Setup is complete, MS-DOS displays an "Unrecognized command"
     message on your screen for each command in your AUTOEXEC.BAT and
     CONFIG.SYS files that is not a valid MS-DOS command. Remove these
     commands from your CONFIG.SYS and AUTOEXEC.BAT files.

  9. Add the DEVICE=HIMEM.SYS command to the beginning of your
     CONFIG.SYS file, and the restart your computer.

1.13 Installing MS-DOS on a Drive Other Than C
----------------------------------------------
As described in the following procedure, you can install MS-DOS
on a drive other than C by using the /M switch to copy the system
files to your startup drive and then using the /Q switch to copy your
MS-DOS files to a different drive.

NOTE  This procedure is designed for advanced users. If your computer
uses disk-compression software, modify the procedure as appropriate.

NOTE  If your computer uses disk-partitioning software, such as Disk
Manager, SpeedStor, Priam, or Everex, do not carry out the procedure until
you have carried out steps 1 through 3 of "You need to install MS-DOS
manually" in the chapter "Diagnosing and Solving Problems" in the
MICROSOFT MS-DOS USER'S GUIDE. If your software uses a driver to
enable the drive on which you want to install MS-DOS, make sure you create
a startup disk with the driver in a CONFIG.SYS or AUTOEXEC.BAT file.
After you have carried out these steps, skip to step 3 of the following
procedure.

1. Run Setup by inserting Setup Disk 1 in drive A or B, and
   typing A:SETUP /M or B:SETUP /M at the command prompt.

   NOTE  Your CONFIG.SYS and AUTOEXEC.BAT files were saved as CONFIG.NEW
   and AUTOEXEC.NEW.

2. Run Setup by inserting Setup Disk 1 in drive A or B, and typing
   A:SETUP /Q or B:SETUP /Q at the command prompt. Follow the
   instructions on your screen.

3. When Setup displays the system settings screen, choose the MS-DOS
   Path option. Type the drive and directory where you want
   to install MS-DOS, and press ENTER. Continue Setup.

4. After Setup is complete, open your CONFIG.NEW and AUTOEXEC.NEW files
   and ensure that their commands specify the correct path. Save the files
   as CONFIG.SYS and AUTOEXEC.BAT. Then restart your computer.

1.14 Bypassing the Uninstall Disk and Using Default Setup Options
-----------------------------------------------------------------
To keep Setup from creating an Uninstall Disk, use the /G switch
with the Setup command.

To bypass the Uninstall disk and use default Setup options
instead of choosing them yourself, use both the /H and /G switches
with the Setup command.

WARNING  The primary purpose of the Uninstall disk is to safeguard
your files during and after Setup. If Setup doesn't create
an Uninstall disk, you will not be able to restore your previous
version of DOS. If Setup should render your hard disk inaccessible,
you will not be able to use the Uninstall disk to make it accessible
again.

IMPORTANT  If you have not created an Uninstall disk and Setup cannot
complete, do not try to use your computer except as directed by 
Microsoft Product Support Services. Otherwise, you could lose data.

NOTE  If you have a version of MS-DOS earlier than 5.0, and you plan
to use the /G switch or the /H and /G switches together, follow the
instructions in the NETWORKS.TXT file to update your network software
before running Setup.

1.15 Installing MS-DOS 6.22 on a System with a CorelSCSI UNI_ASP.SYS Driver
--------------------------------------------------------------------------
If your system uses the CorelSCSI UNI_ASP.SYS device driver for optical
drives, and Setup stops running when you try to install MS-DOS 6,
delete the DEVICE command in your CONFIG.SYS that loads the Corel
UNI_ASP.SYS driver. Then run Setup again. After Setup is complete,
reinstall the Corel UNI_ASP.SYS driver as you originally installed it.
If you continue to have problems, contact Corel Customer Service.

1.16  Installing MS-DOS 6.22 if you have DrivePro or EZ-Drive
------------------------------------------------------------
If Setup detects that your hard disk was set up using Micro House
DrivePro(tm) or EZ-Drive(tm), you must run the DOS6INST.EXE program
before you can safely install MS-DOS 6.22. The DOS6INST.EXE program
is provided on the Micro House diskette; it is also available on
the Micro House BBS at (303)443-9957. For further assistance, 
contact Micro House Technical Support.

1.17 Setup displays the "There is not enough free disk space" screen
     and you are running PC-DOS version 6.1 with compression 
--------------------------------------------------------------------
If your computer is running PC-DOS version 6.1 with PC-DOS disk 
compression, when you run MS-DOS Setup, it displays the message 
"There is not enough free disk space on drive C to install MS-DOS." 

PC-DOS disk compression is incompatible with MS-DOS. Before you 
install MS-DOS 6.22, you must first uninstall your PC-DOS disk
compression from all your compressed drives and then completely
remove PC-DOS disk compression. For more information, see "Upgrading
from PC-DOS 6.1" later in this file.

Note: If you have completely uninstalled PC-DOS compression and this
      message still occurs, you also need to free some space on drive C.

1.18  Setup cannot update a file
--------------------------------
If Setup cannot update one of your MS-DOS files, it displays a message
with the title "Cannot Update File." If you continued Setup, your MS-DOS 
6.22 installation is incomplete because the specified file was not updated
to version 6.22. If the file is one you know you don't need (for example,
if it's a DoubleSpace file and you don't use DoubleSpace), don't worry 
about it. (If you are running PC-DOS 6.1, see section 1.20 of this file).
If you are not sure, update the file using the following procedure (you 
will need your MS-DOS 6.0 distribution disks):

1. If you use DoubleSpace and the file that was not updated was a 
   DoubleSpace file, or if your system does not work properly after 
   you receive this error message, insert your Uninstall disk in 
   drive A and type A:\UNINSTAL at the command prompt. 

2. Insert MS-DOS 6.0 Setup Disk 1 (not MS-DOS 6.22 Setup Disk 1) in 
   drive A or drive B, and then use MS-DOS Editor (EDIT) to view 
   the contents of the PACKING.LST file. This file tells you where each 
   file is located on your MS-DOS 6.0 disks. Determine which MS-DOS 6.0 disk 
   contains the file you need. 

3. Insert the appropriate MS-DOS 6 disk in drive A or drive B, and then
   use the EXPAND command to expand the file. For example, to expand the
   file DRVSPACE.BI_ from the disk in drive A to the directory C:\DOS, 
   you would type the following  command:
   
	EXPAND A:\DRVSPACE.BI_ C:\DOS\DRVSPACE.BIN

   For more information, see the comments at the beginning of the PACKING.LST
   file, or see the MS-DOS 6 User's Guide.

4. Run MS-DOS 6.22 Setup again. This time, Setup should be able to update the
   file. 
   
1.19 Upgrading from PC-DOS 6.1
------------------------------
If your computer is running PC-DOS version 6.1 with PC-DOS disk 
compression, you cannot install MS-DOS 6.22 until you remove the
disk compression. This is because PC-DOS disk compression is 
incompatible with MS-DOS. Follow these steps:

1. First, uninstall your PC-DOS disk compression from all your 
   compressed drives. (For information on uncompressing PC-DOS 
   compressed drives, see the information on the SSUNCOMP command 
   in the PC-DOS documentation.)
 
2. When SSUNCOMP uncompresses your last compressed drive, it asks
   if you want to disable the driver. Answer Yes to remove the
   PC-DOS version of the DRVSPACE.BIN file. 

3. Change to the directory that contains your PC-DOS files, and 
   then type the following command:

	DEL DRVSPACE.*
	
4. Insert MS-DOS 6.22 Setup Disk 1 in drive A or drive B, and then
   type A:SETUP or B:SETUP. 


1.20  Changes to International Keyboard and Character Set Support
-----------------------------------------------------------------
MS-DOS 6.22 includes new codepage information files EGA2.CPI, 
EGA3.CPI and ISO.CPI, as well as the new KEYBRD2.SYS file, which
offers additional keyboards. MS-DOS also includes new country settings 
in COUNTRY.SYS.

For details about enhancements to the international keyboard and codepage
(character set) support, see the COUNTRY.TXT file, which is located in
the directory that contains your MS-DOS files.


2. MEMMAKER AND MEMORY MANAGEMENT
=================================

2.1 Intel Expanded-Memory Driver (EMM.SYS)
------------------------------------------
If you use Intel's EMM.SYS driver with Aboveboard, use EMM.SYS
version 4.0 revision E if you an ISA system, or EMM.SYS version 4.0
revision D if you have an MCA or other system. Contact Intel for a
free upgrade.

2.2 Running MemMaker on a Computer with PC-NFS
----------------------------------------------
If you use PC-NFS network software, carry out the following procedure
before you run MemMaker:

1. Open your MEMMAKER.INF file by using any text editor. This file is
   in the directory that contains your MS-DOS files.

2. Add the following line to the file:

   *NET

3. Save the file, and then run MemMaker.

2.3 You have a Super VGA display and want to conserve memory.
-------------------------------------------------------------
If you use Microsoft Windows on an 80386 computer with extended
memory and a Super VGA display, you can use the MONOUMB.386 file, in
conjunction with MemMaker, to conserve conventional memory for
running programs.

To conserve memory if you have a Super VGA display:

1. Open your Windows SYSTEM.INI file, and find the [386Enh] section.

2. Add a DEVICE command for the MONOUMB.386 file, which is located
   in your MS-DOS directory. For example, if your MS-DOS files are in
   C:\DOS, add the following line to this section:

   DEVICE=C:\DOS\MONOUMB.386

3. Save the file, and restart your computer.
  
4. After your computer starts, run MemMaker by typing MEMMAKER at the
   command prompt.

5. Choose Custom Setup. On the Advanced Options screen, answer Yes to
   the question "Use monochrome region (B000-B7FF) for running programs?"
  
   Follow the instructions on your screen.

2.4 Using MemMaker with IBM LAN
-------------------------------
Before you run MemMaker, you might need to make adjustments to the
parameters specified for your IBM LAN support driver, DXMC0MOD.SYS. In
your CONFIG.SYS file, make sure that the DEVICE command that loads
DXMC0MOD.SYS includes one of the following before you run MemMaker:

o The first three parameters, as in the following example:

  DEVICE=C:\DXMC0MOD.SYS 400000000001,D800,1

o No parameters, as in the following example:

  DEVICE=C:\DXMC0MOD.SYS

o Some parameters and enough commas to fill in the first three
  parameters, as in the following example:

  DEVICE=C:\DXMC0MOD.SYS 400000000001,,

2.5 MemMaker and Adaptec SCSI devices
-------------------------------------
MemMaker is compatible with Adaptec SCSI devices. However, if you use
the ASPI4DOS.SYS driver to support your SCSI device, MemMaker by default
will exclude this driver from the optimization process. If you don't
use the SCSI device as your startup or boot drive, you can include the
ASPI4DOS.SYS driver in the optimization process. To do so, remove the
^ASPI4DOS entry in the MEMMAKER.INF file, and then run MemMaker.

2.6 Using MemMaker on a computer with PC Tools or PC-DOS RAMBoost
-----------------------------------------------------------------
You can use MemMaker or RAMBoost with MS-DOS, but not both at the
same time. MemMaker will prevent RAMBoost from loading, but not
remove its DEVICE= command from your CONFIG.SYS.

2.7 EMM386 detects an error in an application
---------------------------------------------
If EMM386 displays a message such as "EMM386 has detected error
#12 in an application," this indicates that the processor
has reported an exception error to EMM386. An exception error
typically occurs when an application gives the processor an
instruction under invalid or unexpected conditions. In most cases,
these errors are related to a specific program. If you are receiving
an error that does not occur with any particular application, the
error might be caused by a device driver or a memory-resident
(terminate-and-stay-resident) program.

To avoid these errors:

  o  Try to identify the program involved. One way to do this is
     to see if the error occurs when the program is not running.
     If you suspect a memory-resident program or device driver,
     try bypassing it when your computer starts.

  o  Try disabling EMM386. If a particular application is to blame,
     disabling EMM386 might allow that application to generate an
     error message. Disabling EMM386 might also change
     your memory configuration so that the error no longer occurs.

  o  Try changing the order in which you load device drivers and
     memory-resident programs. This might help because some
     errors occur only under specific memory conditions.

  o  If error 12 is occurring, this indicates that a stack is being used
     incorrectly. Try adding the following command to your CONFIG.SYS
     file:

	STACKS=18,512

  o  If error 13 is occurring, the program may be trying to use protected
     mode without cooperating with EMM386. You may need to obtain a
     VCPI-compliant version of the program, or not load EMM386 when
     using this application.

2.8  MemMaker no longer aggressively scans upper memory by default
------------------------------------------------------------------
By default, the MS-DOS 6.22 version of MemMaker does not scan upper
memory aggressively. Instead, the MemMaker option "Scan the upper 
memory area aggressively?" is set to No, and MemMaker limits its search 
for available UMBs to memory addresses C600 through EFFF. In contrast,
the MS-DOS 6 version of MemMaker did scan upper memory aggressively 
by default: in addition to scanning memory in the C600-EFFF range, 
it also scanned addresses in the range F000 through F7FF. 

To make more memory available for running programs, run MemMaker in 
Custom mode and change the "Scan the upper memory area aggressively?" 
option to Yes. (Note that, on some computers, putting UMBs in this 
range prevents the computer from starting properly.)

Note: If you last ran MemMaker with the "Scan the upper memory
      area aggresively" option set to Yes, then the next time
      you run MemMaker, it leaves that option set to Yes.


3. WINDOWS
==========

3.1 Your computer uses a Windows 3.0 permanent swap file.
---------------------------------------------------------
If your computer uses a Windows 3.0 permanent swap file, run
the SPATCH.BAT program to make the swap file compatible with MS-DOS 6.
To do so, carry out the following procedure:

1. Copy the SPATCH.BAT file to your hard disk. To determine the location of
   the file on the Setup disks, view the PACKING.LST file on Setup Disk
   1.

2. Type the following at the command prompt:

   SPATCH [DRIVE]:[PATH]SWAPFILE.EXE
  
   For the DRIVE and PATH parameters, specify the location of
   your SWAPFILE.EXE file.

3. Follow the instructions on your screen.

   The program modifies the SWAPFILE.EXE for use with MS-DOS 6
   and saves a backup copy as SWAPFILE.SAV. After you have confirmed
   the file works correctly, you can delete the SWAPFILE.SAV file.

3.2 Using compressed floppy disks with Windows File Manager
-----------------------------------------------------------
If you are using compressed floppy disks with automounting enabled,
you might encounter error messages or other problems while using File 
Manager. To work around these problems, press the F5 key twice.

For example, if you change from a compressed to an uncompressed floppy
disk, the drive button for the compressed floppy disk's host drive 
remains until you press the F5 key twice.


4. HARDWARE COMPATIBILITY WITH MS-DOS
=====================================

4.1 Compaq EXTDISK.SYS Driver
-----------------------------
The Compaq EXTDISK.SYS driver version 3.00 or later is
compatible with MS-DOS 6. If you have a version earlier
than 3.00, contact your vendor for an upgrade.

4.2 Hardcard
------------
If you upgraded your system from MS-DOS 6 or 6.2, your system
uses its Hardcard drive as its startup drive, and you want to use 
DoubleSpace on that drive, see section 7.18. For additional 
Hardcard information, see the following:

a) Hardcard II

   If you can't use Plus Development Hardcard II or Hardcard
   II XL when running EMM386.EXE, specify the exclude (x=)
   switch to prevent EMM386 from conflicting with the card's
   BIOS address.

   To configure EMM386, run MemMaker.

b) Hardcard 40 or Passport

   If you are using Hardcard 40 or a Passport removable
   disk, and you have a DEVICE command in your CONFIG.SYS file
   for PLUSDRV.SYS, disable or remove the DEVICE command.
   Then run MS-DOS 6.22 Setup. After Setup is complete, reenable or
   restore the DEVICE command for PLUSDRV.SYS. Make it the last line
   in the file.

c) If you upgraded your system from MS-DOS 6 or 6.2, installed 
   DoubleSpace on your Hardcard, and are now unable to access your 
   newly compressed drive, try the following:

   1) Add a DRVSPACE /MOUNT command to your AUTOEXEC.BAT file to mount
      the compressed volume file on the Hardcard every time you start
      your computer.

   2) Or, ensure that there is at least one device driver (for example,
      ANSI.SYS) loaded in your CONFIG.SYS file AFTER the ATDOSXL.SYS
      driver but BEFORE the DRVSPACE.SYS driver.

4.3 Toshiba
-----------
If you used the MS-DOS 5.0 version of EMM386 before you ran
Setup, and you use the Power Management function, use
the VRESUME program or device driver to avoid problems with
the Resume feature. Carry out the following procedure:

1. Make sure the VRESUME.COM or VRESUME.SYS file is on your hard disk.
   To load the TSR, add a command for VRESUME.COM to your AUTOEXEC.BAT file.
   To load the device driver, add a command for the VRESUME.SYS file to
   your CONFIG.SYS file.

2. Save the file, and restart your computer.

   NOTE  For information about using VRESUME with Windows 3.0, see the
   WRESUME.TXT file on your Toshiba MS-DOS 5.0 disks.

5. MICROSOFT BACKUP, DEFRAG AND ANTI-VIRUS
==========================================

5.1 Microsoft Anti-Virus
------------------------
Before cleaning a program file, make sure you have a backup copy of it.
If you clean a program file, and the program is corrupted, reinstall the
program. If Anti-Virus again detects a virus, there is a chance the
detection is in error; contact your software vendor to determine if an
updated version of the program is available.

5.2 Running Microsoft Backup for MS-DOS under Windows
-----------------------------------------------------
You should not run Backup for MS-DOS while Windows is running.  Use
Backup for Windows instead (Backups created using Backup for Windows
can be restored using Backup for MS-DOS).  If you do not have Backup
for Windows installed, see "Installing Anti-Virus, Backup, and Undelete
after Setup" in the "Getting Started" chapter of the Microsoft MS-DOS 
USER'S GUIDE.

5.3  Backup for Windows stops running at the end of the compatibility test
--------------------------------------------------------------------------
If Backup for Windows stops running at the end of the Compatibility
Test, you might be loading an incompatible third-party backup driver
in your SYSTEM.INI file. Carry out the following procedure.

NOTE  This procedure disables your third-party backup program.

1. Open your SYSTEM.INI file, and locate the [386Enh] section.

2. Determine whether any of the following lines are included in this
   section:

   DEVICE=FASTBACK.386
   DEVICE=VFD.386
   DEVICE=CPBVXD.386
   DEVICE=VIRWT.386

3. If you find any of these lines, add a semicolon (;) to the front
   of the line.

4. Save the file, restart Windows, and run Backup for Windows again.

5.4  Running Microsoft Backup with TI4000 and Gateway NOMAD computers
---------------------------------------------------------------------
To avoid a conflict between the Turbo feature and Microsoft Backup
for Windows or MS-DOS, add a /L0 switch to the DEVICE command in
your CONFIG.SYS that loads the BATTERY.PRO file. Or, before you
run Microsoft Backup, type SETPOWER /L0 at the command prompt.

5.5 Using MS-DOS 6.22 Backup to Restore MS-DOS 6 or 6.2 Backups
---------------------------------------------------------------
Like earlier versions of MS-DOS Backup, the Backup programs included 
with MS-DOS 6.22 support data compression during backup. 
However, the MS-DOS 6.22 Backup programs use a different compression
format from earlier versions of Backup.

Because of this, MS-DOS 6.22 Backup for Windows (MWBACKUP.EXE) cannot 
restore compressed backups created by MS-DOS 6 or 6.2 Backup. To
restore such backups, use MS-DOS 6.22 Backup for MS-DOS (MSBACKUP.EXE),
or use the version of Backup that created the compressed backups. For
information about restoring a previous version of Backup, see the
following section.

MS-DOS 6.22 Backup for MS-DOS (MSBACKUP.EXE) can restore earlier compressed
backups only if one of the following conditions is true:

 * DoubleSpace is installed (DBLSPACE.BIN is loaded in memory). 

 * The files DBLSPACE.BIN and DRVSPACE.MR1 are available. For more
   information on DRVSPACE.MR1, see section 7.28.

Both MSBACKUP.EXE and MWBACKUP.EXE can successfully restore MS-DOS 
version 6, 6.2 and 6.21 backups made without backup data compression
If you unchecked the Compress Backup Data box in the Backup Options 
dialog before you backed up, you should have no problems restoring your 
data using the MS-DOS version 6.22 Backup programs.

Restoring a Previous Version of Microsoft Backup
------------------------------------------------
When you run MS-DOS 6.22 Setup, it installs the 6.22 version of the 
Backup program(s). The following procedures explain how to re-install 
the MS-DOS 6 or 6.2 version of Backup for MS-DOS. The procedure you 
use differs depending on the size of your MS-DOS 6 or 6.2 disks. 
(The commands in these procedures assume that your Setup disks are 
in drive A and your MS-DOS files are located in the C:\DOS directory; 
if the disks or MS-DOS files are in a different drive or location, 
adjust the commands accordingly.)

If you have MS-DOS 6.2 disks (either 1.2 MB or 1.44 MB disks) or
MS-DOS 6 disks (1.2 MB disks only):

1. Insert Setup Disk 1 in drive A.

2. Type the following commands:

   COPY A:*.OVL C:\DOS
   EXPAND A:MSBACKUP.EXE C:\DOS
   EXPAND A:MSBACKUP.HLP C:\DOS
   EXPAND A:MSBCONFG.HLP C:\DOS

If you are using MS-DOS 6 disks (1.44 MB disks only):

1. Insert Setup Disk 2 in drive A.

2. Type the following commands:

   EXPAND A:MSBACKUP.EXE C:\DOS
   COPY A:*.OVL C:\DOS

3. Insert Setup Disk 3 in drive A.

4. Type the following commands:

   COPY A:*.OVL C:\DOS
   EXPAND A:MSBACKUP.HLP C:\DOS
   EXPAND A:MSBCONFG.HLP C:\DOS

   These commands copy Backup's files from drive A to the C:\DOS 
   directory. If Setup Disk 1 is in drive B, or if your MS-DOS files 
   are located in a directory other than C:\DOS, you should adjust
   the commands accordingly.

5.6 Microsoft Defragmenter
--------------------------
If you received the "Insufficient Memory" message from Microsoft
Defragmenter, use the MEM command to determine how much conventional,
upper, and extended (XMS) memory is available. In addition to using
all available conventional memory, Defragmenter can make use of up
to 384K of extended memory and 12K of upper memory.

To increase available memory, carry out the procedures in "An MS-DOS
program displays an out-of-memory message" in the chapter "Diagnosing
and Solving Problems" in the MICROSOFT MS-DOS USER'S GUIDE.

If less than 384K of extended memory is available, carry out
the procedures in "Freeing Extended Memory" in the "Making More
Memory Available" chapter in the MICROSOFT MS-DOS USER'S GUIDE.


6. THIRD-PARTY PROGRAMS
=======================

6.1 4DOS and NDOS
-----------------
4DOS and NDOS are compatible with MS-DOS 6.  However, to use some of the
new features in MS-DOS 6.22 (such as MemMaker, the LOADHIGH /L switch,
DIR compression switches, and the ability to bypass startup commands),
contact JP Software to obtain 4DOS 4.02 or later, or Symantec to obtain
Norton Utilities 7.0 or later.
 
If you use multiple configurations, 4DOS or NDOS will not automatically
run your AUTOEXEC.BAT file unless you include a /P on the SHELL line in
your CONFIG.SYS file.
 
To use MS-DOS 6.22 Help instead of 4DOS or NDOS Help, start it by using
COMMAND /C HELP, or define a 4DOS or NDOS alias to run HELP.COM from
your MS-DOS 6.2 directory.

6.2 Above Board 286 and Above Board Plus Installation
    Programs
-----------------------------------------------------
Do not use an Above Board installation program dated May 1989
or earlier until you disable programs that use extended memory,
such as SMARTDrive or RAMDrive. You might lose data if you leave
these programs enabled. After you have installed Above Board,
you can reenable these programs.

6.3 CodeView
-----------
CAUTION  Using versions 3.0 to 3.13 of the CodeView CV.EXE
file may cause data loss if your system has an 80386 memory
manager (such as EMM386.EXE) and device drivers or programs
that use extended memory. To determine which version you
have, type CV.EXE at the command prompt.

6.4 Colorado Tape Backup
------------------------
If you receive a message that you have two versions of the
VFINTD.386 file loaded, you probably need to edit your
SYSTEM.INI file. To do so, carry out the following procedure:

1. Open your SYSTEM.INI file and locate the [386Enh] section.
   You should see two lines similar to the following:

   DEVICE=C:\TAPE\CMSDTAPE.386
   DEVICE=C:\DOS\VFINTD.386

2. If you plan to use your Colorado Tape Backup program, add a semi-
   colon (;) before the DEVICE command for the VFINTD.386 file. If you
   plan to use Microsoft Backup, add a semi-colon before the DEVICE
   command for the CMSDTAPE.386 file.

3. Save the file, and restart Windows.

6.5 Fastback Plus
-----------------
If you have a version of Fifth Generation Systems Fastback Pluse earlier
than 3.0, use the LOADFIX command before running Fastback Plus or the
Fastback Plus installation program to ensure that you don't lose data. To
do so, type the following at the command prompt:

LOADFIX FB.EXE

or

LOADFIX FBINSTAL.EXE

6.6 Norton Desktop for Windows 2.0
----------------------------------
Setup adds a second Tools menu which contains Microsoft Backup and
Antivirus commands (if you installed these Windows programs),
as well as a Compression Info command (if DoubleSpace or DriveSpace 
is installed).

If you use compress the drive that contains SmartCan, you might 
experience system problems afterward. To correct this, reinstall 
Norton Desktop for Windows.

For information about using Norton AntiVirus in conjunction with
DoubleSpace or DriveSpace, see the following section.

6.7 Norton Utilities
--------------------
Norton Speed Disk and Norton Disk Doctor versions 8.0 and earlier will 
not run on DriveSpace drives. For an updated version of these Norton 
utilities, contact your software vendor.

The "Clear Space" option of Norton Speed Disk (prior to version 7.0)
is incompatible with DoubleSpace drives and DriveSpace drives. For 
an updated version of Norton Speed Disk, contact your software vendor.

Do not use the WipeInfo utility (prior to version 8.0) on compressed 
drives. It can cause lost clusters. If you have already used this 
option, use the SCANDISK command to fix the lost clusters.

If Norton AntiVirus is running when you compress the drive that 
contains the NAV_.SYS file, a copy of the NAV_.SYS file remains 
on the host drive. This prevents Norton AntiVirus from reporting a 
virus infection during the compression process. After the compression 
process is complete, you can safely delete the copy of NAV_.SYS on 
the host drive.

If you use the Norton Cache or Speedrive utilities, load the utility
after the DEVICE command that loads DRVSPACE.SYS. For more information,
see section 7.24.

6.8 PC Tools
------------
If PC Shell does not show all of the files or directories on your drive, 
quit PC Shell immediately and contact Central Point Software for an update. 

CAUTION: Do not attempt to use PC Shell on that drive; severe data 
	 loss might occur. This problem affects both compressed and 
	 non-compressed drives. 

The DISKFIX /SCAN option in PC Tools can cause lost clusters on
DriveSpace and DoubleSpace drives. Avoid using this option. (If you 
have already used this option, use ScanDisk to fix the lost clusters.)

The COMPRESS command of PC Tools versions 6.0 and 5.5 
is incompatible with DoubleSpace and DriveSpace.

6.9  QEMM's Stealth DoubleSpace Feature
---------------------------------------
The Stealth DoubleSpace feature of QEMM versions 7.03 and 7.04 are 
fully compatible with MS-DOS 6.22; these versions are available to all 
QEMM 7 users through online services such as CompuServe, BIX, and the 
QuarterDeck BBS, as well as directly from QuarterDeck Office Systems.

The Stealth DoubleSpace driver (ST-DBL.SYS) included with version 7.02 is 
compatible with DoubleSpace, but not with DriveSpace, DEFRAG.EXE or 
automounting compressed floppies. If you use QEMM version 7.02, obtain an 
update from one of the online services listed above or from QuarterDeck 
Office Systems.

The Stealth DoubleSpace driver (ST-DBL.SYS) included with version 7.01 is 
incompatible with MS-DOS 6.22 (both DriveSpace and DoubleSpace). If you use 
QEMM version 7.01 and your system does not start, see the following section.

If you use the Stealth DoubleSpace feature of QEMM version 7.01
---------------------------------------------------------------
The Stealth DoubleSpace feature of QEMM 7.01 is incompatible with 
MS-DOS 6.22. If you are running DoubleSpace and use the Stealth DoubleSpace 
feature of QEMM version 7.01, your computer will not start properly. 

To work around this problem, press F8 when your computer starts.
Answer Y to all prompts except the following:  

    DEVICE=C:\QEMM\ST-DBL.SYS [Y/N]?

When MS-DOS displays this prompt, answer N. (The pathname for
ST-DBL.SYS may be different on your computer.) After your computer 
starts, edit your CONFIG.SYS file and make the following changes:

 * Disable the DEVICE command for ST-DBL.SYS by using the REM command.
 
 * If you use DoubleSpace, add a DEVICE command for DBLSPACE.SYS.
   For example:

   DEVICE=C:\DOS\DBLSPACE.SYS /MOVE

   (If you use DriveSpace, add a DEVICE command for DRVSPACE instead.)
   
6.10  Johnson Computer Systems PC-Vault and PC-Vault Plus
---------------------------------------------------------
If you use version 4.6 or earlier of the PC-Vault or PC-Vault Plus 
hard disk protection system, do not use the Maximum Floppy
Boot Protection option if you use DoubleSpace or DriveSpace.

In these versions of PC-Vault and PC-Vault plus, the Maximum Floppy 
Boot Protection option is incompatible with DoubleSpace and DriveSpace,
and may cause data loss. If your version of PC-Vault or PC-Vault Plus
is earlier than 4.6, contact Johnson Computer Systems for an upgrade.

6.11  AddStor Double Tools 
--------------------------
AddStor's Double Tools version 1.0 and 1.2 work only with DoubleSpace;
they do not work with DriveSpace.

AddStor's Double Tools version 1.0 works with MS-DOS 6.22 DoubleSpace
as long as you do not install AddStor's enhanced DoubleSpace drivers.
When you install Double Tools version 1.0, do not check the "Install 
enhanced DoubleSpace drivers" box. If you do, Double Tools will replace the 
MS-DOS 6.22 DBLSPACE.BIN file with the Double Tools version of DBLSPACE.BIN, 
which is compatible only with MS-DOS 6.0. The next time you start your 
computer, it will display the message "Wrong DBLSPACE.BIN version" and 
none of your compressed drives will be mounted. 

If you are using Double Tools version 1.0 or 1.2 with the enhanced
DoubleSpace driver installed, you will not be able to run MS-DOS 6.22
Setup. To solve this problem, run Double Tools' DTCONFIG.EXE program
and choose the "Microsoft" (version 1.0) or "Standard" (version 1.2)
option. Then save your changes, exit from DTCONFIG, and run MS-DOS 
6.22 Setup again.


7. DRIVESPACE
=============
MS-DOS 6.22 includes DriveSpace compression software. DriveSpace appears
similar to DoubleSpace, which was included with MS-DOS 6 and 6.2. The
main difference is that DriveSpace stores compressed data in a different
format from DoubleSpace. 

Note: If you upgraded from MS-DOS 6 or MS-DOS 6.2, you can still use
      DoubleSpace with MS-DOS 6.22. (If you upgraded from MS-DOS 5 or 
      earlier, you do not have DoubleSpace on your system.)

7.1 Converting DoubleSpace Drives to DriveSpace
-----------------------------------------------
If you currently use DoubleSpace, you can continue using it with MS-DOS 
6.22. Or, you can convert your system and all your DoubleSpace drives to 
DriveSpace.

NOTE  If you purchased the English version of the MS-DOS 6.22 Upgrade, 
      you can obtain DoubleSpace conversion by sending in the enclosed 
      coupon; if you purchased the MS-DOS 6.22 Step-Up or non-English 
      version of MS-DOS 6.22, your version of MS-DOS 6.22 already includes 
      DoubleSpace conversion.)

To convert your system from DoubleSpace to DriveSpace:

1. Back up the data on each DoubleSpace drive, if you have not already
   done so.

2. Type DRVSPACE at the command prompt, and then follow the instructions 
   on your screen. 
   
   DriveSpace converts all mounted DoubleSpace drives to DriveSpace format,
   and also converts your system to run DriveSpace instead of DoubleSpace.

NOTE  The conversion process can take a long time, especially if your 
      DoubleSpace drives contain a lot of data. You might want to plan
      to carry out the conversion process overnight.

7.2 Converting Your XtraDrive Disk-Compression Software
    to DriveSpace
-------------------------------------------------------
If your computer uses XtraDrive disk compression, use its
uninstallation program to remove the compression, and then
install DriveSpace.

7.3  Converting Stacker 3.1 Software to DriveSpace
--------------------------------------------------
If your drive has been compressed using Stacker version 3.1, carry
out the following procedure to remove Stacker 3.1 and install
DriveSpace. (If you use Stacker 2.x or 3.0 software, carry out 
the procedure in section 7.4 instead.)

1. Use Stacker's UNSTACK command to unstack all your Stacker drives.
   (If you have floppy disks compressed by using Stacker, either
   unstack them now or make sure they were configured using Stacker's
   StackerAnywhere feature.)

2. Change to the root directory of your startup hard disk drive,
   and then type the following commands:

   ATTRIB -R -H -S STACKER.INI
   ATTRIB -R -H -S DRVSPACE.BIN
   DEL STACKER.INI
   DEL DRVSPACE.BIN
   
3. Restart your computer.

4. Run DriveSpace Setup by typing DRVSPACE at the command prompt.

7.4  Converting Other Disk-Compression Software to DriveSpace
-------------------------------------------------------------
If you are not using Stacker 3.1 disk compression or XtraDrive 
disk compression, carry out the following procedure to convert 
your disk-compression software to DriveSpace.

1. Install MS-DOS 6.22 if you haven't already done so.

2. Use Microsoft Backup for MS-DOS to back up the files on your
   hard disk. If you didn't install Backup for MS-DOS during Setup,
   see the chapter "Getting Started" in the MICROSOFT MS-DOS USER'S
   GUIDE for instructions on installing it.

3. If your Setup disks are compatible with drive A, insert
   Setup Disk 1 in drive A, and restart your computer. After
   Setup displays the first screen, quit Setup by pressing F3 twice.

   If your Setup disks are not compatible with drive A,
   create a startup floppy disk for drive A. To do this, insert
   Setup Disk 1 in drive B, and a blank floppy disk in drive A.
   Then type B:SETUP /F at the command prompt.
  
   When prompted, choose to install MS-DOS on the floppy disk
   in drive A. After Setup is finished, leave the disk in drive A,
   and restart your computer.

4. Use the FORMAT command to format the drive that contains the
   file that contains all of your compressed files. If you don't know
   where this file is located, see your disk-compression documentation.

   If you are reformatting drive C, include the /S switch to transfer
   system files to it.

5. If you formatted drive C, make sure Setup Disk 1 is in drive A
   or B, and type A:SETUP or B:SETUP at the command prompt.

   Follow the instructions on your screen.

6. After Setup is complete, install DriveSpace by typing DRVSPACE
   at the command prompt. Follow the instructions on your screen.

7. Use Backup for MS-DOS to restore the files you backed up.

   NOTE  When you run Microsoft Backup, you will have to configure it
   again. Also, you will need to retrieve the catalog file from your
   backup floppy disks. To do so, choose the Catalog button in the
   Restore dialog box.

7.5 DriveSpace Setup indicates that your computer is running an
    incompatible disk-caching program.
----------------------------------------------------------------
If DriveSpace Setup displays a message indicating your computer is
running an incompatible disk-caching program, open your CONFIG.SYS or
AUTOEXEC.BAT file, and delete the command that loads your
disk-caching program. If you want to use a disk cache, add a line for
the MS-DOS 6.22 SMARTDRV program in your AUTOEXEC.BAT file. For example,
if your MS-DOS files are in a directory named DOS, add the following
line:

C:\DOS\SMARTDRV.EXE

Quit your text editor, and restart your computer. Run DriveSpace again.

7.6 Your compressed drive runs out of disk space.
-------------------------------------------------
If your compressed drive runs out of free disk space, you can
use the following techniques to free some space on the drive:

o Enlarge that drive.

o Carry out the DRVSPACE /DEFRAG /F and DRVSPACE /DEFRAG commands
  on that drive.

The rest of this section explains each technique.

Enlarging a Compressed Drive
----------------------------
You can enlarge a compressed drive to make more space available on it.
Enlarging a compressed drive uses free space on the uncompressed (host)
drive.

To enlarge the compressed drive:

1. Start the DriveSpace program by typing DRVSPACE at the command prompt.

2. Select the compressed drive you want to enlarge, and then choose
   the Change Size command from the Drive menu.

   The Change Size dialog box appears. The New Free Space line shows how
   much free space the compressed and uncompressed drives will have if you
   choose OK.

3. Specify a smaller number for New Free Space on the uncompressed
   drive. Notice that as you change this number, DriveSpace adjusts
   the New Free Space amount for the compressed drive. When the New Free
   Space amount for both drives is what you want, choose OK.

   DriveSpace enlarges the compressed drive.

Carrying Out the DRVSPACE /DEFRAG /F and DRVSPACE /DEFRAG Commands
on your Compressed Drive
------------------------------------------------------------------
You can sometimes free additional space on a compressed drive by
more fully defragmenting the drive. 

NOTE  You might want to carry out the following procedure overnight, since
defragmenting a large or badly fragmented drive can take a long time.
(To carry out the entire procedure overnight, create a batch file that
contains both the commands in the procedure.)

To free space by defragmenting the drive twice:

1. Make the compressed drive the current drive.

2. Type DEFRAG drive: /F at the command prompt

   Where drive: is the compressed drive. For example, DEFRAG C: /F.
   DEFRAG will fully defragment the drive's file allocation table,
   then start DRVSPACE /DEFRAG to consolidate the free space in
   the CVF.

3. When DEFRAG finishes, type DRVSPACE /DEFRAG /F at the command prompt.

   DriveSpace re-consolidates the free space on the drive so there
   is as much free space as possible.

7.7 Your uncompressed (host) drive runs out of disk space
---------------------------------------------------------
If your uncompressed (host) drive runs out of free disk space, you
can enlarge it by reducing the size of any compressed drives that are
stored on that uncompressed drive. Of course, this will reduce the
amount of free space on the compressed drive(s).

To enlarge the uncompressed (host) drive:

1. Start the DriveSpace program by typing DRVSPACE at the command prompt.

2. Select the compressed drive whose size you want to reduce, and then
   choose the Change Size command from the Drive menu. (Select
   a compressed drive that is stored on the uncompressed drive that's
   out of space. To find out which compressed drives are stored
   on that uncompressed drive, type DRVSPACE /LIST at the command prompt.)

   The Change Size dialog box appears. The New Free Space line shows
   how much free space the compressed and uncompressed drives will have
   if you choose OK.

3. Specify a larger number for the New Free Space on the uncompressed
   drive. Notice that as you change this number, DriveSpace adjusts
   the New Free Space amount for the compressed drive. When the New Free
   Space amount for both drives is what you want, choose OK.

   DriveSpace reduces the size of the compressed drive, which makes
   more free space available on the corresponding uncompressed drive.

7.8 DriveSpace did not compress all of your files because
    the drive ran out of disk space.
----------------------------------------------------------
If DriveSpace indicates that it could not compress some
of your files because there was not enough disk space, carry
out the following procedure.

1. To determine which drive is your uncompressed drive, type
   DRVSPACE /LIST at the command prompt.

2. Using Microsoft Backup, back up to floppy disks the files
   on the uncompressed drive that were not compressed.

3. Delete the files on the uncompressed drive that were not compressed.

4. Type DRVSPACE at the command prompt.

5. From the Drive menu, choose Change Size.

6. To increase the size of your compressed drive, decrease the size
   of your uncompressed drive, and choose OK.

7. From the Drive menu, choose Exit, and use Backup to restore
   the files you backed up to your compressed drive. If you run out of
   space again, repeat steps 5 through 7 until the compressed drive
   is large enough.

7.9 Windows displays the message "The permanent swap file is corrupt."
----------------------------------------------------------------------
If you use a Windows permanent swap file, it must be located on an
uncompressed drive. If your permanent swap file is on a compressed
drive, Windows displays the message "The permanent swap file is corrupt"
when it starts.

When you install DriveSpace, the DriveSpace Setup program checks for
the existence of a Windows permanent swap file. If it finds one,
DriveSpace Setup moves the swap file to your uncompressed drive.
However, if you install Windows after installing DriveSpace, or if you use
Control Panel to change the location of your permanent swap file, your
swap file might end up on a compressed drive. (When you specify a drive
for your permanent swap file, Windows allows you to choose a compressed
drive.)

To move your permanent swap file to an uncompressed drive:

1. Start Windows.

2. At the "Permanent swap file is corrupt" screen, type Y in response
   to the question "Do you want to delete this swap file?", and
   then press ENTER.

3. Open Control Panel, and then Drive-click the 386 Enhanced icon.

4. Choose the Virtual Memory button. Windows displays a dialog box stating
   that a corrupt swap file was found and asks if you want to set the
   file's length to zero.

5. Choose the Yes button. Windows displays another Virtual Memory dialog box.

6. Choose the Change button. Windows displays swap-file settings.

7. In the Drive list box, select a drive that is not compressed. In the
   Type list box, select "Permanent."

   If your uncompressed drive does not have enough free space to create a
   permanent swap file, create a temporary swap file on either your
   compressed or uncompressed drives. (For information about freeing
   space on your uncompressed drive, see section 7.7.)

   When you have finished specifying swap-file settings, choose OK twice,
   and follow the instructions on your screen.

7.10  EXTDISK.SYS displays a warning about drive letters.
---------------------------------------------------------
If you are using DriveSpace on a Compaq computer, and your CONFIG.SYS file
loads the EXTDISK.SYS device driver, EXTDISK.SYS displays the following
message when it loads:

WARNING: EXTDISK.SYS is not the first device driver to assign drive
	 letters. Physical hard drive letters will not be contiguous.

The EXTDISK.SYS driver still works properly. It displays this message
because it expects to be the first module to assign drive letters,
but because DRVSPACE.BIN loads before the CONFIG.SYS file and assigns
some drive letters, EXTDISK.SYS is no longer first. (EXTDISK.SYS
displays the message regardless of when the DRVSPACE.SYS device
driver is loaded in the CONFIG.SYS file.)

7.11 You need a special device driver to use your startup drive
---------------------------------------------------------------
If your startup hard disk drive requires a device driver in your CONFIG.SYS
file, do not compress that drive. If you do, your computer will not
start properly, since DriveSpace will be unable to access your startup
drive. (This is because MS-DOS loads DRVSPACE.BIN, the portion of MS-DOS
that accesses compressed drives, before starting any of the device drivers
in your CONFIG.SYS file.)

To install DriveSpace on a computer with a startup drive that requires a
special device driver, use DriveSpace Setup to compress a drive other than
your startup drive, or use DriveSpace Setup to create a new compressed
drive using free space on any existing drive.

7.12 Defragmenting uncompressed drives after changing file attributes
---------------------------------------------------------------------
You can safely defragment both your compressed or uncompressed
drives, using the Microsoft Defragmenter or another defragmentation
program, as long as you do not change the attributes of your
compressed volume files.

CAUTION  If you change the attributes of a compressed volume file,
	 and then defragment that uncompressed drive without first
	 unmounting the compressed drives, you might lose data.

If you want to fully defragment your uncompressed drive, you must
first unmount all compressed drives located on the uncompressed
drive, remove all their attributes, and then use DEFRAG or another
defragmenter.

7.13  Files DriveSpace cannot compress
--------------------------------------
Some files (such as .ZIP files) are already compressed. DriveSpace
might not be able to compress such files any further.

Encrypted data files, such as the Microsoft Mail 3.0 .MMF file, are
not compressible and will be stored in uncompressed form, even if
you store such files on a compressed drive.

You might want to store uncompressible files on an uncompressed drive
rather than on a compressed drive. Doing so can sometimes improve
your system's speed.

7.14 Microsoft Defragmenter runs out of memory while you are compressing
     a drive
------------------------------------------------------------------------
If the Defragmenter runs out of memory while you are compressing a
drive, quit DriveSpace, and then carry out the procedure in section
5.4 of this file.

If the Defragmenter still runs out of memory after you have tried
these procedures, there might be too many files on your hard disk
for the Defragmenter to organize. For the program to work correctly,
you might need to delete some files or move them to a floppy disk or
a network drive.

7.15 DriveSpace and PC-Vault
-----------------------------
See section 6.10.
  
7.16 Maximum size of a compressed drive
---------------------------------------
The maximum size for a DriveSpace compressed drive is 512 megabytes (MB).
For example, if you compress a disk drive that is 600 MB, the resulting
DriveSpace drive will be no larger than 512 MB. To compress the rest of
the disk drive, run DriveSpace, and choose Create New Drive from the 
Compress menu. Make the new compressed drive as large as possible.
(If your drive is very large, you might need to create several new 
compressed drives in order to compress the entire drive.)

7.17  DriveSpace could not mount a drive due to problems with the drive
-----------------------------------------------------------------------
If the message "DriveSpace could not mount drive X due to problems
with the drive" (in which X is the drive letter) appears when you start
your computer, then the internal organization of the drive has problems
that prevent the drive from being used. DriveSpace stores each
compressed drive in a special file called a compressed volume file (CVF).
The CVF is a file with the hidden, system, and read-only attributes; it
is stored on an uncompressed drive.

To use the compressed drive again, you need to run ScanDisk on that
drive's compressed volume file, and then restart your system. The
error message includes the name of the compressed volume file on which
you need to run ScanDisk (for example, C:\DRVSPACE.000).

To fix this problem for a compressed drive other than drive C:

  o  Type the SCANDISK command specified by the DriveSpace error
     message. For example, SCANDISK D:\DRVSPACE.001. (If MS-DOS cannot
     find the SCANDISK program, see the following procedure.)

To fix this problem for compressed drive C, or if MS-DOS cannot find
the SCANDISK program:

1. Insert Setup Disk 1 in drive A (or B) of your computer.

2. Change to the drive that contains Setup Disk 1.

3. To start ScanDisk, type the SCANDISK command as specified by
   the DriveSpace error message. For example, SCANDISK C:\DRVSPACE.000.
   When ScanDisk displays dialogs describing any problems, choose
   the Fix It button.

4. After ScanDisk has finished, remove the floppy disk and restart
   your computer.

7.18  DriveSpace finishes installation, but you cannot access your Hardcard
----------------------------------------------------------------------------
See section 4.2, part C.

7.19  You receive a DoubleGuard Alarm message
---------------------------------------------
If a DoubleGuard Alarm message appears, DoubleGuard has detected that
an application has damaged memory that DriveSpace was using. DoubleGuard
halts your computer to prevent any further damage to your data. 

Normally, each program "owns" a separate area of memory, and does not use
memory that another program is already using. However, a few programs
contain programming errors that cause them to inadvertently use memory
belonging to another program. If such a program inadvertently uses
memory belonging to DriveSpace, that program could write its own
data over the data DriveSpace was storing there. Since the data that
DriveSpace stores in memory usually includes files you are currently
using, this could cause damage to your data. 

DriveSpace's DoubleGuard safety-checking feature detects when another
program has violated DriveSpace's memory, and immediately shuts down
your computer to minimize the chance of data loss. (If further disk
activity were to occur instead, you could lose some or all of the 
data on your drive, since the data DriveSpace has in memory is probably
invalid due to damage by the other program.)

If you receive a DoubleGuard Alarm message, do the following:

1. Restart your computer by turning the power switch off and then 
   on again.

2. Type the following at the command prompt:

     SCANDISK /ALL

   This runs ScanDisk on all your drives to detect and correct any
   problems that might have been caused by the program that
   violated DriveSpace's memory.

3. Make a note of which program, if any, you were running when the
   DoubleGuard Alarm occurred. That program is probably (but not
   necessarily) the program that caused the DoubleGuard Alarm.
   If you receive additional DoubleGuard Alarms, take notes about
   what you were doing and see if you can detect a pattern.

7.20  A compressed drive is currently too fragmented to mount
-------------------------------------------------------------
If you receive the message "Compressed drive X is currently too
fragmented to mount" (in which X is the drive letter) when your
computer starts, or if DriveSpace displays the message "The
X:\DRVSPACE.nnn file is too fragmented to mount," then DriveSpace
cannot mount the drive because its compressed volume file is stored in
too many fragments on your hard disk. (DriveSpace stores each
compressed drive in a special file called a compressed volume file (CVF).
The CVF is a file with the hidden, system, and read-only attributes, and
is stored on an uncompressed drive.)

To correct this problem, increase the MaxFileFragments setting in your
DRVSPACE.INI file. DriveSpace displays the "too fragmented to mount"
error messages because the number of CVF file fragments exceeds this
setting. Follow these steps:

1. Change to the root directory of your startup drive. (If your
   startup drive is compressed, change to that drive's host drive.)

2. Type the following command:

     TYPE DRVSPACE.INI

3. Note the current value for the MaxFileFragments setting.

4. Use the DRVSPACE /MAXFILEFRAGMENTS command to specify a higher value.
   For example, if MaxFileFragments is currently set to 128, you might
   type the following command:

     DRVSPACE /MAXFILEFRAGMENTS=200

5. Restart your computer. DriveSpace should now be able to mount
   the drive.

If DriveSpace still cannot mount the drive, follow these steps:

1. Run ScanDisk to check the reliability of your hard disk by typing the
   following at the command prompt:

      SCANDISK /ALL /SURFACE

2. Restart your computer. If DriveSpace still cannot mount the drive,
   proceed to step 3.

3. Remove the Read-Only, System, and Hidden file attributes on the
   DRVSPACE.<XXX> file. For example, if the file is H:\DRVSPACE.000,
   type the following at the command prompt:

       ATTRIB H:\DRVSPACE.000 -R -S -H

4. Run Microsoft Defragmenter (Defrag) by typing DEFRAG at the
   command prompt.

5. Use the ATTRIB command to reset the file attributes on DRVSPACE.<XXX>.
   For example, if the file is H:\DRVSPACE.000, type the following at
   the command prompt:

       ATTRIB H:\DRVSPACE.000 +R +S +H

6. Restart your computer again. DriveSpace should now be able to mount
   the compressed drive.

7.21  You receive the message "Your computer is running with an
      incompatible version of DBLSPACE.BIN" 
----------------------------------------------------------------
If you try to run the MS-DOS 6 version of DBLSPACE.EXE with MS-DOS 6.2,
it displays the following message:

  Your computer is running with an incompatible version of DBLSPACE.BIN.
  You must update DBLSPACE.BIN on the root directory of drive @.

DBLSPACE.EXE has detected that its version number does not match that 
of your MS-DOS 6.2 DBLSPACE.BIN. To correct this problem, you need to
update this copy of the DBLSPACE.EXE file.

When you run MS-DOS 6.22 Setup, it updates the DBLSPACE.EXE file in
the directory that contains your MS-DOS files. If there are other
copies of DBLSPACE.EXE elsewhere on your disk -- for example, in the root
directory of your host drive -- Setup does not update those additional
copies. To update them yourself, use the COPY /Y command to copy the 
MS-DOS 6.22 version of DBLSPACE.EXE over the older versions. (The MS-DOS
6.22 version of DBLSPACE.EXE is located in the directory that contains
your MS-DOS files.)

7.22  Using the DRVSPACE command after bypassing DRVSPACE.BIN
-------------------------------------------------------------
If you bypass DRVSPACE.BIN when you start your computer (by pressing
CTRL+F5 or CTRL+F8), then the DRVSPACE command may not work as
expected:

 * Usually, if DriveSpace is installed, typing DRVSPACE runs the
   DriveSpace program. However, if you type DRVSPACE when 
   DRVSPACE.BIN is not loaded, DriveSpace Setup starts instead. 
   If this happens, quit DriveSpace Setup. 

 * If you type the DRVSPACE /MOUNT command, it reports that there
   are no more drive letters for DriveSpace to use. (DriveSpace
   cannot mount a compressed drive unless DRVSPACE.BIN is loaded.)

To use DriveSpace or your compressed drives, restart your computer
without bypassing DRVSPACE.BIN.

7.23  Removing the write-protection from a compressed floppy disk
-----------------------------------------------------------------
If you are using a compressed floppy disk that is write-protected
and Automounting is enabled, the disk will remain write-protected
until it is unmounted -- even if you remove the write-protect tab 
from it.

To remove the write protection, use either of the following methods:

 * Unmount the floppy disk by using the DRVSPACE /UNMOUNT command, 
   and then try using the disk again (this will automatically 
   remount it). For example, if the disk is in drive B, you would
   type DRVSPACE /UNMOUNT B: and then try using the disk again.
   (If Windows is running, you can't use the DRVSPACE /UNMOUNT
   command. In that case, use the following method.)

 * Insert a different floppy disk in the drive and access it (for
   example, carry out the DIR command on it). This automatically
   unmounts the compressed floppy disk that was previously in the
   drive.) Then, reinsert the compressed floppy disk and try using
   it again (this will automatically remount it).

NOTE  If you are using DriveSpace and mount an unconverted DoubleSpace 
      floppy disk, the disk will be mounted with write-protected.
      The only way to remove the write protection on such a disk is
      to convert it to DriveSpace format; for information on converting
      it, see section 7.1.

7.24  Automounting and Norton disk-caching utilities
----------------------------------------------------
If you use a Norton disk-caching utility such as Norton Cache 
(NCACHE2.EXE) or Norton Speedrive (SPEEDRV.EXE) make sure the 
utility is loaded after the DEVICE command for DRVSPACE.SYS. 
If you load one of these utilities before DRVSPACE.SYS, 
DriveSpace's automounting feature will not work.

7.25  Undelete utilities and DriveSpace
----------------------------------------
DriveSpace cannot compress or uncompress drives while an undelete 
utility (for example, Microsoft Undelete's Delete Sentry or Norton's
SmartCan) is running. To compress or uncompress a drive, you will need 
to temporarily disable the undelete utility. Follow these steps:

1. Purge any previously deleted files to conserve disk space. If you 
   are using Microsoft Delete Sentry, type the following at the command 
   prompt:

   UNDELETE /PURGE

   Carry out this command on each drive you plan to compress or uncompress. 
   If you will be uncompressing a drive, you should also purge deleted 
   files from that drive's host drive. To purge deleted files from a 
   drive other than the current drive, specify the drive letter after
   the UNDELETE /PURGE command (for example, UNDELETE /PURGE E:).

   If you use a different undelete utility, see that utility's 
   documentation for information about purging deleted files.

2. Edit your AUTOEXEC.BAT file and use the REM command to disable 
   the command that starts the undelete utility. (For example, if 
   you use Delete Sentry, disable the UNDELETE /S command.)

3. Restart your computer.

4. Try again to compress or uncompress the drive.

5. When you have finished compressing or uncompressing, edit your 
   AUTOEXEC.BAT file, reenable the command that starts the undelete
   utility, and then restart your computer again.

7.26  Creating an Emergency Startup Disk for DriveSpace Systems
---------------------------------------------------------------
To create an MS-DOS 6.22 startup disk if you use DriveSpace:

1. If you are upgrading from MS-DOS 6.0, install MS-DOS 6.22 in the 
   directory that contains your previous version of MS-DOS. 
   
2. To create a startup floppy disk, run Setup again by typing the following 
   command:

   SETUP /F

   Setup installs MS-DOS 6.22 on the floppy disk. The resulting startup disk
   does not include DRVSPACE.BIN, since MS-DOS 6.22 does not include 
   DriveSpace.

3. Add the DRVSPACE.BIN file to the floppy disk by copying it from the
   directory that contains your MS-DOS files. For example, if your MS-DOS
   directory is C:\DOS and the floppy disk is in drive A, you would type:

   COPY C:\DOS\DRVSPACE.BIN A:

Note: If you are upgrading from MS-DOS 6 but need to install to the 
      floppy disk without first installing MS-DOS 6.22 on your hard disk, 
      you can skip Step 1. However, the resulting startup disk will include 
      MS-DOS 6 DoubleSpace rather than MS-DOS 6.2 DoubleSpace. When you 
      start your computer using such a startup disk, you will receive a 
      message from DoubleSpace; to continue, just press ENTER.

7.27  If ScanDisk Cannot Check or Repair a DoubleSpace Volume File
------------------------------------------------------------------
MS-DOS 6.22 ScanDisk can check DoubleSpace drives or volume files only 
if one of the following conditions is true:

 * DoubleSpace is installed and DBLSPACE.BIN is loaded into memory.
  
 * Both the DBLSPACE.BIN and DRVSPACE.MR1 files are available -- located 
   together in the root directory or the directory that contains your 
   MS-DOS files. (For information about the DRVSPACE.MR1 file, see 
   Section 7.28 of this file.)

Otherwise, ScanDisk displays a message like the following:

   ScanDisk cannot check or repair DoubleSpace volume file D:\DBLSPACE.001.

If you receive this message, one of the following might be the cause 
of the problem:

 *  DoubleSpace is not installed and the DBLSPACE.BIN and/or DRVSPACE.MR1 
    files are unavailable or are not in the same directory. These files must 
    be together in the root directory or the directory that contains your 
    MS-DOS files. (For information about the DRVSPACE.MR1 file, see 
    Section 7.28.)

 *  DoubleSpace is installed on your system, but you started your
    computer from a floppy disk or by pressing CTRL+F5 or CTRL+F8. If this 
    is the case, remove any floppy disks from your drives, restart your 
    computer, and try running ScanDisk again. 

 *  You upgraded to MS-DOS 6.22 from a version of MS-DOS that did not
    include DoubleSpace (MS-DOS version 5 or earlier, or MS-DOS 6.21). 
    If your previous version of MS-DOS did not include DoubleSpace,
    you cannot use ScanDisk to check DoubleSpace drives.

7.28  DoubleSpace and the DRVSPACE.MR1 File
-------------------------------------------
In conjunction with the DBLSPACE.BIN file, the DRVSPACE.MR1 file enables 
DriveSpace and ScanDisk to work with DoubleSpace drives and volume files. 
These files also enable MS-DOS 6.22 Backup to work with compressed backups 
stored in the MS-DOS 6 data compression format.

NOTE  The DRVSPACE.MR1 file is included with DoubleSpace conversion. 
      If you purchased the English version of the MS-DOS 6.22 Upgrade, 
      you can obtain DoubleSpace conversion by sending in the enclosed 
      coupon; if you purchased the MS-DOS 6.22 Step-Up or the non-English 
      version of MS-DOS 6.22, your version of MS-DOS 6.22 already includes 
      conversion and the DRVSPACE.MR1 file.)

In conjunction with the DBLSPACE.BIN file, the DRVSPACE.MR1 file enables 
DriveSpace to:

 * Convert DoubleSpace drives to DriveSpace format. (To convert a drive,
   run DriveSpace, and then choose Convert DoubleSpace from the Tools menu.)

 * Mount unconverted DoubleSpace drives for read-only access. The data
   on the drive will be available, but the drive will be write-protected,
   so you will not be able to change or add to the data on the drive.

In conjunction with the DBLSPACE.BIN file, the DRVSPACE.MR1 file enables 
ScanDisk to check and repair unconverted DoubleSpace drives and volume files.

In addition, the DBLSPACE.BIN and DRVSPACE.MR1 files enable MS-DOS 6.22
Backup to read older compressed backups. For more information, see Section
5.5 of this file.

7.29  Using unconverted DoubleSpace drives with DriveSpace
----------------------------------------------------------
If you mount a DoubleSpace drive under the circumstances described in 
section 7.28, DriveSpace will mount the drive write-protected (read-only).
This means that you cannot change the drive or the data it contains. 
To change a DoubleSpace drive or the data on it, you must first convert 
the drive to DriveSpace format. To do this, choose the Convert DoubleSpace 
command from the Tools menu. (You must have the DRVSPACE.MR1 file in 
order to do this; for more information, see section 7.28.)

7.30  If a partially converted drive cannot be mounted
------------------------------------------------------
Normally, when DriveSpace converts a DoubleSpace drive, the drive is 
completely converted to DriveSpace format. However, if the power is 
interrupted during conversion, or something else prevents the conversion 
process from completing, the drive will remain in a partially converted 
state.

To mount a partially converted drive if you are using DriveSpace, you must 
first convert the drive to DriveSpace format. To do this, choose the 
Convert DoubleSpace command from the Tools menu. (You must have the 
DRVSPACE.MR1 file in order to do this; for more information, see section 
7.28.) DriveSpace will then convert and mount the drive.

To mount a partially converted drive if you are using DoubleSpace, you must 
first convert your system to DriveSpace. (For more information, see section
7.1.) After you have converted your system to DriveSpace, convert the 
partially-converted drive to DriveSpace format by choosing the Convert 
DoubleSpace command from the Tools menu. (You must have the DRVSPACE.MR1 
file in order to do this; for more information, see section 7.28.)




