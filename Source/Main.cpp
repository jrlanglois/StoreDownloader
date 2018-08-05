#include "MainComponent.h"

class StoreDownloaderApplication : public JUCEApplication
{
public:
    StoreDownloaderApplication()                            {}
    ~StoreDownloaderApplication()                           {}
    const String getApplicationName() override              { return ProjectInfo::projectName; }
    const String getApplicationVersion() override           { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override              { return false; }
    void initialise (const String&) override                { mainWindow.reset (new MainWindow (getApplicationName())); }
    void shutdown() override                                { mainWindow = nullptr; }
    void systemRequestedQuit() override                     { quit(); }
    void anotherInstanceStarted (const String&) override    {}

private:
    //==============================================================================
    class MainWindow : public DocumentWindow
    {
    public:
        MainWindow (const String& name) :
            DocumentWindow (name, Desktop::getInstance().getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId), DocumentWindow::closeButton)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);
            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

    std::unique_ptr<MainWindow> mainWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StoreDownloaderApplication)
};

//==============================================================================
START_JUCE_APPLICATION (StoreDownloaderApplication)
