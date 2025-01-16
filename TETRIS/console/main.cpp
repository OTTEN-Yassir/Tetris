#include "View.h"
#include "Controller.h"

int main()
{
    View view;
    Controller controller(view);
    controller.start();

    return 0;
}
