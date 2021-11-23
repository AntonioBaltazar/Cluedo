#ifndef DASHBOARD_H_INCLUDED
#define DASHBOARD_H_INCLUDED

#include "../AnimatedElement.h"
#include "../Player.h"

class Dashboard : public AnimatedElement {
private:
public:
    // Constructors & Destructor
    Dashboard();
    Dashboard(int trslX, int trslY, int maxX, int maxY);
    ~Dashboard();

    // Methods
    void renderTurn(Player* p);
};


#endif // DASHBOARD_H_INCLUDED
