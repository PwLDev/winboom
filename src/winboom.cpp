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

typedef BOOL(WINAPI* IsUserAnAdmin_t)(void);

bool isUserAdmin() {
    HMODULE shell32 = LoadLibraryA("shell32.dll");
    if (!shell32) {
        std::cerr << "Failed to load shell32.dll" << std::endl;
        return false;
    }

    auto IsUserAnAdmin = (IsUserAnAdmin_t)GetProcAddress(shell32, "IsUserAnAdmin");
    if (!IsUserAnAdmin) {
        std::cerr << "Failed to resolve IsUserAnAdmin function." << std::endl;
        FreeLibrary(shell32);
        return false;
    }

    BOOL result = IsUserAnAdmin();
    FreeLibrary(shell32);
    return result != FALSE;
}

int main() {
    bool isAdmin = isUserAdmin();
    if (!isAdmin) {
        int box = MessageBoxA(
            NULL, "You need to run winboom as an administrator.", "winboom", MB_OK | MB_ICONWARNING
        );
        return 0;
    }

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
        NTSTATUS privilegeStatus = RtlAdjustPrivilege(
            19,
            TRUE,
            FALSE,
            &oldValue
        );
    
        if (privilegeStatus != 0) {
            std::cerr << "RtlAdjustPrivilege failed: " << std::hex << privilegeStatus << std::endl;
            return 1;
        }

        ULONG response;
        NTSTATUS status = NtRaiseHardError(
            0xC000007B,
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