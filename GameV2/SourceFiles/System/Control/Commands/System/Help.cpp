#include "../../HeaderFiles/System/Control/Commands/System/HelpCmd.h"

#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/Control/Invoker/IInvoker.h"

HelpCmd::HelpCmd(IInvoker& invoker)
    : invoker(invoker)
{
}

bool HelpCmd::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == NAME;
}

bool HelpCmd::execute(const std::vector<std::string>& args, IUserInterface& ui) const {

    ui.inform("=============User Manual=============");

    for (size_t i = 0; i < invoker.getCommands().size(); i++)
    {
        ui.inform("'"+ invoker.getCommands()[i]->getName() + "':" + invoker.getCommands()[i]->getDescription());
    }

    ui.inform("For more information about the commands/ possible errors or the configuration call support.");
    return true;
}

const std::string& HelpCmd::getDescription() const {
    return DESCRIPTION;
}

const std::string& HelpCmd::getName() const
{
    return NAME;
}

ICommand* HelpCmd::clone() const {
    return new HelpCmd(*this);
}
const std::string  HelpCmd::NAME = "help";
const std::string  HelpCmd::DESCRIPTION = "Used to pull out the descrioption for the other commands.";