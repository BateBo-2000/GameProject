#include "../../HeaderFiles/System/Control/Commands/System/ExitCmd.h"

#include "../../HeaderFiles/System/Control/Invoker/IInvoker.h"
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"

ExitCommand::ExitCommand(IInvoker& invoker, IUserInterface& adminPlayer):invoker(invoker), adminUI(adminPlayer)
{
}

ICommand* ExitCommand::clone() const {
    return new ExitCommand(*this);
}

bool ExitCommand::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == NAME;
}

bool ExitCommand::execute(const std::vector<std::string>& args, IUserInterface& ui) const {

    if (&ui != &adminUI) {
        ui.inform("You dont have administrator privilidges.");
        return false;
    }

    if (adminUI.confirm("Are you sure you want to exit?\nAll your unsaved progress will be lost.")) {
        invoker.requestExit();
        return true;
    }
    else {
        return false;
    }
}

const std::string& ExitCommand::getDescription() const
{
    return DESCRIPTION;
}

const std::string& ExitCommand::getName() const
{
    return NAME;
}
const std::string  ExitCommand::NAME = "exit";
const std::string  ExitCommand::DESCRIPTION = "Exit the application immediately; unsaved progress will be lost.";