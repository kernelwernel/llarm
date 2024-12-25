#include <iostream>
#include <windows.h>
#include <string>
#include <chrono>
#include <vector>
#include <winternl.h>

typedef struct _SYSTEM_MODULE_INFORMATION {
    PVOID  Reserved[2];
    PVOID  ImageBaseAddress;
    ULONG  ImageSize;
    ULONG  Flags;
    USHORT Index;
    USHORT NameLength;
    USHORT LoadCount;
    USHORT PathLength;
    CHAR   ImageName[256];
} SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;

typedef struct _SYSTEM_MODULE_INFORMATION_EX {
    ULONG  NumberOfModules;
    SYSTEM_MODULE_INFORMATION Module[1];
} SYSTEM_MODULE_INFORMATION_EX, * PSYSTEM_MODULE_INFORMATION_EX;

typedef NTSTATUS(__stdcall* NTQUERYSYSTEMINFORMATION)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
    );
typedef NTSTATUS(__stdcall* NTALLOCATEVIRTUALMEMORY)(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    ULONG_PTR ZeroBits,
    PSIZE_T RegionSize,
    ULONG AllocationType,
    ULONG Protect
    );
typedef NTSTATUS(__stdcall* NTFREEVIRTUALMEMORY)(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    PSIZE_T RegionSize,
    ULONG FreeType
    );

typedef NTSTATUS(__stdcall* NTOPENFILE)(
    PHANDLE FileHandle,
    ACCESS_MASK DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PIO_STATUS_BLOCK IoStatusBlock,
    ULONG ShareAccess,
    ULONG OpenOptions
    );

typedef NTSTATUS(__stdcall* NTCREATESECTION)(
    PHANDLE SectionHandle,
    ACCESS_MASK DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PLARGE_INTEGER MaximumSize,
    ULONG SectionPageProtection,
    ULONG AllocationAttributes,
    HANDLE FileHandle
    );

typedef enum _SECTION_INHERIT
{
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;

typedef NTSTATUS(__stdcall* NTMAPVIEWOFSECTION)(
    HANDLE SectionHandle,
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    ULONG_PTR ZeroBits,
    SIZE_T CommitSize,
    PLARGE_INTEGER SectionOffset,
    PSIZE_T ViewSize,
    SECTION_INHERIT InheritDisposition,
    ULONG AllocationType,
    ULONG Win32Protect
    );

typedef NTSTATUS(__stdcall* NTUNMAPVIEWOFSECTION)(
    HANDLE ProcessHandle,
    PVOID BaseAddress
    );

typedef NTSTATUS(__stdcall* NTCLOSE)(HANDLE Handle);

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)

constexpr ULONG SystemModuleInformation = 11;

inline void RtlInitUnicodeString(
    PUNICODE_STRING DestinationString,
    PCWSTR SourceString
) {
    if (SourceString == NULL) {
        DestinationString->Length = 0;
        DestinationString->MaximumLength = 0;
        DestinationString->Buffer = NULL;
    }
    else {
        size_t len = wcslen(SourceString) * sizeof(WCHAR);

        DestinationString->Length = (USHORT)len;
        DestinationString->MaximumLength = (USHORT)(len + sizeof(WCHAR));
        DestinationString->Buffer = (PWSTR)SourceString;
    }
}


