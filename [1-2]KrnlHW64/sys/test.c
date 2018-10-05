//ULONG __cdecl DbgPrint ( _In_z_ _Printf_format_string_ PCSTR Format, ...);
int __cdecl DbgPrint (char* Format, ...);

int main() { DbgPrint("DebugStringHere\n"); }
