/* 
http://forum.parallels.com/showthread.php?t=577

We've been using VT (for our own experiments) on the Mac Mini for a while. It is simple to enable, and involves modifying the EFI Setup variable. Potentially this modification can be made via the kernel API used by the nvram utility under Mac OS X, but we use an EFI utility.

The solution is to change byte 0xe7 of the Setup variable from 0 to 1. This causes the firmware to configure the ia32_feature_control MSR with value 5. After you change the variable, you must reboot via a hard reset (since the MSR is a write-once register). I had to unplug my machine from the power supply to clear the prior contents of my MSR.

Here is our EFI utility. We build it under the GNU environment, and I load it using the rEFIt boot loader on a USB stick. From our experience, it doesn't interfere with the BootCamp firmware update. We observed that Parallels Workstation successfully detects VT on the Mini. 

*/

/**** Use at your own risk! *****/

#include <efi.h>
#include <efilib.h>

EFI_BOOT_SERVICES *BS;
EFI_RUNTIME_SERVICES *RS;
EFI_HANDLE IMAGE;

EFI_GUID guid_apple = // 4DFBBAAB-1392-4FDE-ABB8-C41CC5AD7D5D
{0x4DFBBAAB, 0x1392, 0x4FDE, {0xAB, 0xB8, 0xC4, 0x1C, 0xC5, 0xAD, 0x7D, 0x5D}};

EFI_STATUS
efi_main( EFI_HANDLE image, EFI_SYSTEM_TABLE *system_table )
{
EFI_STATUS status;
UINT32 attr = 0;
unsigned char data[0xfe];
UINTN data_size = sizeof(data);

BS = system_table->BootServices;
RS = system_table->RuntimeServices;
IMAGE = image;

InitializeLib( image, system_table ); // Initialize the EFI library.

status = RS->GetVariable( L"Setup", &guid_apple, &attr, &data_size, data );
if( status == EFI_SUCCESS ) {
data[0xe7] = 1;
status = RS->SetVariable( L"Setup", &guid_apple, attr, data_size, data )
;
if( status != EFI_SUCCESS )
Print( L"failure changing variable\n" );
}

BS->Exit( image, status, 0, NULL );
return status;
}


