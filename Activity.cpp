#include "Activity.h"

Activity::Activity()
    : actionType("General"), description("No Description"), threatFlag(false), dataAccessed(0.0) {}

Activity::Activity(std::string type, std::string desc, bool flag, FileSize size)
    : actionType(type), description(desc), threatFlag(flag), dataAccessed(size) {}

std::string Activity::getActionType() const { return actionType; }
std::string Activity::getDescription() const { return description; }
bool Activity::isFlagged() const { return threatFlag; }
FileSize Activity::getDataAccessed() const { return dataAccessed; }

std::ostream& operator<<(std::ostream& out, const Activity& act) {
    out << "[" << act.actionType << "] " << act.description;
    if (act.dataAccessed.getSize() > 0.0)
        out << " (" << act.dataAccessed << ")";
    out << (act.threatFlag ? "  -->  THREAT DETECTED" : "  -->  Normal");
    return out;
}
