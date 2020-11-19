#ifndef PROTOCOL_H
#define PROTOCOL_H


#define UI_SOCKET_PORT  9527

class CMDTYPE {
public:
    static const short CMDTYPE_QUERY    = 1;
    static const short CMDTYPE_RESULT   = 2;
    static const short CMDTYPE_STIMULUS = 3;
};

class UICommand {
public:
    int type;
    int content;
};


#endif // PROTOCOL_H
