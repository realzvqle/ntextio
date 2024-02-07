#include "headers/ntfunc.h"
#include <libloaderapi.h>







int wvsprintA(LPSTR param1, LPCSTR param2, va_list arglist){
    HMODULE user32 = GetModuleHandleA("user32.dll");
    if(!user32){
        return -9;
    }
    wvsprintfptr wvsprint = (wvsprintfptr)GetProcAddress(user32, "wvsprintfA");
    if(!wvsprint){
        return -10;
    }
    int result = wvsprint(param1, param2, arglist);

    return result;
}

void KdPrint(_In_z_ _Printf_format_string_ PCHAR Format ,...){
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if(!ntdll){
        return;
    }
    KdPrintPtr kdprint = (KdPrintPtr)GetProcAddress(ntdll, "KdPrint");
    if(!kdprint){
        return;
    }
    kdprint(Format);
    FreeLibrary(ntdll);
}

ULONG DbgPrint(PCHAR Format, ...){
    HANDLE ntdll = GetModuleHandleA("ntdll.dll");
    if(!ntdll){
        return -282;
    }
    DbgPrintPtr dbgprint = (DbgPrintPtr)GetProcAddress(ntdll, "DbgPrint");
    if(!dbgprint){
        return -47;
    }
    ULONG result = dbgprint(Format);
    FreeLibrary(ntdll);
    return result;
}

NTSTATUS NtClose(HANDLE Handle){
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if(!ntdll){
        return (NTSTATUS)1;
    }
    NtClosePtr ntclose = (NtClosePtr)GetProcAddress(ntdll, "NtClose");
    if(!ntclose){
        return (NTSTATUS)1;
    }
    NTSTATUS result = ntclose(Handle);
    FreeLibrary(ntdll);
    return result;

}

VOID RtlInitUnicodeString(PUNICODE_STRING DestinationString, PCWSTR SourceString) {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if (!ntdll) {
        KdPrint(("Failed Opening ntdll\n"));
        return;
    }

    RtlInitUnicodeStringPtr rtl = (RtlInitUnicodeStringPtr)GetProcAddress(ntdll, "RtlInitUnicodeString");
    if (!rtl) {
        KdPrint(("Failed Getting Address Of RtlInitUnicodeString\n"));
        return;
    }

    rtl(DestinationString, SourceString);
    FreeLibrary(ntdll);

}


NTSTATUS NtCreateFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength) {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if (!ntdll) {
        KdPrint(("Failed Opening ntdll\n"));
        return STATUS_DLL_NOT_FOUND;
    }

    NtCreateFilePtr ntcreatefile = (NtCreateFilePtr)GetProcAddress(ntdll, "NtCreateFile");
    if (!ntcreatefile) {
        KdPrint(("Failed Getting Address Of NTCreateFile\n"));
        return STATUS_ACCESS_VIOLATION;
    }

    NTSTATUS status = ntcreatefile(FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, EaBuffer, EaLength);
    FreeLibrary(ntdll);
    return status;
}


NTSTATUS NtReadFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE  ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG Key){
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if(!ntdll){
        return STATUS_DLL_NOT_FOUND;
    }
    NtReadFilePtr ntreadfile = (NtReadFilePtr)GetProcAddress(ntdll, "NtReadFile");
    if(!ntreadfile){
        return STATUS_DLL_INIT_FAILED;
    }
    NTSTATUS status = ntreadfile(FileHandle, Event, ApcRoutine, ApcContext, IoStatusBlock, Buffer, Length, ByteOffset, Key);
    FreeLibrary(ntdll);
    return status;
}

NTSTATUS NtWriteFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE  ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG Key){
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if(!ntdll){
        return STATUS_DLL_NOT_FOUND;
    }
    NtWriteFilePtr ntwritefile = (NtReadFilePtr)GetProcAddress(ntdll, "NtWriteFile");
    if(!ntwritefile){
        return STATUS_DLL_INIT_FAILED;
    }
    NTSTATUS status = ntwritefile(FileHandle, Event, ApcRoutine, ApcContext, IoStatusBlock, Buffer, Length, ByteOffset, Key);
    FreeLibrary(ntdll);
    return status;
}

NTSTATUS NtQueryInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILEE_INFORMATION_CLASS FileInformationClass){
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if(!ntdll){
        return STATUS_DLL_NOT_FOUND;
    }
    NtQueryInformationFilePtr ntqueryinformationfile = (NtQueryInformationFilePtr)GetProcAddress(ntdll, "NtQueryInformationFile");
    if(!ntqueryinformationfile){
        return STATUS_DLL_INIT_FAILED;
    }
    NTSTATUS status = ntqueryinformationfile(FileHandle, IoStatusBlock, FileInformation, Length, FileInformationClass);
    FreeLibrary(ntdll);
    return status;
}

NTSTATUS NtWaitForSingleObject(HANDLE Handle, BOOLEAN Alertable, PLARGE_INTEGER Timeout){
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if(!ntdll){
        return STATUS_DLL_NOT_FOUND;
    }
    NtWaitForSingleObjectPtr ntwaitforsingleobject = (NtWaitForSingleObjectPtr)GetProcAddress(ntdll, "NtWaitForSingleObject");
    if(!ntwaitforsingleobject){
        return STATUS_DLL_INIT_FAILED;
    }
    NTSTATUS status = ntwaitforsingleobject(Handle, Alertable, Timeout);
    FreeLibrary(ntdll);
    return status;
}
