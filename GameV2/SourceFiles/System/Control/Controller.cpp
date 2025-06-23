#include "../../HeaderFiles/System/Control/Controller.h"

#include "../../HeaderFiles/Communication/Loggers/ILogger.h"
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/Control/Invoker/IInvoker.h"

#include <string>

Controller::Controller(ILogger& logger, IUserInterface& livingUi, IUserInterface& undeadUi, IInvoker& invoker)
    : logger(logger), livingUi(livingUi), undeadUi(undeadUi), invoker(invoker)
{
}

Controller::~Controller() {}

void normalizeInput(std::string& input) {
    //TODO
}

void Controller::run() {
    livingUi.inform("Welcome to the game! Type 'help' for commands.");
    undeadUi.inform("Welcome to the game! Type 'help' for commands.");

    while (true) {
        Faction turn = invoker.getCurrentFaction();

        IUserInterface& ui = (turn == Faction::Living ? livingUi : undeadUi);

        std::string line = ui.askQuestion("Enter command:");
        if (line.empty()) continue;

        normalizeInput(line);

        bool ok = false;
        
        try
        {
            ok = invoker.executeCommandLine(line);
        }
        catch (const std::exception& e)
        {
            ui.error(string("Something went wrong executing this command:") + e.what());
        }
          
        if (!ok) {
            ui.error("Command not succesfull: " + line);
        }

        logger.log("Command: " + line + (ok ? " [ok]" : " [fail]"));

        if (invoker.shouldExit()) {
            break;
        }
    }
}