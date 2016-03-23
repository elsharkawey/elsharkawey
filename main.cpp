#include <irrlicht.h>
#include <IGUIImage.h>
using namespace irr;

using namespace core;

using namespace video;

using namespace gui;
#if defined(_MSC_VER)
#pragma comment(lib, "Irrlicht.lib")
#endif
struct SAppContext
{
IrrlichtDevice *device;
};
// Define some values that we'll use to identify individual GUIcontrols.
enum
{
GUI_ID_QUIT_BUTTON = 101,
GUI_ID_NEW_WINDOW_BUTTON
};
class MyEventReceiver: public IEventReceiver
{
public:
MyEventReceiver(SAppContext & context) : Context(context) { }
virtual bool OnEvent(const SEvent& event)
{
if (event.EventType == EET_GUI_EVENT)
{
s32 id = event.GUIEvent.Caller->getID();
IGUIEnvironment* guienv = Context.device->getGUIEnvironment();
if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
{
if (id == GUI_ID_QUIT_BUTTON)
{
Context.device->closeDevice();
return true;
}
if (id == GUI_ID_NEW_WINDOW_BUTTON)
{
IGUIWindow* window = guienv->addWindow(rect<s32>(100, 100, 300, 200),
false, L"New window");
return true;
}
}
}
return false;
}
private:
    SAppContext & Context;
};
int main()
{
IrrlichtDevice* device = createDevice(EDT_OPENGL,
dimension2d<u32>(640, 480), 16,
false, false, false, 0);
if (!device)
return 1;
IVideoDriver* driver = device->getVideoDriver();
IGUIEnvironment* guienv = device->getGUIEnvironment();
IGUIFont* font = guienv->getFont("lucida.xml");
guienv->addStaticText(L"Hello World!",
rect<s32>(100, 20, 200, 30), true);
recti buttonRect = recti(200,170,228,202);

IGUIButton *mybutton = guienv->addButton(rect<s32>(250, 20, 250 + 120, 50), 0,GUI_ID_QUIT_BUTTON, L"Exit2", L"ExitsProgram");

mybutton->setImage(driver->getTexture("1.jpg"));
mybutton->setUseAlphaChannel(true);
IGUIButton *mybutton2 = guienv->addButton(rect<s32>(400, 20, 400 + 120, 50), 0,GUI_ID_NEW_WINDOW_BUTTON, L"New Window",L"Launches a new Window");

mybutton2->setImage(driver->getTexture("1.jpg"));

SAppContext context;
context.device = device;
MyEventReceiver receiver(context);
device->setEventReceiver(&receiver);
while (device->run())
{
driver->beginScene(true, true, SColor(255, 128, 128, 128));
guienv->drawAll();
font->draw(L"Another text", rect<s32>(300, 300, 300, 50),
SColor(255, 255, 255, 255));
driver->endScene();

}
device->drop();
return 0;
}
