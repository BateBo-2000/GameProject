#include "../../HeaderFiles/System/Control/Commands/System/ExitCmd.h"


ExitCommand::ExitCommand(IInvoker& invoker, IUserInterface& ui):invoker(invoker), ui(ui)
{
    
}

bool ExitCommand::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && (args[0] == "exit" || args[0] == "quit");
}

bool ExitCommand::execute(const std::vector<std::string>& args) const {
    if (ui.confirm("Are you sure you want to exit?\nAll your unsaved progress will be lost.")) {
        invoker.requestExit();
    }
    else {
        //do nothing
    }
    
    return true;
}

ICommand* ExitCommand::clone() const {
    return new ExitCommand(invoker, ui);
}
