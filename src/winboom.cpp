#include <windows.h>
#include <iostream>

typedef NTSTATUS(NTAPI* RtlAdjustPrivilege_t)(
    ULONG Privilege,
    BOOLEAN Enable,
    BOOLEAN CurrentThread,
    PBOOLEAN Enabled
);

typedef NTSTATUS(NTAPI* NtRaiseHardError_t)(
    NTSTATUS ErrorStatus,
    ULONG NumberOfParameters,
    ULONG UnicodeStringParameterMask,
    PULONG_PTR Parameters,
    ULONG ValidResponseOption,
    PULONG Response
);

int main() {
    int result = MessageBoxA(
        NULL, "Do you want to crash your PC?", "winboom", MB_YESNO | MB_ICONINFORMATION
    );

    if (result == IDYES) {
        // boom!
        HMODULE ntdll = LoadLibraryA("ntdll.dll");
        if (!ntdll) {
            std::cerr << "Failed to load ntdll.dll" << std::endl;
            return 1;
        }

        auto RtlAdjustPrivilege = (RtlAdjustPrivilege_t)GetProcAddress(ntdll, "RtlAdjustPrivilege");
        auto NtRaiseHardError = (NtRaiseHardError_t)GetProcAddress(ntdll, "NtRaiseHardError");

        if (!RtlAdjustPrivilege || !NtRaiseHardError) {
            std::cerr << "Failed to resolve ntdll.dll functions!" << std::endl;
            return 1;
        }

        BOOLEAN oldValue;
        NTSTATUS status = RtlAdjustPrivilege(
            19,
            TRUE,
            FALSE,
            &oldValue
        );
    
        if (status != 0) {
            std::cerr << "RtlAdjustPrivilege failed: " << std::hex << status << std::endl;
            return 1;
        }

        ULONG response;
        status = NtRaiseHardError(
            0xC0000022,
            0,
            0,
            nullptr,
            6,
            &response
        );

        std::cout << "NtRaiseHardError returned: " << std::hex << status << std::endl;
    }

    return 0;
}