#include "../../HeaderFiles/System/Control/Commands/System/ExitCmd.h"

#include "../../HeaderFiles/System/Control/Invoker/IInvoker.h"
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"

ExitCommand::ExitCommand(IInvoker& invoker, IUserInterface& ui):invoker(invoker), ui(ui)
{
}

ICommand* ExitCommand::clone() const {
    return new ExitCommand(*this);
}

bool ExitCommand::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == NAME;
}

bool ExitCommand::execute(const std::vector<std::string>& args) const {
    if (ui.confirm("Are you sure you want to exit?\nAll your unsaved progress will be lost.")) {
        invoker.requestExit();
    }
    return true;
}

const std::string& ExitCommand::getDescription() const
{
    return DESCRIPTION;
}

const std::string& ExitCommand::getName() const
{
    return NAME;
}
static const std::string  NAME = "exit";
static const std::string  DESCRIPTION = "Exit the application immediately; unsaved progress will be lost.";