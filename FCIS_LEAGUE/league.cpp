#include "leaguefunctions.h"
#include "league.h"
#include <Windows.h>
using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Media;
[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    FCISLEAGUE::league lea;
    Application::Run(% lea);
}
