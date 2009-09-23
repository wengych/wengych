#pragma once

class InterphonePool
{
public:
    InterphonePool(void);
    ~InterphonePool(void);

    static void InitInterPhonePool();

    void AddChannel(int id);
    void ModifyChannel( int id, bool status );
    int GetRandomAvailableChannel();
};
