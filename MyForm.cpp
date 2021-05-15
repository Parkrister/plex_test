#include "MyForm.h"
#include <Windows.h>

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
int Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CppWinForm1::MyForm form;
	Application::Run(%form);
	return 0;
}