inline static bool GetFunctionAddresses(HMODULE hModule, const char* names[], void** functions, size_t count) {
    const PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(hModule);
    const PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(
        reinterpret_cast<BYTE*>(hModule) + dosHeader->e_lfanew);
    const PIMAGE_EXPORT_DIRECTORY exportDirectory = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(
        reinterpret_cast<BYTE*>(hModule) + ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

    const DWORD* nameOffsets = reinterpret_cast<DWORD*>(reinterpret_cast<BYTE*>(hModule) + exportDirectory->AddressOfNames);
    const DWORD* funcOffsets = reinterpret_cast<DWORD*>(reinterpret_cast<BYTE*>(hModule) + exportDirectory->AddressOfFunctions);
    const WORD* ordinals = reinterpret_cast<WORD*>(reinterpret_cast<BYTE*>(hModule) + exportDirectory->AddressOfNameOrdinals);

    size_t resolved = 0;
    for (DWORD i = 0; i < exportDirectory->NumberOfNames && resolved < count; ++i) {
        const char* exportName = reinterpret_cast<const char*>(reinterpret_cast<BYTE*>(hModule) + nameOffsets[i]);
        for (size_t j = 0; j < count; ++j) {
            if (functions[j] == nullptr && strcmp(exportName, names[j]) == 0) {
                functions[j] = reinterpret_cast<void*>(reinterpret_cast<BYTE*>(hModule) + funcOffsets[ordinals[i]]);
                ++resolved;
            }
        }
    }

    return resolved == count;
}

inline static void analyze_driver(const char* filePath, const HMODULE ntdll, const HANDLE hProcess) {
    const char* functionNames[] = { "NtOpenFile", "NtCreateSection", "NtMapViewOfSection", "NtUnmapViewOfSection", "NtClose" };
    void* functionPointers[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };

    if (!GetFunctionAddresses(ntdll, functionNames, functionPointers, 5))
        return;

    const auto NtOpenFile = reinterpret_cast<NTOPENFILE>(functionPointers[0]);
    const auto NtCreateSection = reinterpret_cast<NTCREATESECTION>(functionPointers[1]);
    const auto NtMapViewOfSection = reinterpret_cast<NTMAPVIEWOFSECTION>(functionPointers[2]);
    const auto NtUnmapViewOfSection = reinterpret_cast<NTUNMAPVIEWOFSECTION>(functionPointers[3]);
    const auto NtClose = reinterpret_cast<NTCLOSE>(functionPointers[4]);

    UNICODE_STRING unicodeFilePath;
    OBJECT_ATTRIBUTES objAttr{};
    IO_STATUS_BLOCK ioStatusBlock;
    HANDLE fileHandle;

    WCHAR widePath[512];
    MultiByteToWideChar(CP_ACP, 0, filePath, -1, widePath, 512);
    RtlInitUnicodeString(&unicodeFilePath, widePath);
    InitializeObjectAttributes(&objAttr, &unicodeFilePath, OBJ_CASE_INSENSITIVE, NULL, NULL);

    NTSTATUS status = NtOpenFile(
        &fileHandle,
        FILE_GENERIC_READ,
        &objAttr,
        &ioStatusBlock,
        FILE_SHARE_READ,
        FILE_NON_DIRECTORY_FILE
    );

    if (!NT_SUCCESS(status))
        return;

    HANDLE sectionHandle;
    status = NtCreateSection(
        &sectionHandle,
        SECTION_MAP_READ,
        NULL,
        NULL,
        PAGE_READONLY,
        SEC_COMMIT,
        fileHandle
    );

    if (!NT_SUCCESS(status)) {
        NtClose(fileHandle);
        return;
    }

    PVOID baseAddress = NULL;
    SIZE_T viewSize = 0;
    status = NtMapViewOfSection(
        sectionHandle,
        hProcess,
        &baseAddress,
        0,
        0,
        NULL,
        &viewSize,
        ViewShare,
        0,
        PAGE_READONLY
    );

    auto close = [&]() -> void {
        NtUnmapViewOfSection(hProcess, baseAddress);
        NtClose(sectionHandle);
        NtClose(fileHandle);
    };

    if (!NT_SUCCESS(status)) {
        close();
        return;
    }

    BYTE* mutableBaseAddress = const_cast<BYTE*>(reinterpret_cast<const BYTE*>(baseAddress));
    std::vector<std::string> outputBuffer;

    PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(mutableBaseAddress);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        close();
        return;
    }

    PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(mutableBaseAddress + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        close();
        return;
    }

    PIMAGE_DATA_DIRECTORY importDirectory = &ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (importDirectory->VirtualAddress == 0) {
        close();
        return;
    }

    PIMAGE_IMPORT_DESCRIPTOR importDescriptor = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(mutableBaseAddress + importDirectory->VirtualAddress);

    if ((BYTE*)importDescriptor < (BYTE*)baseAddress || (BYTE*)importDescriptor >= (BYTE*)baseAddress + viewSize) {
        return;
    }

    int importOrder = 1; // To keep track of the order of imports
    while (importDescriptor->Name != 0) {
        if ((BYTE*)importDescriptor < (BYTE*)baseAddress || (BYTE*)importDescriptor >= (BYTE*)baseAddress + viewSize) {
            break;
        }

        BYTE* nameAddress = mutableBaseAddress + importDescriptor->Name;

        if (nameAddress < mutableBaseAddress || nameAddress >= mutableBaseAddress + viewSize) {
            break;
        }

        const char* dllName = reinterpret_cast<const char*>(nameAddress);
        // Import + Module name + RVA
        outputBuffer.emplace_back(std::to_string(importOrder) + dllName + std::to_string(importDescriptor->Name));

        PIMAGE_THUNK_DATA thunkILT = reinterpret_cast<PIMAGE_THUNK_DATA>(mutableBaseAddress + importDescriptor->OriginalFirstThunk);
        PIMAGE_THUNK_DATA thunkIAT = reinterpret_cast<PIMAGE_THUNK_DATA>(mutableBaseAddress + importDescriptor->FirstThunk);

        int functionOrder = 1; // To track the order of functions within the import
        while (thunkILT->u1.AddressOfData != 0) {
            if (reinterpret_cast<const BYTE*>(thunkILT) < mutableBaseAddress ||
                reinterpret_cast<const BYTE*>(thunkILT) >= mutableBaseAddress + viewSize) {
                break;
            }

            if (thunkILT->u1.Ordinal & IMAGE_ORDINAL_FLAG) {
                // Import by ordinal
                DWORD ordinal = static_cast<DWORD>(thunkILT->u1.Ordinal & 0xFFFF);
                // Function + Imported by ordinal + RVA
                outputBuffer.emplace_back(std::to_string(functionOrder) +
                    std::to_string(ordinal) + std::to_string(static_cast<DWORD>(reinterpret_cast<BYTE*>(thunkIAT) - mutableBaseAddress)));
            }
            else {
                // Import by name
                PIMAGE_IMPORT_BY_NAME importByName = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(mutableBaseAddress + thunkILT->u1.AddressOfData);

                if (reinterpret_cast<const BYTE*>(importByName) < mutableBaseAddress ||
                    reinterpret_cast<const BYTE*>(importByName) >= mutableBaseAddress + viewSize) {
                    break;
                }

                // Function + Name + Hint + RVA
                outputBuffer.emplace_back(std::to_string(functionOrder) +
                    importByName->Name +
                    std::to_string(importByName->Hint) +
                    std::to_string(static_cast<DWORD>(reinterpret_cast<BYTE*>(thunkIAT) - mutableBaseAddress)));
            }

            thunkILT++;
            thunkIAT++;
            functionOrder++;
        }

        importDescriptor++;
        importOrder++;
    }

    close();

    std::string finalOutput;
    finalOutput.reserve(10000);
    for (const auto& line : outputBuffer) {
        finalOutput += line;
    }
}

