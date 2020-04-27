#ifndef Event_H
#define Event_H
enum EventType
{
    DEATH,
    DINNER
};

struct Event
{
    enum EventType type;
};
#endif