int main() {
    const HMODULE hModule = LoadLibraryA("ntdll.dll");
    if (!hModule) return 1;    

    const char* functionNames[] = { "NtQuerySystemInformation", "NtAllocateVirtualMemory", "NtFreeVirtualMemory" };
    void* functionPointers[3] = { nullptr, nullptr, nullptr };

    if (!GetFunctionAddresses(hModule, functionNames, functionPointers, 3)) return 1;

    const auto NtQuerySystemInformation = reinterpret_cast<NTQUERYSYSTEMINFORMATION>(functionPointers[0]);
    const auto NtAllocateVirtualMemory = reinterpret_cast<NTALLOCATEVIRTUALMEMORY>(functionPointers[1]);
    const auto NtFreeVirtualMemory = reinterpret_cast<NTFREEVIRTUALMEMORY>(functionPointers[2]);

    ULONG ulSize = 0;
    NTSTATUS status = NtQuerySystemInformation(SystemModuleInformation, nullptr, 0, &ulSize);
    if (status != STATUS_INFO_LENGTH_MISMATCH) return 1;   

    const HANDLE hProcess = GetCurrentProcess();
    PVOID allocatedMemory = nullptr;
    SIZE_T regionSize = ulSize;
    NtAllocateVirtualMemory(hProcess, &allocatedMemory, 0, &regionSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    auto pSystemModuleInfoEx = reinterpret_cast<PSYSTEM_MODULE_INFORMATION_EX>(allocatedMemory);
    status = NtQuerySystemInformation(SystemModuleInformation, pSystemModuleInfoEx, ulSize, &ulSize);
    if (!NT_SUCCESS(status)) {
        NtFreeVirtualMemory(hProcess, &allocatedMemory, &regionSize, MEM_RELEASE);
        return 1;
    }

    for (ULONG i = 0; i < pSystemModuleInfoEx->NumberOfModules; ++i) {
        const char* driverPath = reinterpret_cast<const char*>(pSystemModuleInfoEx->Module[i].ImageName);
        analyze_driver(driverPath, hModule, hProcess);
    }

    NtFreeVirtualMemory(hProcess, &allocatedMemory, &regionSize, MEM_RELEASE);
    return 0;
}